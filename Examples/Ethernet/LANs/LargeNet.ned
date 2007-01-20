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
import "EtherSwitch";
import "ChannelInstaller";

channel cable extends cBasicChannel
{
    parameters:
        delay = 0.1us;
}


//
// Several hosts on an Ethernet hub
//
module SmallLAN
{
    parameters:
        int h; // number of hosts on the hub
        @display("i=cloud_s");
    gates:
        input in;
        output out;
    submodules:
        hub: EtherHub { 
            @display("is=s");
        };
        host[h]: EtherHost {
            @display("is=s");
        };
    connections:
        for i=0..h-1 {
            hub.out++ --> cable --> host[i].in;
            hub.in++ <-- cable <-- host[i].out;
        };
        hub.out++ --> out;
        hub.in++ <-- in;
}


//
// Several hosts and an Ethernet hub on a switch
//
module MediumLAN
{
    parameters:
        int n; // number of hosts on the switch
        int h; // number of hosts on the hub
        @display("i=cloud_s");
    gates:
        input in;
        output out;
    submodules:
        switch: EtherSwitch {
            @display("is=s");
        };
        host[n]: EtherHost {
            @display("is=s");
        };
        hub: EtherHub {
            @display("is=s");
        };
        hhost[h]: EtherHost {
            @display("is=s");
        };
    connections:
        for i=0..n-1 {
            switch.out++ --> cable --> host[i].in;
            switch.in++ <-- cable <-- host[i].out;
        };

        switch.out++ --> out;
        switch.in++ <-- in;

        for i=0..h-1 {
            hub.out++ --> cable --> hhost[i].in;
            hub.in++ <-- cable <-- hhost[i].out;
        };

        switch.out++ --> cable --> hub.in++;
        switch.in++ <-- cable <-- hub.out++;

}


//
// Several hosts and an Ethernet hub on a switch. One port of the hub
// connect to a 10Base2 segment.
//
module LargeLAN
{
    parameters:
        int n; // number of hosts on the switch
        int h; // number of hosts on the hub
        int b; // number of hosts on the bus
        @display("i=cloud");
    gates:
        input in;
        output out;
    submodules:
        switch: EtherSwitch {
            @display("is=s");
        };
        host[n]: EtherHost {
            @display("is=s");
        };
        hub: EtherHub {
            @display("is=s");
        };
        hhost[h]: EtherHost {
            @display("is=s");
        };
        bus: EtherBus {
            parameters:
                positions = "5 10 15"; // every 5 meters
                propagationSpeed = 200000000;  // 1us = 200m
                @display("b=424,6;o=#408060");
        };
        bhost[b]: EtherHost {
            parameters:
                @display("is=s;p=,,r");
        };
    connections:
        for i=0..n-1 {
            switch.out++ --> cable --> host[i].in;
            switch.in++ <-- cable <-- host[i].out;
        };

        switch.out++ --> out;
        switch.in++ <-- in;

        for i=0..h-1 {
            hub.out++ --> cable --> hhost[i].in;
            hub.in++ <-- cable <-- hhost[i].out;
        };

        switch.out++ --> cable --> hub.in++;
        switch.in++ <-- cable <-- hub.out++;

        for i=0..b-1 {
            bus.out++ --> bhost[i].in;
            bus.in++ <-- bhost[i].out;
        };

        bus.out++ --> hub.in++;
        bus.in++ <-- hub.out++;

}

//
// A large Ethernet LAN -- see model description
// <a href="largenet.html">here</a>.
//
network LargeNet
{
    parameters:
        int n;   // length of the "backbone" (n>5!)
        int bbs; // number of small LANs on "backbone" switches
        int bbm; // number of medium LANs on "backbone" switches
        int bbl; // number of large LANs on "backbone" switches
        int as;  // number of small LANs on switch A
        int am;  // number of medium LANs on switch A
        int al;  // number of large LANs on switch A
        int bs;  // number of small LANs on switch B
        int bm;  // number of medium LANs on switch B
        int bl;  // number of large LANs on switch B
        int cs;  // number of small LANs on switch C
        int cm;  // number of medium LANs on switch C
        int cl;  // number of large LANs on switch C
        int ds;  // number of small LANs on switch D
        int dm;  // number of medium LANs on switch D
        int dl;  // number of large LANs on switch D
    submodules:
        switchBB[n]: EtherSwitch {
            @display("is=s");
        };
        slanBB[n*bbs]: SmallLAN;
        mlanBB[n*bbm]: MediumLAN;
        llanBB[n*bbl]: LargeLAN;
        switchA: EtherSwitch;
        serverA: EtherHost;
        slanA[as]: SmallLAN;
        mlanA[am]: MediumLAN;
        llanA[al]: LargeLAN;
        switchB: EtherSwitch;
        serverB: EtherHost;
        slanB[bs]: SmallLAN;
        mlanB[bm]: MediumLAN;
        llanB[bl]: LargeLAN;
        switchC: EtherSwitch;
        serverC: EtherHost;
        slanC[cs]: SmallLAN;
        mlanC[cm]: MediumLAN;
        llanC[cl]: LargeLAN;
        switchD: EtherSwitch;
        serverD: EtherHost;
        slanD[ds]: SmallLAN;
        mlanD[dm]: MediumLAN;
        llanD[dl]: LargeLAN;
    connections allowunconnected:
        // "backbone" switches
        for k=0..n-1, for i=0..bbs-1 {
            switchBB[k].out++ --> cable --> slanBB[k*bbs+i].in;
            switchBB[k].in++ <-- cable <-- slanBB[k*bbs+i].out;
        };
        for k=0..n-1, for i=0..bbm-1 {
            switchBB[k].out++ --> cable --> mlanBB[k*bbm+i].in;
            switchBB[k].in++ <-- cable <-- mlanBB[k*bbm+i].out;
        };
        for k=0..n-1, for i=0..bbl-1 {
            switchBB[k].out++ --> cable --> llanBB[k*bbl+i].in;
            switchBB[k].in++ <-- cable <-- llanBB[k*bbl+i].out;
        };
        for k=0..n-2 {
            switchBB[k].out++ --> cable --> switchBB[k+1].in++;
            switchBB[k].in++ <-- cable <-- switchBB[k+1].out++;
        };

        // switch A
        for i=0..as-1 {
            switchA.out++ --> cable --> slanA[i].in;
            switchA.in++ <-- cable <-- slanA[i].out;
        };
        for i=0..am-1 {
            switchA.out++ --> cable --> mlanA[i].in;
            switchA.in++ <-- cable <-- mlanA[i].out;
        };
        for i=0..al-1 {
            switchA.out++ --> cable --> llanA[i].in;
            switchA.in++ <-- cable <-- llanA[i].out;
        };
        switchA.out++ --> cable --> serverA.in;
        switchA.in++ <-- cable <-- serverA.out;

        // switch B
        for i=0..bs-1 {
            switchB.out++ --> cable --> slanB[i].in;
            switchB.in++ <-- cable <-- slanB[i].out;
        };
        for i=0..bm-1 {
            switchB.out++ --> cable --> mlanB[i].in;
            switchB.in++ <-- cable <-- mlanB[i].out;
        };
        for i=0..bl-1 {
            switchB.out++ --> cable --> llanB[i].in;
            switchB.in++ <-- cable <-- llanB[i].out;
        };
        switchB.out++ --> cable --> serverB.in;
        switchB.in++ <-- cable <-- serverB.out;

        // switch C
        for i=0..cs-1 {
            switchC.out++ --> cable --> slanC[i].in;
            switchC.in++ <-- cable <-- slanC[i].out;
        };
        for i=0..cm-1 {
            switchC.out++ --> cable --> mlanC[i].in;
            switchC.in++ <-- cable <-- mlanC[i].out;
        };
        for i=0..cl-1 {
            switchC.out++ --> cable --> llanC[i].in;
            switchC.in++ <-- cable <-- llanC[i].out;
        };
        switchC.out++ --> cable --> serverC.in;
        switchC.in++ <-- cable <-- serverC.out;

        // switch D
        for i=0..ds-1 {
            switchD.out++ --> cable --> slanD[i].in;
            switchD.in++ <-- cable <-- slanD[i].out;
        };
        for i=0..dm-1 {
            switchD.out++ --> cable --> mlanD[i].in;
            switchD.in++ <-- cable <-- mlanD[i].out;
        };
        for i=0..dl-1 {
            switchD.out++ --> cable --> llanD[i].in;
            switchD.in++ <-- cable <-- llanD[i].out;
        };
        switchD.out++ --> cable --> serverD.in;
        switchD.in++ <-- cable <-- serverD.out;

        // connect switches
        switchA.out++ --> cable --> switchB.in++;
        switchA.in++ <-- cable <-- switchB.out++;

        switchB.out++ --> cable --> switchC.in++;
        switchB.in++ <-- cable <-- switchC.out++;

        switchC.out++ --> cable --> switchD.in++;
        switchC.in++ <-- cable <-- switchD.out++;

        switchB.out++ --> cable --> switchBB[4].in++;
        switchB.in++ <-- cable <-- switchBB[4].out++;

}


