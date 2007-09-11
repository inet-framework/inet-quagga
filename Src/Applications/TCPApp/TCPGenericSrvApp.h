//
// Copyright 2004 Andras Varga
//
// This library is free software, you can redistribute it and/or modify
// it under  the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation;
// either version 2 of the License, or any later version.
// The library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//

#ifndef __TCPGENERICSRVAPP_H_
#define __TCPGENERICSRVAPP_H_

#include <omnetpp.h>
#include "INETDefs.h"



/**
 * Generic server application. It serves requests coming in GenericAppMsg
 * request messages. Clients are usually subclassed from TCPGenericCliAppBase.
 *
 * @see GenericAppMsg, TCPGenericCliAppBase
 */
class INET_API TCPGenericSrvApp : public cSimpleModule
{
  protected:
    simtime_t delay;
    simtime_t maxMsgDelay;

    long msgsRcvd;
    long msgsSent;
    long bytesRcvd;
    long bytesSent;

    void sendBack(cMessage *msg);
    void sendOrSchedule(cMessage *msg, simtime_t delay);

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif


