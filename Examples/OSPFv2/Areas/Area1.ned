import "EtherHub";
import "OSPFRouter";
import "StandardHost";

module TwoNetsArea
{
    parameters:
        @display("p=10,10;b=412,316");
    gates:
        inout ethg[];
    submodules:
        R1: OSPFRouter {
            parameters:
                @display("p=248,124");
            gates:
                ethg[3];
        };
        N1: EtherHub {
            parameters:
                @display("p=156,72");
            gates:
                ethg[2];
        };
        N2: EtherHub {
            parameters:
                @display("p=160,284");
            gates:
                ethg[2];
        };
        R3: OSPFRouter {
            parameters:
                @display("p=360,180");
            gates:
                ethg[3];
        };
        H1: StandardHost {
            parameters:
                @display("p=56,72;i=device/laptop");
            gates:
                ethg[1];
        };
        H2: StandardHost {
            parameters:
                @display("p=56,288;i=device/laptop");
            gates:
                ethg[1];
        };
        R2: OSPFRouter {
            parameters:
                @display("p=248,232");
            gates:
                ethg[3];
        };
    connections:
        H1.ethg[0] <--> {  delay = 0.1us; } <--> N1.ethg[1];
        N1.ethg[0] <--> {  delay = 0.1us; } <--> R1.ethg[2];
        R1.ethg[0] <--> {  delay = 0.1us; } <--> R3.ethg[2];
        N2.ethg[1] <--> {  delay = 0.1us; } <--> H2.ethg[0];
        R1.ethg[1] <--> {  delay = 0.1us; } <--> R2.ethg[0];
        R2.ethg[1] <--> {  delay = 0.1us; } <--> R3.ethg[1];
        R2.ethg[2] <--> {  delay = 0.1us; } <--> N2.ethg[0];

        // towards other areas
        ethg[0] <--> R3.ethg[0];
}

