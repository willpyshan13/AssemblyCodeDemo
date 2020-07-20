/******************************************************************************
;  *   	@MCU				 : MC32P7031
;  *   	@Create Date         : 2019.12.29
;  *   	@Author/Corporation  : Martin/SinoMCU
;  *   	@����֧��QQȺ		  : 814641858      
;  *    @����΢�ٷ���̳		  : http://bbs.sinomcu.com/	 
;  *   	@Copyright           : 2019 SINOMCU Corporation,All Rights Reserved.
;  *----------------------Abstract Description---------------------------------
;  *				INT0   P00�½��ش�����P54��תһ��

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
;  *    @Description         : �ϵ���RAM
;  *    @IN_Parameter        :
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
;  *    @Description         : IO��ʼ��
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/
void IO_Init(void)
{
	IOP0 = 0x00; //io������λ
	OEP0 = 0xff; //io�ڷ��� 1:out  0:in
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
;  *    @Function Name       : INT_Init
;  *    @Description         : �ⲿ�ж�
;  *    @IN_Parameter        :
;  *    @Return parameter    :
;  ***********************************************/
void INT_Init(void)
{
	PEDGE &= 0xE7;
	PEDGE |= 0x10; //�½��ش���
	OEP0 = 0xfE;   //in
	PUP0 = 0x01;   //��������

	INT0IF = 0;
	INT0IE = 1; //�ⲿ�ж�ʹ��
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
	INT_Init();
	GIE = 1;
}
void main(void)
{
	Sys_Init();
	while (1)
	{
	}
}

void int_isr(void) __interrupt
{
__asm 
	push
__endasm;
	if ((INT0IF) && (INT0IE))
	{
		INT0IF = 0;
		IO_buff.byte = IOP5; //ÿ�δ���IO��ת
		IO_BIT4 = !IO_BIT4;
		IOP5 = IO_buff.byte;
	}
__asm 
	pop
__endasm;
}
