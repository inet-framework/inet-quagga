//
// Copyright (C) 2000 Institut fuer Telematik, Universitaet Karlsruhe
// Copyright (C) 2004,2005 Andras Varga
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


//
// Author: Jochen Reber
// Rewrite: Andras Varga 2004,2005
//

#include <omnetpp.h>
#include <string.h>
#include "UDPPacket.h"
#include "UDP.h"
#include "IPControlInfo.h"
#include "IPv6ControlInfo.h"
#include "ICMPAccess.h"
#include "ICMPv6Access.h"

// the following is only for ICMP error processing
#include "ICMPMessage_m.h"
#include "ICMPv6Message_m.h"
#include "IPDatagram_m.h"
#include "IPv6Datagram_m.h"


#define EPHEMERAL_PORTRANGE_START 1024
#define EPHEMERAL_PORTRANGE_END   5000


Define_Module( UDP );


static std::ostream & operator<<(std::ostream & os, const UDP::SockDesc& sd)
{
    os << "sockId=" << sd.sockId;
    os << " appGateIndex=" << sd.appGateIndex;
    os << " userId=" << sd.userId;
    os << " localPort=" << sd.localPort;
    if (sd.remotePort!=0)
        os << " remotePort=" << sd.remotePort;
    if (!sd.localAddr.isUnspecified())
        os << " localAddr=" << sd.localAddr;
    if (!sd.remoteAddr.isUnspecified())
        os << " remoteAddr=" << sd.remoteAddr;
    if (sd.interfaceId!=-1)
        os << " interfaceId=" << sd.interfaceId;

    return os;
}

static std::ostream & operator<<(std::ostream & os, const UDP::SockDescList& list)
{
    for (UDP::SockDescList::const_iterator i=list.begin(); i!=list.end(); ++i)
        os << "sockId=" << (*i)->sockId << " ";
    return os;
}

//--------

UDP::~UDP()
{
    for (SocketsByIdMap::iterator i=socketsByIdMap.begin(); i!=socketsByIdMap.end(); ++i)
        delete i->second;
}

void UDP::initialize()
{
    WATCH_PTRMAP(socketsByIdMap);
    WATCH_MAP(socketsByPortMap);

    lastEphemeralPort = EPHEMERAL_PORTRANGE_START;
    icmp = NULL;
    icmpv6 = NULL;

    numSent = 0;
    numPassedUp = 0;
    numDroppedWrongPort = 0;
    numDroppedBadChecksum = 0;
    WATCH(numSent);
    WATCH(numPassedUp);
    WATCH(numDroppedWrongPort);
    WATCH(numDroppedBadChecksum);
}

void UDP::bind(int gateIndex, UDPControlInfo *ctrl)
{
    // XXX checks could be added, of when the bind should be allowed to proceed

    // create and fill in SockDesc
    SockDesc *sd = new SockDesc();
    sd->sockId = ctrl->sockId();
    sd->userId = ctrl->userId();
    sd->appGateIndex = gateIndex;
    sd->localAddr = ctrl->srcAddr();
    sd->remoteAddr = ctrl->destAddr();
    sd->localPort = ctrl->srcPort();
    sd->remotePort = ctrl->destPort();
    sd->interfaceId = ctrl->interfaceId();

    if (sd->sockId==-1)
        error("sockId in BIND message not filled in");
    if (sd->localPort==0)
        sd->localPort = getEphemeralPort();

    sd->onlyLocalPortIsSet = sd->localAddr.isUnspecified() &&
                             sd->remoteAddr.isUnspecified() &&
                             sd->remotePort==0 &&
                             sd->interfaceId==-1;

    EV << "Binding socket: " << *sd << "\n";

    // add to socketsByIdMap
    ASSERT(socketsByIdMap.find(sd->sockId)==socketsByIdMap.end());
    socketsByIdMap[sd->sockId] = sd;

    // add to socketsByPortMap
    SockDescList& list = socketsByPortMap[sd->localPort]; // create if doesn't exist
    list.push_back(sd);
}

void UDP::connect(int sockId, IPvXAddress addr, int port)
{
    SocketsByIdMap::iterator it = socketsByIdMap.find(sockId);
    if (it==socketsByIdMap.end())
        error("socket id=%d doesn't exist (already closed?)", sockId);
    if (addr.isUnspecified())
        opp_error("connect: unspecified remote address");
    if (port<=0 || port>65535)
        opp_error("connect: invalid remote port number %d", port);

    SockDesc *sd = it->second;
    sd->remoteAddr = addr;
    sd->remotePort = port;

    sd->onlyLocalPortIsSet = false;

    EV << "Connecting socket: " << *sd << "\n";
}

void UDP::unbind(int sockId)
{
    // remove from socketsByIdMap
    SocketsByIdMap::iterator it = socketsByIdMap.find(sockId);
    if (it==socketsByIdMap.end())
        error("socket id=%d doesn't exist (already closed?)", sockId);
    SockDesc *sd = it->second;
    socketsByIdMap.erase(it);

    EV << "Unbinding socket: " << *sd << "\n";

    // remove from socketsByPortMap
    SockDescList& list = socketsByPortMap[sd->localPort];
    for (SockDescList::iterator it=list.begin(); it!=list.end(); ++it)
        if (*it == sd)
            {list.erase(it); break;}
    if (list.empty())
        socketsByPortMap.erase(sd->localPort);
    delete sd;
}

short UDP::getEphemeralPort()
{
    // start at the last allocated port number + 1, and search for an unused one
    short searchUntil = lastEphemeralPort++;
    if (lastEphemeralPort == EPHEMERAL_PORTRANGE_END) // wrap
        lastEphemeralPort = EPHEMERAL_PORTRANGE_START;

    while (socketsByPortMap.find(lastEphemeralPort)!=socketsByPortMap.end())
    {
        if (lastEphemeralPort == searchUntil) // got back to starting point?
            error("Ephemeral port range %d..%d exhausted, all ports occupied", EPHEMERAL_PORTRANGE_START, EPHEMERAL_PORTRANGE_END);
        lastEphemeralPort++;
        if (lastEphemeralPort == EPHEMERAL_PORTRANGE_END) // wrap
            lastEphemeralPort = EPHEMERAL_PORTRANGE_START;
    }

    // found a free one, return it
    return lastEphemeralPort;
}

void UDP::handleMessage(cMessage *msg)
{
    // received from IP layer
    if (msg->arrivedOn("from_ip") || msg->arrivedOn("from_ipv6"))
    {
        if (dynamic_cast<ICMPMessage *>(msg) || dynamic_cast<ICMPv6Message *>(msg))
            processICMPError(msg);
        else
            processUDPPacket(check_and_cast<UDPPacket *>(msg));
    }
    else // received from application layer
    {
        if (msg->kind()==UDP_C_DATA)
            processMsgFromApp(msg);
        else
            processCommandFromApp(msg);
    }

    if (ev.isGUI())
        updateDisplayString();
}

void UDP::updateDisplayString()
{
    char buf[80];
    sprintf(buf, "passed up: %d pks\nsent: %d pks", numPassedUp, numSent);
    if (numDroppedWrongPort>0)
    {
        sprintf(buf+strlen(buf), "\ndropped (no app): %d pks", numDroppedWrongPort);
        displayString().setTagArg("i",1,"red");
    }
    displayString().setTagArg("t",0,buf);
}

bool UDP::matchesSocket(SockDesc *sd, UDPPacket *udp, IPControlInfo *ipCtrl)
{
    // IPv4 version
    if (sd->remotePort!=0 && sd->remotePort!=udp->sourcePort())
        return false;
    if (!sd->localAddr.isUnspecified() && sd->localAddr.get4()!=ipCtrl->destAddr())
        return false;
    if (!sd->remoteAddr.isUnspecified() && sd->remoteAddr.get4()!=ipCtrl->srcAddr())
        return false;
    if (sd->interfaceId!=-1 && sd->interfaceId!=ipCtrl->interfaceId())
        return false;
    return true;
}

bool UDP::matchesSocket(SockDesc *sd, UDPPacket *udp, IPv6ControlInfo *ipCtrl)
{
    // IPv6 version
    if (sd->remotePort!=0 && sd->remotePort!=udp->sourcePort())
        return false;
    if (!sd->localAddr.isUnspecified() && sd->localAddr.get6()!=ipCtrl->destAddr())
        return false;
    if (!sd->remoteAddr.isUnspecified() && sd->remoteAddr.get6()!=ipCtrl->srcAddr())
        return false;
    if (sd->interfaceId!=-1 && sd->interfaceId!=ipCtrl->interfaceId())
        return false;
    return true;
}

bool UDP::matchesSocket(SockDesc *sd, const IPvXAddress& localAddr, const IPvXAddress& remoteAddr, short remotePort)
{
    return (sd->remotePort==0 || sd->remotePort!=remotePort) &&
           (sd->localAddr.isUnspecified() || sd->localAddr==localAddr) &&
           (sd->remoteAddr.isUnspecified() || sd->remoteAddr==remoteAddr);
}

void UDP::sendUp(cMessage *payload, UDPPacket *udpHeader, IPControlInfo *ipCtrl, SockDesc *sd)
{
    // send payload with UDPControlInfo up to the application -- IPv4 version
    UDPControlInfo *udpCtrl = new UDPControlInfo();
    udpCtrl->setSockId(sd->sockId);
    udpCtrl->setUserId(sd->userId);
    udpCtrl->setSrcAddr(ipCtrl->srcAddr());
    udpCtrl->setDestAddr(ipCtrl->destAddr());
    udpCtrl->setSrcPort(udpHeader->sourcePort());
    udpCtrl->setDestPort(udpHeader->destinationPort());
    udpCtrl->setInterfaceId(ipCtrl->interfaceId());
    payload->setControlInfo(udpCtrl);

    send(payload, "to_app", sd->appGateIndex);
    numPassedUp++;
}

void UDP::sendUp(cMessage *payload, UDPPacket *udpHeader, IPv6ControlInfo *ipCtrl, SockDesc *sd)
{
    // send payload with UDPControlInfo up to the application -- IPv6 version
    UDPControlInfo *udpCtrl = new UDPControlInfo();
    udpCtrl->setSockId(sd->sockId);
    udpCtrl->setUserId(sd->userId);
    udpCtrl->setSrcAddr(ipCtrl->srcAddr());
    udpCtrl->setDestAddr(ipCtrl->destAddr());
    udpCtrl->setSrcPort(udpHeader->sourcePort());
    udpCtrl->setDestPort(udpHeader->destinationPort());
    udpCtrl->setInterfaceId(ipCtrl->interfaceId());
    payload->setControlInfo(udpCtrl);

    send(payload, "to_app", sd->appGateIndex);
    numPassedUp++;
}

void UDP::processUndeliverablePacket(UDPPacket *udpPacket, cPolymorphic *ctrl)
{
    numDroppedWrongPort++;

    // send back ICMP PORT_UNREACHABLE
    if (dynamic_cast<IPControlInfo *>(ctrl)!=NULL)
    {
        if (!icmp)
            icmp = ICMPAccess().get();
        IPControlInfo *ctrl4 = (IPControlInfo *)ctrl;
        if (!ctrl4->destAddr().isMulticast())
            icmp->sendErrorMessage(udpPacket, ctrl4, ICMP_DESTINATION_UNREACHABLE, ICMP_DU_PORT_UNREACHABLE);
    }
    else if (dynamic_cast<IPv6ControlInfo *>(udpPacket->controlInfo())!=NULL)
    {
        if (!icmpv6)
            icmpv6 = ICMPv6Access().get();
        IPv6ControlInfo *ctrl6 = (IPv6ControlInfo *)ctrl;
        if (!ctrl6->destAddr().isMulticast())
            icmpv6->sendErrorMessage(udpPacket, ctrl6, ICMPv6_DESTINATION_UNREACHABLE, PORT_UNREACHABLE);
    }
    else
    {
        error("(%s)%s arrived from lower layer without control info", udpPacket->className(), udpPacket->name());
    }
}

void UDP::processICMPError(cMessage *msg)
{
    // extract details from the error message, then try to notify socket that sent bogus packet
    int type, code;
    IPvXAddress localAddr, remoteAddr;
    int localPort, remotePort;

    if (dynamic_cast<ICMPMessage *>(msg))
    {
        ICMPMessage *icmpMsg = (ICMPMessage *)msg;
        type = icmpMsg->getType();
        code = icmpMsg->getCode();
        icmpMsg->setLength(icmpMsg->encapsulatedMsg()->length()); // trick because payload in ICMP is conceptually truncated
        IPDatagram *datagram = check_and_cast<IPDatagram *>(icmpMsg->decapsulate());
        localAddr = datagram->srcAddress();
        remoteAddr = datagram->destAddress();
        UDPPacket *packet = check_and_cast<UDPPacket *>(datagram->decapsulate());
        localPort = packet->sourcePort();
        remotePort = packet->destinationPort();
        delete icmpMsg;
        delete datagram;
        delete packet;
    }
    else if (dynamic_cast<ICMPv6Message *>(msg))
    {
        ICMPv6Message *icmpMsg = (ICMPv6Message *)msg;
        type = icmpMsg->type();
        code = -1; // FIXME this is dependent on type()...
        IPv6Datagram *datagram = check_and_cast<IPv6Datagram *>(icmpMsg->decapsulate());
        localAddr = datagram->srcAddress();
        remoteAddr = datagram->destAddress();
        UDPPacket *packet = check_and_cast<UDPPacket *>(datagram->decapsulate());
        localPort = packet->sourcePort();
        remotePort = packet->destinationPort();
        delete icmpMsg;
        delete datagram;
        delete packet;
    }
    EV << "ICMP error received: type=" << type << " code=" << code
       << " about packet " << localAddr << ":" << localPort << " > "
       << remoteAddr << ":" << remotePort << "\n";

    // identify socket and report error to it
    SocketsByPortMap::iterator it = socketsByPortMap.find(localPort);
    if (it==socketsByPortMap.end())
    {
        EV << "No socket on that local port, ignoring ICMP error\n";
        return;
    }
    SockDescList& list = it->second;
    SockDesc *srcSocket = NULL;
    for (SockDescList::iterator it=list.begin(); it!=list.end(); ++it)
    {
        SockDesc *sd = *it;
        if (sd->onlyLocalPortIsSet || matchesSocket(sd, localAddr, remoteAddr, remotePort))
        {
            srcSocket = sd; // FIXME what to do if there's more than one matching socket ???
        }
    }
    if (!srcSocket)
    {
        EV << "No matching socket, ignoring ICMP error\n";
        return;
    }

    // send UDP_I_ERROR to socket
    EV << "Source socket is sockId=" << srcSocket->sockId << ", notifying.\n";
    sendUpErrorNotification(srcSocket, UDP_I_ERROR, localAddr, remoteAddr, remotePort);
}

void UDP::sendUpErrorNotification(SockDesc *sd, int msgkind, const IPvXAddress& localAddr, const IPvXAddress& remoteAddr, short remotePort)
{
    cMessage *notifyMsg = new cMessage("ERROR", msgkind);
    UDPControlInfo *udpCtrl = new UDPControlInfo();
    udpCtrl->setSockId(sd->sockId);
    udpCtrl->setUserId(sd->userId);
    udpCtrl->setSrcAddr(localAddr);
    udpCtrl->setDestAddr(remoteAddr);
    udpCtrl->setSrcPort(sd->localPort);
    udpCtrl->setDestPort(remotePort);
    notifyMsg->setControlInfo(udpCtrl);

    send(notifyMsg, "to_app", sd->appGateIndex);
}

void UDP::processUDPPacket(UDPPacket *udpPacket)
{
    // simulate checksum: discard packet if it has bit error
    EV << "Packet " << udpPacket->name() << " received from network, dest port " << udpPacket->destinationPort() << "\n";
    if (udpPacket->hasBitError())
    {
        EV << "Packet has bit error, discarding\n";
        delete udpPacket;
        numDroppedBadChecksum++;
        return;
    }

    int destPort = udpPacket->destinationPort();
    cPolymorphic *ctrl = udpPacket->removeControlInfo();

    // send back ICMP error if no socket is bound to that port
    SocketsByPortMap::iterator it = socketsByPortMap.find(destPort);
    if (it==socketsByPortMap.end())
    {
        EV << "No socket registered on port " << destPort << "\n";
        processUndeliverablePacket(udpPacket, ctrl);
        return;
    }
    SockDescList& list = it->second;

    int matches = 0;

    // deliver a copy of the packet to each matching socket
    cMessage *payload = udpPacket->encapsulatedMsg();
    if (dynamic_cast<IPControlInfo *>(ctrl)!=NULL)
    {
        IPControlInfo *ctrl4 = (IPControlInfo *)ctrl;
        for (SockDescList::iterator it=list.begin(); it!=list.end(); ++it)
        {
            SockDesc *sd = *it;
            if (sd->onlyLocalPortIsSet || matchesSocket(sd, udpPacket, ctrl4))
            {
                EV << "Socket sockId=" << sd->sockId << " matches, sending up a copy.\n";
                sendUp((cMessage*)payload->dup(), udpPacket, ctrl4, sd);
                matches++;
            }
        }
    }
    else if (dynamic_cast<IPv6ControlInfo *>(udpPacket->controlInfo())!=NULL)
    {
        IPv6ControlInfo *ctrl6 = (IPv6ControlInfo *)ctrl;
        for (SockDescList::iterator it=list.begin(); it!=list.end(); ++it)
        {
            SockDesc *sd = *it;
            if (sd->onlyLocalPortIsSet || matchesSocket(sd, udpPacket, ctrl6))
            {
                EV << "Socket sockId=" << sd->sockId << " matches, sending up a copy.\n";
                sendUp((cMessage*)payload->dup(), udpPacket, ctrl6, sd);
                matches++;
            }
        }
    }
    else
    {
        error("(%s)%s arrived from lower layer without control info", udpPacket->className(), udpPacket->name());
    }

    // send back ICMP error if there is no matching socket
    if (matches==0)
    {
        EV << "None of the sockets on port " << destPort << " matches the packet\n";
        processUndeliverablePacket(udpPacket, ctrl);
        return;
    }

    delete udpPacket;
    delete ctrl;
}


void UDP::processMsgFromApp(cMessage *appData)
{
    UDPControlInfo *udpCtrl = check_and_cast<UDPControlInfo *>(appData->removeControlInfo());

    UDPPacket *udpPacket = new UDPPacket(appData->name());
    udpPacket->setByteLength(UDP_HEADER_BYTES);
    udpPacket->encapsulate(appData);

    // set source and destination port
    udpPacket->setSourcePort(udpCtrl->srcPort());
    udpPacket->setDestinationPort(udpCtrl->destPort());

    if (!udpCtrl->destAddr().isIPv6())
    {
        // send to IPv4
        EV << "Sending app packet " << appData->name() << " over IPv4.\n";
        IPControlInfo *ipControlInfo = new IPControlInfo();
        ipControlInfo->setProtocol(IP_PROT_UDP);
        ipControlInfo->setSrcAddr(udpCtrl->srcAddr().get4());
        ipControlInfo->setDestAddr(udpCtrl->destAddr().get4());
        ipControlInfo->setInterfaceId(udpCtrl->interfaceId());
        udpPacket->setControlInfo(ipControlInfo);
        delete udpCtrl;

        send(udpPacket,"to_ip");
    }
    else
    {
        // send to IPv6
        EV << "Sending app packet " << appData->name() << " over IPv6.\n";
        IPv6ControlInfo *ipControlInfo = new IPv6ControlInfo();
        ipControlInfo->setProtocol(IP_PROT_UDP);
        ipControlInfo->setSrcAddr(udpCtrl->srcAddr().get6());
        ipControlInfo->setDestAddr(udpCtrl->destAddr().get6());
        // ipControlInfo->setInterfaceId(udpCtrl->InterfaceId()); FIXME extend IPv6 with this!!!
        udpPacket->setControlInfo(ipControlInfo);
        delete udpCtrl;

        send(udpPacket,"to_ipv6");
    }
    numSent++;
}

void UDP::processCommandFromApp(cMessage *msg)
{
    UDPControlInfo *udpCtrl = check_and_cast<UDPControlInfo *>(msg->removeControlInfo());
    switch (msg->kind())
    {
        case UDP_C_BIND:
            bind(msg->arrivalGate()->index(), udpCtrl);
            break;
        case UDP_C_CONNECT:
            connect(udpCtrl->sockId(), udpCtrl->destAddr(), udpCtrl->destPort());
            break;
        case UDP_C_UNBIND:
            unbind(udpCtrl->sockId());
            break;
        default:
            error("unknown command code (message kind) %d received from app", msg->kind());
    }

    delete udpCtrl;
    delete msg;
}


