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
        inout ethg;
    submodules:
        hub: EtherHub {
            @display("is=s");
        };
        host[h]: EtherHost {
            @display("is=s");
        };
    connections:
        for i=0..h-1 {
            hub.ethg$o++ --> cable --> host[i].ethg$i;
            hub.ethg$i++ <-- cable <-- host[i].ethg$o;
        };
        hub.ethg$o++ --> ethg$o;
        hub.ethg$i++ <-- ethg$i;
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
        inout ethg;
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
            switch.ethg$o++ --> cable --> host[i].ethg$i;
            switch.ethg$i++ <-- cable <-- host[i].ethg$o;
        };

        switch.ethg$o++ --> ethg$o;
        switch.ethg$i++ <-- ethg$i;

        for i=0..h-1 {
            hub.ethg$o++ --> cable --> hhost[i].ethg$i;
            hub.ethg$i++ <-- cable <-- hhost[i].ethg$o;
        };

        switch.ethg$o++ --> cable --> hub.ethg$i++;
        switch.ethg$i++ <-- cable <-- hub.ethg$o++;

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
        inout ethg;
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
            switch.ethg$o++ --> cable --> host[i].ethg$i;
            switch.ethg$i++ <-- cable <-- host[i].ethg$o;
        };

        switch.ethg$o++ --> ethg$o;
        switch.ethg$i++ <-- ethg$i;

        for i=0..h-1 {
            hub.ethg$o++ --> cable --> hhost[i].ethg$i;
            hub.ethg$i++ <-- cable <-- hhost[i].ethg$o;
        };

        switch.ethg$o++ --> cable --> hub.ethg$i++;
        switch.ethg$i++ <-- cable <-- hub.ethg$o++;

        for i=0..b-1 {
            bus.ethg$o++ --> bhost[i].ethg$i;
            bus.ethg$i++ <-- bhost[i].ethg$o;
        };

        bus.ethg$o++ --> hub.ethg$i++;
        bus.ethg$i++ <-- hub.ethg$o++;

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
            switchBB[k].ethg$o++ --> cable --> slanBB[k*bbs+i].ethg$i;
            switchBB[k].ethg$i++ <-- cable <-- slanBB[k*bbs+i].ethg$o;
        };
        for k=0..n-1, for i=0..bbm-1 {
            switchBB[k].ethg$o++ --> cable --> mlanBB[k*bbm+i].ethg$i;
            switchBB[k].ethg$i++ <-- cable <-- mlanBB[k*bbm+i].ethg$o;
        };
        for k=0..n-1, for i=0..bbl-1 {
            switchBB[k].ethg$o++ --> cable --> llanBB[k*bbl+i].ethg$i;
            switchBB[k].ethg$i++ <-- cable <-- llanBB[k*bbl+i].ethg$o;
        };
        for k=0..n-2 {
            switchBB[k].ethg$o++ --> cable --> switchBB[k+1].ethg$i++;
            switchBB[k].ethg$i++ <-- cable <-- switchBB[k+1].ethg$o++;
        };

        // switch A
        for i=0..as-1 {
            switchA.ethg$o++ --> cable --> slanA[i].ethg$i;
            switchA.ethg$i++ <-- cable <-- slanA[i].ethg$o;
        };
        for i=0..am-1 {
            switchA.ethg$o++ --> cable --> mlanA[i].ethg$i;
            switchA.ethg$i++ <-- cable <-- mlanA[i].ethg$o;
        };
        for i=0..al-1 {
            switchA.ethg$o++ --> cable --> llanA[i].ethg$i;
            switchA.ethg$i++ <-- cable <-- llanA[i].ethg$o;
        };
        switchA.ethg$o++ --> cable --> serverA.ethg$i;
        switchA.ethg$i++ <-- cable <-- serverA.ethg$o;

        // switch B
        for i=0..bs-1 {
            switchB.ethg$o++ --> cable --> slanB[i].ethg$i;
            switchB.ethg$i++ <-- cable <-- slanB[i].ethg$o;
        };
        for i=0..bm-1 {
            switchB.ethg$o++ --> cable --> mlanB[i].ethg$i;
            switchB.ethg$i++ <-- cable <-- mlanB[i].ethg$o;
        };
        for i=0..bl-1 {
            switchB.ethg$o++ --> cable --> llanB[i].ethg$i;
            switchB.ethg$i++ <-- cable <-- llanB[i].ethg$o;
        };
        switchB.ethg$o++ --> cable --> serverB.ethg$i;
        switchB.ethg$i++ <-- cable <-- serverB.ethg$o;

        // switch C
        for i=0..cs-1 {
            switchC.ethg$o++ --> cable --> slanC[i].ethg$i;
            switchC.ethg$i++ <-- cable <-- slanC[i].ethg$o;
        };
        for i=0..cm-1 {
            switchC.ethg$o++ --> cable --> mlanC[i].ethg$i;
            switchC.ethg$i++ <-- cable <-- mlanC[i].ethg$o;
        };
        for i=0..cl-1 {
            switchC.ethg$o++ --> cable --> llanC[i].ethg$i;
            switchC.ethg$i++ <-- cable <-- llanC[i].ethg$o;
        };
        switchC.ethg$o++ --> cable --> serverC.ethg$i;
        switchC.ethg$i++ <-- cable <-- serverC.ethg$o;

        // switch D
        for i=0..ds-1 {
            switchD.ethg$o++ --> cable --> slanD[i].ethg$i;
            switchD.ethg$i++ <-- cable <-- slanD[i].ethg$o;
        };
        for i=0..dm-1 {
            switchD.ethg$o++ --> cable --> mlanD[i].ethg$i;
            switchD.ethg$i++ <-- cable <-- mlanD[i].ethg$o;
        };
        for i=0..dl-1 {
            switchD.ethg$o++ --> cable --> llanD[i].ethg$i;
            switchD.ethg$i++ <-- cable <-- llanD[i].ethg$o;
        };
        switchD.ethg$o++ --> cable --> serverD.ethg$i;
        switchD.ethg$i++ <-- cable <-- serverD.ethg$o;

        // connect switches
        switchA.ethg$o++ --> cable --> switchB.ethg$i++;
        switchA.ethg$i++ <-- cable <-- switchB.ethg$o++;

        switchB.ethg$o++ --> cable --> switchC.ethg$i++;
        switchB.ethg$i++ <-- cable <-- switchC.ethg$o++;

        switchC.ethg$o++ --> cable --> switchD.ethg$i++;
        switchC.ethg$i++ <-- cable <-- switchD.ethg$o++;

        switchB.ethg$o++ --> cable --> switchBB[4].ethg$i++;
        switchB.ethg$i++ <-- cable <-- switchBB[4].ethg$o++;

}


