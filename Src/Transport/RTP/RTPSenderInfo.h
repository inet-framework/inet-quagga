/***************************************************************************
                          RTPSenderInfo.h  -  description
                             -------------------
    begin                : Wed Dec 5 2001
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


/** \file RTPSenderInfo.h
 * This file declares the class RTPSenderInfo.
 */

#ifndef __RTPSENDERINFO_H__
#define __RTPSENDERINFO_H__

#include <omnetpp.h>

#include "types.h"
#include "RTPParticipantInfo.h"
#include "reports.h"


/**
 * The class RTPSenderInfo is used by an rtp end system for storing information
 * about itself. With the stored information it can create a SenderReport.
 */
class INET_API RTPSenderInfo : public RTPParticipantInfo
{

    public:

        /**
         * Default constructor.
         */
        RTPSenderInfo(u_int32 ssrc = 0);

        /**
         * Copy constructor.
         */
        RTPSenderInfo(const RTPSenderInfo& senderInfo);

        /**
         * Destructor.
         */
        virtual ~RTPSenderInfo();

        /**
         * Assignment operator.
         */
        RTPSenderInfo& operator=(const RTPSenderInfo& senderInfo);

        /**
         * Duplicates this RTPSenderInfo by calling the copy constructor.
         */
        virtual cObject *dup() const;

        /**
         * Returns the class name "RTPSenderInfo".
         */
        virtual const char *className() const;

        /**
         * Stores information about this outgoing RTPPacket.
         */
        virtual void processRTPPacket(RTPPacket *packet, simtime_t arrivalTime);

        /**
         * Processes an incoming ReceptionReport for this sender.
         */
        virtual void processReceptionReport(ReceptionReport *report, simtime_t arrivalTime);

        /**
         * Returns a SenderReport for this rtp endsystem.
         * If it hasn't sent rtp data packets during the
         * last 2 rtcp intervals, it returns NULL.
         */
        virtual SenderReport *senderReport(simtime_t now);

        /**
         * Sets the time (simTime) when this endsystem has
         * started sending rtp packets.
         */
        virtual void setStartTime(simtime_t startTime);

        /**
         * Sets the clock rate (in ticks per second) this sender
         * increases the rtp time stamp.
         */
        virtual void setClockRate(int clockRate);

        /**
         * Sets the initial rtp time stamp.
         */
        virtual void setTimeStampBase(u_int32 timeStampBase);

        /**
         * Sets the initial sequence number.
         */
        virtual void setSequenceNumberBase(u_int16 sequenceNumberBase);

        /**
         * A sender info shall never be deleted!
         */
        virtual bool toBeDeleted(simtime_t now);

    private:

        /**
         * The time when the transmission was started.
         */
        simtime_t _startTime;

        /**
         * The clock rate this sender increases the rtp time stamp.
         */
        int _clockRate;

        /**
         * The initial rtp time stamp.
         */
        u_int32 _timeStampBase;

        /**
         * The initial sequence number.
         */
        u_int16 _sequenceNumberBase;

        /**
         * The number of rtp data packets this sender has sent.
         */
        u_int32 _packetsSent;

        /**
         * The number of data bytes this sender has sent.
         */
        u_int32 _bytesSent;

};

#endif

