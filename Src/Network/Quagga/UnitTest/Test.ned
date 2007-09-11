
channel ethernetlineX extends cBasicChannel
{
    parameters:
        delay = 10ms;
        datarate = 100000;
}

network Test
{
    submodules:
        channelInstaller: ChannelInstaller {
            parameters:
                channelClass = "ThruputMeteringChannel";
                channelAttrs = "format=u #N";
                @display("p=284,50");

        };
        r1: TestRouter {
            parameters:
                @display("p=100,30");

            gates:
                in[2];
                out[2];
        };
        r2: TestRouter {
            parameters:
                @display("p=50,100");

            gates:
                in[4];
                out[4];
        };
        r3: TestRouter {
            parameters:
                @display("p=150,100");

            gates:
                in[4];
                out[4];
        };
        r4: TestRouter {
            parameters:
                @display("p=10,150");

            gates:
                in[2];
                out[2];
        };
        r5: TestRouter {
            parameters:
                @display("p=100,150");

            gates:
                in[3];
                out[3];
        };
    connections allowunconnected:
        r1.out[0] --> ethernetlineX --> r2.in[0];
        r1.in[0] <-- ethernetlineX <-- r2.out[0];

        r1.out[1] --> ethernetlineX --> r3.in[0];
        r1.in[1] <-- ethernetlineX <-- r3.out[0];

        r2.out[1] --> ethernetlineX --> r3.in[1];
        r2.in[1] <-- ethernetlineX <-- r3.out[1];

        r2.out[2] --> ethernetlineX --> r4.in[0];
        r2.in[2] <-- ethernetlineX <-- r4.out[0];

        r2.out[3] --> ethernetlineX --> r5.in[0];
        r2.in[3] <-- ethernetlineX <-- r5.out[0];

        r3.out[2] --> ethernetlineX --> r5.in[1];
        r3.in[2] <-- ethernetlineX <-- r5.out[1];

        r4.out[1] --> ethernetlineX --> r5.in[2];
        r4.in[1] <-- ethernetlineX <-- r5.out[2];
}

