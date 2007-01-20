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


import "NetworkConfigurator";
import "StandardHost";
import "RSVP_LSR";
import "FailureManager";
import "ScenarioManager";

//
// Example network to demonstrate \RSVP-TE.
//
// See the README file in the model directory for scenario description.
//
network RSVPTE4
{
    submodules:
        configurator: NetworkConfigurator {
            parameters:
                moduleTypes = "RSVP_LSR StandardHost";
                @display("p=115,50");
        };
        LSR1: RSVP_LSR {
            parameters:
                @display("p=160,167");
        };
        LSR2: RSVP_LSR {
            parameters:
                @display("p=254,255");
        };
        LSR3: RSVP_LSR {
            parameters:
                @display("p=253,78");
        };
        LSR4: RSVP_LSR {
            parameters:
                @display("p=358,167");
        };
        LSR5: RSVP_LSR {
            parameters:
                @display("p=460,167");
        };
        LSR6: RSVP_LSR {
            parameters:
                @display("p=400,300");
        };
        LSR7: RSVP_LSR {
            parameters:
                @display("p=400,50");
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
                @display("p=195,50");
        };
        failureManager: FailureManager {
            parameters:
                @display("p=500,50");
        //nam: NAMTraceWriter;
        //    display: "p=152,280;i=old/floppy1";
        };
    connections allowunconnected:
        LSR1.pppg$o++ --> {  delay = 15ms; datarate = 600000; } --> LSR2.pppg$i++;
        LSR1.pppg$i++ <-- {  delay = 15ms; datarate = 600000; } <-- LSR2.pppg$o++;

        LSR1.pppg$o++ --> {  delay = 5ms; datarate = 600000; } --> LSR3.pppg$i++;
        LSR1.pppg$i++ <-- {  delay = 5ms; datarate = 600000; } <-- LSR3.pppg$o++;

        host2.pppg$i++ <-- {  delay = 10ms; datarate = 600000; } <-- LSR1.pppg$o++;
        host2.pppg$o++ --> {  delay = 10ms; datarate = 600000; } --> LSR1.pppg$i++;

        host1.pppg$i++ <-- {  delay = 10ms; datarate = 600000; } <-- LSR1.pppg$o++;
        host1.pppg$o++ --> {  delay = 10ms; datarate = 600000; } --> LSR1.pppg$i++;

        LSR2.pppg$o++ --> {  delay = 5ms; datarate = 600000; } --> LSR4.pppg$i++;
        LSR2.pppg$i++ <-- {  delay = 5ms; datarate = 600000; } <-- LSR4.pppg$o++;

        LSR3.pppg$o++ --> {  delay = 5ms; datarate = 600000; } --> LSR4.pppg$i++;
        LSR3.pppg$i++ <-- {  delay = 5ms; datarate = 600000; } <-- LSR4.pppg$o++;

        LSR4.pppg$o++ --> {  delay = 5ms; datarate = 600000; } --> LSR5.pppg$i++;
        LSR4.pppg$i++ <-- {  delay = 5ms; datarate = 600000; } <-- LSR5.pppg$o++;

        LSR5.pppg$o++ --> {  delay = 10ms; datarate = 600000; } --> host3.pppg$i++;
        LSR5.pppg$i++ <-- {  delay = 10ms; datarate = 600000; } <-- host3.pppg$o++;

        LSR5.pppg$o++ --> {  delay = 10ms; datarate = 600000; } --> host4.pppg$i++;
        LSR5.pppg$i++ <-- {  delay = 10ms; datarate = 600000; } <-- host4.pppg$o++;

        LSR2.pppg$o++ --> {  delay = 10ms; datarate = 600000; } --> LSR6.pppg$i++;
        LSR2.pppg$i++ <-- {  delay = 10ms; datarate = 600000; } <-- LSR6.pppg$o++;

        LSR5.pppg$o++ --> {  delay = 10ms; datarate = 600000; } --> LSR6.pppg$i++;
        LSR5.pppg$i++ <-- {  delay = 10ms; datarate = 600000; } <-- LSR6.pppg$o++;

        LSR3.pppg$o++ --> {  delay = 10ms; datarate = 600000; } --> LSR7.pppg$i++;
        LSR3.pppg$i++ <-- {  delay = 10ms; datarate = 600000; } <-- LSR7.pppg$o++;

        LSR5.pppg$o++ --> {  delay = 10ms; datarate = 600000; } --> LSR7.pppg$i++;
        LSR5.pppg$i++ <-- {  delay = 10ms; datarate = 600000; } <-- LSR7.pppg$o++;

        host5.pppg$i++ <-- {  delay = 10ms; datarate = 600000; } <-- LSR1.pppg$o++;
        host5.pppg$o++ --> {  delay = 10ms; datarate = 600000; } --> LSR1.pppg$i++;
}

