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
        LSR1.out++ --> {  delay = 15ms; datarate = 600000; } --> LSR2.in++;
        LSR1.in++ <-- {  delay = 15ms; datarate = 600000; } <-- LSR2.out++;

        LSR1.out++ --> {  delay = 5ms; datarate = 600000; } --> LSR3.in++;
        LSR1.in++ <-- {  delay = 5ms; datarate = 600000; } <-- LSR3.out++;

        host2.in++ <-- {  delay = 10ms; datarate = 600000; } <-- LSR1.out++;
        host2.out++ --> {  delay = 10ms; datarate = 600000; } --> LSR1.in++;

        host1.in++ <-- {  delay = 10ms; datarate = 600000; } <-- LSR1.out++;
        host1.out++ --> {  delay = 10ms; datarate = 600000; } --> LSR1.in++;

        LSR2.out++ --> {  delay = 5ms; datarate = 600000; } --> LSR4.in++;
        LSR2.in++ <-- {  delay = 5ms; datarate = 600000; } <-- LSR4.out++;

        LSR3.out++ --> {  delay = 5ms; datarate = 600000; } --> LSR4.in++;
        LSR3.in++ <-- {  delay = 5ms; datarate = 600000; } <-- LSR4.out++;

        LSR4.out++ --> {  delay = 5ms; datarate = 600000; } --> LSR5.in++;
        LSR4.in++ <-- {  delay = 5ms; datarate = 600000; } <-- LSR5.out++;

        LSR5.out++ --> {  delay = 10ms; datarate = 600000; } --> host3.in++;
        LSR5.in++ <-- {  delay = 10ms; datarate = 600000; } <-- host3.out++;

        LSR5.out++ --> {  delay = 10ms; datarate = 600000; } --> host4.in++;
        LSR5.in++ <-- {  delay = 10ms; datarate = 600000; } <-- host4.out++;

        LSR2.out++ --> {  delay = 10ms; datarate = 600000; } --> LSR6.in++;
        LSR2.in++ <-- {  delay = 10ms; datarate = 600000; } <-- LSR6.out++;

        LSR5.out++ --> {  delay = 10ms; datarate = 600000; } --> LSR6.in++;
        LSR5.in++ <-- {  delay = 10ms; datarate = 600000; } <-- LSR6.out++;

        LSR3.out++ --> {  delay = 10ms; datarate = 600000; } --> LSR7.in++;
        LSR3.in++ <-- {  delay = 10ms; datarate = 600000; } <-- LSR7.out++;

        LSR5.out++ --> {  delay = 10ms; datarate = 600000; } --> LSR7.in++;
        LSR5.in++ <-- {  delay = 10ms; datarate = 600000; } <-- LSR7.out++;

        host5.in++ <-- {  delay = 10ms; datarate = 600000; } <-- LSR1.out++;
        host5.out++ --> {  delay = 10ms; datarate = 600000; } --> LSR1.in++;
}

