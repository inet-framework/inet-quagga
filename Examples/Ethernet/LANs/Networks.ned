//
// Copyright (C) 2003 CTIE, Monash University
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

import "EtherBus";
import "EtherHub";
import "EtherHost";
import "EtherHost2";
import "EtherSwitch";
import "EtherDuplexSwitch";
import "ChannelInstaller";


//
// Sample Ethernet LAN containing eight hosts, a switch and a bus.
//
network MixedLAN
{
    submodules:
        channelInstaller: ChannelInstaller {
            parameters:
                channelClass = "ThruputMeteringChannel";
                channelAttrs = "format=#N";
                @display("p=75,52");
        };
        bus: EtherBus {
            parameters:
                positions = "10 20 24 35 40 48";
                propagationSpeed = 200000000; // 1us = 200m
                @display("p=277,182;b=424,6;o=#408060");
            gates:
                ethg[6];
        };
        busHostA: EtherHost {
            parameters:
                @display("p=122,118");
        };
        busHostB: EtherHost {
            parameters:
                @display("p=210,118");
        };
        busHostC: EtherHost {
            parameters:
                @display("p=338,238");
        };
        busHostD: EtherHost {
            parameters:
                @display("p=426,238");
        };
        switchHostA: EtherHost {
            parameters:
                @display("p=82,300");
        };
        switchHostB: EtherHost {
            parameters:
                @display("p=162,300");
        };
        switchHostC: EtherHost {
            parameters:
                @display("p=234,300");
        };
        switchHostD: EtherHost {
            parameters:
                @display("p=306,300");
        };
        switch: EtherSwitch {
            parameters:
                @display("p=194,236");
            gates:
                ethg[5];
        };
        hubHostA: EtherHost {
            parameters:
                @display("p=297,55");
        };
        hubHostB: EtherHost {
            parameters:
                @display("p=365,55");
        };
        hubHostC: EtherHost {
            parameters:
                @display("p=430,55");
        };
        hub: EtherHub {
            parameters:
                @display("p=362,132");
            gates:
                ethg[4];
        };
    connections:
        bus.ethg$i[0] <-- busHostA.ethg$o;
        bus.ethg$o[0] --> busHostA.ethg$i;

        bus.ethg$i[1] <-- busHostB.ethg$o;
        bus.ethg$o[1] --> busHostB.ethg$i;

        bus.ethg$i[2] <-- switch.ethg$o[4];
        bus.ethg$o[2] --> switch.ethg$i[4];

        bus.ethg$i[3] <-- busHostC.ethg$o;
        bus.ethg$o[3] --> busHostC.ethg$i;

        bus.ethg$i[4] <-- hub.ethg$o[3];
        bus.ethg$o[4] --> hub.ethg$i[3];

        bus.ethg$i[5] <-- busHostD.ethg$o;
        bus.ethg$o[5] --> busHostD.ethg$i;

        switch.ethg$o[0] --> {  delay = 0.1us; } --> switchHostA.ethg$i;
        switch.ethg$i[0] <-- {  delay = 0.1us; } <-- switchHostA.ethg$o;
        switch.ethg$o[1] --> {  delay = 0.1us; } --> switchHostB.ethg$i;
        switch.ethg$i[1] <-- {  delay = 0.1us; } <-- switchHostB.ethg$o;
        switch.ethg$o[2] --> {  delay = 0.1us; } --> switchHostC.ethg$i;
        switch.ethg$i[2] <-- {  delay = 0.1us; } <-- switchHostC.ethg$o;
        switch.ethg$o[3] --> {  delay = 0.1us; } --> switchHostD.ethg$i;
        switch.ethg$i[3] <-- {  delay = 0.1us; } <-- switchHostD.ethg$o;

        hub.ethg$o[0] --> {  delay = 0.1us; } --> hubHostA.ethg$i;
        hub.ethg$i[0] <-- {  delay = 0.1us; } <-- hubHostA.ethg$o;
        hub.ethg$o[1] --> {  delay = 0.3us; } --> hubHostB.ethg$i;
        hub.ethg$i[1] <-- {  delay = 0.3us; } <-- hubHostB.ethg$o;
        hub.ethg$o[2] --> {  delay = 0.2us; } --> hubHostC.ethg$i;
        hub.ethg$i[2] <-- {  delay = 0.2us; } <-- hubHostC.ethg$o;
}


//
// Sample Ethernet LAN: two hosts directly connected to each other
// via twisted pair.
//
network TwoHosts
{
    submodules:
        hostA: EtherHost {
            parameters:
                @display("p=60,160");
        };
        hostB: EtherHost {
            parameters:
                @display("p=200,140");
        };
    connections:
        hostA.ethg$o --> {  delay = 0.5us; } --> hostB.ethg$i;
        hostB.ethg$o --> {  delay = 0.5us; } --> hostA.ethg$i;
}


//
// Sample Ethernet LAN: four hosts connected to a switch.
//
network SwitchedLAN
{
    submodules:
        hostA: EtherHost {
            parameters:
                @display("p=161,55");
        };
        hostB: EtherHost {
            parameters:
                @display("p=253,125");
        };
        hostC: EtherHost {
            parameters:
                @display("p=158,199");
        };
        hostD: EtherHost {
            parameters:
                @display("p=59,127");
        };
        switch: EtherSwitch {
            parameters:
                @display("p=162,124");
            gates:
                //REMOVE THIS LINE
                ethg[4];
        };
    connections:
        switch.ethg$o[0] --> {  delay = 0.1us; } --> hostA.ethg$i;
        switch.ethg$i[0] <-- {  delay = 0.1us; } <-- hostA.ethg$o;
        switch.ethg$o[1] --> {  delay = 0.1us; } --> hostB.ethg$i;
        switch.ethg$i[1] <-- {  delay = 0.1us; } <-- hostB.ethg$o;
        switch.ethg$o[2] --> {  delay = 0.1us; } --> hostC.ethg$i;
        switch.ethg$i[2] <-- {  delay = 0.1us; } <-- hostC.ethg$o;
        switch.ethg$o[3] --> {  delay = 0.1us; } --> hostD.ethg$i;
        switch.ethg$i[3] <-- {  delay = 0.1us; } <-- hostD.ethg$o;
}


//
// Sample Ethernet LAN: four hosts connected by a hub.
//
network HubLAN
{
    submodules:
        hostA: EtherHost {
            parameters:
                @display("p=161,55");
        };
        hostB: EtherHost {
            parameters:
                @display("p=253,125");
        };
        hostC: EtherHost {
            parameters:
                @display("p=158,199");
        };
        hostD: EtherHost {
            parameters:
                @display("p=59,127");
        };
        hub: EtherHub {
            parameters:
                @display("p=162,124");
            gates:
                //REMOVE THIS LINE
                ethg[4];
        };
    connections:
        hub.ethg$o[0] --> {  delay = 0.1us; } --> hostA.ethg$i;
        hub.ethg$i[0] <-- {  delay = 0.1us; } <-- hostA.ethg$o;
        hub.ethg$o[1] --> {  delay = 0.3us; } --> hostB.ethg$i;
        hub.ethg$i[1] <-- {  delay = 0.3us; } <-- hostB.ethg$o;
        hub.ethg$o[2] --> {  delay = 0.4us; } --> hostC.ethg$i;
        hub.ethg$i[2] <-- {  delay = 0.4us; } <-- hostC.ethg$o;
        hub.ethg$o[3] --> {  delay = 0.2us; } --> hostD.ethg$i;
        hub.ethg$i[3] <-- {  delay = 0.2us; } <-- hostD.ethg$o;
}


//
// Sample Ethernet LAN: four hosts on a bus.
//
network BusLAN
{
    submodules:
        hostA: EtherHost {
            parameters:
                @display("p=100,150");
        };
        hostB: EtherHost {
            parameters:
                @display("p=200,150");
        };
        hostC: EtherHost {
            parameters:
                @display("p=300,150");
        };
        hostD: EtherHost {
            parameters:
                @display("p=400,150");
        };
        bus: EtherBus {
            parameters:
                positions = "0 10 20 30";
                propagationSpeed = 200000000;
                @display("p=250,100;b=400,6;o=#408060");
            gates:
                //REMOVE THIS LINE
                ethg[4];
        };
    connections:
        bus.ethg$i[0] <-- hostA.ethg$o;
        bus.ethg$o[0] --> hostA.ethg$i;
        bus.ethg$i[1] <-- hostB.ethg$o;
        bus.ethg$o[1] --> hostB.ethg$i;
        bus.ethg$i[2] <-- hostC.ethg$o;
        bus.ethg$o[2] --> hostC.ethg$i;
        bus.ethg$i[3] <-- hostD.ethg$o;
        bus.ethg$o[3] --> hostD.ethg$i;
}

channel ethernetline extends cBasicChannel
{
    parameters:
        delay = 0.1us;
        datarate = 10*1000000;
}

network SwitchedDuplexLAN
{
    submodules:
        hostA: EtherHost2 {
            parameters:
                @display("p=161,55");
        };
        hostB: EtherHost2 {
            parameters:
                @display("p=253,125");
        };
        hostC: EtherHost2 {
            parameters:
                @display("p=158,199");
        };
        hostD: EtherHost2 {
            parameters:
                @display("p=59,127");
        };
        switch: EtherSwitch2 {
            parameters:
                @display("p=162,124");
            gates:
                //REMOVE THIS LINE
                ethg[4];
        };
    connections:
        switch.ethg$o[0] --> ethernetline --> hostA.ethg$i;
        switch.ethg$i[0] <-- ethernetline <-- hostA.ethg$o;
        switch.ethg$o[1] --> ethernetline --> hostB.ethg$i;
        switch.ethg$i[1] <-- ethernetline <-- hostB.ethg$o;
        switch.ethg$o[2] --> ethernetline --> hostC.ethg$i;
        switch.ethg$i[2] <-- ethernetline <-- hostC.ethg$o;
        switch.ethg$o[3] --> ethernetline --> hostD.ethg$i;
        switch.ethg$i[3] <-- ethernetline <-- hostD.ethg$o;
}

