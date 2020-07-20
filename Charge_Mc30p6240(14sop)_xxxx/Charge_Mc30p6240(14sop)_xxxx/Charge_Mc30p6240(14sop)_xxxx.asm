INCLUDE MC30P6240.INC
;LED DIM CONTROL FOR HONGYUAN
;EDITED BY COSTA 2020-06-24
;14SOP
;FSYS:8M/2
;=======================================
;BYTE DEFINE SECTION
#DEFINE FLAGBUF	   	0x10
#DEFINE ACCBUF 	   	0x11
#DEFINE TMP0   	   	0X12
#DEFINE FLAG0  	   	0X13
#DEFINE F_K_RND	   	FLAG0,0
#DEFINE F_T1   	   	FLAG0,1
#DEFINE F_T2   	   	FLAG0,2
#DEFINE F_T3   	   	FLAG0,3
#DEFINE F_WK0  	   	FLAG0,5	   	;手电筒工作
#DEFINE F_WK1  	   	FLAG0,6	   	;红外灯工作
#DEFINE F_WK2  	   	FLAG0,7	   	;外部开关工作
#DEFINE KFLAG  	   	0X14
#DEFINE F_PR1  	   	KFLAG,0
#DEFINE F_PR2  	   	KFLAG,1
#DEFINE F_PR3  	   	KFLAG,2
#DEFINE F_PRS  	   	KFLAG,3
#DEFINE F_H1   	   	KFLAG,4
#DEFINE F_H2   	   	KFLAG,5
#DEFINE F_PRESSED  	KFLAG,6
#DEFINE F_HOLD 	   	KFLAG,7

#DEFINE DEBOUNCE   	0X15
#DEFINE HOLD_CNT   	0X16
#DEFINE HALT_CNT   	0X17
#DEFINE KEYIN  	   	0X18
#DEFINE KEYOLD 	   	0X19
#DEFINE FLAG1  	   	0X1A
#DEFINE F_ACTED	   	FLAG1,0
#DEFINE	F_NO_WK	   	FLAG1,1
#DEFINE F_WK1_1	   	FLAG1,2
#DEFINE F_UP   	   	FLAG1,3
#DEFINE	F_INC_EN   	FLAG1,4
#DEFINE STG1   	   	0X1B
#DEFINE	STG2   	   	0X1C
#DEFINE	STG3   	   	0X1D
#DEFINE DLY1   	   	0X1E
#DEFINE DLY2   	   	0X1F
#DEFINE	CNT50MS	   	0X20
#DEFINE TM_CNT 	   	0X21
#DEFINE DUTY_BK	   	0X22
#DEFINE KEY_CNT	   	0X23

;=======================================
;PORT DEFINE SECTION
#DEFINE	P_PSW3 	   	P00D
#DEFINE	P_KLED 	   	P01D
#DEFINE	P_SLED 	   	P02D
#DEFINE	P_RLED 	   	P03D
#DEFINE	P_PWMC 	   	P10D
#DEFINE	P_PWMB 	   	P11D
#DEFINE	P_PWMA 	   	P12D
#DEFINE	P_KYR  	   	P13D
#DEFINE	P_KYS  	   	P14D
#DEFINE	P_KYK  	   	P15D



;=======================================
   	   	   	   	ORG     0x00       	   	;起始地址
   	   	   	   	CLRWDT
   	   	   	   	CLRR   	INTE
   	   	   	   	CLRR   	INTF
   	   	   	   	CLRR   	INTF1
           	   	GOTO    PWON_Start     	   	;调到程序运行
        
       	   	   	ORG    	0x08   	   	;进入中断地址
   	   	   	   	MOVRA  	ACCBUF
   	   	   	   	MOVAR  	STATUS
   	   	   	   	MOVRA  	FLAGBUF
   	   	   	   	JBSET  	T0IF
   	   	   	   	GOTO   	INT_EXIT
   	   	   	   	BCLR   	T0IF   	;EVERY (64/4M)*256=4096US
   	   	   	   	BSET   	F_INC_EN
   	   	   	   	INCR   	KEY_CNT
   	   	   	   	MOVAI  	4
   	   	   	   	RSUBAR 	KEY_CNT
   	   	   	   	JBSET  	C
   	   	   	   	GOTO   	INT_EXIT
   	   	   	   	CLRR   	KEY_CNT
   	   	   	   	BSET   	F_K_RND
   	   	   	   	MOVAR  	HALT_CNT
   	   	   	   	XORAI  	0
   	   	   	   	JBSET  	Z
   	   	   	   	DECR   	HALT_CNT
   	   	   	   	INCR   	CNT50MS
   	   	   	   	MOVAI  	3
   	   	   	   	RSUBAR 	CNT50MS
   	   	   	   	JBSET  	C
   	   	   	   	GOTO   	INT_EXIT
   	   	   	   	CLRR   	CNT50MS
   	   	   	   	MOVAR  	DLY1
   	   	   	   	XORAI  	0
   	   	   	   	JBSET  	Z
   	   	   	   	DECR   	DLY1
   	   	   	   	MOVAR  	DLY2
   	   	   	   	XORAI  	0
   	   	   	   	JBSET  	Z
   	   	   	   	DECR   	DLY2
INT_EXIT:
   	   	   	   	CLRR   	INTF
   	   	   	   	MOVAR  	FLAGBUF
   	   	   	   	MOVRA  	STATUS
   	   	   	   	MOVAR  	ACCBUF
   	   	   	   	RETIE
PWON_Start:
   	   	   	   	CLRR   	DDR0
   	   	   	   	CLRR   	DDR1
   	   	   	   	CLRR   	P0
   	   	   	   	CLRR   	P1
   	   	   	   	MOVAI  	0X50
   	   	   	   	MOVRA  	TMP0
PWON_WAIT:
   	   	   	   	CLRWDT
   	   	   	   	DJZR   	TMP0
   	   	   	   	GOTO   	PWON_WAIT
   	   	   	   	CALL   	HDWARE_INITIAL
   	   	   	   	CALL   	RAM_CLR
   	   	   	   	CALL   	USR_INITIAL
;=======================================
;;;;;;;;;;;MAIN LOOP SECTION;;;;;;;;;;;;
;=======================================
MAIN:
   	   	   	   	CLRWDT
   	   	   	   	CALL   	KEY_SCAN
   	   	   	   	CALL   	GET_STATE
   	   	   	   	CALL   	OUTPUT
   	   	   	   	GOTO   	MAIN   	;FOR TEST
HALT_CHK:
   	   	   	   	JBCLR  	F_PRS
   	   	   	   	GOTO   	MAIN
   	   	   	   	JBCLR  	F_WK0
   	   	   	   	GOTO   	MAIN
   	   	   	   	JBCLR  	F_WK1
   	   	   	   	GOTO   	MAIN
   	   	   	   	JBCLR  	F_WK2
   	   	   	   	GOTO   	MAIN
   	   	   	   	MOVAR  	HALT_CNT
   	   	   	   	XORAI  	0
   	   	   	   	JBSET  	Z
   	   	   	   	GOTO   	MAIN
   	   	   	   	MOVAR  	DLY1
   	   	   	   	XORAI  	0
   	   	   	   	JBSET  	Z
   	   	   	   	GOTO   	MAIN
   	   	   	   	MOVAR  	DLY2
   	   	   	   	XORAI  	0
   	   	   	   	JBSET  	Z
   	   	   	   	GOTO   	MAIN
   	   	   	   	NOP
   	   	   	   	NOP
   	   	   	   	STOP
   	   	   	   	NOP
   	   	   	   	NOP
   	   	   	   	GOTO   	MAIN
;;;;;;;;;;;;;MAIN LOOP END;;;;;;;;;;;;;;
;=======================================
;SUBROUTINE SECTION
KEY_SCAN:
   	   	   	   	CLRWDT
   	   	   	   	JBSET  	F_K_RND
   	   	   	   	GOTO   	KEY_SCAN_EXIT
   	   	   	   	BCLR   	F_K_RND
   	   	   	   	CLRR   	KEYIN
   	   	   	   	JBSET  	P_KYS
   	   	   	   	BSET   	KEYIN,0
   	   	   	   	JBSET  	P_KYR
   	   	   	   	BSET   	KEYIN,1
   	   	   	   	JBSET  	P_KYK
   	   	   	   	BSET   	KEYIN,2
   	   	   	   	MOVAR  	KEYIN
   	   	   	   	XORAI  	0
   	   	   	   	JBCLR  	Z
   	   	   	   	GOTO   	NOKEY_PRO
   	   	   	   	MOVAR  	KEYIN
   	   	   	   	XORAR  	KEYOLD
   	   	   	   	JBSET  	Z
   	   	   	   	GOTO   	NEWKEY_PRO
   	   	   	   	INCR   	DEBOUNCE
   	   	   	   	MOVAI  	0X04
   	   	   	   	RSUBAR 	DEBOUNCE
   	   	   	   	JBSET  	C
   	   	   	   	GOTO   	KEY_SCAN_EXIT
   	   	   	   	MOVAI  	0X04
   	   	   	   	MOVRA  	DEBOUNCE
   	   	   	   	JBCLR  	F_PRESSED
   	   	   	   	GOTO   	KEY_HLD_CHK
   	   	   	   	BSET   	F_PRESSED
   	   	   	   	GOTO   	K_PRS_HLD_CHK
KEY_HLD_CHK:
   	   	   	   	JBCLR  	F_HOLD
   	   	   	   	GOTO   	KEY_SCAN_EXIT
   	   	   	   	INCR   	HOLD_CNT
   	   	   	   	MOVAI  	0X60
   	   	   	   	RSUBAR 	HOLD_CNT
   	   	   	   	JBSET  	C
   	   	   	   	GOTO   	KEY_SCAN_EXIT
   	   	   	   	MOVAI  	0X60
   	   	   	   	MOVRA  	HOLD_CNT
   	   	   	   	BSET   	F_HOLD
K_PRS_HLD_CHK:
   	   	   	   	MOVAI  	122
   	   	   	   	MOVRA  	HALT_CNT
   	   	   	   	MOVAR  	KEYIN
   	   	   	   	XORAI  	00000001B
   	   	   	   	JBCLR  	Z
   	   	   	   	GOTO   	K1_PRO
   	   	   	   	MOVAR  	KEYIN
   	   	   	   	XORAI  	00000010B
   	   	   	   	JBCLR  	Z
   	   	   	   	GOTO   	K2_PRO
   	   	   	   	MOVAR  	KEYIN
   	   	   	   	XORAI  	00000100B
   	   	   	   	JBCLR  	Z
   	   	   	   	GOTO   	K3_PRO
   	   	   	   	GOTO   	KEY_SCAN_EXIT
K1_PRO:	   	;手电筒开关
   	   	   	   	JBCLR  	F_HOLD
   	   	   	   	GOTO   	K1_HLD_PRO
   	   	   	   	BSET   	F_PR1
   	   	   	   	BCLR   	F_H1
   	   	   	   	GOTO   	KEY_SCAN_EXIT
K1_HLD_PRO:
   	   	   	   	BCLR   	F_PR1
   	   	   	   	BSET   	F_H1
   	   	   	   	GOTO   	KEY_SCAN_EXIT
K2_PRO:	   	;红白灯板开关
   	   	   	   	JBCLR  	F_HOLD
   	   	   	   	GOTO   	K2_HLD_PRO
   	   	   	   	BSET   	F_PR2
   	   	   	   	BCLR   	F_H2
   	   	   	   	GOTO   	KEY_SCAN_EXIT
K2_HLD_PRO:
   	   	   	   	BCLR   	F_PR2
   	   	   	   	BSET   	F_H2
   	   	   	   	GOTO   	KEY_SCAN_EXIT
K3_PRO:	   	;外部开关
   	   	   	   	BSET   	F_PR3
   	   	   	   	BSET   	F_T3
   	   	   	   	GOTO   	KEY_SCAN_EXIT
NEWKEY_PRO:
   	   	   	   	BSET	   	F_PRS
   	   	   	   	MOVAR  	KEYIN
   	   	   	   	MOVRA  	KEYOLD
   	   	   	   	MOVAI  	0X04
   	   	   	   	MOVRA  	DEBOUNCE
   	   	   	   	GOTO   	KEY_SCAN_EXIT
NOKEY_PRO:
   	   	   	   	JBCLR  	F_PR1
   	   	   	   	BSET   	F_T1
   	   	   	   	JBCLR  	F_PR2
   	   	   	   	BSET   	F_T2
   	   	   	   	CLRR   	KFLAG
   	   	   	   	CLRR   	KEYOLD
   	   	   	   	CLRR   	DEBOUNCE
   	   	   	   	CLRR   	HOLD_CNT
   	   	   	   	BCLR   	F_ACTED
KEY_SCAN_EXIT:
   	   	   	   	RETURN
;=======================================
GET_STATE:
   	   	   	   	CLRWDT
   	   	   	   	JBSET  	F_T1
   	   	   	   	GOTO   	K1_HLD_CHK
   	   	   	   	BCLR   	F_T1
   	   	   	   	JBCLR  	F_WK0
   	   	   	   	GOTO   	WK0_STG_CHK
A_STG3:
   	   	   	   	BSET   	F_WK0
   	   	   	   	BCLR   	F_NO_WK
   	   	   	   	MOVAR  	T1LOAD
   	   	   	   	MOVRA  	T1DATA
   	   	   	   	MOVAI  	00000100B
   	   	   	   	MOVRA  	STG1
   	   	   	   	BSET   	PWM1AOE
   	   	   	   	GOTO   	GET_STATE_EXIT
WK0_STG_CHK:
   	   	   	   	JBCLR  	STG1,0
   	   	   	   	GOTO   	STOP_PWMA
   	   	   	   	BCLR   	C
   	   	   	   	RRR	   	STG1
   	   	   	   	JBCLR  	STG1,0
   	   	   	   	GOTO   	A_STG1
   	   	   	   	JBCLR  	STG1,1
   	   	   	   	GOTO   	A_STG2
   	   	   	   	JBCLR  	STG1,2
   	   	   	   	GOTO   	A_STG3
   	   	   	   	GOTO   	STOP_PWMA
A_STG1:
   	   	   	   	MOVAI  	75
   	   	   	   	MOVRA  	T1DATA
   	   	   	   	GOTO   	GET_STATE_EXIT
A_STG2:
   	   	   	   	MOVAI  	20
   	   	   	   	MOVRA  	T1DATA
   	   	   	   	GOTO   	GET_STATE_EXIT
K1_HLD_CHK:
   	   	   	   	JBSET  	F_H1
   	   	   	   	GOTO   	K2_PRS_CHK
   	   	   	   	JBCLR  	F_ACTED
   	   	   	   	GOTO   	K2_PRS_CHK
   	   	   	   	BSET   	F_ACTED
STOP_PWMA:
   	   	   	   	BCLR   	F_WK0
   	   	   	   	CLRR   	STG1
   	   	   	   	BCLR   	PWM1AOE
   	   	   	   	BCLR   	P_PWMA
   	   	   	   	JBCLR  	F_WK1
   	   	   	   	GOTO   	GET_STATE_EXIT
   	   	   	   	MOVAI  	102
   	   	   	   	MOVRA  	DLY1
   	   	   	   	GOTO   	GET_STATE_EXIT
K2_PRS_CHK:
   	   	   	   	JBSET  	F_T2
   	   	   	   	GOTO   	K2_HLD_CHK
   	   	   	   	BCLR   	F_T2
   	   	   	   	JBCLR  	F_WK1
   	   	   	   	GOTO   	WK1_STG_CHK
B_STG5:	;白灯亮
   	   	   	   	BSET   	F_WK1
   	   	   	   	BCLR   	F_NO_WK
   	   	   	   	BCLR   	F_WK1_1
   	   	   	   	MOVAR  	T1LOAD
   	   	   	   	MOVRA  	T1DATB
   	   	   	   	BCLR   	PWM1COE
   	   	   	   	BCLR   	P_PWMC
   	   	   	   	MOVAI  	00010000B
   	   	   	   	MOVRA  	STG2
   	   	   	   	BSET   	PWM1BOE
   	   	   	   	GOTO   	GET_STATE_EXIT
WK1_STG_CHK:
   	   	   	   	JBCLR  	STG2,0
   	   	   	   	GOTO   	STOP_PWMBC
   	   	   	   	BCLR   	C
   	   	   	   	RRR	   	STG2
   	   	   	   	JBCLR  	STG2,0
   	   	   	   	GOTO   	B_STG1
   	   	   	   	JBCLR  	STG2,1
   	   	   	   	GOTO   	B_STG2
   	   	   	   	JBCLR  	STG2,2
   	   	   	   	GOTO   	B_STG3
   	   	   	   	JBCLR  	STG2,3
   	   	   	   	GOTO   	B_STG4
   	   	   	   	JBCLR  	STG2,4
   	   	   	   	GOTO   	B_STG5
   	   	   	   	GOTO   	STOP_PWMBC
B_STG1:;红灯亮
   	   	   	   	BCLR   	PWM1BOE
   	   	   	   	BCLR   	P_PWMB
   	   	   	   	MOVAI  	64
   	   	   	   	MOVRA  	T1DATC
   	   	   	   	BSET   	PWM1COE
   	   	   	   	GOTO   	GET_STATE_EXIT
B_STG2:;红灯快闪
   	   	   	   	BCLR   	PWM1BOE
   	   	   	   	BCLR   	P_PWMB
   	   	   	   	MOVAI  	64
   	   	   	   	MOVRA  	T1DATC
   	   	   	   	CLRR   	TM_CNT
   	   	   	   	CLRR   	KEY_CNT
   	   	   	   	BCLR   	F_INC_EN
   	   	   	   	BSET   	PWM1COE
   	   	   	   	GOTO   	GET_STATE_EXIT
B_STG3:;红灯SOS
   	   	   	   	BCLR   	PWM1BOE
   	   	   	   	BCLR   	P_PWMB
   	   	   	   	MOVAI  	01
   	   	   	   	MOVRA  	T1DATC
   	   	   	   	MOVRA  	DUTY_BK
   	   	   	   	BSET   	F_UP
   	   	   	   	CLRR   	KEY_CNT
   	   	   	   	BCLR   	F_INC_EN
   	   	   	   	BSET   	PWM1COE
   	   	   	   	GOTO   	GET_STATE_EXIT
B_STG4:;白灯暗
   	   	   	   	BCLR   	PWM1COE
   	   	   	   	BCLR   	P_PWMC
   	   	   	   	MOVAI  	50
   	   	   	   	MOVRA  	T1DATB
   	   	   	   	BSET   	PWM1BOE
   	   	   	   	GOTO   	GET_STATE_EXIT
K2_HLD_CHK:
   	   	   	   	JBSET  	F_H2
   	   	   	   	GOTO   	K3_PRS_CHK
   	   	   	   	JBCLR  	F_ACTED
   	   	   	   	GOTO   	K3_PRS_CHK
   	   	   	   	BSET   	F_ACTED
STOP_PWMBC:
   	   	   	   	BCLR   	F_WK1
   	   	   	   	CLRR   	STG2
   	   	   	   	BCLR   	PWM1BOE
   	   	   	   	BCLR   	P_PWMB
   	   	   	   	BCLR   	PWM1COE
   	   	   	   	BCLR   	P_PWMC
   	   	   	   	JBCLR  	F_WK0
   	   	   	   	GOTO   	GET_STATE_EXIT
   	   	   	   	MOVAI  	102
   	   	   	   	MOVRA  	DLY1
   	   	   	   	GOTO   	GET_STATE_EXIT
K3_PRS_CHK:
   	   	   	   	JBSET  	F_T3
   	   	   	   	GOTO   	GET_STATE_EXIT
   	   	   	   	BCLR   	F_T3
   	   	   	   	BSET   	F_WK2
   	   	   	   	MOVAI  	102
   	   	   	   	MOVRA  	DLY2
GET_STATE_EXIT:
   	   	   	   	RETURN
;=======================================
OUTPUT:
   	   	   	   	CLRWDT
WK0_CHK:
   	   	   	   	JBSET  	F_WK0
   	   	   	   	GOTO   	WK0_STOP
   	   	   	   	BSET   	P_SLED
   	   	   	   	BSET   	P_PSW3
   	   	   	   	GOTO   	WK1_CHK
WK0_STOP:
   	   	   	   	BCLR   	PWM1AOE
   	   	   	   	BCLR   	P_PWMA
   	   	   	   	BCLR   	P_SLED
   	   	   	   	JBSET  	F_WK1
   	   	   	   	BCLR   	P_PSW3
WK1_CHK:
   	   	   	   	JBSET  	F_WK1
   	   	   	   	GOTO   	WK1_STOP
   	   	   	   	BSET   	P_RLED
   	   	   	   	BSET   	P_PSW3
   	   	   	   	JBCLR  	STG2,1
   	   	   	   	GOTO   	WK1_STG1
   	   	   	   	JBCLR  	STG2,2
   	   	   	   	GOTO   	WK1_STG2
   	   	   	   	GOTO   	WK2_CHK
WK1_STG1:
   	   	   	   	JBSET  	F_INC_EN
   	   	   	   	GOTO   	WK2_CHK
   	   	   	   	BCLR   	F_INC_EN
   	   	   	   	INCR   	TM_CNT
   	   	   	   	MOVAI  	31
   	   	   	   	RSUBAR 	TM_CNT
   	   	   	   	JBSET  	C
   	   	   	   	GOTO   	WK1_STG1_1
   	   	   	   	BCLR   	PWM1COE
   	   	   	   	BCLR   	P_PWMC
   	   	   	   	MOVAI  	61
   	   	   	   	RSUBAR 	TM_CNT
   	   	   	   	JBSET  	C
   	   	   	   	GOTO   	WK2_CHK
   	   	   	   	CLRR   	TM_CNT
WK1_STG1_1:
   	   	   	   	BSET   	PWM1COE
   	   	   	   	GOTO   	WK2_CHK
WK1_STG2:
   	   	   	   	JBSET  	F_INC_EN
   	   	   	   	GOTO   	WK2_CHK
   	   	   	   	BCLR   	F_INC_EN
   	   	   	   	JBSET  	F_UP
   	   	   	   	GOTO   	WK1_STG2_DEC
   	   	   	   	MOVAI  	2
   	   	   	   	ADDRA  	DUTY_BK
   	   	   	   	MOVAI  	125
   	   	   	   	RSUBAR 	DUTY_BK
   	   	   	   	JBCLR  	C  	
   	   	   	   	BCLR   	F_UP
   	   	   	   	GOTO   	WK1_STG2_COM
WK1_STG2_DEC:
   	   	   	   	MOVAI  	2
   	   	   	   	RSUBAR 	DUTY_BK
   	   	   	   	JBCLR  	C
   	   	   	   	GOTO   	WK1_STG2_DECPRO
   	   	   	   	BSET   	F_UP
   	   	   	   	MOVAI  	2
   	   	   	   	MOVRA  	DUTY_BK
   	   	   	   	GOTO   	WK1_STG2_COM
WK1_STG2_DECPRO:
   	   	   	   	MOVAI  	2
   	   	   	   	RSUBRA 	DUTY_BK
WK1_STG2_COM:
   	   	   	   	MOVAR  	DUTY_BK
   	   	   	   	MOVRA  	T1DATC
   	   	   	   	GOTO   	WK2_CHK
WK1_STOP:
   	   	   	   	BCLR   	PWM1BOE
   	   	   	   	BCLR   	PWM1COE
   	   	   	   	BCLR   	P_PWMB
   	   	   	   	BCLR   	P_PWMC
   	   	   	   	BCLR   	P_RLED
   	   	   	   	JBSET  	F_WK0
   	   	   	   	BCLR   	P_PSW3
WK2_CHK:
   	   	   	   	MOVAR  	DLY2
   	   	   	   	XORAI  	0
   	   	   	   	JBSET  	Z
   	   	   	   	GOTO   	WK2_1
   	   	   	   	BCLR   	P_KLED
   	   	   	   	GOTO   	OUTPUT_EXIT
WK2_1:
   	   	   	   	BSET   	P_KLED
OUTPUT_EXIT:
   	   	   	   	RETURN
;=======================================
HDWARE_INITIAL:
   	   	   	   	MOVAI  	00111000B
   	   	   	   	MOVRA  	DDR1
   	   	   	   	MOVAI  	0X00
   	   	   	   	MOVRA  	DDR0
   	   	   	   	MOVRA  	P0
   	   	   	   	MOVRA  	P1
   	   	   	   	MOVRA  	ODCON
   	   	   	   	MOVAI  	0XFF
   	   	   	   	MOVRA  	PUDCON
   	   	   	   	MOVAI  	11100111B
   	   	   	   	MOVRA  	PUCON
   	   	   	   	MOVAI  	10000000B
   	   	   	   	MOVRA  	MCR
   	   	   	   	MOVAI  	00000101B
   	   	   	   	MOVRA  	T0CR
   	   	   	   	MOVAI  	00000000B
   	   	   	   	MOVRA  	CMPCR
   	   	   	   	MOVRA  	TM0CR
   	   	   	   	MOVRA  	T0CNT
   	   	   	   	MOVRA  	P0KBCR
   	   	   	   	MOVRA  	INTF
   	   	   	   	MOVRA  	INTF1
   	   	   	   	MOVAI  	00111000B
   	   	   	   	MOVRA  	P1KBCR
   	   	   	   	MOVAI  	0X00
   	   	   	   	MOVRA  	INTE
   	   	   	   	MOVAI  	01000010B
   	   	   	   	MOVRA  	T1CR
   	   	   	   	MOVAI  	125
   	   	   	   	MOVRA  	T1CNT
   	   	   	   	MOVRA  	T1LOAD
   	   	   	   	MOVAI  	64
   	   	   	   	MOVRA  	T1DATA
   	   	   	   	MOVRA  	T1DATB
   	   	   	   	MOVRA  	T1DATC
   	   	   	   	MOVAI  	0
   	   	   	   	MOVRA  	T1DATD
   	   	   	   	MOVRA  	PWMCR1
   	   	   	   	MOVAI  	00000011B
   	   	   	   	MOVRA  	PWMCR0
   	   	   	   	
   	   	   	   	RETURN
;=======================================
RAM_CLR:
   	   	   	   	MOVAI  	0X10
   	   	   	   	MOVRA  	FSR
RM_CLR_LP:
   	   	   	   	CLRWDT
   	   	   	   	CLRR   	INDF
   	   	   	   	INCR   	FSR
   	   	   	   	MOVAR  	FSR
   	   	   	   	XORAI  	0X40
   	   	   	   	JBSET  	Z
   	   	   	   	GOTO   	RM_CLR_LP
   	   	   	   	RETURN
;=======================================
USR_INITIAL:
   	   	   	   	MOVAI  	122
   	   	   	   	MOVRA  	HALT_CNT
   	   	   	   	BSET   	T1EN
   	   	   	   	BSET   	GIE
   	   	   	   	RETURN
;=======================================
   	   	   	   	END
