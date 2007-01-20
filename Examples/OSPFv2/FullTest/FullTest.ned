import "EtherHub";
import "OSPFRouter";
import "StandardHost";
import "OSPFTestNetworkArea1";
import "OSPFTestNetworkArea2";
import "OSPFTestNetworkArea3";
import "ChannelInstaller";



network OSPF_TestNetwork
{
    parameters:
        @display("p=10,10;b=704,560");
    submodules:
        channelInstaller: ChannelInstaller {
            parameters:
                channelClass = "ThruputMeteringChannel";
                channelAttrs = "format=#N";
                @display("p=98,50");
        };
        Area1: OSPF_Area1 {
            parameters:
                @display("p=120,172;b=176,168");
            gates:
                ethg[3];
        };
        Area2: OSPF_Area2 {
            parameters:
                @display("p=448,468;b=176,168");
            gates:
                ethg[4];
        };
        Area3: OSPF_Area3 {
            parameters:
                @display("p=128,468;b=176,168");
            gates:
                ethg[1];
        };
        RT3: OSPFRouter {
            parameters:
                @display("p=276,208");
            gates:
                ethg[3];
        };
        RT4: OSPFRouter {
            parameters:
                @display("p=276,144");
            gates:
                ethg[2];
        };
        RT5: OSPFRouter {
            parameters:
                @display("p=496,144");
            gates:
                ethg[6];
        };
        RT6: OSPFRouter {
            parameters:
                @display("p=424,208");
            gates:
                ethg[3];
        };
        RT7: OSPFRouter {
            parameters:
                @display("p=496,328");
            gates:
                ethg[4];
        };
        RT10: OSPFRouter {
            parameters:
                @display("p=424,328");
            gates:
                ethg[3];
        };
        RT11: OSPFRouter {
            parameters:
                @display("p=284,468");
            gates:
                ethg[2];
        };
        N12: EtherHub {
            parameters:
                @display("p=608,296");
            gates:
                ethg[3];
        };
        N13: EtherHub {
            parameters:
                @display("p=500,92");
            gates:
                ethg[2];
        };
        N14: EtherHub {
            parameters:
                @display("p=608,92");
            gates:
                ethg[2];
        };
        N15: EtherHub {
            parameters:
                @display("p=608,356");
            gates:
                ethg[2];
        };
        H18: StandardHost {
            parameters:
                @display("p=496,36;i=device/pc_s");
            gates:
                ethg[1];
        };
        H19: StandardHost {
            parameters:
                @display("p=612,36;i=device/pc_s");
            gates:
                ethg[1];
        };
        H20: StandardHost {
            parameters:
                @display("p=688,296;i=device/pc_s");
            gates:
                ethg[1];
        };
        H21: StandardHost {
            parameters:
                @display("p=688,356;i=device/pc_s");
            gates:
                ethg[1];
        };
    connections:
        RT11.ethg$o[0] --> {  delay = 0.1us; } --> Area3.ethg$i[0];
        Area3.ethg$o[0] --> {  delay = 0.1us; } --> RT11.ethg$i[0];
        RT11.ethg$o[1] --> {  delay = 0.1us; } --> Area2.ethg$i[0];
        Area2.ethg$o[0] --> {  delay = 0.1us; } --> RT11.ethg$i[1];
        RT3.ethg$o[0] --> {  delay = 0.1us;@display("m=m,41,50,88,40"); } --> Area1.ethg$i[1];
        Area1.ethg$o[1] --> {  delay = 0.1us;@display("m=m,88,40,64,79"); } --> RT3.ethg$i[0];
        RT3.ethg$o[1] --> {  delay = 0.1us;@display("m=m,77,42,92,96"); } --> Area1.ethg$i[2];
        Area1.ethg$o[2] --> {  delay = 0.1us;@display("m=m,83,100,60,50"); } --> RT3.ethg$i[1];
        N13.ethg$o[1] --> {  delay = 0.1us; } --> RT5.ethg$i[0];
        RT5.ethg$o[0] --> {  delay = 0.1us; } --> N13.ethg$i[1];
        N12.ethg$o[0] --> {  delay = 0.1us; } --> RT5.ethg$i[4];
        RT5.ethg$o[4] --> {  delay = 0.1us; } --> N12.ethg$i[0];
        RT5.ethg$o[5] --> {  delay = 0.1us; } --> N14.ethg$i[1];
        N14.ethg$o[1] --> {  delay = 0.1us; } --> RT5.ethg$i[5];
        RT3.ethg$o[2] --> {  delay = 0.1us; } --> RT6.ethg$i[0];
        RT6.ethg$o[0] --> {  delay = 0.1us; } --> RT3.ethg$i[2];
        RT10.ethg$o[0] --> {  delay = 0.1us; } --> RT6.ethg$i[1];
        RT6.ethg$o[1] --> {  delay = 0.1us; } --> RT10.ethg$i[0];
        RT7.ethg$o[3] --> {  delay = 0.1us; } --> N12.ethg$i[1];
        N12.ethg$o[1] --> {  delay = 0.1us; } --> RT7.ethg$i[3];
        RT7.ethg$o[2] --> {  delay = 0.1us; } --> N15.ethg$i[0];
        N15.ethg$o[0] --> {  delay = 0.1us; } --> RT7.ethg$i[2];
        RT5.ethg$o[3] --> {  delay = 0.1us; } --> RT7.ethg$i[0];
        RT7.ethg$o[0] --> {  delay = 0.1us; } --> RT5.ethg$i[3];
        RT5.ethg$o[2] --> {  delay = 0.1us; } --> RT6.ethg$i[2];
        RT6.ethg$o[2] --> {  delay = 0.1us; } --> RT5.ethg$i[2];
        RT10.ethg$o[1] --> {  delay = 0.1us;@display("m=m,50,50,0,30"); } --> Area2.ethg$i[1];
        Area2.ethg$o[1] --> {  delay = 0.1us;@display("m=m,12,7,50,50"); } --> RT10.ethg$i[1];
        RT10.ethg$o[2] --> {  delay = 0.1us;@display("m=m,50,50,64,12"); } --> Area2.ethg$i[2];
        Area2.ethg$o[2] --> {  delay = 0.1us;@display("m=m,76,33,50,50"); } --> RT10.ethg$i[2];
        RT7.ethg$o[1] --> {  delay = 0.1us; } --> Area2.ethg$i[3];
        Area2.ethg$o[3] --> {  delay = 0.1us; } --> RT7.ethg$i[1];
        RT4.ethg$o[1] --> {  delay = 0.1us; } --> RT5.ethg$i[1];
        RT5.ethg$o[1] --> {  delay = 0.1us; } --> RT4.ethg$i[1];
        RT4.ethg$o[0] --> {  delay = 0.1us; } --> Area1.ethg$i[0];
        Area1.ethg$o[0] --> {  delay = 0.1us; } --> RT4.ethg$i[0];
        N14.ethg$o[0] --> {  delay = 0.1us; } --> H19.ethg$i[0];
        H19.ethg$o[0] --> {  delay = 0.1us; } --> N14.ethg$i[0];
        H20.ethg$o[0] --> {  delay = 0.1us; } --> N12.ethg$i[2];
        N12.ethg$o[2] --> {  delay = 0.1us; } --> H20.ethg$i[0];
        H21.ethg$o[0] --> {  delay = 0.1us; } --> N15.ethg$i[1];
        N15.ethg$o[1] --> {  delay = 0.1us; } --> H21.ethg$i[0];
        H18.ethg$o[0] --> {  delay = 0.1us; } --> N13.ethg$i[0];
        N13.ethg$o[0] --> {  delay = 0.1us; } --> H18.ethg$i[0];
}

