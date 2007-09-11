//
// (C) 2005 Vojtech Janota, Andras Varga
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

#include <omnetpp.h>
#include <algorithm>

#include "LinkStateRouting.h"
#include "IPControlInfo.h"
#include "IPv4InterfaceData.h"
#include "NotifierConsts.h"
#include "RoutingTableAccess.h"
#include "InterfaceTableAccess.h"
#include "NotificationBoard.h"
#include "TED.h"
#include "TEDAccess.h"

Define_Module(LinkStateRouting);

LinkStateRouting::LinkStateRouting()
{
    announceMsg = NULL;
}

LinkStateRouting::~LinkStateRouting()
{
    cancelAndDelete(announceMsg);
}

void LinkStateRouting::initialize(int stage)
{
    // we have to wait until routerId gets assigned in stage 3
    if (stage==4)
    {
        tedmod = TEDAccess().get();

        RoutingTable *rt = RoutingTableAccess().get();
        routerId = rt->routerId();

        // listen for TED modifications
        NotificationBoard *nb = NotificationBoardAccess().get();
        nb->subscribe(this, NF_TED_CHANGED);

        // peers are given as interface names in the "peers" module parameter;
        // store corresponding interface addresses in peerIfAddrs[]
        cStringTokenizer tokenizer(par("peers"));
        InterfaceTable *ift = InterfaceTableAccess().get();
        const char *token;
        while ((token = tokenizer.nextToken())!=NULL)
        {
            ASSERT(ift->interfaceByName(token));
            peerIfAddrs.push_back(ift->interfaceByName(token)->ipv4()->inetAddress());
        }

        // schedule start of flooding link state info
        announceMsg = new cMessage("announce");
        scheduleAt(simTime() + exponential(0.01), announceMsg);
    }
}

void LinkStateRouting::handleMessage(cMessage * msg)
{
    if (msg == announceMsg)
    {
        delete announceMsg;
        announceMsg = NULL;
        sendToPeers(tedmod->ted, true, IPAddress());
    }
    else if (!strcmp(msg->arrivalGate()->name(), "from_ip"))
    {
        EV << "Processing message from IP: " << msg << endl;
        IPControlInfo *controlInfo = check_and_cast<IPControlInfo *>(msg->controlInfo());
        IPAddress sender = controlInfo->srcAddr();
        processLINK_STATE_MESSAGE(check_and_cast<LinkStateMsg*>(msg), sender);
    }
    else
        ASSERT(false);
}

void LinkStateRouting::receiveChangeNotification(int category, cPolymorphic *details)
{
    Enter_Method_Silent();
    printNotificationBanner(category, details);

    ASSERT(category == NF_TED_CHANGED);

    EV << "TED changed\n";

    TEDChangeInfo *d = check_and_cast<TEDChangeInfo *>(details);

    unsigned int k = d->getTedLinkIndicesArraySize();

    ASSERT(k > 0);

    // build linkinfo list
    std::vector<TELinkStateInfo> links;
    for (unsigned int i = 0; i < k; i++)
    {
        unsigned int index = d->getTedLinkIndices(i);

        tedmod->updateTimestamp(&tedmod->ted[index]);
        links.push_back(tedmod->ted[index]);
    }

    sendToPeers(links, false, IPAddress());
}

void LinkStateRouting::processLINK_STATE_MESSAGE(LinkStateMsg* msg, IPAddress sender)
{
    EV << "received LINK_STATE message from " << sender << endl;

    TELinkStateInfoVector forward;

    unsigned int n = msg->getLinkInfoArraySize();

    bool change = false; // in topology

    // loop through every link in the message
    for (unsigned int i = 0; i < n; i++)
    {
        const TELinkStateInfo& link = msg->getLinkInfo(i);

        TELinkStateInfo *match;

        // process link if we haven't seen this already and timestamp is newer
        if(tedmod->checkLinkValidity(link, match))
        {
            ASSERT(link.sourceId == link.advrouter.getInt());

            EV << "new information found" << endl;

            if(!match)
            {
                // and we have no info on this link so far, store it as it is
                tedmod->ted.push_back(link);
                change = true;
            }
            else
            {
                // copy over the information from it
                if(match->state != link.state)
                {
                    match->state = link.state;
                    change = true;
                }
                match->messageId = link.messageId;
                match->sourceId = link.sourceId;
                match->timestamp = link.timestamp;
                for(int i = 0; i < 8; i++)
                    match->UnResvBandwidth[i] = link.UnResvBandwidth[i];
                match->MaxBandwidth = link.MaxBandwidth;
                match->metric = link.metric;
            }

            forward.push_back(link);
        }
    }

    if(change)
        tedmod->rebuildRoutingTable();

    if(msg->getRequest())
    {
        sendToPeer(sender, tedmod->ted, false);
    }

    if(forward.size() > 0)
    {
        sendToPeers(forward, false, sender);
    }

    delete msg;
}

void LinkStateRouting::sendToPeers(const std::vector<TELinkStateInfo>& list, bool req, IPAddress exceptPeer)
{
    EV << "sending LINK_STATE message to peers" << endl;

    // send "list" to every peer (linkid in our ted[] entries???) in a LinkStateMsg
    for (unsigned int i = 0; i < tedmod->ted.size(); i++)
    {
        if(tedmod->ted[i].advrouter != routerId)
            continue;

        if(tedmod->ted[i].linkid == exceptPeer)
            continue;

        if(!tedmod->ted[i].state)
            continue;

        if(find(peerIfAddrs.begin(), peerIfAddrs.end(), tedmod->ted[i].local) == peerIfAddrs.end())
            continue;

        // send a copy
        sendToPeer(tedmod->ted[i].linkid, list, req);
    }
}

void LinkStateRouting::sendToPeer(IPAddress peer, const std::vector<TELinkStateInfo> & list, bool req)
{
    EV << "sending LINK_STATE message to " << peer << endl;

    LinkStateMsg *out = new LinkStateMsg("link state");

    out->setLinkInfoArraySize(list.size());
    for (unsigned int j = 0; j < list.size(); j++)
        out->setLinkInfo(j, list[j]);

    out->setRequest(req);

    sendToIP(out, peer);
}

void LinkStateRouting::sendToIP(LinkStateMsg *msg, IPAddress destAddr)
{
    // attach control info to packet
    IPControlInfo *controlInfo = new IPControlInfo();
    controlInfo->setDestAddr(destAddr);
    controlInfo->setSrcAddr(routerId);
    controlInfo->setProtocol(IP_PROT_OSPF);
    msg->setControlInfo(controlInfo);

    int length = msg->getLinkInfoArraySize() * 72;
    msg->setByteLength(length);

    msg->addPar("color") = TED_TRAFFIC;

    send(msg, "to_ip");
}

