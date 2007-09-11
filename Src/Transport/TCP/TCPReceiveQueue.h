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

#ifndef __TCPRECEIVEQUEUE_H
#define __TCPRECEIVEQUEUE_H

#include <omnetpp.h>
#include "TCPConnection.h"


class TCPSegment;
class TCPCommand;


/**
 * Abstract base class for TCP receive queues. This class represents
 * data received by TCP but not yet passed up to the application.
 * The class also accomodates for selective retransmission, i.e.
 * also acts as a segment buffer.
 *
 * This class goes hand-in-hand with TCPSendQueue.
 *
 * This class is polymorphic because depending on where and how you
 * use the TCP model you might have different ideas about "sending data"
 * on a simulated connection: you might want to transmit real bytes,
 * "dummy" (byte count only), cMessage objects, etc; see discussion
 * at TCPSendQueue. Different subclasses can be written to accomodate
 * different needs.
 *
 * @see TCPSendQueue
 */
class INET_API TCPReceiveQueue : public cPolymorphic
{
  protected:
    TCPConnection *conn; // TCP connection object

  public:
    /**
     * Ctor.
     */
    TCPReceiveQueue()  {conn=NULL;}

    /**
     * Virtual dtor.
     */
    virtual ~TCPReceiveQueue() {}

    /**
     * Set initial receive sequence number.
     */
    virtual void init(uint32 startSeq) = 0;

    /**
     * Called when a TCP segment arrives, it should extract the payload
     * from the segment and store it in the receive queue. The segment
     * object should *not* be deleted.
     *
     * The method should return the sequence number to be ACKed.
     */
    virtual uint32 insertBytesFromSegment(TCPSegment *tcpseg) = 0;

    /**
     * Should create a packet to be passed up to the app, up to (but NOT
     * including) the given sequence no (usually rcv_nxt).
     * It should return NULL if there's no more data to be passed up --
     * this method is called several times until it returns NULL.
     */
    virtual cMessage *extractBytesUpTo(uint32 seq) = 0;

};

#endif


