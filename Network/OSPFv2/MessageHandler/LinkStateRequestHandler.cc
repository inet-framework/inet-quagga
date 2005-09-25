#include "LinkStateRequestHandler.h"
#include "OSPFNeighbor.h"
#include "OSPFRouter.h"
#include <vector>

OSPF::LinkStateRequestHandler::LinkStateRequestHandler (OSPF::Router* containingRouter) :
    OSPF::IMessageHandler (containingRouter)
{
}

void OSPF::LinkStateRequestHandler::ProcessPacket (OSPFPacket* packet, OSPF::Interface* intf, OSPF::Neighbor* neighbor)
{
    router->GetMessageHandler ()->PrintEvent ("Link State Request packet received", intf, neighbor);

    OSPF::Neighbor::NeighborStateType neighborState = neighbor->GetState ();

    if ((neighborState == OSPF::Neighbor::ExchangeState) ||
        (neighborState == OSPF::Neighbor::LoadingState) ||
        (neighborState == OSPF::Neighbor::FullState))
    {
        OSPFLinkStateRequestPacket* lsRequestPacket = check_and_cast<OSPFLinkStateRequestPacket*> (packet);

        unsigned int          requestCount = lsRequestPacket->getRequestsArraySize ();
        bool                  error        = false;
        std::vector<OSPFLSA*> lsas;

        ev << "  Processing packet contents:\n";

        for (int i = 0; i < requestCount; i++) {
            LSARequest&      request = lsRequestPacket->getRequests (i);
            OSPF::LSAKeyType lsaKey;
            char             addressString[16];

            ev << "    LSARequest: type="
               << request.lsType
               << ", LSID="
               << AddressStringFromULong (addressString, sizeof (addressString), request.linkStateID)
               << ", advertisingRouter="
               << AddressStringFromULong (addressString, sizeof (addressString), request.advertisingRouter.getInt ())
               << "\n";

            lsaKey.linkStateID = request.linkStateID;
            lsaKey.advertisingRouter = request.advertisingRouter.getInt ();

            OSPFLSA* lsaInDatabase = router->FindLSA (static_cast<LSAType> (request.lsType), lsaKey, intf->GetArea ()->GetAreaID ());

            if (lsaInDatabase != NULL) {
                lsas.push_back (lsaInDatabase);
            } else {
                error = true;
                neighbor->ProcessEvent (OSPF::Neighbor::BadLinkStateRequest);
                break;
            }
        }

        if (!error) {
            int                   updatesCount   = lsas.size ();
            int                   ttl            = (intf->GetType () == OSPF::Interface::Virtual) ? VIRTUAL_LINK_TTL : 1;
            OSPF::MessageHandler* messageHandler = router->GetMessageHandler ();

            for (int j = 0; j < updatesCount; j++) {
                OSPFLinkStateUpdatePacket* updatePacket = intf->CreateUpdatePacket (lsas[j]);
                if (updatePacket != NULL) {
                    if (intf->GetType () == OSPF::Interface::Broadcast) {
                        if ((intf->GetState () == OSPF::Interface::DesignatedRouterState) ||
                            (intf->GetState () == OSPF::Interface::BackupState) ||
                            (intf->GetDesignatedRouter () == OSPF::NullDesignatedRouterID))
                        {
                            messageHandler->SendPacket (updatePacket, OSPF::AllSPFRouters, intf->GetIfIndex (), ttl);
                        } else {
                            messageHandler->SendPacket (updatePacket, OSPF::AllDRouters, intf->GetIfIndex (), ttl);
                        }
                    } else {
                        if (intf->GetType () == OSPF::Interface::PointToPoint) {
                            messageHandler->SendPacket (updatePacket, OSPF::AllSPFRouters, intf->GetIfIndex (), ttl);
                        } else {
                            messageHandler->SendPacket (updatePacket, neighbor->GetAddress (), intf->GetIfIndex (), ttl);
                        }
                    }

                }
            }
            // These update packets should not be placed on retransmission lists
        }
    }
}
