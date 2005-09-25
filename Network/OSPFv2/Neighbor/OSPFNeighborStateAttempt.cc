#include "OSPFNeighborStateAttempt.hpp"
#include "OSPFNeighborStateDown.hpp"
#include "OSPFNeighborStateInit.hpp"
#include "MessageHandler.hpp"
#include "OSPFInterface.hpp"
#include "OSPFArea.hpp"
#include "OSPFRouter.hpp"

void OSPF::NeighborStateAttempt::ProcessEvent (OSPF::Neighbor* neighbor, OSPF::Neighbor::NeighborEventType event)
{
    if ((event == OSPF::Neighbor::KillNeighbor) || (event == OSPF::Neighbor::LinkDown)) {
        MessageHandler* messageHandler = neighbor->GetInterface ()->GetArea ()->GetRouter ()->GetMessageHandler ();
        neighbor->Reset ();
        messageHandler->ClearTimer (neighbor->GetInactivityTimer ());
        ChangeState (neighbor, new OSPF::NeighborStateDown, this);
    }
    if (event == OSPF::Neighbor::InactivityTimer) {
        neighbor->Reset ();
        if (neighbor->GetInterface ()->GetType () == OSPF::Interface::NBMA) {
            MessageHandler* messageHandler = neighbor->GetInterface ()->GetArea ()->GetRouter ()->GetMessageHandler ();
            messageHandler->StartTimer (neighbor->GetPollTimer (), neighbor->GetInterface ()->GetPollInterval ());
        }
        ChangeState (neighbor, new OSPF::NeighborStateDown, this);
    }
    if (event == OSPF::Neighbor::HelloReceived) {
        MessageHandler* messageHandler = neighbor->GetInterface ()->GetArea ()->GetRouter ()->GetMessageHandler ();
        messageHandler->ClearTimer (neighbor->GetInactivityTimer ());
        messageHandler->StartTimer (neighbor->GetInactivityTimer (), neighbor->GetRouterDeadInterval ());
        ChangeState (neighbor, new OSPF::NeighborStateInit, this);
    }
}
