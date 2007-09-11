/***************************************************************************
                          RTPAVProfilePayload32Sender.cpp  -  description
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

/** \file RTPAVProfilePayload32Sender.cc
 *
 * Parts of the code in this file (reading of the gdf data) are
 * extracted from the program generator.cc of Klaus Wehrle's mpg2
 * package.
 */

#include <fstream.h>
#include <string.h>

#include <omnetpp.h>

#include "RTPPacket.h"
#include "RTPInnerPacket.h"
#include "RTPAVProfilePayload32Sender.h"
#include "RTPMpegPacket.h"

Define_Module_Like(RTPAVProfilePayload32Sender, RTPPayloadSender);

void RTPAVProfilePayload32Sender::initialize() {

    RTPPayloadSender::initialize();

    _clockRate = 90000;
    _payloadType = 32;
};


/*
void RTPAVProfilePayload32Sender::activity() {

    cMessage *msg = receive();

    if (strcmp(msg->className(), "RTPInnerPacket"))
        error("RTPAVProfilePayload32Sender: received message is not an RTPInnerPacket !");

    RTPInnerPacket *rinpIn = (RTPInnerPacket *)msg;

    if (rinpIn->type() == RTPInnerPacket::RTP_INP_INITIALIZE_SENDER_MODULE) {
        initializeSenderModule(rinpIn);
    }
    else {
        error("first messsage to payload sender module must be createSenderModule");
    }

    bool moreFrames = true;


    do {

        cMessage *msgIn;

        if (_status == STOPPED) {
            msgIn = receiveOn(findGate("fromProfile"));

        }
        else {
            msgIn = receive();


        }

        if (msgIn->arrivalGateId() == findGate("fromProfile")) {
            RTPInnerPacket *rinp = (RTPInnerPacket *)msgIn;
            if (rinp->type() == RTPInnerPacket::RTP_INP_SENDER_MODULE_CONTROL) {


                RTPSenderControlMessage *rscm = (RTPSenderControlMessage *)(rinp->decapsulate());


                if (!opp_strcmp(rscm->command(), "PLAY")) {

                    play();


                    moreFrames = sendPacket();


                }
                else if (!opp_strcmp(rscm->command(), "STOP")) {


                    stop();
                }
                else {
                    EV << "payload sender: unknown sender control message, ignored" << endl;
                }
                //delete rscm;
            }
        }
        else {


            moreFrames = sendPacket();
        };
        delete msgIn;

        if (!moreFrames)
            finish();
    } while (true);
};
*/

void RTPAVProfilePayload32Sender::initializeSenderModule(RTPInnerPacket *rinpIn) {

    char line[100];
    char unit[100];
    char description[100];

    RTPPayloadSender::initializeSenderModule(rinpIn);

    // first line: fps unit description
    _inputFileStream.get(line, 100, '\n');

    float fps;
    sscanf(line, "%f %s %s", &fps, unit, description);
    _framesPerSecond = fps;

    _frameNumber = 0;

    // get new line character
    char c;
    _inputFileStream.get(c);

    // second line: initial delay unit description
    _inputFileStream.get(line, 100, '\n');

    float delay;
    sscanf(line, "%f %s %s", &delay, unit, description);

    _initialDelay = delay;

    // wait initial delay
//    cMessage *reminderMessage = new cMessage("next frame");
//    scheduleAt(simTime() + _initialDelay, reminderMessage);

};


bool RTPAVProfilePayload32Sender::sendPacket() {

    // read next frame line
    int bits;
    char unit[100];
    char description[100];

    _inputFileStream >> bits;
    _inputFileStream >> unit;
    _inputFileStream.get(description, 100, '\n');

    int pictureType = 0;

    if (strchr(description, 'I')) {
        pictureType = 1;
    }
    else if (strchr(description, 'P')) {
        pictureType = 2;
    }
    else if (strchr(description, 'B')) {
        pictureType = 3;
    }
    else if (strchr(description, 'D')) {
        pictureType = 4;
    };

    int bytesRemaining = bits / 8;

    if (!_inputFileStream.eof()) {
        while (bytesRemaining > 0) {
            RTPPacket *rtpPacket = new RTPPacket("RTPPacket");
            RTPMpegPacket *mpegPacket = new RTPMpegPacket("MpegPacket");

            // the only mpeg information we know is the picture type
            mpegPacket->setPictureType(pictureType);

            // the maximum number of real data bytes
            int maxDataSize = _mtu - rtpPacket->length() - mpegPacket->length();

            if (bytesRemaining > maxDataSize) {

                // we do not know where slices in the
                // mpeg picture begin
                // so we simulate by assuming a slice
                // has a length of 64 bytes
                int slicedDataSize = (maxDataSize / 64) * 64;

                mpegPacket->addLength(slicedDataSize);


                rtpPacket->encapsulate(mpegPacket);

                bytesRemaining = bytesRemaining - slicedDataSize;
            }
            else {
                mpegPacket->addLength(bytesRemaining);
                rtpPacket->encapsulate(mpegPacket);
                // set marker because this is
                // the last packet of the frame
                rtpPacket->setMarker(1);
                bytesRemaining = 0;
            }

            rtpPacket->setPayloadType(_payloadType);
            rtpPacket->setSequenceNumber(_sequenceNumber);
            _sequenceNumber++;


            rtpPacket->setTimeStamp(_timeStampBase + (_initialDelay + (1 / _framesPerSecond) * (double)_frameNumber) * _clockRate);
            rtpPacket->setSSRC(_ssrc);


            RTPInnerPacket *rinpOut = new RTPInnerPacket("dataOut()");


            rinpOut->dataOut(rtpPacket);

            send(rinpOut, "toProfile");

        };
        _frameNumber++;

        _reminderMessage = new cMessage("nextFrame");
        scheduleAt(simTime() + 1.0 / _framesPerSecond, _reminderMessage);
        return true;
    }
    else {
        return false;
    }
};