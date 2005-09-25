#include "OSPFInterfaceStateNotDesignatedRouter.hpp"
#include "OSPFInterfaceStateDown.hpp"
#include "OSPFInterfaceStateLoopback.hpp"
#include "OSPFArea.hpp"
#include "OSPFRouter.hpp"
#include "MessageHandler.hpp"

void OSPF::InterfaceStateNotDesignatedRouter::ProcessEvent (OSPF::Interface* intf, OSPF::Interface::InterfaceEventType event)
{
    if (event == OSPF::Interface::NeighborChange) {
        CalculateDesignatedRouter (intf);
    }
    if (event == OSPF::Interface::InterfaceDown) {
        intf->Reset ();
        ChangeState (intf, new OSPF::InterfaceStateDown, this);
    }
    if (event == OSPF::Interface::LoopIndication) {
        intf->Reset ();
        ChangeState (intf, new OSPF::InterfaceStateLoopback, this);
    }
    if (event == OSPF::Interface::HelloTimer) {
        if (intf->GetType () == OSPF::Interface::Broadcast) {
            intf->SendHelloPacket (OSPF::AllSPFRouters);
        } else {    // OSPF::Interface::NBMA
            if (intf->GetRouterPriority () > 0) {
                unsigned long neighborCount = intf->GetNeighborCount ();
                for (unsigned long i = 0; i < neighborCount; i++) {
                    const OSPF::Neighbor* neighbor = intf->GetNeighbor (i);
                    if (neighbor->GetPriority () > 0) {
                        intf->SendHelloPacket (neighbor->GetAddress ());
                    }
                }
            } else {
                intf->SendHelloPacket (intf->GetDesignatedRouter ().ipInterfaceAddress);
                intf->SendHelloPacket (intf->GetBackupDesignatedRouter ().ipInterfaceAddress);
            }
        }
        intf->GetArea ()->GetRouter ()->GetMessageHandler ()->StartTimer (intf->GetHelloTimer (), intf->GetHelloInterval ());
    }
    if (event == OSPF::Interface::AcknowledgementTimer) {
        intf->SendDelayedAcknowledgements ();
    }
}

