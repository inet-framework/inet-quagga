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

#include "TCPReno.h"
#include "TCP.h"


Register_Class(TCPReno);


TCPReno::TCPReno() : TCPTahoeRenoFamily(),
  state((TCPRenoStateVariables *&)TCPAlgorithm::state)
{
}

void TCPReno::recalculateSlowStartThreshold()
{
    // set ssthresh to flight size/2, but at least 2 MSS
    // (the formula below practically amounts to ssthresh=cwnd/2 most of the time)
    uint flight_size = Min(state->snd_cwnd, state->snd_wnd);
    state->ssthresh = Max(flight_size/2, 2*state->snd_mss);
    if (ssthreshVector) ssthreshVector->record(state->ssthresh);
}

void TCPReno::processRexmitTimer(TCPEventCode& event)
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

    // Reno retransmits all data (unlike Tahoe which transmits only the segment)
    conn->retransmitData();
}

void TCPReno::receivedDataAck(uint32 firstSeqAcked)
{
    TCPTahoeRenoFamily::receivedDataAck(firstSeqAcked);

    if (state->dupacks>=3)
    {
        //
        // Perform Fast Recovery: set cwnd to ssthresh (deflating the window).
        //
        tcpEV << "Fast Recovery: setting cwnd to ssthresh=" << state->ssthresh << "\n";
        state->snd_cwnd = state->ssthresh;
        if (cwndVector) cwndVector->record(state->snd_cwnd);
    }
    else
    {
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
            // described in rfc 3465. This rfc is experimental and probably not
            // implemented in real-life TCPs, hence it's commented out. Also, the ABC
            // rfc would require other modifications as well in addition to the
            // two lines below.
            //
            // int bytesAcked = state->snd_una - firstSeqAcked;
            // state->snd_cwnd += bytesAcked*state->snd_mss;

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
    }

    // ack and/or cwnd increase may have freed up some room in the window, try sending
    sendData();
}

void TCPReno::receivedDuplicateAck()
{
    TCPTahoeRenoFamily::receivedDuplicateAck();

    if (state->dupacks==3)
    {
        tcpEV << "Reno on dupAck=3: perform Fast Retransmit, and enter Fast Recovery:";

        // Fast Retransmission: retransmit missing segment without waiting
        // for the REXMIT timer to expire
        conn->retransmitOneSegment();

        // enter slow start
        // "set cwnd to ssthresh plus 3 times the segment size." (rfc 2001)
        recalculateSlowStartThreshold();
        state->snd_cwnd = state->ssthresh + 3*state->snd_mss;  // 20051129 (1)
        if (cwndVector) cwndVector->record(state->snd_cwnd);

        tcpEV << "set cwnd=" << state->snd_cwnd << ", ssthresh=" << state->ssthresh << "\n";

        // restart retransmission timer (with rexmit_count=0), and cancel round-trip time measurement
        // (see p972 "29.4 Fast Retransmit and Fast Recovery Algorithms" of
        // TCP/IP Illustrated, Vol2) -- but that's probably New Reno
        cancelEvent(rexmitTimer);
        startRexmitTimer();
        state->rtseq_sendtime = 0;
    }
    else if (state->dupacks > 3)
    {
        //
        // Reno: For each additional duplicate ACK received, increment cwnd by MSS.
        // This artificially inflates the congestion window in order to reflect the
        // additional segment that has left the network
        //
        state->snd_cwnd += state->snd_mss;
        tcpEV << "Reno on dupAck>3: Fast Recovery: inflating cwnd by MSS, new cwnd=" << state->snd_cwnd << "\n";
        if (cwndVector) cwndVector->record(state->snd_cwnd);

        // cwnd increased, try sending
        sendData();  // 20051129 (2)
    }
}


