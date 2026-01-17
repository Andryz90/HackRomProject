	.include "MPlayDef.s"

	.equ	mus_gymleader_johto_grp, voicegroup201
	.equ	mus_gymleader_johto_pri, 2
	.equ	mus_gymleader_johto_rev, 0
	.equ	mus_gymleader_johto_mvl, 100
	.equ	mus_gymleader_johto_key, 0
	.equ	mus_gymleader_johto_tbs, 1
	.equ	mus_gymleader_johto_exg, 1
	.equ	mus_gymleader_johto_cmp, 1

	.section .rodata
	.global	mus_gymleader_johto
	.align	2

@**************** Track 1 (Midi-Chn.1) ****************@

mus_gymleader_johto_1:
	.byte	KEYSH , mus_gymleader_johto_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 189*mus_gymleader_johto_tbs/2
	.byte		VOICE , 56
	.byte		VOL   , 125*mus_gymleader_johto_mvl/mxv
	.byte		PAN   , c_v+0
	.byte		MOD   , 0
	.byte		PAN   , c_v+54
	.byte		N04   , Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		        En4 , v104
	.byte	W06
	.byte		        As4 , v100
	.byte	W06
	.byte		        Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		        En4 , v104
	.byte	W06
	.byte		        As4 , v100
	.byte	W06
	.byte		PAN   , c_v-54
	.byte		N04   , Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		        En4 , v104
	.byte	W06
	.byte		        As4 , v100
	.byte	W06
	.byte		        Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		        En4 , v104
	.byte	W06
	.byte		        As4 , v100
	.byte	W06
@ 001   ----------------------------------------
	.byte		PAN   , c_v+54
	.byte		N04   , Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		        En4 , v104
	.byte	W06
	.byte		        As4 , v100
	.byte	W06
	.byte		        Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		        En4 , v104
	.byte	W06
	.byte		        As4 , v100
	.byte	W06
	.byte		PAN   , c_v-54
	.byte		N04   , Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		PAN   , c_v+54
	.byte		N04   , En4 , v104
	.byte	W06
	.byte		        As4 , v100
	.byte	W06
	.byte		PAN   , c_v-54
	.byte		N04   , Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		PAN   , c_v+54
	.byte		N04   , En4 , v104
	.byte	W06
	.byte		        As4 , v100
	.byte	W06
@ 002   ----------------------------------------
	.byte		PAN   , c_v-54
	.byte	W96
@ 003   ----------------------------------------
	.byte	W96
@ 004   ----------------------------------------
	.byte	W96
@ 005   ----------------------------------------
	.byte	W96
@ 006   ----------------------------------------
	.byte	W96
@ 007   ----------------------------------------
	.byte	W96
@ 008   ----------------------------------------
	.byte	W96
@ 009   ----------------------------------------
	.byte	W84
	.byte		N05   , Gn3 , v120
	.byte	W06
	.byte		        An3 
	.byte	W06
mus_gymleader_johto_1_B1:
@ 010   ----------------------------------------
	.byte	TEMPO , 190*mus_gymleader_johto_tbs/2
	.byte		N44   , As3 , v120, gtp2
	.byte	W48
	.byte		N10   , Dn4 
	.byte	W12
	.byte		        Cn4 , v108
	.byte	W12
	.byte		        As3 , v120
	.byte	W12
	.byte		        Cn4 , v108
	.byte	W12
@ 011   ----------------------------------------
mus_gymleader_johto_1_011:
	.byte		N44   , Cs4 , v120, gtp2
	.byte	W48
	.byte		N10   , Fn4 
	.byte	W12
	.byte		        Ds4 , v108
	.byte	W12
	.byte		        Cs4 , v120
	.byte	W12
	.byte		        Ds4 , v108
	.byte	W12
	.byte	PEND
@ 012   ----------------------------------------
	.byte		N68   , Fn4 , v120, gtp2
	.byte	W72
	.byte		N10   , Ds4 , v108
	.byte	W24
@ 013   ----------------------------------------
	.byte		N68   , Gs4 , v120, gtp3
	.byte	W72
	.byte		N10   , Fn4 , v108
	.byte	W24
@ 014   ----------------------------------------
	.byte		N44   , As3 , v120, gtp2
	.byte	W48
	.byte		N10   , Dn4 
	.byte	W12
	.byte		        Cn4 , v108
	.byte	W12
	.byte		        As3 , v120
	.byte	W12
	.byte		        Cn4 , v108
	.byte	W12
@ 015   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_1_011
@ 016   ----------------------------------------
	.byte		TIE   , Cs4 , v120
	.byte	W96
@ 017   ----------------------------------------
	.byte	W12
	.byte	W12
	.byte	W12
	.byte	W10
	.byte		EOT   
	.byte	W02
	.byte	W12
	.byte	W12
	.byte	W24
@ 018   ----------------------------------------
	.byte	TEMPO , 189*mus_gymleader_johto_tbs/2
	.byte	W96
@ 019   ----------------------------------------
	.byte	W96
@ 020   ----------------------------------------
	.byte	W96
@ 021   ----------------------------------------
	.byte	W96
@ 022   ----------------------------------------
	.byte	W96
@ 023   ----------------------------------------
	.byte	W92
	.byte	W03
	.byte	W01
@ 024   ----------------------------------------
	.byte		N92   , Fn3 , v112, gtp3
	.byte	W80
	.byte	W01
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W02
	.byte	W01
@ 025   ----------------------------------------
	.byte		N44   , Cs3 , v112, gtp3
	.byte	W42
	.byte	W03
	.byte	W03
	.byte		N32   , Fn3 , v112, gtp3
	.byte	W36
	.byte		N11   , Gn3 
	.byte	W12
@ 026   ----------------------------------------
	.byte		N92   , En3 , v112, gtp3
	.byte	W72
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W02
	.byte	W01
@ 027   ----------------------------------------
	.byte		        Gn3 
	.byte	W78
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W05
	.byte	W01
@ 028   ----------------------------------------
	.byte		        Cs4 , v108
	.byte	W80
	.byte	W01
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W02
	.byte	W01
@ 029   ----------------------------------------
	.byte		N44   , As3 , v108, gtp2
	.byte	W48
	.byte		N32   , Cs4 , v108, gtp2
	.byte	W36
	.byte		N10   , Ds4 
	.byte	W12
@ 030   ----------------------------------------
	.byte		N92   , Cn4 
	.byte	W78
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W02
	.byte	W01
@ 031   ----------------------------------------
	.byte		        En4 
	.byte	W80
	.byte	W01
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W02
	.byte	W01
@ 032   ----------------------------------------
	.byte	TEMPO , 188*mus_gymleader_johto_tbs/2
	.byte		N08   , Fn3 , v112
	.byte	W36
	.byte		N08   
	.byte	W36
	.byte		N08   
	.byte	W24
@ 033   ----------------------------------------
	.byte		        Fs3 
	.byte	W36
	.byte		N08   
	.byte	W36
	.byte		N08   
	.byte	W24
@ 034   ----------------------------------------
	.byte		        Gn3 
	.byte	W36
	.byte		N08   
	.byte	W36
	.byte		N08   
	.byte	W24
@ 035   ----------------------------------------
	.byte		        Gs3 
	.byte	W36
	.byte		N08   
	.byte	W36
	.byte		N08   
	.byte	W24
@ 036   ----------------------------------------
	.byte	TEMPO , 189*mus_gymleader_johto_tbs/2
	.byte		N92   , Cn4 , v108, gtp3
	.byte	W80
	.byte	W01
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W02
	.byte	W01
@ 037   ----------------------------------------
	.byte		        Cs4 , v108, gtp3
	.byte	W78
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W02
	.byte	W01
@ 038   ----------------------------------------
	.byte		        Dn4 , v108, gtp3
	.byte	W80
	.byte	W01
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W02
	.byte	W01
@ 039   ----------------------------------------
	.byte		N88   , Ds4 , v108, gtp1
	.byte	W72
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte		N05   , Gn4 , v116
	.byte	W06
@ 040   ----------------------------------------
	.byte	TEMPO , 189*mus_gymleader_johto_tbs/2
	.byte		N44   , Gs4 , v108, gtp3
	.byte	W48
	.byte		N10   , An4 
	.byte	W12
	.byte		        Gs4 
	.byte	W12
	.byte		        Fs4 
	.byte	W12
	.byte		        An4 
	.byte	W12
@ 041   ----------------------------------------
	.byte		N22   , Gs4 
	.byte	W24
	.byte		N23   , Cn5 
	.byte	W24
	.byte		        An4 
	.byte	W24
	.byte		        Gs4 
	.byte	W24
@ 042   ----------------------------------------
	.byte		        Ds5 
	.byte	W24
	.byte		        Gs4 
	.byte	W24
	.byte		        Ds5 
	.byte	W24
	.byte		        Gs4 
	.byte	W24
@ 043   ----------------------------------------
	.byte		N11   , Ds5 
	.byte	W12
	.byte		        Cs5 
	.byte	W12
	.byte		        Cn5 
	.byte	W12
	.byte		        Cs5 
	.byte	W12
	.byte		        Cn5 
	.byte	W12
	.byte		        An4 
	.byte	W12
	.byte		        Gs4 
	.byte	W12
	.byte		        An4 
	.byte	W12
@ 044   ----------------------------------------
	.byte		N44   , Ds4 , v108, gtp3
	.byte	W48
	.byte		N11   , En4 
	.byte	W12
	.byte		        Ds4 
	.byte	W12
	.byte		        Cs4 
	.byte	W12
	.byte		        En4 
	.byte	W12
@ 045   ----------------------------------------
	.byte		N23   , Ds4 
	.byte	W24
	.byte		        Gs4 
	.byte	W24
	.byte		        En4 
	.byte	W24
	.byte		        Cs4 
	.byte	W24
@ 046   ----------------------------------------
	.byte		        Gs4 
	.byte	W24
	.byte		        Cs4 
	.byte	W24
	.byte		        Gs4 
	.byte	W24
	.byte		        Cs4 
	.byte	W24
@ 047   ----------------------------------------
	.byte		N11   , An4 
	.byte	W12
	.byte		        Gs4 
	.byte	W12
	.byte		        Fs4 
	.byte	W12
	.byte		        En4 
	.byte	W12
	.byte		        Ds4 
	.byte	W12
	.byte		        En4 
	.byte	W12
	.byte		        Ds4 
	.byte	W12
	.byte		        Cs4 
	.byte	W12
@ 048   ----------------------------------------
	.byte		N44   , Ds4 , v108, gtp3
	.byte	W48
	.byte		        Cs4 , v108, gtp3
	.byte	W48
@ 049   ----------------------------------------
	.byte		        Bn3 , v108, gtp3
	.byte	W48
	.byte		        An3 , v108, gtp3
	.byte	W48
@ 050   ----------------------------------------
	.byte		N23   , Ds4 
	.byte	W24
	.byte		        Gs4 
	.byte	W24
	.byte		        En4 
	.byte	W24
	.byte		        An4 
	.byte	W24
@ 051   ----------------------------------------
	.byte		N05   , Gs4 
	.byte	W12
	.byte		N05   
	.byte	W12
	.byte		N05   
	.byte	W12
	.byte		N05   
	.byte	W12
	.byte		N05   
	.byte	W12
	.byte		N05   
	.byte	W12
	.byte		N05   
	.byte	W12
	.byte		N05   
	.byte	W12
@ 052   ----------------------------------------
	.byte		        Gs4 , v116
	.byte	W92
	.byte	W03
	.byte	W01
@ 053   ----------------------------------------
	.byte	TEMPO , 189*mus_gymleader_johto_tbs/2
	.byte		N92   , Fn3 , v112, gtp3
	.byte	W78
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W05
	.byte	W01
@ 054   ----------------------------------------
	.byte		        Cn4 , v112, gtp3
	.byte	W78
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W05
	.byte	W01
@ 055   ----------------------------------------
	.byte		        Bn3 , v112, gtp3
	.byte	W78
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W02
	.byte	W01
@ 056   ----------------------------------------
	.byte		        Gn3 , v112, gtp3
	.byte	W78
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W05
	.byte	W01
	.byte	GOTO
	 .word	mus_gymleader_johto_1_B1
mus_gymleader_johto_1_B2:
@ 057   ----------------------------------------
	.byte	FINE

@**************** Track 2 (Midi-Chn.2) ****************@

mus_gymleader_johto_2:
	.byte	KEYSH , mus_gymleader_johto_key+0
@ 000   ----------------------------------------
	.byte		VOICE , 48
	.byte		VOL   , 115*mus_gymleader_johto_mvl/mxv
	.byte		PAN   , c_v+0
	.byte		MOD   , 0
	.byte		PAN   , c_v-54
	.byte		N04   , An3 , v120
	.byte		N04   , An4 , v088
	.byte	W06
	.byte		        Gs3 , v108
	.byte		N04   , Gs4 , v072
	.byte	W06
	.byte		        Fs3 , v120
	.byte		N04   , Fs4 , v088
	.byte	W06
	.byte		        As3 , v120
	.byte		N04   , As4 , v088
	.byte	W06
	.byte		        An3 , v120
	.byte		N04   , An4 , v088
	.byte	W06
	.byte		        Gs3 , v108
	.byte		N04   , Gs4 , v072
	.byte	W06
	.byte		        Fs3 , v120
	.byte		N04   , Fs4 , v088
	.byte	W06
	.byte		        As3 , v120
	.byte		N04   , As4 , v088
	.byte	W06
	.byte		PAN   , c_v+54
	.byte		N04   , Fs3 , v096
	.byte		N04   , An3 , v120
	.byte		N04   , Fs4 , v060
	.byte		N04   , An4 , v088
	.byte	W06
	.byte		        Gs3 , v108
	.byte		N04   , Gs4 , v072
	.byte	W06
	.byte		        Fs3 , v120
	.byte		N04   , Fs4 , v088
	.byte	W06
	.byte		        As3 , v120
	.byte		N04   , As4 , v088
	.byte	W06
	.byte		        An3 , v120
	.byte		N04   , An4 , v088
	.byte	W06
	.byte		        Gs3 , v108
	.byte		N04   , Gs4 , v072
	.byte	W06
	.byte		        Fs3 , v120
	.byte		N04   , Fs4 , v088
	.byte	W06
	.byte		        As3 , v120
	.byte		N04   , As4 , v088
	.byte	W06
@ 001   ----------------------------------------
	.byte		PAN   , c_v-54
	.byte		N05   , Cs3 , v120
	.byte		N05   , Cs4 , v088
	.byte	W06
	.byte		        Bn2 , v108
	.byte		N05   , Bn3 , v072
	.byte	W06
	.byte		        An2 , v116
	.byte		N05   , An3 , v080
	.byte	W06
	.byte		        Cs3 , v120
	.byte		N05   , Cs4 , v088
	.byte	W06
	.byte		        Cs3 , v120
	.byte		N05   , Cs4 , v088
	.byte	W06
	.byte		        Bn2 , v108
	.byte		N05   , Bn3 , v072
	.byte	W06
	.byte		        An2 , v116
	.byte		N05   , An3 , v080
	.byte	W06
	.byte		        Cs3 , v120
	.byte		N05   , Cs4 , v088
	.byte	W06
	.byte		PAN   , c_v+54
	.byte		N05   , Cs3 , v120
	.byte		N05   , Cs4 , v088
	.byte	W06
	.byte		        Bn2 , v108
	.byte		N05   , Bn3 , v072
	.byte	W06
	.byte		PAN   , c_v-54
	.byte		N05   , An2 , v116
	.byte		N05   , An3 , v080
	.byte	W06
	.byte		        Cs3 , v120
	.byte		N05   , Cs4 , v088
	.byte	W06
	.byte		PAN   , c_v+54
	.byte		N23   , Cs3 , v116
	.byte		N23   , Cs4 , v080
	.byte	W12
	.byte		PAN   , c_v-54
	.byte	W11
	.byte		        c_v-50
	.byte	W01
@ 002   ----------------------------------------
	.byte		N08   , Dn4 , v120
	.byte		N08   , An4 
	.byte	W36
	.byte		        Ds3 , v116
	.byte		N08   , As3 
	.byte	W36
	.byte		        Cn3 
	.byte		N08   , Gn3 
	.byte	W24
@ 003   ----------------------------------------
	.byte		        Fn3 , v120
	.byte		N08   , Dn4 
	.byte	W36
	.byte		        Dn3 , v116
	.byte		N08   , An3 
	.byte	W36
	.byte		        Ds3 
	.byte		N08   , As3 
	.byte	W24
@ 004   ----------------------------------------
	.byte		        Dn3 , v120
	.byte		N08   , An3 
	.byte	W36
	.byte		        Ds3 , v116
	.byte		N08   , As3 
	.byte	W36
	.byte		        Cn3 
	.byte		N08   , Gn3 
	.byte	W24
@ 005   ----------------------------------------
	.byte		        Fn3 , v120
	.byte		N08   , Dn4 
	.byte	W36
	.byte		        Gn3 , v116
	.byte		N08   , Ds4 
	.byte	W36
	.byte		N22   , Cn3 , v120
	.byte		N22   , Ds3 
	.byte	W24
@ 006   ----------------------------------------
	.byte		N08   , Gn3 
	.byte		N08   , Dn4 
	.byte	W36
	.byte		        Gs3 , v100
	.byte		N08   , Ds4 , v116
	.byte	W36
	.byte		        Fn3 
	.byte		N08   , Cn4 
	.byte	W24
@ 007   ----------------------------------------
	.byte		        Gs3 , v108
	.byte		N08   , Gn4 , v120
	.byte	W36
	.byte		        Fn3 , v116
	.byte		N08   , Dn4 
	.byte	W36
	.byte		        Gs3 , v100
	.byte		N08   , Ds4 , v116
	.byte	W24
@ 008   ----------------------------------------
	.byte		        Gn3 , v127
	.byte		N08   , Dn4 
	.byte	W36
	.byte		        Gs3 , v108
	.byte		N08   , Ds4 , v120
	.byte	W36
	.byte		        Fn3 
	.byte		N08   , Cn4 
	.byte	W24
@ 009   ----------------------------------------
	.byte		        Gs3 , v112
	.byte		N08   , Gn4 , v127
	.byte	W36
	.byte		        Cn4 , v120
	.byte		N08   , Gs4 
	.byte	W36
	.byte		N05   , As3 
	.byte		N05   , Fs4 
	.byte	W24
mus_gymleader_johto_2_B1:
@ 010   ----------------------------------------
mus_gymleader_johto_2_010:
	.byte		N32   , Dn3 , v096, gtp3
	.byte	W36
	.byte		        Gn3 , v096, gtp3
	.byte	W36
	.byte		N11   , Fn3 
	.byte	W12
	.byte		        Gn3 
	.byte	W12
	.byte	PEND
@ 011   ----------------------------------------
mus_gymleader_johto_2_011:
	.byte		N23   , Gs3 , v084
	.byte	W24
	.byte		        Gn3 , v096
	.byte	W24
	.byte		        Fn3 
	.byte	W24
	.byte		        Gn3 
	.byte	W24
	.byte	PEND
@ 012   ----------------------------------------
	.byte		N68   , Gs3 , v084, gtp3
	.byte	W72
	.byte		N11   , Gn3 , v096
	.byte	W24
@ 013   ----------------------------------------
	.byte		N68   , Cs4 , v096, gtp3
	.byte	W72
	.byte		N11   , Cn4 
	.byte	W24
@ 014   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_2_010
@ 015   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_2_011
@ 016   ----------------------------------------
	.byte		N44   , Gs3 , v084, gtp3
	.byte	W48
	.byte		        Gn3 , v096, gtp3
	.byte	W48
@ 017   ----------------------------------------
	.byte		        Fn3 , v096, gtp3
	.byte	W48
	.byte		        Ds3 , v096, gtp3
	.byte	W48
@ 018   ----------------------------------------
	.byte		N88   , Cn3 , v096, gtp1
	.byte	W96
@ 019   ----------------------------------------
	.byte		N11   , Ds3 
	.byte	W12
	.byte		        En3 
	.byte	W12
	.byte		N32   , Fn3 , v096, gtp3
	.byte	W36
	.byte		N11   , Gn3 
	.byte	W12
	.byte		N23   , Ds3 
	.byte	W24
@ 020   ----------------------------------------
	.byte		N44   , As2 , v096, gtp3
	.byte	W48
	.byte		        Fn3 , v096, gtp3
	.byte	W48
@ 021   ----------------------------------------
	.byte		N11   , Gn3 
	.byte	W12
	.byte		        Gs3 , v084
	.byte	W12
	.byte		N32   , As3 , v096
	.byte	W36
	.byte		N11   
	.byte	W12
	.byte		N23   , Gs3 , v084
	.byte	W24
@ 022   ----------------------------------------
	.byte		N44   , Gn3 , v096, gtp3
	.byte	W48
	.byte		N23   , Fn3 
	.byte	W24
	.byte		N11   , En3 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
@ 023   ----------------------------------------
	.byte		N80   , Cn3 , v096, gtp3
	.byte	W96
@ 024   ----------------------------------------
	.byte		N09   , Fn3 , v100
	.byte	W36
	.byte		N09   
	.byte	W24
	.byte		        En3 
	.byte	W12
	.byte		        Fn3 
	.byte	W24
@ 025   ----------------------------------------
	.byte		N09   
	.byte	W36
	.byte		N09   
	.byte	W36
	.byte		N09   
	.byte	W12
	.byte		        Gn3 , v088
	.byte	W12
@ 026   ----------------------------------------
	.byte		        En3 , v100
	.byte	W36
	.byte		N09   
	.byte	W24
	.byte		        Fn3 
	.byte	W12
	.byte		        En3 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
@ 027   ----------------------------------------
	.byte		        Cn3 
	.byte	W36
	.byte		N09   
	.byte	W36
	.byte		N09   
	.byte	W24
@ 028   ----------------------------------------
	.byte		        Fn3 , v112
	.byte	W36
	.byte		N09   
	.byte	W12
	.byte		        Gs3 , v096
	.byte	W12
	.byte		        En3 , v112
	.byte	W12
	.byte		        Fn3 
	.byte	W12
	.byte		        Gs3 , v096
	.byte	W12
@ 029   ----------------------------------------
	.byte		        Fn3 , v112
	.byte	W12
	.byte		        Cn3 
	.byte	W24
	.byte		        Fn3 
	.byte	W36
	.byte		        En3 
	.byte	W12
	.byte		        Gs3 , v096
	.byte	W12
@ 030   ----------------------------------------
	.byte		        En3 , v112
	.byte	W12
	.byte		        Gn3 
	.byte	W24
	.byte		        En3 
	.byte	W24
	.byte		        Fn3 
	.byte	W12
	.byte		        En3 
	.byte	W12
	.byte		        Fn3 
	.byte	W12
@ 031   ----------------------------------------
	.byte		        Gn3 
	.byte	W36
	.byte		N09   
	.byte	W24
	.byte		        Cn4 
	.byte	W12
	.byte		        Gn3 
	.byte	W12
	.byte		        Cn3 
	.byte	W12
@ 032   ----------------------------------------
	.byte		N08   
	.byte	W36
	.byte		        Cn3 , v104
	.byte	W36
	.byte		        Cn3 , v108
	.byte	W24
@ 033   ----------------------------------------
	.byte		        Cs3 , v112
	.byte	W36
	.byte		        Cs3 , v104
	.byte	W36
	.byte		        Cs3 , v108
	.byte	W24
@ 034   ----------------------------------------
	.byte		        Dn3 , v112
	.byte	W36
	.byte		        Dn3 , v104
	.byte	W36
	.byte		        Dn3 , v108
	.byte	W24
@ 035   ----------------------------------------
	.byte		        Ds3 , v112
	.byte	W36
	.byte		        Ds3 , v104
	.byte	W36
	.byte		        Ds3 , v108
	.byte	W24
@ 036   ----------------------------------------
	.byte	W96
@ 037   ----------------------------------------
	.byte	W96
@ 038   ----------------------------------------
	.byte	W96
@ 039   ----------------------------------------
	.byte	W96
@ 040   ----------------------------------------
	.byte		N44   , Cn4 , v100, gtp3
	.byte	W48
	.byte		N23   , Cs4 , v108
	.byte	W24
	.byte		        Cn4 , v100
	.byte	W24
@ 041   ----------------------------------------
	.byte		N11   , Gs3 
	.byte	W12
	.byte		        Cn4 , v104
	.byte	W12
	.byte		        Gs3 , v100
	.byte	W12
	.byte		        Ds4 , v104
	.byte	W12
	.byte		        Gs3 , v100
	.byte	W12
	.byte		        Cs4 , v104
	.byte	W12
	.byte		        Gs3 , v100
	.byte	W12
	.byte		        Cn4 , v104
	.byte	W12
@ 042   ----------------------------------------
	.byte		N23   , Gs4 
	.byte	W24
	.byte		        Ds4 , v096
	.byte	W24
	.byte		        Gs4 , v104
	.byte	W24
	.byte		        Ds4 , v096
	.byte	W23
	.byte		        Ds4 , v100
	.byte	W01
@ 043   ----------------------------------------
	.byte	W23
	.byte		        Gs3 , v096
	.byte	W24
	.byte		        Ds4 , v100
	.byte	W24
	.byte		        Gs3 , v096
	.byte	W24
	.byte	W01
@ 044   ----------------------------------------
	.byte		N44   , Gs3 , v100, gtp3
	.byte	W48
	.byte		N23   , An3 
	.byte	W24
	.byte		        Gs3 
	.byte	W24
@ 045   ----------------------------------------
	.byte		N11   , Ds3 , v096
	.byte	W12
	.byte		        Gs3 , v100
	.byte	W12
	.byte		        Ds3 , v096
	.byte	W12
	.byte		        Cs4 , v100
	.byte	W12
	.byte		        Ds3 , v096
	.byte	W12
	.byte		        An3 , v100
	.byte	W12
	.byte		        Ds3 , v096
	.byte	W12
	.byte		        Gn3 , v100
	.byte	W12
@ 046   ----------------------------------------
	.byte		N23   , Cs4 
	.byte	W24
	.byte		        Gs3 
	.byte	W24
	.byte		        Cs4 
	.byte	W24
	.byte		        Gs3 
	.byte	W24
@ 047   ----------------------------------------
	.byte		N23   
	.byte	W24
	.byte		        Cs3 , v092
	.byte	W24
	.byte		        Gs3 , v100
	.byte	W24
	.byte		        Cs3 , v092
	.byte	W24
@ 048   ----------------------------------------
	.byte		N44   , Bn3 , v100, gtp3
	.byte	W48
	.byte		        An3 , v092, gtp3
	.byte	W48
@ 049   ----------------------------------------
	.byte		        Gs3 , v096, gtp3
	.byte	W48
	.byte		        Fs3 , v092, gtp3
	.byte	W48
@ 050   ----------------------------------------
	.byte		N23   , An3 , v100
	.byte	W24
	.byte		        Cs4 , v108
	.byte	W24
	.byte		        Bn3 , v100
	.byte	W24
	.byte		        En4 , v112
	.byte	W24
@ 051   ----------------------------------------
	.byte		N05   , Ds4 
	.byte	W12
	.byte		        Ds4 , v100
	.byte	W12
	.byte		N05   
	.byte	W12
	.byte		        Ds4 , v112
	.byte	W12
	.byte		        Ds4 , v100
	.byte	W12
	.byte		N05   
	.byte	W12
	.byte		        Ds4 , v108
	.byte	W12
	.byte		        Ds4 , v100
	.byte	W12
@ 052   ----------------------------------------
	.byte		        Ds4 , v112
	.byte	W96
@ 053   ----------------------------------------
	.byte		N92   , Cn3 , v108, gtp2
	.byte	W96
@ 054   ----------------------------------------
	.byte		        Fn3 , v112, gtp2
	.byte	W96
@ 055   ----------------------------------------
	.byte		        En3 , v100, gtp2
	.byte	W96
@ 056   ----------------------------------------
	.byte		N56   , Ds3 , v108, gtp2
	.byte	W60
	.byte		N10   , As2 
	.byte	W12
	.byte		        Ds3 , v112
	.byte	W12
	.byte		        Fs3 , v120
	.byte	W12
	.byte	GOTO
	 .word	mus_gymleader_johto_2_B1
mus_gymleader_johto_2_B2:
@ 057   ----------------------------------------
	.byte	FINE

@**************** Track 3 (Midi-Chn.3) ****************@

mus_gymleader_johto_3:
	.byte	KEYSH , mus_gymleader_johto_key+0
@ 000   ----------------------------------------
	.byte		VOICE , 36
	.byte		VOL   , 115*mus_gymleader_johto_mvl/mxv
	.byte		PAN   , c_v+0
	.byte		MOD   , 0
	.byte	W12
	.byte		N10   , An0 , v116
	.byte	W24
	.byte		        Gs0 , v108
	.byte	W24
	.byte		        Gn0 , v116
	.byte	W24
	.byte		        Fs0 , v112
	.byte	W12
@ 001   ----------------------------------------
	.byte	W12
	.byte		        Fn0 , v116
	.byte	W24
	.byte		        En0 
	.byte	W12
	.byte		N11   , En0 , v104
	.byte	W12
	.byte		        Gn0 , v116
	.byte	W12
	.byte		N23   , Gs0 , v120
	.byte	W24
@ 002   ----------------------------------------
	.byte		N11   , Gn0 , v116
	.byte	W12
	.byte		        Dn0 
	.byte	W12
	.byte		        Fn0 
	.byte	W12
	.byte		        Gn0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
	.byte		N11   
	.byte	W12
	.byte		        Gn0 
	.byte	W12
	.byte		        Fn0 
	.byte	W12
@ 003   ----------------------------------------
	.byte		        Gn0 
	.byte	W12
	.byte		        Dn0 , v112
	.byte	W12
	.byte		        Fn0 , v116
	.byte	W12
	.byte		        Gn0 
	.byte	W12
	.byte		        Fn0 
	.byte	W12
	.byte		N11   
	.byte	W12
	.byte		        Ds0 , v112
	.byte	W12
	.byte		        Fn0 , v116
	.byte	W12
@ 004   ----------------------------------------
	.byte		        Gn0 
	.byte	W12
	.byte		        Dn0 , v112
	.byte	W12
	.byte		        Fn0 , v116
	.byte	W12
	.byte		        Gn0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
	.byte		N11   
	.byte	W12
	.byte		        Gn0 
	.byte	W12
	.byte		        Fn0 
	.byte	W12
@ 005   ----------------------------------------
	.byte		        Gn0 
	.byte	W12
	.byte		        Dn0 , v112
	.byte	W12
	.byte		        Fn0 , v116
	.byte	W12
	.byte		        Gn0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
	.byte		        Dn0 , v112
	.byte	W12
	.byte		N23   , Fn0 , v116
	.byte	W24
@ 006   ----------------------------------------
mus_gymleader_johto_3_006:
	.byte		N11   , Gn0 , v127
	.byte	W12
	.byte		        Dn0 , v120
	.byte	W12
	.byte		        Fn0 , v127
	.byte	W12
	.byte		        Gn0 
	.byte	W12
	.byte		        Gs0 , v124
	.byte	W12
	.byte		N11   
	.byte	W12
	.byte		        Gn0 , v127
	.byte	W12
	.byte		        Fn0 
	.byte	W12
	.byte	PEND
@ 007   ----------------------------------------
	.byte		        Gn0 
	.byte	W12
	.byte		        Dn0 , v120
	.byte	W12
	.byte		        Fn0 , v127
	.byte	W12
	.byte		        Gn0 
	.byte	W12
	.byte		        Fn0 
	.byte	W12
	.byte		N11   
	.byte	W12
	.byte		        Ds0 , v120
	.byte	W12
	.byte		        Fn0 , v127
	.byte	W12
@ 008   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_3_006
@ 009   ----------------------------------------
	.byte		N11   , Gn0 , v127
	.byte	W12
	.byte		        Dn0 , v120
	.byte	W12
	.byte		        Fn0 , v127
	.byte	W12
	.byte		        Gn0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
	.byte		        Cn1 
	.byte	W12
	.byte		        As0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
mus_gymleader_johto_3_B1:
@ 010   ----------------------------------------
mus_gymleader_johto_3_010:
	.byte		N11   , Dn0 , v127
	.byte	W12
	.byte		        Gn0 , v120
	.byte	W12
	.byte		        Dn0 , v127
	.byte	W12
	.byte		        Gn0 , v120
	.byte	W12
	.byte		        Dn0 , v127
	.byte	W12
	.byte		        Gn0 , v120
	.byte	W12
	.byte		        Dn0 , v127
	.byte	W12
	.byte		        Gn0 , v120
	.byte	W12
	.byte	PEND
@ 011   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_3_010
@ 012   ----------------------------------------
mus_gymleader_johto_3_012:
	.byte		N11   , Cs0 , v127
	.byte	W12
	.byte		        Gs0 , v120
	.byte	W12
	.byte		        Cs0 , v127
	.byte	W12
	.byte		        Gs0 , v120
	.byte	W12
	.byte		        Cs0 , v127
	.byte	W12
	.byte		        Gs0 , v120
	.byte	W12
	.byte		        Cs0 , v127
	.byte	W12
	.byte		        Gs0 , v120
	.byte	W12
	.byte	PEND
@ 013   ----------------------------------------
	.byte		        Cs0 , v127
	.byte	W12
	.byte		        Gs0 , v120
	.byte	W12
	.byte		        Cs0 , v127
	.byte	W12
	.byte		        Gs0 , v120
	.byte	W12
	.byte		        Cs0 , v127
	.byte	W12
	.byte		        As0 , v120
	.byte	W12
	.byte		        An0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
@ 014   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_3_010
@ 015   ----------------------------------------
	.byte		N11   , Dn0 , v127
	.byte	W12
	.byte		        Gn0 , v120
	.byte	W12
	.byte		        Dn0 , v127
	.byte	W12
	.byte		        Gn0 , v120
	.byte	W12
	.byte		        Dn0 , v127
	.byte	W12
	.byte		        Gn0 , v120
	.byte	W12
	.byte		        Gs0 
	.byte	W12
	.byte		        Gn0 
	.byte	W12
@ 016   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_3_012
@ 017   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_3_012
@ 018   ----------------------------------------
	.byte		N11   , Cn0 , v127
	.byte	W12
	.byte		        Gn0 
	.byte	W12
	.byte		        As0 , v120
	.byte	W12
	.byte		        Cn0 , v127
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Fn0 
	.byte	W12
	.byte		        Gn0 
	.byte	W12
	.byte		        As0 
	.byte	W12
@ 019   ----------------------------------------
mus_gymleader_johto_3_019:
	.byte		N11   , Cn0 , v127
	.byte	W12
	.byte		        Gn0 , v120
	.byte	W12
	.byte		        Cn0 , v127
	.byte	W12
	.byte		        Gn0 , v120
	.byte	W12
	.byte		        Cn0 , v127
	.byte	W12
	.byte		        Gn0 , v120
	.byte	W12
	.byte		        Cn0 , v127
	.byte	W12
	.byte		        Gn0 , v120
	.byte	W12
	.byte	PEND
@ 020   ----------------------------------------
	.byte		        AsM1, v127
	.byte	W12
	.byte		        Fn0 , v120
	.byte	W12
	.byte		        AsM1, v127
	.byte	W12
	.byte		        Fn0 , v120
	.byte	W12
	.byte		        AsM1, v127
	.byte	W12
	.byte		        Fn0 , v120
	.byte	W12
	.byte		        AsM1, v127
	.byte	W12
	.byte		        Fn0 , v120
	.byte	W12
@ 021   ----------------------------------------
	.byte		        GnM1, v127
	.byte	W12
	.byte		        Gn0 , v120
	.byte	W12
	.byte		        GnM1, v127
	.byte	W12
	.byte		        Gn0 , v120
	.byte	W12
	.byte		        GnM1, v127
	.byte	W12
	.byte		        AsM1
	.byte	W12
	.byte		        Cs0 
	.byte	W12
	.byte		        Fn0 
	.byte	W12
@ 022   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_3_019
@ 023   ----------------------------------------
	.byte		N11   , Cn0 , v127
	.byte	W12
	.byte		        Gn0 , v120
	.byte	W12
	.byte		        Cn0 , v127
	.byte	W12
	.byte		        Gn0 , v120
	.byte	W12
	.byte		        Cn0 , v127
	.byte	W12
	.byte		        En0 
	.byte	W12
	.byte		        Fn0 
	.byte	W12
	.byte		        Gn0 
	.byte	W12
@ 024   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_3_012
@ 025   ----------------------------------------
	.byte		N11   , AsM1, v127
	.byte	W12
	.byte		        Fn0 
	.byte	W12
	.byte		        AsM1
	.byte	W12
	.byte		        Fn0 
	.byte	W12
	.byte		        AsM1
	.byte	W12
	.byte		        Cn0 
	.byte	W12
	.byte		        Cs0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
@ 026   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_3_019
@ 027   ----------------------------------------
	.byte		N11   , Cn0 , v127
	.byte	W12
	.byte		        Gn0 , v120
	.byte	W12
	.byte		        Cn0 , v127
	.byte	W12
	.byte		        Gn0 , v120
	.byte	W12
	.byte		        Fn0 , v127
	.byte	W12
	.byte		        En0 
	.byte	W12
	.byte		        Fn0 
	.byte	W12
	.byte		        Gn0 
	.byte	W12
@ 028   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_3_012
@ 029   ----------------------------------------
	.byte		N11   , AsM1, v127
	.byte	W12
	.byte		        Fn0 
	.byte	W12
	.byte		        AsM1
	.byte	W12
	.byte		        Fn0 
	.byte	W12
	.byte		        AsM1
	.byte	W12
	.byte		        Fn0 
	.byte	W12
	.byte		        AsM1
	.byte	W12
	.byte		        Fn0 
	.byte	W12
@ 030   ----------------------------------------
	.byte		        Cn0 
	.byte	W12
	.byte		        Gn0 
	.byte	W12
	.byte		        Cn0 
	.byte	W12
	.byte		        Gn0 
	.byte	W12
	.byte		        Cn0 
	.byte	W12
	.byte		        Gn0 
	.byte	W12
	.byte		        Cn0 
	.byte	W12
	.byte		        Gn0 
	.byte	W12
@ 031   ----------------------------------------
	.byte		        Cn0 
	.byte	W12
	.byte		        Gn0 
	.byte	W12
	.byte		        Cn0 
	.byte	W12
	.byte		        Cn1 
	.byte	W12
	.byte		        As0 
	.byte	W12
	.byte		        Gn0 
	.byte	W12
	.byte		        Fn0 
	.byte	W12
	.byte		        Gn0 
	.byte	W12
@ 032   ----------------------------------------
	.byte		N08   , Cn0 
	.byte	W96
@ 033   ----------------------------------------
	.byte		N11   , Cs0 
	.byte	W84
	.byte		N05   , Dn0 , v112
	.byte	W12
@ 034   ----------------------------------------
	.byte		N08   , Dn0 , v127
	.byte	W96
@ 035   ----------------------------------------
	.byte		        Ds0 
	.byte	W60
	.byte		N11   
	.byte	W12
	.byte		        Gn0 
	.byte	W12
	.byte		        As0 
	.byte	W12
@ 036   ----------------------------------------
	.byte		        Cn0 
	.byte	W12
	.byte		        Gn0 
	.byte	W12
	.byte		        Cn1 
	.byte	W12
	.byte		        Cn0 
	.byte	W12
	.byte		        Gn0 
	.byte	W12
	.byte		        Cn1 
	.byte	W12
	.byte		        Cn0 
	.byte	W12
	.byte		        Gn0 
	.byte	W12
@ 037   ----------------------------------------
	.byte		        Cs0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
	.byte		        Cs1 
	.byte	W12
	.byte		        Cs0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
	.byte		        Cs1 
	.byte	W12
	.byte		        Cs0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
@ 038   ----------------------------------------
	.byte		        Dn0 
	.byte	W12
	.byte		        An0 
	.byte	W12
	.byte		        Dn1 
	.byte	W12
	.byte		        Dn0 
	.byte	W12
	.byte		        An0 
	.byte	W12
	.byte		        Dn1 
	.byte	W12
	.byte		        Dn0 
	.byte	W12
	.byte		        An0 
	.byte	W12
@ 039   ----------------------------------------
	.byte		        Ds1 
	.byte	W12
	.byte		        As0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Ds1 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Ds1 
	.byte	W12
	.byte		N23   , Dn1 
	.byte	W23
	.byte		N11   , Ds0 
	.byte	W01
@ 040   ----------------------------------------
mus_gymleader_johto_3_040:
	.byte	W11
	.byte		N11   , Gs0 , v127
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
	.byte		        Ds0 
	.byte	W01
	.byte	PEND
@ 041   ----------------------------------------
	.byte	W11
	.byte		        Gs0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Ds1 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Cs1 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
	.byte		        Ds0 
	.byte	W01
@ 042   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_3_040
@ 043   ----------------------------------------
	.byte	W11
	.byte		N11   , Gs0 , v127
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
	.byte		        Ds0 
	.byte	W13
	.byte		        An0 
	.byte	W11
	.byte		        Gs0 
	.byte	W12
	.byte		        Fs0 
	.byte	W12
	.byte		        Cs0 
	.byte	W01
@ 044   ----------------------------------------
	.byte	W11
	.byte		        Fs0 
	.byte	W12
	.byte		        Cs0 
	.byte	W12
	.byte		        Fs0 
	.byte	W12
	.byte		        Cs0 
	.byte	W12
	.byte		        Fs0 
	.byte	W12
	.byte		        Cs0 
	.byte	W12
	.byte		        Fs0 
	.byte	W12
	.byte		        Cs0 
	.byte	W01
@ 045   ----------------------------------------
	.byte	W11
	.byte		        Fs0 
	.byte	W12
	.byte		        Cs0 
	.byte	W12
	.byte		        Cs1 
	.byte	W12
	.byte		        Cs0 
	.byte	W12
	.byte		        An0 
	.byte	W12
	.byte		        Cs0 
	.byte	W12
	.byte		        Gn0 
	.byte	W12
	.byte		        Cs0 
	.byte	W01
@ 046   ----------------------------------------
	.byte	W11
	.byte		        Fs0 
	.byte	W12
	.byte		        Cs0 
	.byte	W12
	.byte		        Fs0 
	.byte	W12
	.byte		        Cs0 
	.byte	W12
	.byte		        Fs0 
	.byte	W12
	.byte		        Cs0 
	.byte	W12
	.byte		        Fs0 
	.byte	W13
@ 047   ----------------------------------------
	.byte		        Cs0 
	.byte	W12
	.byte		        Fs0 
	.byte	W12
	.byte		        Cs0 
	.byte	W12
	.byte		        Fs0 
	.byte	W12
	.byte		        Cs0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        En0 
	.byte	W12
	.byte		        An0 
	.byte	W12
@ 048   ----------------------------------------
	.byte		        Ds0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
@ 049   ----------------------------------------
	.byte		        Ds0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
	.byte		        An0 
	.byte	W12
	.byte		        Cs1 
	.byte	W12
@ 050   ----------------------------------------
	.byte		        Ds0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        As0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Bn0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Cs1 
	.byte	W12
@ 051   ----------------------------------------
	.byte		        Gs0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Fs0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
	.byte		        An0 
	.byte	W12
	.byte		N11   
	.byte	W12
	.byte		        Gs0 
	.byte	W12
	.byte		        Fs0 
	.byte	W12
@ 052   ----------------------------------------
	.byte		        Gs0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Fs0 
	.byte	W12
	.byte		        Gs0 
	.byte	W12
	.byte		        Fs0 
	.byte	W12
	.byte		N11   
	.byte	W12
	.byte		        En0 
	.byte	W12
	.byte		        Fs0 
	.byte	W12
@ 053   ----------------------------------------
mus_gymleader_johto_3_053:
	.byte		N11   , Fn0 , v127
	.byte	W12
	.byte		        Cn0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Fn0 
	.byte	W12
	.byte		        Fs0 
	.byte	W12
	.byte		N11   
	.byte	W12
	.byte		        Fn0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte	PEND
@ 054   ----------------------------------------
	.byte		        Fn0 
	.byte	W12
	.byte		        Cn0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Fn0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		N11   
	.byte	W12
	.byte		        Cs0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
@ 055   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_3_053
@ 056   ----------------------------------------
	.byte		N11   , Fn0 , v127
	.byte	W12
	.byte		        Cn0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Fn0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte		        Fs0 
	.byte	W12
	.byte		        Fn0 
	.byte	W12
	.byte		        Ds0 
	.byte	W12
	.byte	GOTO
	 .word	mus_gymleader_johto_3_B1
mus_gymleader_johto_3_B2:
@ 057   ----------------------------------------
	.byte	FINE

@**************** Track 4 (Midi-Chn.4) ****************@

mus_gymleader_johto_4:
	.byte	KEYSH , mus_gymleader_johto_key+0
@ 000   ----------------------------------------
	.byte		VOICE , 19
	.byte		VOL   , 100*mus_gymleader_johto_mvl/mxv
	.byte		PAN   , c_v-54
	.byte		MOD   , 0
	.byte		N05   , Fs4 , v092
	.byte	W06
	.byte		        Fn4 , v080
	.byte	W06
	.byte		        En4 , v088
	.byte	W06
	.byte		        As4 , v084
	.byte	W06
	.byte		        Fs4 , v092
	.byte	W06
	.byte		        Fn4 , v080
	.byte	W06
	.byte		        En4 , v088
	.byte	W06
	.byte		        As4 , v084
	.byte	W06
	.byte		PAN   , c_v+52
	.byte		N05   , Fs4 , v092
	.byte	W06
	.byte		        Fn4 , v080
	.byte	W06
	.byte		        En4 , v088
	.byte	W06
	.byte		        As4 , v084
	.byte	W06
	.byte		        Fs4 , v092
	.byte	W06
	.byte		        Fn4 , v080
	.byte	W06
	.byte		        En4 , v088
	.byte	W06
	.byte		        As4 , v084
	.byte	W06
@ 001   ----------------------------------------
	.byte		PAN   , c_v-54
	.byte		N05   , Fs4 , v092
	.byte	W06
	.byte		        Fn4 , v080
	.byte	W06
	.byte		        En4 , v088
	.byte	W06
	.byte		        As4 , v084
	.byte	W06
	.byte		        Fs4 , v092
	.byte	W06
	.byte		        Fn4 , v080
	.byte	W06
	.byte		        En4 , v088
	.byte	W06
	.byte		        As4 , v084
	.byte	W06
	.byte		PAN   , c_v+54
	.byte		N05   , Fs4 , v092
	.byte	W06
	.byte		        Fn4 , v080
	.byte	W06
	.byte		PAN   , c_v-54
	.byte		N05   , En4 , v088
	.byte	W06
	.byte		        As4 , v084
	.byte	W06
	.byte		PAN   , c_v+54
	.byte		N05   , Fs4 , v092
	.byte	W06
	.byte		        Fn4 , v080
	.byte	W06
	.byte		PAN   , c_v-54
	.byte		N05   , En4 , v088
	.byte	W06
	.byte		        As4 , v084
	.byte	W06
@ 002   ----------------------------------------
	.byte	W96
@ 003   ----------------------------------------
	.byte	W96
@ 004   ----------------------------------------
	.byte	W96
@ 005   ----------------------------------------
	.byte	W90
	.byte	W06
@ 006   ----------------------------------------
	.byte		PAN   , c_v-54
	.byte		N05   , Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		        En4 , v104
	.byte	W06
	.byte		        As4 
	.byte	W06
	.byte		        Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		        En4 , v104
	.byte	W06
	.byte		        As4 
	.byte	W06
	.byte		        Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		        En4 , v104
	.byte	W06
	.byte		        As4 
	.byte	W06
	.byte		        Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		        En4 , v104
	.byte	W06
	.byte		        As4 
	.byte	W06
@ 007   ----------------------------------------
	.byte		PAN   , c_v+50
	.byte		N05   , Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		        En4 , v104
	.byte	W06
	.byte		        As4 
	.byte	W06
	.byte		        Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		        En4 , v104
	.byte	W06
	.byte		        As4 
	.byte	W06
	.byte		        Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		        En4 , v104
	.byte	W06
	.byte		        As4 
	.byte	W06
	.byte		        Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		        En4 , v104
	.byte	W06
	.byte		        As4 
	.byte	W06
@ 008   ----------------------------------------
	.byte		PAN   , c_v-54
	.byte		N05   , Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		        En4 , v104
	.byte	W06
	.byte		        As4 
	.byte	W06
	.byte		        Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		        En4 , v104
	.byte	W06
	.byte		        As4 
	.byte	W06
	.byte		PAN   , c_v+50
	.byte		N05   , Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		        En4 , v104
	.byte	W06
	.byte		        As4 
	.byte	W06
	.byte		        Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		        En4 , v104
	.byte	W06
	.byte		        As4 
	.byte	W06
@ 009   ----------------------------------------
	.byte		PAN   , c_v-54
	.byte		N05   , Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		        En4 , v104
	.byte	W06
	.byte		        As4 
	.byte	W06
	.byte		PAN   , c_v+50
	.byte		N05   , Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		        En4 , v104
	.byte	W06
	.byte		        As4 
	.byte	W06
	.byte		PAN   , c_v-54
	.byte		N05   , Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		PAN   , c_v+49
	.byte		N05   , En4 , v104
	.byte	W06
	.byte		        As4 
	.byte	W06
	.byte		PAN   , c_v-54
	.byte		N05   , Fs4 , v108
	.byte	W06
	.byte		        Fn4 , v096
	.byte	W06
	.byte		PAN   , c_v+50
	.byte		N05   , En4 , v104
	.byte	W06
	.byte		        As4 
	.byte	W06
mus_gymleader_johto_4_B1:
@ 010   ----------------------------------------
	.byte		PAN   , c_v-54
	.byte	W96
@ 011   ----------------------------------------
	.byte	W96
@ 012   ----------------------------------------
	.byte	W96
@ 013   ----------------------------------------
mus_gymleader_johto_4_013:
	.byte		N05   , As4 , v084
	.byte	W06
	.byte		        Fn4 , v080
	.byte	W06
	.byte		        Cs4 , v084
	.byte	W06
	.byte		        Cn5 , v076
	.byte	W06
	.byte		        As4 , v084
	.byte	W06
	.byte		        Fn4 , v080
	.byte	W06
	.byte		        Cs4 , v084
	.byte	W06
	.byte		        As4 
	.byte	W06
	.byte		        Fn4 , v080
	.byte	W06
	.byte		        Cs4 , v084
	.byte	W06
	.byte		        Cn5 , v076
	.byte	W06
	.byte		        As4 , v084
	.byte	W06
	.byte		        Fn4 , v080
	.byte	W06
	.byte		        Cs4 , v084
	.byte	W06
	.byte		        Fn4 , v080
	.byte	W06
	.byte		        As4 , v084
	.byte	W06
	.byte	PEND
@ 014   ----------------------------------------
	.byte	W96
@ 015   ----------------------------------------
	.byte	W96
@ 016   ----------------------------------------
	.byte	W72
	.byte	W03
	.byte		PAN   , c_v+46
	.byte	W21
@ 017   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_4_013
@ 018   ----------------------------------------
	.byte	W96
@ 019   ----------------------------------------
	.byte		PAN   , c_v-54
	.byte	W96
@ 020   ----------------------------------------
	.byte	W96
@ 021   ----------------------------------------
	.byte	W96
@ 022   ----------------------------------------
	.byte	W96
@ 023   ----------------------------------------
	.byte	W96
@ 024   ----------------------------------------
	.byte	W96
@ 025   ----------------------------------------
	.byte	W96
@ 026   ----------------------------------------
	.byte	W96
@ 027   ----------------------------------------
	.byte	W96
@ 028   ----------------------------------------
	.byte	W96
@ 029   ----------------------------------------
	.byte	W96
@ 030   ----------------------------------------
	.byte	W96
@ 031   ----------------------------------------
	.byte	W96
@ 032   ----------------------------------------
	.byte	W96
@ 033   ----------------------------------------
	.byte	W96
@ 034   ----------------------------------------
	.byte	W96
@ 035   ----------------------------------------
	.byte	W96
@ 036   ----------------------------------------
	.byte	W96
@ 037   ----------------------------------------
	.byte	W96
@ 038   ----------------------------------------
	.byte	W96
@ 039   ----------------------------------------
	.byte	W96
@ 040   ----------------------------------------
	.byte	W96
@ 041   ----------------------------------------
	.byte	W96
@ 042   ----------------------------------------
	.byte	W96
@ 043   ----------------------------------------
	.byte	W96
@ 044   ----------------------------------------
	.byte	W96
@ 045   ----------------------------------------
	.byte	W96
@ 046   ----------------------------------------
	.byte	W96
@ 047   ----------------------------------------
	.byte	W96
@ 048   ----------------------------------------
	.byte	W96
@ 049   ----------------------------------------
	.byte	W96
@ 050   ----------------------------------------
	.byte	W96
@ 051   ----------------------------------------
	.byte	W96
@ 052   ----------------------------------------
	.byte	W96
@ 053   ----------------------------------------
	.byte	W96
@ 054   ----------------------------------------
	.byte	W96
@ 055   ----------------------------------------
	.byte	W96
@ 056   ----------------------------------------
	.byte	W96
	.byte	GOTO
	 .word	mus_gymleader_johto_4_B1
mus_gymleader_johto_4_B2:
@ 057   ----------------------------------------
	.byte	FINE

@**************** Track 5 (Midi-Chn.5) ****************@

mus_gymleader_johto_5:
	.byte	KEYSH , mus_gymleader_johto_key+0
@ 000   ----------------------------------------
	.byte		VOICE , 36
	.byte		VOL   , 0*mus_gymleader_johto_mvl/mxv
	.byte		PAN   , c_v-54
	.byte		MOD   , 0
	.byte	W96
@ 001   ----------------------------------------
	.byte	W96
@ 002   ----------------------------------------
	.byte	W96
@ 003   ----------------------------------------
	.byte	W96
@ 004   ----------------------------------------
	.byte	W96
@ 005   ----------------------------------------
	.byte	W96
@ 006   ----------------------------------------
	.byte	W96
@ 007   ----------------------------------------
	.byte	W96
@ 008   ----------------------------------------
	.byte	W96
@ 009   ----------------------------------------
	.byte	W96
mus_gymleader_johto_5_B1:
@ 010   ----------------------------------------
mus_gymleader_johto_5_010:
	.byte		N05   , Gn3 , v112
	.byte	W06
	.byte		        Gn3 , v092
	.byte	W06
	.byte		        Gn3 , v100
	.byte	W06
	.byte		        Gn3 , v088
	.byte	W06
	.byte		        Gn3 , v112
	.byte	W06
	.byte		        Gn3 , v092
	.byte	W06
	.byte		        Gn3 , v100
	.byte	W06
	.byte		        Gn3 , v088
	.byte	W06
	.byte		        Gn3 , v112
	.byte	W06
	.byte		        Gn3 , v092
	.byte	W06
	.byte		        Gn3 , v100
	.byte	W06
	.byte		        Gn3 , v088
	.byte	W06
	.byte		        Gn3 , v112
	.byte	W06
	.byte		        Gn3 , v092
	.byte	W06
	.byte		        Gn3 , v100
	.byte	W06
	.byte		        Gn3 , v088
	.byte	W06
	.byte	PEND
@ 011   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_010
@ 012   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_010
@ 013   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_010
@ 014   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_010
@ 015   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_010
@ 016   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_010
@ 017   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_010
@ 018   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_010
@ 019   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_010
@ 020   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_010
@ 021   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_010
@ 022   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_010
@ 023   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_010
@ 024   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_010
@ 025   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_010
@ 026   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_010
@ 027   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_010
@ 028   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_010
@ 029   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_010
@ 030   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_010
@ 031   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_010
@ 032   ----------------------------------------
	.byte	W96
@ 033   ----------------------------------------
	.byte	W96
@ 034   ----------------------------------------
	.byte	W96
@ 035   ----------------------------------------
	.byte	W96
@ 036   ----------------------------------------
	.byte	W96
@ 037   ----------------------------------------
	.byte	W96
@ 038   ----------------------------------------
	.byte	W96
@ 039   ----------------------------------------
	.byte	W96
@ 040   ----------------------------------------
mus_gymleader_johto_5_040:
	.byte		N05   , Gn3 , v100
	.byte	W06
	.byte		        Gn3 , v084
	.byte	W06
	.byte		        Gn3 , v092
	.byte	W06
	.byte		        Gn3 , v076
	.byte	W06
	.byte		        Gn3 , v100
	.byte	W06
	.byte		        Gn3 , v084
	.byte	W06
	.byte		        Gn3 , v092
	.byte	W06
	.byte		        Gn3 , v076
	.byte	W06
	.byte		        Gn3 , v100
	.byte	W06
	.byte		        Gn3 , v084
	.byte	W06
	.byte		        Gn3 , v092
	.byte	W06
	.byte		        Gn3 , v076
	.byte	W06
	.byte		        Gn3 , v100
	.byte	W06
	.byte		        Gn3 , v084
	.byte	W06
	.byte		        Gn3 , v092
	.byte	W06
	.byte		        Gn3 , v076
	.byte	W06
	.byte	PEND
@ 041   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_040
@ 042   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_040
@ 043   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_040
@ 044   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_040
@ 045   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_040
@ 046   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_040
@ 047   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_040
@ 048   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_040
@ 049   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_040
@ 050   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_040
@ 051   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_040
@ 052   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_040
@ 053   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_040
@ 054   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_040
@ 055   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_040
@ 056   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_5_040
	.byte	GOTO
	 .word	mus_gymleader_johto_5_B1
mus_gymleader_johto_5_B2:
@ 057   ----------------------------------------
	.byte	FINE

@**************** Track 6 (Midi-Chn.6) ****************@

mus_gymleader_johto_6:
	.byte	KEYSH , mus_gymleader_johto_key+0
@ 000   ----------------------------------------
	.byte		VOICE , 48
	.byte		VOL   , 120*mus_gymleader_johto_mvl/mxv
	.byte		PAN   , c_v+36
	.byte		MOD   , 0
	.byte	W96
@ 001   ----------------------------------------
	.byte	W96
@ 002   ----------------------------------------
	.byte	W96
@ 003   ----------------------------------------
	.byte	W96
@ 004   ----------------------------------------
	.byte	W96
@ 005   ----------------------------------------
	.byte	W96
@ 006   ----------------------------------------
	.byte		N17   , Dn1 , v092
	.byte	W24
	.byte		N01   , Dn1 , v084
	.byte	W12
	.byte		N01   
	.byte	W12
	.byte		N11   , Dn1 , v092
	.byte	W24
	.byte		N01   , Dn1 , v084
	.byte	W12
	.byte		N01   
	.byte	W12
@ 007   ----------------------------------------
	.byte		N17   , Dn1 , v092
	.byte	W24
	.byte		N01   , Dn1 , v084
	.byte	W12
	.byte		N11   , Dn1 , v092
	.byte	W24
	.byte		N01   , Dn1 , v084
	.byte	W12
	.byte		N17   , Ds1 , v092
	.byte	W24
@ 008   ----------------------------------------
	.byte		        Dn1 
	.byte	W24
	.byte		N01   , Dn1 , v084
	.byte	W12
	.byte		N01   
	.byte	W12
	.byte		N17   , Dn1 , v092
	.byte	W24
	.byte		N01   , Dn1 , v084
	.byte	W12
	.byte		N01   
	.byte	W12
@ 009   ----------------------------------------
	.byte		N17   , Dn1 , v092
	.byte	W24
	.byte		N01   , Dn1 , v084
	.byte	W12
	.byte		N11   , Dn1 , v092
	.byte	W24
	.byte		N01   , Dn1 , v084
	.byte	W12
	.byte		N23   , Ds1 , v092
	.byte	W24
mus_gymleader_johto_6_B1:
@ 010   ----------------------------------------
mus_gymleader_johto_6_010:
	.byte		N17   , Gn1 , v092
	.byte	W24
	.byte		N01   , Gn1 , v084
	.byte	W12
	.byte		N01   
	.byte	W12
	.byte		N11   , Gn1 , v092
	.byte	W24
	.byte		N01   , Gn1 , v084
	.byte	W12
	.byte		N01   
	.byte	W12
	.byte	PEND
@ 011   ----------------------------------------
mus_gymleader_johto_6_011:
	.byte		N17   , Gn1 , v092
	.byte	W24
	.byte		N01   , Gn1 , v084
	.byte	W12
	.byte		N11   , Gn1 , v092
	.byte	W24
	.byte		N01   , Gn1 , v084
	.byte	W12
	.byte		N17   , Gn1 , v092
	.byte	W24
	.byte	PEND
@ 012   ----------------------------------------
mus_gymleader_johto_6_012:
	.byte		N17   , Gs1 , v092
	.byte	W24
	.byte		N01   , Gs1 , v084
	.byte	W12
	.byte		N01   
	.byte	W12
	.byte		N17   , Gs1 , v092
	.byte	W24
	.byte		N01   , Gs1 , v084
	.byte	W12
	.byte		N01   
	.byte	W12
	.byte	PEND
@ 013   ----------------------------------------
	.byte		N17   , Gs1 , v092
	.byte	W24
	.byte		N01   , Gs1 , v084
	.byte	W12
	.byte		N11   , Gs1 , v092
	.byte	W24
	.byte		N01   , As1 , v084
	.byte	W12
	.byte		N23   , Gs1 , v092
	.byte	W24
@ 014   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_6_010
@ 015   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_6_011
@ 016   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_6_012
@ 017   ----------------------------------------
	.byte		N17   , Gs1 , v092
	.byte	W24
	.byte		N01   , Gs1 , v084
	.byte	W12
	.byte		        Cs4 , v127
	.byte		N01   , Ds5 
	.byte	W06
	.byte		        Cs4 
	.byte		N01   , Ds5 
	.byte	W05
	.byte		PAN   , c_v+0
	.byte	W01
	.byte		N44   , Gs1 , v112, gtp2
	.byte		N44   , Gs2 , v112, gtp2
	.byte	W06
	.byte		BEND  , c_v-6
	.byte	W03
	.byte		        c_v-11
	.byte	W03
	.byte		        c_v-17
	.byte	W03
	.byte		        c_v-22
	.byte	W03
	.byte		        c_v-27
	.byte	W03
	.byte		        c_v-33
	.byte	W03
	.byte		        c_v-38
	.byte	W03
	.byte		        c_v-43
	.byte	W03
	.byte		        c_v-49
	.byte	W03
	.byte		        c_v-53
	.byte	W01
	.byte	W02
	.byte		        c_v-59
	.byte	W01
	.byte	W02
	.byte		        c_v-64
	.byte	W01
	.byte	W03
	.byte	W03
	.byte		        c_v-7
	.byte	W02
@ 018   ----------------------------------------
	.byte		N32   , Cn3 , v100, gtp2
	.byte	W01
	.byte		        Fn3 , v116, gtp1
	.byte	W01
	.byte		BEND  , c_v+0
	.byte	W03
	.byte		        c_v+0
	.byte	W30
	.byte	W01
	.byte		N32   , Cn3 , v100, gtp2
	.byte	W01
	.byte		        Ds3 , v116, gtp1
	.byte	W32
	.byte	W03
	.byte		N22   , Cn3 , v100
	.byte	W01
	.byte		N21   , Fn3 , v116
	.byte	W22
	.byte		BEND  , c_v-6
	.byte	W01
@ 019   ----------------------------------------
	.byte		N32   , Ds3 , v100, gtp2
	.byte	W01
	.byte		        Cn4 , v116, gtp1
	.byte	W01
	.byte		BEND  , c_v+0
	.byte	W04
	.byte		        c_v+0
	.byte	W30
	.byte		N32   , Gn3 , v100, gtp2
	.byte	W01
	.byte		        As3 , v116, gtp1
	.byte	W32
	.byte	W03
	.byte		N22   , Gn3 , v100
	.byte	W01
	.byte		N21   , Cn4 , v116
	.byte	W22
	.byte		BEND  , c_v-6
	.byte	W01
@ 020   ----------------------------------------
	.byte		N32   , Fn2 , v100, gtp2
	.byte	W01
	.byte		        Cs3 , v116, gtp1
	.byte	W01
	.byte		BEND  , c_v+0
	.byte	W04
	.byte		        c_v+0
	.byte	W30
	.byte		N32   , Gs2 , v100, gtp2
	.byte	W01
	.byte		        Cn3 , v116, gtp1
	.byte	W32
	.byte	W03
	.byte		N16   , Fn2 , v100
	.byte	W01
	.byte		N15   , Cs3 , v116
	.byte	W17
	.byte		N05   , Cs3 , v100
	.byte		N04   , As3 , v116
	.byte	W04
	.byte		BEND  , c_v-1
	.byte	W02
@ 021   ----------------------------------------
	.byte		N32   , Fn3 , v100, gtp2
	.byte	W01
	.byte		        Cs4 , v116, gtp1
	.byte	W05
	.byte		BEND  , c_v+0
	.byte	W30
	.byte		N32   , Ds3 , v100, gtp2
	.byte	W01
	.byte		        Cn4 , v116, gtp1
	.byte	W32
	.byte	W03
	.byte		N22   , Fn3 , v100
	.byte	W01
	.byte		N21   , Cs4 , v116
	.byte	W22
	.byte		BEND  , c_v-6
	.byte	W01
@ 022   ----------------------------------------
	.byte		N92   , En3 , v100, gtp2
	.byte	W01
	.byte		        Cn4 , v116, gtp1
	.byte	W01
	.byte		BEND  , c_v+0
	.byte	W03
	.byte		        c_v+0
	.byte	W68
	.byte	W02
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W05
	.byte		        c_v-6
	.byte	W01
@ 023   ----------------------------------------
	.byte		N92   , Cn4 , v112, gtp2
	.byte	W01
	.byte		        En4 , v112, gtp1
	.byte	W01
	.byte		BEND  , c_v+0
	.byte	W04
	.byte		        c_v+0
	.byte	W68
	.byte	W01
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W02
	.byte		        c_v-6
	.byte	W01
@ 024   ----------------------------------------
	.byte		N92   , Cs3 , v108, gtp2
	.byte	W02
	.byte		BEND  , c_v+0
	.byte	W04
	.byte		        c_v+0
	.byte	W66
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W05
	.byte		        c_v-6
	.byte	W01
@ 025   ----------------------------------------
	.byte		N44   , As2 , v112, gtp2
	.byte	W02
	.byte		BEND  , c_v+0
	.byte	W04
	.byte		        c_v+0
	.byte	W42
	.byte		N32   , Cs3 , v108, gtp2
	.byte	W36
	.byte		N10   , Ds3 
	.byte	W11
	.byte		BEND  , c_v-6
	.byte	W01
@ 026   ----------------------------------------
	.byte		N92   , Cn3 , v108, gtp2
	.byte	W02
	.byte		BEND  , c_v+0
	.byte	W04
	.byte		        c_v+0
	.byte	W72
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W02
	.byte		        c_v-6
	.byte	W01
@ 027   ----------------------------------------
	.byte		N92   , En3 , v104, gtp2
	.byte	W02
	.byte		BEND  , c_v+0
	.byte	W01
	.byte	W02
	.byte		        c_v+0
	.byte	W68
	.byte	W02
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
	.byte	W03
@ 028   ----------------------------------------
	.byte	W96
@ 029   ----------------------------------------
	.byte	W04
	.byte	W92
@ 030   ----------------------------------------
	.byte	W96
@ 031   ----------------------------------------
	.byte		PAN   , c_v+46
	.byte	W96
@ 032   ----------------------------------------
	.byte		N08   , Cn2 , v080
	.byte		N08   , Fn2 , v088
	.byte	W36
	.byte		        Cn2 , v080
	.byte		N08   , Fn2 , v088
	.byte	W36
	.byte		        Cn2 , v080
	.byte		N08   , Fn2 , v088
	.byte	W24
@ 033   ----------------------------------------
	.byte		        Cs2 , v080
	.byte		N08   , Fs2 , v088
	.byte	W36
	.byte		        Cs2 , v080
	.byte		N08   , Fs2 , v088
	.byte	W36
	.byte		        Cs2 , v080
	.byte		N08   , Fs2 , v088
	.byte	W12
	.byte		N01   , Cs2 , v060
	.byte		N01   , Fs2 , v064
	.byte	W12
@ 034   ----------------------------------------
	.byte		N08   , Dn2 , v080
	.byte		N08   , Gn2 , v088
	.byte	W36
	.byte		        Dn2 , v080
	.byte		N08   , Gn2 , v088
	.byte	W36
	.byte		        Dn2 , v080
	.byte		N08   , Gn2 , v088
	.byte	W12
	.byte		N01   , Dn2 , v060
	.byte		N01   , Gn2 , v064
	.byte	W12
@ 035   ----------------------------------------
	.byte		N08   , Ds2 , v080
	.byte		N08   , Gs2 , v088
	.byte	W36
	.byte		        Ds2 , v080
	.byte		N08   , Gs2 , v088
	.byte	W36
	.byte		        Ds2 , v080
	.byte		N08   , Gs2 , v088
	.byte	W24
@ 036   ----------------------------------------
	.byte		        Cn2 
	.byte		N08   , Gn2 , v092
	.byte	W12
	.byte		N01   , Cn2 , v060
	.byte		N01   , Gn2 , v068
	.byte	W06
	.byte		        Cn2 , v052
	.byte		N01   , Gn2 , v060
	.byte	W06
	.byte		        Cn2 
	.byte		N01   , Gn2 , v068
	.byte	W06
	.byte		        Cn2 , v052
	.byte		N01   , Gn2 , v060
	.byte	W06
	.byte		N08   , Cn2 , v088
	.byte		N08   , Gn2 , v092
	.byte	W12
	.byte		N01   , Cn2 , v060
	.byte		N01   , Gn2 , v068
	.byte	W06
	.byte		        Cn2 , v052
	.byte		N01   , Gn2 , v060
	.byte	W06
	.byte		        Cn2 
	.byte		N01   , Gn2 , v068
	.byte	W06
	.byte		        Cn2 , v052
	.byte		N01   , Gn2 , v060
	.byte	W06
	.byte		N08   , Cn2 , v088
	.byte		N08   , Gn2 , v092
	.byte	W12
	.byte		N01   , Cn2 , v060
	.byte		N01   , Gn2 , v068
	.byte	W06
	.byte		        Cn2 , v052
	.byte		N01   , Gn2 , v060
	.byte	W06
@ 037   ----------------------------------------
	.byte		N08   , Cs2 , v088
	.byte		N08   , Gs2 , v092
	.byte	W12
	.byte		N01   , Cs2 , v060
	.byte		N01   , Gs2 , v068
	.byte	W06
	.byte		        Cs2 , v052
	.byte		N01   , Gs2 , v060
	.byte	W06
	.byte		        Cs2 
	.byte		N01   , Gs2 , v068
	.byte	W06
	.byte		        Cs2 , v052
	.byte		N01   , Gs2 , v060
	.byte	W06
	.byte		N08   , Cs2 , v088
	.byte		N08   , Gs2 , v092
	.byte	W12
	.byte		N01   , Cs2 , v060
	.byte		N01   , Gs2 , v068
	.byte	W06
	.byte		        Cs2 , v052
	.byte		N01   , Gs2 , v060
	.byte	W06
	.byte		        Cs2 
	.byte		N01   , Gs2 , v068
	.byte	W06
	.byte		        Cs2 , v052
	.byte		N01   , Gs2 , v060
	.byte	W06
	.byte		N08   , Cs2 , v088
	.byte		N08   , Gs2 , v092
	.byte	W12
	.byte		N01   , Cs2 , v060
	.byte		N01   , Gs2 , v068
	.byte	W06
	.byte		        Cs2 , v052
	.byte		N01   , Gs2 , v060
	.byte	W06
@ 038   ----------------------------------------
	.byte		N08   , Dn2 , v092
	.byte		N08   , An2 , v100
	.byte	W12
	.byte		N01   , Dn2 , v068
	.byte		N01   , An2 , v072
	.byte	W06
	.byte		        Dn2 , v060
	.byte		N01   , An2 , v064
	.byte	W06
	.byte		        Dn2 , v068
	.byte		N01   , An2 , v072
	.byte	W06
	.byte		        Dn2 , v060
	.byte		N01   , An2 , v064
	.byte	W06
	.byte		N08   , Dn2 , v092
	.byte		N08   , An2 , v100
	.byte	W12
	.byte		N01   , Dn2 , v068
	.byte		N01   , An2 , v072
	.byte	W06
	.byte		        Dn2 , v060
	.byte		N01   , An2 , v064
	.byte	W06
	.byte		        Dn2 , v068
	.byte		N01   , An2 , v072
	.byte	W06
	.byte		        Dn2 , v060
	.byte		N01   , An2 , v064
	.byte	W06
	.byte		N08   , Dn2 , v092
	.byte		N08   , An2 , v100
	.byte	W12
	.byte		N01   , Dn2 , v068
	.byte		N01   , An2 , v072
	.byte	W06
	.byte		        Dn2 , v060
	.byte		N01   , An2 , v064
	.byte	W06
@ 039   ----------------------------------------
	.byte		N08   , Ds2 , v092
	.byte		N08   , As2 , v100
	.byte	W12
	.byte		N01   , Ds2 , v068
	.byte		N01   , As2 , v072
	.byte	W06
	.byte		        Ds2 , v060
	.byte		N01   , As2 , v064
	.byte	W06
	.byte		        Ds2 , v068
	.byte		N01   , As2 , v072
	.byte	W06
	.byte		        Ds2 , v060
	.byte		N01   , As2 , v064
	.byte	W06
	.byte		N08   , Ds2 , v092
	.byte		N08   , As2 , v100
	.byte	W12
	.byte		N01   , Ds2 , v068
	.byte		N01   , As2 , v072
	.byte	W06
	.byte		        Ds2 , v060
	.byte		N01   , As2 , v064
	.byte	W06
	.byte		        Ds2 , v068
	.byte		N01   , As2 , v072
	.byte	W06
	.byte		        Ds2 , v060
	.byte		N01   , As2 , v064
	.byte	W06
	.byte		N08   , Ds2 , v092
	.byte		N08   , As2 , v100
	.byte	W12
	.byte		N01   , Ds2 , v068
	.byte		N01   , As2 , v072
	.byte	W06
	.byte		        Ds2 , v060
	.byte		N01   , As2 , v064
	.byte	W06
@ 040   ----------------------------------------
mus_gymleader_johto_6_040:
	.byte		N17   , Gs1 , v092
	.byte	W24
	.byte		N01   , Gs1 , v084
	.byte	W12
	.byte		N01   
	.byte	W12
	.byte		N11   , Gs1 , v092
	.byte	W24
	.byte		N01   , Gs1 , v084
	.byte	W12
	.byte		N01   
	.byte	W12
	.byte	PEND
@ 041   ----------------------------------------
	.byte		N17   , Gs1 , v092
	.byte	W24
	.byte		N01   , Gs1 , v084
	.byte	W12
	.byte		N11   , Gs1 , v092
	.byte	W24
	.byte		N01   , Gs1 , v084
	.byte	W12
	.byte		N17   , Gs1 , v092
	.byte	W24
@ 042   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_6_012
@ 043   ----------------------------------------
	.byte		N17   , Gs1 , v092
	.byte	W24
	.byte		N01   , Gs1 , v084
	.byte	W12
	.byte		N11   , Gs1 , v092
	.byte	W24
	.byte		N01   , Gs1 , v084
	.byte	W12
	.byte		N23   , Gs1 , v092
	.byte	W24
@ 044   ----------------------------------------
	.byte		N17   , Fs1 
	.byte	W24
	.byte		N01   , Fs1 , v084
	.byte	W12
	.byte		N01   
	.byte	W12
	.byte		N11   , Fs1 , v092
	.byte	W24
	.byte		N01   , Fs1 , v084
	.byte	W12
	.byte		N01   
	.byte	W12
@ 045   ----------------------------------------
	.byte		N17   , Fs1 , v092
	.byte	W24
	.byte		N01   , Fs1 , v084
	.byte	W12
	.byte		N11   , Fs1 , v092
	.byte	W24
	.byte		N01   , Fs1 , v084
	.byte	W12
	.byte		N17   , Fs1 , v092
	.byte	W24
@ 046   ----------------------------------------
	.byte		N17   
	.byte	W24
	.byte		N01   , Fs1 , v084
	.byte	W12
	.byte		N01   
	.byte	W12
	.byte		N17   , Fs1 , v092
	.byte	W24
	.byte		N01   , Fs1 , v084
	.byte	W12
	.byte		N01   
	.byte	W12
@ 047   ----------------------------------------
	.byte		N17   , Fs1 , v092
	.byte	W24
	.byte		N01   , Fs1 , v084
	.byte	W12
	.byte		N11   , Fs1 , v092
	.byte	W24
	.byte		N01   , Fs1 , v084
	.byte	W12
	.byte		N23   , Fs1 , v092
	.byte	W24
@ 048   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_6_040
@ 049   ----------------------------------------
	.byte		N17   , Gs1 , v092
	.byte	W24
	.byte		N01   , Gs1 , v084
	.byte	W12
	.byte		N11   , Gs1 , v092
	.byte	W24
	.byte		N01   , Gs1 , v084
	.byte	W12
	.byte		N11   , Gs1 , v092
	.byte	W12
	.byte		N01   , Gs1 , v072
	.byte	W06
	.byte		N01   
	.byte	W06
@ 050   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_6_012
@ 051   ----------------------------------------
	.byte		N17   , Gs1 , v096
	.byte	W24
	.byte		N01   , Gs1 , v088
	.byte	W06
	.byte		N01   
	.byte	W06
	.byte		N18   , Gs1 , v096
	.byte	W24
	.byte		N01   , Gs1 , v088
	.byte	W06
	.byte		N01   
	.byte	W06
	.byte		N06   , Gs1 , v096
	.byte	W12
	.byte		N01   , Gs1 , v088
	.byte	W06
	.byte		N01   
	.byte	W06
@ 052   ----------------------------------------
	.byte		N11   , Gs1 , v096
	.byte	W96
@ 053   ----------------------------------------
	.byte		N17   , Fn1 , v092
	.byte	W24
	.byte		N01   , Fn1 , v084
	.byte	W12
	.byte		N01   
	.byte	W12
	.byte		N11   , Fn1 , v092
	.byte	W24
	.byte		N01   , Fn1 , v084
	.byte	W12
	.byte		N01   
	.byte	W12
@ 054   ----------------------------------------
	.byte		N17   , Fn1 , v092
	.byte	W24
	.byte		N01   , Fn1 , v084
	.byte	W12
	.byte		N11   , Fn1 , v092
	.byte	W24
	.byte		N01   , Fn1 , v084
	.byte	W12
	.byte		N10   , Fn1 , v092
	.byte	W12
	.byte		N01   , Fn1 , v084
	.byte	W12
@ 055   ----------------------------------------
	.byte		N17   , Fn1 , v092
	.byte	W24
	.byte		N01   , Fn1 , v084
	.byte	W12
	.byte		N01   
	.byte	W12
	.byte		N17   , Fn1 , v092
	.byte	W24
	.byte		N01   , Fn1 , v084
	.byte	W12
	.byte		N01   
	.byte	W12
@ 056   ----------------------------------------
	.byte		N17   , Fn1 , v092
	.byte	W24
	.byte		N01   , Fn1 , v084
	.byte	W12
	.byte		N11   , Fn1 , v092
	.byte	W24
	.byte		N01   , Fn1 , v084
	.byte	W12
	.byte		N23   , Fn1 , v092
	.byte	W24
	.byte	GOTO
	 .word	mus_gymleader_johto_6_B1
mus_gymleader_johto_6_B2:
@ 057   ----------------------------------------
	.byte	FINE

@**************** Track 7 (Midi-Chn.7) ****************@

mus_gymleader_johto_7:
	.byte	KEYSH , mus_gymleader_johto_key+0
@ 000   ----------------------------------------
	.byte		VOICE , 48
	.byte		VOL   , 110*mus_gymleader_johto_mvl/mxv
	.byte		PAN   , c_v+46
	.byte		MOD   , 0
	.byte	W96
@ 001   ----------------------------------------
	.byte	W96
@ 002   ----------------------------------------
	.byte	W96
@ 003   ----------------------------------------
	.byte	W96
@ 004   ----------------------------------------
	.byte	W96
@ 005   ----------------------------------------
	.byte	W92
	.byte	W03
	.byte	W01
@ 006   ----------------------------------------
	.byte		N92   , Dn3 , v100, gtp3
	.byte		N92   , Fn3 , v108, gtp3
	.byte	W06
	.byte	W12
	.byte	W12
	.byte	W12
	.byte	W18
	.byte	W06
	.byte	W18
	.byte	W12
@ 007   ----------------------------------------
	.byte		        Dn3 , v100, gtp3
	.byte		N92   , Gn3 , v112, gtp3
	.byte	W06
	.byte	W12
	.byte	W12
	.byte	W12
	.byte	W18
	.byte	W06
	.byte	W18
	.byte	W12
@ 008   ----------------------------------------
	.byte		        Dn3 , v100, gtp3
	.byte		N92   , An3 , v108, gtp3
	.byte	W12
	.byte	W12
	.byte	W18
	.byte	W18
	.byte	W06
	.byte	W18
	.byte	W12
@ 009   ----------------------------------------
	.byte		        Dn3 , v100, gtp3
	.byte		N44   , Cn4 , v104, gtp3
	.byte	W06
	.byte	W18
	.byte	W18
	.byte	W06
	.byte		        Ds4 , v108, gtp3
	.byte	W18
	.byte	W30
mus_gymleader_johto_7_B1:
@ 010   ----------------------------------------
	.byte		N92   , Dn4 , v100, gtp3
	.byte	W84
	.byte	W06
	.byte	W06
@ 011   ----------------------------------------
	.byte	W96
@ 012   ----------------------------------------
	.byte	W96
@ 013   ----------------------------------------
	.byte	W96
@ 014   ----------------------------------------
	.byte	W96
@ 015   ----------------------------------------
	.byte	W96
@ 016   ----------------------------------------
	.byte	W96
@ 017   ----------------------------------------
	.byte	W96
@ 018   ----------------------------------------
	.byte	W96
@ 019   ----------------------------------------
	.byte	W96
@ 020   ----------------------------------------
	.byte	W96
@ 021   ----------------------------------------
	.byte	W96
@ 022   ----------------------------------------
	.byte	W96
@ 023   ----------------------------------------
	.byte	W96
@ 024   ----------------------------------------
	.byte	W96
@ 025   ----------------------------------------
	.byte	W96
@ 026   ----------------------------------------
	.byte	W96
@ 027   ----------------------------------------
	.byte	W96
@ 028   ----------------------------------------
	.byte	W96
@ 029   ----------------------------------------
	.byte	W96
@ 030   ----------------------------------------
	.byte	W96
@ 031   ----------------------------------------
	.byte	W96
@ 032   ----------------------------------------
	.byte	W96
@ 033   ----------------------------------------
	.byte	W96
@ 034   ----------------------------------------
	.byte	W96
@ 035   ----------------------------------------
	.byte	W90
	.byte	W06
@ 036   ----------------------------------------
	.byte		        Gn3 , v088, gtp3
	.byte	W96
@ 037   ----------------------------------------
	.byte		        Gs3 , v096, gtp3
	.byte	W96
@ 038   ----------------------------------------
	.byte		N44   , An3 , v092, gtp3
	.byte	W48
	.byte		N11   , As3 , v096
	.byte	W12
	.byte		        An3 , v084
	.byte	W12
	.byte		        Gs3 , v088
	.byte	W12
	.byte		        An3 , v080
	.byte	W12
@ 039   ----------------------------------------
	.byte		N44   , As3 , v096, gtp3
	.byte	W48
	.byte		N11   , Bn3 
	.byte	W12
	.byte		        As3 , v088
	.byte	W12
	.byte		        An3 , v092
	.byte	W12
	.byte		        Cs4 , v088
	.byte	W12
@ 040   ----------------------------------------
	.byte	W96
@ 041   ----------------------------------------
	.byte	W96
@ 042   ----------------------------------------
	.byte	W96
@ 043   ----------------------------------------
	.byte	W96
@ 044   ----------------------------------------
	.byte	W96
@ 045   ----------------------------------------
	.byte	W96
@ 046   ----------------------------------------
	.byte	W96
@ 047   ----------------------------------------
	.byte	W96
@ 048   ----------------------------------------
	.byte	W96
@ 049   ----------------------------------------
	.byte	W96
@ 050   ----------------------------------------
	.byte	W96
@ 051   ----------------------------------------
	.byte	W96
@ 052   ----------------------------------------
	.byte	W96
@ 053   ----------------------------------------
	.byte		N92   , Fn3 , v096, gtp3
	.byte	W96
@ 054   ----------------------------------------
	.byte		        Cn4 , v104, gtp3
	.byte	W96
@ 055   ----------------------------------------
	.byte		        Bn3 , v092, gtp3
	.byte	W96
@ 056   ----------------------------------------
	.byte		        Gn3 , v096, gtp3
	.byte	W96
	.byte	GOTO
	 .word	mus_gymleader_johto_7_B1
mus_gymleader_johto_7_B2:
@ 057   ----------------------------------------
	.byte	FINE

@**************** Track 8 (Midi-Chn.10) ****************@

mus_gymleader_johto_8:
	.byte	KEYSH , mus_gymleader_johto_key+0
@ 000   ----------------------------------------
	.byte		VOICE , 0
	.byte		MOD   , 0
	.byte		PAN   , c_v-49
	.byte		VOL   , 100*mus_gymleader_johto_mvl/mxv
	.byte		MOD   , 0
	.byte		PAN   , c_v+0
	.byte		VOL   , 100*mus_gymleader_johto_mvl/mxv
	.byte		        100*mus_gymleader_johto_mvl/mxv
	.byte		PAN   , c_v+0
	.byte		MOD   , 0
	.byte	W96
@ 001   ----------------------------------------
	.byte		N11   , Bn0 , v112
	.byte	W48
	.byte		        Bn0 , v120
	.byte	W12
	.byte		        Bn0 , v116
	.byte	W12
	.byte		N05   , Bn0 , v120
	.byte	W06
	.byte		        Bn0 , v116
	.byte	W06
	.byte		        Bn0 , v120
	.byte	W06
	.byte		        Bn0 , v116
	.byte	W06
@ 002   ----------------------------------------
	.byte		N11   , Bn0 , v120
	.byte		N23   , An2 
	.byte	W24
	.byte		N11   , Bn0 
	.byte	W24
	.byte		N11   
	.byte	W24
	.byte		N11   
	.byte	W24
@ 003   ----------------------------------------
mus_gymleader_johto_8_003:
	.byte		N11   , Bn0 , v120
	.byte	W24
	.byte		N11   
	.byte	W24
	.byte		N11   
	.byte	W24
	.byte		N11   
	.byte	W24
	.byte	PEND
@ 004   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 005   ----------------------------------------
	.byte		N11   , Bn0 , v120
	.byte	W24
	.byte		N11   
	.byte	W24
	.byte		N11   
	.byte	W24
	.byte		N05   
	.byte	W06
	.byte		        Bn0 , v112
	.byte	W06
	.byte		        Bn0 , v120
	.byte	W06
	.byte		        Bn0 , v112
	.byte	W06
@ 006   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 007   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 008   ----------------------------------------
	.byte		N11   , Bn0 , v120
	.byte		N05   , Dn1 , v080
	.byte	W06
	.byte		N05   
	.byte	W06
	.byte		N05   
	.byte	W06
	.byte		        Dn1 , v084
	.byte	W06
	.byte		N11   , Bn0 , v120
	.byte		N05   , Dn1 , v084
	.byte	W06
	.byte		N05   
	.byte	W06
	.byte		N05   
	.byte	W06
	.byte		        Dn1 , v088
	.byte	W06
	.byte		N11   , Bn0 , v120
	.byte		N05   , Dn1 , v088
	.byte	W06
	.byte		N05   
	.byte	W06
	.byte		N05   
	.byte	W06
	.byte		N05   
	.byte	W06
	.byte		N11   , Bn0 , v120
	.byte		N05   , Dn1 , v092
	.byte	W06
	.byte		N05   
	.byte	W06
	.byte		N05   
	.byte	W06
	.byte		N05   
	.byte	W06
@ 009   ----------------------------------------
	.byte		N11   , Bn0 , v120
	.byte		N05   , Dn1 , v096
	.byte	W06
	.byte		N05   
	.byte	W06
	.byte		N05   
	.byte	W06
	.byte		N05   
	.byte	W06
	.byte		N11   , Bn0 , v120
	.byte		N05   , Dn1 , v100
	.byte	W06
	.byte		N05   
	.byte	W06
	.byte		N05   
	.byte	W06
	.byte		N05   
	.byte	W06
	.byte		N11   , Bn0 , v120
	.byte		N02   , Dn1 , v104
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		N11   , Bn0 , v120
	.byte		N02   , Dn1 , v104
	.byte	W03
	.byte		        Dn1 , v108
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		N11   , Bn0 , v116
	.byte		N02   , Dn1 , v108
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		N02   
	.byte	W03
mus_gymleader_johto_8_B1:
@ 010   ----------------------------------------
mus_gymleader_johto_8_010:
	.byte		N11   , Bn0 , v120
	.byte		N23   , An2 , v127
	.byte	W24
	.byte		N11   , Bn0 , v120
	.byte	W24
	.byte		N11   
	.byte	W24
	.byte		N11   
	.byte	W24
	.byte	PEND
@ 011   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 012   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 013   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 014   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 015   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 016   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 017   ----------------------------------------
mus_gymleader_johto_8_017:
	.byte		N11   , Bn0 , v120
	.byte	W24
	.byte		N11   
	.byte	W24
	.byte		N11   
	.byte	W24
	.byte		N11   
	.byte	W12
	.byte		N11   
	.byte	W12
	.byte	PEND
@ 018   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 019   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 020   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 021   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 022   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 023   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 024   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 025   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 026   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 027   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 028   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 029   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 030   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 031   ----------------------------------------
	.byte		N11   , Bn0 , v120
	.byte	W12
	.byte		N11   
	.byte	W12
	.byte		N11   
	.byte	W12
	.byte		N11   
	.byte	W12
	.byte		N05   
	.byte		N05   , Dn1 , v088
	.byte	W06
	.byte		        Bn0 , v108
	.byte		N05   , Dn1 , v088
	.byte	W06
	.byte		        Bn0 , v116
	.byte		N05   , Dn1 , v092
	.byte	W06
	.byte		        Bn0 , v108
	.byte		N05   , Dn1 , v092
	.byte	W06
	.byte		        Bn0 , v120
	.byte		N05   , Dn1 , v096
	.byte	W06
	.byte		        Bn0 , v108
	.byte		N05   , Dn1 , v096
	.byte	W06
	.byte		        Bn0 , v116
	.byte		N05   , Dn1 , v100
	.byte	W06
	.byte		        Bn0 , v108
	.byte		N05   , Dn1 , v100
	.byte	W06
@ 032   ----------------------------------------
	.byte		N11   , Bn0 , v120
	.byte		N23   , An2 , v127
	.byte	W96
@ 033   ----------------------------------------
mus_gymleader_johto_8_033:
	.byte		N11   , Bn0 , v120
	.byte		N23   , An2 , v127
	.byte	W84
	.byte		N11   , Bn0 , v100
	.byte	W12
	.byte	PEND
@ 034   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_033
@ 035   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_033
@ 036   ----------------------------------------
mus_gymleader_johto_8_036:
	.byte		N11   , Bn0 , v120
	.byte		N23   , An2 , v127
	.byte	W36
	.byte		N11   , Bn0 , v116
	.byte	W36
	.byte		        Bn0 , v120
	.byte	W24
	.byte	PEND
@ 037   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_036
@ 038   ----------------------------------------
	.byte		N11   , Bn0 , v120
	.byte		N05   , Dn1 , v056
	.byte		N23   , An2 , v127
	.byte	W06
	.byte		N05   , Dn1 , v056
	.byte	W06
	.byte		        Dn1 , v060
	.byte	W06
	.byte		        Dn1 , v064
	.byte	W06
	.byte		        Dn1 , v068
	.byte	W06
	.byte		N05   
	.byte	W06
	.byte		N11   , Bn0 , v116
	.byte		N05   , Dn1 , v072
	.byte	W06
	.byte		        Dn1 , v076
	.byte	W06
	.byte		        Dn1 , v080
	.byte	W06
	.byte		N05   
	.byte	W06
	.byte		        Dn1 , v084
	.byte	W06
	.byte		        Dn1 , v088
	.byte	W06
	.byte		N11   , Bn0 , v120
	.byte		N05   , Dn1 , v088
	.byte	W06
	.byte		        Dn1 , v092
	.byte	W06
	.byte		        Dn1 , v096
	.byte	W06
	.byte		N05   
	.byte	W06
@ 039   ----------------------------------------
	.byte		N11   , Bn0 , v120
	.byte		N05   , Dn1 , v096
	.byte		N23   , An2 , v127
	.byte	W06
	.byte		N05   , Dn1 , v100
	.byte	W06
	.byte		N05   
	.byte	W06
	.byte		N05   
	.byte	W06
	.byte		N11   , Bn0 , v120
	.byte		N05   , Dn1 , v100
	.byte	W06
	.byte		        Dn1 , v104
	.byte	W06
	.byte		N05   
	.byte	W06
	.byte		N05   
	.byte	W06
	.byte		N11   , Bn0 , v120
	.byte		N02   , Dn1 , v104
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		        Dn1 , v108
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		N11   , Bn0 , v120
	.byte		N02   , Dn1 , v108
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		N05   , Bn0 , v120
	.byte		N02   , Dn1 , v108
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		N05   , Bn0 , v112
	.byte		N02   , Dn1 
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		N05   , Bn0 , v116
	.byte		N02   , Dn1 , v112
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		N05   , Bn0 
	.byte		N02   , Dn1 
	.byte	W03
	.byte		N02   
	.byte	W03
@ 040   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_010
@ 041   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 042   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 043   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 044   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 045   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 046   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 047   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_017
@ 048   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 049   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 050   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 051   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 052   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 053   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 054   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 055   ----------------------------------------
	.byte	PATT
	 .word	mus_gymleader_johto_8_003
@ 056   ----------------------------------------
	.byte		N11   , Bn0 , v120
	.byte		N02   , Dn1 , v080
	.byte	W06
	.byte		        Dn1 , v072
	.byte	W06
	.byte		        Dn1 , v080
	.byte	W06
	.byte		        Dn1 , v072
	.byte	W06
	.byte		N11   , Bn0 , v120
	.byte		N02   , Dn1 , v080
	.byte	W06
	.byte		        Dn1 , v072
	.byte	W06
	.byte		        Dn1 , v080
	.byte	W06
	.byte		        Dn1 , v072
	.byte	W06
	.byte		N11   , Bn0 , v120
	.byte		N02   , Dn1 , v080
	.byte	W03
	.byte		        Dn1 , v084
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		        Dn1 , v088
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		        Dn1 , v092
	.byte	W03
	.byte		N11   , Bn0 , v120
	.byte		N02   , Dn1 , v092
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		        Dn1 , v096
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		        Dn1 , v100
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte		N02   
	.byte	W03
	.byte	GOTO
	 .word	mus_gymleader_johto_8_B1
mus_gymleader_johto_8_B2:
@ 057   ----------------------------------------
	.byte	FINE

@******************************************************@
	.align	2

mus_gymleader_johto:
	.byte	7	@ NumTrks
	.byte	0	@ NumBlks
	.byte	mus_gymleader_johto_pri	@ Priority
	.byte	mus_gymleader_johto_rev	@ Reverb.

	.word	mus_gymleader_johto_grp

	.word	mus_gymleader_johto_1
	.word	mus_gymleader_johto_2
	.word	mus_gymleader_johto_3
	.word	mus_gymleader_johto_4
	.word	mus_gymleader_johto_5
	.word	mus_gymleader_johto_6
	.word	mus_gymleader_johto_7
	@.word	mus_gymleader_johto_8

	.end
