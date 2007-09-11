//
// Copyright (C) 2005 Andras Varga
// Copyright (C) 2005 Wei Yang, Ng
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//


#include <omnetpp.h>
#include "IPv6.h"
#include "InterfaceTableAccess.h"
#include "RoutingTable6Access.h"
#include "ICMPv6Access.h"
#include "IPv6NeighbourDiscoveryAccess.h"
#include "IPv6ControlInfo.h"
#include "IPv6NDMessage_m.h"
#include "Ieee802Ctrl_m.h"
#include "ICMPv6Message_m.h"


#define FRAGMENT_TIMEOUT 60   // 60 sec, from IPv6 RFC


Define_Module(IPv6);

void IPv6::initialize()
{
    QueueBase::initialize();

    ift = InterfaceTableAccess().get();
    rt = RoutingTable6Access().get();
    nd = IPv6NeighbourDiscoveryAccess().get();
    icmp = ICMPv6Access().get();

    mapping.parseProtocolMapping(par("protocolMapping"));

    curFragmentId = 0;
    lastCheckTime = 0;
    fragbuf.init(icmp);

    numMulticast = numLocalDeliver = numDropped = numUnroutable = numForwarded = 0;

    WATCH(numMulticast);
    WATCH(numLocalDeliver);
    WATCH(numDropped);
    WATCH(numUnroutable);
    WATCH(numForwarded);
}

void IPv6::updateDisplayString()
{
    char buf[80] = "";
    if (numForwarded>0) sprintf(buf+strlen(buf), "fwd:%d ", numForwarded);
    if (numLocalDeliver>0) sprintf(buf+strlen(buf), "up:%d ", numLocalDeliver);
    if (numMulticast>0) sprintf(buf+strlen(buf), "mcast:%d ", numMulticast);
    if (numDropped>0) sprintf(buf+strlen(buf), "DROP:%d ", numDropped);
    if (numUnroutable>0) sprintf(buf+strlen(buf), "UNROUTABLE:%d ", numUnroutable);
    displayString().setTagArg("t",0,buf);
}

void IPv6::endService(cMessage *msg)
{
    if (msg->arrivalGate()->isName("transportIn") ||
       (msg->arrivalGate()->isName("ndIn") && dynamic_cast<IPv6NDMessage*>(msg)) ||
       (msg->arrivalGate()->isName("icmpIn") && dynamic_cast<ICMPv6Message*>(msg)))//Added this for ICMP msgs from ICMP module-WEI
    {
        // packet from upper layers or ND: encapsulate and send out
        handleMessageFromHL(msg);
    }
    else
    {
        // datagram from network or from ND: localDeliver and/or route
        IPv6Datagram *dgram = check_and_cast<IPv6Datagram *>(msg);
        handleDatagramFromNetwork(dgram);
    }

    if (ev.isGUI())
        updateDisplayString();
}

InterfaceEntry *IPv6::sourceInterfaceFrom(cMessage *msg)
{
    cGate *g = msg->arrivalGate();
    return g ? ift->interfaceByNetworkLayerGateIndex(g->index()) : NULL;
}

void IPv6::handleDatagramFromNetwork(IPv6Datagram *datagram)
{
    // check for header biterror
    if (datagram->hasBitError())
    {
        EV << "bit error\n";return; // revise!
/*FIXME revise
        // probability of bit error in header = size of header / size of total message
        // (ignore bit error if in payload)
        double relativeHeaderLength = datagram->headerLength() / (double)datagram->byteLength();
        if (dblrand() <= relativeHeaderLength)
        {
            EV << "bit error found, sending ICMP_PARAMETER_PROBLEM\n";
            icmp->sendErrorMessage(datagram, ICMP_PARAMETER_PROBLEM, 0);
            return;
        }
*/
    }

    // remove control info
    delete datagram->removeControlInfo();

    // routepacket
    if (!datagram->destAddress().isMulticast())
        routePacket(datagram, NULL, false);
    else
        routeMulticastPacket(datagram, NULL, sourceInterfaceFrom(datagram));
}

void IPv6::handleMessageFromHL(cMessage *msg)
{
    // if no interface exists, do not send datagram
    if (ift->numInterfaces() == 0)
    {
        EV << "No interfaces exist, dropping packet\n";
        delete msg;
        return;
    }

    // encapsulate upper-layer packet into IPv6Datagram
    InterfaceEntry *destIE; // to be filled in by encapsulate()
    IPv6Datagram *datagram = encapsulate(msg, destIE);

    // possibly fragment (in IPv6, only the source node does that), then route it
    fragmentAndRoute(datagram, destIE);
}

void IPv6::fragmentAndRoute(IPv6Datagram *datagram, InterfaceEntry *destIE)
{
/*
FIXME implement fragmentation here.
   1. determine output interface
   2. compare packet size with interface MTU
   3. if bigger, do fragmentation
         int mtu = ift->interfaceByPortNo(outputGateIndex)->mtu();
*/
    EV << "fragmentation not implemented yet\n";

    // route packet
    if (destIE!=NULL)
        sendDatagramToOutput(datagram, destIE, MACAddress::BROADCAST_ADDRESS); // FIXME what MAC address to use?
    else if (!datagram->destAddress().isMulticast())
        routePacket(datagram, destIE, true);
    else
        routeMulticastPacket(datagram, destIE, NULL);
}

void IPv6::routePacket(IPv6Datagram *datagram, InterfaceEntry *destIE, bool fromHL)
{
    // TBD add option handling code here
    IPv6Address destAddress = datagram->destAddress();

    EV << "Routing datagram `" << datagram->name() << "' with dest=" << destAddress << ": ";

    // local delivery of unicast packets
    if (rt->localDeliver(destAddress))
    {
        EV << "local delivery\n";
        if (datagram->srcAddress().isUnspecified())
            datagram->setSrcAddress(destAddress); // allows two apps on the same host to communicate
        numLocalDeliver++;
        localDeliver(datagram);
        return;
    }

    if (!fromHL)
    {
        // if datagram arrived from input gate and IP forwarding is off, delete datagram
        //yes but datagrams from the ND module is getting dropped too!-WEI
        //so we add a 2nd condition
        // FIXME rewrite code so that condition is cleaner --Andras
        //if (!rt->isRouter())
        if (!rt->isRouter() && !(datagram->arrivalGate()->isName("ndIn")))
        {
            EV << "forwarding is off, dropping packet\n";
            numDropped++;
            delete datagram;
            return;
        }

        // don't forward link-local addresses or weaker
        if (destAddress.isLinkLocal() || destAddress.isLoopback())
        {
            EV << "dest address is link-local (or weaker) scope, doesn't get forwarded\n";
            delete datagram;
            return;
        }

        // hop counter decrement: only if datagram arrived from network, and will be
        // sent out to the network (hoplimit check will be done just before sending
        // out datagram)
        // TBD: in IPv4, arrange TTL check like this
        datagram->setHopLimit(datagram->hopLimit()-1);
    }

    // routing
    // first try destination cache
    int interfaceId;
    IPv6Address nextHop = rt->lookupDestCache(destAddress, interfaceId);
    if (interfaceId==-1)
    {
        // address not in destination cache: do longest prefix match in routing table
        const IPv6Route *route = rt->doLongestPrefixMatch(destAddress);
        if (!route)
        {
            if (rt->isRouter())
            {
                EV << "unroutable, sending ICMPv6_DESTINATION_UNREACHABLE\n";
                numUnroutable++;
                icmp->sendErrorMessage(datagram, ICMPv6_DESTINATION_UNREACHABLE, 0); // FIXME check ICMP 'code'
            }
            else // host
            {
                EV << "no match in routing table, passing datagram to Neighbour Discovery module for default router selection\n";
                send(datagram, "ndOut");
            }
            return;
        }
        interfaceId = route->interfaceID();
        nextHop = route->nextHop();
        if (nextHop.isUnspecified())
            nextHop = destAddress;  // next hop is the host itself

        // add result into destination cache
        rt->updateDestCache(destAddress, nextHop, interfaceId);
    }

    InterfaceEntry *ie = ift->interfaceAt(interfaceId);
    EV << "next hop for " << destAddress << " is " << nextHop << ", interface " << ie->name() << "\n";
    ASSERT(!nextHop.isUnspecified() && ie!=NULL);

    MACAddress macAddr = nd->resolveNeighbour(nextHop, interfaceId);
    if (macAddr.isUnspecified())
    {
        EV << "no link-layer address for next hop yet, passing datagram to Neighbour Discovery module\n";
        send(datagram, "ndOut");
        return;
    }
    EV << "link-layer address: " << macAddr << "\n";

    // set datagram source address if not yet set
    if (datagram->srcAddress().isUnspecified())
    {
        const IPv6Address& srcAddr = ie->ipv6()->preferredAddress();
        ASSERT(!srcAddr.isUnspecified()); // FIXME what if we don't have an address yet?
        datagram->setSrcAddress(srcAddr);
    }

    // send out datagram
    numForwarded++;
    sendDatagramToOutput(datagram, ie, macAddr);
}

void IPv6::routeMulticastPacket(IPv6Datagram *datagram, InterfaceEntry *destIE, InterfaceEntry *fromIE)
{
    const IPv6Address& destAddr = datagram->destAddress();

    EV << "destination address " << destAddr << " is multicast, doing multicast routing\n";
    numMulticast++;

    // if received from the network...
    if (fromIE!=NULL)
    {
        // deliver locally
        if (rt->localDeliver(destAddr))
        {
            EV << "local delivery of multicast packet\n";
            numLocalDeliver++;
            localDeliver((IPv6Datagram *)datagram->dup());
        }

        // if datagram arrived from input gate and IP forwarding is off, delete datagram
        if (!rt->isRouter())
        {
            EV << "forwarding is off\n";
            delete datagram;
            return;
        }

        // make sure scope of multicast address is large enough to be forwarded to other links
        if (destAddr.multicastScope()<=2)
        {
            EV << "multicast dest address is link-local (or smaller) scope\n";
            delete datagram;
            return;
        }

        // hop counter decrement: only if datagram arrived from network, and will be
        // sent out to the network (hoplimit check will be done just before sending
        // out datagram)
        // TBD: in IPv4, arrange TTL check like this
        datagram->setHopLimit(datagram->hopLimit()-1);
    }

    // for now, we just send it out on every interface except on which it came. FIXME better!!!
    EV << "sending out datagram on every interface (except incoming one)\n";
    for (int i=0; i<ift->numInterfaces(); i++)
    {
        InterfaceEntry *ie = ift->interfaceAt(i);
        if (fromIE!=ie)
            sendDatagramToOutput((IPv6Datagram *)datagram->dup(), ie, MACAddress::BROADCAST_ADDRESS);
    }
    delete datagram;

/* FIXME implement handling of multicast

    According to Gopi: "multicast routing table" should map
       srcAddr+multicastDestAddr to a set of next hops (interface+nexthopAddr)
    Where srcAddr is the multicast server, and destAddr sort of narrows it down to a given stream

    // FIXME multicast-->tunneling link (present in original IPSuite) missing from here

    // DVMRP: process datagram only if sent locally or arrived on the shortest
    // route (provided routing table already contains srcAddr); otherwise
    // discard and continue.
    int inputGateIndex = datagram->arrivalGate() ? datagram->arrivalGate()->index() : -1;
    int shortestPathInputGateIndex = rt->outputGateIndexNo(datagram->srcAddress());
    if (inputGateIndex!=-1 && shortestPathInputGateIndex!=-1 && inputGateIndex!=shortestPathInputGateIndex)
    {
        // FIXME count dropped
        EV << "Packet dropped.\n";
        delete datagram;
        return;
    }

    // check for local delivery
    IPv6Address destAddress = datagram->destAddress();
    if (rt->multicastLocalDeliver(destAddress))
    {
        IPv6Datagram *datagramCopy = (IPv6Datagram *) datagram->dup();

        // FIXME code from the MPLS model: set packet dest address to routerId (???)
        datagramCopy->setDestAddress(rt->routerId());

        localDeliver(datagramCopy);
    }

    // forward datagram only if IP forward is enabled, or sent locally
    if (inputGateIndex!=-1 && !rt->isRouter())
    {
        delete datagram;
        return;
    }

    MulticastRoutes routes = rt->multicastRoutesFor(destAddress);
    if (routes.size()==0)
    {
        // no destination: delete datagram
        delete datagram;
    }
    else
    {
        // copy original datagram for multiple destinations
        for (unsigned int i=0; i<routes.size(); i++)
        {
            int outputGateIndex = routes[i].interf->outputGateIndex();

            // don't forward to input port
            if (outputGateIndex>=0 && outputGateIndex!=inputGateIndex)
            {
                IPv6Datagram *datagramCopy = (IPv6Datagram *) datagram->dup();

                // set datagram source address if not yet set
                if (datagramCopy->srcAddress().isUnspecified())
                    datagramCopy->setSrcAddress(ift->interfaceByPortNo(outputGateIndex)->ipv6()->inetAddress());

                // send
                IPv6Address nextHopAddr = routes[i].gateway;
                sendDatagramToOutput(datagramCopy, outputGateIndex, macAddr);
            }
        }

        // only copies sent, delete original datagram
        delete datagram;
    }
*/
}

void IPv6::localDeliver(IPv6Datagram *datagram)
{
/* FIXME revise and complete defragmentation
    // Defragmentation. skip defragmentation if datagram is not fragmented
    if (datagram->fragmentOffset()!=0 || datagram->moreFragments())
    {
        EV << "Datagram fragment: offset=" << datagram->fragmentOffset()
           << ", MORE=" << (datagram->moreFragments() ? "true" : "false") << ".\n";

        // erase timed out fragments in fragmentation buffer; check every 10 seconds max
        if (simTime() >= lastCheckTime + 10)
        {
            lastCheckTime = simTime();
            fragbuf.purgeStaleFragments(simTime()-FRAGMENT_TIMEOUT);
        }

        datagram = fragbuf.addFragment(datagram, simTime());
        if (!datagram)
        {
            EV << "No complete datagram yet.\n";
            return;
        }
        EV << "This fragment completes the datagram.\n";
    }
*/
    // decapsulate and send on appropriate output gate
    int protocol = datagram->transportProtocol();
    cMessage *packet = decapsulate(datagram);

    if (protocol==IP_PROT_IPv6_ICMP && dynamic_cast<IPv6NDMessage*>(packet))
    {
        EV << "Neigbour Discovery packet: passing it to ND module\n";
        send(packet, "ndOut");
    }
    else if (protocol==IP_PROT_IPv6_ICMP && dynamic_cast<ICMPv6Message*>(packet))
    {
        EV << "ICMPv6 packet: passing it to ICMPv6 module\n";
        send(packet, "icmpOut");
    }//Added by WEI to forward ICMPv6 msgs to ICMPv6 module.
    else if (protocol==IP_PROT_IP || protocol==IP_PROT_IPv6)
    {
        EV << "Tunnelled IP datagram\n";
        // FIXME handle tunnelling
        error("tunnelling not yet implemented");
    }
    else
    {
        int gateindex = mapping.outputGateForProtocol(protocol);
        EV << "Protocol " << protocol << ", passing up on gate " << gateindex << "\n";
        //TODO: Indication of forward progress
        send(packet, "transportOut", gateindex);
    }
}

void IPv6::handleReceivedICMP(ICMPv6Message *msg)
{
    switch (msg->type())
    {
        case ICMPv6_REDIRECT:  // TODO implement redirect handling
        case ICMPv6_DESTINATION_UNREACHABLE:
        case ICMPv6_PACKET_TOO_BIG:
        case ICMPv6_TIME_EXCEEDED:
        case ICMPv6_PARAMETER_PROBLEM: {
            // ICMP errors are delivered to the appropriate higher layer protocols
            IPv6Datagram *bogusPacket = check_and_cast<IPv6Datagram *>(msg->encapsulatedMsg());
            int protocol = bogusPacket->transportProtocol();
            int gateindex = mapping.outputGateForProtocol(protocol);
            send(msg, "transportOut", gateindex);
            break;
        }
        default: {
            // all others are delivered to ICMP:
            // ICMPv6_ECHO_REQUEST, ICMPv6_ECHO_REPLY, ICMPv6_MLD_QUERY, ICMPv6_MLD_REPORT,
            // ICMPv6_MLD_DONE, ICMPv6_ROUTER_SOL, ICMPv6_ROUTER_AD, ICMPv6_NEIGHBOUR_SOL,
            // ICMPv6_NEIGHBOUR_AD, ICMPv6_MLDv2_REPORT
            int gateindex = mapping.outputGateForProtocol(IP_PROT_ICMP);
            send(msg, "transportOut", gateindex);
        }
     }
}


cMessage *IPv6::decapsulate(IPv6Datagram *datagram)
{
    // decapsulate transport packet
    InterfaceEntry *fromIE = sourceInterfaceFrom(datagram);
    cMessage *packet = datagram->decapsulate();

    // create and fill in control info
    IPv6ControlInfo *controlInfo = new IPv6ControlInfo();
    controlInfo->setProtocol(datagram->transportProtocol());
    controlInfo->setSrcAddr(datagram->srcAddress());
    controlInfo->setDestAddr(datagram->destAddress());
    controlInfo->setHopLimit(datagram->hopLimit());
    controlInfo->setInterfaceId(fromIE ? fromIE->interfaceId() : -1);

    // original IP datagram might be needed in upper layers to send back ICMP error message
    controlInfo->setOrigDatagram(datagram);

    // attach control info
    packet->setControlInfo(controlInfo);

    return packet;
}

IPv6Datagram *IPv6::encapsulate(cMessage *transportPacket, InterfaceEntry *&destIE)
{
    IPv6ControlInfo *controlInfo = check_and_cast<IPv6ControlInfo*>(transportPacket->removeControlInfo());

    IPv6Datagram *datagram = new IPv6Datagram(transportPacket->name());
    datagram->setByteLength(datagram->calculateHeaderByteLength());
    datagram->encapsulate(transportPacket);

    // IPV6_MULTICAST_IF option, but allow interface selection for unicast packets as well
    destIE = ift->interfaceAt(controlInfo->interfaceId());

    // set source and destination address
    IPv6Address dest = controlInfo->destAddr();
    datagram->setDestAddress(dest);

    IPv6Address src = controlInfo->srcAddr();

    // when source address was given, use it; otherwise it'll get the address
    // of the outgoing interface after routing
    if (!src.isUnspecified())
    {
        // if interface parameter does not match existing interface, do not send datagram
        if (rt->interfaceByAddress(src)==NULL)
            opp_error("Wrong source address %s in (%s)%s: no interface with such address",
                      src.str().c_str(), transportPacket->className(), transportPacket->fullName());
        datagram->setSrcAddress(src);
    }

    // set other fields
    datagram->setHopLimit(controlInfo->hopLimit()>0 ? controlInfo->hopLimit() : 32); //FIXME use iface hop limit instead of 32?
    datagram->setTransportProtocol(controlInfo->protocol());
    delete controlInfo;

    // setting IP options is currently not supported

    return datagram;
}

void IPv6::sendDatagramToOutput(IPv6Datagram *datagram, InterfaceEntry *ie, const MACAddress& macAddr)
{
    // hop counter check
    if (datagram->hopLimit() <= 0)
    {
        // drop datagram, destruction responsibility in ICMP
        EV << "datagram hopLimit reached zero, sending ICMPv6_TIME_EXCEEDED\n";
        icmp->sendErrorMessage(datagram, ICMPv6_TIME_EXCEEDED, 0); // FIXME check icmp 'code'
        return;
    }

    // in link layer uses MAC addresses (basically, not PPP), add control info
    if (!macAddr.isUnspecified())
    {
        Ieee802Ctrl *controlInfo = new Ieee802Ctrl();
        controlInfo->setDest(macAddr);
        datagram->setControlInfo(controlInfo);
    }

    // send datagram to link layer
    send(datagram, "queueOut", ie->networkLayerGateIndex());
}


