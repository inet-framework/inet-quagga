/*
 * Copyright (C) 2003 CTIE, Monash University
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


#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

#include "Ethernet.h"
#include "EtherFrame_m.h"

// Self-message kind values
#define ENDIFG             0
#define ENDRECEPTION       1
#define ENDBACKOFF         2
#define ENDTRANSMISSION    3
#define ENDJAMMING         4
#define ENDPAUSE           5

// MAC transmit state
#define TX_IDLE_STATE      1
#define WAIT_IFG_STATE     2
#define TRANSMITTING_STATE 3
#define JAMMING_STATE      4
#define BACKOFF_STATE      5
#define PAUSE_STATE        6

// MAC receive states
#define RX_IDLE_STATE      1
#define RECEIVING_STATE    2
#define RX_COLLISION_STATE 3


/**
 * Ethernet MAC module.
 */
class EtherMAC : public cSimpleModule
{
    Module_Class_Members(EtherMAC,cSimpleModule,0);

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

  public:
    /**
     * Public function to query output queue size.
     */
    long queueLength() {return outputbuffer.length();}

  private:
    // counter for automatic address generation
    static unsigned int autoAddressCtr;

    // MAC operation modes and parameters
    MACAddress myaddress;
    bool promiscuous;
    bool duplexChannel;     // channel connecting to MAC is full duplex, i.e. like a switch with 2 half-duplex lines
    bool carrierExtension;  // Determines whether carrier extension i.e. when it is Gigabit Ethernet
    bool frameBursting;     // Determines whether frame bursting has been set
    int maxQueueSize;       // max queue length

    // MAC transmission characteristics
    double txrate;          // transmission rate of MAC, bit/s
    double bitTime;         // precalculated as 1/txrate
    double slotTime;        // slot time
    double interFrameGap;   // IFG
    double jamDuration;     // precalculated as 8*JAM_SIGNAL_BYTES*bitTime
    double shortestFrameDuration;  // precalculated from MIN_ETHERNET_FRAME or GIGABIT_MIN_FRAME_WITH_EXT

    // States
    int  transmitState;     // State of the MAC unit transmitting
    int  receiveState;      // State of the MAC unit receiving
    int  framesSentInBurst; // Number of frames send out in current frame burst
    int  bytesSentInBurst;  // Number of bytes transmitted in current frame burst
    int  backoffs;          // Value of backoff for exponential back-off algorithm
    int  numConcurrentTransmissions; // number of colliding frames -- we must receive this many jams
    int  pauseUnitsRequested; // requested pause duration, or zero -- examined at endTx

    // Other variables
    cQueue outputbuffer;    // Output queue
    EtherFrame *frameBeingReceived;
    cMessage *endTxMsg, *endRxMsg, *endIFGMsg, *endBackoffMsg, *endJammingMsg, *endPauseMsg;

    // Statistics:
    simtime_t totalCollisionTime;      // total duration of collisions on channel
    simtime_t totalSuccessfulRxTxTime; // total duration of successful transmissions on channel
    simtime_t channelBusySince;        // needed for computing totalCollisionTime/totalSuccessfulRxTxTime
    unsigned long numFramesSent;
    unsigned long numFramesReceivedOK;
    unsigned long numBytesSent;        // includes Ethernet frame bytes with preamble
    unsigned long numBytesReceivedOK;  // includes Ethernet frame bytes with preamble
    unsigned long numDroppedQueueFull;
    unsigned long numDroppedBitError;  // frames dropped because of bit errors
    unsigned long numDroppedNotForUs;  // frames dropped because destination address didn't match
    unsigned long numFramesPassedToHL; // frames passed to higher layer
    unsigned long numPauseFramesRcvd;  // PAUSE frames received from network
    unsigned long numPauseFramesSent;  // PAUSE frames sent
    unsigned long numCollisions;       // collisions (NOT number of collided frames!) sensed
    unsigned long numBackoffs;         // number of retransmissions
    cOutVector numFramesSentVector;
    cOutVector numFramesReceivedOKVector;
    cOutVector numBytesSentVector;
    cOutVector numBytesReceivedOKVector;
    cOutVector numDroppedQueueFullVector;
    cOutVector numDroppedBitErrorVector;
    cOutVector numDroppedNotForUsVector;
    cOutVector numFramesPassedToHLVector;
    cOutVector numPauseFramesRcvdVector;
    cOutVector numPauseFramesSentVector;
    cOutVector numCollisionsVector;
    cOutVector numBackoffsVector;

    // event handlers
    void processFrameFromUpperLayer(EtherFrame *msg);
    void processMsgFromNetwork(cMessage *msg);
    void handleEndIFGPeriod();
    void handleEndTxPeriod();
    void handleEndRxPeriod();
    void handleEndBackoffPeriod();
    void handleEndJammingPeriod();
    void handleEndPausePeriod();

    // helpers
    void scheduleEndIFGPeriod();
    void scheduleEndTxPeriod(cMessage*);
    void scheduleEndRxPeriod(cMessage*);
    void scheduleEndPausePeriod(int pauseUnits);
    void sendJamSignal();
    void handleRetransmission();
    void printState();
    void beginSendFrames();
    void frameReceptionComplete(EtherFrame *frame);
    void processReceivedDataFrame(EtherFrame *frame);
    void processPauseCommand(int pauseUnits);
    void startFrameTransmission();
};


