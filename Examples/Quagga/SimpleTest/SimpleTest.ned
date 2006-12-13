import "EtherHub";
import "QuaggaRouter";
import "StandardHost";
import "ChannelInstaller";

network SimpleTest
{
    parameters:
        @display("p=10,10;b=712,152");
    submodules:
        channelInstaller: ChannelInstaller {
            parameters:
                channelClass = "ThruputMeteringChannel";
                channelAttrs = "format=#N";
                @display("p=130,40");
        };
        H1: StandardHost {
            parameters:
                @display("p=56,92;i=device/laptop");
            gates:
                ethIn[1];
                ethOut[1];
        };
        N1: EtherHub {
            parameters:
                @display("p=184,92");
            gates:
                in[2];
                out[2];
        };
        R1: QuaggaRouter {
            parameters:
                @display("p=296,92");
            gates:
                ethIn[1];
                ethOut[1];
        };
        R2: QuaggaRouter {
            parameters:
                @display("p=416,92");
            gates:
                ethIn[1];
                ethOut[1];
        };
        N2: EtherHub {
            parameters:
                @display("p=532,92");
            gates:
                in[2];
                out[2];
        };
        H2: StandardHost {
            parameters:
                @display("p=660,92;i=device/laptop");
            gates:
                ethIn[1];
                ethOut[1];
        };
    connections:
        H1.ethOut[0] --> {  delay = 0.1us; } --> N1.in[0];
        N1.out[0] --> {  delay = 0.1us; } --> H1.ethIn[0];
        N1.out[1] --> {  delay = 0.1us; } --> R1.ethIn[0];
        R1.ethOut[0] --> {  delay = 0.1us; } --> N1.in[1];

        R1.out++ --> {  datarate = 10000000; delay = 0.1us; } --> R2.in++;
        R2.out++ --> {  datarate = 10000000; delay = 0.1us; } --> R1.in++;

        R2.ethOut[0] --> {  delay = 0.1us; } --> N2.in[0];
        N2.out[0] --> {  delay = 0.1us; } --> R2.ethIn[0];
        N2.out[1] --> {  delay = 0.1us; } --> H2.ethIn[0];
        H2.ethOut[0] --> {  delay = 0.1us; } --> N2.in[1];
}

