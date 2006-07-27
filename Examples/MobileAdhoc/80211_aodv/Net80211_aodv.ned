//
// Copyright (C) 2005 Andras Varga
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


import
    "MobileHostRouting",
    "ChannelControl";


module Net80211_aodv
    parameters:
        numHosts: numeric const,
        numFixHosts: numeric const,
        playgroundSizeX: numeric const,
        playgroundSizeY: numeric const;
    submodules:
        fixhost: FixManetRoutingHost[numFixHosts];
            display: "i=device/pocketpc_s;r=,,#707070";
        host: MobileManetRoutingHost[numHosts];
            display: "i=device/pocketpc_s;r=,,#707070";
        channelcontrol: ChannelControl;
            parameters:
                playgroundSizeX = playgroundSizeX,
                playgroundSizeY = playgroundSizeY;
            display: "p=60,50;i=misc/sun";
        configurator: FlatNetworkConfigurator;
            parameters:
                moduleTypes = "MobileManetRoutingHost FixManetRoutingHost",
                nonIPModuleTypes = "",
                networkAddress = "145.236.0.0",
                netmask = "255.255.0.0";
            display: "p=140,50;i=block/cogwheel_s";
    connections nocheck:
endmodule

network net80211_aodv : Net80211_aodv
endnetwork

