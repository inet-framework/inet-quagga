//
// Copyright (C) 2006 Andras Varga
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


#include "Ieee80211MgmtBase.h"
#include "Ieee802Ctrl_m.h"


static std::ostream& operator<< (std::ostream& out, cMessage *msg)
{
    out << "(" << msg->className() << ")" << msg->fullName();
    return out;
}

void Ieee80211MgmtBase::initialize(int stage)
{
    if (stage==0)
    {
        PassiveQueueBase::initialize();

        dataQueue.setName("wlanDataQueue");
        mgmtQueue.setName("wlanMgmtQueue");
        dataQueueLenVec.setName("queue length");
        dataQueueDropVec.setName("queue drop count");

        numDataFramesReceived = 0;
        numMgmtFramesReceived = 0;
        numMgmtFramesDropped = 0;
        WATCH(numDataFramesReceived);
        WATCH(numMgmtFramesReceived);
        WATCH(numMgmtFramesDropped);

        // configuration
        frameCapacity = par("frameCapacity");


    }
    else if (stage==1)
    {
        // obtain our address from MAC
        cModule *mac = parentModule()->submodule("mac");
        if (!mac)
            error("MAC module not found; it is expected to be next to this submodule and called 'mac'");
        myAddress.setAddress(mac->par("address").stringValue());
    }
}


void Ieee80211MgmtBase::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        // process timers
        EV << "Timer expired: " << msg << "\n";
        handleTimer(msg);
    }
    else if (msg->arrivedOn("macIn"))
    {
        // process incoming frame
        EV << "Frame arrived from MAC: " << msg << "\n";
        Ieee80211DataOrMgmtFrame *frame = check_and_cast<Ieee80211DataOrMgmtFrame *>(msg);
        processFrame(frame);
    }
    else if (msg->arrivedOn("agentIn"))
    {
        // process command from agent
        EV << "Command arrived from agent: " << msg << "\n";
        int msgkind = msg->kind();
        cPolymorphic *ctrl = msg->removeControlInfo();
        delete msg;

        handleCommand(msgkind, ctrl);
    }
    else
    {
        // packet from upper layers, to be sent out
        EV << "Packet arrived from upper layers: " << msg << "\n";
        if (msg->byteLength() > 2312)
            error("message from higher layer (%s)%s is too long for 802.11b, %d bytes (fragmentation is not supported yet)",
                  msg->className(), msg->name(), msg->byteLength());

        handleUpperMessage(msg);
    }
}

void Ieee80211MgmtBase::sendOrEnqueue(cMessage *frame)
{
    PassiveQueueBase::handleMessage(frame);
}

bool Ieee80211MgmtBase::enqueue(cMessage *msg)
{
    ASSERT(dynamic_cast<Ieee80211DataOrMgmtFrame *>(msg)!=NULL);
    bool isDataFrame = dynamic_cast<Ieee80211DataFrame *>(msg)!=NULL;

    if (!isDataFrame)
    {
        // management frames are inserted into mgmtQueue
        mgmtQueue.insert(msg);
        return false;
    }
    else if (frameCapacity && dataQueue.length() >= frameCapacity)
    {
        EV << "Queue full, dropping packet.\n";
        delete msg;
        dataQueueDropVec.record(1);
        return true;
    }
    else
    {
        dataQueue.insert(msg);
        dataQueueLenVec.record(dataQueue.length());
        return false;
    }
}

cMessage *Ieee80211MgmtBase::dequeue()
{
    // management frames have priority
    if (!mgmtQueue.empty())
        return (cMessage *)mgmtQueue.pop();

    // return a data frame if we have one
    if (dataQueue.empty())
        return NULL;

    cMessage *pk = (cMessage *)dataQueue.pop();

    // statistics
    dataQueueLenVec.record(dataQueue.length());
    return pk;
}

void Ieee80211MgmtBase::sendOut(cMessage *msg)
{
    send(msg, "macOut");
}

void Ieee80211MgmtBase::dropManagementFrame(Ieee80211ManagementFrame *frame)
{
    EV << "ignoring management frame: " << (cMessage *)frame << "\n";
    delete frame;
    numMgmtFramesDropped++;
}

cMessage *Ieee80211MgmtBase::decapsulate(Ieee80211DataFrame *frame)
{
    cMessage *payload = frame->decapsulate();

    Ieee802Ctrl *ctrl = new Ieee802Ctrl();
    ctrl->setSrc(frame->getAddress3());
    ctrl->setDest(frame->getReceiverAddress());
    payload->setControlInfo(ctrl);

    delete frame;
    return payload;
}

void Ieee80211MgmtBase::sendUp(cMessage *msg)
{
    send(msg, "uppergateOut");
}

void Ieee80211MgmtBase::processFrame(Ieee80211DataOrMgmtFrame *frame)
{
    switch(frame->getType())
    {
      case ST_DATA:
        numDataFramesReceived++;
        handleDataFrame(check_and_cast<Ieee80211DataFrame *>(frame));
        break;
      case ST_AUTHENTICATION:
        numMgmtFramesReceived++;
        handleAuthenticationFrame(check_and_cast<Ieee80211AuthenticationFrame *>(frame));
        break;
      case ST_DEAUTHENTICATION:
        numMgmtFramesReceived++;
        handleDeauthenticationFrame(check_and_cast<Ieee80211DeauthenticationFrame *>(frame));
        break;
      case ST_ASSOCIATIONREQUEST:
        numMgmtFramesReceived++;
        handleAssociationRequestFrame(check_and_cast<Ieee80211AssociationRequestFrame *>(frame));
        break;
      case ST_ASSOCIATIONRESPONSE:
        numMgmtFramesReceived++;
        handleAssociationResponseFrame(check_and_cast<Ieee80211AssociationResponseFrame *>(frame));
        break;
      case ST_REASSOCIATIONREQUEST:
        numMgmtFramesReceived++;
        handleReassociationRequestFrame(check_and_cast<Ieee80211ReassociationRequestFrame *>(frame));
        break;
      case ST_REASSOCIATIONRESPONSE:
        numMgmtFramesReceived++;
        handleReassociationResponseFrame(check_and_cast<Ieee80211ReassociationResponseFrame *>(frame)); break;
      case ST_DISASSOCIATION:
        numMgmtFramesReceived++;
        handleDisassociationFrame(check_and_cast<Ieee80211DisassociationFrame *>(frame));
        break;
      case ST_BEACON:
        numMgmtFramesReceived++;
        handleBeaconFrame(check_and_cast<Ieee80211BeaconFrame *>(frame));
        break;
      case ST_PROBEREQUEST:
        numMgmtFramesReceived++;
        handleProbeRequestFrame(check_and_cast<Ieee80211ProbeRequestFrame *>(frame));
        break;
      case ST_PROBERESPONSE:
        numMgmtFramesReceived++;
        handleProbeResponseFrame(check_and_cast<Ieee80211ProbeResponseFrame *>(frame));
        break;
      default:
        error("unexpected frame type (%s)%s", frame->className(), frame->name());
    }
}

