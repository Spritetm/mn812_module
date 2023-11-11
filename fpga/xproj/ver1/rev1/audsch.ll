Revision 3
; Created by bitgen D.19 at Sat Nov 11 08:01:00 2023
; Bit lines have the following form:
; <offset> <frame number> <frame offset> <information>
; <information> may be zero or more <kw>=<value> pairs
; Block=<blockname     specifies the block associated with this
;                      memory cell.
;
; Latch=<name>         specifies the latch associated with this memory cell.
;
; Net=<netname>        specifies the user net associated with this
;                      memory cell.
;
; COMPARE=[YES | NO]   specifies whether or not it is appropriate
;                      to compare this bit position between a
;                      "program" and a "readback" bitstream.
;                      If not present the default is NO.
;
; Ram=<ram id>:<bit>   This is used in cases where a CLB function
; Rom=<ram id>:<bit>   generator is used as RAM (or ROM).  <Ram id>
;                      will be either 'F', 'G', or 'M', indicating
;                      that it is part of a single F or G function
;                      generator used as RAM, or as a single RAM
;                      (or ROM) built from both F and G.  <Bit> is
;                      a decimal number.
;
; Info lines have the following form:
; Info <name>=<value>  specifies a bit associated with the LCA
;                      configuration options, and the value of
;                      that bit.  The names of these bits may have
;                      special meaning to software reading the .ll file.
;
Bit      361      6     65 Block=P46 Latch=PAD Net=$Net00046_
Bit      369      6     57 Block=P48 Latch=PAD
Bit      377      6     49 Block=P49 Latch=PAD
Bit      385      6     41 Block=P51 Latch=PAD
Bit      393      6     33 Block=P53 Latch=PAD
Bit      401      6     25 Block=P55 Latch=PAD
Bit      409      6     17 Block=P56 Latch=PAD
Bit      417      6      9 Block=P58 Latch=PAD
Bit      432      7     65 Block=P46 Latch=IQ
Bit      440      7     57 Block=P48 Latch=IQ
Bit      448      7     49 Block=P49 Latch=IQ
Bit      456      7     41 Block=P51 Latch=IQ
Bit      464      7     33 Block=P53 Latch=IQ
Bit      472      7     25 Block=P55 Latch=IQ
Bit      480      7     17 Block=P56 Latch=IQ
Bit      488      7      9 Block=P58 Latch=IQ
Bit      633      9      6 Block=P59 Latch=IQ
Bit      649     10     61 Block=P47 Latch=IQ
Bit      657     10     53 Block=UNB29 Latch=IQ
Bit      665     10     45 Block=P50 Latch=IQ
Bit      673     10     37 Block=UNB25 Latch=IQ
Bit      681     10     29 Block=P54 Latch=IQ
Bit      689     10     21 Block=UNB21 Latch=IQ
Bit      697     10     13 Block=P57 Latch=IQ
Bit      930     14     64 Block=P47 Latch=PAD Net=$Net00048_
Bit      938     14     56 Block=UNB29 Latch=PAD
Bit      946     14     48 Block=P50 Latch=PAD
Bit      954     14     40 Block=UNB25 Latch=PAD
Bit      962     14     32 Block=P54 Latch=PAD
Bit      970     14     24 Block=UNB21 Latch=PAD
Bit      978     14     16 Block=P57 Latch=PAD Net=$Net00004_
Bit      986     14      8 Block=P59 Latch=PAD
Bit     1421     21     70 Block=P43 Latch=PAD Net=$Net00045_
Bit     1489     21      2 Block=P61 Latch=PAD
Bit     1705     25     70 Block=P43 Latch=IQ
Bit     1710     25     65 Block=HH Latch=QY
Bit     1718     25     57 Block=GH Latch=QY
Bit     1726     25     49 Block=FH Latch=QY
Bit     1734     25     41 Block=EH Latch=QY
Bit     1742     25     33 Block=DH Latch=QY
Bit     1750     25     25 Block=CH Latch=QY Net=$Net00130_
Bit     1758     25     17 Block=BH Latch=QY
Bit     1766     25      9 Block=AH Latch=QY
Bit     1773     25      2 Block=P61 Latch=IQ
Bit     1775     26     71 Block=P42 Latch=IQ
Bit     1781     26     65 Block=HH Latch=QX
Bit     1789     26     57 Block=GH Latch=QX
Bit     1797     26     49 Block=FH Latch=QX
Bit     1805     26     41 Block=EH Latch=QX
Bit     1813     26     33 Block=DH Latch=QX
Bit     1821     26     25 Block=CH Latch=QX Net=$Net00132_
Bit     1829     26     17 Block=BH Latch=QX
Bit     1837     26      9 Block=AH Latch=QX
Bit     1845     26      1 Block=P62 Latch=IQ
Bit     1989     29     70 Block=P42 Latch=PAD Net=$Net00047_
Bit     2057     29      2 Block=P62 Latch=PAD
Bit     2983     43     70 Block=P41 Latch=PAD Net=$Net00054_
Bit     3051     43      2 Block=P63 Latch=PAD
Bit     3267     47     70 Block=P41 Latch=IQ
Bit     3272     47     65 Block=HG Latch=QY
Bit     3280     47     57 Block=GG Latch=QY
Bit     3288     47     49 Block=FG Latch=QY
Bit     3296     47     41 Block=EG Latch=QY
Bit     3304     47     33 Block=DG Latch=QY
Bit     3312     47     25 Block=CG Latch=QY
Bit     3320     47     17 Block=BG Latch=QY
Bit     3328     47      9 Block=AG Latch=QY
Bit     3335     47      2 Block=P63 Latch=IQ
Bit     3337     48     71 Block=P40 Latch=IQ
Bit     3343     48     65 Block=HG Latch=QX
Bit     3351     48     57 Block=GG Latch=QX
Bit     3359     48     49 Block=FG Latch=QX
Bit     3367     48     41 Block=EG Latch=QX
Bit     3375     48     33 Block=DG Latch=QX
Bit     3383     48     25 Block=CG Latch=QX
Bit     3391     48     17 Block=BG Latch=QX
Bit     3399     48      9 Block=AG Latch=QX
Bit     3407     48      1 Block=P64 Latch=IQ
Bit     3551     51     70 Block=P40 Latch=PAD
Bit     3619     51      2 Block=P64 Latch=PAD Net=BUSD<0>
Bit     4545     65     70 Block=P39 Latch=PAD Net=$Net00002_
Bit     4613     65      2 Block=P65 Latch=PAD Net=BUSD<1>
Bit     4829     69     70 Block=P39 Latch=IQ
Bit     4834     69     65 Block=HF Latch=QY
Bit     4842     69     57 Block=GF Latch=QY
Bit     4850     69     49 Block=FF Latch=QY
Bit     4858     69     41 Block=EF Latch=QY
Bit     4866     69     33 Block=DF Latch=QY
Bit     4874     69     25 Block=CF Latch=QY
Bit     4882     69     17 Block=BF Latch=QY
Bit     4890     69      9 Block=AF Latch=QY
Bit     4897     69      2 Block=P65 Latch=IQ
Bit     4899     70     71 Block=P38 Latch=IQ
Bit     4905     70     65 Block=HF Latch=QX
Bit     4913     70     57 Block=GF Latch=QX
Bit     4921     70     49 Block=FF Latch=QX
Bit     4929     70     41 Block=EF Latch=QX
Bit     4937     70     33 Block=DF Latch=QX
Bit     4945     70     25 Block=CF Latch=QX
Bit     4953     70     17 Block=BF Latch=QX
Bit     4961     70      9 Block=AF Latch=QX
Bit     4969     70      1 Block=P66 Latch=IQ
Bit     5113     73     70 Block=P38 Latch=PAD
Bit     5181     73      2 Block=P66 Latch=PAD Net=BUSD<2>
Bit     6107     87     70 Block=P37 Latch=PAD
Bit     6175     87      2 Block=P67 Latch=PAD Net=GLOBAL_LOGIC0_0
Bit     6391     91     70 Block=P37 Latch=IQ
Bit     6396     91     65 Block=HE Latch=QY
Bit     6404     91     57 Block=GE Latch=QY
Bit     6412     91     49 Block=FE Latch=QY
Bit     6420     91     41 Block=EE Latch=QY Net=Q<3>
Bit     6428     91     33 Block=DE Latch=QY
Bit     6436     91     25 Block=CE Latch=QY
Bit     6444     91     17 Block=BE Latch=QY
Bit     6452     91      9 Block=AE Latch=QY Net=LADD<0>
Bit     6459     91      2 Block=P67 Latch=IQ
Bit     6461     92     71 Block=P36 Latch=IQ
Bit     6467     92     65 Block=HE Latch=QX
Bit     6475     92     57 Block=GE Latch=QX
Bit     6483     92     49 Block=FE Latch=QX
Bit     6491     92     41 Block=EE Latch=QX Net=Q<2>
Bit     6499     92     33 Block=DE Latch=QX
Bit     6507     92     25 Block=CE Latch=QX
Bit     6515     92     17 Block=BE Latch=QX
Bit     6523     92      9 Block=AE Latch=QX Net=LADD<1>
Bit     6531     92      1 Block=P68 Latch=IQ
Bit     6675     95     70 Block=P36 Latch=PAD
Bit     6743     95      2 Block=P68 Latch=PAD Net=GLOBAL_LOGIC0_0
Bit     7669    109     70 Block=P34 Latch=PAD
Bit     7737    109      2 Block=P2 Latch=PAD Net=GLOBAL_LOGIC0_0
Bit     7953    113     70 Block=P34 Latch=IQ
Bit     7958    113     65 Block=HD Latch=QY
Bit     7966    113     57 Block=GD Latch=QY Net=Q<14>
Bit     7974    113     49 Block=FD Latch=QY
Bit     7982    113     41 Block=ED Latch=QY Net=Q<0>
Bit     7990    113     33 Block=DD Latch=QY
Bit     7998    113     25 Block=CD Latch=QY Net=Q<10>
Bit     8006    113     17 Block=BD Latch=QY Net=Q<7>
Bit     8014    113      9 Block=AD Latch=QY
Bit     8021    113      2 Block=P2 Latch=IQ
Bit     8023    114     71 Block=P33 Latch=IQ
Bit     8029    114     65 Block=HD Latch=QX
Bit     8037    114     57 Block=GD Latch=QX
Bit     8045    114     49 Block=FD Latch=QX Net=Q<15>
Bit     8053    114     41 Block=ED Latch=QX Net=Q<1>
Bit     8061    114     33 Block=DD Latch=QX
Bit     8069    114     25 Block=CD Latch=QX
Bit     8077    114     17 Block=BD Latch=QX
Bit     8085    114      9 Block=AD Latch=QX
Bit     8093    114      1 Block=P3 Latch=IQ
Bit     8237    117     70 Block=P33 Latch=PAD
Bit     8305    117      2 Block=P3 Latch=PAD Net=GLOBAL_LOGIC0_0
Bit     9231    131     70 Block=P32 Latch=PAD
Bit     9299    131      2 Block=P4 Latch=PAD Net=$Net00096_
Bit     9515    135     70 Block=P32 Latch=IQ
Bit     9520    135     65 Block=HC Latch=QY Net=CSEL0
Bit     9528    135     57 Block=GC Latch=QY
Bit     9536    135     49 Block=FC Latch=QY Net=Q<12>
Bit     9544    135     41 Block=EC Latch=QY Net=LADD<5>
Bit     9552    135     33 Block=DC Latch=QY
Bit     9560    135     25 Block=CC Latch=QY
Bit     9568    135     17 Block=BC Latch=QY Net=Q<4>
Bit     9576    135      9 Block=AC Latch=QY Net=LADD<2>
Bit     9583    135      2 Block=P4 Latch=IQ
Bit     9585    136     71 Block=P31 Latch=IQ
Bit     9591    136     65 Block=HC Latch=QX Net=CSEL1
Bit     9599    136     57 Block=GC Latch=QX Net=$Net00001_
Bit     9607    136     49 Block=FC Latch=QX Net=Q<13>
Bit     9615    136     41 Block=EC Latch=QX Net=LADD<4>
Bit     9623    136     33 Block=DC Latch=QX
Bit     9631    136     25 Block=CC Latch=QX Net=Q<11>
Bit     9639    136     17 Block=BC Latch=QX Net=Q<5>
Bit     9647    136      9 Block=AC Latch=QX Net=LADD<3>
Bit     9655    136      1 Block=P5 Latch=IQ
Bit     9799    139     70 Block=P31 Latch=PAD
Bit     9867    139      2 Block=P5 Latch=PAD Net=$Net00095_
Bit    10793    153     70 Block=P30 Latch=PAD
Bit    10861    153      2 Block=P6 Latch=PAD Net=$Net00094_
Bit    11077    157     70 Block=P30 Latch=IQ
Bit    11082    157     65 Block=HB Latch=QY
Bit    11090    157     57 Block=GB Latch=QY
Bit    11098    157     49 Block=FB Latch=QY
Bit    11106    157     41 Block=EB Latch=QY
Bit    11114    157     33 Block=DB Latch=QY
Bit    11122    157     25 Block=CB Latch=QY
Bit    11130    157     17 Block=BB Latch=QY
Bit    11138    157      9 Block=AB Latch=QY
Bit    11145    157      2 Block=P6 Latch=IQ
Bit    11147    158     71 Block=P29 Latch=IQ
Bit    11153    158     65 Block=HB Latch=QX Net=CSEL2
Bit    11161    158     57 Block=GB Latch=QX
Bit    11169    158     49 Block=FB Latch=QX
Bit    11177    158     41 Block=EB Latch=QX
Bit    11185    158     33 Block=DB Latch=QX
Bit    11193    158     25 Block=CB Latch=QX
Bit    11201    158     17 Block=BB Latch=QX
Bit    11209    158      9 Block=AB Latch=QX
Bit    11217    158      1 Block=P7 Latch=IQ
Bit    11361    161     70 Block=P29 Latch=PAD
Bit    11429    161      2 Block=P7 Latch=PAD Net=$Net00093_
Bit    12081    171     60 Block=P23 Latch=PAD Net=BUSD<3>
Bit    12089    171     52 Block=P22 Latch=PAD Net=BUSD<4>
Bit    12097    171     44 Block=P20 Latch=PAD Net=BUSD<6>
Bit    12105    171     36 Block=P19 Latch=PAD Net=GLOBAL_LOGIC0
Bit    12113    171     28 Block=P16 Latch=PAD Net=$Net00033_
Bit    12121    171     20 Block=P14 Latch=PAD Net=$Net00090_
Bit    12129    171     12 Block=P13 Latch=PAD Net=$Net00091_
Bit    12355    175     70 Block=P28 Latch=PAD
Bit    12423    175      2 Block=P8 Latch=PAD Net=$Net00092_
Bit    12507    177     60 Block=P23 Latch=IQ
Bit    12515    177     52 Block=P22 Latch=IQ
Bit    12523    177     44 Block=P20 Latch=IQ
Bit    12531    177     36 Block=P19 Latch=IQ
Bit    12539    177     28 Block=P16 Latch=IQ
Bit    12547    177     20 Block=P14 Latch=IQ
Bit    12555    177     12 Block=P13 Latch=IQ
Bit    12575    178     63 Block=P24 Latch=PAD
Bit    12583    178     55 Block=UNB51 Latch=PAD
Bit    12591    178     47 Block=P21 Latch=PAD Net=BUSD<5>
Bit    12599    178     39 Block=UNB55 Latch=PAD
Bit    12607    178     31 Block=P17 Latch=PAD Net=$Net00088_
Bit    12615    178     23 Block=P15 Latch=PAD Net=$Net00089_
Bit    12623    178     15 Block=UNB61 Latch=PAD
Bit    12631    178      7 Block=P12 Latch=PAD Net=GLOBAL_LOGIC1
Bit    12639    179     70 Block=P28 Latch=IQ
Bit    12644    179     65 Block=HA Latch=QY
Bit    12652    179     57 Block=GA Latch=QY
Bit    12660    179     49 Block=FA Latch=QY
Bit    12668    179     41 Block=EA Latch=QY
Bit    12676    179     33 Block=DA Latch=QY
Bit    12684    179     25 Block=CA Latch=QY Net=Q<9>
Bit    12692    179     17 Block=BA Latch=QY
Bit    12700    179      9 Block=AA Latch=QY
Bit    12706    179      3 Block=P11 Latch=PAD Net=$Net00135_
Bit    12707    179      2 Block=P8 Latch=IQ
Bit    12709    180     71 Block=P27 Latch=IQ
Bit    12715    180     65 Block=HA Latch=QX
Bit    12723    180     57 Block=GA Latch=QX
Bit    12731    180     49 Block=FA Latch=QX
Bit    12739    180     41 Block=EA Latch=QX
Bit    12747    180     33 Block=DA Latch=QX
Bit    12755    180     25 Block=CA Latch=QX Net=Q<8>
Bit    12763    180     17 Block=BA Latch=QX Net=Q<6>
Bit    12771    180      9 Block=AA Latch=QX
Bit    12779    180      1 Block=P9 Latch=IQ
Bit    12846    181      5 Block=P11 Latch=IQ
Bit    12923    183     70 Block=P27 Latch=PAD
Bit    12991    183      2 Block=P9 Latch=PAD
Bit    13496    191     65 Block=P24 Latch=IQ
Bit    13504    191     57 Block=UNB51 Latch=IQ
Bit    13512    191     49 Block=P21 Latch=IQ
Bit    13520    191     41 Block=UNB55 Latch=IQ
Bit    13528    191     33 Block=P17 Latch=IQ
Bit    13536    191     25 Block=P15 Latch=IQ
Bit    13544    191     17 Block=UNB61 Latch=IQ
Bit    13552    191      9 Block=P12 Latch=IQ
Info Readback=Used
Info ReadCaptureEnabled=1
