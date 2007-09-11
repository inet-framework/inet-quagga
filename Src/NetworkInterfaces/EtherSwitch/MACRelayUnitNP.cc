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

#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif


#include "MACRelayUnitNP.h"
#include "EtherFrame_m.h"
#include "utils.h"
#include "Ethernet.h"
#include "MACAddress.h"



Define_Module( MACRelayUnitNP );


/* unused for now
static std::ostream& operator<< (std::ostream& os, cMessage *msg)
{
    os << "(" << msg->className() << ")" << msg->fullName();
    return os;
}
*/

MACRelayUnitNP::MACRelayUnitNP()
{
    endProcEvents = NULL;
    numCPUs = 0;
}

MACRelayUnitNP::~MACRelayUnitNP()
{
    for (int i=0; i<numCPUs; i++)
        cancelAndDelete(endProcEvents[i]);
    delete [] endProcEvents;
}

void MACRelayUnitNP::initialize()
{
    MACRelayUnitBase::initialize();

    bufferLevel.setName("buffer level");
    queue.setName("queue");

    numProcessedFrames = numDroppedFrames = 0;
    WATCH(numProcessedFrames);
    WATCH(numDroppedFrames);

    numCPUs = par("numCPUs");

    processingTime    = par("processingTime");
    bufferSize = par("bufferSize");
    highWatermark = par("highWatermark");
    pauseUnits = par("pauseUnits");

    // 1 pause unit is 512 bit times; we assume 100Mb MACs here.
    // We send a pause again when previous one is about to expire.
    pauseInterval = pauseUnits*512.0/100000.0;

    pauseLastSent = 0;
    WATCH(pauseLastSent);

    bufferUsed = 0;
    WATCH(bufferUsed);

    endProcEvents = new cMessage *[numCPUs];
    for (int i=0; i<numCPUs; i++)
    {
        char msgname[20];
        sprintf(msgname, "endProcessing-cpu%d", i);
        endProcEvents[i] = new cMessage(msgname,i);
    }

    EV << "Parameters of (" << className() << ") " << fullPath() << "\n";
    EV << "number of processors: " << numCPUs << "\n";
    EV << "processing time: " << processingTime << "\n";
    EV << "ports: " << numPorts << "\n";
    EV << "buffer size: " << bufferSize << "\n";
    EV << "address table size: " << addressTableSize << "\n";
    EV << "aging time: " << agingTime << "\n";
    EV << "high watermark: " << highWatermark << "\n";
    EV << "pause time: " << pauseUnits << "\n";
    EV << "\n";
}

void MACRelayUnitNP::handleMessage(cMessage *msg)
{
    if (!msg->isSelfMessage())
    {
        // Frame received from MAC unit
        handleIncomingFrame(check_and_cast<EtherFrame *>(msg));
    }
    else
    {
        // Self message signal used to indicate a frame has finished processing
        processFrame(msg);
    }
}

void MACRelayUnitNP::handleIncomingFrame(EtherFrame *frame)
{
    // If buffer not full, insert payload frame into buffer and process the frame in parallel.

    long length = frame->byteLength();
    if (length + bufferUsed < bufferSize)
    {
        bufferUsed += length;

        // send PAUSE if above watermark
        if (pauseUnits>0 && highWatermark>0 && bufferUsed>=highWatermark && simTime()-pauseLastSent>pauseInterval)
        {
            // send PAUSE on all ports
            for (int i=0; i<numPorts; i++)
                sendPauseFrame(i, pauseUnits);
            pauseLastSent = simTime();
        }

        // assign frame to a free CPU (if there is one)
        int i;
        for (i=0; i<numCPUs; i++)
            if (!endProcEvents[i]->isScheduled())
                break;
        if (i==numCPUs)
        {
            EV << "All CPUs busy, enqueueing incoming frame " << frame << " for later processing\n";
            queue.insert(frame);
        }
        else
        {
            EV << "Idle CPU-" << i << " starting processing of incoming frame " << frame << endl;
            cMessage *msg = endProcEvents[i];
            msg->encapsulate(frame);
            scheduleAt(simTime() + processingTime, msg);
        }
    }
    // Drop the frame and record the number of dropped frames
    else
    {
        EV << "Buffer full, dropping frame " << frame << endl;
        delete frame;
        ++numDroppedFrames;
    }

    // Record statistics of buffer usage levels
    bufferLevel.record(bufferUsed);
}

void MACRelayUnitNP::processFrame(cMessage *msg)
{
    int cpu = msg->kind();
    EtherFrame *frame = (EtherFrame *) msg->decapsulate();
    long length = frame->byteLength();
    int inputport = frame->arrivalGate()->index();

    EV << "CPU-" << cpu << " completed processing of frame " << frame << endl;

    handleAndDispatchFrame(frame, inputport);
    printAddressTable();

    bufferUsed -= length;
    bufferLevel.record(bufferUsed);

    numProcessedFrames++;

    // Process next frame in queue if they are pending
    if (!queue.empty())
    {
        EtherFrame *newframe = (EtherFrame *) queue.pop();
        msg->encapsulate(newframe);
        EV << "CPU-" << cpu << " starting processing of frame " << newframe << endl;
        scheduleAt(simTime()+processingTime, msg);
    }
    else
    {
        EV << "CPU-" << cpu << " idle\n";
    }
}

void MACRelayUnitNP::finish()
{
    if (par("writeScalars").boolValue())
    {
        recordScalar("processed frames", numProcessedFrames);
        recordScalar("dropped frames", numDroppedFrames);
    }
}

