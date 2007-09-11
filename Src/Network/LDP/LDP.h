//
// (C) 2005 Vojtech Janota
// (C) 2004 Andras Varga
//
// This library is free software, you can redistribute it
// and/or modify
// it under  the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation;
// either version 2 of the License, or any later version.
// The library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//

#ifndef __LDP_H__
#define __LDP_H__


#include <string>
#include <omnetpp.h>
#include <iostream>
#include <vector>
#include "INETDefs.h"
#include "LDPPacket_m.h"
#include "UDPSocket.h"
#include "TCPSocket.h"
#include "TCPSocketMap.h"
#include "IClassifier.h"
#include "NotificationBoard.h"

#define LDP_PORT  646

#define LDP_TRAFFIC         4       // session (TCP) traffic
#define LDP_HELLO_TRAFFIC   5       // discovery (UDP) traffic
#define LDP_USER_TRAFFIC    100     // label switched user traffic


class InterfaceTable;
class RoutingTable;
class LIBTable;
class TED;


/**
 * LDP (rfc 3036) protocol implementation.
 */
class INET_API LDP: public cSimpleModule, public TCPSocket::CallbackInterface, public IClassifier, public INotifiable
{
  public:

    struct fec_t
    {
        int fecid;

        // FEC value
        IPAddress addr;
        int length;

        // FEC's next hop address
        IPAddress nextHop;

        // possibly also: (speed up)
        // std::string nextHopInterface
    };
    typedef std::vector<fec_t> FecVector;


    struct fec_bind_t
    {
        int fecid;

        IPAddress peer;
        int label;
    };
    typedef std::vector<fec_bind_t> FecBindVector;


    struct pending_req_t
    {
        int fecid;
        IPAddress peer;
    };
    typedef std::vector<pending_req_t> PendingVector;

    struct peer_info
    {
        IPAddress peerIP;   // IP address of LDP peer
        bool activeRole;    // we're in active or passive role in this session
        TCPSocket *socket;  // TCP socket
        std::string linkInterface;
        cMessage *timeout;
    };
    typedef std::vector<peer_info> PeerVector;

  private:
    // configuration
    double holdTime;
    double helloInterval;

    // currently recognized FECs
    FecVector fecList;
    // bindings advertised upstream
    FecBindVector fecUp;
    // mappings learnt from downstream
    FecBindVector fecDown;
    // currently requested and yet unserviced mappings
    PendingVector pending;

    // the collection of all HELLO adjacencies.
    PeerVector myPeers;

    //
    // other variables:
    //
    InterfaceTable *ift;
    RoutingTable *rt;
    LIBTable *lt;
    TED *tedmod;
    NotificationBoard *nb;

    UDPSocket udpSocket;     // for sending/receiving Hello
    TCPSocket serverSocket;  // for listening on LDP_PORT
    TCPSocketMap socketMap;  // holds TCP connections with peers

    // hello timeout message
    cMessage *sendHelloMsg;

    int maxFecid;

  private:
    /**
     * This method finds next peer in upstream direction
     */
    IPAddress locateNextHop(IPAddress dest);

    /**
     * This method maps the peerIP with the interface name in routing table.
     * It is expected that for MPLS host, entries linked to MPLS peers are available.
     * In case no corresponding peerIP found, a peerIP (not deterministic)
     * will be returned.
     */
    IPAddress findPeerAddrFromInterface(std::string interfaceName);

    //This method is the reserve of above method
    std::string findInterfaceFromPeerAddr(IPAddress peerIP);

    /** Utility: return peer's index in myPeers table, or -1 if not found */
    int findPeer(IPAddress peerAddr);

    /** Utility: return socket for given peer. Throws error if there's no TCP connection */
    TCPSocket *peerSocket(IPAddress peerAddr);
    /** Utility: return socket for given peer and NULL if session doesn't exist */
    TCPSocket *peerSocketSoft(IPAddress peerAddr);

    void sendToPeer(IPAddress dest, cMessage *msg);


    //bool matches(const FEC_TLV& a, const FEC_TLV& b);

    FecVector::iterator findFecEntry(FecVector& fecs, IPAddress addr, int length);
    FecBindVector::iterator findFecEntry(FecBindVector& fecs, int fecid, IPAddress peer);

    void sendMappingRequest(IPAddress dest, IPAddress addr, int length);
    void sendMapping(int type, IPAddress dest, int label, IPAddress addr, int length);
    void sendNotify(int status, IPAddress dest, IPAddress addr, int length);

    void rebuildFecList();
    void updateFecList(IPAddress nextHop);
    void updateFecListEntry(fec_t oldItem);

    void announceLinkChange(int tedlinkindex);

  public:
    LDP();
    virtual ~LDP();

  protected:
    virtual int numInitStages() const  {return 4;}
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);

    void sendHelloTo(IPAddress dest);
    void openTCPConnectionToPeer(int peerIndex);

    void processLDPHello(LDPHello *msg);
    void processHelloTimeout(cMessage *msg);
    void processMessageFromTCP(cMessage *msg);
    void processLDPPacketFromTCP(LDPPacket *ldpPacket);

    void processLABEL_MAPPING(LDPLabelMapping *packet);
    void processLABEL_REQUEST(LDPLabelRequest *packet);
    void processLABEL_RELEASE(LDPLabelMapping *packet);
    void processLABEL_WITHDRAW(LDPLabelMapping *packet);
    void processNOTIFICATION(LDPNotify* packet);

    /** @name TCPSocket::CallbackInterface callback methods */
    //@{
    virtual void socketEstablished(int connId, void *yourPtr);
    virtual void socketDataArrived(int connId, void *yourPtr, cMessage *msg, bool urgent);
    virtual void socketPeerClosed(int connId, void *yourPtr);
    virtual void socketClosed(int connId, void *yourPtr);
    virtual void socketFailure(int connId, void *yourPtr, int code);
    virtual void socketStatusArrived(int connId, void *yourPtr, TCPStatusInfo *status) {delete status;}
    //@}

    // IClassifier
    virtual bool lookupLabel(IPDatagram *ipdatagram, LabelOpVector& outLabel, std::string& outInterface, int& color);

    // INotifiable
    virtual void receiveChangeNotification(int category, cPolymorphic *details);
};

#endif


