;**********************************************
;Pin define
;       PWM P53   
;		AD  P40
;		P00 out·­×ª
;--------------------------------------------------------------------------
#include <mc32p7031.inc>

R_Temp          equ             00H
R_WorkTemp      equ             01H
R_WorkTemp1     equ             02H
R_LoopNum       equ             03H
R_VoltageH_Max 	equ             04H
R_VoltageL_Max 	equ             05H
R_VoltageH_Min 	equ             06H
R_VoltageL_Min 	equ             07H
R_VoltageSumH  	equ             08H
R_VoltageSumL  	equ	   	09H
R_VoltageH 	equ	   	0AH
R_VoltageL 	equ	   	0BH
R_OverloadCntH 	equ	   	0CH
R_OverloadCntL 	equ	   	0DH
R_PwmBuf   	equ	   	0EH
R_Pwm  	   	equ	   	0FH

R_DispNumM 	equ	   	10H
R_DispNumL 	equ	   	11H
R_Flag 	   	equ	   	12H
#define	   	B_8MsFlag  	R_Flag,0
#define	   	B_Overload 	R_Flag,1
#define	   	B_Reset	   	R_Flag,2
#define	   	B_AdSample 	R_Flag,3
#define	   	B_AdOk 	   	R_Flag,4

R_SampleCnt	equ             13H
R_VH_Max   	equ             14H
R_VL_Max   	equ             15H
R_VH_Min   	equ             16H
R_VL_Min   	equ             17H
R_VSumH	   	equ             18H
R_VSumL	   	equ	   	19H
R_DefCnt   	equ	   	1AH
R_DisplayCnt   	equ	   	1BH
R_8MsCnt   	equ	   	1CH
R_SegCnt   	equ	   	1DH
R_VoltageHBak  	equ	   	1EH
R_VoltageLBak  	equ	   	1FH

wr0	   	equ	   	20H
wr1	   	equ	   	21H
wr2	   	equ	   	22H
wr3	   	equ	   	23H
wr4	   	equ	   	24H
wr5	   	equ	   	25H
wr6	   	equ	   	26H
wr7	   	equ	   	27H
wr8	   	equ	   	28H
wr9	   	equ	   	29H
R_SampleNum	equ	   	2AH
R_VoltageSumM  	equ	   	2BH
;-------------------------------------------------
;MACRO
;-------------------------------------------------
MOV             MACRO           REG0,REG1
                movar  	   	REG1
                movra           REG0
       	       	ENDM
;-------------------------------------------------
MOVI            MACRO           REG0,IMM0
                movai           IMM0
                movra           REG0
       	       	ENDM
;-------------------------------------------------
ANDIR           MACRO           REG0,IMM0
                movai           IMM0
                ANDRA           REG0
       	       	ENDM
;-------------------------------------------------
IORIR           MACRO           REG0,IMM0
                movai           IMM0
                orra   	       	REG0
       	       	ENDM
;-------------------------------------------------
XORIR           MACRO           REG0,IMM0
                movai           IMM0
                xorra  	       	REG0
       	       	ENDM
;-------------------------------------------------
CJZ1            MACRO           REG0,ADDRESS
                movar  	       	REG0
                jbclr           Z
                goto            ADDRESS
       	       	ENDM
;-------------------------------------------------
CJNZ1           MACRO           REG0,ADDRESS
                movar  	       	REG0
                jbset           Z
                goto            ADDRESS
       	       	ENDM
;-------------------------------------------------
CJZ2            MACRO           REG0,REG1,ADDRESS
                movar  	       	REG0
                orar   	       	REG1
                jbclr           Z
                goto            ADDRESS
                ENDM
;-------------------------------------------------
CJNZ2           MACRO           REG0,REG1,ADDRESS
                movar  	       	REG0
                orar   	       	REG1
                jbset           Z
                goto            ADDRESS
       	       	ENDM
;-------------------------------------------------
CJZ3            MACRO           REG0,REG1,REG2,ADDRESS
                movar  	       	REG0
                orar   	       	REG1
                orar   	       	REG2
                jbclr           Z
                goto            ADDRESS
       	       	ENDM
;-------------------------------------------------
CJNZ3           MACRO           REG0,REG1,REG2,ADDRESS
                movar  	       	REG0
                orar   	       	REG1
                orar   	       	REG2
                jbset           Z
                goto            ADDRESS
       	       	ENDM
;-------------------------------------------------
CJZ4            MACRO           REG0,REG1,REG2,REG3,ADDRESS
                movar  	       	REG0
                orar           	REG1
                orar           	REG2
                orar           	REG3
                jbclr           Z
                goto            ADDRESS
       	       	ENDM
;-------------------------------------------------
CJNZ4           MACRO           REG0,REG1,REG2,REG3,ADDRESS
                movar  	       	REG0
                orar           	REG1
                orar           	REG2
                orar           	REG3
                jbset           Z
                goto            ADDRESS
       	       	ENDM
;-------------------------------------------------
CJE1            MACRO           REG0,IMM0,ADDRESS
                movai           IMM0
                xorar           REG0
                jbclr           Z
                goto            ADDRESS
       	       	ENDM
;-------------------------------------------------
CJNE1           MACRO           REG0,IMM0,ADDRESS
                movai           IMM0
                xorar           REG0
                jbset           Z
                goto            ADDRESS
       	       	ENDM
;-------------------------------------------------
CJE2            MACRO           REG0,REG1,IMM0,IMM1,ADDRESS
       	       	movai  	       	IMM0
       	       	XORAR  	       	REG0
       	       	JBSET  	       	Z
       	       	GOTO   	       	$+5
       	       	movai  	       	IMM1
       	       	XORAR  	       	REG1
       	       	JBCLR  	       	Z
       	       	GOTO   	       	ADDRESS
       	       	ENDM
;-------------------------------------------------
CJNE2           MACRO           REG0,REG1,IMM0,IMM1,ADDRESS
       	       	movai  	       	IMM0
       	       	XORAR  	       	REG0
       	       	JBSET  	       	Z
       	       	GOTO   	       	ADDRESS
       	       	movai  	       	IMM1
       	       	XORAR  	       	REG1
       	       	JBSET  	       	Z
       	       	GOTO   	       	ADDRESS
       	       	ENDM
;-------------------------------------------------
CJS1   	       	MACRO  	       	REG0,IMM0,ADDRESS
       	       	movai  	       	IMM0
       	       	ASUBAR 	       	REG0
       	       	JBCLR  	       	C
       	       	GOTO   	       	ADDRESS
       	       	ENDM
;-------------------------------------------------
CJB1   	       	MACRO  	       	REG0,IMM0,ADDRESS
       	       	movai  	       	IMM0
       	       	ASUBAR 	       	REG0
       	       	JBSET  	       	C
       	       	GOTO   	       	ADDRESS
       	       	ENDM
;-------------------------------------------------
CPE1   	       	MACRO  	       	REG0,REG1,ADDRESS
       	       	MOVAR  	       	REG1
       	       	XORAR  	       	REG0
       	       	JBCLR  	       	Z
       	       	GOTO   	       	ADDRESS
       	       	ENDM
;-------------------------------------------------
CPNE1  	       	MACRO  	       	REG0,REG1,ADDRESS
       	       	MOVAR  	       	REG1
       	       	XORAR  	       	REG0
       	       	JBSET  	       	Z
       	       	GOTO   	       	ADDRESS
       	       	ENDM
;-------------------------------------------------
CPS1            MACRO           REG0,REG1,ADDRESS
                movar  	       	REG0
                asubar 	       	REG1
                jbset           C
                goto            ADDRESS
       	       	ENDM
;-------------------------------------------------
CPB1   	       	MACRO           REG0,REG1,ADDRESS
                movar  	       	REG0
                asubar 	       	REG1
                jbclr           C
                goto            ADDRESS
       	       	ENDM
;-------------------------------------------------
CJS2            MACRO           REG0H,REG0L,IMMH,IMML,ADDRESS
                movar  	       	REG0H
                asubai 	       	IMMH
                jbset           C
                goto            ADDRESS
                jbset           Z
                goto            $+5
                movar  	       	REG0L
                asubai 	       	IMML
                jbset           C
                goto            ADDRESS
       	       	ENDM
;-------------------------------------------------
CJB2            MACRO           REG0H,REG0L,IMMH,IMML,ADDRESS
                movar  	       	REG0H
                asubai 	       	IMMH
                jbset           C
                goto            $+7
                jbset           Z
                goto            ADDRESS
                movar  	       	REG0L
                asubai 	       	IMML
                jbclr           C
                goto            ADDRESS
       	       	ENDM
;-------------------------------------------------
CPS2            MACRO           REG0H,REG0L,REG1H,REG1L,ADDRESS
                movar  	       	REG0H
                asubar 	       	REG1H
                jbset           C
                goto            ADDRESS
                jbset           Z
                goto            $+5
                movar  	       	REG0L
                asubar 	       	REG1L
                jbset           C
                goto            ADDRESS
       	       	ENDM
;--------------------------------------------------------------------------
   	   	org    	       	0x00
   	   	goto   	       	Reset
;--------------------------------------------------------------------------
   	   	org    	       	08h
Interrupt_Service:
   	   	PUSH
   	   	jbset  	   	T0IF
   	   	goto   	   	Interrupt_Service_Ret
   	   	bclr   	   	T0IF
   	   	XORIR  	   	IOP0,1
   	   	jzr	   	R_8MsCnt
   	   	nop
   	   	call   	   	F_Output
   	   	CJS1   	   	R_8MsCnt,8,Interrupt_Service_Ret
   	   	clrr   	   	R_8MsCnt
   	   	bset   	   	B_8MsFlag
Interrupt_Service_Ret:
   	   	POP
   	   	retie
;--------------------------------------------------------------------------
F_PwmTable:
   	   	;dw	   	3  	;0
   	   	;dw	   	5  	;1 
   	   	;dw	   	8  	;2 
   	   	;dw	   	10 	;3 
   	   	;dw	   	13 	;4 
   	   	;dw	   	15 	;5 
   	   	;dw	   	18 	;6 
   	   	dw 	   	20 ;20 ;7 
   	   	dw 	   	23 ;23 ;8 
   	   	dw 	   	26 ;26 ;9 
   	   	dw 	   	28 ;28 ;10
   	   	dw 	   	31 ;31 ;11
   	   	dw 	   	33 ;33 ;12
   	   	dw 	   	36 ;36 ;13
   	   	dw 	   	38 ;38 ;14
   	   	dw 	   	41 ;41 ;15
   	   	dw 	   	43 ;43 ;16
   	   	dw 	   	46 ;46 ;17
   	   	dw 	   	48 ;48 ;18
   	   	dw 	   	51 ;51 ;19
   	   	dw 	   	54 ;54 ;20
   	   	dw 	   	56 ;56 ;21
   	   	dw 	   	59 ;59 ;22
   	   	dw 	   	61 ;61 ;23
   	   	dw 	   	64 ;64 ;24
   	   	dw 	   	66 ;66 ;25
   	   	dw 	   	69 ;69 ;26
   	   	dw 	   	71 ;71 ;27
   	   	dw 	   	74 ;74 ;28
   	   	dw 	   	77 ;77 ;29
   	   	dw 	   	79 ;79 ;30
   	   	dw 	   	82 ;82 ;31
   	   	dw 	   	84 ;84 ;32
   	   	dw 	   	87 ;87 ;33
   	   	dw 	   	89 ;89 ;34
   	   	dw 	   	92 ;92 ;35
   	   	dw 	   	94 ;94 ;36
   	   	dw 	   	97 ;97 ;37
   	   	dw 	   	99 ;99 ;38
   	   	dw 	   	102;102;39
   	   	dw 	   	105;105;40
   	   	dw 	   	107;107;41
   	   	dw 	   	110;110;42
   	   	dw 	   	112;112;43
   	   	dw 	   	115;115;44
   	   	dw 	   	117;117;45
   	   	dw 	   	120;120;46
   	   	dw 	   	122;122;47
   	   	dw 	   	125;125;48
   	   	dw 	   	128;128;49
   	   	dw 	   	130;130;50
   	   	dw 	   	133;133;51
   	   	dw 	   	135;135;52
   	   	dw 	   	138;138;53
   	   	dw 	   	140;140;54
   	   	dw 	   	143;143;55
   	   	dw 	   	145;145;56
   	   	dw 	   	148;148;57
   	   	dw 	   	150;150;58
   	   	dw 	   	153;153;59
   	   	dw 	   	156;156;60
   	   	dw 	   	158;158;61
   	   	dw 	   	161;161;62
   	   	dw 	   	163;163;63
   	   	dw 	   	166;166;64
   	   	dw 	   	168;168;65
   	   	dw 	   	171;171;66
   	   	dw 	   	173;173;67
   	   	dw 	   	176;176;68
   	   	dw 	   	179;179;69
   	   	dw 	   	181;181;70
   	   	dw 	   	184;184;71
   	   	dw 	   	186;186;72
   	   	dw 	   	189;189;73
   	   	dw 	   	191;191;74
   	   	dw 	   	194;194;75
   	   	dw 	   	196;196;76
   	   	dw 	   	199;199;77
   	   	dw 	   	201;201;78
   	   	dw 	   	204;204;79
   	   	dw 	   	207;207;80
   	   	dw 	   	209;209;81
   	   	dw 	   	212;212;82
   	   	dw 	   	214;214;83
   	   	dw 	   	217;217;84
   	   	dw 	   	219;219;85
   	   	dw 	   	222;222;86
   	   	dw 	   	224;224;87
   	   	dw 	   	227;227;88
   	   	dw 	   	230;230;89
   	   	dw 	   	232;232;90
   	   	dw 	   	232;235;91
   	   	dw 	   	232;237;92
   	   	dw 	   	232;240;93
   	   	dw 	   	232;242;94
   	   	dw 	   	232;245;95
   	   	dw 	   	232;247;96
   	   	dw 	   	232;250;97
   	   	dw 	   	232;252;98
   	   	dw 	   	232;255;99
;--------------------------------------------------------------------------
Reset:
       	   	movai  	       	0x00
       	   	movra  	       	IOP0
       	   	movai  	       	11111111B
       	   	movra  	       	OEP0
       	   	movai  	       	0x00
       	   	movra  	       	IOP0

       	   	movai  	       	0x00
       	   	movra  	       	IOP4
       	   	movai  	       	11111100B
       	   	movra  	       	OEP4
       	   	movai  	       	0x00
       	   	movra  	       	IOP4

       	   	movai  	       	0x00
       	   	movra  	       	IOP5
       	   	movai  	       	11111111B
       	   	movra  	       	OEP5
       	   	movai  	       	0x00
       	   	movra  	       	IOP5
       	   	
       	   	bset   	   	IOP4,4

       	   	clrr   	       	FSR1
       	   	movai  	       	127
       	   	movra  	       	FSR0
       	   	clrr   	       	INDF
       	   	djzr   	       	FSR0
       	   	goto   	       	$-2
       	   	clrr   	       	INDF
   	   	movai  	   	5AH
   	   	movar  	   	WDTR

       	   	movai  	       	0x03
       	   	movra  	       	ANSEL

       	   	movai  	       	0x90
       	   	movra  	       	ADCR

   	   	MOVI   	   	VREF,02H;Vref=4V

       	   	movai  	       	00110000B;0x20;0111 0000
       	   	movra  	       	ADRL   	;ad covert times,Fcpu/8

       	   	movai  	       	00001000B
       	   	movra  	       	TXCR
       	   	
       	   	movai  	       	11010100B
       	   	movra  	       	T0CR

       	   	movai  	       	130
       	   	movra  	       	T0C
       	   	movra  	       	T0D
       	   	
       	   	movai  	       	11010000B
       	   	movra  	       	T1CR
       	   	movai  	       	0
       	   	movra  	       	T1C
       	   	movra  	       	T1D

       	   	bclr   	       	T0IF
       	   	bset   	       	T0IE
       	   	bset   	       	GIE
       	   	bset   	   	B_Reset
;--------------------------------------------------------------------------
Main:
   	   	movai  	   	5AH
   	   	movra  	   	WDTR
   	   	jbclr  	   	B_Reset
   	   	goto   	   	$+4
   	   	jbset  	   	B_8MsFlag
   	   	goto   	   	Main
   	   	bclr   	   	B_8MsFlag
   	  ; 	call   	   	ADC_Config
   	   	call   	   	F_AdSample
   	   	call   	   	F_Ad_Level
   	   	call   	   	F_Pwm
   	   	goto   	   	Main

;------------------------------------------------------------------------------
F_AdSample:
               	MOVI   	   	R_LoopNum,0Ah
   	   	clrr   	   	R_VoltageSumH
   	   	clrr   	   	R_VoltageSumL
   	   	bclr   	   	ADCHS2
   	   	bclr   	   	ADCHS1
   	   	bclr   	   	ADCHS0
       	   	bclr   	       	ADEOC
       	   	bset   	       	ADST
       	   	goto   	   	$+1
       	   	goto   	   	$+1
       	   	goto   	   	$+1
       	   	jbset  	       	ADEOC
       	   	goto   	       	$-1

       	   	bclr   	       	ADEOC
       	   	bset   	       	ADST
       	   	goto   	   	$+1
       	   	goto   	   	$+1
       	   	goto   	   	$+1
       	   	jbset  	       	ADEOC
       	   	goto   	       	$-1
L_AdSample_Loop:
       	   	bclr   	       	ADEOC
       	   	bset   	       	ADST
       	   	goto   	   	$+1
       	   	goto   	   	$+1
       	   	goto   	   	$+1
       	   	jbset  	       	ADEOC
       	   	goto   	       	$-1

       	   	swapar 	   	ADRL
       	   	andai  	   	0F0H
       	   	movra  	       	R_Temp

       	   	movar  	       	ADRH
       	   	movra  	       	R_WorkTemp

   	   	bclr   	   	C
   	   	rrr	   	R_WorkTemp
   	   	rrr	   	R_Temp
   	   	bclr   	   	C
   	   	rrr	   	R_WorkTemp
   	   	rrr	   	R_Temp
   	   	bclr   	   	C
   	   	rrr	   	R_WorkTemp
   	   	rrr	   	R_Temp
   	   	bclr   	   	C
   	   	rrr	   	R_WorkTemp
   	   	rrr	   	R_Temp

   	   	CJNE1  	   	R_LoopNum,0AH,L_AdComapre
   	   	movar  	   	R_Temp
   	   	movra  	   	R_VoltageL_Min
   	   	movra  	   	R_VoltageL_Max
   	   	movar  	   	R_WorkTemp
   	   	movra  	   	R_VoltageH_Min
   	   	movra  	   	R_VoltageH_Max
   	   	goto   	   	L_AdAverage
L_AdComapre:
   	   	CPS2   	   	R_WorkTemp,R_Temp,R_VoltageH_Max,R_VoltageL_Max,L_AdComapre_Min
   	   	movar  	   	R_Temp
   	   	movra  	   	R_VoltageL_Max
   	   	movar  	   	R_WorkTemp
   	   	movra  	   	R_VoltageH_Max
L_AdComapre_Min:
   	   	CPS2   	   	R_VoltageH_Min,R_VoltageL_Min,R_WorkTemp,R_Temp,L_AdAverage
   	   	movar  	   	R_Temp
   	   	movra  	   	R_VoltageL_Min
   	   	movar  	   	R_WorkTemp
   	   	movra  	   	R_VoltageH_Min
L_AdAverage:
   	   	movar  	   	R_Temp
   	   	addra  	   	R_VoltageSumL
   	   	jbclr  	   	C
   	   	jzr	   	R_VoltageSumH
   	   	nop
   	   	movar  	   	R_WorkTemp
   	   	addra  	   	R_VoltageSumH

   	   	djzr   	   	R_LoopNum
   	   	goto   	   	L_AdSample_Loop

   	   	movar  	   	R_VoltageSumL  	   	;sub Min
   	   	asubar 	   	R_VoltageL_Min
   	   	movra  	   	R_VoltageSumL
   	   	jbset  	   	C
   	   	djzr   	   	R_VoltageSumH
   	   	nop
   	   	movar  	   	R_VoltageSumH
   	   	asubar 	   	R_VoltageH_Min
   	   	movra  	   	R_VoltageSumH

   	   	movar  	   	R_VoltageSumL  	   	;sub Max
   	   	asubar 	   	R_VoltageL_Max
   	   	movra  	   	R_VoltageSumL
   	   	jbset  	   	C
   	   	djzr   	   	R_VoltageSumH
   	   	nop
   	   	movar  	   	R_VoltageSumH
   	   	asubar 	   	R_VoltageH_Max
   	   	movra  	   	R_VoltageSumH

   	   	bclr   	   	C
   	   	rrr	   	R_VoltageSumH
   	   	rrr	   	R_VoltageSumL
   	   	bclr   	   	C
   	   	rrr	   	R_VoltageSumH
   	   	rrr	   	R_VoltageSumL
   	   	bclr   	   	C
   	   	rrr	   	R_VoltageSumH
   	   	rrr	   	R_VoltageSumL
L_AdSample_Ret:
   	   	return
;**********************************************
F_Ad_Level:
   	   	bclr   	   	C
   	   	rrr	   	R_VoltageSumH
   	   	rrr	   	R_VoltageSumL
   	   	bclr   	   	C
   	   	rrr	   	R_VoltageSumH
   	   	rrr	   	R_VoltageSumL
   	   	bclr   	   	C
   	   	rrr	   	R_VoltageSumH
   	   	rrr	   	R_VoltageSumL
   	   	bclr   	   	C
   	   	rrr	   	R_VoltageSumH
   	   	rrr	   	R_VoltageSumL
   	   	clrr   	   	FSR1
   	   	movai  	   	F_PwmTable
   	   	
   	   	addar  	   	R_VoltageSumL
   	   	movra  	   	FSR0
   	   	movc
   	   	movra  	   	R_PwmBuf
L_AD_Level_Ret:
   	   	return
;------------------------------------------------------------------------------
F_Output:
   	   	CJZ1   	   	R_PwmBuf,L_Output_Ret
   	   	jbset  	   	B_Reset
   	   	goto   	   	L_Output_Do
   	   	
   	   	jbset  	   	B_AdOk
   	   	goto   	   	L_Output_Do
   	   	   	
   	   	movar  	   	R_PwmBuf
   	   	asubar 	   	R_Pwm
   	   	jbclr  	   	Z
   	   	goto   	   	L_Output_Do0
   	   	jbset  	   	C
   	   	goto   	   	L_Ad_Level_Dec
   	   	jzr	   	R_Pwm
   	   	nop
   	   	goto   	   	L_AD_Level_Ret
L_Ad_Level_Dec:
   	   	djzr   	   	R_Pwm
   	   	nop
   	   	goto   	   	L_Output_Ret
L_Output_Do0:
   	   	bclr   	   	B_AdOk
L_Output_Do:
   	   	bclr   	   	B_Reset
   	   	MOV	   	R_Pwm,R_PwmBuf
   	   	goto   	   	L_Output_Ret
L_Output_Ret:
   	   	return
;------------------------------------------------------------------------------
F_Pwm:
   	   	CJZ1   	   	R_Pwm,L_Pwm_Off
   	   	CJE1   	   	R_Pwm,0FFH,L_Pwm_Full
   	   	MOV	   	T1D,R_Pwm
   	   	bset   	   	PWM1OE
   	   	goto   	   	L_Pwm_Ret
L_Pwm_Off:
   	   	bclr   	   	PWM1OE
   	   	bclr   	   	IOP5,3
   	   	goto   	   	L_Pwm_Ret
L_Pwm_Full:	
   	   	bclr   	   	PWM1OE
   	   	bset   	   	IOP5,3 	
L_Pwm_Ret:
   	   	return

;**********************************************
;FILE NAME:DIV32X16
;IN:wr8wr7wr6wr5/wr3wr2
;OUT:wr8wr7wr6wr5
;TEMP:wr1,wr0,wr4
;SMALL DATA: wr1wr0
;------------------------------------------
F_Div:
   	   	clrr   	   	wr0
   	   	clrr   	   	wr1
   	   	MOVI   	   	wr4,32
                           	
   	   	CJNZ2  	   	wr3,wr2,L_Div
   	   	clrr   	   	wr5
   	   	clrr   	   	wr6
   	   	clrr   	   	wr7
   	   	clrr   	   	wr8
           	goto   	   	L_Div_Ret
L_Div:                     	
   	   	bclr   	   	C
           	rlr    	   	wr5
           	rlr    	   	wr6
   	   	rlr	   	wr7
   	   	rlr	   	wr8
           	rlr	   	wr0
   	   	rlr	   	wr1
   	   	jbclr  	   	C
   	   	goto   	   	L_Div_1
                           	
   	   	movar  	   	wr1
   	   	asubar 	   	wr3
                           	
   	   	jbset  	   	C
   	   	goto   	   	L_Div_2
                           	
   	   	jbset  	   	Z
   	   	goto   	   	L_Div_1
                           	
   	   	movar  	   	wr0
   	   	asubar 	   	wr2
   	   	jbset  	   	C
   	   	goto   	   	L_Div_2
                           	
L_Div_1:                   	
   	   	jzr	   	wr5
   	   	nop        	
   	   	movar  	   	wr1
   	   	asubar 	   	wr3
   	   	movra  	   	wr1
                           	
   	   	movar  	   	wr0
   	   	asubar 	   	wr2
   	   	movra  	   	wr0
                           	
   	   	jbclr  	   	C
   	   	goto   	   	L_Div_2
   	   	djzr   	   	wr1
   	   	nop        	
L_Div_2:                   	
   	   	djzr   	   	wr4
   	   	goto   	   	L_Div
L_Div_Ret:
   	   	return
;------------------------------------------------------------------------------
   	   	END
