/***************************************************************************
                          RTPPayloadSender.h  -  description
                             -------------------
    begin                : Wed Nov 28 2001
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


/** \file RTPPayloadSender.h
 * This file declares the class RTPPayloadSender.
 */

#ifndef __RTPPAYLOADSENDER_H__
#define __RTPPAYLOADSENDER_H__

#include <fstream>
#include <omnetpp.h>
#include "INETDefs.h"
#include "types.h"
#include "RTPInnerPacket.h"


/**
 * The class RTPPayloadSender is the base class for all modules creating
 * rtp data packets. It provides functionality needed by every rtp data
 * packet sender like opening and closing the data file and choosing sequence
 * number and time stamp start values.
 */
class INET_API RTPPayloadSender : public cSimpleModule
{
    public: //FIXME
    //protected:

        /**
         * Constructor, with activity() stack size.
         */
        RTPPayloadSender() : cSimpleModule(32768) {}

        /**
         * Cleaning up. Calls closeSourceFile.
         */
        virtual ~RTPPayloadSender();

        /**
         * Chooses sequence number and time stamp base values and
         * reads the omnet parameter "mtu".
         */
        virtual void initialize();

        virtual void activity();

        /**
         * A sender module's transmission can be in different states.
         */
        enum SenderStatus {
            STOPPED, //< No transmission.
            PLAYING  ///< Data is being sent.
        };

    protected:

        /**
         * The input file stream for the data file.
         */
        std::ifstream  _inputFileStream;

        /**
         * The maximum size of an RTPPacket.
         */
        int _mtu;

        /**
         * The ssrc identifier of this sender module.
         */
        u_int32 _ssrc;

        /**
         * The payload type this sender creates.
         */
        int _payloadType;

        /**
         * The clock rate in ticks per second this sender uses.
         */
        int _clockRate;

        /**
         * The first rtp time stamp used for created rtp data
         * packets. The value is chosen randomly.
         */
        u_int32 _timeStampBase;

        /**
         * The current rtp time stamp.
         */
        u_int32 _timeStamp;

        /**
         * The first sequence number used for created rtp data
         * packets. The value is chosen randomly.
         */
        u_int16 _sequenceNumberBase;

        /**
         * The current sequence number.
         */
        u_int16 _sequenceNumber;

        /**
         * The current state of data transmission.
         */
        SenderStatus _status;

        /**
        A self message used as timer for the moment the next packet must be sent.
        It's a member variable because when playing gets paused or stopped the timer
        must be cancelled.
        */
        cMessage *_reminderMessage;

        /**
         * This method is called when a newly create sender module
         * received its initialization message from profile module.
         * It returns an RTP_INP_SENDER_MODULE_INITIALIZED message which
         */
        virtual void initializeSenderModule(RTPInnerPacket *);

        /**
         * This method is called by initializeSenderModule and opens the
         * source data file as an inputFileStream stored in member
         * variable _inputFileStream. Most data formats can use
         * this method directly, but when using a library for a certain
         * data format which offers an own open routine this method
         * must be overwritten.
         */
        virtual void openSourceFile(const char *fileName);

        /**
         * This method is called by the destructor and closes the data file.
         */
        virtual void closeSourceFile();

        /**
         * Starts data transmission.
         * Every sender module must implement this method.
         */
        virtual void play();

        /**
         * Starts transmission from the current file position and plays until given
         * time (relative to start of file) is reached.
         * Implementation in sender modules is optional.
         */
        virtual void playUntilTime(simtime_t moment);

        /**
         * Starts transmission from the current file position and plays until given
         * byte position (excluding file header) is reached.
         * Implementation in sender modules is optional.
        */
        virtual void playUntilByte(int position);

        /**
         * When data is being transmitted this methods suspends till
         * a new PLAY command.
         * Implementation in sender modules is optional.
         */
        virtual void pause();

        /**
         * When the data transmission is paused the current position is
         * changed to this time (relative to start of file).
         * Implementation in sender modules is optional.
         */
        virtual void seekTime(simtime_t moment);

        /**
         * When the data transmission is paused the current position is
         * changed to this byte position (excluding file header).
         * Implementation in sender modules is optional.
         */
        virtual void seekByte(int position);

        /**
         * This method stop data transmission and resets the sender module so
         * that a following PLAY command would start the transmission at the
         * beginning again.
         */
        virtual void stop();

        /**
         * This method gets called when the sender module reaches the end of
         * file. For the transmission it has the same effect like stop().
         */
        virtual void endOfFile();

        /**
         * This method gets called when one (or more) rtp data packets have
         * to be sent. Subclasses must overwrite this method to do something
         * useful. This implementation doesn't send packets it just returns
         */
        virtual bool sendPacket();
};

#endif

