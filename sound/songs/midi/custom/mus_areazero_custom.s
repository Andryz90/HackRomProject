	.include "MPlayDef.s"

	.equ	mus_areazero_grp, voicegroup200
	.equ	mus_areazero_pri, 2
	.equ	mus_areazero_rev, 0
	.equ	mus_areazero_mvl, 100
	.equ	mus_areazero_key, 0
	.equ	mus_areazero_tbs, 1
	.equ	mus_areazero_exg, 1
	.equ	mus_areazero_cmp, 1

	.section .rodata
	.global	mus_areazero
	.align	2

@**************** Track 1 (Midi-Chn.1) ****************@

mus_areazero_1:
	.byte	KEYSH , mus_areazero_key+0
mus_areazero_1_B1:
@ 000   ----------------------------------------
@ 001   ----------------------------------------
@ 002   ----------------------------------------
@ 003   ----------------------------------------
@ 004   ----------------------------------------
@ 005   ----------------------------------------
@ 006   ----------------------------------------
@ 007   ----------------------------------------
@ 008   ----------------------------------------
@ 009   ----------------------------------------
	.byte	TEMPO , 115*mus_areazero_tbs/2
	.byte		VOICE , 24
	.byte		VOL   , 92*mus_areazero_mvl/mxv
	.byte		PAN   , c_v-16
	.byte		N12   , Fn3 , v092
	.byte	W12
	.byte		        Fs3 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs2 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs3 
	.byte	W12
	.byte		        Fn3 
	.byte	W12
	.byte		        Fs3 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs2 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs3 
	.byte	W12
@ 010   ----------------------------------------
	.byte		        Fn3 
	.byte	W12
	.byte		        Fs3 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs2 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs3 
	.byte	W12
	.byte		        Fn3 
	.byte	W12
	.byte		        Fs3 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs2 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs3 
	.byte	W12
@ 011   ----------------------------------------
	.byte		VOL   , 77*mus_areazero_mvl/mxv
	.byte		PAN   , c_v-16
	.byte		N12   , Fn4 
	.byte	W12
	.byte		        Fs4 
	.byte	W12
	.byte		        Cs4 
	.byte	W12
	.byte		        Ds4 
	.byte	W12
	.byte		        Gs3 
	.byte	W12
	.byte		        Cs4 
	.byte	W12
	.byte		        Ds4 
	.byte	W12
	.byte		        Gs4 
	.byte	W12
	.byte		        Fn4 
	.byte	W12
	.byte		        Fs4 
	.byte	W12
	.byte		        Cs4 
	.byte	W12
	.byte		        Ds4 
	.byte	W12
	.byte		        Gs3 
	.byte	W12
	.byte		        Cs4 
	.byte	W12
	.byte		        Ds4 
	.byte	W12
	.byte		        Gs4 
	.byte	W12
@ 012   ----------------------------------------
mus_areazero_1_012:
	.byte		N12   , Fn4 , v092
	.byte	W12
	.byte		        Fs4 
	.byte	W12
	.byte		        Cs4 
	.byte	W12
	.byte		        Ds4 
	.byte	W12
	.byte		        Gs3 
	.byte	W12
	.byte		        Cs4 
	.byte	W12
	.byte		        Ds4 
	.byte	W12
	.byte		        Gs4 
	.byte	W12
	.byte		        Fn4 
	.byte	W12
	.byte		        Fs4 
	.byte	W12
	.byte		        Cs4 
	.byte	W12
	.byte		        Ds4 
	.byte	W12
	.byte		        Gs3 
	.byte	W12
	.byte		        Cs4 
	.byte	W12
	.byte		        Ds4 
	.byte	W12
	.byte		        Gs4 
	.byte	W12
	.byte	PEND
@ 013   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_1_012
@ 014   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_1_012
@ 015   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_1_012
@ 016   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_1_012
@ 017   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_1_012
@ 018   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_1_012
@ 019   ----------------------------------------
	.byte		N06   , Fn4 , v092
	.byte	W12
	.byte		        Fs4 
	.byte	W12
	.byte		        Cs4 
	.byte	W12
	.byte		        Ds4 
	.byte	W12
	.byte		        Gs3 
	.byte	W12
	.byte		        Cs4 
	.byte	W12
	.byte		        Ds4 
	.byte	W12
	.byte		        Gs4 
	.byte	W12
	.byte		        Fn3 
	.byte		N06   , Fn4 
	.byte	W12
	.byte		        Fs3 
	.byte		N06   , Fs4 
	.byte	W12
	.byte		        Cs3 
	.byte		N06   , Cs4 
	.byte	W12
	.byte		        Ds3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Gs2 
	.byte		N06   , Gs3 
	.byte	W12
	.byte		        Cs3 
	.byte		N06   , Cs4 
	.byte	W12
	.byte		        Ds3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Gs3 
	.byte		N06   , Gs4 
	.byte	W12
@ 020   ----------------------------------------
mus_areazero_1_020:
	.byte		N06   , Fn3 , v092
	.byte		N06   , Fn4 
	.byte	W12
	.byte		        Fs3 
	.byte		N06   , Fs4 
	.byte	W12
	.byte		        Cs3 
	.byte		N06   , Cs4 
	.byte	W12
	.byte		        Ds3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Gs2 
	.byte		N06   , Gs3 
	.byte	W12
	.byte		        Cs3 
	.byte		N06   , Cs4 
	.byte	W12
	.byte		        Ds3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Gs3 
	.byte		N06   , Gs4 
	.byte	W12
	.byte		        Fn3 
	.byte		N06   , Fn4 
	.byte	W12
	.byte		        Fs3 
	.byte		N06   , Fs4 
	.byte	W12
	.byte		        Cs3 
	.byte		N06   , Cs4 
	.byte	W12
	.byte		        Ds3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Gs2 
	.byte		N06   , Gs3 
	.byte	W12
	.byte		        Cs3 
	.byte		N06   , Cs4 
	.byte	W12
	.byte		        Ds3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Gs3 
	.byte		N06   , Gs4 
	.byte	W12
	.byte	PEND
@ 021   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_1_020
@ 022   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_1_020
@ 023   ----------------------------------------
	.byte		N06   , Fn3 , v092
	.byte		N06   , Fn4 
	.byte	W12
	.byte		        Fs3 
	.byte		N06   , Fs4 
	.byte	W12
	.byte		        Cs3 
	.byte		N06   , Cs4 
	.byte	W12
	.byte		        Ds3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Gs2 
	.byte		N06   , Gs3 
	.byte	W12
	.byte		        Cs3 
	.byte		N06   , Cs4 
	.byte	W12
	.byte		        Ds3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Gs3 
	.byte		N06   , Gs4 
	.byte	W12
	.byte		        Gs3 
	.byte		N06   , Fn4 
	.byte	W12
	.byte		        As3 
	.byte		N06   , Fs4 
	.byte	W12
	.byte		        Fn3 
	.byte		N06   , Cs4 
	.byte	W12
	.byte		        Fs3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Ds3 
	.byte		N06   , Gs3 
	.byte	W12
	.byte		        As3 
	.byte		N06   , Cs4 
	.byte	W12
	.byte		        Gs3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Cs4 
	.byte		N06   , Gs4 
	.byte	W12
@ 024   ----------------------------------------
mus_areazero_1_024:
	.byte		N06   , Gs3 , v092
	.byte		N06   , Fn4 
	.byte	W12
	.byte		        As3 
	.byte		N06   , Fs4 
	.byte	W12
	.byte		        Fn3 
	.byte		N06   , Cs4 
	.byte	W12
	.byte		        Fs3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Ds3 
	.byte		N06   , Gs3 
	.byte	W12
	.byte		        As3 
	.byte		N06   , Cs4 
	.byte	W12
	.byte		        Gs3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Cs4 
	.byte		N06   , Gs4 
	.byte	W12
	.byte		        Gs3 
	.byte		N06   , Fn4 
	.byte	W12
	.byte		        As3 
	.byte		N06   , Fs4 
	.byte	W12
	.byte		        Fn3 
	.byte		N06   , Cs4 
	.byte	W12
	.byte		        Fs3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Ds3 
	.byte		N06   , Gs3 
	.byte	W12
	.byte		        As3 
	.byte		N06   , Cs4 
	.byte	W12
	.byte		        Gs3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Cs4 
	.byte		N06   , Gs4 
	.byte	W12
	.byte	PEND
@ 025   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_1_024
@ 026   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_1_024
@ 027   ----------------------------------------
	.byte		VOL   , 84*mus_areazero_mvl/mxv
	.byte		PAN   , c_v-31
	.byte		N06   , Fn3 , v064
	.byte		N06   , Fn4 
	.byte	W12
	.byte		        Fs3 
	.byte		N06   , Fs4 
	.byte	W12
	.byte		        Cs3 
	.byte		N06   , Cs4 
	.byte	W12
	.byte		        Ds3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Gs2 
	.byte		N06   , Gs3 
	.byte	W12
	.byte		        Cs3 
	.byte		N06   , Cs4 
	.byte	W12
	.byte		        Ds3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Gs3 
	.byte		N06   , Gs4 
	.byte	W24
	.byte		N12   , Fs3 , v092
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs2 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs3 
	.byte		N12   , Cs4 
	.byte	W12
@ 028   ----------------------------------------
mus_areazero_1_028:
	.byte		N12   , Ds3 , v092
	.byte	W12
	.byte		        Gs3 
	.byte		N12   , Cs4 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs3 
	.byte		N12   , Cs4 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs3 
	.byte		N12   , Cs4 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs3 
	.byte		N12   , Cs4 
	.byte	W24
	.byte		        Fs3 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs2 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs3 
	.byte		N12   , Cs4 
	.byte	W12
	.byte	PEND
@ 029   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_1_028
@ 030   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_1_028
@ 031   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_1_028
@ 032   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_1_028
@ 033   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_1_028
@ 034   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_1_028
@ 035   ----------------------------------------
	.byte		N12   , Ds3 , v092
	.byte	W12
	.byte		        Gs3 
	.byte		N12   , Cs4 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs3 
	.byte		N12   , Cs4 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs3 
	.byte		N12   , Cs4 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs3 
	.byte		N12   , Cs4 
	.byte	W24
	.byte		        Fs3 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs2 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs3 
	.byte	W12
@ 036   ----------------------------------------
mus_areazero_1_036:
	.byte	W12
	.byte		N12   , Fs3 , v092
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs2 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs3 
	.byte	W24
	.byte		        Fs3 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs2 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs3 
	.byte	W12
	.byte	PEND
@ 037   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_1_036
@ 038   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_1_036
@ 039   ----------------------------------------
	.byte	W12
	.byte		N12   , Fs3 , v092
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs2 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs3 
	.byte	W12
	.byte	GOTO
	 .word	mus_areazero_1_B1
mus_areazero_1_B2:
	.byte	W96
@ 040   ----------------------------------------
	.byte	FINE

@**************** Track 2 (Midi-Chn.2) ****************@

mus_areazero_2:
	.byte	KEYSH , mus_areazero_key+0
mus_areazero_2_B1:
@ 000   ----------------------------------------
@ 001   ----------------------------------------
@ 002   ----------------------------------------
@ 003   ----------------------------------------
@ 004   ----------------------------------------
@ 005   ----------------------------------------
@ 006   ----------------------------------------
@ 007   ----------------------------------------
@ 008   ----------------------------------------
	.byte		VOICE , 48
	.byte		VOL   , 92*mus_areazero_mvl/mxv
	.byte		PAN   , c_v+0
	.byte	W96
	.byte	W96
@ 009   ----------------------------------------
	.byte	W96
	.byte	W96
@ 010   ----------------------------------------
	.byte	W96
	.byte		TIE   , Ds0 , v092
	.byte		TIE   , Ds1 
	.byte		TIE   , Fn2 
	.byte	W96
@ 011   ----------------------------------------
mus_areazero_2_011:
	.byte	W02
	.byte	W04
	.byte	W05
	.byte	W04
	.byte	W05
	.byte	W04
	.byte	W04
	.byte	W04
	.byte	W04
	.byte	W04
	.byte	W04
	.byte	W04
	.byte	W04
	.byte	W04
	.byte	W03
	.byte	W04
	.byte	W04
	.byte	W03
	.byte	W14
	.byte	PEND
	.byte		EOT   , Ds0 
	.byte		        Ds1 
	.byte		        Fn2 
	.byte	W12
	.byte		N12   , Ds0 , v092
	.byte		N12   , Ds1 
	.byte		N12   , Fn2 
	.byte	W96
@ 012   ----------------------------------------
mus_areazero_2_012:
	.byte	W96
	.byte		TIE   , BnM1, v092
	.byte		TIE   , Bn0 
	.byte	W96
	.byte	PEND
@ 013   ----------------------------------------
	.byte	W96
	.byte	W96
@ 014   ----------------------------------------
	.byte	W03
	.byte	W06
	.byte	W06
	.byte	W05
	.byte	W06
	.byte	W06
	.byte	W05
	.byte	W06
	.byte	W05
	.byte	W06
	.byte	W05
	.byte	W05
	.byte	W05
	.byte	W05
	.byte	W05
	.byte	W05
	.byte	W05
	.byte	W05
	.byte	W02
	.byte		EOT   , BnM1
	.byte		        Bn0 
	.byte		TIE   , Ds0 
	.byte		TIE   , Ds1 
	.byte		TIE   , Fn2 
	.byte	W96
@ 015   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_2_011
	.byte		EOT   , Ds0 
	.byte		        Ds1 
	.byte		        Fn2 
	.byte	W12
	.byte		N12   , Ds0 , v092
	.byte		N12   , Ds1 
	.byte		N12   , Fn2 
	.byte	W96
@ 016   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_2_012
@ 017   ----------------------------------------
	.byte	W96
	.byte	W96
@ 018   ----------------------------------------
	.byte	W96
	.byte		EOT   , BnM1
	.byte		        Bn0 
	.byte		N48   , Ds0 , v092
	.byte	W48
	.byte		N48   
	.byte		N48   , Ds1 
	.byte	W48
@ 019   ----------------------------------------
mus_areazero_2_019:
	.byte	W12
	.byte		N12   , Ds0 , v092
	.byte	W24
	.byte		N12   
	.byte	W12
	.byte		N48   
	.byte		N48   , Ds1 
	.byte	W48
	.byte		N24   , Ds0 
	.byte	W36
	.byte		N12   
	.byte	W12
	.byte		N48   
	.byte		N48   , Ds1 
	.byte	W48
	.byte	PEND
@ 020   ----------------------------------------
mus_areazero_2_020:
	.byte	W12
	.byte		N12   , Ds0 , v092
	.byte	W24
	.byte		N12   
	.byte	W12
	.byte		N48   
	.byte		N48   , Ds1 
	.byte	W48
	.byte		        Bn0 
	.byte	W48
	.byte		N48   
	.byte		N48   , Bn1 
	.byte	W48
	.byte	PEND
@ 021   ----------------------------------------
mus_areazero_2_021:
	.byte	W12
	.byte		N12   , Bn0 , v092
	.byte	W24
	.byte		N12   
	.byte	W12
	.byte		N48   
	.byte		N48   , Bn1 
	.byte	W48
	.byte		N24   , Bn0 
	.byte	W36
	.byte		N12   
	.byte	W12
	.byte		N48   
	.byte		N48   , Bn1 
	.byte	W48
	.byte	PEND
@ 022   ----------------------------------------
	.byte	W12
	.byte		N12   , Bn0 
	.byte	W24
	.byte		N12   
	.byte	W12
	.byte		N48   
	.byte		N48   , Bn1 
	.byte	W48
	.byte		        Ds0 
	.byte	W48
	.byte		N48   
	.byte		N48   , Ds1 
	.byte	W48
@ 023   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_2_019
@ 024   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_2_020
@ 025   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_2_021
@ 026   ----------------------------------------
	.byte	W12
	.byte		N12   , Bn0 , v092
	.byte	W24
	.byte		N12   
	.byte	W12
	.byte		N48   
	.byte		N48   , Bn1 
	.byte	W48
	.byte		N72   , Ds0 
	.byte		N72   , Ds1 
	.byte	W72
	.byte		N24   , En0 
	.byte		N24   , En1 
	.byte	W24
@ 027   ----------------------------------------
mus_areazero_2_027:
	.byte		N84   , Ds0 , v092
	.byte		N84   , Ds1 
	.byte	W96
	.byte		N72   , Ds0 
	.byte		N72   , Ds1 
	.byte	W72
	.byte		N24   , En0 
	.byte		N24   , En1 
	.byte	W24
	.byte	PEND
@ 028   ----------------------------------------
mus_areazero_2_028:
	.byte		N48   , Ds0 , v092
	.byte		N48   , Ds1 
	.byte	W48
	.byte		N24   , Cs0 
	.byte		N24   , Cs1 
	.byte	W24
	.byte		        AnM1
	.byte		N24   , An0 
	.byte	W24
	.byte		N72   , Ds0 
	.byte		N72   , Ds1 
	.byte	W72
	.byte		N24   , En0 
	.byte		N24   , En1 
	.byte	W24
	.byte	PEND
@ 029   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_2_027
@ 030   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_2_028
@ 031   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_2_027
@ 032   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_2_028
@ 033   ----------------------------------------
	.byte		N84   , Ds0 , v092
	.byte		N84   , Ds1 
	.byte	W96
	.byte		N72   , Ds0 
	.byte		N72   , Ds1 
	.byte	W84
	.byte		N12   , BnM1
	.byte		N12   , Bn0 
	.byte	W12
@ 034   ----------------------------------------
	.byte		N48   , BnM1
	.byte		N48   , Bn0 
	.byte	W48
	.byte		        Cs0 
	.byte		N48   , Cs1 
	.byte	W48
	.byte		N72   , Ds0 
	.byte		N72   , Ds1 
	.byte	W72
	.byte		N12   , En0 
	.byte		N12   , Fs1 
	.byte	W12
	.byte		        En0 
	.byte		N12   , Gs1 
	.byte	W12
@ 035   ----------------------------------------
	.byte		N84   , Ds0 
	.byte		N84   , Ds1 
	.byte	W84
	.byte		N06   , Gs1 
	.byte	W06
	.byte		        As1 
	.byte	W06
	.byte		        Cs1 
	.byte	W06
	.byte		N66   , Ds0 
	.byte		N66   , Ds1 
	.byte	W78
	.byte		N12   , BnM1
	.byte		N12   , Bn0 
	.byte	W12
@ 036   ----------------------------------------
	.byte		N18   , Ds0 
	.byte		N06   , Gs1 
	.byte	W06
	.byte		        As1 
	.byte	W06
	.byte		        En1 
	.byte	W06
	.byte		N30   , Ds0 
	.byte		N30   , Ds1 
	.byte	W30
	.byte		N24   , Cs0 
	.byte		N24   , Cs1 
	.byte	W24
	.byte		        AnM1
	.byte		N24   , An0 
	.byte	W24
	.byte		N72   , Ds0 
	.byte		N72   , Ds1 
	.byte	W72
	.byte		N24   , En0 
	.byte		N06   , Gs1 
	.byte	W06
	.byte		        As1 
	.byte	W06
	.byte		        En1 
	.byte	W12
@ 037   ----------------------------------------
	.byte		N84   , Ds0 
	.byte		N84   , Ds1 
	.byte	W84
	.byte		N06   , Gs1 
	.byte	W06
	.byte		        As1 
	.byte	W06
	.byte		        Cs1 
	.byte	W06
	.byte		N66   , Ds0 
	.byte		N66   , Ds1 
	.byte	W78
	.byte		N60   , BnM1
	.byte		N60   , Bn0 
	.byte	W12
@ 038   ----------------------------------------
	.byte	W48
	.byte		N48   , Cs0 
	.byte		N48   , Cs1 
	.byte	W48
	.byte	GOTO
	 .word	mus_areazero_2_B1
mus_areazero_2_B2:
	.byte	W96
@ 039   ----------------------------------------
	.byte	FINE

@**************** Track 3 (Midi-Chn.3) ****************@

mus_areazero_3:
	.byte	KEYSH , mus_areazero_key+0
mus_areazero_3_B1:
@ 000   ----------------------------------------
@ 001   ----------------------------------------
@ 002   ----------------------------------------
@ 003   ----------------------------------------
@ 004   ----------------------------------------
@ 005   ----------------------------------------
@ 006   ----------------------------------------
@ 007   ----------------------------------------
@ 008   ----------------------------------------
	.byte		VOICE , 48
	.byte		VOL   , 100*mus_areazero_mvl/mxv
	.byte		PAN   , c_v+0
	.byte	W96
	.byte	W96
@ 009   ----------------------------------------
	.byte	W96
	.byte	W96
@ 010   ----------------------------------------
	.byte	W96
	.byte	W96
@ 011   ----------------------------------------
	.byte		N84   , Ds3 , v092
	.byte		N84   , As3 
	.byte		N84   , Ds4 
	.byte	W02
	.byte	W04
	.byte	W05
	.byte	W04
	.byte	W05
	.byte	W04
	.byte	W04
	.byte	W04
	.byte	W04
	.byte	W04
	.byte	W04
	.byte	W04
	.byte	W04
	.byte	W04
	.byte	W03
	.byte	W04
	.byte	W04
	.byte	W03
	.byte	W24
	.byte	W02
	.byte		N12   , Ds3 
	.byte		N12   , As3 
	.byte		N12   , Ds4 
	.byte	W96
@ 012   ----------------------------------------
mus_areazero_3_012:
	.byte	W96
	.byte		TIE   , Fs3 , v092
	.byte		TIE   , As3 
	.byte	W96
	.byte	PEND
@ 013   ----------------------------------------
	.byte	W96
	.byte		EOT   , Fs3 
	.byte		        As3 
	.byte		N96   
	.byte		N96   , Cs4 
	.byte	W96
@ 014   ----------------------------------------
	.byte		N48   , Fs3 
	.byte		N48   , Ds4 
	.byte	W48
	.byte		        Ds3 
	.byte		N48   , As3 
	.byte	W48
	.byte		TIE   , Ds3 
	.byte		TIE   , Fs3 
	.byte	W96
@ 015   ----------------------------------------
	.byte	W02
	.byte	W06
	.byte	W05
	.byte	W05
	.byte	W05
	.byte	W05
	.byte	W05
	.byte	W05
	.byte	W04
	.byte	W05
	.byte	W05
	.byte	W04
	.byte	W05
	.byte	W04
	.byte	W04
	.byte	W05
	.byte	W04
	.byte	W04
	.byte	W02
	.byte		EOT   , Ds3 
	.byte		        Fs3 
	.byte	W12
	.byte		N12   , Ds3 
	.byte		N12   , Fs3 
	.byte	W96
@ 016   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_3_012
@ 017   ----------------------------------------
	.byte	W96
	.byte		EOT   , Fs3 
	.byte		        As3 
	.byte		N96   , As3 , v092
	.byte		N96   , Cs4 
	.byte	W96
@ 018   ----------------------------------------
	.byte		VOL   , 100*mus_areazero_mvl/mxv
	.byte		PAN   , c_v+0
	.byte		N48   , As3 , v064
	.byte		N48   , Ds4 
	.byte	W48
	.byte		        Cs4 
	.byte		N48   , Fs4 
	.byte	W48
	.byte		N12   , Cn4 
	.byte		N12   , Fn4 
	.byte	W96
@ 019   ----------------------------------------
	.byte	W96
	.byte	W96
@ 020   ----------------------------------------
	.byte	W96
	.byte	W96
@ 021   ----------------------------------------
	.byte	W96
	.byte	W96
@ 022   ----------------------------------------
	.byte	W96
	.byte	W96
@ 023   ----------------------------------------
	.byte	W96
	.byte	W96
@ 024   ----------------------------------------
	.byte	W96
	.byte	W96
@ 025   ----------------------------------------
	.byte	W96
	.byte	W96
@ 026   ----------------------------------------
	.byte	W96
	.byte	W96
@ 027   ----------------------------------------
	.byte	W96
	.byte	W96
@ 028   ----------------------------------------
	.byte	W06
	.byte	W96
	.byte	W60
	.byte	W06
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W18
@ 029   ----------------------------------------
	.byte	W96
	.byte	W96
@ 030   ----------------------------------------
	.byte	W96
	.byte	W96
@ 031   ----------------------------------------
	.byte	W96
	.byte	W96
@ 032   ----------------------------------------
	.byte	W96
	.byte	W96
@ 033   ----------------------------------------
	.byte	W96
	.byte	W96
@ 034   ----------------------------------------
	.byte	W96
	.byte	W96
@ 035   ----------------------------------------
	.byte	W96
	.byte	W96
@ 036   ----------------------------------------
	.byte	W96
	.byte	W96
@ 037   ----------------------------------------
	.byte	W96
	.byte	W96
@ 038   ----------------------------------------
	.byte	W96
	.byte	GOTO
	 .word	mus_areazero_3_B1
mus_areazero_3_B2:
	.byte	W96
@ 039   ----------------------------------------
	.byte	FINE

@**************** Track 4 (Midi-Chn.4) ****************@

mus_areazero_4:
	.byte	KEYSH , mus_areazero_key+0
mus_areazero_4_B1:
@ 000   ----------------------------------------
@ 001   ----------------------------------------
@ 002   ----------------------------------------
@ 003   ----------------------------------------
@ 004   ----------------------------------------
@ 005   ----------------------------------------
@ 006   ----------------------------------------
@ 007   ----------------------------------------
@ 008   ----------------------------------------
	.byte		VOICE , 73
	.byte		VOL   , 100*mus_areazero_mvl/mxv
	.byte		PAN   , c_v+0
	.byte	W96
	.byte	W96
@ 009   ----------------------------------------
	.byte	W96
	.byte	W96
@ 010   ----------------------------------------
	.byte	W96
	.byte	W96
@ 011   ----------------------------------------
	.byte	W96
	.byte	W96
@ 012   ----------------------------------------
	.byte	W96
	.byte	W96
@ 013   ----------------------------------------
	.byte	W96
	.byte	W96
@ 014   ----------------------------------------
	.byte	W96
	.byte	W96
@ 015   ----------------------------------------
	.byte	W96
	.byte	W96
@ 016   ----------------------------------------
	.byte	W96
	.byte	W96
@ 017   ----------------------------------------
	.byte	W96
	.byte	W96
@ 018   ----------------------------------------
	.byte	W96
	.byte	W48
	.byte		N24   , Fs2 , v092
	.byte	W24
	.byte		        Gs2 
	.byte	W24
@ 019   ----------------------------------------
	.byte		N72   , Cs3 
	.byte		N72   , Fn3 
	.byte	W72
	.byte		N24   , Ds3 
	.byte		N24   , Fs3 
	.byte	W24
	.byte		N96   , Cs3 
	.byte		N96   , Fn3 
	.byte	W96
@ 020   ----------------------------------------
	.byte		N24   , Ds3 
	.byte	W24
	.byte		        Fn3 
	.byte	W24
	.byte		        Gs2 
	.byte	W24
	.byte		N18   , Cs3 
	.byte	W18
	.byte		N03   , Cn3 
	.byte	W03
	.byte		        Bn2 
	.byte	W03
	.byte		TIE   , Fs2 
	.byte		TIE   , As2 
	.byte	W96
@ 021   ----------------------------------------
	.byte	W24
	.byte		EOT   , Fs2 
	.byte		        As2 
	.byte		N24   , Gs2 
	.byte	W24
	.byte		        As2 
	.byte	W24
	.byte		        Cs3 
	.byte	W24
	.byte		N96   , Fs2 
	.byte		N96   , As2 
	.byte	W96
@ 022   ----------------------------------------
	.byte		N24   , Gs2 
	.byte	W24
	.byte		        As2 
	.byte	W24
	.byte		        Fs2 
	.byte	W24
	.byte		        Gs2 
	.byte	W24
	.byte		N48   , Fn2 
	.byte	W48
	.byte		N24   , Fs2 
	.byte	W24
	.byte		        Gs2 
	.byte	W24
@ 023   ----------------------------------------
	.byte		N72   , As2 
	.byte		N72   , Cs3 
	.byte		N72   , Fn3 
	.byte	W72
	.byte		N24   , As2 
	.byte		N24   , Ds3 
	.byte		N24   , Fs3 
	.byte	W24
	.byte		N96   , As2 
	.byte		N96   , Cs3 
	.byte		N96   , Fn3 
	.byte	W96
@ 024   ----------------------------------------
	.byte		        As2 
	.byte		N96   , Cs3 
	.byte		N24   , Fn3 
	.byte	W24
	.byte		        Fs3 
	.byte	W24
	.byte		        Cs4 
	.byte	W24
	.byte		        Fn3 
	.byte		N24   , Bn3 
	.byte	W24
	.byte		TIE   , Cs3 
	.byte		TIE   , Fs3 
	.byte		TIE   , As3 
	.byte	W96
@ 025   ----------------------------------------
	.byte	W24
	.byte		EOT   , Cs3 
	.byte		        Fs3 
	.byte		        As3 
	.byte		N24   , Fs3 
	.byte	W24
	.byte		        Cs4 
	.byte	W24
	.byte		        Fn3 
	.byte		N24   , Bn3 
	.byte	W24
	.byte		N96   , Fs3 
	.byte		N96   , As3 
	.byte	W96
@ 026   ----------------------------------------
	.byte		        Ds3 
	.byte		N24   , Gs3 
	.byte	W24
	.byte		        As3 
	.byte	W24
	.byte		        Fs3 
	.byte	W24
	.byte		        Gs3 
	.byte	W96
	.byte	W24
@ 027   ----------------------------------------
	.byte	W96
	.byte	W96
@ 028   ----------------------------------------
	.byte	W96
	.byte	W96
@ 029   ----------------------------------------
	.byte	W96
	.byte	W96
@ 030   ----------------------------------------
	.byte		VOICE , 81
	.byte		VOL   , 92*mus_areazero_mvl/mxv
	.byte		PAN   , c_v+0
	.byte	W96
	.byte	W96
@ 031   ----------------------------------------
	.byte	W96
	.byte	W96
@ 032   ----------------------------------------
	.byte	W96
	.byte	W96
@ 033   ----------------------------------------
	.byte	W96
	.byte	W96
@ 034   ----------------------------------------
	.byte	W96
	.byte	W96
@ 035   ----------------------------------------
	.byte	W96
	.byte	W96
@ 036   ----------------------------------------
	.byte	W96
	.byte	W96
@ 037   ----------------------------------------
	.byte	W96
	.byte	W96
@ 038   ----------------------------------------
	.byte	W96
	.byte	GOTO
	 .word	mus_areazero_4_B1
mus_areazero_4_B2:
	.byte	W96
@ 039   ----------------------------------------
	.byte	FINE

@**************** Track 5 (Midi-Chn.5) ****************@

mus_areazero_5:
	.byte	KEYSH , mus_areazero_key+0
mus_areazero_5_B1:
@ 000   ----------------------------------------
@ 001   ----------------------------------------
@ 002   ----------------------------------------
@ 003   ----------------------------------------
@ 004   ----------------------------------------
@ 005   ----------------------------------------
@ 006   ----------------------------------------
@ 007   ----------------------------------------
@ 008   ----------------------------------------
	.byte		VOICE , 24
	.byte		VOL   , 84*mus_areazero_mvl/mxv
	.byte		PAN   , c_v+32
	.byte	W96
	.byte	W96
@ 009   ----------------------------------------
	.byte	W96
	.byte	W96
@ 010   ----------------------------------------
	.byte	W96
	.byte	W96
@ 011   ----------------------------------------
	.byte	W96
	.byte	W96
@ 012   ----------------------------------------
	.byte	W96
	.byte	W96
@ 013   ----------------------------------------
	.byte	W96
	.byte	W96
@ 014   ----------------------------------------
	.byte	W96
	.byte	W96
@ 015   ----------------------------------------
	.byte	W96
	.byte	W96
@ 016   ----------------------------------------
	.byte	W96
	.byte	W96
@ 017   ----------------------------------------
	.byte	W96
	.byte	W96
@ 018   ----------------------------------------
	.byte		VOL   , 71*mus_areazero_mvl/mxv
	.byte		PAN   , c_v+16
	.byte	W96
	.byte		N06   , Fn3 , v092
	.byte	W12
	.byte		        Fs3 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs2 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Cs3 
	.byte		N06   , Gs3 
	.byte	W12
@ 019   ----------------------------------------
mus_areazero_5_019:
	.byte		N06   , Ds3 , v092
	.byte	W12
	.byte		        Cs3 
	.byte		N06   , Gs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Cs3 
	.byte		N06   , Gs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Cs3 
	.byte		N06   , Gs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Cs3 
	.byte		N06   , Gs3 
	.byte	W12
	.byte		        Fn3 
	.byte	W12
	.byte		        Fs3 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Gs2 
	.byte	W12
	.byte		        Cs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Cs3 
	.byte		N06   , Gs3 
	.byte	W12
	.byte	PEND
@ 020   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_5_019
@ 021   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_5_019
@ 022   ----------------------------------------
	.byte		VOL   , 84*mus_areazero_mvl/mxv
	.byte		PAN   , c_v+32
	.byte		N06   , Ds3 , v064
	.byte	W12
	.byte		        Cs3 
	.byte		N06   , Gs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Cs3 
	.byte		N06   , Gs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Cs3 
	.byte		N06   , Gs3 
	.byte	W12
	.byte		        Ds3 
	.byte	W12
	.byte		        Cs3 
	.byte		N06   , Gs3 
	.byte	W96
	.byte	W12
@ 023   ----------------------------------------
	.byte	W96
	.byte	W96
@ 024   ----------------------------------------
	.byte	W96
	.byte	W96
@ 025   ----------------------------------------
	.byte	W96
	.byte	W96
@ 026   ----------------------------------------
	.byte	W96
	.byte	W06
	.byte	W90
@ 027   ----------------------------------------
mus_areazero_5_027:
	.byte	W96
	.byte	W96
	.byte	PEND
@ 028   ----------------------------------------
	.byte	W96
	.byte	W96
@ 029   ----------------------------------------
	.byte		VOL   , 92*mus_areazero_mvl/mxv
	.byte		PAN   , c_v-63
	.byte	W96
	.byte	W24
	.byte		N08   , Fs4 , v092
	.byte	W08
	.byte		N08   
	.byte	W08
	.byte		N08   
	.byte	W08
	.byte		N08   
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte		N08   
	.byte	W08
	.byte		N08   
	.byte	W08
	.byte		N08   
	.byte	W08
	.byte		N08   
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte		N08   
	.byte	W08
@ 030   ----------------------------------------
	.byte		N08   
	.byte	W08
	.byte		N08   
	.byte	W08
	.byte		N08   
	.byte	W96
	.byte	W80
@ 031   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_5_027
@ 032   ----------------------------------------
	.byte	W96
	.byte	W96
@ 033   ----------------------------------------
	.byte		VOL   , 77*mus_areazero_mvl/mxv
	.byte		PAN   , c_v-31
	.byte	W48
	.byte		N06   , Cs4 , v092
	.byte	W06
	.byte		        Fs4 
	.byte	W12
	.byte		        As4 
	.byte	W12
	.byte		        Ds4 
	.byte	W06
	.byte		        Fs4 
	.byte	W96
	.byte	W12
@ 034   ----------------------------------------
	.byte	W96
	.byte	W96
@ 035   ----------------------------------------
	.byte	W96
	.byte	W96
@ 036   ----------------------------------------
	.byte	W96
	.byte	W96
@ 037   ----------------------------------------
	.byte	W96
	.byte	W96
@ 038   ----------------------------------------
	.byte		VOL   , 71*mus_areazero_mvl/mxv
	.byte		PAN   , c_v+16
	.byte	W96
	.byte	GOTO
	 .word	mus_areazero_5_B1
mus_areazero_5_B2:
	.byte	W96
@ 039   ----------------------------------------
	.byte	FINE

@**************** Track 6 (Midi-Chn.6) ****************@

mus_areazero_6:
	.byte	KEYSH , mus_areazero_key+0
mus_areazero_6_B1:
@ 000   ----------------------------------------
@ 001   ----------------------------------------
@ 002   ----------------------------------------
@ 003   ----------------------------------------
@ 004   ----------------------------------------
@ 005   ----------------------------------------
@ 006   ----------------------------------------
@ 007   ----------------------------------------
@ 008   ----------------------------------------
	.byte		VOICE , 24
	.byte		VOL   , 100*mus_areazero_mvl/mxv
	.byte		PAN   , c_v+0
	.byte	W96
	.byte	W96
@ 009   ----------------------------------------
	.byte	W96
	.byte	W96
@ 010   ----------------------------------------
	.byte	W96
	.byte	W96
@ 011   ----------------------------------------
	.byte	W96
	.byte	W96
@ 012   ----------------------------------------
	.byte	W96
	.byte	W96
@ 013   ----------------------------------------
	.byte	W96
	.byte	W96
@ 014   ----------------------------------------
	.byte	W96
	.byte	W96
@ 015   ----------------------------------------
	.byte	W96
	.byte	W96
@ 016   ----------------------------------------
	.byte	W96
	.byte	W96
@ 017   ----------------------------------------
	.byte	W96
	.byte	W96
@ 018   ----------------------------------------
	.byte	W96
	.byte	W96
@ 019   ----------------------------------------
	.byte	W96
	.byte	W96
@ 020   ----------------------------------------
	.byte	W96
	.byte	W96
@ 021   ----------------------------------------
	.byte	W96
	.byte	W96
@ 022   ----------------------------------------
	.byte		VOL   , 77*mus_areazero_mvl/mxv
	.byte		PAN   , c_v+32
	.byte	W24
	.byte	W48
	.byte	W96
	.byte	W24
@ 023   ----------------------------------------
	.byte	W96
	.byte	W96
@ 024   ----------------------------------------
	.byte	W96
	.byte	W96
@ 025   ----------------------------------------
	.byte	W96
	.byte	W96
@ 026   ----------------------------------------
	.byte	W96
	.byte	W96
@ 027   ----------------------------------------
	.byte	W96
	.byte	W96
@ 028   ----------------------------------------
	.byte	W96
	.byte	W96
@ 029   ----------------------------------------
	.byte		VOL   , 92*mus_areazero_mvl/mxv
	.byte		PAN   , c_v+63
	.byte	W96
	.byte	W24
	.byte		N08   , Fs4 , v092
	.byte	W08
	.byte		N08   
	.byte	W08
	.byte		N08   
	.byte	W08
	.byte		N08   
	.byte	W08
	.byte		N08   
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte		N08   
	.byte	W08
	.byte		N08   
	.byte	W08
	.byte		N08   
	.byte	W08
	.byte		N08   
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
@ 030   ----------------------------------------
	.byte		N08   
	.byte	W08
	.byte		N08   
	.byte	W08
	.byte		N08   
	.byte	W96
	.byte	W80
@ 031   ----------------------------------------
	.byte	W96
	.byte	W96
@ 032   ----------------------------------------
	.byte		VOL   , 77*mus_areazero_mvl/mxv
	.byte		PAN   , c_v+32
	.byte	W96
	.byte	W42
	.byte		N06   , Cs4 
	.byte	W12
	.byte		        Fs4 
	.byte	W12
	.byte		        Ds4 
	.byte	W06
	.byte		        Fs4 
	.byte	W24
@ 033   ----------------------------------------
	.byte	W96
	.byte	W72
	.byte		        Cs4 
	.byte	W12
	.byte		        Fs4 
	.byte	W12
@ 034   ----------------------------------------
	.byte		        Ds4 
	.byte	W06
	.byte		        Fs4 
	.byte	W96
	.byte	W90
@ 035   ----------------------------------------
	.byte	W96
	.byte	W96
@ 036   ----------------------------------------
	.byte	W96
	.byte	W96
@ 037   ----------------------------------------
	.byte	W96
	.byte	W96
@ 038   ----------------------------------------
	.byte		PAN   , c_v-16
	.byte		VOL   , 92*mus_areazero_mvl/mxv
	.byte	W96
	.byte	GOTO
	 .word	mus_areazero_6_B1
mus_areazero_6_B2:
	.byte	W96
@ 039   ----------------------------------------
	.byte	FINE

@**************** Track 7 (Midi-Chn.7) ****************@

mus_areazero_7:
	.byte		VOL   , 115*mus_areazero_mvl/mxv
	.byte	KEYSH , mus_areazero_key+0
mus_areazero_7_B1:
@ 000   ----------------------------------------
@ 001   ----------------------------------------
@ 002   ----------------------------------------
@ 003   ----------------------------------------
@ 004   ----------------------------------------
@ 005   ----------------------------------------
@ 006   ----------------------------------------
@ 007   ----------------------------------------
@ 008   ----------------------------------------
	.byte		VOICE , 60 @french horn
	.byte	W96
	.byte	W96
@ 009   ----------------------------------------
	.byte	W96
	.byte	W96
@ 010   ----------------------------------------
	.byte	W96
	.byte	W96
@ 011   ----------------------------------------
	.byte	W96
	.byte	W96
@ 012   ----------------------------------------
	.byte	W96
	.byte	W96
@ 013   ----------------------------------------
	.byte	W96
	.byte	W96
@ 014   ----------------------------------------
	.byte	W96
	.byte	W96
@ 015   ----------------------------------------
	.byte	W96
	.byte	W96
@ 016   ----------------------------------------
	.byte	W96
	.byte	W96
@ 017   ----------------------------------------
	.byte	W96
	.byte	W96
@ 018   ----------------------------------------
	.byte	W96
	.byte	W48
	.byte		N24   , Fs3 , v092
	.byte	W24
	.byte		        Gs3 
	.byte	W24
@ 019   ----------------------------------------
	.byte		N72   , Cs4 
	.byte		N72   , Fn4 
	.byte	W72
	.byte		N24   , Ds4 
	.byte		N24   , Fs4 
	.byte	W24
	.byte		N96   , Cs4 
	.byte		N96   , Fn4 
	.byte	W96
@ 020   ----------------------------------------
	.byte		N24   , Ds4 
	.byte	W24
	.byte		        Fn4 
	.byte	W24
	.byte		        Gs3 
	.byte	W24
	.byte		N18   , Cs4 
	.byte	W18
	.byte		N03   , Cn4 
	.byte	W03
	.byte		        Bn3 
	.byte	W03
	.byte		TIE   , Fs3 
	.byte		TIE   , As3 
	.byte	W96
@ 021   ----------------------------------------
	.byte	W24
	.byte		EOT   , Fs3 
	.byte		        As3 
	.byte		N24   , Gs3 
	.byte	W24
	.byte		        As3 
	.byte	W24
	.byte		        Cs4 
	.byte	W24
	.byte		N96   , Fs3 
	.byte		N96   , As3 
	.byte	W96
@ 022   ----------------------------------------
	.byte		N24   , Gs3 
	.byte	W24
	.byte		        As3 
	.byte	W24
	.byte		        Fs3 
	.byte	W24
	.byte		        Gs3 
	.byte	W24
	.byte		N48   , Fn3 
	.byte	W48
	.byte		N24   , Fs3 
	.byte	W24
	.byte		        Gs3 
	.byte	W24
@ 023   ----------------------------------------
	.byte		N72   , As3 
	.byte		N72   , Cs4 
	.byte		N72   , Fn4 
	.byte	W72
	.byte		N24   , As3 
	.byte		N24   , Ds4 
	.byte		N24   , Fs4 
	.byte	W24
	.byte		N96   , As3 
	.byte		N96   , Cs4 
	.byte		N96   , Fn4 
	.byte	W96
@ 024   ----------------------------------------
	.byte		        As3 
	.byte		N96   , Cs4 
	.byte		N24   , Fn4 
	.byte	W24
	.byte		        Fs4 
	.byte	W24
	.byte		        Cs5 
	.byte	W24
	.byte		        Fn4 
	.byte		N24   , Bn4 
	.byte	W24
	.byte		TIE   , Cs4 
	.byte		TIE   , Fs4 
	.byte		TIE   , As4 
	.byte	W96
@ 025   ----------------------------------------
	.byte	W24
	.byte		EOT   , Cs4 
	.byte		        Fs4 
	.byte		        As4 
	.byte		N24   , Fs4 
	.byte	W24
	.byte		        Cs5 
	.byte	W24
	.byte		        Fn4 
	.byte		N24   , Bn4 
	.byte	W24
	.byte		N96   , Fs4 
	.byte		N96   , As4 
	.byte	W96
@ 026   ----------------------------------------
	.byte		N24   , Ds4 
	.byte		N24   , Gs4 
	.byte	W24
	.byte		        Ds4 
	.byte		N24   , As4 
	.byte	W24
	.byte		        Ds4 
	.byte		N24   , Fs4 
	.byte	W24
	.byte		        Ds4 
	.byte		N24   , Gs4 
	.byte	W24
	.byte		N72   , Fs3 
	.byte		N72   , As3 
	.byte		N72   , Cs4 
	.byte		N72   , Fn4 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W66
	.byte		N24   , Gn3 
	.byte		N24   , Bn3 
	.byte		N24   , Dn4 
	.byte		N24   , Fs4 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W18
@ 027   ----------------------------------------
mus_areazero_7_027:
	.byte		N84   , Fs3 , v092
	.byte		N84   , As3 
	.byte		N84   , Cs4 
	.byte		N84   , Fn4 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W90
	.byte		N72   , Fs3 
	.byte		N72   , As3 
	.byte		N72   , Cs4 
	.byte		N72   , Fn4 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W66
	.byte		N24   , Gn3 
	.byte		N24   , Bn3 
	.byte		N24   , Dn4 
	.byte		N24   , Fs4 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W18
	.byte	PEND
@ 028   ----------------------------------------
mus_areazero_7_028:
	.byte		N48   , Fs3 , v092
	.byte		N48   , As3 
	.byte		N48   , Cs4 
	.byte		N48   , Fn4 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W42
	.byte		N24   , En3 
	.byte		N24   , Gs3 
	.byte		N24   , Bn3 
	.byte		N24   , Ds4 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W18
	.byte		        Cn3 
	.byte		N24   , En3 
	.byte		N24   , Gn3 
	.byte		N24   , Bn3 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W18
	.byte		N72   , Fs3 
	.byte		N72   , As3 
	.byte		N72   , Cs4 
	.byte		N72   , Fn4 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W66
	.byte		N24   , Gn3 
	.byte		N24   , Bn3 
	.byte		N24   , Dn4 
	.byte		N24   , Fs4 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W18
	.byte	PEND
@ 029   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_7_027
@ 030   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_7_028
@ 031   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_7_027
@ 032   ----------------------------------------
	.byte		N48   , Fs3 , v092
	.byte		N48   , As3 
	.byte		N48   , Cs4 
	.byte		N48   , Fn4 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W42
	.byte		N24   , En3 
	.byte		N24   , Gs3 
	.byte		N24   , Bn3 
	.byte		N24   , Ds4 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W18
	.byte		        Cn3 
	.byte		N24   , En3 
	.byte		N24   , Gn3 
	.byte		N24   , Bn3 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W18
	.byte		N72   , Fs3 
	.byte		N72   , As3 
	.byte		N72   , Cs4 
	.byte		N72   , Fn4 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W66
	.byte		N24   , Gn3 
	.byte		N24   , Bn3 
	.byte		N24   , Dn4 
	.byte		N24   , Fs4 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W18
@ 033   ----------------------------------------
	.byte		N84   , Fs3 
	.byte		N84   , As3 
	.byte		N84   , Cs4 
	.byte		N84   , Fn4 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W90
	.byte		N72   , Fs3 
	.byte		N72   , As3 
	.byte		N72   , Cs4 
	.byte		N72   , Fn4 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W78
	.byte		N12   , Cs3 
	.byte		N12   , Ds3 
	.byte		N60   , Fs3 
	.byte		N60   , Bn3 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W06
@ 034   ----------------------------------------
	.byte		N48   , Cs3 
	.byte		N48   , Ds3 
	.byte	W48
	.byte		N48   
	.byte		N48   , Fn3 
	.byte		N48   , Gs3 
	.byte		N48   , Cs4 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W42
	.byte		N72   , Fs3 
	.byte		N72   , As3 
	.byte		N72   , Cs4 
	.byte		N72   , Fn4 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W66
	.byte		N24   , Gn3 
	.byte		N24   , Bn3 
	.byte		N24   , Dn4 
	.byte		N24   , Fs4 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W18
@ 035   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_7_027
@ 036   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_7_028
@ 037   ----------------------------------------
	.byte		N84   , Fs3 , v092
	.byte		N84   , As3 
	.byte		N84   , Cs4 
	.byte		N84   , Fn4 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W90
	.byte		N72   , Fs3 
	.byte		N72   , As3 
	.byte		N72   , Cs4 
	.byte		N72   , Fn4 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W78
	.byte		N60   , Cs3 
	.byte		N60   , Ds3 
	.byte		N60   , Fs3 
	.byte		N60   , Bn3 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W06
@ 038   ----------------------------------------
	.byte	W48
	.byte		N24   , Cs3 
	.byte		N24   , Fn3 
	.byte		N24   , Gs3 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W18
	.byte		        As2 
	.byte		N24   , Ds3 
	.byte		N24   , Fs3 
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W01
	.byte	W18
	.byte	GOTO
	 .word	mus_areazero_7_B1
mus_areazero_7_B2:
	.byte	W96
@ 039   ----------------------------------------
	.byte	FINE

@**************** Track 8 (Midi-Chn.8) ****************@

mus_areazero_8:
	.byte		VOL   , 127*mus_areazero_mvl/mxv
	.byte	KEYSH , mus_areazero_key+0
mus_areazero_8_B1:
@ 000   ----------------------------------------
@ 001   ----------------------------------------
@ 002   ----------------------------------------
@ 003   ----------------------------------------
@ 004   ----------------------------------------
@ 005   ----------------------------------------
@ 006   ----------------------------------------
@ 007   ----------------------------------------
@ 008   ----------------------------------------
	.byte		VOICE , 60
	.byte	W96
	.byte	W96
@ 009   ----------------------------------------
	.byte	W96
	.byte	W96
@ 010   ----------------------------------------
	.byte	W96
	.byte	W96
@ 011   ----------------------------------------
	.byte	W96
	.byte	W96
@ 012   ----------------------------------------
	.byte	W96
	.byte	W96
@ 013   ----------------------------------------
	.byte	W96
	.byte	W96
@ 014   ----------------------------------------
	.byte	W96
	.byte	W96
@ 015   ----------------------------------------
	.byte	W96
	.byte	W96
@ 016   ----------------------------------------
	.byte	W96
	.byte	W96
@ 017   ----------------------------------------
	.byte	W96
	.byte	W96
@ 018   ----------------------------------------
	.byte	W96
	.byte	W96
@ 019   ----------------------------------------
	.byte	W96
	.byte	W96
@ 020   ----------------------------------------
	.byte	W96
	.byte	W96
@ 021   ----------------------------------------
	.byte	W96
	.byte	W96
@ 022   ----------------------------------------
	.byte	W96
	.byte		N06   , Gs3 , v092
	.byte		N06   , Fn4 
	.byte	W12
	.byte		        As3 
	.byte		N06   , Fs4 
	.byte	W12
	.byte		        Fn3 
	.byte		N06   , Cs4 
	.byte	W12
	.byte		        Fs3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Ds3 
	.byte		N06   , Gs3 
	.byte	W12
	.byte		        As3 
	.byte		N06   , Cs4 
	.byte	W12
	.byte		        Gs3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Cs4 
	.byte		N06   , Gs4 
	.byte	W12
@ 023   ----------------------------------------
mus_areazero_8_023:
	.byte		N06   , Gs3 , v092
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Cs4 
	.byte		N06   , Gs4 
	.byte	W12
	.byte		        As3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Cs4 
	.byte		N06   , Gs4 
	.byte	W12
	.byte		        Gs3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Cs4 
	.byte		N06   , Gs4 
	.byte	W12
	.byte		        As3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Cs4 
	.byte		N06   , Gs4 
	.byte	W12
	.byte		        Gs3 
	.byte		N06   , Fn4 
	.byte	W12
	.byte		        As3 
	.byte		N06   , Fs4 
	.byte	W12
	.byte		        Fn3 
	.byte		N06   , Cs4 
	.byte	W12
	.byte		        Fs3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Ds3 
	.byte		N06   , Gs3 
	.byte	W12
	.byte		        As3 
	.byte		N06   , Cs4 
	.byte	W12
	.byte		        Gs3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Cs4 
	.byte		N06   , Gs4 
	.byte	W12
	.byte	PEND
@ 024   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_8_023
@ 025   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_8_023
@ 026   ----------------------------------------
	.byte		N06   , Gs3 , v092
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Cs4 
	.byte		N06   , Gs4 
	.byte	W12
	.byte		        As3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Cs4 
	.byte		N06   , Gs4 
	.byte	W12
	.byte		        Gs3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Cs4 
	.byte		N06   , Gs4 
	.byte	W12
	.byte		        As3 
	.byte		N06   , Ds4 
	.byte	W12
	.byte		        Cs4 
	.byte		N06   , Gs4 
	.byte	W96
	.byte	W12
@ 027   ----------------------------------------
	.byte	W96
	.byte	W96
@ 028   ----------------------------------------
	.byte	W96
	.byte	W96
@ 029   ----------------------------------------
	.byte	W96
	.byte	W96
@ 030   ----------------------------------------
	.byte	W96
	.byte	W96
@ 031   ----------------------------------------
	.byte	W96
	.byte	W96
@ 032   ----------------------------------------
	.byte	W96
	.byte	W96
@ 033   ----------------------------------------
	.byte	W96
	.byte	W96
@ 034   ----------------------------------------
	.byte	W96
	.byte	W96
@ 035   ----------------------------------------
	.byte	W96
	.byte	W96
@ 036   ----------------------------------------
	.byte	W96
	.byte	W96
@ 037   ----------------------------------------
	.byte	W96
	.byte	W96
@ 038   ----------------------------------------
	.byte	W96
	.byte	GOTO
	 .word	mus_areazero_8_B1
mus_areazero_8_B2:
	.byte	W96
@ 039   ----------------------------------------
	.byte	FINE

@**************** Track 9 (Midi-Chn.10) ****************@

mus_areazero_9:
	.byte	KEYSH , mus_areazero_key+0
mus_areazero_9_B1:
@ 000   ----------------------------------------
@ 001   ----------------------------------------
@ 002   ----------------------------------------
@ 003   ----------------------------------------
@ 004   ----------------------------------------
@ 005   ----------------------------------------
@ 006   ----------------------------------------
@ 007   ----------------------------------------
@ 008   ----------------------------------------
	.byte		VOICE , 0
	.byte		VOL   , 0*mus_areazero_mvl/mxv
	.byte		PAN   , c_v+0
	.byte	W96
	.byte	W96
@ 009   ----------------------------------------
	.byte	W96
	.byte	W96
@ 010   ----------------------------------------
	.byte	W96
	.byte	W96
@ 011   ----------------------------------------
	.byte	W96
	.byte	W96
@ 012   ----------------------------------------
	.byte	W96
	.byte	W96
@ 013   ----------------------------------------
	.byte	W96
	.byte	W96
@ 014   ----------------------------------------
	.byte	W96
	.byte	W96
@ 015   ----------------------------------------
	.byte	W96
	.byte	W96
@ 016   ----------------------------------------
	.byte	W96
	.byte	W96
@ 017   ----------------------------------------
	.byte	W96
	.byte	W96
@ 018   ----------------------------------------
	.byte	W96
	.byte		N12   , Cn1 , v092
	.byte	W48
	.byte		        En1 
	.byte	W48
@ 019   ----------------------------------------
mus_areazero_9_019:
	.byte	W12
	.byte		N12   , Cn1 , v092
	.byte	W12
	.byte		N06   
	.byte	W06
	.byte		N03   
	.byte	W03
	.byte		N03   
	.byte	W15
	.byte		N12   , En1 
	.byte	W48
	.byte		        Cn1 
	.byte	W48
	.byte		        En1 
	.byte	W48
	.byte	PEND
@ 020   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_9_019
@ 021   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_9_019
@ 022   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_9_019
@ 023   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_9_019
@ 024   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_9_019
@ 025   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_9_019
@ 026   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_9_019
@ 027   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_9_019
@ 028   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_9_019
@ 029   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_9_019
@ 030   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_9_019
@ 031   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_9_019
@ 032   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_9_019
@ 033   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_9_019
@ 034   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_9_019
@ 035   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_9_019
@ 036   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_9_019
@ 037   ----------------------------------------
	.byte	PATT
	 .word	mus_areazero_9_019
@ 038   ----------------------------------------
	.byte	W12
	.byte		N12   , Cn1 , v092
	.byte	W12
	.byte		N06   
	.byte	W06
	.byte		N03   
	.byte	W03
	.byte		N03   
	.byte	W15
	.byte		N12   , En1 
	.byte	W48
	.byte	GOTO
	 .word	mus_areazero_9_B1
mus_areazero_9_B2:
	.byte	W96
@ 039   ----------------------------------------
	.byte	FINE

@******************************************************@
	.align	2

mus_areazero:
	.byte	9	@ NumTrks
	.byte	0	@ NumBlks
	.byte	mus_areazero_pri	@ Priority
	.byte	mus_areazero_rev	@ Reverb.

	.word	mus_areazero_grp

	.word	mus_areazero_1
	.word	mus_areazero_2
	.word	mus_areazero_3
	.word	mus_areazero_4
	.word	mus_areazero_5
	.word	mus_areazero_6
	.word	mus_areazero_7
	.word	mus_areazero_8
	.word	mus_areazero_9

	.end
