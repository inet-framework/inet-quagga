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


#include "MACRelayUnitBase.h"

#include "MACAddress.h"
#include "EtherFrame_m.h"
#include "utils.h"
#include "Ethernet.h"



/* unused for now
static std::ostream& operator<< (std::ostream& os, cMessage *msg)
{
    os << "(" << msg->className() << ")" << msg->fullName();
    return os;
}
*/

static std::ostream& operator<< (std::ostream& os, const MACRelayUnitBase::AddressEntry& e)
{
    os << "port=" << e.portno << " insTime=" << e.insertionTime;
    return os;
}


void MACRelayUnitBase::initialize()
{
    // number of ports
    numPorts = gate("lowerLayerOut",0)->size();
    if (gate("lowerLayerIn",0)->size()!=numPorts)
        error("the sizes of the lowerLayerIn[] and lowerLayerOut[] gate vectors must be the same");

    // other parameters
    addressTableSize = par("addressTableSize");
    addressTableSize = addressTableSize >= 0 ? addressTableSize : 0;

    agingTime = par("agingTime");
    agingTime = agingTime > 0 ? agingTime : 10;

    // Option to pre-read in Address Table. To turn ot off, set addressTableFile to empty string
    const char *addressTableFile = par("addressTableFile");
    if (addressTableFile && *addressTableFile)
        readAddressTable(addressTableFile);

    seqNum = 0;

    WATCH_MAP(addresstable);
}

void MACRelayUnitBase::handleAndDispatchFrame(EtherFrame *frame, int inputport)
{
    // update address table
    updateTableWithAddress(frame->getSrc(), inputport);

    // handle broadcast frames first
    if (frame->getDest().isBroadcast())
    {
        EV << "Broadcasting broadcast frame " << frame << endl;
        broadcastFrame(frame, inputport);
        return;
    }

    // Finds output port of destination address and sends to output port
    // if not found then broadcasts to all other ports instead
    int outputport = getPortForAddress(frame->getDest());
    if (inputport==outputport)
    {
        EV << "Output port is same as input port, " << frame->fullName() <<
              " dest " << frame->getDest() << ", discarding frame\n";
        delete frame;
        return;
    }
    if (outputport>=0)
    {
        EV << "Sending frame " << frame << " with dest address " << frame->getDest() << " to port " << outputport << endl;
        send(frame, "lowerLayerOut", outputport);
    }
    else
    {
        EV << "Dest address " << frame->getDest() << " unknown, broadcasting frame " << frame << endl;
        broadcastFrame(frame, inputport);
    }
}

void MACRelayUnitBase::broadcastFrame(EtherFrame *frame, int inputport)
{
    for (int i=0; i<numPorts; ++i)
        if (i!=inputport)
            send((EtherFrame*)frame->dup(), "lowerLayerOut", i);
    delete frame;
}

void MACRelayUnitBase::printAddressTable()
{
    AddressTable::iterator iter;
    EV << "Address Table (" << addresstable.size() << " entries):\n";
    for (iter = addresstable.begin(); iter!=addresstable.end(); ++iter)
    {
        EV << "  " << iter->first << " --> port" << iter->second.portno <<
              (iter->second.insertionTime+agingTime <= simTime() ? " (aged)" : "") << endl;
    }
}

void MACRelayUnitBase::removeAgedEntriesFromTable()
{
    for (AddressTable::iterator iter = addresstable.begin(); iter != addresstable.end();)
    {
        AddressTable::iterator cur = iter++; // iter will get invalidated after erase()
        AddressEntry& entry = cur->second;
        if (entry.insertionTime + agingTime <= simTime())
        {
            EV << "Removing aged entry from Address Table: " <<
                  cur->first << " --> port" << cur->second.portno << "\n";
            addresstable.erase(cur);
        }
    }
}

void MACRelayUnitBase::removeOldestTableEntry()
{
    AddressTable::iterator oldest = addresstable.end();
    simtime_t oldestInsertTime = simTime()+1;
    for (AddressTable::iterator iter = addresstable.begin(); iter != addresstable.end(); iter++)
    {
        if (iter->second.insertionTime < oldestInsertTime)
        {
            oldest = iter;
            oldestInsertTime = iter->second.insertionTime;
        }
    }
    if (oldest != addresstable.end())
    {
        EV << "Table full, removing oldest entry: " <<
              oldest->first << " --> port" << oldest->second.portno << "\n";
        addresstable.erase(oldest);
    }
}

void MACRelayUnitBase::updateTableWithAddress(MACAddress& address, int portno)
{
    AddressTable::iterator iter;

    iter = addresstable.find(address);
    if (iter == addresstable.end())
    {
        // Observe finite table size
        if (addressTableSize!=0 && addresstable.size() == (unsigned int)addressTableSize)
        {
            // lazy removal of aged entries: only if table gets full (this step is not strictly needed)
            EV << "Making room in Address Table by throwing out aged entries.\n";
            removeAgedEntriesFromTable();

            if (addresstable.size() == (unsigned int)addressTableSize)
                removeOldestTableEntry();
        }

        // Add entry to table
        EV << "Adding entry to Address Table: "<< address << " --> port" << portno << "\n";
        AddressEntry entry;
        entry.portno = portno;
        entry.insertionTime = simTime();
        addresstable[address] = entry;
    }
    else
    {
        // Update existing entry
        EV << "Updating entry in Address Table: "<< address << " --> port" << portno << "\n";
        AddressEntry& entry = iter->second;
        entry.insertionTime = simTime();
        entry.portno = portno;
    }
}

int MACRelayUnitBase::getPortForAddress(MACAddress& address)
{
    AddressTable::iterator iter = addresstable.find(address);
    if (iter == addresstable.end())
    {
        // not found
        return -1;
    }
    if (iter->second.insertionTime + agingTime <= simTime())
    {
        // don't use (and throw out) aged entries
        EV << "Ignoring and deleting aged entry: "<< iter->first << " --> port" << iter->second.portno << "\n";
        addresstable.erase(iter);
        return -1;
    }
    return iter->second.portno;
}


void MACRelayUnitBase::readAddressTable(const char* fileName)
{
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL)
        error("cannot open address table file `%s'", fileName);

    //  Syntax of the file goes as:
    //  Address in hexadecimal representation, Portno
    //  ffffffff    1
    //  ffffeed1    2
    //  aabcdeff    3
    //
    //  etc...
    //
    //  Each iteration of the loop reads in an entire line i.e. up to '\n' or EOF characters
    //  and uses strtok to extract tokens from the resulting string
    char *line;
    int lineno = 0;
    while ((line = fgetline(fp)) != NULL)
    {
        lineno++;

        // lines beginning with '#' are treated as comments
        if (line[0]=='#')
            continue;

        // scan in hexaddress
        char *hexaddress = strtok(line, " \t");
        // scan in port number
        char *portno = strtok(NULL, " \t");

        // empty line?
        if (!hexaddress)
            continue;

        // broken line?
        if (!portno)
            error("line %d invalid in address table file `%s'", lineno, fileName);

        // Create an entry with address and portno and insert into table
        AddressEntry entry;
        entry.insertionTime = 0;
        entry.portno = atoi(portno);
        addresstable[MACAddress(hexaddress)] = entry;

        // Garbage collection before next iteration
        delete [] line;
    }
    fclose(fp);
}


void MACRelayUnitBase::sendPauseFrame(int portno, int pauseUnits)
{
    EV << "Creating and sending PAUSE frame on port " << portno << " with duration=" << pauseUnits << " units\n";

    // create Ethernet frame
    char framename[40];
    sprintf(framename, "pause-%d-%d", id(), seqNum++);
    EtherPauseFrame *frame = new EtherPauseFrame(framename, ETH_PAUSE);
    frame->setPauseTime(pauseUnits);

    frame->setByteLength(ETHER_MAC_FRAME_BYTES+ETHER_PAUSE_COMMAND_BYTES);
    if (frame->byteLength() < MIN_ETHERNET_FRAME)
        frame->setByteLength(MIN_ETHERNET_FRAME);

    send(frame, "lowerLayerOut", portno);
}

