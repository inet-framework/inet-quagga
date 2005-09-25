#include "OSPFInterfaceStateLoopback.hpp"
#include "OSPFInterfaceStateDown.hpp"

void OSPF::InterfaceStateLoopback::ProcessEvent (OSPF::Interface* intf, OSPF::Interface::InterfaceEventType event)
{
    if (event == OSPF::Interface::InterfaceDown) {
        intf->Reset ();
        ChangeState (intf, new OSPF::InterfaceStateDown, this);
    }
    if (event == OSPF::Interface::UnloopIndication) {
        ChangeState (intf, new OSPF::InterfaceStateDown, this);
    }
}

