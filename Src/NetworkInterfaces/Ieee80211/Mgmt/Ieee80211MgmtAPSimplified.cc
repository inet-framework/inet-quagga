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


#include "Ieee80211MgmtAPSimplified.h"
#include "Ieee802Ctrl_m.h"
#include "EtherFrame_m.h"

Define_Module(Ieee80211MgmtAPSimplified);


// FIXME add sequence number handling

void Ieee80211MgmtAPSimplified::initialize(int stage)
{
    Ieee80211MgmtAPBase::initialize(stage);
}

void Ieee80211MgmtAPSimplified::handleTimer(cMessage *msg)
{
    ASSERT(false);
}

void Ieee80211MgmtAPSimplified::handleUpperMessage(cMessage *msg)
{
    // convert Ethernet frames arriving from MACRelayUnit (i.e. from
    // the AP's other Ethernet or wireless interfaces)
    Ieee80211DataFrame *frame = convertFromEtherFrame(check_and_cast<EtherFrame *>(msg));
    sendOrEnqueue(frame);
}

void Ieee80211MgmtAPSimplified::handleCommand(int msgkind, cPolymorphic *ctrl)
{
    error("handleCommand(): no commands supported");
}

void Ieee80211MgmtAPSimplified::receiveChangeNotification(int category, cPolymorphic *details)
{
    Enter_Method_Silent();
    printNotificationBanner(category, details);
}

void Ieee80211MgmtAPSimplified::handleDataFrame(Ieee80211DataFrame *frame)
{
    // check toDS bit
    if (!frame->getToDS())
    {
        // looks like this is not for us - discard
        delete frame;
        return;
    }

    if (hasRelayUnit)
    {
        // LAN bridging: if we have a relayUnit, send up the frame to it.
        // We don't need to call distributeReceivedDataFrame() here, because
        // if the frame needs to be distributed onto the wireless LAN too,
        // then relayUnit will send a copy back to us.
        send(convertToEtherFrame(frame), "uppergateOut");
    }
    else
    {
        // send it out to the destination STA
        distributeReceivedDataFrame(frame);
    }
}

void Ieee80211MgmtAPSimplified::handleAuthenticationFrame(Ieee80211AuthenticationFrame *frame)
{
    dropManagementFrame(frame);
}

void Ieee80211MgmtAPSimplified::handleDeauthenticationFrame(Ieee80211DeauthenticationFrame *frame)
{
    dropManagementFrame(frame);
}

void Ieee80211MgmtAPSimplified::handleAssociationRequestFrame(Ieee80211AssociationRequestFrame *frame)
{
    dropManagementFrame(frame);
}

void Ieee80211MgmtAPSimplified::handleAssociationResponseFrame(Ieee80211AssociationResponseFrame *frame)
{
    dropManagementFrame(frame);
}

void Ieee80211MgmtAPSimplified::handleReassociationRequestFrame(Ieee80211ReassociationRequestFrame *frame)
{
    dropManagementFrame(frame);
}

void Ieee80211MgmtAPSimplified::handleReassociationResponseFrame(Ieee80211ReassociationResponseFrame *frame)
{
    dropManagementFrame(frame);
}

void Ieee80211MgmtAPSimplified::handleDisassociationFrame(Ieee80211DisassociationFrame *frame)
{
    dropManagementFrame(frame);
}

void Ieee80211MgmtAPSimplified::handleBeaconFrame(Ieee80211BeaconFrame *frame)
{
    dropManagementFrame(frame);
}

void Ieee80211MgmtAPSimplified::handleProbeRequestFrame(Ieee80211ProbeRequestFrame *frame)
{
    dropManagementFrame(frame);
}

void Ieee80211MgmtAPSimplified::handleProbeResponseFrame(Ieee80211ProbeResponseFrame *frame)
{
    dropManagementFrame(frame);
}


