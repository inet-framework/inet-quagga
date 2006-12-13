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


import "NotificationBoard";
import "RoutingTable";
import "InterfaceTable";
import "NetworkLayer";
import "LDP";
import "TCP";
import "UDP";
import "LinkStateRouting";
import "TED";
import "MPLS";
import "PPPInterface";
import "LIBTable";
import "NAMTraceWriter";


//
// An LDP-capable router.
//
// LDP Capable Routers are main building blocks for an LDP MPLS network.
//
module LDP_LSR
{
    parameters:
        double holdTime = default(15) @unit("s");
        double helloInterval = default(5) @unit("s");
        int namid;
        string peers;
        string routerId = default("auto");
        string routingFile = default("");
        @display("i=abstract/router");
    gates:
        input in[];
        output out[];
    submodules:
        notificationBoard: NotificationBoard {
            parameters:
                @display("p=70,60");
        };
        interfaceTable: InterfaceTable {
            parameters:
                @display("p=70,150");
        };
        routingTable: RoutingTable {
            parameters:
                IPForward = true;
                routerId = routerId;
                routingFile = routingFile;
                @display("p=70,240");
        };
        ldp: LDP {
            parameters:
                holdTime = holdTime;
                helloInterval = helloInterval;
                @display("p=222,67");
        };
        ted: TED {
            parameters:
                @display("p=340,244");
        };
        linkStateRouting: LinkStateRouting {
            parameters:
                peers = peers;
                @display("p=360,150");
        };
        tcp: TCP {
            parameters:
                @display("p=177,145");
        };
        udp: UDP {
            parameters:
                @display("p=267,145");
        };
        networkLayer: NetworkLayer {
            parameters:
                @display("p=224,223");
            gates:
                ifIn[sizeof(out)];
                ifOut[sizeof(out)];
        };
        ppp[sizeof(out)]: PPPInterface {
            parameters:
                @display("p=105,388,row,90;q=l2queue");
        };
        mpls: MPLS {
            parameters:
                //peers = peers,
                classifier = "ldp";
                @display("p=224,302");
            gates:
                netwIn[sizeof(out)];
                netwOut[sizeof(out)];
                ifIn[sizeof(out)];
                ifOut[sizeof(out)];
        };
        libTable: LIBTable {
            parameters:
                @display("p=340,305");
        };
        namTrace: NAMTraceWriter {
            parameters:
                namid = namid;
                @display("p=70,310");

        };
    connections allowunconnected:
        linkStateRouting.to_ip --> networkLayer.OSPFIn;
        linkStateRouting.from_ip <-- networkLayer.OSPFOut;

        ldp.tcpIn <-- tcp.to_appl++;
        ldp.tcpOut --> tcp.from_appl++;

        ldp.udpOut --> udp.from_app++;
        ldp.udpIn <-- udp.to_app++;

        udp.to_ip --> networkLayer.UDPIn;
        udp.from_ip <-- networkLayer.UDPOut;

        tcp.to_ip --> networkLayer.TCPIn;
        tcp.from_ip <-- networkLayer.TCPOut;

        for i=0..sizeof(out)-1 {
            in[i] --> ppp[i].physIn;
            out[i] <-- ppp[i].physOut;

            ppp[i].netwOut --> mpls.ifIn[i];
            ppp[i].netwIn <-- mpls.ifOut[i];

            mpls.netwOut[i] --> networkLayer.ifIn[i];
            mpls.netwIn[i] <-- networkLayer.ifOut[i];
        };
}



