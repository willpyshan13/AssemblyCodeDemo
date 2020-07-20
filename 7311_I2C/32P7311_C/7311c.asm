;--------------------------------------------------------
; File Created by SN-SDCC : ANSI-C Compiler
; Version 0.0.4 (Apr 28 2016) (MINGW32)
; This file was generated Thu Dec 08 17:32:23 2016
;--------------------------------------------------------
; MC3X port for the RISC core
;--------------------------------------------------------
;	.file	"7311c.c"
	list	p=7311
	radix dec
	include "7311.inc"
;--------------------------------------------------------
; external declarations
;--------------------------------------------------------
	extern	_I2C_Delay10us
	extern	_Delay10ms
	extern	_INDF0bits
	extern	_INDF1bits
	extern	_INDF2bits
	extern	_HIBYTEbits
	extern	_FSR0bits
	extern	_FSR1bits
	extern	_PCLbits
	extern	_STATUSbits
	extern	_MCRbits
	extern	_INDF3bits
	extern	_INTEbits
	extern	_INTFbits
	extern	_DRVCRbits
	extern	_KBCRbits
	extern	_IOP0bits
	extern	_OEP0bits
	extern	_PUP0bits
	extern	_PDP0bits
	extern	_IOP1bits
	extern	_OEP1bits
	extern	_PUP1bits
	extern	_PDP1bits
	extern	_T0CRbits
	extern	_T0CNTbits
	extern	_T0LOADbits
	extern	_T0DATAbits
	extern	_T1CRbits
	extern	_T1CNTbits
	extern	_T1LOADbits
	extern	_T1DATAbits
	extern	_T2CRbits
	extern	_T2CNTbits
	extern	_T2LOADbits
	extern	_T2DATAbits
	extern	_T3CRbits
	extern	_T3CNTbits
	extern	_T3LOADbits
	extern	_PWM0DEbits
	extern	_PWM1DEbits
	extern	_OPCR0bits
	extern	_PWMCR0bits
	extern	_PWMCR1bits
	extern	_OSCMbits
	extern	_LVDCRbits
	extern	_ADCR0bits
	extern	_ADCR1bits
	extern	_ADCR2bits
	extern	_ADRHbits
	extern	_ADRLbits
	extern	_ANSEL0bits
	extern	_ANSEL1bits
	extern	_VBGCALbits
	extern	_OSCCALLbits
	extern	_OSCCALHbits
	extern	_INDF
	extern	_INDF0
	extern	_INDF1
	extern	_INDF2
	extern	_HIBYTE
	extern	_FSR
	extern	_FSR0
	extern	_FSR1
	extern	_PCL
	extern	_STATUS
	extern	_PFLAG
	extern	_MCR
	extern	_INDF3
	extern	_INTE
	extern	_INTF
	extern	_DRVCR
	extern	_KBCR
	extern	_IOP0
	extern	_OEP0
	extern	_PUP0
	extern	_PDP0
	extern	_IOP1
	extern	_OEP1
	extern	_PUP1
	extern	_PDP1
	extern	_T0CR
	extern	_T0CNT
	extern	_T0LOAD
	extern	_T0DATA
	extern	_T1CR
	extern	_T1CNT
	extern	_T1LOAD
	extern	_T1DATA
	extern	_T2CR
	extern	_T2CNT
	extern	_T2LOAD
	extern	_T2DATA
	extern	_T3CR
	extern	_T3CNT
	extern	_T3LOAD
	extern	_PWM0DE
	extern	_PWM1DE
	extern	_PWM2DE
	extern	_PWMCR0
	extern	_PWMCR1
	extern	_OSCM
	extern	_LVDCR
	extern	_ADCR0
	extern	_ADCR1
	extern	_ADCR2
	extern	_ADRH
	extern	_ADRL
	extern	_ANSEL0
	extern	_ANSEL1
	extern	_VBGCAL
	extern	_OSCCALH
	extern	_OSCCALL
;--------------------------------------------------------
; global declarations
;--------------------------------------------------------
	global	_IIC_read_onebyte
	global	_IIC_write_onebyte
	global	_I2C_ReceiveByte
	global	_I2C_SendByte
	global	_I2C_NoAck
	global	_I2C_Ack
	global	_I2C_Stop
	global	_I2C_Start
	global	_I2C_delay
	global	_delay
	global	_InitSub
	global	_RamInit
	global	_IRQInit
	global	_IOPortInit
	global	_URAT_SendData
	global	_main
	global	_int_isr
	global	_pflagtemp
	global	_acctemp
	global	_read_temp
	global	_time_1ms
	global	_m
	global	_Array
	global	_flg
	global	_flg1
	global	_flg2
	global	_flg3
	global	_n

	global STK06
	global STK05
	global STK04
	global STK03
	global STK02
	global STK01
	global STK00

sharebank udata_ovr 0x0000
STK06	res 1
STK05	res 1
STK04	res 1
STK03	res 1
STK02	res 1
STK01	res 1
STK00	res 1

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
UD_7311c_0	udata
_pflagtemp	res	1

UD_7311c_1	udata
_acctemp	res	1

UD_7311c_2	udata
_read_temp	res	1

UD_7311c_3	udata
_time_1ms	res	1

UD_7311c_4	udata
_m	res	1

UD_7311c_5	udata
_Array	res	124

UD_7311c_6	udata
_flg	res	1

UD_7311c_7	udata
_flg1	res	1

UD_7311c_8	udata
_flg2	res	1

UD_7311c_9	udata
_flg3	res	1

;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
UDL_7311c_0	udata
r0x1080	res	1
r0x1081	res	1
r0x1082	res	1
r0x1087	res	1
r0x1088	res	1
r0x1083	res	1
r0x1084	res	1
r0x1085	res	1
r0x1086	res	1
;--------------------------------------------------------
; initialized data
;--------------------------------------------------------

ID_7311c_0	idata
_n
	db	0x00


;@Allocation info for local variables in function 'IOPortInit'
;@IOPortInit RamInit                   Allocated to registers ;size:2
;@IOPortInit InitSub                   Allocated to registers ;size:2
;@IOPortInit IRQInit                   Allocated to registers ;size:2
;@IOPortInit I2C_Delay10us             Allocated to registers ;size:2
;@IOPortInit delay                     Allocated to registers ;size:2
;@IOPortInit I2C_delay                 Allocated to registers ;size:2
;@IOPortInit I2C_Start                 Allocated to registers ;size:2
;@IOPortInit I2C_Stop                  Allocated to registers ;size:2
;@IOPortInit I2C_Ack                   Allocated to registers ;size:2
;@IOPortInit I2C_NoAck                 Allocated to registers ;size:2
;@IOPortInit I2C_SendByte              Allocated to registers ;size:2
;@IOPortInit I2C_ReceiveByte           Allocated to registers ;size:2
;@IOPortInit IIC_write_onebyte         Allocated to registers ;size:2
;@IOPortInit IIC_read_onebyte          Allocated to registers ;size:2
;@IOPortInit Delay10ms                 Allocated to registers ;size:2
;@IOPortInit INDF0bits                 Allocated to registers ;size:1
;@IOPortInit INDF1bits                 Allocated to registers ;size:1
;@IOPortInit INDF2bits                 Allocated to registers ;size:1
;@IOPortInit HIBYTEbits                Allocated to registers ;size:1
;@IOPortInit FSR0bits                  Allocated to registers ;size:1
;@IOPortInit FSR1bits                  Allocated to registers ;size:1
;@IOPortInit PCLbits                   Allocated to registers ;size:1
;@IOPortInit STATUSbits                Allocated to registers ;size:1
;@IOPortInit MCRbits                   Allocated to registers ;size:1
;@IOPortInit INDF3bits                 Allocated to registers ;size:1
;@IOPortInit INTEbits                  Allocated to registers ;size:1
;@IOPortInit INTFbits                  Allocated to registers ;size:1
;@IOPortInit DRVCRbits                 Allocated to registers ;size:1
;@IOPortInit KBCRbits                  Allocated to registers ;size:1
;@IOPortInit IOP0bits                  Allocated to registers ;size:1
;@IOPortInit OEP0bits                  Allocated to registers ;size:1
;@IOPortInit PUP0bits                  Allocated to registers ;size:1
;@IOPortInit PDP0bits                  Allocated to registers ;size:1
;@IOPortInit IOP1bits                  Allocated to registers ;size:1
;@IOPortInit OEP1bits                  Allocated to registers ;size:1
;@IOPortInit PUP1bits                  Allocated to registers ;size:1
;@IOPortInit PDP1bits                  Allocated to registers ;size:1
;@IOPortInit T0CRbits                  Allocated to registers ;size:1
;@IOPortInit T0CNTbits                 Allocated to registers ;size:1
;@IOPortInit T0LOADbits                Allocated to registers ;size:1
;@IOPortInit T0DATAbits                Allocated to registers ;size:1
;@IOPortInit T1CRbits                  Allocated to registers ;size:1
;@IOPortInit T1CNTbits                 Allocated to registers ;size:1
;@IOPortInit T1LOADbits                Allocated to registers ;size:1
;@IOPortInit T1DATAbits                Allocated to registers ;size:1
;@IOPortInit T2CRbits                  Allocated to registers ;size:1
;@IOPortInit T2CNTbits                 Allocated to registers ;size:1
;@IOPortInit T2LOADbits                Allocated to registers ;size:1
;@IOPortInit T2DATAbits                Allocated to registers ;size:1
;@IOPortInit T3CRbits                  Allocated to registers ;size:1
;@IOPortInit T3CNTbits                 Allocated to registers ;size:1
;@IOPortInit T3LOADbits                Allocated to registers ;size:1
;@IOPortInit PWM0DEbits                Allocated to registers ;size:1
;@IOPortInit PWM1DEbits                Allocated to registers ;size:1
;@IOPortInit OPCR0bits                 Allocated to registers ;size:1
;@IOPortInit PWMCR0bits                Allocated to registers ;size:1
;@IOPortInit PWMCR1bits                Allocated to registers ;size:1
;@IOPortInit OSCMbits                  Allocated to registers ;size:1
;@IOPortInit LVDCRbits                 Allocated to registers ;size:1
;@IOPortInit ADCR0bits                 Allocated to registers ;size:1
;@IOPortInit ADCR1bits                 Allocated to registers ;size:1
;@IOPortInit ADCR2bits                 Allocated to registers ;size:1
;@IOPortInit ADRHbits                  Allocated to registers ;size:1
;@IOPortInit ADRLbits                  Allocated to registers ;size:1
;@IOPortInit ANSEL0bits                Allocated to registers ;size:1
;@IOPortInit ANSEL1bits                Allocated to registers ;size:1
;@IOPortInit VBGCALbits                Allocated to registers ;size:1
;@IOPortInit OSCCALLbits               Allocated to registers ;size:1
;@IOPortInit OSCCALHbits               Allocated to registers ;size:1
;@IOPortInit pflagtemp                 Allocated to registers ;size:1
;@IOPortInit acctemp                   Allocated to registers ;size:1
;@IOPortInit read_temp                 Allocated to registers ;size:1
;@IOPortInit time_1ms                  Allocated to registers ;size:1
;@IOPortInit m                         Allocated to registers ;size:1
;@IOPortInit Array                     Allocated to registers ;size:124
;@IOPortInit flg                       Allocated to registers ;size:1
;@IOPortInit flg1                      Allocated to registers ;size:1
;@IOPortInit flg2                      Allocated to registers ;size:1
;@IOPortInit flg3                      Allocated to registers ;size:1
;@IOPortInit n                         Allocated to registers ;size:1
;@IOPortInit INDF                      Allocated to registers ;size:1
;@IOPortInit INDF0                     Allocated to registers ;size:1
;@IOPortInit INDF1                     Allocated to registers ;size:1
;@IOPortInit INDF2                     Allocated to registers ;size:1
;@IOPortInit HIBYTE                    Allocated to registers ;size:1
;@IOPortInit FSR                       Allocated to registers ;size:1
;@IOPortInit FSR0                      Allocated to registers ;size:1
;@IOPortInit FSR1                      Allocated to registers ;size:1
;@IOPortInit PCL                       Allocated to registers ;size:1
;@IOPortInit STATUS                    Allocated to registers ;size:1
;@IOPortInit PFLAG                     Allocated to registers ;size:1
;@IOPortInit MCR                       Allocated to registers ;size:1
;@IOPortInit INDF3                     Allocated to registers ;size:1
;@IOPortInit INTE                      Allocated to registers ;size:1
;@IOPortInit INTF                      Allocated to registers ;size:1
;@IOPortInit DRVCR                     Allocated to registers ;size:1
;@IOPortInit KBCR                      Allocated to registers ;size:1
;@IOPortInit IOP0                      Allocated to registers ;size:1
;@IOPortInit OEP0                      Allocated to registers ;size:1
;@IOPortInit PUP0                      Allocated to registers ;size:1
;@IOPortInit PDP0                      Allocated to registers ;size:1
;@IOPortInit IOP1                      Allocated to registers ;size:1
;@IOPortInit OEP1                      Allocated to registers ;size:1
;@IOPortInit PUP1                      Allocated to registers ;size:1
;@IOPortInit PDP1                      Allocated to registers ;size:1
;@IOPortInit T0CR                      Allocated to registers ;size:1
;@IOPortInit T0CNT                     Allocated to registers ;size:1
;@IOPortInit T0LOAD                    Allocated to registers ;size:1
;@IOPortInit T0DATA                    Allocated to registers ;size:1
;@IOPortInit T1CR                      Allocated to registers ;size:1
;@IOPortInit T1CNT                     Allocated to registers ;size:1
;@IOPortInit T1LOAD                    Allocated to registers ;size:1
;@IOPortInit T1DATA                    Allocated to registers ;size:1
;@IOPortInit T2CR                      Allocated to registers ;size:1
;@IOPortInit T2CNT                     Allocated to registers ;size:1
;@IOPortInit T2LOAD                    Allocated to registers ;size:1
;@IOPortInit T2DATA                    Allocated to registers ;size:1
;@IOPortInit T3CR                      Allocated to registers ;size:1
;@IOPortInit T3CNT                     Allocated to registers ;size:1
;@IOPortInit T3LOAD                    Allocated to registers ;size:1
;@IOPortInit PWM0DE                    Allocated to registers ;size:1
;@IOPortInit PWM1DE                    Allocated to registers ;size:1
;@IOPortInit PWM2DE                    Allocated to registers ;size:1
;@IOPortInit PWMCR0                    Allocated to registers ;size:1
;@IOPortInit PWMCR1                    Allocated to registers ;size:1
;@IOPortInit OSCM                      Allocated to registers ;size:1
;@IOPortInit LVDCR                     Allocated to registers ;size:1
;@IOPortInit ADCR0                     Allocated to registers ;size:1
;@IOPortInit ADCR1                     Allocated to registers ;size:1
;@IOPortInit ADCR2                     Allocated to registers ;size:1
;@IOPortInit ADRH                      Allocated to registers ;size:1
;@IOPortInit ADRL                      Allocated to registers ;size:1
;@IOPortInit ANSEL0                    Allocated to registers ;size:1
;@IOPortInit ANSEL1                    Allocated to registers ;size:1
;@IOPortInit VBGCAL                    Allocated to registers ;size:1
;@IOPortInit OSCCALH                   Allocated to registers ;size:1
;@IOPortInit OSCCALL                   Allocated to registers ;size:1
;@end Allocation info for local variables in function 'IOPortInit';
;@Allocation info for local variables in function 'IRQInit'
;@end Allocation info for local variables in function 'IRQInit';
;@Allocation info for local variables in function 'RamInit'
;@end Allocation info for local variables in function 'RamInit';
;@Allocation info for local variables in function 'InitSub'
;@end Allocation info for local variables in function 'InitSub';
;@Allocation info for local variables in function 'delay'
;@delay x                         Allocated to registers ;size:1
;@delay a                         Allocated to registers r0x1080 ;size:1
;@delay b                         Allocated to registers r0x1081 ;size:1
;@end Allocation info for local variables in function 'delay';
;@Allocation info for local variables in function 'I2C_delay'
;@I2C_delay i                         Allocated to registers r0x1080 ;size:1
;@end Allocation info for local variables in function 'I2C_delay';
;@Allocation info for local variables in function 'I2C_Start'
;@end Allocation info for local variables in function 'I2C_Start';
;@Allocation info for local variables in function 'I2C_Stop'
;@end Allocation info for local variables in function 'I2C_Stop';
;@Allocation info for local variables in function 'I2C_Ack'
;@end Allocation info for local variables in function 'I2C_Ack';
;@Allocation info for local variables in function 'I2C_NoAck'
;@end Allocation info for local variables in function 'I2C_NoAck';
;@Allocation info for local variables in function 'I2C_SendByte'
;@I2C_SendByte SendByte                  Allocated to registers r0x1081 ;size:1
;@I2C_SendByte i                         Allocated to registers r0x1082 ;size:1
;@end Allocation info for local variables in function 'I2C_SendByte';
;@Allocation info for local variables in function 'I2C_ReceiveByte'
;@I2C_ReceiveByte i                         Allocated to registers r0x1082 ;size:1
;@I2C_ReceiveByte ReceiveByte               Allocated to registers r0x1081 ;size:1
;@end Allocation info for local variables in function 'I2C_ReceiveByte';
;@Allocation info for local variables in function 'IIC_write_onebyte'
;@IIC_write_onebyte write_data                Allocated to registers r0x1088 ;size:1
;@IIC_write_onebyte write_add                 Allocated to registers r0x1087 ;size:1
;@end Allocation info for local variables in function 'IIC_write_onebyte';
;@Allocation info for local variables in function 'IIC_read_onebyte'
;@IIC_read_onebyte read_add                  Allocated to registers r0x1083 ;size:1
;@IIC_read_onebyte i                         Allocated to registers r0x1083 ;size:1
;@end Allocation info for local variables in function 'IIC_read_onebyte';
;@Allocation info for local variables in function 'URAT_SendData'
;@end Allocation info for local variables in function 'URAT_SendData';
;@Allocation info for local variables in function 'main'
;@end Allocation info for local variables in function 'main';
;@Allocation info for local variables in function 'int_isr'
;@end Allocation info for local variables in function 'int_isr';

;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
;	udata_ovr
;--------------------------------------------------------
; reset vector 
;--------------------------------------------------------
STARTUP	code 0x0000
	goto	_main
;--------------------------------------------------------
; interrupt and initialization code
;--------------------------------------------------------
c_interrupt	code	0x8
__sdcc_interrupt
;***
;  pBlock Stats: dbName = I
;***
;entry:  _int_isr	;Function start
; 0 exit points
;; Starting pCode block
_int_isr	;Function start
; 0 exit points
;	.line	289; "7311c.c"	__endasm;
	movra _acctemp
	swapar _PFLAG
	movra _pflagtemp
	
;	.line	291; "7311c.c"	if(T0IF)
	JBSET	_INTFbits,0
	GOTO	_00214_DS_
;	.line	293; "7311c.c"	T0IF=0;
	BCLR	_INTFbits,0
;	.line	294; "7311c.c"	if(++time_1ms >= 40)
	INCR	_time_1ms
;;unsigned compare: left < lit(0x28=40), size=1
	MOVAI	0x28
	RSUBAR	_time_1ms
	JBSET	STATUS,0
	GOTO	_00214_DS_
;;genSkipc:3251: created from rifx:0022608C
;	.line	296; "7311c.c"	time_1ms = 0;
	CLRR	_time_1ms
;	.line	297; "7311c.c"	F_time20ms = 1;
	BSET	_flg,0
_00214_DS_
;	.line	308; "7311c.c"	__endasm;
	swapar _pflagtemp
	movra _PFLAG
	movar _acctemp
	
END_OF_INTERRUPT
	RETIE	

;--------------------------------------------------------
; code
;--------------------------------------------------------
code_7311c	code
;***
;  pBlock Stats: dbName = M
;***
;entry:  _main	;Function start
; 2 exit points
;has an exit
;functions called:
;   _InitSub
;   _delay
;   _IIC_read_onebyte
;   _URAT_SendData
;   _InitSub
;   _delay
;   _IIC_read_onebyte
;   _URAT_SendData
;; Starting pCode block
_main	;Function start
; 2 exit points
;	.line	241; "7311c.c"	SCL28 = 0; 
	BCLR	_IOP1bits,1
;	.line	242; "7311c.c"	GIE = 0;   
	BCLR	_MCRbits,7
;	.line	243; "7311c.c"	InitSub();
	CALL	_InitSub
;	.line	244; "7311c.c"	GIE = 1;
	BSET	_MCRbits,7
;	.line	245; "7311c.c"	SCL28 = 1;
	BSET	_IOP1bits,1
;	.line	247; "7311c.c"	delay(200);
	MOVAI	0xc8
	CALL	_delay
_00204_DS_
;	.line	251; "7311c.c"	if(F_time20ms)
	JBSET	_flg,0
	GOTO	_00200_DS_
;	.line	253; "7311c.c"	F_time20ms = 0;
	BCLR	_flg,0
;	.line	254; "7311c.c"	for(m=0;m<25;m++)
	CLRR	_m
;;unsigned compare: left < lit(0x19=25), size=1
_00206_DS_
	MOVAI	0x19
	RSUBAR	_m
	JBCLR	STATUS,0
	GOTO	_00200_DS_
;;genSkipc:3251: created from rifx:0022608C
;	.line	256; "7311c.c"	IIC_read_onebyte(0x00);
	MOVAI	0x00
	CALL	_IIC_read_onebyte
;	.line	254; "7311c.c"	for(m=0;m<25;m++)
	INCR	_m
	GOTO	_00206_DS_
_00200_DS_
;	.line	260; "7311c.c"	if(!GPIO12_MCU_EN)
	JBCLR	_IOP1bits,3
	GOTO	_00204_DS_
;	.line	262; "7311c.c"	URAT_SendData();
	CALL	_URAT_SendData
	GOTO	_00204_DS_
	RETURN	
; exit point of _main

;***
;  pBlock Stats: dbName = C
;***
;entry:  _URAT_SendData	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
_URAT_SendData	;Function start
; 2 exit points
;	.line	231; "7311c.c"	}
	RETURN	
; exit point of _URAT_SendData

;***
;  pBlock Stats: dbName = C
;***
;entry:  _IIC_read_onebyte	;Function start
; 2 exit points
;has an exit
;functions called:
;   _I2C_Start
;   _I2C_SendByte
;   _I2C_Ack
;   _I2C_SendByte
;   _I2C_Ack
;   _I2C_Start
;   _I2C_SendByte
;   _I2C_Ack
;   _I2C_ReceiveByte
;   _I2C_NoAck
;   _I2C_Ack
;   _I2C_NoAck
;   _I2C_Stop
;   _I2C_Start
;   _I2C_SendByte
;   _I2C_Ack
;   _I2C_SendByte
;   _I2C_Ack
;   _I2C_Start
;   _I2C_SendByte
;   _I2C_Ack
;   _I2C_ReceiveByte
;   _I2C_NoAck
;   _I2C_Ack
;   _I2C_NoAck
;   _I2C_Stop
;4 compiler assigned registers:
;   r0x1083
;   r0x1084
;   r0x1085
;   r0x1086
;; Starting pCode block
_IIC_read_onebyte	;Function start
; 2 exit points
;	.line	186; "7311c.c"	void IIC_read_onebyte(uchar read_add)
	MOVRA	r0x1083
;	.line	191; "7311c.c"	I2C_Start();
	CALL	_I2C_Start
;	.line	192; "7311c.c"	I2C_SendByte(0x2a);       //器件地址
	MOVAI	0x2a
	CALL	_I2C_SendByte
;	.line	193; "7311c.c"	I2C_Ack();
	CALL	_I2C_Ack
;	.line	195; "7311c.c"	I2C_SendByte(read_add);   //设置段内地址 
	MOVAR	r0x1083
	CALL	_I2C_SendByte
;	.line	196; "7311c.c"	I2C_Ack();
	CALL	_I2C_Ack
;	.line	198; "7311c.c"	I2C_Start();
	CALL	_I2C_Start
;	.line	199; "7311c.c"	I2C_SendByte(0x2b); //读命令
	MOVAI	0x2b
	CALL	_I2C_SendByte
;	.line	200; "7311c.c"	I2C_Ack();
	CALL	_I2C_Ack
;	.line	202; "7311c.c"	for(i=0;i<5;i++)
	CLRR	r0x1083
;;unsigned compare: left < lit(0x5=5), size=1
_00187_DS_
	MOVAI	0x05
	RSUBAR	r0x1083
	JBCLR	STATUS,0
	GOTO	_00190_DS_
;;genSkipc:3251: created from rifx:0022608C
;	.line	205; "7311c.c"	Array[i+n] = I2C_ReceiveByte();
	MOVAR	_n
	ADDAR	r0x1083
	MOVRA	r0x1084
	MOVAR	r0x1084
	ADDAI	(_Array + 0)
	MOVRA	r0x1084
	MOVAI	high (_Array + 0)
	JBCLR	STATUS,0
	ADDAI	0x01
	MOVRA	r0x1085
	CALL	_I2C_ReceiveByte
	MOVRA	r0x1086
	MOVAR	r0x1084
	MOVRA	FSR
	BCLR	STATUS,7
	JBCLR	r0x1085,0
	BSET	STATUS,7
	MOVAR	r0x1086
	MOVRA	INDF
;	.line	206; "7311c.c"	if(i == 4)
	MOVAR	r0x1083
	XORAI	0x04
	JBSET	STATUS,2
	GOTO	_00185_DS_
;	.line	208; "7311c.c"	I2C_NoAck();
	CALL	_I2C_NoAck
	GOTO	_00189_DS_
_00185_DS_
;	.line	212; "7311c.c"	I2C_Ack();
	CALL	_I2C_Ack
_00189_DS_
;	.line	202; "7311c.c"	for(i=0;i<5;i++)
	INCR	r0x1083
	GOTO	_00187_DS_
_00190_DS_
;	.line	215; "7311c.c"	n = n+5;
	MOVAI	0x05
	ADDRA	_n
;	.line	220; "7311c.c"	I2C_NoAck();
	CALL	_I2C_NoAck
;	.line	221; "7311c.c"	I2C_Stop();   
	CALL	_I2C_Stop
	RETURN	
; exit point of _IIC_read_onebyte

;***
;  pBlock Stats: dbName = C
;***
;entry:  _IIC_write_onebyte	;Function start
; 2 exit points
;has an exit
;functions called:
;   _I2C_Start
;   _I2C_SendByte
;   _I2C_Ack
;   _I2C_SendByte
;   _I2C_Ack
;   _I2C_SendByte
;   _I2C_Ack
;   _I2C_Stop
;   _I2C_Start
;   _I2C_SendByte
;   _I2C_Ack
;   _I2C_SendByte
;   _I2C_Ack
;   _I2C_SendByte
;   _I2C_Ack
;   _I2C_Stop
;3 compiler assigned registers:
;   r0x1087
;   STK00
;   r0x1088
;; Starting pCode block
_IIC_write_onebyte	;Function start
; 2 exit points
;	.line	172; "7311c.c"	void IIC_write_onebyte(uchar write_add,uchar write_data)
	MOVRA	r0x1087
	MOVAR	STK00
	MOVRA	r0x1088
;	.line	174; "7311c.c"	I2C_Start();
	CALL	_I2C_Start
;	.line	175; "7311c.c"	I2C_SendByte(0x2a);       //器件地址
	MOVAI	0x2a
	CALL	_I2C_SendByte
;	.line	176; "7311c.c"	I2C_Ack();
	CALL	_I2C_Ack
;	.line	178; "7311c.c"	I2C_SendByte(write_add);  //设置段内地址 
	MOVAR	r0x1087
	CALL	_I2C_SendByte
;	.line	179; "7311c.c"	I2C_Ack();
	CALL	_I2C_Ack
;	.line	181; "7311c.c"	I2C_SendByte(write_data);  //写的数据
	MOVAR	r0x1088
	CALL	_I2C_SendByte
;	.line	182; "7311c.c"	I2C_Ack();
	CALL	_I2C_Ack
;	.line	183; "7311c.c"	I2C_Stop();      
	CALL	_I2C_Stop
	RETURN	
; exit point of _IIC_write_onebyte

;***
;  pBlock Stats: dbName = C
;***
;entry:  _I2C_ReceiveByte	;Function start
; 2 exit points
;has an exit
;functions called:
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;2 compiler assigned registers:
;   r0x1081
;   r0x1082
;; Starting pCode block
_I2C_ReceiveByte	;Function start
; 2 exit points
;	.line	155; "7311c.c"	uchar ReceiveByte=0; 
	CLRR	r0x1081
;	.line	156; "7311c.c"	SDA_H;     	       	           	       	       	  
	BCLR	_OEP1bits,5
;	.line	157; "7311c.c"	for(i=0;i<8;i++)
	CLRR	r0x1082
;;unsigned compare: left < lit(0x8=8), size=1
_00172_DS_
	MOVAI	0x08
	RSUBAR	r0x1082
	JBCLR	STATUS,0
	GOTO	_00175_DS_
;;genSkipc:3251: created from rifx:0022608C
;	.line	159; "7311c.c"	ReceiveByte<<=1;       
	BCLR	STATUS,0
	RLR	r0x1081
;	.line	160; "7311c.c"	SCL_L; 
	BSET	_OEP1bits,6
	BCLR	_IOP1bits,6
;	.line	161; "7311c.c"	I2C_delay(); 
	CALL	_I2C_delay
;	.line	162; "7311c.c"	SCL_H; 	       	       	       	    //在SCL高电平期间读取数据
	BCLR	_OEP1bits,6
;	.line	163; "7311c.c"	I2C_delay();   	       	       	
	CALL	_I2C_delay
;	.line	164; "7311c.c"	if(SDA_read) 
	JBSET	_IOP1bits,5
	GOTO	_00174_DS_
;	.line	165; "7311c.c"	ReceiveByte|=0x01; 
	BSET	r0x1081,0
_00174_DS_
;	.line	157; "7311c.c"	for(i=0;i<8;i++)
	INCR	r0x1082
	GOTO	_00172_DS_
_00175_DS_
;	.line	168; "7311c.c"	SCL_L;     	       	       	       	   //数据读完后，将SCL拉低，等待下一位数据
	BSET	_OEP1bits,6
	BCLR	_IOP1bits,6
;	.line	169; "7311c.c"	return ReceiveByte; 
	MOVAR	r0x1081
	RETURN	
; exit point of _I2C_ReceiveByte

;***
;  pBlock Stats: dbName = C
;***
;entry:  _I2C_SendByte	;Function start
; 2 exit points
;has an exit
;functions called:
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;2 compiler assigned registers:
;   r0x1081
;   r0x1082
;; Starting pCode block
_I2C_SendByte	;Function start
; 2 exit points
;	.line	130; "7311c.c"	void I2C_SendByte(uchar SendByte) //数据从高位到低位// 
	MOVRA	r0x1081
;	.line	133; "7311c.c"	for(i=0;i<8;i++)
	CLRR	r0x1082
;;unsigned compare: left < lit(0x8=8), size=1
_00162_DS_
	MOVAI	0x08
	RSUBAR	r0x1082
	JBCLR	STATUS,0
	GOTO	_00165_DS_
;;genSkipc:3251: created from rifx:0022608C
;	.line	135; "7311c.c"	SCL_L; 	       	       	  //SCL低电平期间，数据可改变
	BSET	_OEP1bits,6
	BCLR	_IOP1bits,6
;	.line	136; "7311c.c"	I2C_delay(); 
	CALL	_I2C_delay
;	.line	137; "7311c.c"	if((SendByte)&0x80) 
	JBSET	r0x1081,7
	GOTO	_00160_DS_
;	.line	138; "7311c.c"	SDA_H;  
	BCLR	_OEP1bits,5
	GOTO	_00161_DS_
_00160_DS_
;	.line	140; "7311c.c"	SDA_L;    
	BSET	_OEP1bits,5
_00161_DS_
	BCLR	_IOP1bits,5
;	.line	141; "7311c.c"	SendByte<<=1; 
	BCLR	STATUS,0
	RLR	r0x1081
;	.line	142; "7311c.c"	I2C_delay(); 
	CALL	_I2C_delay
;	.line	143; "7311c.c"	SCL_H; 	       	        //把数据送到SDA上后，拉高
	BCLR	_OEP1bits,6
;	.line	144; "7311c.c"	I2C_delay(); 
	CALL	_I2C_delay
;	.line	133; "7311c.c"	for(i=0;i<8;i++)
	INCR	r0x1082
	GOTO	_00162_DS_
_00165_DS_
;	.line	146; "7311c.c"	SCL_L;     	       	       	//数据送出后，SCL拉低
	BSET	_OEP1bits,6
	BCLR	_IOP1bits,6
	RETURN	
; exit point of _I2C_SendByte

;***
;  pBlock Stats: dbName = C
;***
;entry:  _I2C_NoAck	;Function start
; 2 exit points
;has an exit
;functions called:
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;; Starting pCode block
_I2C_NoAck	;Function start
; 2 exit points
;	.line	117; "7311c.c"	SCL_L; 
	BSET	_OEP1bits,6
	BCLR	_IOP1bits,6
;	.line	118; "7311c.c"	I2C_delay(); 
	CALL	_I2C_delay
;	.line	119; "7311c.c"	SDA_H; 
	BCLR	_OEP1bits,5
;	.line	120; "7311c.c"	I2C_delay(); 
	CALL	_I2C_delay
;	.line	121; "7311c.c"	SCL_H; 
	BCLR	_OEP1bits,6
;	.line	122; "7311c.c"	I2C_delay(); 
	CALL	_I2C_delay
;	.line	123; "7311c.c"	SCL_L; 
	BSET	_OEP1bits,6
	BCLR	_IOP1bits,6
;	.line	124; "7311c.c"	I2C_delay(); 
	CALL	_I2C_delay
	RETURN	
; exit point of _I2C_NoAck

;***
;  pBlock Stats: dbName = C
;***
;entry:  _I2C_Ack	;Function start
; 2 exit points
;has an exit
;functions called:
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;; Starting pCode block
_I2C_Ack	;Function start
; 2 exit points
;	.line	103; "7311c.c"	SCL_L; 
	BSET	_OEP1bits,6
	BCLR	_IOP1bits,6
;	.line	104; "7311c.c"	I2C_delay(); 
	CALL	_I2C_delay
;	.line	105; "7311c.c"	SDA_L; 
	BSET	_OEP1bits,5
	BCLR	_IOP1bits,5
;	.line	106; "7311c.c"	I2C_delay(); 
	CALL	_I2C_delay
;	.line	107; "7311c.c"	SCL_H; 
	BCLR	_OEP1bits,6
;	.line	108; "7311c.c"	I2C_delay(); 
	CALL	_I2C_delay
;	.line	109; "7311c.c"	SCL_L; 
	BSET	_OEP1bits,6
	BCLR	_IOP1bits,6
;	.line	110; "7311c.c"	I2C_delay(); 
	CALL	_I2C_delay
	RETURN	
; exit point of _I2C_Ack

;***
;  pBlock Stats: dbName = C
;***
;entry:  _I2C_Stop	;Function start
; 2 exit points
;has an exit
;functions called:
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;; Starting pCode block
_I2C_Stop	;Function start
; 2 exit points
;	.line	89; "7311c.c"	SDA_L;
	BSET	_OEP1bits,5
	BCLR	_IOP1bits,5
;	.line	90; "7311c.c"	I2C_delay(); 
	CALL	_I2C_delay
;	.line	91; "7311c.c"	SCL_H; 
	BCLR	_OEP1bits,6
;	.line	92; "7311c.c"	I2C_delay(); 
	CALL	_I2C_delay
;	.line	93; "7311c.c"	SDA_H; 
	BCLR	_OEP1bits,5
;	.line	94; "7311c.c"	I2C_delay(); 
	CALL	_I2C_delay
;	.line	95; "7311c.c"	SCL_L; 
	BSET	_OEP1bits,6
	BCLR	_IOP1bits,6
;	.line	96; "7311c.c"	I2C_delay();
	CALL	_I2C_delay
	RETURN	
; exit point of _I2C_Stop

;***
;  pBlock Stats: dbName = C
;***
;entry:  _I2C_Start	;Function start
; 2 exit points
;has an exit
;functions called:
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;   _I2C_delay
;; Starting pCode block
_I2C_Start	;Function start
; 2 exit points
;	.line	75; "7311c.c"	SDA_H; 
	BCLR	_OEP1bits,5
;	.line	76; "7311c.c"	I2C_delay();
	CALL	_I2C_delay
;	.line	77; "7311c.c"	SCL_H; 
	BCLR	_OEP1bits,6
;	.line	78; "7311c.c"	I2C_delay();   	  
	CALL	_I2C_delay
;	.line	79; "7311c.c"	SDA_L; 
	BSET	_OEP1bits,5
	BCLR	_IOP1bits,5
;	.line	80; "7311c.c"	I2C_delay();   	       	       	       	       	               	
	CALL	_I2C_delay
;	.line	81; "7311c.c"	SCL_L; 
	BSET	_OEP1bits,6
	BCLR	_IOP1bits,6
;	.line	82; "7311c.c"	I2C_delay();
	CALL	_I2C_delay
	RETURN	
; exit point of _I2C_Start

;***
;  pBlock Stats: dbName = C
;***
;entry:  _I2C_delay	;Function start
; 2 exit points
;has an exit
;1 compiler assigned register :
;   r0x1080
;; Starting pCode block
_I2C_delay	;Function start
; 2 exit points
;	.line	65; "7311c.c"	while(i)  
	MOVAI	0x96
	MOVRA	r0x1080
_00135_DS_
	MOVAI	0x00
	ORAR	r0x1080
	JBCLR	STATUS,2
	GOTO	_00138_DS_
;	.line	67; "7311c.c"	i--;  
	DECR	r0x1080
	GOTO	_00135_DS_
_00138_DS_
	RETURN	
; exit point of _I2C_delay

;***
;  pBlock Stats: dbName = C
;***
;entry:  _delay	;Function start
; 2 exit points
;has an exit
;2 compiler assigned registers:
;   r0x1080
;   r0x1081
;; Starting pCode block
_delay	;Function start
; 2 exit points
;	.line	52; "7311c.c"	void delay(uchar x)
	MOVRA	r0x1080
_00126_DS_
;	.line	55; "7311c.c"	for(a=x;a>0;a--)
	MOVAI	0x00
	ORAR	r0x1080
	JBCLR	STATUS,2
	GOTO	_00130_DS_
;	.line	56; "7311c.c"	for(b=110;b>0;b--);
	MOVAI	0x6e
	MOVRA	r0x1081
_00122_DS_
	MOVAI	0x00
	ORAR	r0x1081
	JBCLR	STATUS,2
	GOTO	_00128_DS_
	DECR	r0x1081
	GOTO	_00122_DS_
_00128_DS_
;	.line	55; "7311c.c"	for(a=x;a>0;a--)
	DECR	r0x1080
	GOTO	_00126_DS_
_00130_DS_
	RETURN	
; exit point of _delay

;***
;  pBlock Stats: dbName = C
;***
;entry:  _InitSub	;Function start
; 2 exit points
;has an exit
;functions called:
;   _RamInit
;   _IOPortInit
;   _IRQInit
;   _RamInit
;   _IOPortInit
;   _IRQInit
;; Starting pCode block
_InitSub	;Function start
; 2 exit points
;	.line	46; "7311c.c"	RamInit();
	CALL	_RamInit
;	.line	47; "7311c.c"	IOPortInit();
	CALL	_IOPortInit
;	.line	48; "7311c.c"	IRQInit();     	  
	CALL	_IRQInit
	RETURN	
; exit point of _InitSub

;***
;  pBlock Stats: dbName = C
;***
;entry:  _RamInit	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
_RamInit	;Function start
; 2 exit points
_00113_DS_
;	.line	37; "7311c.c"	INDF0=0;
	CLRR	_INDF0
;	.line	38; "7311c.c"	++FSR0;
	INCR	_FSR0
;	.line	39; "7311c.c"	if (FSR0)
	MOVAI	0x00
	ORAR	_FSR0
	JBSET	STATUS,2
	GOTO	_00113_DS_
;	.line	41; "7311c.c"	goto RamInit;
	RETURN	
; exit point of _RamInit

;***
;  pBlock Stats: dbName = C
;***
;entry:  _IRQInit	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
_IRQInit	;Function start
; 2 exit points
;	.line	29; "7311c.c"	T0CR = 0xe0;
	MOVAI	0xe0
	MOVRA	_T0CR
;	.line	30; "7311c.c"	T0CNT = 6;
	MOVAI	0x06
	MOVRA	_T0CNT
;	.line	31; "7311c.c"	T0IE = 1;      	       	
	BSET	_INTEbits,0
	RETURN	
; exit point of _IRQInit

;***
;  pBlock Stats: dbName = C
;***
;entry:  _IOPortInit	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
_IOPortInit	;Function start
; 2 exit points
;	.line	21; "7311c.c"	OEP0 = 0;      
	CLRR	_OEP0
;	.line	22; "7311c.c"	OEP1 = 0xf7;      //P1,3设置为输入，其余P1口全为输出
	MOVAI	0xf7
	MOVRA	_OEP1
;	.line	23; "7311c.c"	PUP1 = 0;         
	CLRR	_PUP1
;	.line	24; "7311c.c"	ANSEL0 = 0;
	CLRR	_ANSEL0
;	.line	25; "7311c.c"	ANSEL1 = 0;            	
	CLRR	_ANSEL1
	RETURN	
; exit point of _IOPortInit


;	code size estimation:
;	  243+    0 =   243 instructions (  486 byte)

	end
