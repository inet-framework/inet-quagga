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


import "Router";
import "StandardHost";
import "FlatNetworkConfigurator";


channel ethernetline2 extends cBasicChannel
{
    parameters:
        delay = 0.1us;
        datarate = 100*1000000;
}

channel gigabitline2 extends cBasicChannel
{
    parameters:
        delay = 0.1us;
        datarate = 1000*1000000;
}

network NClients2
{
    parameters:
        int numrouters;
        double hostsperrouter;
    submodules:
        configurator: FlatNetworkConfigurator {
            parameters:
                moduleTypes = "Router StandardHost";
                nonIPModuleTypes = "";
        };
        r[numrouters]: Router {
        };
        cli[numrouters*hostsperrouter]: StandardHost {
            parameters:
                @display("i=device/laptop_vs");
        };
        srv: StandardHost {
            parameters:
                @display("i=device/server_l");
        };
    connections allowunconnected:
        for i=0..numrouters-1, for j=0..hostsperrouter-1 {
            cli[i*hostsperrouter+j].pppg$o++ --> ethernetline2 --> r[i].pppg$i++;
            cli[i*hostsperrouter+j].pppg$i++ <-- ethernetline2 <-- r[i].pppg$o++;
        };

        for i=0..numrouters-2 {
            r[i].pppg$o++ --> gigabitline2 --> r[i+1].pppg$i++;
            r[i+1].pppg$o++ --> gigabitline2 --> r[i].pppg$i++;
        };
        r[numrouters-1].pppg$o++ --> ethernetline2 --> srv.pppg$i++;
        r[numrouters-1].pppg$i++ <-- ethernetline2 <-- srv.pppg$o++;
}

