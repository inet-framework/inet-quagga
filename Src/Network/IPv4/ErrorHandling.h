//
// Copyright (C) 2000 Institut fuer Telematik, Universitaet Karlsruhe
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


//  Cleanup and rewrite: Andras Varga, 2004

#ifndef __ERRORHANDLING_H__
#define __ERRORHANDLING_H__

#include <omnetpp.h>
#include "INETDefs.h"
#include "IPControlInfo.h"


/**
 * Error Handling: print out received error
 */
// FIXME is such thing needed at all???
class INET_API ErrorHandling: public cSimpleModule
{
  protected:
    long numReceived;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif

