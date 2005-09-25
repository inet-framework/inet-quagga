#include "OSPFNeighborStateExchangeStart.hpp"
#include "OSPFNeighborStateDown.hpp"
#include "OSPFNeighborStateInit.hpp"
#include "OSPFNeighborStateTwoWay.hpp"
#include "OSPFNeighborStateExchange.hpp"
#include "MessageHandler.hpp"
#include "OSPFInterface.hpp"
#include "OSPFArea.hpp"
#include "OSPFRouter.hpp"

void OSPF::NeighborStateExchangeStart::ProcessEvent (OSPF::Neighbor* neighbor, OSPF::Neighbor::NeighborEventType event)
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
    if (event == OSPF::Neighbor::OneWayReceived) {
        neighbor->Reset ();
        ChangeState (neighbor, new OSPF::NeighborStateInit, this);
    }
    if (event == OSPF::Neighbor::HelloReceived) {
        MessageHandler* messageHandler = neighbor->GetInterface ()->GetArea ()->GetRouter ()->GetMessageHandler ();
        messageHandler->ClearTimer (neighbor->GetInactivityTimer ());
        messageHandler->StartTimer (neighbor->GetInactivityTimer (), neighbor->GetRouterDeadInterval ());
    }
    if (event == OSPF::Neighbor::IsAdjacencyOK) {
        if (!neighbor->NeedAdjacency ()) {
            neighbor->Reset ();
            ChangeState (neighbor, new OSPF::NeighborStateTwoWay, this);
        }
    }
    if (event == OSPF::Neighbor::DDRetransmissionTimer) {
        MessageHandler* messageHandler = neighbor->GetInterface ()->GetArea ()->GetRouter ()->GetMessageHandler ();
        neighbor->RetransmitDatabaseDescriptionPacket ();
        messageHandler->StartTimer (neighbor->GetDDRetransmissionTimer (), neighbor->GetInterface ()->GetRetransmissionInterval ());
    }
    if (event == OSPF::Neighbor::NegotiationDone) {
        neighbor->CreateDatabaseSummary ();
        neighbor->SendDatabaseDescriptionPacket ();
        MessageHandler* messageHandler = neighbor->GetInterface ()->GetArea ()->GetRouter ()->GetMessageHandler ();
        messageHandler->ClearTimer (neighbor->GetDDRetransmissionTimer ());
        ChangeState (neighbor, new OSPF::NeighborStateExchange, this);
    }
}
