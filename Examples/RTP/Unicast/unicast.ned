import "RTPHost";


channel ErrorChannel extends cBasicChannel
{
    parameters:
        //delay normal (0.004, 0.0041)
        error = 0.0;
}

network RTPNetwork

{
    parameters:
        bool debug;

    submodules:
        sender: RTPHost {
            parameters:
                debug = debug;
                profileName = "RTPAVProfile";
                destinationAddress = "10.0.0.2";
                portNumber = 5004;
                bandwidth = 8000;
                fileName = "../Data/moving.mpg.gdf";
                payloadType = 32;
                numOfProcessors = 1;
                routingFile = "server1.irt";
        };
        receiver: RTPHost {
            parameters:
                debug = debug;
                profileName = "RTPAVProfile";
                destinationAddress = "10.0.0.1";
                portNumber = 5004;
                bandwidth = 8000;
                fileName = "";
                payloadType = 0;
                numOfProcessors = 1;
                routingFile = "client2.irt";

        };
    connections:
        sender.out[0] --> ErrorChannel --> receiver.in[0];
        sender.in[0] <-- ErrorChannel <-- receiver.out[0];

}

