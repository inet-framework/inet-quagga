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


import "Router6";
import "StandardHost6";
import "EtherHub";
import "FlatNetworkConfigurator6";


channel fiberline extends cBasicChannel
{
    parameters:
        delay = 1us;
        datarate = 512*1000000;
}

channel ethernetline extends cBasicChannel
{
    parameters:
        delay = 0.1us;
}

network NClientsEth
{
    parameters:
        int n;
    submodules:
        configurator: FlatNetworkConfigurator6 {
            parameters:
                moduleTypes = "Router6 StandardHost6 EtherHub";
                nonIPModuleTypes = "EtherHub";
        };
        r1: Router6 {
        };
        r2: Router6 {
        };
        r3: Router6 {
        };
        cli[n]: StandardHost6 {
        };
        srv: StandardHost6 {
        };
        hub: EtherHub {
        };
    connections allowunconnected:
        for i=0..n-1 {
            cli[i].ethOut++ --> ethernetline --> hub.in++;
            cli[i].ethIn++ <-- ethernetline <-- hub.out++;
        };

        hub.out++ --> ethernetline --> r1.ethIn++;
        hub.in++ <-- ethernetline <-- r1.ethOut++;

        r1.ethOut++ --> ethernetline --> r2.ethIn++;
        r1.ethIn++ <-- ethernetline <-- r2.ethOut++;

        r2.ethOut++ --> ethernetline --> r3.ethIn++;
        r2.ethIn++ <-- ethernetline <-- r3.ethOut++;

        r3.ethOut++ --> ethernetline --> srv.ethIn++;
        r3.ethIn++ <-- ethernetline <-- srv.ethOut++;

        // Mixing ethernet and ppp currently doesn't work, due to a bug in
        // FlatNetworkConfigurator6::determineGateIndex.
        //
        // r1.out++ --> fiberline --> r2.in++;
        // r1.in++ <-- fiberline <-- r2.out++;
        //
        // r2.out++ --> fiberline --> r3.in++;
        // r2.in++ <-- fiberline <-- r3.out++;
        //
        // r3.out++ --> fiberline --> srv.in++;
        // r3.in++ <-- fiberline <-- srv.out++;

}

