#include "OSPFInterfaceStateDown.h"
#include "MessageHandler.h"
#include "OSPFArea.h"
#include "OSPFRouter.h"
#include "OSPFInterfaceStatePointToPoint.h"
#include "OSPFInterfaceStateNotDesignatedRouter.h"
#include "OSPFInterfaceStateWaiting.h"
#include "OSPFInterfaceStateLoopback.h"

void OSPF::InterfaceStateDown::ProcessEvent (OSPF::Interface* intf, OSPF::Interface::InterfaceEventType event)
{
    if (event == OSPF::Interface::InterfaceUp) {
        OSPF::MessageHandler* messageHandler = intf->GetArea ()->GetRouter ()->GetMessageHandler ();
        messageHandler->StartTimer (intf->GetHelloTimer (), truncnormal (0.1, 0.01)); // add some deviation to avoid startup collisions
        messageHandler->StartTimer (intf->GetAcknowledgementTimer (), intf->GetAcknowledgementDelay ());
        switch (intf->GetType ()) {
            case OSPF::Interface::PointToPoint:
            case OSPF::Interface::PointToMultiPoint:
            case OSPF::Interface::Virtual:
                ChangeState (intf, new OSPF::InterfaceStatePointToPoint, this);
                break;

            case OSPF::Interface::NBMA:
                if (intf->GetRouterPriority () == 0) {
                    ChangeState (intf, new OSPF::InterfaceStateNotDesignatedRouter, this);
                } else {
                    ChangeState (intf, new OSPF::InterfaceStateWaiting, this);
                    messageHandler->StartTimer (intf->GetWaitTimer (), intf->GetRouterDeadInterval ());

                    long neighborCount = intf->GetNeighborCount ();
                    for (long i = 0; i < neighborCount; i++) {
                        OSPF::Neighbor* neighbor = intf->GetNeighbor (i);
                        if (neighbor->GetPriority () > 0) {
                            neighbor->ProcessEvent (OSPF::Neighbor::Start);
                        }
                    }
                }
                break;

            case OSPF::Interface::Broadcast:
                if (intf->GetRouterPriority () == 0) {
                    ChangeState (intf, new OSPF::InterfaceStateNotDesignatedRouter, this);
                } else {
                    ChangeState (intf, new OSPF::InterfaceStateWaiting, this);
                    messageHandler->StartTimer (intf->GetWaitTimer (), intf->GetRouterDeadInterval ());
                }
                break;

            default:
                break;
        }
    }
    if (event == OSPF::Interface::LoopIndication) {
        intf->Reset ();
        ChangeState (intf, new OSPF::InterfaceStateLoopback, this);
    }
}

