#ifndef __LINKSTATEACKNOWLEDGEMENTHANDLER_HPP__
#define __LINKSTATEACKNOWLEDGEMENTHANDLER_HPP__

#include "IMessageHandler.hpp"

namespace OSPF {

class LinkStateAcknowledgementHandler : public IMessageHandler {
public:
    LinkStateAcknowledgementHandler (Router* containingRouter);

    void    ProcessPacket (OSPFPacket* packet, Interface* intf, Neighbor* neighbor);
};

} // namespace OSPF

#endif // __LINKSTATEACKNOWLEDGEMENTHANDLER_HPP__

