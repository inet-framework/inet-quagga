//
// This library is free software, you can redistribute it
// and/or modify
// it under  the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation;
// either version 2 of the License, or any later version.
// The library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//

channel net37ch extends cBasicChannel
{
    parameters:
        delay = 15ms;
        datarate = 128kbps;
}

network R37
{
    submodules:
        configurator: NetworkConfigurator {
            parameters:
                moduleTypes = "RSVP_LSR StandardHost";
                @display("p=100,100");
        };
        channelInstaller: ChannelInstaller {
            parameters:
                channelClass = "ThruputMeteringChannel";
                channelAttrs = "format=u";
                @display("p=100,160");
        };
        nam: NAMTrace {
            parameters:
                @display("p=100,220");
        };
        LSR0: RSVP_LSR {
            parameters:
                @display("p=391,225");
        };
        LSR1: RSVP_LSR {
            parameters:
                @display("p=799,589");
        };
        LSR2: RSVP_LSR {
            parameters:
                @display("p=289,472");
        };
        LSR3: RSVP_LSR {
            parameters:
                @display("p=712,418");
        };
        LSR4: RSVP_LSR {
            parameters:
                @display("p=541,228");
        };
        LSR5: RSVP_LSR {
            parameters:
                @display("p=288,169");
        };
        LSR6: RSVP_LSR {
            parameters:
                @display("p=256,394");
        };
        LSR7: RSVP_LSR {
            parameters:
                @display("p=380,263");
        };
        LSR8: RSVP_LSR {
            parameters:
                @display("p=682,348");
        };
        LSR9: RSVP_LSR {
            parameters:
                @display("p=536,142");
        };
        LSR10: RSVP_LSR {
            parameters:
                @display("p=177,170");
        };
        LSR11: RSVP_LSR {
            parameters:
                @display("p=424,262");
        };
        LSR12: RSVP_LSR {
            parameters:
                @display("p=470,279");
        };
        LSR13: RSVP_LSR {
            parameters:
                @display("p=278,91");
        };
        LSR14: RSVP_LSR {
            parameters:
                @display("p=467,214");
        };
        LSR15: RSVP_LSR {
            parameters:
                @display("p=724,19");
        };
        LSR16: RSVP_LSR {
            parameters:
                @display("p=685,287");
        };
        LSR17: RSVP_LSR {
            parameters:
                @display("p=20,519");
        };
        LSR18: RSVP_LSR {
            parameters:
                @display("p=298,236");
        };
        LSR19: RSVP_LSR {
            parameters:
                @display("p=390,390");
        };
        LSR20: RSVP_LSR {
            parameters:
                @display("p=148,502");
        };
        LSR21: RSVP_LSR {
            parameters:
                @display("p=362,448");
        };
        LSR22: RSVP_LSR {
            parameters:
                @display("p=476,397");
        };
        LSR23: RSVP_LSR {
            parameters:
                @display("p=517,325");
        };
        LSR24: RSVP_LSR {
            parameters:
                @display("p=514,34");
        };
        LSR25: RSVP_LSR {
            parameters:
                @display("p=548,599");
        };
        LSR26: RSVP_LSR {
            parameters:
                @display("p=330,301");
        };
        LSR27: RSVP_LSR {
            parameters:
                @display("p=612,310");
        };
        LSR28: RSVP_LSR {
            parameters:
                @display("p=556,502");
        };
        LSR29: RSVP_LSR {
            parameters:
                @display("p=83,570");
        };
        LSR30: RSVP_LSR {
            parameters:
                @display("p=796,466");
        };
        LSR31: RSVP_LSR {
            parameters:
                @display("p=610,65");
        };
        LSR32: RSVP_LSR {
            parameters:
                @display("p=435,321");
        };
        LSR33: RSVP_LSR {
            parameters:
                @display("p=605,337");
        };
        LSR34: RSVP_LSR {
            parameters:
                @display("p=707,227");
        };
        LSR35: RSVP_LSR {
            parameters:
                @display("p=613,405");
        };
        LSR36: RSVP_LSR {
            parameters:
                @display("p=435,361");

        };
        host1: StandardHost {
            parameters:
                @display("p=299,522;i=device/laptop_s");
        };
        host2: StandardHost {
            parameters:
                @display("p=757,227;i=device/laptop_s");

        };
    connections:
        LSR7.pppg++ <--> net37ch <--> LSR0.pppg++;
        LSR7.pppg$i++ <-- net37ch <-- LSR0.pppg$o++; // cost 259
        LSR8.pppg++ <--> net37ch <--> LSR3.pppg++;
        LSR8.pppg$i++ <-- net37ch <-- LSR3.pppg$o++; // cost 474
        LSR9.pppg++ <--> net37ch <--> LSR4.pppg++;
        LSR9.pppg$i++ <-- net37ch <-- LSR4.pppg$o++; // cost 540
        LSR11.pppg++ <--> net37ch <--> LSR7.pppg++;
        LSR11.pppg$i++ <-- net37ch <-- LSR7.pppg$o++; // cost 264
        LSR12.pppg++ <--> net37ch <--> LSR11.pppg++;
        LSR12.pppg$i++ <-- net37ch <-- LSR11.pppg$o++; // cost 275
        LSR13.pppg++ <--> net37ch <--> LSR0.pppg++;
        LSR13.pppg$i++ <-- net37ch <-- LSR0.pppg$o++; // cost 1067
        LSR13.pppg++ <--> net37ch <--> LSR5.pppg++;
        LSR13.pppg$i++ <-- net37ch <-- LSR5.pppg$o++; // cost 610
        LSR13.pppg++ <--> net37ch <--> LSR10.pppg++;
        LSR13.pppg$i++ <-- net37ch <-- LSR10.pppg$o++; // cost 462
        LSR14.pppg++ <--> net37ch <--> LSR0.pppg++;
        LSR14.pppg$i++ <-- net37ch <-- LSR0.pppg$o++; // cost 552
        LSR14.pppg++ <--> net37ch <--> LSR4.pppg++;
        LSR14.pppg$i++ <-- net37ch <-- LSR4.pppg$o++; // cost 381
        LSR14.pppg++ <--> net37ch <--> LSR12.pppg++;
        LSR14.pppg$i++ <-- net37ch <-- LSR12.pppg$o++; // cost 592
        LSR16.pppg++ <--> net37ch <--> LSR8.pppg++;
        LSR16.pppg$i++ <-- net37ch <-- LSR8.pppg$o++; // cost 436
        LSR18.pppg++ <--> net37ch <--> LSR0.pppg++;
        LSR18.pppg$i++ <-- net37ch <-- LSR0.pppg$o++; // cost 540
        LSR18.pppg++ <--> net37ch <--> LSR5.pppg++;
        LSR18.pppg$i++ <-- net37ch <-- LSR5.pppg$o++; // cost 239
        LSR18.pppg++ <--> net37ch <--> LSR10.pppg++;
        LSR18.pppg$i++ <-- net37ch <-- LSR10.pppg$o++; // cost 690
        LSR18.pppg++ <--> net37ch <--> LSR17.pppg++;
        LSR18.pppg$i++ <-- net37ch <-- LSR17.pppg$o++; // cost 1977
        LSR20.pppg++ <--> net37ch <--> LSR2.pppg++;
        LSR20.pppg$i++ <-- net37ch <-- LSR2.pppg$o++; // cost 760
        LSR20.pppg++ <--> net37ch <--> LSR6.pppg++;
        LSR20.pppg$i++ <-- net37ch <-- LSR6.pppg$o++; // cost 834
        LSR20.pppg++ <--> net37ch <--> LSR17.pppg++;
        LSR20.pppg$i++ <-- net37ch <-- LSR17.pppg$o++; // cost 751
        LSR21.pppg++ <--> net37ch <--> LSR2.pppg++;
        LSR21.pppg$i++ <-- net37ch <-- LSR2.pppg$o++; // cost 508
        LSR21.pppg++ <--> net37ch <--> LSR6.pppg++;
        LSR21.pppg$i++ <-- net37ch <-- LSR6.pppg$o++; // cost 756
        LSR21.pppg++ <--> net37ch <--> LSR19.pppg++;
        LSR21.pppg$i++ <-- net37ch <-- LSR19.pppg$o++; // cost 411
        LSR23.pppg++ <--> net37ch <--> LSR4.pppg++;
        LSR23.pppg$i++ <-- net37ch <-- LSR4.pppg$o++; // cost 757
        LSR23.pppg++ <--> net37ch <--> LSR12.pppg++;
        LSR23.pppg$i++ <-- net37ch <-- LSR12.pppg$o++; // cost 456
        LSR23.pppg++ <--> net37ch <--> LSR22.pppg++;
        LSR23.pppg$i++ <-- net37ch <-- LSR22.pppg$o++; // cost 522
        LSR24.pppg++ <--> net37ch <--> LSR9.pppg++;
        LSR24.pppg$i++ <-- net37ch <-- LSR9.pppg$o++; // cost 722
        LSR24.pppg++ <--> net37ch <--> LSR15.pppg++;
        LSR24.pppg$i++ <-- net37ch <-- LSR15.pppg$o++; // cost 1182
        LSR25.pppg++ <--> net37ch <--> LSR1.pppg++;
        LSR25.pppg$i++ <-- net37ch <-- LSR1.pppg$o++; // cost 1363
        LSR26.pppg++ <--> net37ch <--> LSR6.pppg++;
        LSR26.pppg$i++ <-- net37ch <-- LSR6.pppg$o++; // cost 747
        LSR26.pppg++ <--> net37ch <--> LSR7.pppg++;
        LSR26.pppg$i++ <-- net37ch <-- LSR7.pppg$o++; // cost 393
        LSR26.pppg++ <--> net37ch <--> LSR18.pppg++;
        LSR26.pppg$i++ <-- net37ch <-- LSR18.pppg$o++; // cost 514
        LSR26.pppg++ <--> net37ch <--> LSR19.pppg++;
        LSR26.pppg$i++ <-- net37ch <-- LSR19.pppg$o++; // cost 594
        LSR27.pppg++ <--> net37ch <--> LSR4.pppg++;
        LSR27.pppg$i++ <-- net37ch <-- LSR4.pppg$o++; // cost 420
        LSR27.pppg++ <--> net37ch <--> LSR8.pppg++;
        LSR27.pppg$i++ <-- net37ch <-- LSR8.pppg$o++; // cost 668
        LSR28.pppg++ <--> net37ch <--> LSR21.pppg++;
        LSR28.pppg$i++ <-- net37ch <-- LSR21.pppg$o++; // cost 907
        LSR28.pppg++ <--> net37ch <--> LSR22.pppg++;
        LSR28.pppg$i++ <-- net37ch <-- LSR22.pppg$o++; // cost 720
        LSR28.pppg++ <--> net37ch <--> LSR25.pppg++;
        LSR28.pppg$i++ <-- net37ch <-- LSR25.pppg$o++; // cost 638
        LSR29.pppg++ <--> net37ch <--> LSR2.pppg++;
        LSR29.pppg$i++ <-- net37ch <-- LSR2.pppg$o++; // cost 1244
        LSR29.pppg++ <--> net37ch <--> LSR17.pppg++;
        LSR29.pppg$i++ <-- net37ch <-- LSR17.pppg$o++; // cost 471
        LSR30.pppg++ <--> net37ch <--> LSR1.pppg++;
        LSR30.pppg$i++ <-- net37ch <-- LSR1.pppg$o++; // cost 794
        LSR30.pppg++ <--> net37ch <--> LSR3.pppg++;
        LSR30.pppg$i++ <-- net37ch <-- LSR3.pppg$o++; // cost 487
        LSR31.pppg++ <--> net37ch <--> LSR9.pppg++;
        LSR31.pppg$i++ <-- net37ch <-- LSR9.pppg$o++; // cost 777
        LSR31.pppg++ <--> net37ch <--> LSR15.pppg++;
        LSR31.pppg$i++ <-- net37ch <-- LSR15.pppg$o++; // cost 597
        LSR32.pppg++ <--> net37ch <--> LSR12.pppg++;
        LSR32.pppg$i++ <-- net37ch <-- LSR12.pppg$o++; // cost 271
        LSR32.pppg++ <--> net37ch <--> LSR26.pppg++;
        LSR32.pppg$i++ <-- net37ch <-- LSR26.pppg$o++; // cost 600
        LSR33.pppg++ <--> net37ch <--> LSR23.pppg++;
        LSR33.pppg$i++ <-- net37ch <-- LSR23.pppg$o++; // cost 534
        LSR33.pppg++ <--> net37ch <--> LSR27.pppg++;
        LSR33.pppg$i++ <-- net37ch <-- LSR27.pppg$o++; // cost 376
        LSR34.pppg++ <--> net37ch <--> LSR4.pppg++;
        LSR34.pppg$i++ <-- net37ch <-- LSR4.pppg$o++; // cost 775
        LSR34.pppg++ <--> net37ch <--> LSR15.pppg++;
        LSR34.pppg$i++ <-- net37ch <-- LSR15.pppg$o++; // cost 1370
        LSR34.pppg++ <--> net37ch <--> LSR16.pppg++;
        LSR34.pppg$i++ <-- net37ch <-- LSR16.pppg$o++; // cost 383
        LSR35.pppg++ <--> net37ch <--> LSR1.pppg++;
        LSR35.pppg$i++ <-- net37ch <-- LSR1.pppg$o++; // cost 1500
        LSR35.pppg++ <--> net37ch <--> LSR3.pppg++;
        LSR35.pppg$i++ <-- net37ch <-- LSR3.pppg$o++; // cost 551
        LSR35.pppg++ <--> net37ch <--> LSR28.pppg++;
        LSR35.pppg$i++ <-- net37ch <-- LSR28.pppg$o++; // cost 783
        LSR35.pppg++ <--> net37ch <--> LSR33.pppg++;
        LSR35.pppg$i++ <-- net37ch <-- LSR33.pppg$o++; // cost 400
        LSR36.pppg++ <--> net37ch <--> LSR19.pppg++;
        LSR36.pppg$i++ <-- net37ch <-- LSR19.pppg$o++; // cost 507
        LSR36.pppg++ <--> net37ch <--> LSR22.pppg++;
        LSR36.pppg$i++ <-- net37ch <-- LSR22.pppg$o++; // cost 327
        LSR36.pppg++ <--> net37ch <--> LSR32.pppg++;
        LSR36.pppg$i++ <-- net37ch <-- LSR32.pppg$o++; // cost 218

        host1.pppg++ <--> net37ch <--> LSR2.pppg++;
        host2.pppg++ <--> net37ch <--> LSR34.pppg++;

}

