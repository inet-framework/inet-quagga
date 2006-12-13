//
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
import "InterfaceTable";
import "RoutingTable6";
import "PPPInterface";
import "EthernetInterface";
import "NetworkLayer6";


//
// \IPv6 router.
//
module Router6
{
    parameters:
        @display("i=abstract/router");
    gates:
        input in[];
        output out[];
        input ethIn[];
        output ethOut[];
    submodules:
        notificationBoard: NotificationBoard {
            parameters:
                @display("p=60,60");
        };
        interfaceTable: InterfaceTable {
            parameters:
                @display("p=150,60");
        };
        routingTable6: RoutingTable6 {
            parameters:
                isRouter = true;
                @display("p=240,60");
        };
        networkLayer: NetworkLayer6 {
            parameters:
                @display("p=200,141;q=queue");
            gates:
                ifIn[sizeof(out)+sizeof(ethOut)];
                ifOut[sizeof(out)+sizeof(ethOut)];
        };
        ppp[sizeof(out)]: PPPInterface {
            parameters:
                @display("p=90,257,row,110;q=l2queue");
        };
        eth[sizeof(ethOut)]: EthernetInterface {
            parameters:
                @display("p=145,257,row,110;q=l2queue");
        };
    connections allowunconnected:
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

