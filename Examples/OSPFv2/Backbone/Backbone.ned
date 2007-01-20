import "EtherHub";
import "OSPFRouter";
import "StandardHost";
import "ChannelInstaller";

network Backbone
{
    parameters:
        @display("p=10,10;b=736,568");
    submodules:
        channelInstaller: ChannelInstaller {
            parameters:
                channelClass = "ThruputMeteringChannel";
                channelAttrs = "format=#N";
                @display("p=98,50");
        };
        R1: OSPFRouter {
            parameters:
                @display("p=372,340");
            gates:
                ethIn[3];
                ethOut[3];
        };
        N1: EtherHub {
            parameters:
                @display("p=368,268");
            gates:
                in[2];
                out[2];
        };
        N2: EtherHub {
            parameters:
                @display("p=452,384");
            gates:
                in[3];
                out[3];
        };
        R2: OSPFRouter {
            parameters:
                @display("p=368,188");
            gates:
                ethIn[2];
                ethOut[2];
        };
        R4: OSPFRouter {
            parameters:
                @display("p=216,432");
            gates:
                ethIn[2];
                ethOut[2];
        };
        R3: OSPFRouter {
            parameters:
                @display("p=532,428");
            gates:
                ethIn[2];
                ethOut[2];
        };
        N4: EtherHub {
            parameters:
                @display("p=368,100");
            gates:
                in[4];
                out[4];
        };
        N5: EtherHub {
            parameters:
                @display("p=612,476");
            gates:
                in[3];
                out[3];
        };
        R5: OSPFRouter {
            parameters:
                @display("p=488,284");
            gates:
                ethIn[2];
                ethOut[2];
        };
        R7: OSPFRouter {
            parameters:
                @display("p=256,284");
            gates:
                ethIn[2];
                ethOut[2];
        };
        R6: OSPFRouter {
            parameters:
                @display("p=372,476");
            gates:
                ethIn[2];
                ethOut[2];
        };
        N6: EtherHub {
            parameters:
                @display("p=136,476");
            gates:
                in[3];
                out[3];
        };
        N3: EtherHub {
            parameters:
                @display("p=292,384");
            gates:
                in[2];
                out[2];
        };
        H1: StandardHost {
            parameters:
                @display("p=372,420;i=device/laptop");
            gates:
                ethIn[1];
                ethOut[1];
        };
        H2: StandardHost {
            parameters:
                @display("p=368,40;i=device/laptop");
            gates:
                ethIn[1];
                ethOut[1];
        };
    connections:
        R1.ethg$o[0] --> {  delay = 0.1us; } --> N1.pppg$i[1];
        N1.pppg$o[1] --> {  delay = 0.1us; } --> R1.ethg$i[0];
        R1.ethg$o[1] --> {  delay = 0.1us; } --> N2.pppg$i[2];
        N2.pppg$o[2] --> {  delay = 0.1us; } --> R1.ethg$i[1];
        N1.pppg$o[0] --> {  delay = 0.1us; } --> R2.ethg$i[1];
        R2.ethg$o[1] --> {  delay = 0.1us; } --> N1.pppg$i[0];
        R2.ethg$o[0] --> {  delay = 0.1us; } --> N4.pppg$i[2];
        N4.pppg$o[2] --> {  delay = 0.1us; } --> R2.ethg$i[0];
        N4.pppg$o[1] --> {  delay = 0.1us; } --> R5.ethg$i[1];
        R5.ethg$o[1] --> {  delay = 0.1us; } --> N4.pppg$i[1];
        R5.ethg$o[0] --> {  delay = 0.1us; } --> N5.pppg$i[2];
        N5.pppg$o[2] --> {  delay = 0.1us; } --> R5.ethg$i[0];
        N2.pppg$o[0] --> {  delay = 0.1us; } --> R3.ethg$i[1];
        R3.ethg$o[1] --> {  delay = 0.1us; } --> N2.pppg$i[0];
        R3.ethg$o[0] --> {  delay = 0.1us; } --> N5.pppg$i[1];
        N5.pppg$o[1] --> {  delay = 0.1us; } --> R3.ethg$i[0];
        N5.pppg$o[0] --> {  delay = 0.1us; } --> R6.ethg$i[0];
        R6.ethg$o[0] --> {  delay = 0.1us; } --> N5.pppg$i[0];
        N6.pppg$o[2] --> {  delay = 0.1us; } --> R6.ethg$i[1];
        R6.ethg$o[1] --> {  delay = 0.1us; } --> N6.pppg$i[2];
        R1.ethg$o[2] --> {  delay = 0.1us; } --> N3.pppg$i[0];
        N3.pppg$o[0] --> {  delay = 0.1us; } --> R1.ethg$i[2];
        N3.pppg$o[1] --> {  delay = 0.1us; } --> R4.ethg$i[0];
        R4.ethg$o[0] --> {  delay = 0.1us; } --> N3.pppg$i[1];
        R4.ethg$o[1] --> {  delay = 0.1us; } --> N6.pppg$i[1];
        N6.pppg$o[1] --> {  delay = 0.1us; } --> R4.ethg$i[1];
        N4.pppg$o[3] --> {  delay = 0.1us; } --> R7.ethg$i[0];
        R7.ethg$o[0] --> {  delay = 0.1us; } --> N4.pppg$i[3];
        R7.ethg$o[1] --> {  delay = 0.1us; } --> N6.pppg$i[0];
        N6.pppg$o[0] --> {  delay = 0.1us; } --> R7.ethg$i[1];
        N4.pppg$o[0] --> {  delay = 0.1us; } --> H2.ethg$i[0];
        H2.ethg$o[0] --> {  delay = 0.1us; } --> N4.pppg$i[0];
        N2.pppg$o[1] --> {  delay = 0.1us; } --> H1.ethg$i[0];
        H1.ethg$o[0] --> {  delay = 0.1us; } --> N2.pppg$i[1];
}

