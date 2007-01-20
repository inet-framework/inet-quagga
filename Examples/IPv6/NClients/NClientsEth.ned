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
            cli[i].ethg$o++ --> ethernetline --> hub.pppg$i++;
            cli[i].ethg$i++ <-- ethernetline <-- hub.pppg$o++;
        };

        hub.pppg$o++ --> ethernetline --> r1.ethg$i++;
        hub.pppg$i++ <-- ethernetline <-- r1.ethg$o++;

        r1.ethg$o++ --> ethernetline --> r2.ethg$i++;
        r1.ethg$i++ <-- ethernetline <-- r2.ethg$o++;

        r2.ethg$o++ --> ethernetline --> r3.ethg$i++;
        r2.ethg$i++ <-- ethernetline <-- r3.ethg$o++;

        r3.ethg$o++ --> ethernetline --> srv.ethg$i++;
        r3.ethg$i++ <-- ethernetline <-- srv.ethg$o++;

        // Mixing ethernet and ppp currently doesn't work, due to a bug in
        // FlatNetworkConfigurator6::determineGateIndex.
        //
        // r1.pppg$o++ --> fiberline --> r2.pppg$i++;
        // r1.pppg$i++ <-- fiberline <-- r2.pppg$o++;
        //
        // r2.pppg$o++ --> fiberline --> r3.pppg$i++;
        // r2.pppg$i++ <-- fiberline <-- r3.pppg$o++;
        //
        // r3.pppg$o++ --> fiberline --> srv.pppg$i++;
        // r3.pppg$i++ <-- fiberline <-- srv.pppg$o++;

}

