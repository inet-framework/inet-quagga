import "EtherHub";
import "OSPFRouter";
import "StandardHost";

module OneNetArea
{
    parameters:
        @display("p=10,10;b=404,108");
    gates:
        input in[];
        output out[];
    submodules:
        H3: StandardHost {
            parameters:
                @display("p=372,72;i=device/laptop");
            gates:
                ethIn[1];
                ethOut[1];
        };
        N3: EtherHub {
            parameters:
                @display("p=264,72");
            gates:
                in[2];
                out[2];
        };
        R5: OSPFRouter {
            parameters:
                @display("p=160,72");
            gates:
                ethIn[2];
                ethOut[2];
        };
        R4: OSPFRouter {
            parameters:
                @display("p=64,72");
            gates:
                ethIn[2];
                ethOut[2];
        };
    connections:
        R4.ethg$o[0] --> {  delay = 0.1us; } --> R5.ethg$i[1];
        R5.ethg$o[1] --> {  delay = 0.1us; } --> R4.ethg$i[0];
        R5.ethg$o[0] --> {  delay = 0.1us; } --> N3.pppg$i[1];
        N3.pppg$o[1] --> {  delay = 0.1us; } --> R5.ethg$i[0];
        N3.pppg$o[0] --> {  delay = 0.1us; } --> H3.ethg$i[0];
        H3.ethg$o[0] --> {  delay = 0.1us; } --> N3.pppg$i[0];

        // towards other areas
        in[0] --> R4.ethg$i[1];
        R4.ethg$o[1] --> out[0];
}

