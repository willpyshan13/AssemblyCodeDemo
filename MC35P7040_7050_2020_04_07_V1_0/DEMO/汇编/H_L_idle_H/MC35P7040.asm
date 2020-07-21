;******************************************************************************
;  *   	@MCU   	   	   	   	 : MC35P7040
;  *   	@Create Date         : 2020.01.09
;  *   	@Author/Corporation  : Martin/SinoMCU
;  *   	@����֧��QQȺ   	  : 814641858      
;  *    @����΢�ٷ���̳   	  : http://bbs.sinomcu.com/	 
;  *   	@Copyright           : 2019 SINOMCU Corporation,All Rights Reserved.
;  *----------------------Abstract Description---------------------------------    	
;  *            ��Ƶ-��Ƶ-����ģʽ-��Ƶ-��Ƶ-IO��ת 2S T0����һ�Σ�  
;                P01��ת200�����
;                P54D 2S��ת
;                ģʽ�л��ɸ��������ֲ� ģʽ�л�ʾ��ͼ �޸ģ�
;******************************************************************************
#include "MC35P7040.INC"

num	EQU	0x00

   	ORG     0x0000
   	goto   	MAIN
    ORG     0x08
INT_ISR:
   	push
   	JBSET  	T0IF
   	GOTO   	TIMER0_END
   	JBSET  	T0IE
   	GOTO   	TIMER0_END
   	BCLR   	T0IF
    MOVAI  	00010000B
   	XORRA  	IOP5   	   	    ;  P54Dȡ�� 	
TIMER0_END:
   	pop
   	RETIE  	

MAIN:
   	CALL   	Sys_Init
MAIN_LOOP:
   	BCLR   	ADEN    ;�ر�����  
   	BSET   	CLKS    ;�л�����Ƶ 4t
   	nop
   	BSET   	HFDE   	   	   	   	   	   
   	MOVAI  	256-125
   	MOVRA  	T0CNT
   	BSET   	T0EN
   	BSET   	T0IE
   	CLRR   	INTF
   	nop
   	nop
   	MOVAI  	0xe7
   	ANDRA  	OSCM
   	BSET   	OSCM,4 ;��ɫģʽ
   	nop
   	nop    	   	  
   	nop
   	BCLR   	T0IE
   	BCLR   	T0EN
   	BCLR   	HFDE    ;�򿪸�Ƶ  (�û��Լ�ѡ��)
   	nop
   	nop
   	BCLR   	CLKS    ;�л�����Ƶ(�û��Լ�ѡ��)
   	BSET   	ADEN    ;������Ӧ������  (�û��Լ�ѡ��)
    CLRR    num
IO_OUT_P01:
    JZR    num
    nop
    MOVAI  	199
    ASUBAR 	num
    JBSET  	C
    GOTO   	MAIN_LOOP 
    MOVAI  	00000010B
   	XORRA  	IOP0   	   	    ;  P01Dȡ��
   	nop
   	nop
   	nop
   	nop
   	nop
   	nop
   	nop
   	nop
   	GOTO   	IO_OUT_P01

Sys_Init:
   	BCLR   	GIE
   	CALL   	CLR_RAM
   	CALL   	IO_Init
   	CALL   	TIMER0_INT_Init  
   	BSET   	GIE
   	RETURN 	
; exit point of _Sys_Init

TIMER0_INT_Init:
   	MOVAI  	0x06
   	MOVRA  	TMRCR   ;T1CLK=FCPU/2      T0CLK=Fosc    ����T0�������
   	MOVAI  	0x04
   	MOVRA  	T0CR   ;����T0    128��Ƶ  T0CLK�ڲ�ʱ��  �Զ�����  �ر�PWM
   	MOVAI  	0x83
   	MOVRA  	T0CNT  ;T0CNT=256-125;
   	MOVAI  	0x83
   	MOVRA  	T0LDR  ;�����Ƶ��   32k/4/128=2s    ��Ƶģʽ�̶�4t
   	RETURN 	
; exit point of _TIMER0_INT_Init

IO_Init:   	
   	CLRR   	IOP0
   	MOVAI  	0xff
   	MOVRA  	OEP0   ;io�ڷ��� 1:out  0:in  
   	MOVAI  	0x00
   	MOVRA  	PUP0   ;io����������   1:enable  0:disable
   	CLRR   	IOP4   ;io������λ
   	MOVAI  	0xff
   	MOVRA  	OEP4   ;io�ڷ��� 1:out  0:in   
   	CLRR   	PUP4   ;io����������   1:enable  0:disable
   	CLRR   	IOP5   ;io������λ
   	MOVAI  	0xff    ;io�ڷ��� 1:out  0:in  
   	MOVRA  	OEP5
   	CLRR   	PUP5   ;io����������   1:enable  0:disable
   	MOVAI  	0xff
   	MOVRA  	P4CON
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
