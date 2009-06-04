
package org.omnetpp.inet.networklayer.quagga.unitTest;

import inet.base.NotificationBoard;
import inet.linklayer.ppp.PPPInterface;
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.ipv4.RoutingTable;
import inet.nodes.inet.NetworkLayer;
import inet.transport.tcp.TCP;
import inet.transport.udp.UDP;


module TestRouter
{
    parameters:
        string routingFile;
        string routerId;
        string testUnit;
    gates:
        inout pppg[];
    submodules:
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
                routerId = routerId;
                routingFile = routingFile;
                @display("p=240,60");
        }
        networkLayer: NetworkLayer {
            parameters:
                @display("p=200,341;q=queue");
            gates:
                ifIn[sizeof(out)];
                ifOut[sizeof(out)];
        }
        ppp[sizeof(out)]: PPPInterface {
            parameters:
                @display("p=90,457,row,110;q=l2queue");
        }
        tcp: TCP {
            parameters:
                @display("p=200,250");
        }
        udp: UDP {
            parameters:
                @display("p=300,250");
        }
        unit: <testUnit> like IUnitTest {
            parameters:
                @display("p=250, 150");
        }
    connections allowunconnected:
        // connections to network outside
        for i=0..sizeof(out)-1 {
            pppg[i] <--> ppp[i].phys;
            ppp[i].netwOut --> networkLayer.ifIn[i];
            ppp[i].netwIn <-- networkLayer.ifOut[i];
        }

        tcp.ipOut --> networkLayer.tcpIn;
        tcp.ipIn <-- networkLayer.TCPOut;

        udp.ipOut --> networkLayer.udpIn;
        udp.ipIn <-- networkLayer.udpOut;

        unit.tcpIn <-- tcp.appOut++;
        unit.tcpOut --> tcp.appIn++;

        unit.udpIn <-- udp.appOut++;
        unit.udpOut --> udp.appIn++;

        unit.ipOut --> networkLayer.ospfIn;
        unit.ipIn <-- networkLayer.ospfOut;
}

