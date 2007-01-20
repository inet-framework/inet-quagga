import "EtherHub";
import "OSPFRouter";
import "StandardHost";



module OSPF_Area1
{
    parameters:
        @display("p=10,42;b=432,504");
    gates:
        input ethg[];
    submodules:
        RT1: OSPFRouter {
            parameters:
                @display("p=232,136");
            gates:
                ethg[2];
        };
        RT2: OSPFRouter {
            parameters:
                @display("p=236,348");
            gates:
                ethg[2];
        };
        N1: EtherHub {
            parameters:
                @display("p=140,136");
            gates:
                ethg[3];
        };
        N2: EtherHub {
            parameters:
                @display("p=140,348");
            gates:
                ethg[3];
        };
        N3: EtherHub {
            parameters:
                @display("p=360,252");
            gates:
                ethg[5];
        };
        N4: EtherHub {
            parameters:
                @display("p=360,464");
            gates:
                ethg[3];
        };
        H1: StandardHost {
            parameters:
                @display("p=56,96;i=device/pc_s");
            gates:
                ethg[1];
        };
        H2: StandardHost {
            parameters:
                @display("p=56,172;i=device/pc_s");
            gates:
                ethg[1];
        };
        H3: StandardHost {
            parameters:
                @display("p=56,316;i=device/pc_s");
            gates:
                ethg[1];
        };
        H4: StandardHost {
            parameters:
                @display("p=56,388;i=device/pc_s");
            gates:
                ethg[1];
        };
        H5: StandardHost {
            parameters:
                @display("p=360,188;i=device/pc_s");
            gates:
                ethg[1];
        };
        H6: StandardHost {
            parameters:
                @display("p=316,520;i=device/pc_s");
            gates:
                ethg[1];
        };
        H7: StandardHost {
            parameters:
                @display("p=400,520;i=device/pc_s");
            gates:
                ethg[1];
        };
    connections:
        H1.ethg$o[0] --> {  delay = 0.1us; } --> N1.pppg$i[0];
        N1.pppg$o[0] --> {  delay = 0.1us; } --> H1.ethg$i[0];
        N1.pppg$o[1] --> {  delay = 0.1us; } --> H2.ethg$i[0];
        H2.ethg$o[0] --> {  delay = 0.1us; } --> N1.pppg$i[1];
        N2.pppg$o[0] --> {  delay = 0.1us; } --> H3.ethg$i[0];
        H3.ethg$o[0] --> {  delay = 0.1us; } --> N2.pppg$i[0];
        N2.pppg$o[1] --> {  delay = 0.1us; } --> H4.ethg$i[0];
        H4.ethg$o[0] --> {  delay = 0.1us; } --> N2.pppg$i[1];
        N1.pppg$o[2] --> {  delay = 0.1us; } --> RT1.ethg$i[0];
        RT1.ethg$o[0] --> {  delay = 0.1us; } --> N1.pppg$i[2];
        RT1.ethg$o[1] --> {  delay = 0.1us; } --> N3.pppg$i[1];
        N3.pppg$o[1] --> {  delay = 0.1us; } --> RT1.ethg$i[1];
        N3.pppg$o[0] --> {  delay = 0.1us; } --> H5.ethg$i[0];
        H5.ethg$o[0] --> {  delay = 0.1us; } --> N3.pppg$i[0];
        N4.pppg$o[0] --> {  delay = 0.1us; } --> H6.ethg$i[0];
        H6.ethg$o[0] --> {  delay = 0.1us; } --> N4.pppg$i[0];
        N4.pppg$o[1] --> {  delay = 0.1us; } --> H7.ethg$i[0];
        H7.ethg$o[0] --> {  delay = 0.1us; } --> N4.pppg$i[1];
        N2.pppg$o[2] --> {  delay = 0.1us; } --> RT2.ethg$i[0];
        RT2.ethg$o[0] --> {  delay = 0.1us; } --> N2.pppg$i[2];
        RT2.ethg$o[1] --> {  delay = 0.1us; } --> N3.pppg$i[2];
        N3.pppg$o[2] --> {  delay = 0.1us; } --> RT2.ethg$i[1];

        // towards other areas
        N3.pppg$o[4] --> { @display("m=m,100,44,100,32"); } --> ethg$o[0];
        ethg$i[0] --> { @display("m=m,100,32,100,48"); } --> N3.pppg$i[4];
        N3.pppg$o[3] --> { @display("m=m,96,96,100,52"); } --> ethg$o[1];
        ethg$i[1] --> { @display("m=m,100,52,89,64"); } --> N3.pppg$i[3];
        N4.pppg$o[2] --> ethg$o[2];
        ethg$i[2] --> N4.pppg$i[2];
}

