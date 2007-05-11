/**
 * Copyright (C) 2005 Andras Varga
 * Copyright (C) 2005 Wei Yang, Ng
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "IPv6NeighbourDiscovery.h"


#define MK_ASSIGN_LINKLOCAL_ADDRESS 0
#define MK_SEND_PERIODIC_RTRADV 1
#define MK_SEND_SOL_RTRADV 2
#define MK_INITIATE_RTRDIS 3
#define MK_DAD_TIMEOUT 4
#define MK_RD_TIMEOUT 5
#define MK_NUD_TIMEOUT 6
#define MK_AR_TIMEOUT 7

Define_Module(IPv6NeighbourDiscovery);


IPv6NeighbourDiscovery::IPv6NeighbourDiscovery()
{
}

IPv6NeighbourDiscovery::~IPv6NeighbourDiscovery()
{
    // FIXME delete the following data structures, cancelAndDelete timers in them etc.
    // Deleting the data structures my become unnecessary if the lists store the
    // structs themselves and not pointers.
    //   RATimerList raTimerList;
    //   DADList dadList;
    //   RDList rdList;
    //   AdvIfList advIfList;
}

void IPv6NeighbourDiscovery::initialize(int stage)
{
    // We have to wait until the 3rd stage (stage 2) with scheduling messages,
    // because interface registration and IPv6 configuration takes places
    // in the first two stages.
    if (stage==3)
    {
        ift = InterfaceTableAccess().get();
        rt6 = RoutingTable6Access().get();
        icmpv6 = ICMPv6Access().get();
        pendingQueue.setName("pendingQueue");

        for (int i=0; i < ift->numInterfaces(); i++)
        {
            InterfaceEntry *ie = ift->interfaceAt(i);

            if (ie->ipv6()->advSendAdvertisements() && !(ie->isLoopback()))
            {
                createRATimer(ie);
            }
        }
        //This simulates random node bootup time. Link local address assignment
        //takes place during this time.
        cMessage *msg = new cMessage("assignLinkLocalAddr", MK_ASSIGN_LINKLOCAL_ADDRESS);
        //We want routers to boot up faster!
        if (rt6->isRouter())
            scheduleAt(uniform(0,0.3), msg);//Random Router bootup time
        else
            scheduleAt(uniform(0.4,1), msg);//Random Host bootup time
    }
}

void IPv6NeighbourDiscovery::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        EV << "Self message received!\n";
        if (msg->kind()==MK_SEND_PERIODIC_RTRADV)
        {
            EV << "Sending periodic RA\n";
            sendPeriodicRA(msg);
        }
        else if (msg->kind()==MK_SEND_SOL_RTRADV)
        {
            EV << "Sending solicited RA\n";
            sendSolicitedRA(msg);
        }
        else if (msg->kind()==MK_ASSIGN_LINKLOCAL_ADDRESS)
        {
            EV << "Assigning Link Local Address\n";
            assignLinkLocalAddress(msg);
        }
        else if (msg->kind()==MK_DAD_TIMEOUT)
        {
            EV << "DAD Timeout message received\n";
            processDADTimeout(msg);
        }
        else if (msg->kind()==MK_RD_TIMEOUT)
        {
            EV << "Router Discovery message received\n";
            processRDTimeout(msg);
        }
        else if (msg->kind()==MK_INITIATE_RTRDIS)
        {
            EV << "initiate router discovery.\n";
            initiateRouterDiscovery(msg);
        }
        else if (msg->kind()==MK_NUD_TIMEOUT)
        {
            EV << "NUD Timeout message received\n";
            processNUDTimeout(msg);
        }
        else if (msg->kind()==MK_AR_TIMEOUT)
        {
            EV << "Address Resolution Timeout message received\n";
            processARTimeout(msg);
        }
        else
            error("Unrecognized Timer");//stops sim w/ error msg.
    }
    else if (dynamic_cast<ICMPv6Message *>(msg))
    {
        //This information will serve as input parameters to various processors.
        IPv6ControlInfo *ctrlInfo
            = check_and_cast<IPv6ControlInfo*>(msg->removeControlInfo());
        ICMPv6Message *ndMsg = (ICMPv6Message *)msg;
        processNDMessage(ndMsg, ctrlInfo);
    }
    else if (dynamic_cast<IPv6Datagram *>(msg))// not ND message
    {
        IPv6Datagram *datagram = (IPv6Datagram *)msg;
        processIPv6Datagram(datagram);
    }
    else
        error("Unknown message type received.\n");
}

void IPv6NeighbourDiscovery::processNDMessage(ICMPv6Message *msg,
    IPv6ControlInfo *ctrlInfo)
{

    if (dynamic_cast<IPv6RouterSolicitation *>(msg))
    {
        IPv6RouterSolicitation *rs = (IPv6RouterSolicitation *)msg;
        processRSPacket(rs, ctrlInfo);
    }
    else if (dynamic_cast<IPv6RouterAdvertisement *>(msg))
    {
        IPv6RouterAdvertisement *ra = (IPv6RouterAdvertisement *)msg;
        processRAPacket(ra, ctrlInfo);
    }
    else if (dynamic_cast<IPv6NeighbourSolicitation *>(msg))
    {
        IPv6NeighbourSolicitation *ns = (IPv6NeighbourSolicitation *)msg;
        processNSPacket(ns, ctrlInfo);
    }
    else if (dynamic_cast<IPv6NeighbourAdvertisement *>(msg))
    {
        IPv6NeighbourAdvertisement *na = (IPv6NeighbourAdvertisement *)msg;
        processNAPacket(na, ctrlInfo);
    }
    else if (dynamic_cast<IPv6Redirect *>(msg))
    {
        IPv6Redirect *redirect = (IPv6Redirect *)msg;
        processRedirectPacket(redirect, ctrlInfo);
    }
    else
    {
        error("Unrecognized ND message!");
    }
}

void IPv6NeighbourDiscovery::finish()
{
}

void IPv6NeighbourDiscovery::processIPv6Datagram(IPv6Datagram *msg)
{
    EV << "Packet " << msg << " arrived from IPv6 module.\n";

    int nextHopIfID;
    EV << "Determining Next Hop" << endl;
    IPv6Address nextHopAddr = determineNextHop(msg->destAddress(), nextHopIfID);
    if (nextHopIfID == -1)
    {
        //draft-ietf-ipv6-2461bis-04 has omitted on-link assumption.
        //draft-ietf-v6ops-onlinkassumption-03 explains why.
        icmpv6->sendErrorMessage(msg, ICMPv6_DESTINATION_UNREACHABLE, NO_ROUTE_TO_DEST);
        return;
    }
    EV << "Next Hop Address is: " << nextHopAddr << " on interface: " << nextHopIfID << endl;

    //RFC2461: Section 5.2 Conceptual Sending Algorithm
    //Once the IP address of the next-hop node is known, the sender examines the
    //Neighbor Cache for link-layer information about that neighbor.
    Neighbour *nce = neighbourCache.lookup(nextHopAddr, nextHopIfID);

    if (nce==NULL)
    {
        //If no entry exists,
        EV << "No Entry exists in the Neighbour Cache.\n";

        //the sender creates one, sets its state to INCOMPLETE,
        EV << "Creating an INCOMPLETE entry in the neighbour cache.\n";
        nce = neighbourCache.addNeighbour(nextHopAddr, nextHopIfID);

        //initiates Address Resolution,
        EV << "Initiating Address Resolution for:" << nextHopAddr
           << " on Interface:" << nextHopIfID << endl;
        initiateAddressResolution(msg->srcAddress(), nce);

        //and then queues the data packet pending completion of address resolution.
        EV << "Add packet to entry's queue until Address Resolution is complete.\n";
        nce->pendingPackets.push_back(msg);
        pendingQueue.insert(msg);
    }
    else if (nce->reachabilityState == IPv6NeighbourCache::INCOMPLETE)
    {
        EV << "Reachability State is INCOMPLETE.Address Resolution already initiated.\n";
        bubble("Packet added to queue until Address Resolution is complete.");
        nce->pendingPackets.push_back(msg);
        pendingQueue.insert(msg);
    }
    else if (nce->macAddress.isUnspecified())
    {
        EV << "NCE's MAC address is unspecified.\n";
        EV << "Initiate Address Resolution and add packet to queue.\n";
        initiateAddressResolution(msg->srcAddress(), nce);
        nce->pendingPackets.push_back(msg);
        pendingQueue.insert(msg);
    }
    else if (nce->reachabilityState == IPv6NeighbourCache::STALE)
    {
        EV << "Reachability State is STALE.\n";
        send(msg,"toIPv6");
        initiateNeighbourUnreachabilityDetection(nce);
    }
    else if (nce->reachabilityState == IPv6NeighbourCache::REACHABLE)
    {
        EV << "Next hop is REACHABLE, sending packet to next-hop address.";
        sendPacketToIPv6Module(msg, nextHopAddr, msg->srcAddress(), nextHopIfID);
    }
    else if (nce->reachabilityState == IPv6NeighbourCache::DELAY)//TODO: What if NCE is in PROBE state?
    {
        EV << "Next hop is in DELAY state, sending packet to next-hop address.";
        sendPacketToIPv6Module(msg, nextHopAddr, msg->srcAddress(), nextHopIfID);
    }
    else
        error("Unknown Neighbour cache entry state.");
}

IPv6NeighbourDiscovery::AdvIfEntry *IPv6NeighbourDiscovery::fetchAdvIfEntry(InterfaceEntry *ie)
{
   for (AdvIfList::iterator it=advIfList.begin(); it!=advIfList.end(); it++)
   {
       AdvIfEntry *advIfEntry = (*it);
       if (advIfEntry->interfaceId == ie->interfaceId())
       {
           return advIfEntry;
       }
   }
   return NULL;
}

IPv6NeighbourDiscovery::RDEntry *IPv6NeighbourDiscovery::fetchRDEntry(InterfaceEntry *ie)
{
   for (RDList::iterator it=rdList.begin(); it!=rdList.end(); it++)
   {
       RDEntry *rdEntry = (*it);
       if (rdEntry->interfaceId == ie->interfaceId())
       {
           return rdEntry;
       }
   }
   return NULL;
}

const MACAddress& IPv6NeighbourDiscovery::resolveNeighbour(const IPv6Address& nextHop, int interfaceId)
{
    Enter_Method("resolveNeighbor(%s,if=%d)", nextHop.str().c_str(), interfaceId);

    Neighbour *nce = neighbourCache.lookup(nextHop, interfaceId);
    //InterfaceEntry *ie = ift->interfaceAt(interfaceId);

    if (!nce || nce->reachabilityState==IPv6NeighbourCache::INCOMPLETE)
        return MACAddress::UNSPECIFIED_ADDRESS;
    else if (nce->reachabilityState==IPv6NeighbourCache::STALE)
        initiateNeighbourUnreachabilityDetection(nce);
    else if (nce->reachabilityState==IPv6NeighbourCache::REACHABLE &&
        simTime() > nce->reachabilityExpires)
    {
        nce->reachabilityState = IPv6NeighbourCache::STALE;
        initiateNeighbourUnreachabilityDetection(nce);
    }
    else if (nce->reachabilityState!=IPv6NeighbourCache::REACHABLE)
    {
        //reachability state must be either in DELAY or PROBE
        ASSERT(nce->reachabilityState==IPv6NeighbourCache::DELAY ||
               nce->reachabilityState==IPv6NeighbourCache::PROBE);
        EV << "NUD in progress.\n";
    }
    //else the entry is REACHABLE and no further action is required here.
    return nce->macAddress;
}

void IPv6NeighbourDiscovery::reachabilityConfirmed(const IPv6Address& neighbour, int interfaceId)
{
    Enter_Method("reachabilityConfirmed(%s,if=%d)", neighbour.str().c_str(), interfaceId);
    //hmmm... this should only be invoked if a TCP ACK was received and NUD is
    //currently being performed on the neighbour where the TCP ACK was received from.

    Neighbour *nce = neighbourCache.lookup(neighbour, interfaceId);

    cMessage *msg = nce->nudTimeoutEvent;
    if (msg != NULL)
    {
        EV << "NUD in progress. Cancelling NUD Timer\n";
        bubble("Reachability Confirmed via NUD.");
        cancelEvent(msg);
        delete msg;
    }

    // TODO (see header file for description)
    /*A neighbor is considered reachable if the node has recently received
    a confirmation that packets sent recently to the neighbor were
    received by its IP layer.  Positive confirmation can be gathered in
    two ways: hints from upper layer protocols that indicate a connection
    is making "forward progress", or receipt of a Neighbor Advertisement
    message that is a response to a Neighbor Solicitation message.

    A connection makes "forward progress" if the packets received from a
    remote peer can only be arriving if recent packets sent to that peer
    are actually reaching it.  In TCP, for example, receipt of a (new)
    acknowledgement indicates that previously sent data reached the peer.
    Likewise, the arrival of new (non-duplicate) data indicates that

    earlier acknowledgements are being delivered to the remote peer.  If
    packets are reaching the peer, they must also be reaching the
    sender's next-hop neighbor; thus "forward progress" is a confirmation
    that the next-hop neighbor is reachable.  For off-link destinations,
    forward progress implies that the first-hop router is reachable.
    When available, this upper-layer information SHOULD be used.

    In some cases (e.g., UDP-based protocols and routers forwarding
    packets to hosts) such reachability information may not be readily
    available from upper-layer protocols.  When no hints are available
    and a node is sending packets to a neighbor, the node actively probes
    the neighbor using unicast Neighbor Solicitation messages to verify
    that the forward path is still working.

    The receipt of a solicited Neighbor Advertisement serves as
    reachability confirmation, since advertisements with the Solicited
    flag set to one are sent only in response to a Neighbor Solicitation.
    Receipt of other Neighbor Discovery messages such as Router
    Advertisements and Neighbor Advertisement with the Solicited flag set
    to zero MUST NOT be treated as a reachability confirmation.  Receipt
    of unsolicited messages only confirm the one-way path from the sender
    to the recipient node.  In contrast, Neighbor Unreachability
    Detection requires that a node keep track of the reachability of the
    forward path to a neighbor from the its perspective, not the
    neighbor's perspective.  Note that receipt of a solicited
    advertisement indicates that a path is working in both directions.
    The solicitation must have reached the neighbor, prompting it to
    generate an advertisement.  Likewise, receipt of an advertisement
    indicates that the path from the sender to the recipient is working.
    However, the latter fact is known only to the recipient; the
    advertisement's sender has no direct way of knowing that the
    advertisement it sent actually reached a neighbor.  From the
    perspective of Neighbor Unreachability Detection, only the
    reachability of the forward path is of interest.*/
}

IPv6Address IPv6NeighbourDiscovery::determineNextHop(
    const IPv6Address& destAddr, int& outIfID)
{
    IPv6Address nextHopAddr;

    //RFC 2461 Section 5.2
    //Next-hop determination for a given unicast destination operates as follows.

    //The sender performs a longest prefix match against the Prefix List to
    //determine whether the packet's destination is on- or off-link.
    EV << "Find out if supplied dest addr is on-link or off-link.\n";
    const IPv6Route *route = rt6->doLongestPrefixMatch(destAddr);

    if (route != NULL)
    {
        //If the destination is on-link, the next-hop address is the same as the
        //packet's destination address.
        if (route->nextHop().isUnspecified())
        {
            EV << "Dest is on-link, next-hop addr is same as dest addr.\n";
            outIfID = route->interfaceID();
            nextHopAddr = destAddr;
        }
        else
        {
            EV << "A next-hop address was found with the route, dest is off-link\n";
            EV << "Assume next-hop address as the selected default router.\n";
            outIfID = route->interfaceID();
            nextHopAddr = route->nextHop();
        }
    }
    else
    {
        //Otherwise, the sender selects a router from the Default Router List
        //(following the rules described in Section 6.3.6).

        EV << "No routes were found, Dest addr is off-link.\n";
        nextHopAddr = selectDefaultRouter(outIfID);

        if (outIfID == -1) EV << "No Default Routers were found.";
        else EV << "Default router found.\n";
    }

    /*the results of next-hop determination computations are saved in the Destination
    Cache (which also contains updates learned from Redirect messages).*/
    rt6->updateDestCache(destAddr, nextHopAddr, outIfID);
    return nextHopAddr;
}

void IPv6NeighbourDiscovery::initiateNeighbourUnreachabilityDetection(
    Neighbour *nce)
{
    ASSERT(nce->reachabilityState==IPv6NeighbourCache::STALE);
    const Key *nceKey = nce->nceKey;
    EV << "Initiating Neighbour Unreachability Detection";
    InterfaceEntry *ie = ift->interfaceAt(nceKey->interfaceID);
    EV << "Setting NCE state to DELAY.\n";
    /*The first time a node sends a packet to a neighbor whose entry is
    STALE, the sender changes the state to DELAY*/
    nce->reachabilityState = IPv6NeighbourCache::DELAY;

    /*and sets a timer to expire in DELAY_FIRST_PROBE_TIME seconds.*/
    cMessage *msg = new cMessage("NUDTimeout", MK_NUD_TIMEOUT);
    msg->setContextPointer(nce);
    nce->nudTimeoutEvent = msg;
    scheduleAt(simTime()+ie->ipv6()->_delayFirstProbeTime(), msg);
}

void IPv6NeighbourDiscovery::processNUDTimeout(cMessage *timeoutMsg)
{
    EV << "NUD has timed out\n";
    Neighbour *nce = (Neighbour *) timeoutMsg->contextPointer();
    const Key *nceKey = nce->nceKey;
    InterfaceEntry *ie = ift->interfaceAt(nceKey->interfaceID);

    if (nce->reachabilityState == IPv6NeighbourCache::DELAY)
    {
        /*If the entry is still in the DELAY state when the timer expires, the
        entry's state changes to PROBE. If reachability confirmation is received,
        the entry's state changes to REACHABLE.*/
        EV << "Neighbour Entry is still in DELAY state.\n";
        EV << "Entering PROBE state. Sending NS probe.\n";
        nce->reachabilityState = IPv6NeighbourCache::PROBE;
        nce->numProbesSent = 0;
    }

    /*If no response is received after waiting RetransTimer milliseconds
    after sending the MAX_UNICAST_SOLICIT solicitations, retransmissions cease
    and the entry SHOULD be deleted. Subsequent traffic to that neighbor will
    recreate the entry and performs address resolution again.*/
    if (nce->numProbesSent == ie->ipv6()->_maxUnicastSolicit())
    {
        EV << "Max number of probes have been sent." << endl;
        EV << "Neighbour is Unreachable, removing NCE." << endl;
        neighbourCache.remove(nceKey->address, nceKey->interfaceID);
        return;
    }

    /*Upon entering the PROBE state, a node sends a unicast Neighbor Solicitation
    message to the neighbor using the cached link-layer address.*/
    createAndSendNSPacket(nceKey->address, nceKey->address,
        ie->ipv6()->preferredAddress(), ie);
    nce->numProbesSent++;
    /*While in the PROBE state, a node retransmits Neighbor Solicitation messages
    every RetransTimer milliseconds until reachability confirmation is obtained.
    Probes are retransmitted even if no additional packets are sent to the
    neighbor.*/
    scheduleAt(simTime()+ie->ipv6()->_retransTimer(), timeoutMsg);
}

IPv6Address IPv6NeighbourDiscovery::selectDefaultRouter(int& outIfID)
{
    EV << "Selecting default router...\n";
    //draft-ietf-ipv6-2461bis-04.txt Section 6.3.6
    /*The algorithm for selecting a router depends in part on whether or not a
    router is known to be reachable. The exact details of how a node keeps track
    of a neighbor's reachability state are covered in Section 7.3.  The algorithm
    for selecting a default router is invoked during next-hop determination when
    no Destination Cache entry exists for an off-link destination or when
    communication through an existing router appears to be failing.  Under normal
    conditions, a router would be selected the first time traffic is sent to a
    destination, with subsequent traffic for that destination using the same router
    as indicated in the Destination Cache modulo any changes to the Destination
    Cache caused by Redirect messages.

    The policy for selecting routers from the Default Router List is as
    follows:*/

    IPv6Address routerAddr;
    //Cycle through all entries in the neighbour cache entry.
    for(IPv6NeighbourCache::iterator it=neighbourCache.begin(); it != neighbourCache.end(); it++)
    {
        Key key = it->first;
        Neighbour nce = it->second;
        bool routerExpired = false;
        if (nce.isDefaultRouter)
        {
            if (simTime()>nce.routerExpiryTime)
            {
                EV << "Found an expired default router. Deleting entry...\n";
                neighbourCache.remove(key.address,key.interfaceID);
                routerExpired = true;
            }
        }

        if (routerExpired == false)
        {
            if (nce.reachabilityState == IPv6NeighbourCache::REACHABLE ||
                nce.reachabilityState == IPv6NeighbourCache::STALE ||
                nce.reachabilityState == IPv6NeighbourCache::DELAY)//TODO: Need to improve this algorithm!
            {
                EV << "Found a router in the neighbour cache(default router list).\n";
                outIfID = key.interfaceID;
                if (routerExpired == false) return key.address;
            }
        }
    }
    EV << "No suitable routers found.\n";

    /*1) Routers that are reachable or probably reachable (i.e., in any state
    other than INCOMPLETE) SHOULD be preferred over routers whose reachability
    is unknown or suspect (i.e., in the INCOMPLETE state, or for which no Neighbor
    Cache entry exists). An implementation may choose to always return the same
    router or cycle through the router list in a round-robin fashion as long as
    it always returns a reachable or a probably reachable router when one is
    available.*/

    /*2) When no routers on the list are known to be reachable or probably
    reachable, routers SHOULD be selected in a round-robin fashion, so that
    subsequent requests for a default router do not return the same router until
    all other routers have been selected.

    Cycling through the router list in this case ensures that all available
    routers are actively probed by the Neighbor Unreachability Detection algorithm.
    A request for a default router is made in conjunction with the sending of a
    packet to a router, and the selected router will be probed for reachability
    as a side effect.*/

    outIfID = -1;//nothing found yet
    return IPv6Address();
}

void IPv6NeighbourDiscovery::timeoutPrefixEntry(const IPv6Address& destPrefix,
    int prefixLength)//REDUNDANT
{
    //RFC 2461: Section 6.3.5
    /*Whenever the invalidation timer expires for a Prefix List entry, that
    entry is discarded.*/
    rt6->removeOnLinkPrefix(destPrefix, prefixLength);
    //hmmm... should the unicast address associated with this prefix be deleted
    //as well?-TODO: The address should be timeout/deleted as well!!

    /*No existing Destination Cache entries need be updated, however. Should a
    reachability problem arise with an existing Neighbor Cache entry, Neighbor
    Unreachability Detection will perform any needed recovery.*/
}

void IPv6NeighbourDiscovery::timeoutDefaultRouter(const IPv6Address& addr,
    int interfaceID)
{
    //RFC 2461: Section 6.3.5
    /*Whenever the Lifetime of an entry in the Default Router List expires,
    that entry is discarded.*/
    neighbourCache.remove(addr, interfaceID);

    /*When removing a router from the Default Router list, the node MUST update
    the Destination Cache in such a way that all entries using the router perform
    next-hop determination again rather than continue sending traffic to the
    (deleted) router.*/
    rt6->purgeDestCacheEntriesToNeighbour(addr, interfaceID);
}

void IPv6NeighbourDiscovery::initiateAddressResolution(const IPv6Address& dgSrcAddr,
    Neighbour *nce)
{
    const Key *nceKey = nce->nceKey;
    InterfaceEntry *ie = ift->interfaceAt(nceKey->interfaceID);
    IPv6Address neighbourAddr = nceKey->address;
    int ifID = nceKey->interfaceID;

    //RFC2461: Section 7.2.2
    //When a node has a unicast packet to send to a neighbor, but does not
    //know the neighbor's link-layer address, it performs address
    //resolution.  For multicast-capable interfaces this entails creating a
    //Neighbor Cache entry in the INCOMPLETE state(already created if not done yet)
    //WEI-If entry already exists, we still have to ensure that its state is INCOMPLETE.
    nce->reachabilityState = IPv6NeighbourCache::INCOMPLETE;

    //and transmitting a Neighbor Solicitation message targeted at the
    //neighbor.  The solicitation is sent to the solicited-node multicast
    //address "corresponding to"(or "derived from") the target address.
    //(in this case, the target address is the address we are trying to resolve)
    EV << "Preparing to send NS to solicited-node multicast group\n";
    EV << "on the next hop interface\n";
    IPv6Address nsDestAddr = neighbourAddr.formSolicitedNodeMulticastAddress();//for NS datagram
    IPv6Address nsTargetAddr = neighbourAddr;//for the field within the NS
    IPv6Address nsSrcAddr;

    /*If the source address of the packet prompting the solicitation is the
    same as one of the addresses assigned to the outgoing interface,*/
    if (ie->ipv6()->hasAddress(dgSrcAddr))
        /*that address SHOULD be placed in the IP Source Address of the outgoing
        solicitation.*/
        nsSrcAddr = dgSrcAddr;
    else
        /*Otherwise, any one of the addresses assigned to the interface
        should be used.*/
        nsSrcAddr = ie->ipv6()->preferredAddress();
    ASSERT(ifID != -1);
    //Sending NS on specified interface.
    createAndSendNSPacket(nsTargetAddr, nsDestAddr, nsSrcAddr, ie);
    nce->numOfARNSSent = 1;
    nce->nsSrcAddr = nsSrcAddr;

    /*While awaiting a response, the sender SHOULD retransmit Neighbor Solicitation
    messages approximately every RetransTimer milliseconds, even in the absence
    of additional traffic to the neighbor. Retransmissions MUST be rate-limited
    to at most one solicitation per neighbor every RetransTimer milliseconds.*/
    cMessage *msg = new cMessage("arTimeout", MK_AR_TIMEOUT);//AR msg timer
    nce->arTimer = msg;
    msg->setContextPointer(nce);
    scheduleAt(simTime()+ie->ipv6()->_retransTimer(), msg);
}


void IPv6NeighbourDiscovery::processARTimeout(cMessage *arTimeoutMsg)
{
    //AR timeouts are cancelled when a valid solicited NA is received.
    Neighbour *nce = (Neighbour *)arTimeoutMsg->contextPointer();
    const Key *nceKey = nce->nceKey;
    IPv6Address nsTargetAddr = nceKey->address;
    InterfaceEntry *ie = ift->interfaceAt(nceKey->interfaceID);
    EV << "Num Of NS Sent:" << nce->numOfARNSSent << endl;
    EV << "Max Multicast Solicitation:" << ie->ipv6()->_maxMulticastSolicit() << endl;
    if (nce->numOfARNSSent < ie->ipv6()->_maxMulticastSolicit())
    {
        EV << "Sending another Address Resolution NS message" << endl;
        IPv6Address nsDestAddr = nsTargetAddr.formSolicitedNodeMulticastAddress();
        createAndSendNSPacket(nsTargetAddr, nsDestAddr, nce->nsSrcAddr, ie);
        nce->numOfARNSSent++;
        scheduleAt(simTime()+ie->ipv6()->_retransTimer(), arTimeoutMsg);
        return;
    }
    EV << "Address Resolution has failed." << endl;
    dropQueuedPacketsAwaitingAR(nce);
    EV << "Deleting AR timeout msg\n";
    delete arTimeoutMsg;
}

void IPv6NeighbourDiscovery::dropQueuedPacketsAwaitingAR(Neighbour *nce)
{
    const Key *nceKey = nce->nceKey;
    //RFC 2461: Section 7.2.2
    /*If no Neighbor Advertisement is received after MAX_MULTICAST_SOLICIT
    solicitations, address resolution has failed. The sender MUST return ICMP
    destination unreachable indications with code 3 (Address Unreachable) for
    each packet queued awaiting address resolution.*/
    MsgPtrVector pendingPackets = nce->pendingPackets;
    EV << "Pending Packets empty:" << pendingPackets.empty() << endl;
    while (!pendingPackets.empty())
    {
        MsgPtrVector::iterator i = pendingPackets.begin();
        cMessage *msg = (*i);
        IPv6Datagram *ipv6Msg = (IPv6Datagram *)msg;
        //Assume msg is the packet itself. I need the datagram's source addr.
        //The datagram's src addr will be the destination of the unreachable msg.
        EV << "Sending ICMP unreachable destination." << endl;
        pendingPackets.erase(i);
        pendingQueue.remove(msg);
        icmpv6->sendErrorMessage(ipv6Msg, ICMPv6_DESTINATION_UNREACHABLE, ADDRESS_UNREACHABLE);
    }

    //RFC 2461: Section 7.3.3
    /*If address resolution fails, the entry SHOULD be deleted, so that subsequent
    traffic to that neighbor invokes the next-hop determination procedure again.*/
    EV << "Removing neighbour cache entry" << endl;
    neighbourCache.remove(nceKey->address, nceKey->interfaceID);
}

void IPv6NeighbourDiscovery::sendPacketToIPv6Module(cMessage *msg, const IPv6Address& destAddr,
    const IPv6Address& srcAddr, int interfaceId)
{
    IPv6ControlInfo *controlInfo = new IPv6ControlInfo();
    controlInfo->setProtocol(IP_PROT_IPv6_ICMP);
    controlInfo->setDestAddr(destAddr);
    controlInfo->setSrcAddr(srcAddr);
    controlInfo->setHopLimit(255);
    controlInfo->setInterfaceId(interfaceId);
    msg->setControlInfo(controlInfo);

    send(msg,"toIPv6");
}

/**Not used yet-unsure if we really need it. --DELETED, Andras*/

void IPv6NeighbourDiscovery::sendQueuedPacketsToIPv6Module(Neighbour *nce)
{
    MsgPtrVector& pendingPackets = nce->pendingPackets;
    while(!pendingPackets.empty())//FIXME: pendingPackets are always empty!!!!
    {
        MsgPtrVector::iterator i = pendingPackets.begin();
        cMessage *msg = (*i);
        pendingPackets.erase(i);
        pendingQueue.remove(msg);
        EV << "Sending queued packet " << msg << endl;
        send(msg,"toIPv6");
    }
}

void IPv6NeighbourDiscovery::assignLinkLocalAddress(cMessage *timerMsg)
{
    //Node has booted up. Start assigning a link-local address for each
    //interface in this node.
    for (int i=0; i < ift->numInterfaces(); i++)
{
        InterfaceEntry *ie = ift->interfaceAt(i);

        //Skip the loopback interface.
        if (ie->isLoopback()) continue;

    IPv6Address linkLocalAddr = ie->ipv6()->linkLocalAddress();
    if (linkLocalAddr.isUnspecified())
    {
        //if no link local address exists for this interface, we assign one to it.
            EV << "No link local address exists. Forming one" << endl;
        linkLocalAddr = IPv6Address().formLinkLocalAddress(ie->interfaceToken());
        ie->ipv6()->assignAddress(linkLocalAddr, true, 0, 0);
    }

        //Before we can use this address, we MUST initiate DAD first.
        initiateDAD(linkLocalAddr, ie);
    }
    delete timerMsg;
}

void IPv6NeighbourDiscovery::initiateDAD(const IPv6Address& tentativeAddr,
    InterfaceEntry *ie)
{
    DADEntry *dadEntry = new DADEntry();
    dadEntry->interfaceId = ie->interfaceId();
    dadEntry->address = tentativeAddr;
    dadEntry->numNSSent = 0;
    dadList.insert(dadEntry);
    /*
    RFC2462: Section 5.4.2
    To check an address, a node sends DupAddrDetectTransmits Neighbor
    Solicitations, each separated by RetransTimer milliseconds. The
    solicitation's Target Address is set to the address being checked,
    the IP source is set to the unspecified address and the IP
    destination is set to the solicited-node multicast address of the
    target address.*/
    IPv6Address destAddr = tentativeAddr.formSolicitedNodeMulticastAddress();
    //Send a NS
    createAndSendNSPacket(tentativeAddr, destAddr,
        IPv6Address::UNSPECIFIED_ADDRESS, ie);
    dadEntry->numNSSent++;

    cMessage *msg = new cMessage("dadTimeout", MK_DAD_TIMEOUT);
    msg->setContextPointer(dadEntry);
    scheduleAt(simTime()+ie->ipv6()->retransTimer(), msg);
}

void IPv6NeighbourDiscovery::processDADTimeout(cMessage *msg)
{
    DADEntry *dadEntry = (DADEntry *)msg->contextPointer();
    InterfaceEntry *ie = (InterfaceEntry *)ift->interfaceAt(dadEntry->interfaceId);
    IPv6Address tentativeAddr = dadEntry->address;
    //Here, we need to check how many DAD messages for the interface entry were
    //sent vs. DupAddrDetectTransmits
    EV << "numOfDADMessagesSent is: " << dadEntry->numNSSent << endl;
    EV << "dupAddrDetectTrans is: " << ie->ipv6()->dupAddrDetectTransmits() << endl;
    if (dadEntry->numNSSent < ie->ipv6()->dupAddrDetectTransmits())
    {
        bubble("Sending another DAD NS message.");
        IPv6Address destAddr = tentativeAddr.formSolicitedNodeMulticastAddress();
        createAndSendNSPacket(dadEntry->address, destAddr, IPv6Address::UNSPECIFIED_ADDRESS, ie);
        dadEntry->numNSSent++;
        //Reuse the received msg
        scheduleAt(simTime()+ie->ipv6()->retransTimer(), msg);
    }
    else
    {
        bubble("Max number of DAD messages for interface sent. Address is unique.");
        ie->ipv6()->permanentlyAssign(tentativeAddr);
        dadList.erase(dadEntry);
        EV << "delete dadEntry and msg\n";
        delete dadEntry;
        delete msg;
        /*RFC 2461: Section 6.3.7 2nd Paragraph
        Before a host sends an initial solicitation, it SHOULD delay the
        transmission for a random amount of time between 0 and
        MAX_RTR_SOLICITATION_DELAY.  This serves to alleviate congestion when
        many hosts start up on a link at the same time, such as might happen
        after recovery from a power failure.*/
        //TODO: Placing these operations here means fast router solicitation is
        //not adopted. Will relocate.
        if (ie->ipv6()->advSendAdvertisements() == false)
        {
            EV << "creating router discovery message timer\n";
            cMessage *rtrDisMsg = new cMessage("initiateRTRDIS",MK_INITIATE_RTRDIS);
            rtrDisMsg->setContextPointer(ie);
            simtime_t interval = uniform(0, SIMTIME_DBL(ie->ipv6()->_maxRtrSolicitationDelay())); // random delay
            scheduleAt(simTime()+interval, rtrDisMsg);
        }
    }
}

IPv6RouterSolicitation *IPv6NeighbourDiscovery::createAndSendRSPacket(InterfaceEntry *ie)
{
    ASSERT(ie->ipv6()->advSendAdvertisements() == false);
    //RFC 2461: Section 6.3.7 Sending Router Solicitations
    //A host sends Router Solicitations to the All-Routers multicast address. The
    //IP source address is set to either one of the interface's unicast addresses
    //or the unspecified address.
    IPv6Address myIPv6Address = ie->ipv6()->preferredAddress();
    if (myIPv6Address.isUnspecified())
        myIPv6Address = ie->ipv6()->linkLocalAddress();//so we use the link local address instead
    if (ie->ipv6()->isTentativeAddress(myIPv6Address))
        myIPv6Address = IPv6Address::UNSPECIFIED_ADDRESS;//set my IPv6 address to unspecified.
    IPv6Address destAddr = IPv6Address::ALL_ROUTERS_2;//all_routers multicast
    IPv6RouterSolicitation *rs = new IPv6RouterSolicitation("RSpacket");
    rs->setType(ICMPv6_ROUTER_SOL);

    //The Source Link-Layer Address option SHOULD be set to the host's link-layer
    //address, if the IP source address is not the unspecified address.
    if (!myIPv6Address.isUnspecified())
        rs->setSourceLinkLayerAddress(ie->macAddress());

    //Construct a Router Solicitation message
    sendPacketToIPv6Module(rs, destAddr, myIPv6Address, ie->interfaceId());
    return rs;
}

void IPv6NeighbourDiscovery::initiateRouterDiscovery(cMessage *msg)
{
    EV << "Initiating Router Discovery" << endl;
    InterfaceEntry *ie = (InterfaceEntry *)msg->contextPointer();
    delete msg;
    //RFC2461: Section 6.3.7
    /*When an interface becomes enabled, a host may be unwilling to wait for the
    next unsolicited Router Advertisement to locate default routers or learn
    prefixes.  To obtain Router Advertisements quickly, a host SHOULD transmit up
    to MAX_RTR_SOLICITATIONS Router Solicitation messages each separated by at
    least RTR_SOLICITATION_INTERVAL seconds.(FIXME:Therefore this should be invoked
    at the beginning of the simulation-WEI)*/
    RDEntry *rdEntry = new RDEntry();
    rdEntry->interfaceId = ie->interfaceId();
    rdEntry->numRSSent = 0;
    createAndSendRSPacket(ie);
    rdEntry->numRSSent++;

    //Create and schedule a message for retransmission to this module
    cMessage *rdTimeoutMsg = new cMessage("processRDTimeout", MK_RD_TIMEOUT);
    rdTimeoutMsg->setContextPointer(ie);
    rdEntry->timeoutMsg = rdTimeoutMsg;
    rdList.insert(rdEntry);
    /*Before a host sends an initial solicitation, it SHOULD delay the
    transmission for a random amount of time between 0 and
    MAX_RTR_SOLICITATION_DELAY.  This serves to alleviate congestion when
    many hosts start up on a link at the same time, such as might happen
    after recovery from a power failure.  If a host has already performed
    a random delay since the interface became (re)enabled (e.g., as part
    of Duplicate Address Detection [ADDRCONF]) there is no need to delay
    again before sending the first Router Solicitation message.*/
    //simtime_t rndInterval = uniform(0, ie->ipv6()->_maxRtrSolicitationDelay());
    scheduleAt(simTime()+ie->ipv6()->_rtrSolicitationInterval(), rdTimeoutMsg);
}

void IPv6NeighbourDiscovery::cancelRouterDiscovery(InterfaceEntry *ie)
{
    //Next we retrieve the rdEntry with the Interface Entry.
    RDEntry *rdEntry = fetchRDEntry(ie);
    if (rdEntry != NULL)
    {
        EV << "rdEntry is not NULL, RD cancelled!" << endl;
        cancelEvent(rdEntry->timeoutMsg);
        rdList.erase(rdEntry);
        delete rdEntry;
    }
    else
        EV << "rdEntry is NULL, not cancelling RD!" << endl;
}

void IPv6NeighbourDiscovery::processRDTimeout(cMessage *msg)
{
    InterfaceEntry *ie = (InterfaceEntry *)msg->contextPointer();
    RDEntry *rdEntry = fetchRDEntry(ie);
    if (rdEntry->numRSSent < ie->ipv6()->_maxRtrSolicitations())
    {
        bubble("Sending another RS message.");
        createAndSendRSPacket(ie);
        rdEntry->numRSSent++;
        //Need to find out if this is the last RS we are sending out.
        if (rdEntry->numRSSent == ie->ipv6()->_maxRtrSolicitations())
            scheduleAt(simTime()+ie->ipv6()->_maxRtrSolicitationDelay(), msg);
        else
            scheduleAt(simTime()+ie->ipv6()->_rtrSolicitationInterval(), msg);
    }
    else
    {
        //RFC 2461, Section 6.3.7
        /*If a host sends MAX_RTR_SOLICITATIONS solicitations, and receives no Router
        Advertisements after having waited MAX_RTR_SOLICITATION_DELAY seconds after
        sending the last solicitation, the host concludes that there are no routers
        on the link for the purpose of [ADDRCONF]. However, the host continues to
        receive and process Router Advertisements messages in the event that routers
        appear on the link.*/
        bubble("Max number of RS messages sent");
        EV << "No RA messages were received. Assume no routers are on-link";
        delete rdEntry;
        delete msg;
    }
}

void IPv6NeighbourDiscovery::processRSPacket(IPv6RouterSolicitation *rs,
    IPv6ControlInfo *rsCtrlInfo)
{
    if (validateRSPacket(rs, rsCtrlInfo) == false) return;
    //Find out which interface the RS message arrived on.
    InterfaceEntry *ie = ift->interfaceAt(rsCtrlInfo->interfaceId());
    AdvIfEntry *advIfEntry = fetchAdvIfEntry(ie);//fetch advertising interface entry.

    //RFC 2461: Section 6.2.6
    //A host MUST silently discard any received Router Solicitation messages.
    if (ie->ipv6()->advSendAdvertisements())
    {
        EV << "This is an advertising interface, processing RS\n";

        if (validateRSPacket(rs, rsCtrlInfo) == false) return;
        EV << "RS message validated\n";

        //First we extract RS specific information from the received message
        MACAddress macAddr = rs->sourceLinkLayerAddress();
        EV << "MAC Address extracted\n";
        delete rs;

        /*A router MAY choose to unicast the response directly to the soliciting
        host's address (if the solicitation's source address is not the unspecified
        address), but the usual case is to multicast the response to the
        all-nodes group. In the latter case, the interface's interval timer is
        reset to a new random value, as if an unsolicited advertisement had just
        been sent(see Section 6.2.4).*/

        /*In all cases, Router Advertisements sent in response to a Router
        Solicitation MUST be delayed by a random time between 0 and
        MAX_RA_DELAY_TIME seconds. (If a single advertisement is sent in
        response to multiple solicitations, the delay is relative to the
        first solicitation.)  In addition, consecutive Router Advertisements
        sent to the all-nodes multicast address MUST be rate limited to no
        more than one advertisement every MIN_DELAY_BETWEEN_RAS seconds.*/

        /*A router might process Router Solicitations as follows:
        - Upon receipt of a Router Solicitation, compute a random delay
        within the range 0 through MAX_RA_DELAY_TIME. If the computed
        value corresponds to a time later than the time the next multicast
        Router Advertisement is scheduled to be sent, ignore the random
        delay and send the advertisement at the already-scheduled time.*/
        cMessage *msg = new cMessage("sendSolicitedRA", MK_SEND_SOL_RTRADV);
        msg->setContextPointer(ie);
        simtime_t interval = uniform(0, SIMTIME_DBL(ie->ipv6()->_maxRADelayTime()));

        if (interval < advIfEntry->nextScheduledRATime)
        {
            simtime_t nextScheduledTime;
            nextScheduledTime = simTime()+interval;
            scheduleAt(nextScheduledTime, msg);
            advIfEntry->nextScheduledRATime = nextScheduledTime;
        }
        //else we ignore the generate interval and send it at the next scheduled time.

        //We need to keep a log here each time an RA is sent. Not implemented yet.
        //Assume the first course of action.
        /*- If the router sent a multicast Router Advertisement (solicited or
        unsolicited) within the last MIN_DELAY_BETWEEN_RAS seconds,
        schedule the advertisement to be sent at a time corresponding to
        MIN_DELAY_BETWEEN_RAS plus the random value after the previous
        advertisement was sent. This ensures that the multicast Router
        Advertisements are rate limited.

        - Otherwise, schedule the sending of a Router Advertisement at the
        time given by the random value.*/
    }
    else
    {
        EV << "This interface is a host, discarding RA message\n";
        delete rs;
    }
}

bool IPv6NeighbourDiscovery::validateRSPacket(IPv6RouterSolicitation *rs,
    IPv6ControlInfo *rsCtrlInfo)
{
    bool result = true;
    /*6.1.1.  Validation of Router Solicitation Messages
    A router MUST silently discard any received Router Solicitation
    messages that do not satisfy all of the following validity checks:

    - The IP Hop Limit field has a value of 255, i.e., the packet
    could not possibly have been forwarded by a router.*/
    if (rsCtrlInfo->hopLimit() != 255)
    {
        EV << "Hop limit is not 255! RS validation failed!\n";
        result = false;
    }
    //- ICMP Code is 0.
    if (rsCtrlInfo->protocol() != IP_PROT_IPv6_ICMP)
    {
        EV << "ICMP Code is not 0! RS validation failed!\n";
        result = false;
    }
    //- If the IP source address is the unspecified address, there is no
    //source link-layer address option in the message.
    if (rsCtrlInfo->srcAddr().isUnspecified())
    {
        EV << "IP source address is unspecified\n";
        if (rs->sourceLinkLayerAddress().isUnspecified() == false)
        {
            EV << " but source link layer address is provided. RS validation failed!\n";
        }
    }
    return result;
}

IPv6RouterAdvertisement *IPv6NeighbourDiscovery::createAndSendRAPacket(
    const IPv6Address& destAddr, InterfaceEntry *ie)
{
    EV << "Create and send RA invoked!\n";
    //Must use link-local addr. See: RFC2461 Section 6.1.2
    IPv6Address sourceAddr = ie->ipv6()->linkLocalAddress();

    //This operation includes all options, regardless whether it is solicited or unsolicited.
    if (ie->ipv6()->advSendAdvertisements()) //if this is an advertising interface
    {
        //Construct a Router Advertisment message
        IPv6RouterAdvertisement *ra = new IPv6RouterAdvertisement("RApacket");
        ra->setType(ICMPv6_ROUTER_AD);

        //RFC 2461: Section 6.2.3 Router Advertisment Message Content
        /*A router sends periodic as well as solicited Router Advertisements out
        its advertising interfaces.  Outgoing Router Advertisements are filled
        with the following values consistent with the message format given in
        Section 4.2:*/

        //- In the Router Lifetime field: the interface's configured AdvDefaultLifetime.
        ra->setRouterLifetime(SIMTIME_DBL(ie->ipv6()->advDefaultLifetime()));

        //- In the M and O flags: the interface's configured AdvManagedFlag and
        //AdvOtherConfigFlag, respectively.  See [ADDRCONF].
        ra->setManagedAddrConfFlag(ie->ipv6()->advManagedFlag());
        ra->setOtherStatefulConfFlag(ie->ipv6()->advOtherConfigFlag());

        //- In the Cur Hop Limit field: the interface's configured CurHopLimit.
        ra->setCurHopLimit(ie->ipv6()->advCurHopLimit());

        //- In the Reachable Time field: the interface's configured AdvReachableTime.
        ra->setReachableTime(ie->ipv6()->advReachableTime());

        //- In the Retrans Timer field: the interface's configured AdvRetransTimer.
        ra->setRetransTimer(ie->ipv6()->advRetransTimer());

        //- In the options:
        /*o Source Link-Layer Address option: link-layer address of the sending
            interface.  (Assumption: We always send this)*/
        ra->setSourceLinkLayerAddress(ie->macAddress());
        ra->setMTU(ie->ipv6()->advLinkMTU());

        //Add all Advertising Prefixes to the RA
        int numAdvPrefixes = ie->ipv6()->numAdvPrefixes();
        EV << "Number of Adv Prefixes: " << numAdvPrefixes << endl;
        ra->setPrefixInformationArraySize(numAdvPrefixes);
        for (int i = 0; i < numAdvPrefixes; i++)
        {
            IPv6InterfaceData::AdvPrefix advPrefix = ie->ipv6()->advPrefix(i);
            IPv6NDPrefixInformation prefixInfo;
            prefixInfo.setPrefix(advPrefix.prefix);
            prefixInfo.setPrefixLength(advPrefix.prefixLength);

            //- In the "on-link" flag: the entry's AdvOnLinkFlag.
            prefixInfo.setOnlinkFlag(advPrefix.advOnLinkFlag);
            //- In the Valid Lifetime field: the entry's AdvValidLifetime.
            prefixInfo.setValidLifetime(SIMTIME_DBL(advPrefix.advValidLifetime));
            //- In the "Autonomous address configuration" flag: the entry's
            //AdvAutonomousFlag.
            prefixInfo.setAutoAddressConfFlag(advPrefix.advAutonomousFlag);
            //- In the Preferred Lifetime field: the entry's AdvPreferredLifetime.
            prefixInfo.setPreferredLifetime(SIMTIME_DBL(advPrefix.advPreferredLifetime));
            //Now we pop the prefix info into the RA.
            ra->setPrefixInformation(i, prefixInfo);
        }
        sendPacketToIPv6Module(ra, destAddr, sourceAddr, ie->interfaceId());
        return ra;
    }
}

void IPv6NeighbourDiscovery::processRAPacket(IPv6RouterAdvertisement *ra,
    IPv6ControlInfo *raCtrlInfo)
{
    InterfaceEntry *ie = ift->interfaceAt(raCtrlInfo->interfaceId());

    if (ie->ipv6()->advSendAdvertisements())
    {
        EV << "Interface is an advertising interface, dropping RA message.\n";
        delete ra;
        return;
    }
    else
    {
        if (validateRAPacket(ra, raCtrlInfo) == false)
        {
            delete ra;
            return;
        }
        cancelRouterDiscovery(ie);//Cancel router discovery if it is in progress.
        EV << "Interface is a host, processing RA.\n";

        processRAForRouterUpdates(ra, raCtrlInfo);//See RFC2461: Section 6.3.4

        //Possible options
        MACAddress macAddress = ra->sourceLinkLayerAddress();
        uint mtu = ra->MTU();
        for (int i = 0; i < ra->prefixInformationArraySize(); i++)
        {
            IPv6NDPrefixInformation& prefixInfo = ra->prefixInformation(i);
            if (prefixInfo.autoAddressConfFlag() == true)//If auto addr conf is set
                processRAPrefixInfoForAddrAutoConf(prefixInfo, ie);//We process prefix Info and form an addr
        }
    }
    delete raCtrlInfo;
    delete ra;
}

void IPv6NeighbourDiscovery::processRAForRouterUpdates(IPv6RouterAdvertisement *ra,
    IPv6ControlInfo *raCtrlInfo)
{
    EV << "Processing RA for Router Updates\n";
    //RFC2461: Section 6.3.4
    //Paragraphs 1 and 2 omitted.

    //On receipt of a valid Router Advertisement, a host extracts the source
    //address of the packet and does the following:
    IPv6Address raSrcAddr = raCtrlInfo->srcAddr();
    InterfaceEntry *ie = ift->interfaceAt(raCtrlInfo->interfaceId());
    int ifID = ie->interfaceId();

    /*- If the address is not already present in the host's Default Router List,
    and the advertisement's Router Lifetime is non-zero, create a new entry in
    the list, and initialize its invalidation timer value from the advertisement's
    Router Lifetime field.*/
    Neighbour *neighbour = neighbourCache.lookup(raSrcAddr, ifID);
    if (neighbour == NULL)
    {
        EV << "Neighbour Cache Entry does not contain RA's source address\n";
        if (ra->routerLifetime() != 0)
        {
            EV << "RA's router lifetime is non-zero, creating an entry in the "
               << "Host's default router list.\n" << ra->routerLifetime();
            //If a Neighbor Cache entry is created for the router its reachability
            //state MUST be set to STALE as specified in Section 7.3.3.
            if (ra->sourceLinkLayerAddress().isUnspecified())
            {
                neighbour = neighbourCache.addRouter(raSrcAddr, ifID,
                    simTime()+ra->routerLifetime());
                //Note:invalidation timers are not explicitly defined.
            }
            else
            {
                neighbour = neighbourCache.addRouter(raSrcAddr, ifID,
                    ra->sourceLinkLayerAddress(), simTime()+ra->routerLifetime());
                //According to Greg, we should add a default route for hosts as well!
                rt6->addDefaultRoute(raSrcAddr, ifID, simTime()+ra->routerLifetime());
            }
        }
        else
        {
            EV << "Router Lifetime is 0, adding NON-default router.\n";
            //WEI-The router is advertising itself, BUT not as a default router.
            if (ra->sourceLinkLayerAddress().isUnspecified())
                neighbour = neighbourCache.addNeighbour(raSrcAddr, ifID);
            else
                neighbour = neighbourCache.addNeighbour(raSrcAddr, ifID,
                    ra->sourceLinkLayerAddress());
            neighbour->isRouter = true;
        }
    }
    else
    {
        //If no Source Link-Layer Address is included, but a corresponding Neighbor
        //Cache entry exists, its IsRouter flag MUST be set to TRUE.
        neighbour->isRouter = true;

        //If a cache entry already exists and is updated with a different link-
        //layer address the reachability state MUST also be set to STALE.
        if (ra->sourceLinkLayerAddress().isUnspecified() == false &&
            neighbour->macAddress.equals(ra->sourceLinkLayerAddress()) == false)
            neighbour->macAddress = ra->sourceLinkLayerAddress();

        /*- If the address is already present in the host's Default Router List
        as a result of a previously-received advertisement, reset its invalidation
        timer to the Router Lifetime value in the newly-received advertisement.*/
        neighbour->routerExpiryTime = simTime()+ra->routerLifetime();

        /*- If the address is already present in the host's Default Router List
        and the received Router Lifetime value is zero, immediately time-out the
        entry as specified in Section 6.3.5.*/
        if (ra->routerLifetime() == 0)
        {
            EV << "RA's router lifetime is ZERO. Timing-out entry.\n";
            timeoutDefaultRouter(raSrcAddr, ifID);
        }
    }

    //Paragraph Omitted.

    //If the received Cur Hop Limit value is non-zero the host SHOULD set
    //its CurHopLimit variable to the received value.
    if (ra->curHopLimit() != 0)
    {
        EV << "RA's Cur Hop Limit is non-zero. Setting host's Cur Hop Limit to "
           << "received value.\n";
        ie->ipv6()->setCurHopLimit(ra->curHopLimit());
    }

    //If the received Reachable Time value is non-zero the host SHOULD set its
    //BaseReachableTime variable to the received value.
    if (ra->reachableTime() != 0)
    {
        EV << "RA's reachable time is non-zero ";
        if (ra->reachableTime() != SIMTIME_DBL(ie->ipv6()->reachableTime()))
        {
            EV << " and RA's and Host's reachable time differ, \nsetting host's base"
               << " reachable time to received value.\n";
            ie->ipv6()->setBaseReachableTime(ra->reachableTime());
            //If the new value differs from the previous value, the host SHOULD
            //recompute a new random ReachableTime value.
            ie->ipv6()->setReachableTime(ie->ipv6()->generateReachableTime());
        }
        EV << endl;
    }

    //The RetransTimer variable SHOULD be copied from the Retrans Timer field,
    //if the received value is non-zero.
    if (ra->retransTimer() != 0)
    {
        EV << "RA's retrans timer is non-zero, copying retrans timer variable.\n";
        ie->ipv6()->setRetransTimer(ra->retransTimer());
    }

    /*If the MTU option is present, hosts SHOULD copy the option's value into
    LinkMTU so long as the value is greater than or equal to the minimum link MTU
    [IPv6] and does not exceed the default LinkMTU value specified in the link
    type specific document (e.g., [IPv6-ETHER]).*/
    //TODO: not done yet

    processRAPrefixInfo(ra, ie);
}

void IPv6NeighbourDiscovery::processRAPrefixInfo(IPv6RouterAdvertisement *ra,
    InterfaceEntry *ie)
{
    //Continued from section 6.3.4
    /*Prefix Information options that have the "on-link" (L) flag set indicate a
    prefix identifying a range of addresses that should be considered on-link.
    Note, however, that a Prefix Information option with the on-link flag set to
    zero conveys no information concerning on-link determination and MUST NOT be
    interpreted to mean that addresses covered by the prefix are off-link. The
    only way to cancel a previous on-link indication is to advertise that prefix
    with the L-bit set and the Lifetime set to zero. The default behavior (see
    Section 5.2) when sending a packet to an address for which no information is
    known about the on-link status of the address is to forward the packet to a
    default router; the reception of a Prefix Information option with the "on-link "
    (L) flag set to zero does not change this behavior. The reasons for an address
    being treated as on-link is specified in the definition of "on-link" in
    Section 2.1. Prefixes with the on-link flag set to zero would normally have
    the autonomous flag set and be used by [ADDRCONF].*/
    IPv6NDPrefixInformation prefixInfo;
    //For each Prefix Information option
    for (int i = 0; i < ra->prefixInformationArraySize(); i++)
    {
        prefixInfo = ra->prefixInformation(i);
        if (!prefixInfo.onlinkFlag()) break;//skip to next prefix option

        //with the on-link flag set, a host does the following:
        EV << "Fetching Prefix Information:" << i+1 << " of "
           << ra->prefixInformationArraySize() << endl;
        uint prefixLength = prefixInfo.prefixLength();
        simtime_t validLifetime = prefixInfo.validLifetime();
        uint preferredLifetime = prefixInfo.preferredLifetime();
        IPv6Address prefix = prefixInfo.prefix();

        //- If the prefix is the link-local prefix, silently ignore the Prefix
        //Information option.
        if (prefix.isLinkLocal())
        {
            EV << "Prefix is link-local, ignoring prefix.\n";
            return;
        }

        //- If the prefix is not already present in the Prefix List,
        if (!rt6->isPrefixPresent(prefix)) {
            //and the Prefix Information option's Valid Lifetime field is non-zero,
            if (validLifetime != 0)
            {
                /*create a new entry for the prefix and initialize its invalidation
                timer to the Valid Lifetime value in the Prefix Information option.*/
                rt6->addOrUpdateOnLinkPrefix(prefix, prefixLength, ie->interfaceId(),
                    simTime()+validLifetime);
            }
            /*- If the Prefix Information option's Valid Lifetime field is zero,
            and the prefix is not present in the host's Prefix List,
            silently ignore the option.*/
        }
        else
        {
            /* If the new Lifetime value is zero, time-out the prefix immediately
            (see Section 6.3.5).*/
            if (validLifetime == 0)
            {
                EV << "Prefix Info's valid lifetime is 0, time-out prefix\n";
                rt6->removeOnLinkPrefix(prefix, prefixLength);
                return;
            }
            /*- If the prefix is already present in the host's Prefix List as
            the result of a previously-received advertisement, reset its
            invalidation timer to the Valid Lifetime value in the Prefix
            Information option.*/
            rt6->addOrUpdateOnLinkPrefix(prefix, prefixLength, ie->interfaceId(),
                simTime()+validLifetime);
        }

        /*Stateless address autoconfiguration [ADDRCONF] may in some
        circumstances increase the Valid Lifetime of a prefix or ignore it
        completely in order to prevent a particular denial of service attack.
        However, since the effect of the same denial of service targeted at
        the on-link prefix list is not catastrophic (hosts would send packets
        to a default router and receive a redirect rather than sending
        packets directly to a neighbor) the Neighbor Discovery protocol does
        not impose such a check on the prefix lifetime values.*/
    }
}

void IPv6NeighbourDiscovery::processRAPrefixInfoForAddrAutoConf(
    IPv6NDPrefixInformation& prefixInfo, InterfaceEntry *ie)
{
    EV << "Processing Prefix Info for address auto-configuration.\n";
    IPv6Address prefix = prefixInfo.prefix();
    uint prefixLength = prefixInfo.prefixLength();
    simtime_t preferredLifetime = prefixInfo.preferredLifetime();
    simtime_t validLifetime = prefixInfo.validLifetime();

    //RFC 2461: Section 5.5.3
    //First condition tested, the autonomous flag is already set

    //b) If the prefix is the link-local prefix, silently ignore the Prefix
    //Information option.
    if (prefixInfo.prefix().isLinkLocal() == true)
    {
        EV << "Prefix is link-local, ignore Prefix Information Option\n";
        return;
    }

    //c) If the preferred lifetime is greater than the valid lifetime, silently
    //ignore the Prefix Information option. A node MAY wish to log a system
    //management error in this case.
    if (preferredLifetime > validLifetime)
    {
        EV << "Preferred lifetime is greater than valid lifetime, ignore Prefix Information\n";
        return;
    }

    bool isPrefixAssignedToInterface = false;
    for (int i = 0; i < ie->ipv6()->numAddresses(); i++)
    {
        if (ie->ipv6()->address(i).matches(prefix, prefixLength) == true)
            isPrefixAssignedToInterface = true;
    }
    /*d) If the prefix advertised does not match the prefix of an address already
         in the list, and the Valid Lifetime is not 0, form an address (and add
         it to the list) by combining the advertised prefix with the link�s
         interface identifier as follows:*/
    if (isPrefixAssignedToInterface == false && validLifetime != 0)
    {
        IPv6Address linkLocalAddress = ie->ipv6()->linkLocalAddress();
        ASSERT(linkLocalAddress.isUnspecified() == false);
        IPv6Address newAddr = linkLocalAddress.setPrefix(prefix, prefixLength);
        //TODO: for now we leave the newly formed address as not tentative,
        //according to Greg, we have to always perform DAD for a newly formed address.
        EV << "Assigning new address to: " << ie->name() << endl;
        ie->ipv6()->assignAddress(newAddr, false, simTime()+validLifetime,
            simTime()+preferredLifetime);
    }

    //TODO: this is the simplified version.
    /*e) If the advertised prefix matches the prefix of an autoconfigured
       address (i.e., one obtained via stateless or stateful address
       autoconfiguration) in the list of addresses associated with the
       interface, the specific action to perform depends on the Valid
       Lifetime in the received advertisement and the Lifetime
       associated with the previously autoconfigured address (which we
       call StoredLifetime in the discussion that follows):

       1) If the received Lifetime is greater than 2 hours or greater
          than StoredLifetime, update the stored Lifetime of the
          corresponding address.

       2) If the StoredLifetime is less than or equal to 2 hours and the
          received Lifetime is less than or equal to StoredLifetime,
          ignore the prefix, unless the Router Advertisement from which

          this Prefix Information option was obtained has been
          authenticated (e.g., via IPSec [RFC2402]). If the Router
          Advertisment was authenticated, the StoredLifetime should be
          set to the Lifetime in the received option.

       3) Otherwise, reset the stored Lifetime in the corresponding
          address to two hours.*/

}

void IPv6NeighbourDiscovery::createRATimer(InterfaceEntry *ie)
{
    cMessage *msg = new cMessage("sendPeriodicRA", MK_SEND_PERIODIC_RTRADV);
    msg->setContextPointer(ie);
    AdvIfEntry *advIfEntry = new AdvIfEntry();
    advIfEntry->interfaceId = ie->interfaceId();
    advIfEntry->numRASent = 0;
    simtime_t interval
        = uniform(SIMTIME_DBL(ie->ipv6()->minRtrAdvInterval()),SIMTIME_DBL(ie->ipv6()->maxRtrAdvInterval()));
    advIfEntry->raTimeoutMsg = msg;

    simtime_t nextScheduledTime = simTime() + interval;
    advIfEntry->nextScheduledRATime = nextScheduledTime;
    advIfList.insert(advIfEntry);
    EV << "Interval: " << interval << endl;
    EV << "Next scheduled time: " << nextScheduledTime << endl;
    //now we schedule the msg for whatever time that was derived
    scheduleAt(nextScheduledTime, msg);
}

void IPv6NeighbourDiscovery::resetRATimer(InterfaceEntry *ie)
{//Not used yet but could be useful later on.-WEI
    //Iterate through all RA timers within the Neighbour Discovery module.
/*
    for (RATimerList::iterator it=raTimerList.begin(); it != raTimerList.end(); it++)
    {
        cMessage *msg = (*it);
        InterfaceEntry *msgIE = (InterfaceEntry *)msg->contextPointer();
        //Find the timer that matches the given Interface Entry.
        if (msgIE->outputPort() == ie->outputPort())
        {
            EV << "Resetting RA timer for port: " << ie->outputPort();
            cancelEvent(msg);//Cancel the next scheduled msg.
            simtime_t interval
                = uniform(ie->ipv6()->minRtrAdvInterval(),ie->ipv6()->maxRtrAdvInterval());
            scheduleAt(simTime()+interval, msg);
        }
    }
*/
}

void IPv6NeighbourDiscovery::sendPeriodicRA(cMessage *msg)
{
    InterfaceEntry *ie = (InterfaceEntry *)msg->contextPointer();
    AdvIfEntry *advIfEntry = fetchAdvIfEntry(ie);
    IPv6Address destAddr = IPv6Address("FF02::1");
    createAndSendRAPacket(destAddr, ie);
    advIfEntry->numRASent++;
    simtime_t nextScheduledTime;

    //RFC 2461, Section 6.2.4
    /*Whenever a multicast advertisement is sent from an interface, the timer is
    reset to a uniformly-distributed random value between the interface's
    configured MinRtrAdvInterval and MaxRtrAdvInterval; expiration of the timer
    causes the next advertisement to be sent and a new random value to be chosen.*/
    simtime_t interval
        = uniform(SIMTIME_DBL(ie->ipv6()->minRtrAdvInterval()),SIMTIME_DBL(ie->ipv6()->maxRtrAdvInterval()));
    nextScheduledTime = simTime() + interval;

    /*For the first few advertisements (up to MAX_INITIAL_RTR_ADVERTISEMENTS)
    sent from an interface when it becomes an advertising interface,*/
    EV << "Num RA sent is: " << advIfEntry->numRASent << endl;
    EV << "maxInitialRtrAdvertisements is: " << ie->ipv6()->_maxInitialRtrAdvertisements() << endl;
    if(advIfEntry->numRASent <= ie->ipv6()->_maxInitialRtrAdvertisements())
    {
        if (interval > ie->ipv6()->_maxInitialRtrAdvertInterval())
        {
            //if the randomly chosen interval is greater than MAX_INITIAL_RTR_ADVERT_INTERVAL,
            //the timer SHOULD be set to MAX_INITIAL_RTR_ADVERT_INTERVAL instead.
            nextScheduledTime = simTime() + ie->ipv6()->_maxInitialRtrAdvertInterval();
            EV << "Sending initial RA but interval is too long. Using default value." << endl;
        }
        else
            EV << "Sending initial RA. Using randomly generated interval." << endl;
    }
    EV << "Next scheduled time: " << nextScheduledTime << endl;
    advIfEntry->nextScheduledRATime = nextScheduledTime;
    ASSERT(nextScheduledTime > simTime());
    scheduleAt(nextScheduledTime, msg);
}

void IPv6NeighbourDiscovery::sendSolicitedRA(cMessage *msg)
{
    EV << "Send Solicited RA invoked!\n";
    InterfaceEntry *ie = (InterfaceEntry *)msg->contextPointer();
    IPv6Address destAddr = IPv6Address("FF02::1");
    EV << "Testing condition!\n";
    createAndSendRAPacket(destAddr, ie);
    delete msg;
}

bool IPv6NeighbourDiscovery::validateRAPacket(IPv6RouterAdvertisement *ra,
    IPv6ControlInfo *raCtrlInfo)
{
    bool result = true;

    //RFC 2461: Section 6.1.2 Validation of Router Advertisement Messages
    /*A node MUST silently discard any received Router Advertisement
    messages that do not satisfy all of the following validity checks:*/
    raCtrlInfo->srcAddr();
    //- IP Source Address is a link-local address.  Routers must use
    //  their link-local address as the source for Router Advertisement
    //  and Redirect messages so that hosts can uniquely identify
    //  routers.
    if (raCtrlInfo->srcAddr().isLinkLocal() == false)
    {
        EV << "RA source address is not link-local. RA validation failed!\n";
        result = false;
    }

    //- The IP Hop Limit field has a value of 255, i.e., the packet
    //  could not possibly have been forwarded by a router.
    if (raCtrlInfo->hopLimit() != 255)
    {
        EV << "Hop limit is not 255! RA validation failed!\n";
        result = false;
    }

    //- ICMP Code is 0.
    if (raCtrlInfo->protocol() != IP_PROT_IPv6_ICMP)
    {
        EV << "ICMP Code is not 0! RA validation failed!\n";
        result = false;
    }

    return result;
}

IPv6NeighbourSolicitation *IPv6NeighbourDiscovery::createAndSendNSPacket(
    const IPv6Address& nsTargetAddr, const IPv6Address& dgDestAddr,
    const IPv6Address& dgSrcAddr, InterfaceEntry *ie)
{
    MACAddress myMacAddr = ie->macAddress();

    //Construct a Neighbour Solicitation message
    IPv6NeighbourSolicitation *ns = new IPv6NeighbourSolicitation("NSpacket");
    ns->setType(ICMPv6_NEIGHBOUR_SOL);

    //Neighbour Solicitation Specific Information
    ns->setTargetAddress(nsTargetAddr);

    /*If the solicitation is being sent to a solicited-node multicast
    address, the sender MUST include its link-layer address (if it has
    one) as a Source Link-Layer Address option.*/
    if (dgDestAddr.matches(IPv6Address("FF02::1:FF00:0"),104) && // FIXME what's this? make constant...
        !dgSrcAddr.isUnspecified())
        ns->setSourceLinkLayerAddress(myMacAddr);

    sendPacketToIPv6Module(ns, dgDestAddr, dgSrcAddr, ie->interfaceId());

    return ns;
}

void IPv6NeighbourDiscovery::processNSPacket(IPv6NeighbourSolicitation *ns,
    IPv6ControlInfo *nsCtrlInfo)
{
    //Control Information
    InterfaceEntry *ie = ift->interfaceAt(nsCtrlInfo->interfaceId());

    IPv6Address nsTargetAddr = ns->targetAddress();

    //RFC 2461:Section 7.2.3
    //If target address is not a valid "unicast" or anycast address assigned to the
    //receiving interface, we should silently discard the packet.
    if (validateNSPacket(ns, nsCtrlInfo) == false
        || ie->ipv6()->hasAddress(nsTargetAddr) == false)
    {
        bubble("NS validation failed\n");
        delete nsCtrlInfo;
        delete ns;
        return;
    }
    bubble("NS validation passed.\n");
    if (ie->ipv6()->isTentativeAddress(nsTargetAddr))
    {
        //If the Target Address is tentative, the Neighbor Solicitation should
        //be processed as described in [ADDRCONF].
        EV << "Process NS for Tentative target address.\n";
        processNSForTentativeAddress(ns, nsCtrlInfo);
    }
    else
    {
        //Otherwise, the following description applies.
        EV << "Process NS for Non-Tentative target address.\n";
        processNSForNonTentativeAddress(ns, nsCtrlInfo, ie);
    }
    delete nsCtrlInfo;
    delete ns;
}

bool IPv6NeighbourDiscovery::validateNSPacket(IPv6NeighbourSolicitation *ns,
    IPv6ControlInfo *nsCtrlInfo)
{
    bool result = true;
    /*RFC 2461:7.1.1. Validation of Neighbor Solicitations(some checks are omitted)
    A node MUST silently discard any received Neighbor Solicitation
    messages that do not satisfy all of the following validity checks:*/
    //- The IP Hop Limit field has a value of 255, i.e., the packet
    //could not possibly have been forwarded by a router.
    if (nsCtrlInfo->hopLimit() != 255)
    {
        EV << "Hop limit is not 255! NS validation failed!\n";
        result = false;
    }
    //- Target Address is not a multicast address.
    if (ns->targetAddress().isMulticast() == true)
    {
        EV << "Target address is a multicast address! NS validation failed!\n";
        result = false;
    }
    //- If the IP source address is the unspecified address,
    if (nsCtrlInfo->srcAddr().isUnspecified())
    {
        EV << "Source Address is unspecified\n";
        //the IP destination address is a solicited-node multicast address.
        if (nsCtrlInfo->destAddr().matches(IPv6Address::SOLICITED_NODE_PREFIX,104) == false)
        {
            EV << " but IP dest address is not a solicited-node multicast address! NS validation failed!\n";
            result = false;
        }
        //there is no source link-layer address option in the message.
        else if (ns->sourceLinkLayerAddress().isUnspecified() == false)
        {
            EV << " but Source link-layer address is not empty! NS validation failed!\n";
            result = false;
        }
        else
            EV << "NS Validation Passed\n";
    }

    return result;
}

void IPv6NeighbourDiscovery::processNSForTentativeAddress(IPv6NeighbourSolicitation *ns,
    IPv6ControlInfo *nsCtrlInfo)
{
    //Control Information
    IPv6Address nsSrcAddr = nsCtrlInfo->srcAddr();
    IPv6Address nsDestAddr = nsCtrlInfo->destAddr();

    ASSERT(nsSrcAddr.isUnicast() || nsSrcAddr.isUnspecified());
    //solicitation is processed as described in RFC2462:section 5.4.3

    if (nsSrcAddr.isUnspecified())
    {
        EV << "Source Address is UNSPECIFIED. Sender is performing DAD\n";
        //Sender performing Duplicate Address Detection
        if (rt6->localDeliver(nsSrcAddr))
            EV << "NS comes from myself. Ignoring NS\n";
        else
            EV << "NS comes from another node. Address is duplicate!\n";
            error("Duplicate Address Detected! Manual Attention Required!");
    }
    else if (nsSrcAddr.isUnicast())
    {
        //Sender performing address resolution
        EV << "Sender is performing Address Resolution\n";
        EV << "Target Address is tentative. Ignoring NS.\n";
    }
}

void IPv6NeighbourDiscovery::processNSForNonTentativeAddress(IPv6NeighbourSolicitation *ns,
    IPv6ControlInfo *nsCtrlInfo, InterfaceEntry *ie)
{
    //Neighbour Solicitation Information
    MACAddress nsMacAddr = ns->sourceLinkLayerAddress();

    int ifID = ie->interfaceId();

    //target addr is not tentative addr
    //solicitation processed as described in RFC2461:section 7.2.3
    if (nsCtrlInfo->srcAddr().isUnspecified())
    {
        EV << "Address is duplicate! Inform Sender of duplicate address!\n";
        sendSolicitedNA(ns, nsCtrlInfo, ie);
    }
    else
    {
        processNSWithSpecifiedSrcAddr(ns, nsCtrlInfo, ie);
    }
}

void IPv6NeighbourDiscovery::processNSWithSpecifiedSrcAddr(IPv6NeighbourSolicitation *ns,
    IPv6ControlInfo *nsCtrlInfo, InterfaceEntry *ie)
{
    //RFC 2461, Section 7.2.3
    /*If the Source Address is not the unspecified address and, on link layers
    that have addresses, the solicitation includes a Source Link-Layer Address
    option, then the recipient SHOULD create or update the Neighbor Cache entry
    for the IP Source Address of the solicitation.*/

    //Neighbour Solicitation Information
    MACAddress nsMacAddr = ns->sourceLinkLayerAddress();

    int ifID = ie->interfaceId();

    //Look for the Neighbour Cache Entry
    Neighbour *entry = neighbourCache.lookup(nsCtrlInfo->srcAddr(), ifID);

    if (entry == NULL)
    {
        /*If an entry does not already exist, the node SHOULD create a new one
        and set its reachability state to STALE as specified in Section 7.3.3.*/
        EV << "Neighbour Entry not found. Create a Neighbour Cache Entry.\n";
        neighbourCache.addNeighbour(nsCtrlInfo->srcAddr(), ifID, nsMacAddr);
    }
    else
    {
        /*If an entry already exists, and the cached link-layer address differs from
        the one in the received Source Link-Layer option,*/
        if (!(entry->macAddress.equals(nsMacAddr)) && !nsMacAddr.isUnspecified())
        {
            //the cached address should be replaced by the received address
            entry->macAddress = nsMacAddr;
            //and the entry's reachability state MUST be set to STALE.
            entry->reachabilityState = IPv6NeighbourCache::STALE;
        }
    }
    /*After any updates to the Neighbor Cache, the node sends a Neighbor
    Advertisement response as described in the next section.*/
    sendSolicitedNA(ns, nsCtrlInfo, ie);
}

void IPv6NeighbourDiscovery::sendSolicitedNA(IPv6NeighbourSolicitation *ns,
    IPv6ControlInfo *nsCtrlInfo, InterfaceEntry *ie)
{
    IPv6NeighbourAdvertisement *na = new IPv6NeighbourAdvertisement("NApacket");
    //RFC 2461: Section 7.2.4
    /*A node sends a Neighbor Advertisement in response to a valid Neighbor
    Solicitation targeting one of the node's assigned addresses.  The
    Target Address of the advertisement is copied from the Target Address
    of the solicitation.*/
    na->setTargetAddress(ns->targetAddress());

    /*If the solicitation's IP Destination Address is not a multicast address,
    the Target Link-Layer Address option MAY be omitted; the neighboring node's
    cached value must already be current in order for the solicitation to have
    been received. If the solicitation's IP Destination Address is a multicast
    address, the Target Link-Layer option MUST be included in the advertisement.*/
    na->setTargetLinkLayerAddress(ie->macAddress());//here, we always include the MAC addr.

    /*Furthermore, if the node is a router, it MUST set the Router flag to one;
    otherwise it MUST set the flag to zero.*/
    na->setRouterFlag(rt6->isRouter());

    /*If the (NS)Target Address is either an anycast address or a unicast
    address for which the node is providing proxy service, or the Target
    Link-Layer Address option is not included,*/
    //TODO:ANYCAST will not be implemented here!
    if (ns->sourceLinkLayerAddress().isUnspecified())
        //the Override flag SHOULD be set to zero.
        na->setOverrideFlag(false);
    else
        //Otherwise, the Override flag SHOULD be set to one.
        na->setOverrideFlag(true);
    /*Proper setting of the Override flag ensures that nodes give preference to
    non-proxy advertisements, even when received after proxy advertisements, and
    also ensures that the first advertisement for an anycast address "wins".*/

    IPv6Address naDestAddr;
    //If the source of the solicitation is the unspecified address,
    if(nsCtrlInfo->srcAddr().isUnspecified())
    {
        /*the node MUST set the Solicited flag to zero and multicast the advertisement
        to the all-nodes address.*/
        na->setSolicitedFlag(false);
        naDestAddr = IPv6Address::ALL_NODES_2;
    }
    else
    {
        /*Otherwise, the node MUST set the Solicited flag to one and unicast
        the advertisement to the Source Address of the solicitation.*/
        na->setSolicitedFlag(true);
        naDestAddr = nsCtrlInfo->srcAddr();
    }

    /*If the Target Address is an anycast address the sender SHOULD delay sending
    a response for a random time between 0 and MAX_ANYCAST_DELAY_TIME seconds.*/
    /*TODO: More associated complexity for this one. We will have to delay
    sending off the solicitation. Perhaps the self message could have a context
    pointer pointing to a struct with enough info to create and send a NA packet.*/

    /*Because unicast Neighbor Solicitations are not required to include a
    Source Link-Layer Address, it is possible that a node sending a
    solicited Neighbor Advertisement does not have a corresponding link-
    layer address for its neighbor in its Neighbor Cache.  In such
    situations, a node will first have to use Neighbor Discovery to
    determine the link-layer address of its neighbor (i.e, send out a
    multicast Neighbor Solicitation).*/
    //TODO: if above mentioned happens, can addr resolution be performed for ND messages?
    //if no link-layer addr exists for unicast addr when sending solicited NA, we should
    //add the NA to the list of queued packets. What if we have a list of queued
    //packets for different unicast solicitations? each time addr resolution is
    //done we should check the destinations of the list of queued packets and send
    //off the respective ones.
    IPv6Address myIPv6Addr = ie->ipv6()->preferredAddress();
    sendPacketToIPv6Module(na, naDestAddr, myIPv6Addr, ie->interfaceId());
}

void IPv6NeighbourDiscovery::sendUnsolicitedNA(InterfaceEntry *ie)
{
    //RFC 2461
    //Section 7.2.6: Sending Unsolicited Neighbor Advertisements

    /*In some cases a node may be able to determine that its link-layer
    address has changed (e.g., hot-swap of an interface card) and may
    wish to inform its neighbors of the new link-layer address quickly.
    In such cases a node MAY send up to MAX_NEIGHBOR_ADVERTISEMENT
    unsolicited Neighbor Advertisement messages to the all-nodes
    multicast address.  These advertisements MUST be separated by at
    least RetransTimer seconds.

    The Target Address field in the unsolicited advertisement is set to
    an IP address of the interface, and the Target Link-Layer Address
    option is filled with the new link-layer address.  The Solicited flag
    MUST be set to zero, in order to avoid confusing the Neighbor
    Unreachability Detection algorithm.  If the node is a router, it MUST
    set the Router flag to one; otherwise it MUST set it to zero.  The
    Override flag MAY be set to either zero or one.  In either case,
    neighboring nodes will immediately change the state of their Neighbor
    Cache entries for the Target Address to STALE, prompting them to
    verify the path for reachability.  If the Override flag is set to
    one, neighboring nodes will install the new link-layer address in
    their caches.  Otherwise, they will ignore the new link-layer
    address, choosing instead to probe the cached address.

    A node that has multiple IP addresses assigned to an interface MAY
    multicast a separate Neighbor Advertisement for each address.  In
    such a case the node SHOULD introduce a small delay between the
    sending of each advertisement to reduce the probability of the
    advertisements being lost due to congestion.

    A proxy MAY multicast Neighbor Advertisements when its link-layer
    address changes or when it is configured (by system management or
    other mechanisms) to proxy for an address.  If there are multiple
    nodes that are providing proxy services for the same set of addresses
    the proxies SHOULD provide a mechanism that prevents multiple proxies
    from multicasting advertisements for any one address, in order to
    reduce the risk of excessive multicast traffic.

    Also, a node belonging to an anycast address MAY multicast
    unsolicited Neighbor Advertisements for the anycast address when the
    node's link-layer address changes.

    Note that because unsolicited Neighbor Advertisements do not reliably
    update caches in all nodes (the advertisements might not be received
    by all nodes), they should only be viewed as a performance
    optimization to quickly update the caches in most neighbors.  The
    Neighbor Unreachability Detection algorithm ensures that all nodes
    obtain a reachable link-layer address, though the delay may be
    slightly longer.*/
}

void IPv6NeighbourDiscovery::processNAPacket(IPv6NeighbourAdvertisement *na,
    IPv6ControlInfo *naCtrlInfo)
{
    if (validateNAPacket(na, naCtrlInfo) == false)
    {
        delete naCtrlInfo;
        delete na;
        return;
    }

    //Neighbour Advertisement Information
    IPv6Address naTargetAddr = na->targetAddress();

    //First, we check if the target address in NA is found in the interface it
    //was received on is tentative.
    InterfaceEntry *ie = ift->interfaceAt(naCtrlInfo->interfaceId());
    if (ie->ipv6()->isTentativeAddress(naTargetAddr))
    {
        error("Duplicate Address Detected! Manual attention needed!");
    }
    //Logic as defined in Section 7.2.5
    Neighbour *neighbourEntry = neighbourCache.lookup(naTargetAddr, ie->interfaceId());

    if (neighbourEntry == NULL)
    {
        EV << "NA received. Target Address not found in Neighbour Cache\n";
        EV << "Dropping NA packet.\n";
        delete naCtrlInfo;
        delete na;
        return;
    }

    //Target Address has entry in Neighbour Cache
    EV << "NA received. Target Address found in Neighbour Cache\n";

    if (neighbourEntry->reachabilityState == IPv6NeighbourCache::INCOMPLETE)
        processNAForIncompleteNCEState(na, neighbourEntry);
    else
        processNAForOtherNCEStates(na, neighbourEntry);
    delete naCtrlInfo;
    delete na;
}

bool IPv6NeighbourDiscovery::validateNAPacket(IPv6NeighbourAdvertisement *na,
    IPv6ControlInfo *naCtrlInfo)
{
    bool result = true;//adopt optimistic approach

    //RFC 2461:7.1.2 Validation of Neighbor Advertisments(some checks are omitted)
    //A node MUST silently discard any received Neighbor Advertisment messages
    //that do not satisfy all of the following validity checks:

    //- The IP Hop Limit field has a value of 255, i.e., the packet
    //  could not possibly have been forwarded by a router.
    if (naCtrlInfo->hopLimit() != 255)
    {
        EV << "Hop Limit is not 255! NA validation failed!\n";
        result = false;
    }

    //- Target Address is not a multicast address.
    if (na->targetAddress().isMulticast() == true)
    {
        EV << "Target Address is a multicast address! NA validation failed!\n";
        result = false;
    }

    //- If the IP Destination Address is a multicast address the Solicited flag
    //  is zero.
    if (naCtrlInfo->destAddr().isMulticast())
    {
        if (na->solicitedFlag() == true)
        {
            EV << "Dest Address is multicast address but solicted flag is 0!\n";
            result = false;
        }
    }

    if (result == true) bubble("NA validation passed.");
    else bubble("NA validation failed.");
    return result;
}

void IPv6NeighbourDiscovery::processNAForIncompleteNCEState(
                    IPv6NeighbourAdvertisement *na, Neighbour *nce)
{
    MACAddress naMacAddr = na->targetLinkLayerAddress();
    bool naRouterFlag = na->routerFlag();
    bool naSolicitedFlag = na->solicitedFlag();
    const Key *nceKey = nce->nceKey;
    InterfaceEntry *ie = ift->interfaceAt(nceKey->interfaceID);

    /*If the target's neighbour Cache entry is in the INCOMPLETE state when the
    advertisement is received, one of two things happens.*/
    if (naMacAddr.isUnspecified())
    {
        /*If the link layer has addresses and no Target Link-Layer address option
        is included, the receiving node SHOULD silently discard the received
        advertisement.*/
        EV << "No MAC Address specified in NA. Ignoring NA\n";
        return;
    }
    else
    {
        //Otherwise, the receiving node performs the following steps:
        //- It records the link-layer address in the neighbour Cache entry.
        EV << "ND is updating Neighbour Cache Entry.\n";
        nce->macAddress = naMacAddr;

        //- If the advertisement's Solicited flag is set, the state of the
        //  entry is set to REACHABLE, otherwise it is set to STALE.
        if (naSolicitedFlag == true)
        {
            nce->reachabilityState = IPv6NeighbourCache::REACHABLE;
            EV << "Reachability confirmed through successful Addr Resolution.\n";
            nce->reachabilityExpires = simTime() + ie->ipv6()->_reachableTime();
        }
        else
            nce->reachabilityState = IPv6NeighbourCache::STALE;

        //- It sets the IsRouter flag in the cache entry based on the Router
        //  flag in the received advertisement.
        nce->isRouter = naRouterFlag;

        //- It sends any packets queued for the neighbour awaiting address
        //  resolution.
        sendQueuedPacketsToIPv6Module(nce);
        cancelEvent(nce->arTimer);
    }
}

void IPv6NeighbourDiscovery:: processNAForOtherNCEStates(
    IPv6NeighbourAdvertisement *na, Neighbour *nce)
{
    bool naRouterFlag = na->routerFlag();
    bool naSolicitedFlag = na->solicitedFlag();
    bool naOverrideFlag = na->overrideFlag();
    MACAddress naMacAddr = na->targetLinkLayerAddress();
    const Key *nceKey = nce->nceKey;
    InterfaceEntry *ie = ift->interfaceAt(nceKey->interfaceID);

    /*draft-ietf-ipv6-2461bis-04
    Section 7.2.5: Receipt of Neighbour Advertisements
    If the target's Neighbor Cache entry is in any state other than INCOMPLETE
    when the advertisement is received, the following actions take place:*/

    if (naOverrideFlag == false && !(naMacAddr.equals(nce->macAddress))
        && !(naMacAddr.isUnspecified()))
    {
        EV << "NA override is FALSE and NA MAC addr is different.\n";
        //I. If the Override flag is clear and the supplied link-layer address
        //   differs from that in the cache, then one of two actions takes place:
        //(Note: An unspecified MAC should not be compared with the NCE's mac!)
        //a. If the state of the entry is REACHABLE,
        if (nce->reachabilityState == IPv6NeighbourCache::REACHABLE)
        {
            EV << "NA mac is different. Change NCE state from REACHABLE to STALE\n";
            //set it to STALE, but do not update the entry in any other way.
            nce->reachabilityState = IPv6NeighbourCache::STALE;
        }
        else
            //b. Otherwise, the received advertisement should be ignored and
            //MUST NOT update the cache.
            EV << "NCE is not in REACHABLE state. Ignore NA.\n";
    }
    else if (naOverrideFlag == true || naMacAddr.equals(nce->macAddress)
        || naMacAddr.isUnspecified())
    {
        EV << "NA override flag is TRUE. or Advertised MAC is same as NCE's. or"
           << " NA MAC is not specified.\n";
        /*II. If the Override flag is set, or the supplied link-layer address
        is the same as that in the cache, or no Target Link-layer address
        option was supplied, the received advertisement MUST update the
        Neighbor Cache entry as follows:*/

        /*- The link-layer address in the Target Link-Layer Address option
            MUST be inserted in the cache (if one is supplied and is
            Different than the already recorded address).*/
        if (!(naMacAddr.isUnspecified()) &&
            !(naMacAddr.equals(nce->macAddress)))
        {
            EV << "Updating NCE's MAC addr with NA's.\n";
            nce->macAddress = naMacAddr;
        }

        //- If the Solicited flag is set,
        if (naSolicitedFlag == true)
        {
            EV << "Solicited Flag is TRUE. Set NCE state to REACHABLE.\n";
            //the state of the entry MUST be set to REACHABLE.
            nce->reachabilityState = IPv6NeighbourCache::REACHABLE;
            //We have to cancel the NUD self timer message if there is one.
            cMessage *msg = nce->nudTimeoutEvent;
            if (msg != NULL)
            {
                EV << "NUD in progress. Cancelling NUD Timer\n";
                bubble("Reachability Confirmed via NUD.");
                nce->reachabilityExpires = simTime() + ie->ipv6()->_reachableTime();
                cancelEvent(msg);
                delete msg;
            }
        }
        else
        {
            //If the Solicited flag is zero
            EV << "Solicited Flag is FALSE.\n";
            //and the link layer address was updated with a different address
            if (!(naMacAddr.equals(nce->macAddress)))
            {
                EV << "NA's MAC is different from NCE's.Set NCE state to STALE\n";
                //the state MUST be set to STALE.
                nce->reachabilityState = IPv6NeighbourCache::STALE;
            }
            else
                //Otherwise, the entry's state remains unchanged.
                EV << "NA's MAC is the same as NCE's. State remains unchanged.\n";
        }
        //(Next paragraph with explanation is omitted.-WEI)

        /*- The IsRouter flag in the cache entry MUST be set based on the
        Router flag in the received advertisement.*/
        EV << "Updating NCE's router flag to " << naRouterFlag << endl;
        nce->isRouter = naRouterFlag;

        //TODO: To be implemented
        /*In those cases where the IsRouter flag changes from TRUE to FALSE as a
        result of this update, the node MUST remove that router from the Default
        Router List and update the Destination Cache entries for all destinations
        using that neighbor as a router as specified in Section 7.3.3. This is
        needed to detect when a node that is used as a router stops forwarding
        packets due to being configured as a host.*/
    }
}

IPv6Redirect *IPv6NeighbourDiscovery::createAndSendRedirectPacket(InterfaceEntry *ie)
{
    //Construct a Redirect message
    IPv6Redirect *redirect = new IPv6Redirect("redirectMsg");
    redirect->setType(ICMPv6_REDIRECT);

    //Redirect Message Specific Information
    //redirect->setTargetAddress();
    //redirect->setDestinationAddress();

    //Possible Option
    //redirect->setTargetLinkLayerAddress();

    return redirect;
}

void IPv6NeighbourDiscovery::processRedirectPacket(IPv6Redirect *redirect,
    IPv6ControlInfo *ctrlInfo)
{
    //First we need to extract information from the redirect message
    IPv6Address targetAddr = redirect->targetAddress();//Addressed to me
    IPv6Address destAddr = redirect->destinationAddress();//new dest addr

    //Optional
    MACAddress macAddr = redirect->targetLinkLayerAddress();
}

