/***************************************************************************
                          RTPProfile.h  -  description
                             -------------------
    begin                : Fri Oct 19 2001
    copyright            : (C) 2001 by Matthias Oppitz
    email                : Matthias.Oppitz@gmx.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/** \file RTPProfile.h
 * This file declares the class RTPProfile.
 */

#ifndef __RTPPROFILE_H__
#define __RTPPROFILE_H__

#include <omnetpp.h>

//XXX #include "in_port.h"
#include "tmp/defs.h"

#include "RTPInnerPacket.h"
#include "RTPSSRCGate.h"


/**
 * The class RTPProfile is a module which handles RTPPayloadSender and
 * RTPPayloadReceiver modules. It creates them dynamically on demand.
 * This class offers all functionality for the above tasks, subclasses
 * just need to set variables like profile name, rtcp percentage and
 * preferred port in their initialize() method.
 * The dynamically created sender and receiver modules must
 * have have following class names:
 * RTP<profileName>Payload<payloadType>Sender
 * RTP<profileName>Payload<payloadType>Receiver
 */
class INET_API RTPProfile : public cSimpleModule
{
    public: // FIXME
    //protected:
        /**
         * Initializes variables. Must be overwritten by subclasses.
         */
        virtual void initialize();

        /**
         * Creates and removes payload sender and receiver modules on demand.
         */
        virtual void handleMessage(cMessage *msg);

        /**
         * Handles messages received from the rtp module.
         */
        virtual void handleMessageFromRTP(cMessage *msg);

        /**
         * Handles messages coming from the sender module.
         */
        virtual void handleMessageFromPayloadSender(cMessage *msg);

        /**
         * Handles messages coming from a receiver module.
         */
        virtual void handleMessageFromPayloadReceiver(cMessage *msg);

        /**
         * Initialization message received from rtp module.
         */
        virtual void initializeProfile(RTPInnerPacket *rinp);

        /**
         * This method is called when the application issued the creation
         * of an rtp payload sender module to transmit data.
         * It creates a new sender module and connects it. The profile
         * module informs the rtp module of having finished this task.
         * Then it initializes the newly create sender module with
         * a inititalizeSenderModule message.
         */
        virtual void createSenderModule(RTPInnerPacket *rinp);

        /**
         * When a sender module is no longer needed it can be deleted by the
         * profile module.
         */
        virtual void deleteSenderModule(RTPInnerPacket *rinp);

        /**
         * The profile module forwards sender control messages to the
         * sender module.
         */
        virtual void senderModuleControl(RTPInnerPacket *rinp);

        /**
         * Handles incoming data packets: If there isn't a receiver module for this
         * sender it creates one. The data packet is forwarded to the receiver module
         * after calling processIncomingPacket.
         */
        virtual void dataIn(RTPInnerPacket *rinp);

        /**
         * The sender module returns a senderModuleInitialized message after
         * being initialized. The profile module forwards this message to
         * the rtp module which delivers it to its destination, the rtcp module.
         */
        virtual void senderModuleInitialized(RTPInnerPacket *rinp);

        /**
         * After having received a sender module control message the sender module
         * returns a sender status message to inform the application what it's doing
         * at the moment.
         */
        virtual void senderModuleStatus(RTPInnerPacket *rinp);

        /**
         * Handles outgoing data packets: Calls processOutgoingPacket and forwards
         * the packet to the rtp module.
         */
        virtual void dataOut(RTPInnerPacket *rinp);

        /**
         * Every time a rtp packet is received it it pre-processed by this method to
         * remove profile specific extension which are not handled by the payload
         * receiver module. In this implementation the packet isn't changed.
         * Important: This method works with RTPInnerPacket. So the rtp packet must
         * be decapsulated, changed and encapsulated again.
         */
        virtual void processIncomingPacket(RTPInnerPacket *rinp);

        /**
         * Simular to the procedure for incoming packets, this adds profile specific extensions
         * to outgoing rtp packets.
         */
        virtual void processOutgoingPacket(RTPInnerPacket *rinp);

        /**
         * Finds the gate of the receiver module for rtp data
         * packets from this ssrc.
         */
        virtual RTPSSRCGate *findSSRCGate(u_int32 ssrc);

        /**
         * Creates a new association ssrc/gateId for this ssrc.
         */
        virtual RTPSSRCGate *newSSRCGate(u_int32 ssrc);

        /**
         * The name of this profile. Needed for dynamic creating
         * of sender and receiver modules.
         */
        const char *_profileName;

        /**
         * The maximum number of incoming data streams this profile
         * module can handle. It is set to the gate size of
         * "toPayloadReceiver", "fromPayloadReceiver".
         */
        int _maxReceivers;

        /**
         * Stores information to which gate rtp data packets
         * from a ssrc must be forwarded.
         */
        cArray *_ssrcGates;

        /**
         * The percentage of the available bandwidth to be used for rtcp.
         */
        int _rtcpPercentage;

        /**
         * The rtp port this profile uses if no port is given.
         */
        IN_Port _preferredPort;

        /**
         * The maximum size an RTPPacket can have.
         */
        int _mtu;

        /**
         * If this is set true the RTPProfile automatically sets the output
         * file name for payload receiver modules so the user is not bothered
         * to set them manually during simulation runtime.
         */
        bool _autoOutputFileNames;
};

#endif

