import "EtherHub";
import "OSPFRouter";
import "StandardHost";

module OSPF_Area2
{
    parameters:
        @display("p=10,10;b=424,400");
    gates:
        input in[];
        output out[];
    submodules:
        RT8: OSPFRouter {
            parameters:
                @display("p=304,196");
            gates:
                ethIn[2];
                ethOut[2];
        };
        N6: EtherHub {
            parameters:
                @display("p=304,100");
            gates:
                in[4];
                out[4];
        };
        N7: EtherHub {
            parameters:
                @display("p=304,300");
            gates:
                in[3];
                out[3];
        };
        N8: EtherHub {
            parameters:
                @display("p=104,100");
            gates:
                in[3];
                out[3];
        };
        H8: StandardHost {
            parameters:
                @display("p=392,100;i=device/pc_s");
            gates:
                ethIn[1];
                ethOut[1];
        };
        H9: StandardHost {
            parameters:
                @display("p=348,364;i=device/pc_s");
            gates:
                ethIn[1];
                ethOut[1];
        };
        H10: StandardHost {
            parameters:
                @display("p=260,364;i=device/pc_s");
            gates:
                ethIn[1];
                ethOut[1];
        };
        H11: StandardHost {
            parameters:
                @display("p=104,156;i=device/pc_s");
            gates:
                ethIn[1];
                ethOut[1];
        };
    connections:
        N8.pppg$o[1] --> {  delay = 0.1us; } --> H11.ethg$i[0];
        H11.ethg$o[0] --> {  delay = 0.1us; } --> N8.pppg$i[1];
        N6.pppg$o[2] --> {  delay = 0.1us; } --> RT8.ethg$i[0];
        RT8.ethg$o[0] --> {  delay = 0.1us; } --> N6.pppg$i[2];
        N6.pppg$o[3] --> {  delay = 0.1us; } --> H8.ethg$i[0];
        H8.ethg$o[0] --> {  delay = 0.1us; } --> N6.pppg$i[3];
        RT8.ethg$o[1] --> {  delay = 0.1us; } --> N7.pppg$i[0];
        N7.pppg$o[0] --> {  delay = 0.1us; } --> RT8.ethg$i[1];
        N7.pppg$o[1] --> {  delay = 0.1us; } --> H10.ethg$i[0];
        H10.ethg$o[0] --> {  delay = 0.1us; } --> N7.pppg$i[1];
        N7.pppg$o[2] --> {  delay = 0.1us; } --> H9.ethg$i[0];
        H9.ethg$o[0] --> {  delay = 0.1us; } --> N7.pppg$i[2];

        // towards other areas
        N8.pppg$o[0] --> out[0];
        in[0] --> N8.pppg$i[0];
        N8.pppg$o[2] --> { @display("m=m,52,64,40,0"); } --> out[1];
        in[1] --> { @display("m=m,40,0,64,8"); } --> N8.pppg$i[2];
        N6.pppg$o[1] --> { @display("m=m,28,36,48,0"); } --> out[2];
        in[2] --> { @display("m=m,48,0,28,28"); } --> N6.pppg$i[1];
        N6.pppg$o[0] --> out[3];
        in[3] --> N6.pppg$i[0];
}

