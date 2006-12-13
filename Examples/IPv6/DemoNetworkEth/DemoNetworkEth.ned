//
// Copyright (C) 2005 Wei Yang, Ng
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

import "Router6";
import "StandardHost6";
import "FlatNetworkConfigurator6";
import "TCPDump";

channel ethernetline extends cBasicChannel
{
    parameters:
        delay = 0.1us;
}

network DemoNetworkEth
{
    parameters:
        double n;
    submodules:
        configurator: FlatNetworkConfigurator6 {
            parameters:
                moduleTypes = "Router6 StandardHost6 TCPDump";
                nonIPModuleTypes = "EtherHub TCPDump";
                @display("");
        };
        r1: Router6 {
            parameters:
                @display("");
        };
        r2: Router6 {
            parameters:
                @display("");
        };
        cli[n]: StandardHost6 {
            parameters:
                @display("");
        };
        srv[n]: StandardHost6 {
            parameters:
                @display("");
        };
        linemonitor[n]: TCPDump {
            parameters:
                @display("");
        };
    connections allowunconnected:
        for i=0..n-1 {
            cli[i].ethOut++ --> ethernetline --> linemonitor[i].in1;
            linemonitor[i].out2 --> ethernetline --> r1.ethIn++;
            linemonitor[i].in2 <-- ethernetline <-- r1.ethOut++;
            cli[i].ethIn++ <-- ethernetline <-- linemonitor[i].out1;
            //cli[i].ethOut++ --> ethernetline --> r1.ethIn++;
            //cli[i].ethIn++ <-- ethernetline <-- r1.ethOut++;
            srv[i].ethOut++ --> ethernetline --> r2.ethIn++;
            srv[i].ethIn++ <-- ethernetline <-- r2.ethOut++;
        };

        r1.ethOut++ --> ethernetline --> r2.ethIn++;
        r1.ethIn++ <-- ethernetline <-- r2.ethOut++;

}

