//
// This library is free software, you can redistribute it
// and/or modify
// it under  the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation;
// either version 2 of the License, or any later version.
// The library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//


import "StandardHost";
import "LDP_LSR";
import "FailureManager";
import "ScenarioManager";
import "NAMTrace";

network LDPTEST
{
    submodules:
        nam: NAMTrace {
            parameters:
                @display("p=152,280");

        };
        LSR1: LDP_LSR {
            parameters:
                peers = "ppp0 ppp1 ppp2";
                @display("p=150,200");
            gates:
                //REMOVE THIS LINE
                pppg[4];
        };
        LSR2: LDP_LSR {
            parameters:
                peers = "ppp0 ppp1 ppp2 ppp3";
                @display("p=250,200");
            gates:
                //REMOVE THIS LINE
                pppg[4];
        };
        LSR3: LDP_LSR {
            parameters:
                peers = "ppp0 ppp1 ppp2";
                @display("p=350,200");
            gates:
                //REMOVE THIS LINE
                pppg[4];
        };
        LSR4: LDP_LSR {
            parameters:
                peers = "ppp0 ppp1 ppp2";
                @display("p=250,100");
            gates:
                //REMOVE THIS LINE
                pppg[4];
        };
        LSR5: LDP_LSR {
            parameters:
                peers = "ppp0 ppp1 ppp2";
                @display("p=250,300");

            gates:
                //REMOVE THIS LINE
                pppg[4];
        };
        host1: StandardHost { // client
            parameters:
                @display("p=40,200;i=device/pc2");
        };
        host2: StandardHost { // client
            parameters:
                @display("p=440,200;i=device/pc2");
        };
        host3: StandardHost { // client
            parameters:
                @display("p=250,10;i=device/pc2");
        };
        host4: StandardHost { // client
            parameters:
                @display("p=250,390;i=device/pc2");

        };
        scenarioManager: ScenarioManager {
            parameters:
                @display("p=150,50");

        };
        failureManager: FailureManager {
            parameters:
                @display("p=350,50");

        };
    connections allowunconnected:
        LSR1.pppg$o[0] --> {  delay = 15ms; datarate = 600000; } --> LSR2.pppg$i[0];
        LSR1.pppg$i[0] <-- {  delay = 15ms; datarate = 600000; } <-- LSR2.pppg$o[0];

        LSR1.pppg$o[1] --> {  delay = 5ms; datarate = 600000; } --> LSR4.pppg$i[0];
        LSR1.pppg$i[1] <-- {  delay = 5ms; datarate = 600000; } <-- LSR4.pppg$o[0];

        LSR1.pppg$o[2] --> {  delay = 5ms; datarate = 600000; } --> LSR5.pppg$i[0];
        LSR1.pppg$i[2] <-- {  delay = 5ms; datarate = 600000; } <-- LSR5.pppg$o[0];

        LSR2.pppg$o[1] --> {  delay = 5ms; datarate = 600000; } --> LSR3.pppg$i[0];
        LSR2.pppg$i[1] <-- {  delay = 5ms; datarate = 600000; } <-- LSR3.pppg$o[0];

        LSR2.pppg$o[2] --> {  delay = 5ms; datarate = 600000; } --> LSR4.pppg$i[1];
        LSR2.pppg$i[2] <-- {  delay = 5ms; datarate = 600000; } <-- LSR4.pppg$o[1];

        LSR2.pppg$o[3] --> {  delay = 5ms; datarate = 600000; } --> LSR5.pppg$i[1];
        LSR2.pppg$i[3] <-- {  delay = 5ms; datarate = 600000; } <-- LSR5.pppg$o[1];

        LSR3.pppg$o[1] --> {  delay = 10ms; datarate = 600000; } --> LSR4.pppg$i[2];
        LSR3.pppg$i[1] <-- {  delay = 10ms; datarate = 600000; } <-- LSR4.pppg$o[2];

        LSR3.pppg$o[2] --> {  delay = 10ms; datarate = 600000; } --> LSR5.pppg$i[2];
        LSR3.pppg$i[2] <-- {  delay = 10ms; datarate = 600000; } <-- LSR5.pppg$o[2];

        host1.pppg$i++ <-- {  delay = 10ms; datarate = 600000; } <-- LSR1.pppg$o[3];
        host1.pppg$o++ --> {  delay = 10ms; datarate = 600000; } --> LSR1.pppg$i[3];

        host2.pppg$i++ <-- {  delay = 10ms; datarate = 600000; } <-- LSR3.pppg$o[3];
        host2.pppg$o++ --> {  delay = 10ms; datarate = 600000; } --> LSR3.pppg$i[3];

        host3.pppg$i++ <-- {  delay = 10ms; datarate = 600000; } <-- LSR4.pppg$o[3];
        host3.pppg$o++ --> {  delay = 10ms; datarate = 600000; } --> LSR4.pppg$i[3];

        host4.pppg$i++ <-- {  delay = 10ms; datarate = 600000; } <-- LSR5.pppg$o[3];
        host4.pppg$o++ --> {  delay = 10ms; datarate = 600000; } --> LSR5.pppg$i[3];
}

