import "OSPFAreaTest_Area1";
import "OSPFAreaTest_Area2";
import "ChannelInstaller";


network OSPF_AreaTest
{
    submodules:
        channelInstaller: ChannelInstaller {
            parameters:
                channelClass = "ThruputMeteringChannel";
                channelAttrs = "format=#N";
                @display("p=456,36");
        };
        Area1: TwoNetsArea {
            parameters:
                @display("p=108,112;b=136,128");
            gates:
                in[1];
                out[1];
        };
        Area2: OneNetArea {
            parameters:
                @display("p=324,112;b=136,128");
            gates:
                in[1];
                out[1];
        };
    connections:
        Area1.pppg$o[0] --> {  delay = 0.1us; } --> Area2.pppg$i[0];
        Area2.pppg$o[0] --> {  delay = 0.1us; } --> Area1.pppg$i[0];
}

