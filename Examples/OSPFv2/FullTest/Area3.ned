import "EtherHub";
import "OSPFRouter";
import "StandardHost";

module OSPF_Area3
{
    parameters:
        @display("p=10,10;b=264,528");
    gates:
        //REMOVE THIS LINE
        input ethg[];
    submodules:
        RT9: OSPFRouter {
            parameters:
                @display("p=148,200");
            gates:
                //REMOVE THIS LINE
                ethg[2];
        };
        RT12: OSPFRouter {
            parameters:
                @display("p=148,360");
            gates:
                //REMOVE THIS LINE
                ethg[3];
        };
        N9: EtherHub {
            parameters:
                @display("p=148,284");
            gates:
                //REMOVE THIS LINE
                ethg[4];
        };
        N10: EtherHub {
            parameters:
                @display("p=148,452");
            gates:
                //REMOVE THIS LINE
                ethg[3];
        };
        N11: EtherHub {
            parameters:
                @display("p=144,112");
            gates:
                //REMOVE THIS LINE
                ethg[3];
        };
        H12: StandardHost {
            parameters:
                @display("p=92,52;i=device/pc_s");
            gates:
                //REMOVE THIS LINE
                ethg[1];
        };
        H13: StandardHost {
            parameters:
                @display("p=196,52;i=device/pc_s");
            gates:
                //REMOVE THIS LINE
                ethg[1];
        };
        H14: StandardHost {
            parameters:
                @display("p=60,284;i=device/pc_s");
            gates:
                //REMOVE THIS LINE
                ethg[1];
        };
        H15: StandardHost {
            parameters:
                @display("p=60,360;i=device/pc_s");
            gates:
                //REMOVE THIS LINE
                ethg[1];
        };
        H16: StandardHost {
            parameters:
                @display("p=92,492;i=device/pc_s");
            gates:
                //REMOVE THIS LINE
                ethg[1];
        };
        H17: StandardHost {
            parameters:
                @display("p=196,492;i=device/pc_s");
            gates:
                //REMOVE THIS LINE
                ethg[1];
        };
    connections:
        H12.ethg$o[0] --> {  delay = 0.1us; } --> N11.pppg$i[0];
        N11.pppg$o[0] --> {  delay = 0.1us; } --> H12.ethg$i[0];
        N11.pppg$o[1] --> {  delay = 0.1us; } --> RT9.ethg$i[0];
        RT9.ethg$o[0] --> {  delay = 0.1us; } --> N11.pppg$i[1];
        N11.pppg$o[2] --> {  delay = 0.1us; } --> H13.ethg$i[0];
        H13.ethg$o[0] --> {  delay = 0.1us; } --> N11.pppg$i[2];
        RT9.ethg$o[1] --> {  delay = 0.1us; } --> N9.pppg$i[0];
        N9.pppg$o[0] --> {  delay = 0.1us; } --> RT9.ethg$i[1];
        N9.pppg$o[1] --> {  delay = 0.1us; } --> H14.ethg$i[0];
        H14.ethg$o[0] --> {  delay = 0.1us; } --> N9.pppg$i[1];
        N9.pppg$o[2] --> {  delay = 0.1us; } --> RT12.ethg$i[0];
        RT12.ethg$o[0] --> {  delay = 0.1us; } --> N9.pppg$i[2];
        RT12.ethg$o[1] --> {  delay = 0.1us; } --> H15.ethg$i[0];
        H15.ethg$o[0] --> {  delay = 0.1us; } --> RT12.ethg$i[1];
        RT12.ethg$o[2] --> {  delay = 0.1us; } --> N10.pppg$i[0];
        N10.pppg$o[0] --> {  delay = 0.1us; } --> RT12.ethg$i[2];
        N10.pppg$o[1] --> {  delay = 0.1us; } --> H16.ethg$i[0];
        H16.ethg$o[0] --> {  delay = 0.1us; } --> N10.pppg$i[1];
        N10.pppg$o[2] --> {  delay = 0.1us; } --> H17.ethg$i[0];
        H17.ethg$o[0] --> {  delay = 0.1us; } --> N10.pppg$i[2];

        // towards other areas
        N9.pppg$o[3] --> ethg$o[0];
        ethg$i[0] --> N9.pppg$i[3];
}

