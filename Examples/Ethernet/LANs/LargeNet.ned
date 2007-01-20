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
            hub.pppg$o++ --> cable --> host[i].in;
            hub.pppg$i++ <-- cable <-- host[i].out;
        };
        hub.pppg$o++ --> out;
        hub.pppg$i++ <-- in;
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
            switch.pppg$o++ --> cable --> host[i].in;
            switch.pppg$i++ <-- cable <-- host[i].out;
        };

        switch.pppg$o++ --> out;
        switch.pppg$i++ <-- in;

        for i=0..h-1 {
            hub.pppg$o++ --> cable --> hhost[i].in;
            hub.pppg$i++ <-- cable <-- hhost[i].out;
        };

        switch.pppg$o++ --> cable --> hub.pppg$i++;
        switch.pppg$i++ <-- cable <-- hub.pppg$o++;

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
            switch.pppg$o++ --> cable --> host[i].in;
            switch.pppg$i++ <-- cable <-- host[i].out;
        };

        switch.pppg$o++ --> out;
        switch.pppg$i++ <-- in;

        for i=0..h-1 {
            hub.pppg$o++ --> cable --> hhost[i].in;
            hub.pppg$i++ <-- cable <-- hhost[i].out;
        };

        switch.pppg$o++ --> cable --> hub.pppg$i++;
        switch.pppg$i++ <-- cable <-- hub.pppg$o++;

        for i=0..b-1 {
            bus.pppg$o++ --> bhost[i].in;
            bus.pppg$i++ <-- bhost[i].out;
        };

        bus.pppg$o++ --> hub.pppg$i++;
        bus.pppg$i++ <-- hub.pppg$o++;

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
            switchBB[k].pppg$o++ --> cable --> slanBB[k*bbs+i].in;
            switchBB[k].pppg$i++ <-- cable <-- slanBB[k*bbs+i].out;
        };
        for k=0..n-1, for i=0..bbm-1 {
            switchBB[k].pppg$o++ --> cable --> mlanBB[k*bbm+i].in;
            switchBB[k].pppg$i++ <-- cable <-- mlanBB[k*bbm+i].out;
        };
        for k=0..n-1, for i=0..bbl-1 {
            switchBB[k].pppg$o++ --> cable --> llanBB[k*bbl+i].in;
            switchBB[k].pppg$i++ <-- cable <-- llanBB[k*bbl+i].out;
        };
        for k=0..n-2 {
            switchBB[k].pppg$o++ --> cable --> switchBB[k+1].pppg$i++;
            switchBB[k].pppg$i++ <-- cable <-- switchBB[k+1].pppg$o++;
        };

        // switch A
        for i=0..as-1 {
            switchA.pppg$o++ --> cable --> slanA[i].in;
            switchA.pppg$i++ <-- cable <-- slanA[i].out;
        };
        for i=0..am-1 {
            switchA.pppg$o++ --> cable --> mlanA[i].in;
            switchA.pppg$i++ <-- cable <-- mlanA[i].out;
        };
        for i=0..al-1 {
            switchA.pppg$o++ --> cable --> llanA[i].in;
            switchA.pppg$i++ <-- cable <-- llanA[i].out;
        };
        switchA.pppg$o++ --> cable --> serverA.in;
        switchA.pppg$i++ <-- cable <-- serverA.out;

        // switch B
        for i=0..bs-1 {
            switchB.pppg$o++ --> cable --> slanB[i].in;
            switchB.pppg$i++ <-- cable <-- slanB[i].out;
        };
        for i=0..bm-1 {
            switchB.pppg$o++ --> cable --> mlanB[i].in;
            switchB.pppg$i++ <-- cable <-- mlanB[i].out;
        };
        for i=0..bl-1 {
            switchB.pppg$o++ --> cable --> llanB[i].in;
            switchB.pppg$i++ <-- cable <-- llanB[i].out;
        };
        switchB.pppg$o++ --> cable --> serverB.in;
        switchB.pppg$i++ <-- cable <-- serverB.out;

        // switch C
        for i=0..cs-1 {
            switchC.pppg$o++ --> cable --> slanC[i].in;
            switchC.pppg$i++ <-- cable <-- slanC[i].out;
        };
        for i=0..cm-1 {
            switchC.pppg$o++ --> cable --> mlanC[i].in;
            switchC.pppg$i++ <-- cable <-- mlanC[i].out;
        };
        for i=0..cl-1 {
            switchC.pppg$o++ --> cable --> llanC[i].in;
            switchC.pppg$i++ <-- cable <-- llanC[i].out;
        };
        switchC.pppg$o++ --> cable --> serverC.in;
        switchC.pppg$i++ <-- cable <-- serverC.out;

        // switch D
        for i=0..ds-1 {
            switchD.pppg$o++ --> cable --> slanD[i].in;
            switchD.pppg$i++ <-- cable <-- slanD[i].out;
        };
        for i=0..dm-1 {
            switchD.pppg$o++ --> cable --> mlanD[i].in;
            switchD.pppg$i++ <-- cable <-- mlanD[i].out;
        };
        for i=0..dl-1 {
            switchD.pppg$o++ --> cable --> llanD[i].in;
            switchD.pppg$i++ <-- cable <-- llanD[i].out;
        };
        switchD.pppg$o++ --> cable --> serverD.in;
        switchD.pppg$i++ <-- cable <-- serverD.out;

        // connect switches
        switchA.pppg$o++ --> cable --> switchB.pppg$i++;
        switchA.pppg$i++ <-- cable <-- switchB.pppg$o++;

        switchB.pppg$o++ --> cable --> switchC.pppg$i++;
        switchB.pppg$i++ <-- cable <-- switchC.pppg$o++;

        switchC.pppg$o++ --> cable --> switchD.pppg$i++;
        switchC.pppg$i++ <-- cable <-- switchD.pppg$o++;

        switchB.pppg$o++ --> cable --> switchBB[4].pppg$i++;
        switchB.pppg$i++ <-- cable <-- switchBB[4].pppg$o++;

}


