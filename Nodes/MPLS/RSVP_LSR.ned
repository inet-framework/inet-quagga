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
import "NetworkLayer";
import "MPLS";
import "LIBTable";
import "RoutingTable";
import "InterfaceTable";
import "SimpleClassifier";
import "RSVP";
import "LinkStateRouting";
import "TED";
import "NAMTraceWriter";

//
// An \RSVP-TE capable router.
//
// \RSVP occupies the Transport layer; however, it is not a transport protocol
// itself. \RSVP uses transport protocols to route packets. TED is used
// to calculate shortest paths.
//
module RSVP_LSR
{
    parameters:

        volatile int namid;

        string peers;
        string routerId = default("auto");
        string routingFile = default("");
        @display("i=abstract/router_s");
    gates:
        input in[];
        output out[];

    submodules:
        notificationBoard: NotificationBoard {
            parameters:
                @display("p=74,57");
        };
        routingTable: RoutingTable {
            parameters:
                IPForward = true;
                routerId = routerId;
                routingFile = routingFile;
                @display("p=68,138");
        };
        interfaceTable: InterfaceTable {
            parameters:
                @display("p=68,208");
        };
        ted: TED {
            parameters:
                @display("p=312,203");
        };
        linkStateRouting: LinkStateRouting {
            parameters:
                peers = peers;
                @display("p=254,115");
        };
        rsvp: RSVP {
            parameters:
                peers = peers;
                @display("p=156,67");
        };
        classifier: SimpleClassifier {
            parameters:
                @display("p=330,67");
        };
        networkLayer: NetworkLayer {
            parameters:
                @display("p=192,195");
            gates:
                ifIn[sizeof(out)];
                ifOut[sizeof(out)];
        };
        ppp[sizeof(out)]: PPPInterface {
            parameters:
                @display("p=88,329,row,90;q=l2queue");
        };
        mpls: MPLS {
            parameters:
                //peers = peers;
                classifier = "classifier";
                @display("o=#ff8000;p=192,270;b=66,14");
            gates:
                netwIn[sizeof(out)];
                netwOut[sizeof(out)];
                ifIn[sizeof(out)];
                ifOut[sizeof(out)];
        };
        libTable: LIBTable {
            parameters:
                @display("p=312,268");
        };
        namTrace: NAMTraceWriter {
            parameters:
                namid = namid;
                @display("p=70,270");

        };
    connections allowunconnected:
        linkStateRouting.to_ip --> networkLayer.OSPFIn;
        linkStateRouting.from_ip <-- networkLayer.OSPFOut;

        rsvp.to_ip --> networkLayer.RSVPIn;
        rsvp.from_ip <-- networkLayer.RSVPOut;

        for i=0..sizeof(out)-1 {
            in[i] --> ppp[i].physIn;
            out[i] <-- ppp[i].physOut;

            ppp[i].netwOut --> mpls.ifIn[i];
            ppp[i].netwIn <-- mpls.ifOut[i];

            mpls.netwOut[i] --> networkLayer.ifIn[i];
            mpls.netwIn[i] <-- networkLayer.ifOut[i];
        };
}

