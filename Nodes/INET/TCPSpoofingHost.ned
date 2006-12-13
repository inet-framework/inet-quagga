//
// Copyright (C) 2006 Andras Varga
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
// \IP host with TCPSpoof in the application layer.
//
module TCPSpoofingHost
{
    parameters:
        int numTcpApps = default(0);
        int numUdpApps = default(0);
        string tcpAppType = default("");
        string udpAppType = default("");
        bool IPForward = default(false);
        int namid;
        string routingFile = default("");
    gates:
        input in[];
        output out[];
        input ethIn[];
        output ethOut[];
    submodules:
        namTrace: NAMTraceWriter {
            parameters:
                namid = namid;
                @display("p=71,294");
        };
        notificationBoard: NotificationBoard {
            parameters:
                @display("p=71,54");
        };
        interfaceTable: InterfaceTable {
            parameters:
                @display("p=71,134");
        };
        routingTable: RoutingTable {
            parameters:
                IPForward = IPForward;
                routerId = "";
                routingFile = routingFile;
                @display("p=71,214");
        };
        tcpSpoof: TCPSpoof {
            parameters:
                @display("p=168,122");
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
        tcpSpoof.ipv4Out --> networkLayer.TCPIn;

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

