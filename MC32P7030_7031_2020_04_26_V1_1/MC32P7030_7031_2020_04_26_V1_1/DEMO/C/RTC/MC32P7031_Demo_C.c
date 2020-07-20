/******************************************************************************
;  *   	@MCU   	   	   	   	 : MC32P7031
;  *   	@Create Date         : 2019.12.29
;  *   	@Author/Corporation  : Martin/SinoMCU
;  *   	@����֧��QQȺ   	   	  : 814641858      
;  *    @����΢�ٷ���̳   	   	  : http://bbs.sinomcu.com/	 
;  *   	@Copyright           : 2019 SINOMCU Corporation,All Rights Reserved.
;  *----------------------Abstract Description---------------------------------
;  *   	   	   	   	T2RTCģʽ
   	   	   	   	   	ѭ���������ߣ�1S���ѣ��ж�P43��ת
   	   	   	   	   	���Ѻ�P41��ת���10��

   	   	   	   	   	ע�� 7031����ֱ�Ӷ�IOĳһλ
   	   	   	   	   	   	�� if(P54D==x)
   	   	   	   	   	   	   	P54D=!P54D;
   	   	   	   	   	   	��Ϊ ������IO������һ������
   	   	   	   	   	   	   	buff=IOP5;
   	   	   	   	   	   	   	���ж�buffĳһλ
******************************************************************************/ 

#include "user.h"

/************************************************
;  *    @Function Name       : CLR_RAM
;  *    @Description         : ��RAM
;  *    @IN_Parameter      	 :
;  *    @Return parameter    :
;  ***********************************************/
void CLR_RAM(void)
{
__asm 
   	movai 0x7F 
   	movra FSR0
   	clrr FSR1
   	clrr INDF
   	DJZR FSR0 
   	goto $ -2 
   	clrr INDF
__endasm;
}
/************************************************
;  *    @Function Name       : IO_Init
;  *    @Description         : io�ڳ�ʼ��
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/
void IO_Init(void)
{
   	IOP0 = 0x00; //io������λ
   	OEP0 = 0xFF; //io�ڷ��� 1:out  0:in
   	PUP0 = 0x00; //io����������   1:enable  0:disable

   	IOP4 = 0x00;  //io������λ
   	OEP4 = 0xff;  //io�ڷ��� 1:out  0:in
   	PUP4 = 0x00;  //io����������   1:enable  0:disable
   	ANSEL = 0x00; //io����ѡ��  1:ģ������  0:ͨ��io

   	IOP5 = 0x00; //io������λ
   	OEP5 = 0xff; //io�ڷ��� 1:out  0:in
   	PUP5 = 0x00; //io����������   1:enable  0:disable
}
/************************************************
;  *    @Function Name       : Timer2_RTC_Init
;  *    @Description         : T2 RTCģʽ
;  *    @IN_Parameter      	 :
;  *    @Return parameter    :
;  ***********************************************/
void Timer2_RTC_Init(void)
{
   	T2CR = 0x0C; //128��Ƶ �ⲿ32K(RTC) �Զ�����
   	T2C = 0;   	 //����256
   	T2D = 0;
   	TC2EN = 1; //ʹ�� ������
   	T2IE = 1;  //ʹ��T2�ж�
}
/************************************************
;  *    @Function Name       : Sys_Init
;  *    @Description         : ϵͳ��ʼ��
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/
void Sys_Init(void)
{
   	GIE = 0;
   	CLR_RAM();
   	IO_Init();
   	Timer2_RTC_Init();
   	GIE = 1;
}
void main(void)
{
   	u8 count1;
   	Sys_Init();
   	while (1)
   	{
   	   	//����ǰ��Ҫ�ر�����
   	   	GIE = 0;
   	   	OSCM &= 0xE7;
   	   	OSCM |= 0x08;
   	   	Nop();
   	   	Nop();
   	   	GIE = 1;
   	   	//���Ѻ�������
   	   	Nop();
   	   	for (count1 = 0; count1 < 10; count1++)
   	   	{
   	   	   	IO_buff.byte = IOP4;
   	   	   	IO_BIT1 = !IO_BIT1;
   	   	   	IOP4 = IO_buff.byte;
   	   	}
   	}
}

void int_isr(void) __interrupt
{
__asm 
   	push
__endasm;

   	if (T2IF && T2IE) //T2�ж�
   	{
   	   	T2IF = 0;
   	   	IO_buff.byte = IOP4;
   	   	IO_BIT3 = !IO_BIT3;
   	   	IOP4 = IO_buff.byte;
   	}
__asm 
   	pop
__endasm;
}
