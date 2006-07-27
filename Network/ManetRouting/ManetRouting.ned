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

//FIXME FIXME FIXME documentation, reindenting, etc!!!!

simple AODVUU
    parameters:
        log_to_file: bool,
        hello_jittering: bool,
        optimized_hellos: bool,
        expanding_ring_search: bool,
        local_repair: bool,
        rreq_gratuitous: bool,
	debug: bool,
        rt_log_interval: numeric const,
        unidir_hack: numeric const,
        internet_gw_mode: numeric const,
        receive_n_hellos: numeric const,
        wait_on_reboot: numeric const,
        ratelimit: numeric const,
        internet_gw_address: string,
        active_timeout : numeric const,
        llfeedback: numeric const;
    gates:
        in: from_ip;
        out: to_ip;
endsimple


simple ManetManager
    parameters:
// Manager parameters
         routingProtocol: string,
	 manetActive: bool,
         manetPurgeRoutingTables : bool;
// Aodv parameters 
      gates:
        in: from_ip;
//        out: to_ip;
        out: to_aodv;
endsimple

module ManetRouting
    gates:
        in: from_ip;
        out: to_ip;
    submodules:
// the name of manet routing manager module must be "manetmanager", the routing protocols is ManetRouting.ned
        manetmanager: ManetManager;
            parameters:
// Manager parameters
// eliminate in the routing table all the initial reference to wlan interfaces
                manetActive = true,
                routingProtocol = "AODV",
		manetPurgeRoutingTables=true;
        aodvprotocol : AODVUU;
	    parameters:
// Aodv parameters 
                log_to_file = true,
                hello_jittering = true,
                optimized_hellos = false,
                expanding_ring_search = false,
                local_repair = true,
                rreq_gratuitous = true,
                debug=false,
                rt_log_interval = 0,
                unidir_hack = 0,
                internet_gw_mode = 0,
                receive_n_hellos = 1,
                ratelimit = 1000,
                llfeedback = 0, //1000, not suport inter layer communication
                wait_on_reboot=0,
                active_timeout = 6000, // time in ms
                internet_gw_address="0.0.0.0";
            display: "i=block/control;p=169,56";
      connections nocheck:
        manetmanager.from_ip <-- from_ip;
        manetmanager.to_aodv --> aodvprotocol.from_ip;
        aodvprotocol.to_ip --> to_ip;

endmodule





