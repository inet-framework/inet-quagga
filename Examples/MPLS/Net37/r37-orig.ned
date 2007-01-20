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
        datarate = 60000;
}

network R37orig
{
    submodules:
        configurator: NetworkConfigurator {
            parameters:
                moduleTypes = "RSVP_LSR";
        };
        LSR0: RSVP_LSR {
            parameters:
                @display("p=489,376");
        };
        LSR1: RSVP_LSR {
            parameters:
                @display("p=999,983");
        };
        LSR2: RSVP_LSR {
            parameters:
                @display("p=362,787");
        };
        LSR3: RSVP_LSR {
            parameters:
                @display("p=890,698");
        };
        LSR4: RSVP_LSR {
            parameters:
                @display("p=677,381");
        };
        LSR5: RSVP_LSR {
            parameters:
                @display("p=360,282");
        };
        LSR6: RSVP_LSR {
            parameters:
                @display("p=320,657");
        };
        LSR7: RSVP_LSR {
            parameters:
                @display("p=476,439");
        };
        LSR8: RSVP_LSR {
            parameters:
                @display("p=853,581");
        };
        LSR9: RSVP_LSR {
            parameters:
                @display("p=670,237");
        };
        LSR10: RSVP_LSR {
            parameters:
                @display("p=222,284");
        };
        LSR11: RSVP_LSR {
            parameters:
                @display("p=531,437");
        };
        LSR12: RSVP_LSR {
            parameters:
                @display("p=588,466");
        };
        LSR13: RSVP_LSR {
            parameters:
                @display("p=348,152");
        };
        LSR14: RSVP_LSR {
            parameters:
                @display("p=584,357");
        };
        LSR15: RSVP_LSR {
            parameters:
                @display("p=905,32");
        };
        LSR16: RSVP_LSR {
            parameters:
                @display("p=857,479");
        };
        LSR17: RSVP_LSR {
            parameters:
                @display("p=25,866");
        };
        LSR18: RSVP_LSR {
            parameters:
                @display("p=373,394");
        };
        LSR19: RSVP_LSR {
            parameters:
                @display("p=488,651");
        };
        LSR20: RSVP_LSR {
            parameters:
                @display("p=185,838");
        };
        LSR21: RSVP_LSR {
            parameters:
                @display("p=453,748");
        };
        LSR22: RSVP_LSR {
            parameters:
                @display("p=595,662");
        };
        LSR23: RSVP_LSR {
            parameters:
                @display("p=647,542");
        };
        LSR24: RSVP_LSR {
            parameters:
                @display("p=643,58");
        };
        LSR25: RSVP_LSR {
            parameters:
                @display("p=686,999");
        };
        LSR26: RSVP_LSR {
            parameters:
                @display("p=413,502");
        };
        LSR27: RSVP_LSR {
            parameters:
                @display("p=766,518");
        };
        LSR28: RSVP_LSR {
            parameters:
                @display("p=696,837");
        };
        LSR29: RSVP_LSR {
            parameters:
                @display("p=104,950");
        };
        LSR30: RSVP_LSR {
            parameters:
                @display("p=995,778");
        };
        LSR31: RSVP_LSR {
            parameters:
                @display("p=763,109");
        };
        LSR32: RSVP_LSR {
            parameters:
                @display("p=544,535");
        };
        LSR33: RSVP_LSR {
            parameters:
                @display("p=757,563");
        };
        LSR34: RSVP_LSR {
            parameters:
                @display("p=884,379");
        };
        LSR35: RSVP_LSR {
            parameters:
                @display("p=767,675");
        };
        LSR36: RSVP_LSR {
            parameters:
                @display("p=544,603");

        };
    connections:
        LSR7.pppg$o++ --> net37ch --> LSR0.pppg$i++;
        LSR7.pppg$i++ <-- net37ch <-- LSR0.pppg$o++; // cost 259
        LSR8.pppg$o++ --> net37ch --> LSR3.pppg$i++;
        LSR8.pppg$i++ <-- net37ch <-- LSR3.pppg$o++; // cost 474
        LSR9.pppg$o++ --> net37ch --> LSR4.pppg$i++;
        LSR9.pppg$i++ <-- net37ch <-- LSR4.pppg$o++; // cost 540
        LSR11.pppg$o++ --> net37ch --> LSR7.pppg$i++;
        LSR11.pppg$i++ <-- net37ch <-- LSR7.pppg$o++; // cost 264
        LSR12.pppg$o++ --> net37ch --> LSR11.pppg$i++;
        LSR12.pppg$i++ <-- net37ch <-- LSR11.pppg$o++; // cost 275
        LSR13.pppg$o++ --> net37ch --> LSR0.pppg$i++;
        LSR13.pppg$i++ <-- net37ch <-- LSR0.pppg$o++; // cost 1067
        LSR13.pppg$o++ --> net37ch --> LSR5.pppg$i++;
        LSR13.pppg$i++ <-- net37ch <-- LSR5.pppg$o++; // cost 610
        LSR13.pppg$o++ --> net37ch --> LSR10.pppg$i++;
        LSR13.pppg$i++ <-- net37ch <-- LSR10.pppg$o++; // cost 462
        LSR14.pppg$o++ --> net37ch --> LSR0.pppg$i++;
        LSR14.pppg$i++ <-- net37ch <-- LSR0.pppg$o++; // cost 552
        LSR14.pppg$o++ --> net37ch --> LSR4.pppg$i++;
        LSR14.pppg$i++ <-- net37ch <-- LSR4.pppg$o++; // cost 381
        LSR14.pppg$o++ --> net37ch --> LSR12.pppg$i++;
        LSR14.pppg$i++ <-- net37ch <-- LSR12.pppg$o++; // cost 592
        LSR16.pppg$o++ --> net37ch --> LSR8.pppg$i++;
        LSR16.pppg$i++ <-- net37ch <-- LSR8.pppg$o++; // cost 436
        LSR18.pppg$o++ --> net37ch --> LSR0.pppg$i++;
        LSR18.pppg$i++ <-- net37ch <-- LSR0.pppg$o++; // cost 540
        LSR18.pppg$o++ --> net37ch --> LSR5.pppg$i++;
        LSR18.pppg$i++ <-- net37ch <-- LSR5.pppg$o++; // cost 239
        LSR18.pppg$o++ --> net37ch --> LSR10.pppg$i++;
        LSR18.pppg$i++ <-- net37ch <-- LSR10.pppg$o++; // cost 690
        LSR18.pppg$o++ --> net37ch --> LSR17.pppg$i++;
        LSR18.pppg$i++ <-- net37ch <-- LSR17.pppg$o++; // cost 1977
        LSR20.pppg$o++ --> net37ch --> LSR2.pppg$i++;
        LSR20.pppg$i++ <-- net37ch <-- LSR2.pppg$o++; // cost 760
        LSR20.pppg$o++ --> net37ch --> LSR6.pppg$i++;
        LSR20.pppg$i++ <-- net37ch <-- LSR6.pppg$o++; // cost 834
        LSR20.pppg$o++ --> net37ch --> LSR17.pppg$i++;
        LSR20.pppg$i++ <-- net37ch <-- LSR17.pppg$o++; // cost 751
        LSR21.pppg$o++ --> net37ch --> LSR2.pppg$i++;
        LSR21.pppg$i++ <-- net37ch <-- LSR2.pppg$o++; // cost 508
        LSR21.pppg$o++ --> net37ch --> LSR6.pppg$i++;
        LSR21.pppg$i++ <-- net37ch <-- LSR6.pppg$o++; // cost 756
        LSR21.pppg$o++ --> net37ch --> LSR19.pppg$i++;
        LSR21.pppg$i++ <-- net37ch <-- LSR19.pppg$o++; // cost 411
        LSR23.pppg$o++ --> net37ch --> LSR4.pppg$i++;
        LSR23.pppg$i++ <-- net37ch <-- LSR4.pppg$o++; // cost 757
        LSR23.pppg$o++ --> net37ch --> LSR12.pppg$i++;
        LSR23.pppg$i++ <-- net37ch <-- LSR12.pppg$o++; // cost 456
        LSR23.pppg$o++ --> net37ch --> LSR22.pppg$i++;
        LSR23.pppg$i++ <-- net37ch <-- LSR22.pppg$o++; // cost 522
        LSR24.pppg$o++ --> net37ch --> LSR9.pppg$i++;
        LSR24.pppg$i++ <-- net37ch <-- LSR9.pppg$o++; // cost 722
        LSR24.pppg$o++ --> net37ch --> LSR15.pppg$i++;
        LSR24.pppg$i++ <-- net37ch <-- LSR15.pppg$o++; // cost 1182
        LSR25.pppg$o++ --> net37ch --> LSR1.pppg$i++;
        LSR25.pppg$i++ <-- net37ch <-- LSR1.pppg$o++; // cost 1363
        LSR26.pppg$o++ --> net37ch --> LSR6.pppg$i++;
        LSR26.pppg$i++ <-- net37ch <-- LSR6.pppg$o++; // cost 747
        LSR26.pppg$o++ --> net37ch --> LSR7.pppg$i++;
        LSR26.pppg$i++ <-- net37ch <-- LSR7.pppg$o++; // cost 393
        LSR26.pppg$o++ --> net37ch --> LSR18.pppg$i++;
        LSR26.pppg$i++ <-- net37ch <-- LSR18.pppg$o++; // cost 514
        LSR26.pppg$o++ --> net37ch --> LSR19.pppg$i++;
        LSR26.pppg$i++ <-- net37ch <-- LSR19.pppg$o++; // cost 594
        LSR27.pppg$o++ --> net37ch --> LSR4.pppg$i++;
        LSR27.pppg$i++ <-- net37ch <-- LSR4.pppg$o++; // cost 420
        LSR27.pppg$o++ --> net37ch --> LSR8.pppg$i++;
        LSR27.pppg$i++ <-- net37ch <-- LSR8.pppg$o++; // cost 668
        LSR28.pppg$o++ --> net37ch --> LSR21.pppg$i++;
        LSR28.pppg$i++ <-- net37ch <-- LSR21.pppg$o++; // cost 907
        LSR28.pppg$o++ --> net37ch --> LSR22.pppg$i++;
        LSR28.pppg$i++ <-- net37ch <-- LSR22.pppg$o++; // cost 720
        LSR28.pppg$o++ --> net37ch --> LSR25.pppg$i++;
        LSR28.pppg$i++ <-- net37ch <-- LSR25.pppg$o++; // cost 638
        LSR29.pppg$o++ --> net37ch --> LSR2.pppg$i++;
        LSR29.pppg$i++ <-- net37ch <-- LSR2.pppg$o++; // cost 1244
        LSR29.pppg$o++ --> net37ch --> LSR17.pppg$i++;
        LSR29.pppg$i++ <-- net37ch <-- LSR17.pppg$o++; // cost 471
        LSR30.pppg$o++ --> net37ch --> LSR1.pppg$i++;
        LSR30.pppg$i++ <-- net37ch <-- LSR1.pppg$o++; // cost 794
        LSR30.pppg$o++ --> net37ch --> LSR3.pppg$i++;
        LSR30.pppg$i++ <-- net37ch <-- LSR3.pppg$o++; // cost 487
        LSR31.pppg$o++ --> net37ch --> LSR9.pppg$i++;
        LSR31.pppg$i++ <-- net37ch <-- LSR9.pppg$o++; // cost 777
        LSR31.pppg$o++ --> net37ch --> LSR15.pppg$i++;
        LSR31.pppg$i++ <-- net37ch <-- LSR15.pppg$o++; // cost 597
        LSR32.pppg$o++ --> net37ch --> LSR12.pppg$i++;
        LSR32.pppg$i++ <-- net37ch <-- LSR12.pppg$o++; // cost 271
        LSR32.pppg$o++ --> net37ch --> LSR26.pppg$i++;
        LSR32.pppg$i++ <-- net37ch <-- LSR26.pppg$o++; // cost 600
        LSR33.pppg$o++ --> net37ch --> LSR23.pppg$i++;
        LSR33.pppg$i++ <-- net37ch <-- LSR23.pppg$o++; // cost 534
        LSR33.pppg$o++ --> net37ch --> LSR27.pppg$i++;
        LSR33.pppg$i++ <-- net37ch <-- LSR27.pppg$o++; // cost 376
        LSR34.pppg$o++ --> net37ch --> LSR4.pppg$i++;
        LSR34.pppg$i++ <-- net37ch <-- LSR4.pppg$o++; // cost 775
        LSR34.pppg$o++ --> net37ch --> LSR15.pppg$i++;
        LSR34.pppg$i++ <-- net37ch <-- LSR15.pppg$o++; // cost 1370
        LSR34.pppg$o++ --> net37ch --> LSR16.pppg$i++;
        LSR34.pppg$i++ <-- net37ch <-- LSR16.pppg$o++; // cost 383
        LSR35.pppg$o++ --> net37ch --> LSR1.pppg$i++;
        LSR35.pppg$i++ <-- net37ch <-- LSR1.pppg$o++; // cost 1500
        LSR35.pppg$o++ --> net37ch --> LSR3.pppg$i++;
        LSR35.pppg$i++ <-- net37ch <-- LSR3.pppg$o++; // cost 551
        LSR35.pppg$o++ --> net37ch --> LSR28.pppg$i++;
        LSR35.pppg$i++ <-- net37ch <-- LSR28.pppg$o++; // cost 783
        LSR35.pppg$o++ --> net37ch --> LSR33.pppg$i++;
        LSR35.pppg$i++ <-- net37ch <-- LSR33.pppg$o++; // cost 400
        LSR36.pppg$o++ --> net37ch --> LSR19.pppg$i++;
        LSR36.pppg$i++ <-- net37ch <-- LSR19.pppg$o++; // cost 507
        LSR36.pppg$o++ --> net37ch --> LSR22.pppg$i++;
        LSR36.pppg$i++ <-- net37ch <-- LSR22.pppg$o++; // cost 327
        LSR36.pppg$o++ --> net37ch --> LSR32.pppg$i++;
        LSR36.pppg$i++ <-- net37ch <-- LSR32.pppg$o++; // cost 218
}

