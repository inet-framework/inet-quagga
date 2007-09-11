//
// Copyright (C) 2004-2005 Andras Varga
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

#include "TCPTahoe.h"
#include "TCP.h"


Register_Class(TCPTahoe);


TCPTahoe::TCPTahoe() : TCPTahoeRenoFamily(),
  state((TCPTahoeStateVariables *&)TCPAlgorithm::state)
{
}

void TCPTahoe::recalculateSlowStartThreshold()
{
    // set ssthresh to flight size/2, but at least 2 MSS
    // (the formula below practically amounts to ssthresh=cwnd/2 most of the time)
    uint flight_size = Min(state->snd_cwnd, state->snd_wnd);
    state->ssthresh = Max(flight_size/2, 2*state->snd_mss);
    if (ssthreshVector) ssthreshVector->record(state->ssthresh);
}

void TCPTahoe::processRexmitTimer(TCPEventCode& event)
{
    TCPTahoeRenoFamily::processRexmitTimer(event);
    if (event==TCP_E_ABORT)
        return;

    // begin Slow Start (RFC2001)
    recalculateSlowStartThreshold();
    state->snd_cwnd = state->snd_mss;
    if (cwndVector) cwndVector->record(state->snd_cwnd);
    tcpEV << "Begin Slow Start: resetting cwnd to " << state->snd_cwnd
          << ", ssthresh=" << state->ssthresh << "\n";

    // Tahoe retransmits only one segment at the front of the queue
    conn->retransmitOneSegment();
}

void TCPTahoe::receivedDataAck(uint32 firstSeqAcked)
{
    TCPTahoeRenoFamily::receivedDataAck(firstSeqAcked);

    //
    // Perform slow start and congestion avoidance.
    //
    if (state->snd_cwnd < state->ssthresh)
    {
        tcpEV << "cwnd<=ssthresh: Slow Start: increasing cwnd by one segment, to ";

        // perform Slow Start. rfc 2581: "During slow start, a TCP increments cwnd
        // by at most SMSS bytes for each ACK received that acknowledges new data."
        state->snd_cwnd += state->snd_mss;

        // NOTE: we could increase cwnd based on the number of bytes being
        // acknowledged by each arriving ACK, rather than by the number of ACKs
        // that arrive. This is called "Appropriate Byte Counting" (ABC) and is
        // described in rfc 3465 (experimental).
        //
        // int bytesAcked = state->snd_una - firstSeqAcked;
        // state->snd_cwnd += bytesAcked;

        if (cwndVector) cwndVector->record(state->snd_cwnd);

        tcpEV << "cwnd=" << state->snd_cwnd << "\n";
    }
    else
    {
        // perform Congestion Avoidance (rfc 2581)
        int incr = state->snd_mss * state->snd_mss / state->snd_cwnd;
        if (incr==0)
            incr = 1;
        state->snd_cwnd += incr;
        if (cwndVector) cwndVector->record(state->snd_cwnd);

        //
        // NOTE: some implementations use extra additive constant mss/8 here
        // which is known to be incorrect (rfc 2581 p5)
        //
        // NOTE 2: rfc 3465 (experimental) "Appropriate Byte Counting" (ABC)
        // would require maintaining a bytes_acked variable here which we don't do
        //

        tcpEV << "cwnd>ssthresh: Congestion Avoidance: increasing cwnd linearly, to " << state->snd_cwnd << "\n";
    }

    // ack and/or cwnd increase may have freed up some room in the window, try sending
    sendData();
}

void TCPTahoe::receivedDuplicateAck()
{
    TCPTahoeRenoFamily::receivedDuplicateAck();

    if (state->dupacks==3)
    {
        tcpEV << "Tahoe on dupAck=3: perform Fast Retransmit, and enter Slow Start:\n";

        // Fast Retransmission: retransmit missing segment without waiting
        // for the REXMIT timer to expire
        conn->retransmitOneSegment();

        // enter Slow Start
        recalculateSlowStartThreshold();
        state->snd_cwnd = state->snd_mss;
        if (cwndVector) cwndVector->record(state->snd_cwnd);

        tcpEV << "Set cwnd=" << state->snd_cwnd << ", ssthresh=" << state->ssthresh << "\n";

        // FIXME FIXME FIXME FIXME FIXME FIXME FIXME FIXME FIXME FIXME FIXME FIXME
        // double-check if Tahoe really restarts REXMIT timer here
        //
        // restart retransmission timer (with rexmit_count=0), and cancel round-trip time measurement
        // (see p972 "29.4 Fast Retransmit and Fast Recovery Algorithms" of
        // TCP/IP Illustrated, Vol2) -- but that's probably New Reno
        cancelEvent(rexmitTimer);
        startRexmitTimer();
        state->rtseq_sendtime = 0;
    }
}


