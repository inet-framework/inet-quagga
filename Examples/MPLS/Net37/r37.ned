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
        datarate = 128000;
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
        LSR7.out++ --> net37ch --> LSR0.in++;
        LSR7.in++ <-- net37ch <-- LSR0.out++; // cost 259
        LSR8.out++ --> net37ch --> LSR3.in++;
        LSR8.in++ <-- net37ch <-- LSR3.out++; // cost 474
        LSR9.out++ --> net37ch --> LSR4.in++;
        LSR9.in++ <-- net37ch <-- LSR4.out++; // cost 540
        LSR11.out++ --> net37ch --> LSR7.in++;
        LSR11.in++ <-- net37ch <-- LSR7.out++; // cost 264
        LSR12.out++ --> net37ch --> LSR11.in++;
        LSR12.in++ <-- net37ch <-- LSR11.out++; // cost 275
        LSR13.out++ --> net37ch --> LSR0.in++;
        LSR13.in++ <-- net37ch <-- LSR0.out++; // cost 1067
        LSR13.out++ --> net37ch --> LSR5.in++;
        LSR13.in++ <-- net37ch <-- LSR5.out++; // cost 610
        LSR13.out++ --> net37ch --> LSR10.in++;
        LSR13.in++ <-- net37ch <-- LSR10.out++; // cost 462
        LSR14.out++ --> net37ch --> LSR0.in++;
        LSR14.in++ <-- net37ch <-- LSR0.out++; // cost 552
        LSR14.out++ --> net37ch --> LSR4.in++;
        LSR14.in++ <-- net37ch <-- LSR4.out++; // cost 381
        LSR14.out++ --> net37ch --> LSR12.in++;
        LSR14.in++ <-- net37ch <-- LSR12.out++; // cost 592
        LSR16.out++ --> net37ch --> LSR8.in++;
        LSR16.in++ <-- net37ch <-- LSR8.out++; // cost 436
        LSR18.out++ --> net37ch --> LSR0.in++;
        LSR18.in++ <-- net37ch <-- LSR0.out++; // cost 540
        LSR18.out++ --> net37ch --> LSR5.in++;
        LSR18.in++ <-- net37ch <-- LSR5.out++; // cost 239
        LSR18.out++ --> net37ch --> LSR10.in++;
        LSR18.in++ <-- net37ch <-- LSR10.out++; // cost 690
        LSR18.out++ --> net37ch --> LSR17.in++;
        LSR18.in++ <-- net37ch <-- LSR17.out++; // cost 1977
        LSR20.out++ --> net37ch --> LSR2.in++;
        LSR20.in++ <-- net37ch <-- LSR2.out++; // cost 760
        LSR20.out++ --> net37ch --> LSR6.in++;
        LSR20.in++ <-- net37ch <-- LSR6.out++; // cost 834
        LSR20.out++ --> net37ch --> LSR17.in++;
        LSR20.in++ <-- net37ch <-- LSR17.out++; // cost 751
        LSR21.out++ --> net37ch --> LSR2.in++;
        LSR21.in++ <-- net37ch <-- LSR2.out++; // cost 508
        LSR21.out++ --> net37ch --> LSR6.in++;
        LSR21.in++ <-- net37ch <-- LSR6.out++; // cost 756
        LSR21.out++ --> net37ch --> LSR19.in++;
        LSR21.in++ <-- net37ch <-- LSR19.out++; // cost 411
        LSR23.out++ --> net37ch --> LSR4.in++;
        LSR23.in++ <-- net37ch <-- LSR4.out++; // cost 757
        LSR23.out++ --> net37ch --> LSR12.in++;
        LSR23.in++ <-- net37ch <-- LSR12.out++; // cost 456
        LSR23.out++ --> net37ch --> LSR22.in++;
        LSR23.in++ <-- net37ch <-- LSR22.out++; // cost 522
        LSR24.out++ --> net37ch --> LSR9.in++;
        LSR24.in++ <-- net37ch <-- LSR9.out++; // cost 722
        LSR24.out++ --> net37ch --> LSR15.in++;
        LSR24.in++ <-- net37ch <-- LSR15.out++; // cost 1182
        LSR25.out++ --> net37ch --> LSR1.in++;
        LSR25.in++ <-- net37ch <-- LSR1.out++; // cost 1363
        LSR26.out++ --> net37ch --> LSR6.in++;
        LSR26.in++ <-- net37ch <-- LSR6.out++; // cost 747
        LSR26.out++ --> net37ch --> LSR7.in++;
        LSR26.in++ <-- net37ch <-- LSR7.out++; // cost 393
        LSR26.out++ --> net37ch --> LSR18.in++;
        LSR26.in++ <-- net37ch <-- LSR18.out++; // cost 514
        LSR26.out++ --> net37ch --> LSR19.in++;
        LSR26.in++ <-- net37ch <-- LSR19.out++; // cost 594
        LSR27.out++ --> net37ch --> LSR4.in++;
        LSR27.in++ <-- net37ch <-- LSR4.out++; // cost 420
        LSR27.out++ --> net37ch --> LSR8.in++;
        LSR27.in++ <-- net37ch <-- LSR8.out++; // cost 668
        LSR28.out++ --> net37ch --> LSR21.in++;
        LSR28.in++ <-- net37ch <-- LSR21.out++; // cost 907
        LSR28.out++ --> net37ch --> LSR22.in++;
        LSR28.in++ <-- net37ch <-- LSR22.out++; // cost 720
        LSR28.out++ --> net37ch --> LSR25.in++;
        LSR28.in++ <-- net37ch <-- LSR25.out++; // cost 638
        LSR29.out++ --> net37ch --> LSR2.in++;
        LSR29.in++ <-- net37ch <-- LSR2.out++; // cost 1244
        LSR29.out++ --> net37ch --> LSR17.in++;
        LSR29.in++ <-- net37ch <-- LSR17.out++; // cost 471
        LSR30.out++ --> net37ch --> LSR1.in++;
        LSR30.in++ <-- net37ch <-- LSR1.out++; // cost 794
        LSR30.out++ --> net37ch --> LSR3.in++;
        LSR30.in++ <-- net37ch <-- LSR3.out++; // cost 487
        LSR31.out++ --> net37ch --> LSR9.in++;
        LSR31.in++ <-- net37ch <-- LSR9.out++; // cost 777
        LSR31.out++ --> net37ch --> LSR15.in++;
        LSR31.in++ <-- net37ch <-- LSR15.out++; // cost 597
        LSR32.out++ --> net37ch --> LSR12.in++;
        LSR32.in++ <-- net37ch <-- LSR12.out++; // cost 271
        LSR32.out++ --> net37ch --> LSR26.in++;
        LSR32.in++ <-- net37ch <-- LSR26.out++; // cost 600
        LSR33.out++ --> net37ch --> LSR23.in++;
        LSR33.in++ <-- net37ch <-- LSR23.out++; // cost 534
        LSR33.out++ --> net37ch --> LSR27.in++;
        LSR33.in++ <-- net37ch <-- LSR27.out++; // cost 376
        LSR34.out++ --> net37ch --> LSR4.in++;
        LSR34.in++ <-- net37ch <-- LSR4.out++; // cost 775
        LSR34.out++ --> net37ch --> LSR15.in++;
        LSR34.in++ <-- net37ch <-- LSR15.out++; // cost 1370
        LSR34.out++ --> net37ch --> LSR16.in++;
        LSR34.in++ <-- net37ch <-- LSR16.out++; // cost 383
        LSR35.out++ --> net37ch --> LSR1.in++;
        LSR35.in++ <-- net37ch <-- LSR1.out++; // cost 1500
        LSR35.out++ --> net37ch --> LSR3.in++;
        LSR35.in++ <-- net37ch <-- LSR3.out++; // cost 551
        LSR35.out++ --> net37ch --> LSR28.in++;
        LSR35.in++ <-- net37ch <-- LSR28.out++; // cost 783
        LSR35.out++ --> net37ch --> LSR33.in++;
        LSR35.in++ <-- net37ch <-- LSR33.out++; // cost 400
        LSR36.out++ --> net37ch --> LSR19.in++;
        LSR36.in++ <-- net37ch <-- LSR19.out++; // cost 507
        LSR36.out++ --> net37ch --> LSR22.in++;
        LSR36.in++ <-- net37ch <-- LSR22.out++; // cost 327
        LSR36.out++ --> net37ch --> LSR32.in++;
        LSR36.in++ <-- net37ch <-- LSR32.out++; // cost 218

        host1.out++ --> net37ch --> LSR2.in++;
        host1.in++ <-- net37ch <-- LSR2.out++;
        host2.out++ --> net37ch --> LSR34.in++;
        host2.in++ <-- net37ch <-- LSR34.out++;

}

