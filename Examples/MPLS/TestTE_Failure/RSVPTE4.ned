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
import "RSVP_LSR";
import "FailureManager";
import "ScenarioManager";
import "NAMTrace";

//
// Example network to demonstrate \RSVP-TE.
//
// See the README file in the model directory for scenario description.
//
network RSVPTE4
{
    submodules:
        nam: NAMTrace {
            parameters:
                @display("p=152,280");

        };
        LSR1: RSVP_LSR {
            parameters:
                peers = "ppp0 ppp1";
                @display("p=160,167");
            gates:
                in[5];
                out[5];
        };
        LSR2: RSVP_LSR {
            parameters:
                peers = "ppp0 ppp1 ppp2";
                @display("p=254,255");
            gates:
                in[3];
                out[3];
        };
        LSR3: RSVP_LSR {
            parameters:
                peers = "ppp0 ppp1 ppp2";
                @display("p=253,78");
            gates:
                in[3];
                out[3];
        };
        LSR4: RSVP_LSR {
            parameters:
                peers = "ppp0 ppp1 ppp2";
                @display("p=358,167");
            gates:
                in[3];
                out[3];
        };
        LSR5: RSVP_LSR {
            parameters:
                peers = "ppp0 ppp3 ppp4";
                @display("p=460,167");
            gates:
                in[5];
                out[5];
        };
        LSR6: RSVP_LSR {
            parameters:
                peers = "ppp0 ppp1";
                @display("p=400,300");
            gates:
                in[2];
                out[2];
        };
        LSR7: RSVP_LSR {
            parameters:
                peers = "ppp0 ppp1";
                @display("p=400,50");
            gates:
                in[2];
                out[2];
        };
        host1: StandardHost { // client
            parameters:
                @display("p=71,80;i=device/pc2");
        };
        host2: StandardHost { // client
            parameters:
                @display("p=72,153;i=device/pc2");
        };
        host3: StandardHost { // server
            parameters:
                @display("p=570,88;i=device/server");
        };
        host4: StandardHost { // server
            parameters:
                @display("p=562,256;i=device/server");
        };
        host5: StandardHost { // client
            parameters:
                @display("p=73,233;i=device/pc2");
        };
        scenarioManager: ScenarioManager {
            parameters:
                @display("p=150,50");
        };
        failureManager: FailureManager {
            parameters:
                @display("p=500,50");
        };
    connections allowunconnected:
        LSR1.pppg$o[0] --> {  delay = 15ms; datarate = 600000; } --> LSR2.pppg$i[0];
        LSR1.pppg$i[0] <-- {  delay = 15ms; datarate = 600000; } <-- LSR2.pppg$o[0];

        LSR1.pppg$o[1] --> {  delay = 5ms; datarate = 600000; } --> LSR3.pppg$i[0];
        LSR1.pppg$i[1] <-- {  delay = 5ms; datarate = 600000; } <-- LSR3.pppg$o[0];

        host2.pppg$i++ <-- {  delay = 10ms; datarate = 600000; } <-- LSR1.pppg$o[2];
        host2.pppg$o++ --> {  delay = 10ms; datarate = 600000; } --> LSR1.pppg$i[2];

        host1.pppg$i++ <-- {  delay = 10ms; datarate = 600000; } <-- LSR1.pppg$o[3];
        host1.pppg$o++ --> {  delay = 10ms; datarate = 600000; } --> LSR1.pppg$i[3];

        LSR2.pppg$o[1] --> {  delay = 5ms; datarate = 600000; } --> LSR4.pppg$i[0];
        LSR2.pppg$i[1] <-- {  delay = 5ms; datarate = 600000; } <-- LSR4.pppg$o[0];

        LSR3.pppg$o[1] --> {  delay = 5ms; datarate = 600000; } --> LSR4.pppg$i[2];
        LSR3.pppg$i[1] <-- {  delay = 5ms; datarate = 600000; } <-- LSR4.pppg$o[2];

        LSR4.pppg$o[1] --> {  delay = 5ms; datarate = 600000; } --> LSR5.pppg$i[0];
        LSR4.pppg$i[1] <-- {  delay = 5ms; datarate = 600000; } <-- LSR5.pppg$o[0];

        LSR5.pppg$o[1] --> {  delay = 10ms; datarate = 600000; } --> host3.pppg$i++;
        LSR5.pppg$i[1] <-- {  delay = 10ms; datarate = 600000; } <-- host3.pppg$o++;

        LSR5.pppg$o[2] --> {  delay = 10ms; datarate = 600000; } --> host4.pppg$i++;
        LSR5.pppg$i[2] <-- {  delay = 10ms; datarate = 600000; } <-- host4.pppg$o++;

        LSR2.pppg$o[2] --> {  delay = 10ms; datarate = 600000; } --> LSR6.pppg$i[0];
        LSR2.pppg$i[2] <-- {  delay = 10ms; datarate = 600000; } <-- LSR6.pppg$o[0];

        LSR5.pppg$o[3] --> {  delay = 10ms; datarate = 600000; } --> LSR6.pppg$i[1];
        LSR5.pppg$i[3] <-- {  delay = 10ms; datarate = 600000; } <-- LSR6.pppg$o[1];

        LSR3.pppg$o[2] --> {  delay = 10ms; datarate = 600000; } --> LSR7.pppg$i[0];
        LSR3.pppg$i[2] <-- {  delay = 10ms; datarate = 600000; } <-- LSR7.pppg$o[0];

        LSR5.pppg$o[4] --> {  delay = 10ms; datarate = 600000; } --> LSR7.pppg$i[1];
        LSR5.pppg$i[4] <-- {  delay = 10ms; datarate = 600000; } <-- LSR7.pppg$o[1];

        host5.pppg$i++ <-- {  delay = 10ms; datarate = 600000; } <-- LSR1.pppg$o[4];
        host5.pppg$o++ --> {  delay = 10ms; datarate = 600000; } --> LSR1.pppg$i[4];
}

