/******************************************************************************
;  *   	@MCU				 : MC32P7031
;  *   	@Create Date         : 2019.12.29
;  *   	@Author/Corporation  : Martin/SinoMCU
;  *   	@技术支持QQ群		  : 814641858      
;  *    @晟矽微官方论坛		  : http://bbs.sinomcu.com/	 
;  *   	@Copyright           : 2019 SINOMCU Corporation,All Rights Reserved.
;  *----------------------Abstract Description---------------------------------
;  *				INT0   P00下降沿触发，P54翻转一次

					注意 7031不能直接读IO某一位
						如 if(P54D==x)
							P54D=!P54D;
						改为 将整组IO读出到一个变量
							buff=IOP5;
							在判断buff某一位
******************************************************************************/

#include "user.h"

/************************************************
;  *    @Function Name       : CLR_RAM
;  *    @Description         : 上电清RAM
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
;  *    @Description         : IO初始化
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/
void IO_Init(void)
{
	IOP0 = 0x00; //io口数据位
	OEP0 = 0xff; //io口方向 1:out  0:in
	PUP0 = 0x00; //io口上拉电阻   1:enable  0:disable

	IOP4 = 0x00;  //io口数据位
	OEP4 = 0xff;  //io口方向 1:out  0:in
	PUP4 = 0x00;  //io口上拉电阻   1:enable  0:disable
	ANSEL = 0x00; //io类型选择  1:模拟输入  0:通用io

	IOP5 = 0x00; //io口数据位
	OEP5 = 0xff; //io口方向 1:out  0:in
	PUP5 = 0x00; //io口上拉电阻   1:enable  0:disable
}
/************************************************
;  *    @Function Name       : INT_Init
;  *    @Description         : 外部中断
;  *    @IN_Parameter        :
;  *    @Return parameter    :
;  ***********************************************/
void INT_Init(void)
{
	PEDGE &= 0xE7;
	PEDGE |= 0x10; //下降沿触发
	OEP0 = 0xfE;   //in
	PUP0 = 0x01;   //上拉电阻

	INT0IF = 0;
	INT0IE = 1; //外部中断使能
}
/************************************************
;  *    @Function Name       : Sys_Init
;  *    @Description         : 系统初始化
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
		IO_buff.byte = IOP5; //每次触发IO翻转
		IO_BIT4 = !IO_BIT4;
		IOP5 = IO_buff.byte;
	}
__asm 
	pop
__endasm;
}
