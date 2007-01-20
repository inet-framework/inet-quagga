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
import "ThruputMeter";
import "FlatNetworkConfigurator";
import "ScenarioManager";
import "ChannelInstaller";

network REDTestTh
{
    submodules:
        channelInstaller: ChannelInstaller {
            parameters:
                channelClass = "ThruputMeteringChannel";
                channelAttrs = "format=b (u)";
                @display("p=327,40");
        };
        configurator: FlatNetworkConfigurator {
            parameters:
                moduleTypes = "Router StandardHost ThruputMeter";
                nonIPModuleTypes = "ThruputMeter";
                networkAddress = "145.236.0.0";
                netmask = "255.255.0.0";
                @display("p=149,40");
        };
        scenarioManager: ScenarioManager {
            parameters:
                @display("p=236,40");
        };
        r1: Router {
            parameters:
                @display("p=147,143");
        };
        r2: Router {
            parameters:
                @display("p=317,143");
        };
        s1: StandardHost {
            parameters:
                @display("p=68,64;i=device/laptop");
        };
        s2: StandardHost {
            parameters:
                @display("p=65,193;i=device/laptop");
        };
        s3: StandardHost {
            parameters:
                @display("p=421,83;i=device/laptop");
        };
        s4: StandardHost {
            parameters:
                @display("p=420,195;i=device/laptop");
        };
        th: ThruputMeter {
            parameters:
                @display("p=259,163");
        };
    connections allowunconnected:
        r1.pppg$o++ --> {  datarate = 1.5e6; delay = 20e-3; } --> th.in;
        th.out --> r2.pppg$i++;
        r1.pppg$i++ <-- {  datarate = 1.5e6; delay = 20e-3; } <-- r2.pppg$o++;

        s1.pppg++ <--> {  datarate = 10e6; delay = 2e-3; } <--> r1.pppg++;

        s2.pppg++ <--> {  datarate = 10e6; delay = 3e-3; } <--> r1.pppg++;

        s3.pppg++ <--> {  datarate = 10e6; delay = 4e-3; } <--> r2.pppg++;

        s4.pppg++ <--> {  datarate = 10e6; delay = 5e-3; } <--> r2.pppg++;

}

