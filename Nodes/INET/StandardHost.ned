//
// Copyright (C) 2004 Andras Varga
// Copyright (C) 2000 Institut fuer Telematik, Universitaet Karlsruhe
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


import "NotificationBoard";
import "NAMTraceWriter";
import "InterfaceTable";
import "RoutingTable";
import "TCPApp.ned";
import "TCP.ned";
import "UDP";
import "UDPApp";
import "NetworkLayer";
import "PingApp";
import "PPPInterface";
import "EthernetInterface";



//
// \IP host with TCP, UDP layers and applications.
//
module StandardHost
{
    parameters:
        int numTcpApps;
        int numUdpApps;
        string tcpAppType;
        string udpAppType;
        bool IPForward;
        int namid;
        string routingFile;
        @display("i=device/pc2");
    gates:
        input in[];
        output out[];
        input ethIn[];
        output ethOut[];
    submodules:
        namTrace: NAMTraceWriter {
            parameters:
                namid = namid;
                @display("p=60,310");
        };
        notificationBoard: NotificationBoard {
            parameters:
                @display("p=60,70");
        };
        interfaceTable: InterfaceTable {
            parameters:
                @display("p=60,150");
        };
        routingTable: RoutingTable {
            parameters:
                IPForward = IPForward;
                routerId = "";
                routingFile = routingFile;
                @display("p=60,230");
        };
        tcpApp[numTcpApps]: <tcpAppType> like TCPApp {
            parameters:
                @display("p=163,67");
        };
        tcp: TCP {
            parameters:
                @display("p=163,154");
        };
        udpApp[numUdpApps]: <udpAppType> like UDPApp {
            parameters:
                @display("p=272,67");
        };
        udp: UDP {
            parameters:
                @display("p=272,154");
        };
        pingApp: PingApp {
            parameters:
                @display("p=343,200");
        };
        networkLayer: NetworkLayer {
            parameters:
                proxyARP = false;
                @display("p=248,247;q=queue");
            gates:
                ifIn[sizeof(out)+sizeof(ethOut)];
                ifOut[sizeof(out)+sizeof(ethOut)];
        };
        ppp[sizeof(out)]: PPPInterface {
            parameters:
                @display("p=205,350,row,90;q=txQueue");
        };
        eth[sizeof(ethOut)]: EthernetInterface {
            parameters:
                @display("p=240,350,row,90;q=txQueue");
        };
    connections allowunconnected:
        for i=0..numTcpApps-1 {
            tcpApp[i].tcpOut --> tcp.from_appl++;
            tcpApp[i].tcpIn <-- tcp.to_appl++;
        };

        tcp.to_ip --> networkLayer.TCPIn;
        tcp.from_ip <-- networkLayer.TCPOut;

        for i=0..numUdpApps-1 {
            udpApp[i].to_udp --> udp.from_app++;
            udpApp[i].from_udp <-- udp.to_app++;
        };

        udp.to_ip --> networkLayer.UDPIn;
        udp.from_ip <-- networkLayer.UDPOut;

        networkLayer.pingOut --> pingApp.pingIn;
        networkLayer.pingIn <-- pingApp.pingOut;

        // connections to network outside
        for i=0..sizeof(out)-1 {
            in[i] --> ppp[i].physIn;
            out[i] <-- ppp[i].physOut;
            ppp[i].netwOut --> networkLayer.ifIn[i];
            ppp[i].netwIn <-- networkLayer.ifOut[i];
        };

        for i=0..sizeof(ethOut)-1 {
            ethIn[i] --> eth[i].physIn;
            ethOut[i] <-- eth[i].physOut;
            eth[i].netwOut --> networkLayer.ifIn[sizeof(out)+i];
            eth[i].netwIn <-- networkLayer.ifOut[sizeof(out)+i];
        };
}

