//
// Copyright (C) 2004 Andras Varga
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


#include <string.h>
#include "TCP.h"
#include "TCPConnection.h"
#include "TCPSegment.h"
#include "TCPCommand_m.h"
#include "IPControlInfo.h"
#include "IPv6ControlInfo.h"
#include "TCPSendQueue.h"
#include "TCPReceiveQueue.h"
#include "TCPAlgorithm.h"


//
// helper functions
//

const char *TCPConnection::stateName(int state)
{
#define CASE(x) case x: s=#x+6; break
    const char *s = "unknown";
    switch (state)
    {
        CASE(TCP_S_INIT);
        CASE(TCP_S_CLOSED);
        CASE(TCP_S_LISTEN);
        CASE(TCP_S_SYN_SENT);
        CASE(TCP_S_SYN_RCVD);
        CASE(TCP_S_ESTABLISHED);
        CASE(TCP_S_CLOSE_WAIT);
        CASE(TCP_S_LAST_ACK);
        CASE(TCP_S_FIN_WAIT_1);
        CASE(TCP_S_FIN_WAIT_2);
        CASE(TCP_S_CLOSING);
        CASE(TCP_S_TIME_WAIT);
    }
    return s;
#undef CASE
}

const char *TCPConnection::eventName(int event)
{
#define CASE(x) case x: s=#x+6; break
    const char *s = "unknown";
    switch (event)
    {
        CASE(TCP_E_IGNORE);
        CASE(TCP_E_OPEN_ACTIVE);
        CASE(TCP_E_OPEN_PASSIVE);
        CASE(TCP_E_SEND);
        CASE(TCP_E_CLOSE);
        CASE(TCP_E_ABORT);
        CASE(TCP_E_STATUS);
        CASE(TCP_E_RCV_DATA);
        CASE(TCP_E_RCV_ACK);
        CASE(TCP_E_RCV_SYN);
        CASE(TCP_E_RCV_SYN_ACK);
        CASE(TCP_E_RCV_FIN);
        CASE(TCP_E_RCV_FIN_ACK);
        CASE(TCP_E_RCV_RST);
        CASE(TCP_E_RCV_UNEXP_SYN);
        CASE(TCP_E_TIMEOUT_2MSL);
        CASE(TCP_E_TIMEOUT_CONN_ESTAB);
        CASE(TCP_E_TIMEOUT_FIN_WAIT_2);
    }
    return s;
#undef CASE
}

const char *TCPConnection::indicationName(int code)
{
#define CASE(x) case x: s=#x+6; break
    const char *s = "unknown";
    switch (code)
    {
        CASE(TCP_I_DATA);
        CASE(TCP_I_URGENT_DATA);
        CASE(TCP_I_ESTABLISHED);
        CASE(TCP_I_PEER_CLOSED);
        CASE(TCP_I_CLOSED);
        CASE(TCP_I_CONNECTION_REFUSED);
        CASE(TCP_I_CONNECTION_RESET);
        CASE(TCP_I_TIMED_OUT);
        CASE(TCP_I_STATUS);
    }
    return s;
#undef CASE
}

void TCPConnection::printConnBrief()
{
    tcpEV << "Connection ";
    tcpEV << localAddr << ":" << localPort << " to " << remoteAddr << ":" << remotePort;
    tcpEV << "  on app[" << appGateIndex << "],connId=" << connId;
    tcpEV << "  in " << stateName(fsm.state());
    tcpEV << "  (ptr=0x" << this << ")\n";
}

void TCPConnection::printSegmentBrief(TCPSegment *tcpseg)
{
    tcpEV << "." << tcpseg->srcPort() << " > ";
    tcpEV << "." << tcpseg->destPort() << ": ";

    if (tcpseg->synBit())  tcpEV << (tcpseg->ackBit() ? "SYN+ACK " : "SYN ");
    if (tcpseg->finBit())  tcpEV << "FIN(+ACK) ";
    if (tcpseg->rstBit())  tcpEV << (tcpseg->ackBit() ? "RST+ACK " : "RST ");
    if (tcpseg->pshBit())  tcpEV << "PSH ";

    if (tcpseg->payloadLength()>0 || tcpseg->synBit())
    {
        tcpEV << tcpseg->sequenceNo() << ":" << tcpseg->sequenceNo()+tcpseg->payloadLength();
        tcpEV << "(" << tcpseg->payloadLength() << ") ";
    }
    if (tcpseg->ackBit())  tcpEV << "ack " << tcpseg->ackNo() << " ";
    tcpEV << "win " << tcpseg->window() << "\n";
    if (tcpseg->urgBit())  tcpEV << "urg " << tcpseg->urgentPointer() << " ";
}

TCPConnection *TCPConnection::cloneListeningConnection()
{
    TCPConnection *conn = new TCPConnection(tcpMain,appGateIndex,connId);

    // following code to be kept consistent with initConnection()
    const char *sendQueueClass = sendQueue->className();
    conn->sendQueue = check_and_cast<TCPSendQueue *>(createOne(sendQueueClass));

    const char *receiveQueueClass = receiveQueue->className();
    conn->receiveQueue = check_and_cast<TCPReceiveQueue *>(createOne(receiveQueueClass));

    const char *tcpAlgorithmClass = tcpAlgorithm->className();
    conn->tcpAlgorithm = check_and_cast<TCPAlgorithm *>(createOne(tcpAlgorithmClass));
    conn->tcpAlgorithm->setConnection(conn);

    conn->state = conn->tcpAlgorithm->stateVariables();
    configureStateVariables();
    conn->tcpAlgorithm->initialize();

    // put it into LISTEN, with our localAddr/localPort
    conn->state->active = false;
    conn->state->fork = true;
    conn->localAddr = localAddr;
    conn->localPort = localPort;
    FSM_Goto(conn->fsm, TCP_S_LISTEN);

    return conn;
}

void TCPConnection::sendToIP(TCPSegment *tcpseg)
{
    // record seq (only if we do send data) and ackno
    if (sndNxtVector && tcpseg->payloadLength()!=0)
        sndNxtVector->record(tcpseg->sequenceNo());
    if (sndAckVector) sndAckVector->record(tcpseg->ackNo());

    // final touches on the segment before sending
    tcpseg->setSrcPort(localPort);
    tcpseg->setDestPort(remotePort);
    tcpseg->setByteLength(TCP_HEADER_OCTETS+tcpseg->payloadLength());
    // TBD account for Options (once they get implemented)

    tcpEV << "Sending: ";
    printSegmentBrief(tcpseg);

    // TBD reuse next function for sending

    if (!remoteAddr.isIPv6())
    {
        // send over IPv4
        IPControlInfo *controlInfo = new IPControlInfo();
        controlInfo->setProtocol(IP_PROT_TCP);
        controlInfo->setSrcAddr(localAddr.get4());
        controlInfo->setDestAddr(remoteAddr.get4());
        tcpseg->setControlInfo(controlInfo);

        tcpMain->send(tcpseg,"to_ip");
    }
    else
    {
        // send over IPv6
        IPv6ControlInfo *controlInfo = new IPv6ControlInfo();
        controlInfo->setProtocol(IP_PROT_TCP);
        controlInfo->setSrcAddr(localAddr.get6());
        controlInfo->setDestAddr(remoteAddr.get6());
        tcpseg->setControlInfo(controlInfo);

        tcpMain->send(tcpseg,"to_ipv6");
    }
}

void TCPConnection::sendToIP(TCPSegment *tcpseg, IPvXAddress src, IPvXAddress dest)
{
    tcpEV << "Sending: ";
    printSegmentBrief(tcpseg);

    if (!dest.isIPv6())
    {
        // send over IPv4
        IPControlInfo *controlInfo = new IPControlInfo();
        controlInfo->setProtocol(IP_PROT_TCP);
        controlInfo->setSrcAddr(src.get4());
        controlInfo->setDestAddr(dest.get4());
        tcpseg->setControlInfo(controlInfo);

        check_and_cast<TCP *>(simulation.contextModule())->send(tcpseg,"to_ip");
    }
    else
    {
        // send over IPv6
        IPv6ControlInfo *controlInfo = new IPv6ControlInfo();
        controlInfo->setProtocol(IP_PROT_TCP);
        controlInfo->setSrcAddr(src.get6());
        controlInfo->setDestAddr(dest.get6());
        tcpseg->setControlInfo(controlInfo);

        check_and_cast<TCP *>(simulation.contextModule())->send(tcpseg,"to_ipv6");
    }
}

void TCPConnection::signalConnectionTimeout()
{
    sendIndicationToApp(TCP_I_TIMED_OUT);
}

void TCPConnection::sendIndicationToApp(int code)
{
    tcpEV << "Notifying app: " << indicationName(code) << "\n";
    cMessage *msg = new cMessage(indicationName(code));
    msg->setKind(code);
    TCPCommand *ind = new TCPCommand();
    ind->setConnId(connId);
    msg->setControlInfo(ind);
    tcpMain->send(msg, "to_appl", appGateIndex);
}

void TCPConnection::sendEstabIndicationToApp()
{
    tcpEV << "Notifying app: " << indicationName(TCP_I_ESTABLISHED) << "\n";
    cMessage *msg = new cMessage(indicationName(TCP_I_ESTABLISHED));
    msg->setKind(TCP_I_ESTABLISHED);

    TCPConnectInfo *ind = new TCPConnectInfo();
    ind->setConnId(connId);
    ind->setLocalAddr(localAddr);
    ind->setRemoteAddr(remoteAddr);
    ind->setLocalPort(localPort);
    ind->setRemotePort(remotePort);

    msg->setControlInfo(ind);
    tcpMain->send(msg, "to_appl", appGateIndex);
}

void TCPConnection::sendToApp(cMessage *msg)
{
    tcpMain->send(msg, "to_appl", appGateIndex);
}

void TCPConnection::initConnection(TCPOpenCommand *openCmd)
{
    // create send/receive queues
    const char *sendQueueClass = openCmd->sendQueueClass();
    if (!sendQueueClass || !sendQueueClass[0])
        sendQueueClass = tcpMain->par("sendQueueClass");
    sendQueue = check_and_cast<TCPSendQueue *>(createOne(sendQueueClass));

    const char *receiveQueueClass = openCmd->receiveQueueClass();
    if (!receiveQueueClass || !receiveQueueClass[0])
        receiveQueueClass = tcpMain->par("receiveQueueClass");
    receiveQueue = check_and_cast<TCPReceiveQueue *>(createOne(receiveQueueClass));

    // create algorithm
    const char *tcpAlgorithmClass = openCmd->tcpAlgorithmClass();
    if (!tcpAlgorithmClass || !tcpAlgorithmClass[0])
        tcpAlgorithmClass = tcpMain->par("tcpAlgorithmClass");
    tcpAlgorithm = check_and_cast<TCPAlgorithm *>(createOne(tcpAlgorithmClass));
    tcpAlgorithm->setConnection(this);

    // create state block
    state = tcpAlgorithm->stateVariables();
    configureStateVariables();
    tcpAlgorithm->initialize();
}

void TCPConnection::configureStateVariables()
{
    state->snd_mss = tcpMain->par("mss").longValue(); // TODO: mss=-1 should mean autodetect
    state->rcv_wnd = tcpMain->par("advertisedWindow").longValue();
}

void TCPConnection::selectInitialSeqNum()
{
    // set the initial send sequence number
    state->iss = (unsigned long)SIMTIME_DBL(fmod(tcpMain->simTime()*250000.0, 1.0+(double)(unsigned)0xffffffffUL)) & 0xffffffffUL;

    state->snd_una = state->snd_nxt = state->snd_max = state->iss;

    sendQueue->init(state->iss+1); // +1 is for SYN
}

bool TCPConnection::isSegmentAcceptable(TCPSegment *tcpseg)
{
    // segment entirely falls in receive window
    //FIXME probably not this simple, see old code segAccept() below...
    return seqGE(tcpseg->sequenceNo(),state->rcv_nxt) &&
           seqLE(tcpseg->sequenceNo()+tcpseg->payloadLength(),state->rcv_nxt+state->rcv_wnd);
}

void TCPConnection::sendSyn()
{
    if (remoteAddr.isUnspecified() || remotePort==-1)
        opp_error("Error processing command OPEN_ACTIVE: foreign socket unspecified");
    if (localPort==-1)
        opp_error("Error processing command OPEN_ACTIVE: local port unspecified");

    // create segment
    TCPSegment *tcpseg = new TCPSegment("SYN");
    tcpseg->setSequenceNo(state->iss);
    tcpseg->setSynBit(true);
    tcpseg->setWindow(state->rcv_wnd);

    state->snd_max = state->snd_nxt = state->iss+1;

    // send it
    sendToIP(tcpseg);
}

void TCPConnection::sendSynAck()
{
    // create segment
    TCPSegment *tcpseg = new TCPSegment("SYN+ACK");
    tcpseg->setSequenceNo(state->iss);
    tcpseg->setAckNo(state->rcv_nxt);
    tcpseg->setSynBit(true);
    tcpseg->setAckBit(true);
    tcpseg->setWindow(state->rcv_wnd);

    state->snd_max = state->snd_nxt = state->iss+1;

    // send it
    sendToIP(tcpseg);
}

void TCPConnection::sendRst(uint32 seqNo)
{
    sendRst(seqNo, localAddr, remoteAddr, localPort, remotePort);
}

void TCPConnection::sendRst(uint32 seq, IPvXAddress src, IPvXAddress dest, int srcPort, int destPort)
{
    TCPSegment *tcpseg = new TCPSegment("RST");

    tcpseg->setSrcPort(srcPort);
    tcpseg->setDestPort(destPort);

    tcpseg->setRstBit(true);
    tcpseg->setSequenceNo(seq);

    // send it
    sendToIP(tcpseg, src, dest);
}

void TCPConnection::sendRstAck(uint32 seq, uint32 ack, IPvXAddress src, IPvXAddress dest, int srcPort, int destPort)
{
    TCPSegment *tcpseg = new TCPSegment("RST+ACK");

    tcpseg->setSrcPort(srcPort);
    tcpseg->setDestPort(destPort);

    tcpseg->setRstBit(true);
    tcpseg->setAckBit(true);
    tcpseg->setSequenceNo(seq);
    tcpseg->setAckNo(ack);

    // send it
    sendToIP(tcpseg, src, dest);
}

void TCPConnection::sendAck()
{
    TCPSegment *tcpseg = new TCPSegment("ACK");

    tcpseg->setAckBit(true);
    tcpseg->setSequenceNo(state->snd_nxt);
    tcpseg->setAckNo(state->rcv_nxt);
    tcpseg->setWindow(state->rcv_wnd);

    // send it
    sendToIP(tcpseg);

    // notify
    tcpAlgorithm->ackSent();
}

void TCPConnection::sendFin()
{
    TCPSegment *tcpseg = new TCPSegment("FIN");

    // Note: ACK bit *must* be set for both FIN and FIN+ACK. What makes
    // the difference for FIN+ACK is that its ackNo acks the remote TCP's FIN.
    tcpseg->setFinBit(true);
    tcpseg->setAckBit(true);
    tcpseg->setAckNo(state->rcv_nxt);
    tcpseg->setSequenceNo(state->snd_nxt);
    tcpseg->setWindow(state->rcv_wnd);

    // send it
    sendToIP(tcpseg);

    // notify
    tcpAlgorithm->ackSent();
}

void TCPConnection::sendSegment(int bytes)
{
    // send one segment of 'bytes' bytes from snd_nxt, and advance snd_nxt
    TCPSegment *tcpseg = sendQueue->createSegmentWithBytes(state->snd_nxt, bytes);
    tcpseg->setAckNo(state->rcv_nxt);
    tcpseg->setAckBit(true);
    tcpseg->setWindow(state->rcv_wnd);
    // TBD when to set PSH bit?
    // TBD set URG bit if needed
    ASSERT(bytes==tcpseg->payloadLength());

    state->snd_nxt += bytes;

    if (state->send_fin && state->snd_nxt==state->snd_fin_seq)
    {
        tcpEV << "Setting FIN on segment\n";
        tcpseg->setFinBit(true);
        state->snd_nxt = state->snd_fin_seq+1;
    }

    sendToIP(tcpseg);
}

bool TCPConnection::sendData(bool fullSegmentsOnly, int congestionWindow)
{
    // we'll start sending from snd_max
    state->snd_nxt = state->snd_max;

    // check how many bytes we have
    ulong buffered = sendQueue->bytesAvailable(state->snd_nxt);
    if (buffered==0)
        return false;

    // maxWindow is smaller of (snd_wnd, congestionWindow)
    long maxWindow = state->snd_wnd;
    if (congestionWindow>=0 && maxWindow > congestionWindow)
        maxWindow = congestionWindow;

    // effectiveWindow: number of bytes we're allowed to send now
    long effectiveWin = maxWindow - (state->snd_nxt - state->snd_una);
    if (effectiveWin <= 0)
    {
        tcpEV << "Effective window is zero (advertised window " << state->snd_wnd <<
                 ", congestion window " << congestionWindow << "), cannot send.\n";
        return false;
    }

    ulong bytesToSend = effectiveWin;

    if (bytesToSend > buffered)
        bytesToSend = buffered;

    if (fullSegmentsOnly && bytesToSend < state->snd_mss)
    {
        tcpEV << "Cannot send, not enough data for a full segment (MSS=" << state->snd_mss
              << ", in buffer " << buffered << ")\n";
        return false;
    }

    // start sending 'bytesToSend' bytes
    tcpEV << "Will send " << bytesToSend << " bytes (effectiveWindow " << effectiveWin
          << ", in buffer " << buffered << " bytes)\n";

    uint32 old_snd_nxt = state->snd_nxt;
    ASSERT(bytesToSend>0);

#ifdef TCP_SENDFRAGMENTS  /* normally undefined */
    // make agressive use of the window until the last byte
    while (bytesToSend>0)
    {
        ulong bytes = Min(bytesToSend, state->snd_mss);
        sendSegment(bytes);
        bytesToSend -= bytes;
    }
#else
    // send <MSS segments only if it's the only segment we can send now
    // FIXME this should probably obey Nagle's alg -- to be checked
    if (bytesToSend <= state->snd_mss)
    {
        sendSegment(bytesToSend);
    }
    else
    {
        // send whole segments only
        while (bytesToSend>=state->snd_mss)
        {
            sendSegment(state->snd_mss);
            bytesToSend -= state->snd_mss;
        }
        if (bytesToSend>0)
           tcpEV << bytesToSend << " bytes of space left in effectiveWindow\n";
    }
#endif

    // remember highest seq sent (snd_nxt may be set back on retransmission,
    // but we'll need snd_max to check validity of ACKs -- they must ack
    // something we really sent)
    state->snd_max = state->snd_nxt;
    if (unackedVector) unackedVector->record(state->snd_max - state->snd_una);

    // notify (once is enough)
    tcpAlgorithm->ackSent();
    tcpAlgorithm->dataSent(old_snd_nxt);

    return true;
}

bool TCPConnection::sendProbe()
{
    // we'll start sending from snd_max
    state->snd_nxt = state->snd_max;

    // check we have 1 byte to send
    if (sendQueue->bytesAvailable(state->snd_nxt)==0)
    {
        tcpEV << "Cannot send probe because send buffer is empty\n";
        return false;
    }

    uint32 old_snd_nxt = state->snd_nxt;

    tcpEV << "Sending 1 byte as probe, with seq=" << state->snd_nxt << "\n";
    sendSegment(1);

    // remember highest seq sent (snd_nxt may be set back on retransmission,
    // but we'll need snd_max to check validity of ACKs -- they must ack
    // something we really sent)
    state->snd_max = state->snd_nxt;
    if (unackedVector) unackedVector->record(state->snd_max - state->snd_una);

    // notify
    tcpAlgorithm->ackSent();
    tcpAlgorithm->dataSent(old_snd_nxt);

    return true;
}

void TCPConnection::retransmitOneSegment()
{
    // retransmit one segment at snd_una, and set snd_nxt accordingly
    state->snd_nxt = state->snd_una;

    ulong bytes = Min(state->snd_mss, state->snd_max - state->snd_nxt);
    ASSERT(bytes!=0);

    sendSegment(bytes);

    // notify
    tcpAlgorithm->ackSent();
}

void TCPConnection::retransmitData()
{
    // retransmit everything from snd_una
    state->snd_nxt = state->snd_una;

    ulong bytesToSend = state->snd_max - state->snd_nxt;
    ASSERT(bytesToSend!=0);

    while (bytesToSend>0)
    {
        ulong bytes = Min(bytesToSend, state->snd_mss);
        sendSegment(bytes);
        bytesToSend -= bytes;
    }
}


