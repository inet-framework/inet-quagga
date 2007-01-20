//
// Copyright (C) 2004 Emin Ilker Cetinbas (niw3@yahoo.com)
//
// This library is free software, you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation;
// either version 2 of the License, or any later version.
// The library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//

import "Router";
import "StandardHost";
import "EtherBus";
import "FlatNetworkConfigurator";


network ARPTest
{
    submodules:
        server: StandardHost {
            parameters:
                @display("p=480,198;i=device/server_l");
        };
        router8: Router {
            parameters:
                @display("p=478,100");
        };
        router7: Router {
            parameters:
                @display("p=329,100");
        };
        router6: Router {
            parameters:
                @display("p=254,100");
        };
        bus2: EtherBus {
            parameters:
                positions = "";
                propagationSpeed = 2e8;
                writeScalars = false;
                @display("p=260,40;b=260,10");
        };
        router5: Router {
            parameters:
                @display("p=187,98");
        };
        bus1: EtherBus {
            parameters:
                positions = "";
                propagationSpeed = 2e8;
                writeScalars = false;
                @display("p=280,170;b=260,10");
        };
        router4: Router {
            parameters:
                @display("p=386,240");
        };
        router3: Router {
            parameters:
                @display("p=320,240");
        };
        router2: Router {
            parameters:
                @display("p=247,240");
        };
        router1: Router {
            parameters:
                @display("p=182,283");
        };
        client: StandardHost {
            parameters:
                @display("p=54,274;i=device/laptop_l");
        };
        configurator: FlatNetworkConfigurator {
            parameters:
                moduleTypes = "Router StandardHost EtherBus";
                nonIPModuleTypes = "EtherBus";
                networkAddress = "10.0.0.0";
                netmask = "255.255.0.0";
                @display("p=46,111");
        };
    connections:
        server.ethg$o++ --> router8.ethg$i++;
        router8.ethg$o++ --> server.ethg$i++;

        bus2.ethg$o++ --> router5.ethg$i++;
        router5.ethg$o++ --> bus2.ethg$i++;

        bus2.ethg$o++ --> router6.ethg$i++;
        router6.ethg$o++ --> bus2.ethg$i++;

        bus2.ethg$o++ --> router7.ethg$i++;
        router7.ethg$o++ --> bus2.ethg$i++;

        router8.ethg$o++ --> router7.ethg$i++;
        router7.ethg$o++ --> router8.ethg$i++;

        bus1.ethg$o++ --> router1.ethg$i++;
        router1.ethg$o++ --> bus1.ethg$i++;

        bus1.ethg$o++ --> router5.ethg$i++;
        router5.ethg$o++ --> bus1.ethg$i++;

        bus1.ethg$o++ --> router2.ethg$i++;
        router2.ethg$o++ --> bus1.ethg$i++;

        bus1.ethg$o++ --> router3.ethg$i++;
        router3.ethg$o++ --> bus1.ethg$i++;

        bus1.ethg$o++ --> router4.ethg$i++;
        router4.ethg$o++ --> bus1.ethg$i++;

        client.ethg$o++ --> router1.ethg$i++;
        router1.ethg$o++ --> client.ethg$i++;
}

