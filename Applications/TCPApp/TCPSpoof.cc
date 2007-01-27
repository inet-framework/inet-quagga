//
// Copyright 2006 Andras Varga
//
// This library is free software, you can redistribute it and/or modify
// it under  the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation;
// either version 2 of the License, or any later version.
// The library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//


#include "TCPSpoof.h"
#include "IPControlInfo.h"
#include "IPv6ControlInfo.h"


Define_Module(TCPSpoof);

void TCPSpoof::initialize()
{
    simtime_t t = par("t").doubleValue();
    scheduleAt(t, new cMessage("timer"));
}

void TCPSpoof::handleMessage(cMessage *msg)
{
    if (!msg->isSelfMessage())
        error("Does not process incoming messages");

    sendSpoofPacket();
    delete msg;
}

void TCPSpoof::sendSpoofPacket()
{
    TCPSegment *tcpseg = new TCPSegment("spoof");

    IPvXAddress srcAddr = IPAddressResolver().resolve(par("srcAddress"));
    IPvXAddress destAddr = IPAddressResolver().resolve(par("destAddress"));
    int srcPort = par("srcPort");
    int destPort = par("destPort");
    bool isSYN = par("isSYN");
    unsigned long seq = par("seqNo").longValue()==-1 ? initialSeqNum() : par("seqNo").longValue();

    // one can customize the following according to concrete needs
    tcpseg->setSrcPort(srcPort);
    tcpseg->setDestPort(destPort);
    tcpseg->setByteLength(TCP_HEADER_OCTETS);
    tcpseg->setSequenceNo(seq);
    //tcpseg->setAckNo(...);
    tcpseg->setSynBit(isSYN);
    tcpseg->setWindow(16384);

    sendToIP(tcpseg, srcAddr, destAddr);
}

void TCPSpoof::sendToIP(TCPSegment *tcpseg, IPvXAddress src, IPvXAddress dest)
{
    EV << "Sending: ";
    //printSegmentBrief(tcpseg);

    if (!dest.isIPv6())
    {
        // send over IPv4
        IPControlInfo *controlInfo = new IPControlInfo();
        controlInfo->setProtocol(IP_PROT_TCP);
        controlInfo->setSrcAddr(src.get4());
        controlInfo->setDestAddr(dest.get4());
        tcpseg->setControlInfo(controlInfo);

        send(tcpseg,"ipv4Out");
    }
    else
    {
        // send over IPv6
        IPv6ControlInfo *controlInfo = new IPv6ControlInfo();
        controlInfo->setProtocol(IP_PROT_TCP);
        controlInfo->setSrcAddr(src.get6());
        controlInfo->setDestAddr(dest.get6());
        tcpseg->setControlInfo(controlInfo);

        send(tcpseg,"ipv6Out");
    }
}

unsigned long TCPSpoof::initialSeqNum()
{
    // choose an initial send sequence number in the same way as TCP does
    return (unsigned long)SIMTIME_DBL(fmod(simTime()*250000.0, 1.0+(double)(unsigned)0xffffffffUL)) & 0xffffffffUL;
}


