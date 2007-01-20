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


import "Router";
import "StandardHost";
import "FlatNetworkConfigurator";


channel fiberline extends cBasicChannel
{
    parameters:
        delay = 1us;
        datarate = 512*1000000;
}

channel ethernetline extends cBasicChannel
{
    parameters:
        delay = 0.1us;
        datarate = 10*1000000;
}

network FlatNet
{
    submodules:
        configurator: FlatNetworkConfigurator {
            parameters:
                moduleTypes = "Router StandardHost";
                nonIPModuleTypes = "";
                networkAddress = "145.236.0.0";
                netmask = "255.255.0.0";
        };
        rte[57]: Router {
            parameters:
                @display("is=vs");
        };
        cli[2]: StandardHost {
            parameters:
                @display("i=device/laptop_s");
        };
        srv: StandardHost {
            parameters:
                @display("i=device/server_s");
        };
    connections allowunconnected:
        cli[0].pppg$o++ --> ethernetline --> rte[50].pppg$i++;
        cli[0].pppg$i++ <-- ethernetline <-- rte[50].pppg$o++;
        cli[1].pppg$o++ --> ethernetline --> rte[8].pppg$i++;
        cli[1].pppg$i++ <-- ethernetline <-- rte[8].pppg$o++;

        srv.pppg$o++ --> fiberline --> rte[18].pppg$i++;
        srv.pppg$i++ <-- fiberline <-- rte[18].pppg$o++;

        rte[0].pppg$o++ --> fiberline --> rte[1].pppg$i++;
        rte[0].pppg$i++ <-- fiberline <-- rte[1].pppg$o++;

        rte[1].pppg$o++ --> fiberline --> rte[2].pppg$i++;
        rte[1].pppg$i++ <-- fiberline <-- rte[2].pppg$o++;

        rte[1].pppg$o++ --> fiberline --> rte[4].pppg$i++;
        rte[1].pppg$i++ <-- fiberline <-- rte[4].pppg$o++;

        rte[3].pppg$o++ --> fiberline --> rte[4].pppg$i++;
        rte[3].pppg$i++ <-- fiberline <-- rte[4].pppg$o++;

        rte[4].pppg$o++ --> fiberline --> rte[5].pppg$i++;
        rte[4].pppg$i++ <-- fiberline <-- rte[5].pppg$o++;

        rte[4].pppg$o++ --> fiberline --> rte[7].pppg$i++;
        rte[4].pppg$i++ <-- fiberline <-- rte[7].pppg$o++;

        rte[5].pppg$o++ --> fiberline --> rte[6].pppg$i++;
        rte[5].pppg$i++ <-- fiberline <-- rte[6].pppg$o++;

        rte[5].pppg$o++ --> fiberline --> rte[10].pppg$i++;
        rte[5].pppg$i++ <-- fiberline <-- rte[10].pppg$o++;

        rte[6].pppg$o++ --> fiberline --> rte[7].pppg$i++;
        rte[6].pppg$i++ <-- fiberline <-- rte[7].pppg$o++;

        rte[6].pppg$o++ --> fiberline --> rte[9].pppg$i++;
        rte[6].pppg$i++ <-- fiberline <-- rte[9].pppg$o++;

        rte[7].pppg$o++ --> fiberline --> rte[8].pppg$i++;
        rte[7].pppg$i++ <-- fiberline <-- rte[8].pppg$o++;

        rte[7].pppg$o++ --> fiberline --> rte[12].pppg$i++;
        rte[7].pppg$i++ <-- fiberline <-- rte[12].pppg$o++;

        rte[9].pppg$o++ --> fiberline --> rte[11].pppg$i++;
        rte[9].pppg$i++ <-- fiberline <-- rte[11].pppg$o++;

        rte[10].pppg$o++ --> fiberline --> rte[11].pppg$i++;
        rte[10].pppg$i++ <-- fiberline <-- rte[11].pppg$o++;

        rte[10].pppg$o++ --> fiberline --> rte[13].pppg$i++;
        rte[10].pppg$i++ <-- fiberline <-- rte[13].pppg$o++;

        rte[11].pppg$o++ --> fiberline --> rte[12].pppg$i++;
        rte[11].pppg$i++ <-- fiberline <-- rte[12].pppg$o++;

        rte[11].pppg$o++ --> fiberline --> rte[14].pppg$i++;
        rte[11].pppg$i++ <-- fiberline <-- rte[14].pppg$o++;

        rte[12].pppg$o++ --> fiberline --> rte[15].pppg$i++;
        rte[12].pppg$i++ <-- fiberline <-- rte[15].pppg$o++;

        rte[13].pppg$o++ --> fiberline --> rte[18].pppg$i++;
        rte[13].pppg$i++ <-- fiberline <-- rte[18].pppg$o++;

        rte[14].pppg$o++ --> fiberline --> rte[15].pppg$i++;
        rte[14].pppg$i++ <-- fiberline <-- rte[15].pppg$o++;

        rte[14].pppg$o++ --> fiberline --> rte[22].pppg$i++;
        rte[14].pppg$i++ <-- fiberline <-- rte[22].pppg$o++;

        rte[15].pppg$o++ --> fiberline --> rte[16].pppg$i++;
        rte[15].pppg$i++ <-- fiberline <-- rte[16].pppg$o++;

        rte[16].pppg$o++ --> fiberline --> rte[17].pppg$i++;
        rte[16].pppg$i++ <-- fiberline <-- rte[17].pppg$o++;

        rte[16].pppg$o++ --> fiberline --> rte[23].pppg$i++;
        rte[16].pppg$i++ <-- fiberline <-- rte[23].pppg$o++;

        rte[18].pppg$o++ --> fiberline --> rte[19].pppg$i++;
        rte[18].pppg$i++ <-- fiberline <-- rte[19].pppg$o++;

        rte[18].pppg$o++ --> fiberline --> rte[21].pppg$i++;
        rte[18].pppg$i++ <-- fiberline <-- rte[21].pppg$o++;

        rte[19].pppg$o++ --> fiberline --> rte[20].pppg$i++;
        rte[19].pppg$i++ <-- fiberline <-- rte[20].pppg$o++;

        rte[19].pppg$o++ --> fiberline --> rte[26].pppg$i++;
        rte[19].pppg$i++ <-- fiberline <-- rte[26].pppg$o++;

        rte[20].pppg$o++ --> fiberline --> rte[21].pppg$i++;
        rte[20].pppg$i++ <-- fiberline <-- rte[21].pppg$o++;

        rte[20].pppg$o++ --> fiberline --> rte[24].pppg$i++;
        rte[20].pppg$i++ <-- fiberline <-- rte[24].pppg$o++;

        rte[20].pppg$o++ --> fiberline --> rte[25].pppg$i++;
        rte[20].pppg$i++ <-- fiberline <-- rte[25].pppg$o++;

        rte[21].pppg$o++ --> fiberline --> rte[22].pppg$i++;
        rte[21].pppg$i++ <-- fiberline <-- rte[22].pppg$o++;

        rte[21].pppg$o++ --> fiberline --> rte[23].pppg$i++;
        rte[21].pppg$i++ <-- fiberline <-- rte[23].pppg$o++;

        rte[21].pppg$o++ --> fiberline --> rte[24].pppg$i++;
        rte[21].pppg$i++ <-- fiberline <-- rte[24].pppg$o++;

        rte[23].pppg$o++ --> fiberline --> rte[24].pppg$i++;
        rte[23].pppg$i++ <-- fiberline <-- rte[24].pppg$o++;

        rte[24].pppg$o++ --> fiberline --> rte[28].pppg$i++;
        rte[24].pppg$i++ <-- fiberline <-- rte[28].pppg$o++;

        rte[25].pppg$o++ --> fiberline --> rte[27].pppg$i++;
        rte[25].pppg$i++ <-- fiberline <-- rte[27].pppg$o++;

        rte[26].pppg$o++ --> fiberline --> rte[32].pppg$i++;
        rte[26].pppg$i++ <-- fiberline <-- rte[32].pppg$o++;

        rte[27].pppg$o++ --> fiberline --> rte[29].pppg$i++;
        rte[27].pppg$i++ <-- fiberline <-- rte[29].pppg$o++;

        rte[27].pppg$o++ --> fiberline --> rte[30].pppg$i++;
        rte[27].pppg$i++ <-- fiberline <-- rte[30].pppg$o++;

        rte[27].pppg$o++ --> fiberline --> rte[32].pppg$i++;
        rte[27].pppg$i++ <-- fiberline <-- rte[32].pppg$o++;

        rte[28].pppg$o++ --> fiberline --> rte[29].pppg$i++;
        rte[28].pppg$i++ <-- fiberline <-- rte[29].pppg$o++;

        rte[28].pppg$o++ --> fiberline --> rte[31].pppg$i++;
        rte[28].pppg$i++ <-- fiberline <-- rte[31].pppg$o++;

        rte[29].pppg$o++ --> fiberline --> rte[31].pppg$i++;
        rte[29].pppg$i++ <-- fiberline <-- rte[31].pppg$o++;

        rte[30].pppg$o++ --> fiberline --> rte[36].pppg$i++;
        rte[30].pppg$i++ <-- fiberline <-- rte[36].pppg$o++;

        rte[31].pppg$o++ --> fiberline --> rte[33].pppg$i++;
        rte[31].pppg$i++ <-- fiberline <-- rte[33].pppg$o++;

        rte[32].pppg$o++ --> fiberline --> rte[34].pppg$i++;
        rte[32].pppg$i++ <-- fiberline <-- rte[34].pppg$o++;

        rte[33].pppg$o++ --> fiberline --> rte[37].pppg$i++;
        rte[33].pppg$i++ <-- fiberline <-- rte[37].pppg$o++;

        rte[34].pppg$o++ --> fiberline --> rte[35].pppg$i++;
        rte[34].pppg$i++ <-- fiberline <-- rte[35].pppg$o++;

        rte[34].pppg$o++ --> fiberline --> rte[40].pppg$i++;
        rte[34].pppg$i++ <-- fiberline <-- rte[40].pppg$o++;

        rte[35].pppg$o++ --> fiberline --> rte[36].pppg$i++;
        rte[35].pppg$i++ <-- fiberline <-- rte[36].pppg$o++;

        rte[35].pppg$o++ --> fiberline --> rte[39].pppg$i++;
        rte[35].pppg$i++ <-- fiberline <-- rte[39].pppg$o++;

        rte[36].pppg$o++ --> fiberline --> rte[37].pppg$i++;
        rte[36].pppg$i++ <-- fiberline <-- rte[37].pppg$o++;

        rte[37].pppg$o++ --> fiberline --> rte[38].pppg$i++;
        rte[37].pppg$i++ <-- fiberline <-- rte[38].pppg$o++;

        rte[38].pppg$o++ --> fiberline --> rte[39].pppg$i++;
        rte[38].pppg$i++ <-- fiberline <-- rte[39].pppg$o++;

        rte[38].pppg$o++ --> fiberline --> rte[42].pppg$i++;
        rte[38].pppg$i++ <-- fiberline <-- rte[42].pppg$o++;

        rte[39].pppg$o++ --> fiberline --> rte[40].pppg$i++;
        rte[39].pppg$i++ <-- fiberline <-- rte[40].pppg$o++;

        rte[39].pppg$o++ --> fiberline --> rte[41].pppg$i++;
        rte[39].pppg$i++ <-- fiberline <-- rte[41].pppg$o++;

        rte[40].pppg$o++ --> fiberline --> rte[43].pppg$i++;
        rte[40].pppg$i++ <-- fiberline <-- rte[43].pppg$o++;

        rte[40].pppg$o++ --> fiberline --> rte[44].pppg$i++;
        rte[40].pppg$i++ <-- fiberline <-- rte[44].pppg$o++;

        rte[40].pppg$o++ --> fiberline --> rte[52].pppg$i++;
        rte[40].pppg$i++ <-- fiberline <-- rte[52].pppg$o++;

        rte[41].pppg$o++ --> fiberline --> rte[42].pppg$i++;
        rte[41].pppg$i++ <-- fiberline <-- rte[42].pppg$o++;

        rte[41].pppg$o++ --> fiberline --> rte[43].pppg$i++;
        rte[41].pppg$i++ <-- fiberline <-- rte[43].pppg$o++;

        rte[42].pppg$o++ --> fiberline --> rte[43].pppg$i++;
        rte[42].pppg$i++ <-- fiberline <-- rte[43].pppg$o++;

        rte[43].pppg$o++ --> fiberline --> rte[46].pppg$i++;
        rte[43].pppg$i++ <-- fiberline <-- rte[46].pppg$o++;

        rte[44].pppg$o++ --> fiberline --> rte[45].pppg$i++;
        rte[44].pppg$i++ <-- fiberline <-- rte[45].pppg$o++;

        rte[44].pppg$o++ --> fiberline --> rte[47].pppg$i++;
        rte[44].pppg$i++ <-- fiberline <-- rte[47].pppg$o++;

        rte[45].pppg$o++ --> fiberline --> rte[46].pppg$i++;
        rte[45].pppg$i++ <-- fiberline <-- rte[46].pppg$o++;

        rte[46].pppg$o++ --> fiberline --> rte[49].pppg$i++;
        rte[46].pppg$i++ <-- fiberline <-- rte[49].pppg$o++;

        rte[47].pppg$o++ --> fiberline --> rte[48].pppg$i++;
        rte[47].pppg$i++ <-- fiberline <-- rte[48].pppg$o++;

        rte[48].pppg$o++ --> fiberline --> rte[50].pppg$i++;
        rte[48].pppg$i++ <-- fiberline <-- rte[50].pppg$o++;

        rte[48].pppg$o++ --> fiberline --> rte[51].pppg$i++;
        rte[48].pppg$i++ <-- fiberline <-- rte[51].pppg$o++;

        rte[49].pppg$o++ --> fiberline --> rte[50].pppg$i++;
        rte[49].pppg$i++ <-- fiberline <-- rte[50].pppg$o++;

        rte[50].pppg$o++ --> fiberline --> rte[53].pppg$i++;
        rte[50].pppg$i++ <-- fiberline <-- rte[53].pppg$o++;

        rte[51].pppg$o++ --> fiberline --> rte[52].pppg$i++;
        rte[51].pppg$i++ <-- fiberline <-- rte[52].pppg$o++;

        rte[51].pppg$o++ --> fiberline --> rte[53].pppg$i++;
        rte[51].pppg$i++ <-- fiberline <-- rte[53].pppg$o++;

        rte[52].pppg$o++ --> fiberline --> rte[53].pppg$i++;
        rte[52].pppg$i++ <-- fiberline <-- rte[53].pppg$o++;

        rte[52].pppg$o++ --> fiberline --> rte[54].pppg$i++;
        rte[52].pppg$i++ <-- fiberline <-- rte[54].pppg$o++;

        rte[53].pppg$o++ --> fiberline --> rte[56].pppg$i++;
        rte[53].pppg$i++ <-- fiberline <-- rte[56].pppg$o++;

        rte[54].pppg$o++ --> fiberline --> rte[55].pppg$i++;
        rte[54].pppg$i++ <-- fiberline <-- rte[55].pppg$o++;

        rte[55].pppg$o++ --> fiberline --> rte[56].pppg$i++;
        rte[55].pppg$i++ <-- fiberline <-- rte[56].pppg$o++;
}

