#include "OSPFNeighborStateDown.hpp"
#include "OSPFNeighborStateAttempt.hpp"
#include "OSPFNeighborStateInit.hpp"
#include "MessageHandler.hpp"
#include "OSPFInterface.hpp"
#include "OSPFArea.hpp"
#include "OSPFRouter.hpp"

void OSPF::NeighborStateDown::ProcessEvent (OSPF::Neighbor* neighbor, OSPF::Neighbor::NeighborEventType event)
{
    if (event == OSPF::Neighbor::Start) {
        MessageHandler* messageHandler = neighbor->GetInterface ()->GetArea ()->GetRouter ()->GetMessageHandler ();
        int             ttl            = (neighbor->GetInterface ()->GetType () == OSPF::Interface::Virtual) ? VIRTUAL_LINK_TTL : 1;

        messageHandler->ClearTimer (neighbor->GetPollTimer ());
        neighbor->GetInterface ()->SendHelloPacket (neighbor->GetAddress (), ttl);
        messageHandler->StartTimer (neighbor->GetInactivityTimer (), neighbor->GetRouterDeadInterval ());
        ChangeState (neighbor, new OSPF::NeighborStateAttempt, this);
    }
    if (event == OSPF::Neighbor::HelloReceived) {
        MessageHandler* messageHandler = neighbor->GetInterface ()->GetArea ()->GetRouter ()->GetMessageHandler ();
        messageHandler->ClearTimer (neighbor->GetPollTimer ());
        messageHandler->StartTimer (neighbor->GetInactivityTimer (), neighbor->GetRouterDeadInterval ());
        ChangeState (neighbor, new OSPF::NeighborStateInit, this);
    }
    if (event == OSPF::Neighbor::PollTimer) {
        int ttl = (neighbor->GetInterface ()->GetType () == OSPF::Interface::Virtual) ? VIRTUAL_LINK_TTL : 1;
        neighbor->GetInterface ()->SendHelloPacket (neighbor->GetAddress (), ttl);
        MessageHandler* messageHandler = neighbor->GetInterface ()->GetArea ()->GetRouter ()->GetMessageHandler ();
        messageHandler->StartTimer (neighbor->GetPollTimer (), neighbor->GetInterface ()->GetPollInterval ());
    }
}
