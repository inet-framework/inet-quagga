//
// Copyright (C) 2006 Alfonso Ariza Quintana
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


#include <omnetpp.h>
#include <stdlib.h>
#include <string.h>

#include "ManetManager.h"
#include "RoutingTableAccess.h"
#include "RoutingTable.h"

Define_Module(ManetManager);


void ManetManager::initialize(int stage)
{
   bool manetPurgeRoutingTables=false;	
   if (stage==4)
   {
	manetActive = (bool) par("manetActive");
	routingProtocol = par("routingProtocol").stringValue ();

	if (manetActive)
	{
		manetPurgeRoutingTables = (bool) par("manetPurgeRoutingTables");
		if (manetPurgeRoutingTables)
		{
			RoutingTable *rt = RoutingTableAccess ().get ();
			RoutingEntry *entry;
// clean the route table wlan interface entry
	                for (int i=rt->numRoutingEntries()-1;i>=0;i--)
			{
                	        entry= rt->routingEntry(i);
	
				if (strstr (entry->interfacePtr->name(),"wlan")!=NULL)
				{
					rt->deleteRoutingEntry(entry);
				}


			}
		}
/* for use dinamic modules in the future */
/*
		if (strcmp("AODV", routingProtocol)==0)
		{
			cModuleType *moduleType = findModuleType("AODVUU");
			routingModule = moduleType->create("ManetRoutingProtocol", this);
// set up parameters and gate sizes before we set up its submodules
			routingModule->par("unidir_hack") = par("unidir_hack");
			routingModule->par("rreq_gratuitous") = par("rreq_gratuitous");
			routingModule->par("expanding_ring_search") = par("expanding_ring_search");
			routingModule->par("local_repair")= par("local_repair");
			routingModule->par("receive_n_hellos") = par("receive_n_hellos");
			routingModule->par("hello_jittering") = par("hello_jittering");
			routingModule->par ("wait_on_reboot") =par ("wait_on_reboot");
			routingModule->par("debug")=par("debug");
			routingModule->par("rt_log_interval")=par("rt_log_interval");	// Note: in milliseconds!
			routingModule->par("log_to_file")=par("log_to_file");
			routingModule->par("optimized_hellos")=par("optimized_hellos");
			routingModule->par("ratelimit")=par("ratelimit");
			routingModule->par("llfeedback")=par("llfeedback");
			routingModule->par("internet_gw_mode")=par("internet_gw_mode");
                        routingModule->par("internet_gw_address")=par("internet_gw_address");
// Connet to ip
			routingModule->gate("to_ip")->connectTo(gate("to_ip"));
// create internals, and schedule it
                        routingModule->buildInside();
                        routingModule->scheduleStart(simTime());
		}
		else if (strcmp("DSR",routingProtocol)==0)
		{
		}
*/
	}
	if (strcmp("AODV", routingProtocol)==0)
		routing_protocol = AODV;
        else
		manetActive=false;


    }
}




void ManetManager::handleMessage(cMessage *msg)
{
/* for use dinamic modules in the future */
/*

	sendDirect(msg,0, routingModule, "from_ip");
*/
    if (manetActive)
	switch (routing_protocol)
        {
        case AODV:
         send( msg, "to_aodv");
        break;
        case DSR:
         send( msg, "to_dsr");
        break;
        }
}

