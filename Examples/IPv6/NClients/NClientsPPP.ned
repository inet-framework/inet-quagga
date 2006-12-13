//
// Copyright (C) 2004 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//


import "Router6";
import "StandardHost6";
import "FlatNetworkConfigurator6";


channel fiberline extends cBasicChannel
{
    parameters:
        delay = 1us;
        datarate = 512*1000000;
}

network NClientsPPP
{
    parameters:
        double n;
    submodules:
        configurator: FlatNetworkConfigurator6 {
            parameters:
                moduleTypes = "Router6 StandardHost6";
                nonIPModuleTypes = "";
                @display("");
        };
        r1: Router6 {
            parameters:
                @display("");
        };
        r2: Router6 {
            parameters:
                @display("");
        };
        r3: Router6 {
            parameters:
                @display("");
        };
        cli[n]: StandardHost6 {
            parameters:
                @display("");
        };
        srv: StandardHost6 {
            parameters:
                @display("");
        };
    connections allowunconnected:
        for i=0..n-1 {
            cli[i].out++ --> fiberline --> r1.in++;
            cli[i].in++ <-- fiberline <-- r1.out++;
        };

        r1.out++ --> fiberline --> r2.in++;
        r1.in++ <-- fiberline <-- r2.out++;

        r2.out++ --> fiberline --> r3.in++;
        r2.in++ <-- fiberline <-- r3.out++;

        r3.out++ --> fiberline --> srv.in++;
        r3.in++ <-- fiberline <-- srv.out++;

}

