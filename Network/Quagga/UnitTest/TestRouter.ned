import "NotificationBoard";
import "InterfaceTable";
import "RoutingTable";
import "PPPInterface";
import "NetworkLayer";
import "TCP";
import "UDP";
import "TestNop";

module TestRouter
{
    parameters:
        string routingFile;
        string routerId;
        string testUnit;
    gates:
        input in[];
        output out[];
    submodules:
        notificationBoard: NotificationBoard {
            parameters:
                @display("p=60,60");
        };
        interfaceTable: InterfaceTable {
            parameters:
                @display("p=150,60");
        };
        routingTable: RoutingTable {
            parameters:
                IPForward = true;
                routerId = routerId;
                routingFile = routingFile;
                @display("p=240,60");
        };
        networkLayer: NetworkLayer {
            parameters:
                @display("p=200,341;q=queue");
            gates:
                ifIn[sizeof(out)];
                ifOut[sizeof(out)];
        };
        ppp[sizeof(out)]: PPPInterface {
            parameters:
                @display("p=90,457,row,110;q=l2queue");
        };
        tcp: TCP {
            parameters:
                @display("p=200,250");
        };
        udp: UDP {
            parameters:
                @display("p=300,250");
        };
        unit: <testUnit> like TestNop {
            parameters:
                @display("p=250, 150");
        };
    connections allowunconnected:
        // connections to network outside
        for i=0..sizeof(out)-1 {
            in[i] --> ppp[i].physIn;
            out[i] <-- ppp[i].physOut;
            ppp[i].netwOut --> networkLayer.ifIn[i];
            ppp[i].netwIn <-- networkLayer.ifOut[i];
        };

        tcp.to_ip --> networkLayer.TCPIn;
        tcp.from_ip <-- networkLayer.TCPOut;

        udp.to_ip --> networkLayer.UDPIn;
        udp.from_ip <-- networkLayer.UDPOut;

        unit.tcpIn <-- tcp.to_appl++;
        unit.tcpOut --> tcp.from_appl++;

        unit.udpIn <-- udp.to_app++;
        unit.udpOut --> udp.from_app++;

        unit.ipOut --> networkLayer.OSPFIn;
        unit.ipIn <-- networkLayer.OSPFOut;
}

