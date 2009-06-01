//
// Copyright (C) 2005 Vojta Janota
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

package org.omnetpp.inet.networklayer.quagga;

import inet.base.NotificationBoard;
import inet.linklayer.ethernet.EthernetInterface;
import inet.linklayer.ppp.PPPInterface;
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.ipv4.RoutingTable;
import inet.nodes.inet.NetworkLayer;
import inet.transport.tcp.TCP;
import inet.transport.udp.UDP;
import inet.util.NAMTraceWriter;


//
// Quagga-based \IP router.
//
module QuaggaRouter
{
    parameters:
        int namid;
        string routingFile = default("");
        string routingDaemon; // "Ripd", "Ospfd", etc.
        @display("i=srouter");
    gates:
        inout pppg[];
        inout ethg[];
    submodules:
        namTrace: NAMTraceWriter {
            parameters:
                namid = namid;
                @display("p=330,60");
        }
        notificationBoard: NotificationBoard {
            parameters:
                @display("p=60,60");
        }
        interfaceTable: InterfaceTable {
            parameters:
                @display("p=150,60");
        }
        routingTable: RoutingTable {
            parameters:
                IPForward = true;
                routerId = "auto";
                routingFile = routingFile;
                @display("p=240,60");
        }
        networkLayer: NetworkLayer {
            parameters:
                @display("p=200,341;q=queue");
            gates:
                ifIn[sizeof(pppg)+sizeof(ethg)];
                ifOut[sizeof(pppg)+sizeof(ethg)];
        }
        ppp[sizeof(pppg)]: PPPInterface {
            parameters:
                @display("p=90,457,row,110;q=l2queue");
        }
        eth[sizeof(ethg)]: EthernetInterface {
            parameters:
                @display("p=145,457,row,110;q=l2queue");
        }
        tcp: TCP {
            parameters:
                @display("p=200,250");
        }
        udp: UDP {
            parameters:
                @display("p=300,250");
        }
        zebra: Zebra {
            parameters:
                @display("p=150, 150");
        }
        router: <routingDaemon> like Zebra {
            parameters:
                @display("p=250, 150");
        }
    connections allowunconnected:
        // connections to network outside
        for i=0..sizeof(pppg)-1 {
            pppg[i] <--> ppp[i].phys;
            ppp[i].netwOut --> networkLayer.ifIn[i];
            ppp[i].netwIn <-- networkLayer.ifOut[i];
        }

        tcp.ipOut --> networkLayer.tcpIn;
        tcp.ipIn <-- networkLayer.TCPOut;

        udp.ipOut --> networkLayer.udpIn;
        udp.ipIn <-- networkLayer.udpOut;

        zebra.tcpIn <-- tcp.appOut++;
        zebra.tcpOut --> tcp.appIn++;

        router.tcpIn <-- tcp.appOut++;
        router.tcpOut --> tcp.appIn++;

        router.udpIn <-- udp.appOut++;
        router.udpOut --> udp.appIn++;

        router.ipOut --> networkLayer.ospfIn;
        router.ipIn <-- networkLayer.ospfOut;

        for i=0..sizeof(ethg)-1 {
            ethg[i] <--> eth[i].phys;
            eth[i].netwOut --> networkLayer.ifIn[sizeof(pppg)+i];
            eth[i].netwIn <-- networkLayer.ifOut[sizeof(pppg)+i];
        }
}

