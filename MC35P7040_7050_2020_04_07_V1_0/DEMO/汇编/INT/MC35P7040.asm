;******************************************************************************
;  *   	@MCU   	   	   	   	 : MC35P7040
;  *   	@Create Date         : 2020.01.09
;  *   	@Author/Corporation  : Martin/SinoMCU
;  *   	@����֧��QQȺ   	  : 814641858      
;  *    @����΢�ٷ���̳   	  : http://bbs.sinomcu.com/	 
;  *   	@Copyright           : 2019 SINOMCU Corporation,All Rights Reserved.
;  *----------------------Abstract Description---------------------------------    	
;  *           P00,P01�������ⲿ�ж��½��ش�����P02��P03��ת��δ��������
;******************************************************************************
#include "MC35P7040.INC"   

    ORG    	0x0000
   	goto   	MAIN
   	ORG	   	0x8

INT_ISR:
   	push
   	JBSET  	INT0IF
   	GOTO   	INT1_INTERR
   	JBSET  	INT0IE
   	GOTO   	INT1_INTERR
   	BCLR   	INT0IF
    MOVAI  	00000100B
   	XORRA  	IOP0   	   	    ;  P02Dȡ��


INT1_INTERR:
   	JBSET  	INT1IF
   	GOTO   	INT_END
   	JBSET  	INT1IE
   	GOTO   	INT_END
   	BCLR   	INT1IF
    MOVAI  	00001000B
   	XORRA  	IOP0   	   	    ;  P03Dȡ��

INT_END:
   	RETIE  	

MAIN:  	
   	CALL   	Sys_Init
MAIN_LOOP:
   	GOTO   	MAIN_LOOP
   	RETURN 	
; exit point of main

Sys_Init:
   	BCLR   	GIE
   	CALL   	CLR_RAM
   	CALL    IO_Init
   	CALL   	INT_Init  
   	BSET   	GIE
   	RETURN 	
; exit point of Sys_Init

INT_Init:  	
   	BSET   	INT0IE
   	BSET   	INT1IE  ;ʹ���ⲿ�ж�
   	MOVAI  	0x10    
   	MOVRA  	EINTCR  ;�½��ش���
   	RETURN 	
; exit point of INT_Init

IO_Init:
   	CLRR   	IOP0    ;io������λ
   	MOVAI  	0xfc
   	MOVRA  	OEP0    ;io�ڷ��� 1:out  0:in  
   	MOVAI  	0x03
   	MOVRA  	PUP0    ;io����������   1:enable  0:disable
   	CLRR   	IOP4    ;io������λ
   	MOVAI  	0xf0
   	MOVRA  	OEP4    ;io�ڷ��� 1:out  0:in   
   	CLRR   	PUP4    ;io����������   1:enable  0:disable
   	CLRR   	IOP5    ;io������λ
   	MOVAI  	0xff
   	MOVRA  	OEP5    ;io�ڷ��� 1:out  0:in  
   	CLRR   	PUP5    ;io����������   1:enable  0:disable
   	MOVAI  	0xff
   	MOVRA  	P4CON
   	RETURN 	
; exit point of IO_Init

CLR_RAM:
   	movai 0x3F
   	movra FSR0
   	clrr FSR1
   	clrr INDF
   	DJZR FSR0
   	goto $-2
   	clrr INDF
   	RETURN 	
; exit point of CLR_RAM


   	end
