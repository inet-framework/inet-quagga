//
// Copyright (C) 2006 Andras Varga
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


#include "Ieee80211MgmtAdhoc.h"
#include "Ieee802Ctrl_m.h"


Define_Module(Ieee80211MgmtAdhoc);


void Ieee80211MgmtAdhoc::initialize(int stage)
{
    Ieee80211MgmtBase::initialize(stage);
}

void Ieee80211MgmtAdhoc::handleTimer(cMessage *msg)
{
    ASSERT(false);
}

void Ieee80211MgmtAdhoc::handleUpperMessage(cMessage *msg)
{
    Ieee80211DataFrame *frame = encapsulate(msg);
    sendOrEnqueue(frame);
}

void Ieee80211MgmtAdhoc::receiveChangeNotification(int category, cPolymorphic *details)
{
    Enter_Method_Silent();
    EV << "ignoring change notification\n";
}

void Ieee80211MgmtAdhoc::handleDataFrame(Ieee80211DataFrame *frame)
{
    cMessage *msg = decapsulate(frame);
    send(msg, "upperGateOut");
}

void Ieee80211MgmtAdhoc::handleAuthenticationFrame(Ieee80211AuthenticationFrame *frame)
{
    EV << "ignoring frame " << frame << "\n";
}

void Ieee80211MgmtAdhoc::handleDeauthenticationFrame(Ieee80211DeauthenticationFrame *frame)
{
    EV << "ignoring frame " << frame << "\n";
}

void Ieee80211MgmtAdhoc::handleAssociationRequestFrame(Ieee80211AssociationRequestFrame *frame)
{
    EV << "ignoring frame " << frame << "\n";
}

void Ieee80211MgmtAdhoc::handleAssociationResponseFrame(Ieee80211AssociationResponseFrame *frame)
{
    EV << "ignoring frame " << frame << "\n";
}

void Ieee80211MgmtAdhoc::handleReassociationRequestFrame(Ieee80211ReassociationRequestFrame *frame)
{
    EV << "ignoring frame " << frame << "\n";
}

void Ieee80211MgmtAdhoc::handleReassociationResponseFrame(Ieee80211ReassociationResponseFrame *frame)
{
    EV << "ignoring frame " << frame << "\n";
}

void Ieee80211MgmtAdhoc::handleDisassociationFrame(Ieee80211DisassociationFrame *frame)
{
    EV << "ignoring frame " << frame << "\n";
}

void Ieee80211MgmtAdhoc::handleBeaconFrame(Ieee80211BeaconFrame *frame)
{
    EV << "ignoring frame " << frame << "\n";
}

void Ieee80211MgmtAdhoc::handleProbeRequestFrame(Ieee80211ProbeRequestFrame *frame)
{
    EV << "ignoring frame " << frame << "\n";
}

void Ieee80211MgmtAdhoc::handleProbeResponseFrame(Ieee80211ProbeResponseFrame *frame)
{
    EV << "ignoring frame " << frame << "\n";
}

