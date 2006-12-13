simple RTPApplication

{
    parameters:

        string commonName;
        string profileName;
        volatile double bandwidth @unit("bps");
        string destinationAddress = default("");
        volatile int portNumber;
        string fileName;
        volatile int payloadType;
        volatile double sessionEnterDelay @unit("s");
        volatile double transmissionStartDelay @unit("s");
        volatile double transmissionStopDelay @unit("s");
        volatile double sessionLeaveDelay @unit("s");

    gates:
        output toRTP;
        input fromRTP;


}
