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


#ifndef __ICMPv6_H__
#define __ICMPv6_H__

#include <omnetpp.h>
#include "RoutingTable6Access.h"
#include "IPv6Datagram.h"
#include "ICMPv6Message_m.h"
#include "IPv6ControlInfo.h"


/**
 * ICMPv6 implementation.
 */
class INET_API ICMPv6 : public cSimpleModule
{
  public:
    /**
     *  This method can be called from other modules to send an ICMPv6 error packet.
     *  RFC 2463, Section 3: ICMPv6 Error Messages
     *  There are a total of 4 ICMPv6 error messages as described in the RFC.
     *  This method will construct and send error messages corresponding to the
     *  given type.
     *  Error Types:
     *      - Destination Unreachable Message - 1
     *      - Packet Too Big Message          - 2
     *      - Time Exceeded Message           - 3
     *      - Parameter Problem Message       - 4
     *  Code Types have different semantics for each error type. See RFC 2463.
     */
    void sendErrorMessage(IPv6Datagram *datagram, ICMPv6Type type, int code);

    /**
     * This method can be called from other modules to send an ICMP error packet
     * in response to a received bogus packet from the transport layer (like UDP).
     * The ICMP error packet needs to include (part of) the original IP datagram,
     * so this function will wrap back the transport packet into the IP datagram
     * based on its IPControlInfo.
     */
    void sendErrorMessage(cMessage *transportPacket, IPv6ControlInfo *ctrl, ICMPv6Type type, int code);

  protected:
    // internal helper functions
    void sendToIP(ICMPv6Message *msg, const IPv6Address& dest);
    void sendToIP(ICMPv6Message *msg); // FIXME check if really needed

    ICMPv6Message *createDestUnreachableMsg(int code);
    ICMPv6Message *createPacketTooBigMsg(int mtu);
    ICMPv6Message *createTimeExceededMsg(int code);
    ICMPv6Message *createParamProblemMsg(int code);//TODO:Section 3.4 describes a pointer. What is it?

  protected:
    /**
     * Initialization
     */
    virtual void initialize();

    /**
     *  Processing of messages that arrive in this module. Messages arrived here
     *  could be for ICMP ping requests or ICMPv6 messages that require processing.
     */
    virtual void handleMessage(cMessage *msg);
    virtual void processICMPv6Message(ICMPv6Message *);

    /**
     *  Respond to the machine that tried to ping us.
     */
    virtual void processEchoRequest(ICMPv6EchoRequestMsg *);

    /**
     *  Forward the ping reply to the "pingOut" of this module.
     */
    virtual void processEchoReply(ICMPv6EchoReplyMsg *);

    /**
     *  Ping a machine. The information needed to do this is in the cMessage
     *  parameter.  TODO where in cMessage? document!!!
     */
    virtual void sendEchoRequest(cMessage *);

    /**
     * Validate the received IPv6 datagram before responding with error message.
     */
    bool validateDatagramPromptingError(IPv6Datagram *datagram);

    virtual void errorOut(ICMPv6Message *);
};


#endif


