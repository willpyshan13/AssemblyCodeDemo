;******************************************************************************
;  *   	@MCU   	   	   	   	 : MC35P7040
;  *   	@Create Date         : 2020.01.09
;  *   	@Author/Corporation  : Martin/SinoMCU
;  *   	@����֧��QQȺ   	  : 814641858      
;  *    @����΢�ٷ���̳   	  : http://bbs.sinomcu.com/	 
;  *   	@Copyright           : 2019 SINOMCU Corporation,All Rights Reserved.
;  *----------------------Abstract Description---------------------------------      	
;  *            ��¼ʱѡ��LVD3.6V 
;			����3.6VʱLVD36��־��1 P01����ߣ���֮����ͣ�
;			LVD˵����
;					LVD���ֵ����¼ʱ��д�̶���
;					ʹ��ע��LVD���
;******************************************************************************
#include "MC35P7040.INC"   
    
    ORG 	0x0000
	goto	MAIN
	ORG		0x8
INT_ISR:
	push
	;
    ;
	pop
	RETIE	

MAIN:
	CALL	Sys_Init
MAIN_LOOP:
	JBSET	PFLAG,5     ;LVD��¼ѡ��3.6V
	GOTO	VOL_NORMAL
	BSET	P01D
	GOTO	MAIN_LOOP
VOL_NORMAL:
	BCLR	P01D
	GOTO	MAIN_LOOP
; exit point of main

Sys_Init:
	BCLR	GIE
	CALL	CLR_RAM
	CALL	IO_Init        
	BSET	GIE
	RETURN	
; exit point of _Sys_Init

IO_Init:
	CLRR	IOP0   ;io������λ
	MOVAI	0xff
	MOVRA	OEP0   ;io�ڷ��� 1:out  0:in  
	CLRR	PUP0   ;io����������   1:enable  0:disable
	CLRR	IOP4   ;io������λ
	MOVAI	0xff
	MOVRA	OEP4   ;io�ڷ��� 1:out  0:in  
	CLRR	PUP4   ;io����������   1:enable  0:disable
	CLRR	IOP5   ;io������λ
	MOVAI	0xff
	MOVRA	OEP5   ;io�ڷ��� 1:out  0:in  
	CLRR	PUP5   ;io����������   1:enable  0:disable
	MOVAI	0xff
	MOVRA	P4CON
	RETURN	
; exit point of _IO_Init

CLR_RAM:	
	movai 0x3F
	movra FSR0
	clrr FSR1
	clrr INDF
	DJZR FSR0
	goto $-2
	clrr INDF
	RETURN	
; exit point of _CLR_RAM


	end
