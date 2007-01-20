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
                in[6];
                out[6];
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
                in[5];
                out[5];
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
                in[4];
                out[4];
        };
    connections:
        bus.pppg$i[0] <-- busHostA.out;
        bus.pppg$o[0] --> busHostA.in;

        bus.pppg$i[1] <-- busHostB.out;
        bus.pppg$o[1] --> busHostB.in;

        bus.pppg$i[2] <-- switch.pppg$o[4];
        bus.pppg$o[2] --> switch.pppg$i[4];

        bus.pppg$i[3] <-- busHostC.out;
        bus.pppg$o[3] --> busHostC.in;

        bus.pppg$i[4] <-- hub.pppg$o[3];
        bus.pppg$o[4] --> hub.pppg$i[3];

        bus.pppg$i[5] <-- busHostD.out;
        bus.pppg$o[5] --> busHostD.in;

        switch.pppg$o[0] --> {  delay = 0.1us; } --> switchHostA.in;
        switch.pppg$i[0] <-- {  delay = 0.1us; } <-- switchHostA.out;
        switch.pppg$o[1] --> {  delay = 0.1us; } --> switchHostB.in;
        switch.pppg$i[1] <-- {  delay = 0.1us; } <-- switchHostB.out;
        switch.pppg$o[2] --> {  delay = 0.1us; } --> switchHostC.in;
        switch.pppg$i[2] <-- {  delay = 0.1us; } <-- switchHostC.out;
        switch.pppg$o[3] --> {  delay = 0.1us; } --> switchHostD.in;
        switch.pppg$i[3] <-- {  delay = 0.1us; } <-- switchHostD.out;

        hub.pppg$o[0] --> {  delay = 0.1us; } --> hubHostA.in;
        hub.pppg$i[0] <-- {  delay = 0.1us; } <-- hubHostA.out;
        hub.pppg$o[1] --> {  delay = 0.3us; } --> hubHostB.in;
        hub.pppg$i[1] <-- {  delay = 0.3us; } <-- hubHostB.out;
        hub.pppg$o[2] --> {  delay = 0.2us; } --> hubHostC.in;
        hub.pppg$i[2] <-- {  delay = 0.2us; } <-- hubHostC.out;
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
        hostA.out --> {  delay = 0.5us; } --> hostB.in;
        hostB.out --> {  delay = 0.5us; } --> hostA.in;
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
                in[4];
                out[4];
        };
    connections:
        switch.pppg$o[0] --> {  delay = 0.1us; } --> hostA.in;
        switch.pppg$i[0] <-- {  delay = 0.1us; } <-- hostA.out;
        switch.pppg$o[1] --> {  delay = 0.1us; } --> hostB.in;
        switch.pppg$i[1] <-- {  delay = 0.1us; } <-- hostB.out;
        switch.pppg$o[2] --> {  delay = 0.1us; } --> hostC.in;
        switch.pppg$i[2] <-- {  delay = 0.1us; } <-- hostC.out;
        switch.pppg$o[3] --> {  delay = 0.1us; } --> hostD.in;
        switch.pppg$i[3] <-- {  delay = 0.1us; } <-- hostD.out;
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
                in[4];
                out[4];
        };
    connections:
        hub.pppg$o[0] --> {  delay = 0.1us; } --> hostA.in;
        hub.pppg$i[0] <-- {  delay = 0.1us; } <-- hostA.out;
        hub.pppg$o[1] --> {  delay = 0.3us; } --> hostB.in;
        hub.pppg$i[1] <-- {  delay = 0.3us; } <-- hostB.out;
        hub.pppg$o[2] --> {  delay = 0.4us; } --> hostC.in;
        hub.pppg$i[2] <-- {  delay = 0.4us; } <-- hostC.out;
        hub.pppg$o[3] --> {  delay = 0.2us; } --> hostD.in;
        hub.pppg$i[3] <-- {  delay = 0.2us; } <-- hostD.out;
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
                in[4];
                out[4];
        };
    connections:
        bus.pppg$i[0] <-- hostA.out;
        bus.pppg$o[0] --> hostA.in;
        bus.pppg$i[1] <-- hostB.out;
        bus.pppg$o[1] --> hostB.in;
        bus.pppg$i[2] <-- hostC.out;
        bus.pppg$o[2] --> hostC.in;
        bus.pppg$i[3] <-- hostD.out;
        bus.pppg$o[3] --> hostD.in;
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
                in[4];
                out[4];
        };
    connections:
        switch.pppg$o[0] --> ethernetline --> hostA.in;
        switch.pppg$i[0] <-- ethernetline <-- hostA.out;
        switch.pppg$o[1] --> ethernetline --> hostB.in;
        switch.pppg$i[1] <-- ethernetline <-- hostB.out;
        switch.pppg$o[2] --> ethernetline --> hostC.in;
        switch.pppg$i[2] <-- ethernetline <-- hostC.out;
        switch.pppg$o[3] --> ethernetline --> hostD.in;
        switch.pppg$i[3] <-- ethernetline <-- hostD.out;
}

