import "EtherHub";
import "OSPFRouter";
import "StandardHost";

module OneNetArea
{
    parameters:
        @display("p=10,10;b=404,108");
    gates:
        inout ethg[];
    submodules:
        H3: StandardHost {
            parameters:
                @display("p=372,72;i=device/laptop");
            gates:
                ethg[1];
        };
        N3: EtherHub {
            parameters:
                @display("p=264,72");
            gates:
                ethg[2];
        };
        R5: OSPFRouter {
            parameters:
                @display("p=160,72");
            gates:
                ethg[2];
        };
        R4: OSPFRouter {
            parameters:
                @display("p=64,72");
            gates:
                ethg[2];
        };
    connections:
        R4.ethg[0] <--> {  delay = 0.1us; } <--> R5.ethg[1];
        R5.ethg[0] <--> {  delay = 0.1us; } <--> N3.ethg[1];
        N3.ethg[0] <--> {  delay = 0.1us; } <--> H3.ethg[0];

        // towards other areas
        ethg[0] <--> R4.ethg[1];
}

