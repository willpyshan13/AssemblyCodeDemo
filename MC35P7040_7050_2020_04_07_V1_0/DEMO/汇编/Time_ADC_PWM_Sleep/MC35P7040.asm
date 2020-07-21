;******************************************************************************
;  *   	@MCU   	   	   	   	 : MC35P7040
;  *   	@Create Date         : 2020.01.09
;  *   	@Author/Corporation  : Martin/SinoMCU
;  *   	@����֧��QQȺ   	  : 814641858      
;  *    @����΢�ٷ���̳   	  : http://bbs.sinomcu.com/	 
;  *   	@Copyright           : 2019 SINOMCU Corporation,All Rights Reserved.
;  *----------------------Abstract Description---------------------------------     	
;  	   		P54 1ms��ת,P53���PWM,P00����,P40.P41.VDDAD�ɼ�  
;       	 ����У׼ʵ��Ӧ���Ƕ�ѡһ
;       	 ƫ0   ѡ���У׼
;       	 ƫvdd ѡ����У׼ 
;******************************************************************************

#include "MC35P7040.INC"

cblock 0x0000
r0x0001
timer0_count1:2
flag1
endc

#define	FLAG_TIMER0_5000ms 	flag1,0


        org    	0x0000
        goto   	MAIN   	   	

        org    	0x8
        goto   	INT_ISR	   	;�ж�
   

INT_ISR:
       	push
       	
       	JBSET   T0IF
       	GOTO   	INTER_END
       	JBSET  	T0IE
       	GOTO   	INTER_END
       	BCLR   	T0IF
   	   	MOVAI  	00010000B
   	   	XORRA  	IOP5   	   	    ;  P54Dȡ��

       	JZR    	timer0_count1
   	   	GOTO   	$+3
       	JZR    	(timer0_count1 + 1)
   	   	NOP
       	;timer0_count1 >= 5000
       	MOVAI  	0x13
       	ASUBAR 	(timer0_count1 + 1)
       	JBSET  	C
   	   	GOTO   	INTER_END
   	   	JBSET  	Z
   	   	GOTO   	INTER_END
       	MOVAI  	0x88
       	ASUBAR 	timer0_count1
       	JBSET  	C
       	GOTO   	INTER_END

       	CLRR   	timer0_count1
       	CLRR   	(timer0_count1 + 1)
       	BSET   	FLAG_TIMER0_5000ms
INTER_END:
       	pop
       	
       	RETIE  	

MAIN:
       	CALL   	Sys_Init

MAIN_LOOP:
;*****************AD�ɼ�**********************
   	   	MOVAR  	ADM
   	   	ANDAI  	0xf8   	   	   	
   	   	ORAI   	0x00   	;ͨ��0   	   	P40
   	   	MOVRA  	ADM
   	   	CALL   	ADC_Get_Value  	
   	   	CALL   	ADC_Get_Value  	;�л�ͨ����ȥǰ�����βɼ�
   	   	CALL   	ADC_Get_Value  	;demo��ʾ��ʵ��ʹ�ÿͻ������˲�  	
   	   	MOVAR  	ADM
   	   	ANDAI  	0xf8   	   	   	
   	   	ORAI   	0x01   	;ͨ��1   	   	P41
   	   	MOVRA  	ADM
   	   	CALL   	ADC_Get_Value  	
   	   	CALL   	ADC_Get_Value  	;�л�ͨ����ȥǰ�����βɼ�
   	   	CALL   	ADC_Get_Value  	;demo��ʾ��ʵ��ʹ�ÿͻ������˲� 
   	   	MOVAR  	ADM
   	   	ANDAI  	0xf8  	   	   	
   	   	ORAI   	0x05   	;ͨ��VDD  	
   	   	MOVRA  	ADM
   	   	CALL   	ADC_Get_Value  	
   	   	CALL   	ADC_Get_Value  	;�л�ͨ����ȥǰ�����βɼ�
   	   	CALL   	ADC_Get_Value  	;demo��ʾ��ʵ��ʹ�ÿͻ������˲� 
;*****************����************************
   	   	;5000ms��������
       	JBSET  	FLAG_TIMER0_5000ms
       	GOTO   	MAIN_LOOP
       	BCLR   	FLAG_TIMER0_5000ms
   	  ;    	���߹ر�����
       	BCLR   	GIE
       	BCLR   	ADEN
       	BCLR   	PWM1OE
       	BCLR   	T1EN
       	CLRR   	IOP5
       	nop
       	MOVAI  	0xe7
       	ANDRA  	OSCM
       	BSET   	OSCM,3
       	nop   
       	nop
       	nop	
       	BSET   	GIE
       	BSET   	PWM1OE
       	BSET   	T1EN
   	   	 ; ���Ѻ�������
       	BSET   	ADEN
       	GOTO   	MAIN_LOOP


ADC_Get_Value:
       	BCLR   	ADEOC
       	BSET   	ADSTR
       	JBSET  	ADEOC
       	GOTO   	$-1
       	RETURN 	
    ; exit point of _ADC_Get_Value
    
Sys_Init:
       	BCLR   	GIE
       	CALL   	CLR_RAM
       	CALL   	IO_Init
ADC_ADJ_INIT:
		;        ����У׼ʵ��Ӧ���Ƕ�ѡһ
		;        ƫ0   ѡ���У׼
		;        ƫvdd ѡ����У׼ 
       	CALL   	ADC_Zero_ADJ
       	MOVRA  	r0x0001
       	MOVAR   r0x0001
       	JBSET  	Z
       	GOTO   	ADC_ADJ_INIT   	   	;demo��ʾ ���˴�У׼ʧ��һֱУ׼������ѭ��
   	   	
   ;   	   	CALL   	ADC_Vertex_ADJ
   ;       	MOVRA  	r0x0001
   ;       	MOVAR   r0x0001
   ;       	JBSET  	Z
   ;       	GOTO   	ADC_ADJ_INIT   	   	;demo��ʾ ���˴�У׼ʧ��һֱУ׼������ѭ��

       	CALL   	TIMER0_INT_Init  
       	CALL   	TIMER1_PWM_Init   
       	CALL   	ADC_Init
       	BSET   	GIE
       	RETURN 	
    ; exit point of _Sys_Init
ADC_Vertex_ADJ:
    ;  	����У׼   ADTR[4:0]=0x10
       	MOVAI  	0xd0
       	MOVRA   ADT
       	CLRR   	VREFCR 	;  �ڲ�2V
       	CLRR   	ADR	; 64��Ƶ
       	BSET   	GCHS
       	BSET   	ADEN
       	BCLR   	ADEOC
       	BSET   	ADSTR

       	JBSET  	ADEOC
       	GOTO   	$-1
    ;  ����Ƿ�Ϊ0x0fff
       	MOVAR  	ADB
       	XORAI  	0xff
       	JBSET  	Z
       	GOTO   	ADC_ADJ_VER_ADD
       	MOVAI  	0x0f
       	ANDAR  	ADR
       	XORAI  	0x0f
       	JBSET  	Z
       	GOTO   	ADC_ADJ_VER_ADD

       	MOVAI  	0xe0
       	ANDRA  	ADT

       	MOVAI  	0x0f
       	ORRA   	ADT
       	BCLR   	ADEOC
       	BSET   	ADSTR

       	JBSET  	ADEOC
       	GOTO   	$-1
    ;  	����Ƿ�Ϊ0x0fff
       	MOVAR  	ADB
       	XORAI  	0xff
       	JBSET  	Z
       	GOTO   	ADC_ADJ_VER_DEC
       	MOVAI  	0x0f
       	ANDAR  	ADR
       	XORAI  	0x0f
       	JBSET  	Z
       	GOTO   	ADC_ADJ_VER_DEC

       	MOVAI  	0x3f
       	ANDRA  	ADT	   	   	;����ģʽ
   	   	BCLR   	ADEN
       	MOVAI  	0x00   	   	;PASS
       	GOTO   	ADC_VER_ADJ_END 
ADC_ADJ_VER_DEC:
       	MOVAR  	ADT
       	ANDAI  	0x0f
       	JBCLR  	Z
       	GOTO   	ADC_ADJ_VER_FAIL1
       	DJZR   	ADT
       	NOP	
       	BCLR   	ADEOC
       	BSET   	ADSTR

       	JBSET  	ADEOC
       	GOTO   	$-1
    ;  ����Ƿ�Ϊ0x0fff
       	MOVAR  	ADB
       	XORAI  	0xff
       	JBSET  	Z
       	GOTO   	ADC_ADJ_VER_DEC
       	MOVAI  	0x0f
       	ANDAR  	ADR
       	XORAI  	0x0f
       	JBSET  	Z
       	GOTO   	ADC_ADJ_VER_DEC
    ;   ����ģʽ
       	MOVAI  	0x3f
       	ANDRA  	ADT
   	   	BCLR   	ADEN
       	MOVAI  	0x00   	;PASS
       	GOTO   	ADC_VER_ADJ_END
ADC_ADJ_VER_FAIL1:
   	   	MOVAI  	0x3f
       	ANDRA  	ADT	   	   	;����ģʽ
   	   	BCLR   	ADEN
       	MOVAI  	0x01   	   	   	;FAIL
       	GOTO   	ADC_VER_ADJ_END
ADC_ADJ_VER_ADD:   	
       	MOVAI  	0x0f
       	ANDAR  	ADT
       	XORAI  	0x0f   	   	;�Ƿ�ӵ�0x0f 
       	JBSET  	Z
       	GOTO   	$+2
       	GOTO   	ADC_ADJ_VER_FAIL1

       	MOVAI  	0x01
       	ADDRA  	ADT
       	BCLR   	ADEOC
       	BSET   	ADSTR

       	JBSET  	ADEOC
       	GOTO   	$-1
    ; ����Ƿ�Ϊ0x0fff
       	MOVAR  	ADB
       	XORAI  	0xff
       	JBSET  	Z
       	GOTO   	ADC_ADJ_VER_ADD
       	MOVAI  	0x0f
       	ANDAR  	ADR
       	XORAI  	0x0f
       	JBSET  	Z
       	GOTO   	ADC_ADJ_VER_ADD
 
       	MOVAI  	0x3f   	
   	   	BCLR   	ADEN
       	ANDRA  	ADT	   ;����ģʽ
       	MOVAI  	0x00   ;PASS
ADC_VER_ADJ_END:
       	RETURN 	
    ; exit point of _ADC_Vertex_ADJ
    
ADC_Zero_ADJ:
       	MOVAI  	0x80
       	MOVRA  	ADT	   	;���У׼   ADTR[4:0]=0
       	CLRR   	VREFCR 	    ;�ڲ�2V
       	CLRR   	ADR	   ;64��Ƶ
       	BSET   	GCHS
       	BSET   	ADEN
       	BCLR   	ADEOC
       	BSET   	ADSTR

       	JBSET  	ADEOC
       	GOTO   	$-1
    ;  	����Ƿ�Ϊ0
       	MOVAR   ADB
       	JBSET  	Z
       	GOTO   	ADC_ADJ_ZERO_ADD
       	MOVAR  	ADR
       	ANDAI  	0x0f
       	JBSET  	Z
       	GOTO   	ADC_ADJ_ZERO_ADD
       	MOVAI  	0x1f
       	ORRA   	ADT
       	BCLR   	ADEOC
       	BSET   	ADSTR

       	JBSET  	ADEOC
       	GOTO   	$-1
    ;  	����Ƿ�Ϊ0
       	MOVAR   ADB
       	JBSET  	Z
       	GOTO   	ADC_ADJ_ZERO_DEC
       	MOVAR  	ADR
       	ANDAI  	0x0f
       	JBSET  	Z
       	GOTO   	ADC_ADJ_ZERO_DEC
    ;  ����ģʽ
       	MOVAI  	0x3f
       	ANDRA  	ADT  
   	   	BCLR   	ADEN
       	MOVAI  	0x00   	   	;PASS
       	GOTO   	ADC_ZERO_ADJ_END
ADC_ADJ_ZERO_DEC:
       	MOVAR  	ADT
       	ANDAI  	0x0f
       	JBCLR  	Z
       	GOTO   	ADC_ADJ_ZERO_FAIL1
       	DJZR   	ADT
       	NOP	
       	BCLR   	ADEOC
       	BSET   	ADSTR

       	JBSET  	ADEOC
       	GOTO   	$-1
    ;  ����Ƿ�Ϊ0
       	MOVAR   ADB
       	JBSET  	Z
       	GOTO   	ADC_ADJ_ZERO_DEC
       	MOVAR  	ADR
       	ANDAI  	0x0f
       	JBSET  	Z
       	GOTO   	ADC_ADJ_ZERO_DEC
    ;  	����ģʽ
       	MOVAI  	0x3f
       	ANDRA  	ADT
   	   	BCLR   	ADEN
       	MOVAI  	0x00   	;PASS
       	GOTO   	ADC_ZERO_ADJ_END
ADC_ADJ_ZERO_FAIL1:
   	   	MOVAI  	0x3f
       	ANDRA  	ADT	   	   	;����ģʽ
   	   	BCLR   	ADEN
       	MOVAI  	0x01   	;FAIL
       	GOTO   	ADC_ZERO_ADJ_END
ADC_ADJ_ZERO_ADD:
   	   	MOVAI  	0x0f
       	ANDAR  	ADT
       	XORAI  	0x0f
       	JBSET  	Z
       	GOTO   	$+2
       	GOTO   	ADC_ADJ_ZERO_FAIL1

       	MOVAI  	0x01
       	ADDRA  	ADT
       	BCLR   	ADEOC
       	BSET   	ADSTR

       	JBSET  	ADEOC
       	GOTO   	$-1
    ;  	����Ƿ�Ϊ0
       	MOVAR   ADB
       	JBSET  	Z
       	GOTO   	ADC_ADJ_ZERO_ADD
       	MOVAR  	ADR
       	ANDAI  	0x0f
       	JBSET  	Z
       	GOTO   	ADC_ADJ_ZERO_ADD
    ;   ����ģʽ
       	MOVAI  	0x3f
       	ANDRA  	ADT
   	   	BCLR   	ADEN
       	MOVAI  	0x00   	;PASS
ADC_ZERO_ADJ_END:
       	RETURN 	
    ; exit point of _ADC_Zero_ADJ
    
ADC_Init:
       	CLRR   	ADM
       	MOVAI  	0x90
       	ORRA   	ADM
       	CLRR   	VREFCR 	    ;  	�ڲ�2V
       	CLRR   	ADR	    ;   adcʱ��  Fcpu/64
       	RETURN 	
    ; exit point of _ADC_Init
TIMER1_PWM_Init:
       	MOVAI  	0xf1
       	MOVRA  	T1CR
    ;  ����T1    1��Ƶ  T1CLK�ڲ�ʱ��  ����PWM  256������
       	MOVAI  	0x80
       	MOVRA  	T1LDR
       	RETURN 	
    ; exit point of _TIMER1_PWM_Init 
TIMER0_INT_Init:
    ; T1CLK=FCPU/2      T0CLK=FCPU/2    �ر�T0�������
       	CLRR   	TMRCR
    ; ����T0    32��Ƶ  T0CLK�ڲ�ʱ��  �Զ�����  �ر�PWM
       	MOVAI  	0xa4
       	MOVRA  	T0CR
       	MOVAI  	0x83
       	MOVRA  	T0CNT
       	MOVAI  	0x83
       	MOVRA  	T0LDR  	   	;  1ms
       	BSET   	T0IE
       	RETURN 	
    ; exit point of _TIMER0_INT_Init
    
IO_Init:
       	CLRR   	IOP0    
       	MOVAI  	0xfe
       	MOVRA  	OEP0   	   	;  io�ڷ��� 1:out  0:in
       	MOVAI  	0x01
       	MOVRA  	PUP0   	   	; io����������   1:enable  0:disable
       	CLRR   	IOP4
       	MOVAI  	0xfc
       	MOVRA  	OEP4   	   	;  io�ڷ��� 1:out  0:in
       	CLRR   	PUP4   	   	; io����������   1:enable  0:disable
       	CLRR   	IOP5   
       	MOVAI  	0xff
       	MOVRA  	OEP5   	   	; io�ڷ��� 1:out  0:in
       	CLRR   	PUP5       	; io����������   1:enable  0:disable
       	MOVAI  	0x03
       	MOVRA  	P4CON  	   	; P40 P41ģ��
       	RETURN 	
    ; exit point of _IO_Init
CLR_RAM:
       	movai  	0x3F
       	movra  	FSR0
       	clrr   	FSR1
       	clrr   	INDF
       	DJZR   	FSR0
       	goto   	$ -2
       	clrr   	INDF
       	RETURN 	
    ; exit point of _CLR_RAM
    
    
       	end


