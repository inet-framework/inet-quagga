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
                ethg[1];
        };
        N1: EtherHub {
            parameters:
                @display("p=184,92");
            gates:
                ethg[2];
        };
        R1: QuaggaRouter {
            parameters:
                @display("p=296,92");
            gates:
                ethg[1];
        };
        R2: QuaggaRouter {
            parameters:
                @display("p=416,92");
            gates:
                ethg[1];
        };
        N2: EtherHub {
            parameters:
                @display("p=532,92");
            gates:
                ethg[2];
        };
        H2: StandardHost {
            parameters:
                @display("p=660,92;i=device/laptop");
            gates:
                ethg[1];
        };
    connections:
        H1.ethg$o[0] --> {  delay = 0.1us; } --> N1.pppg$i[0];
        N1.pppg$o[0] --> {  delay = 0.1us; } --> H1.ethg$i[0];
        N1.pppg$o[1] --> {  delay = 0.1us; } --> R1.ethg$i[0];
        R1.ethg$o[0] --> {  delay = 0.1us; } --> N1.pppg$i[1];

        R1.pppg$o++ --> {  datarate = 10000000; delay = 0.1us; } --> R2.pppg$i++;
        R2.pppg$o++ --> {  datarate = 10000000; delay = 0.1us; } --> R1.pppg$i++;

        R2.ethg$o[0] --> {  delay = 0.1us; } --> N2.pppg$i[0];
        N2.pppg$o[0] --> {  delay = 0.1us; } --> R2.ethg$i[0];
        N2.pppg$o[1] --> {  delay = 0.1us; } --> H2.ethg$i[0];
        H2.ethg$o[0] --> {  delay = 0.1us; } --> N2.pppg$i[1];
}

