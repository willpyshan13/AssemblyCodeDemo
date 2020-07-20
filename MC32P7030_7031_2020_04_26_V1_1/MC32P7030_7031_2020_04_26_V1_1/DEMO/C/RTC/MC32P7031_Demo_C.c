/******************************************************************************
;  *   	@MCU   	   	   	   	 : MC32P7031
;  *   	@Create Date         : 2019.12.29
;  *   	@Author/Corporation  : Martin/SinoMCU
;  *   	@技术支持QQ群   	   	  : 814641858      
;  *    @晟矽微官方论坛   	   	  : http://bbs.sinomcu.com/	 
;  *   	@Copyright           : 2019 SINOMCU Corporation,All Rights Reserved.
;  *----------------------Abstract Description---------------------------------
;  *   	   	   	   	T2RTC模式
   	   	   	   	   	循环进入休眠，1S唤醒，中断P43翻转
   	   	   	   	   	唤醒后P41翻转输出10次

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
;  *    @Description         : 清RAM
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
;  *    @Description         : io口初始化
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/
void IO_Init(void)
{
   	IOP0 = 0x00; //io口数据位
   	OEP0 = 0xFF; //io口方向 1:out  0:in
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
;  *    @Function Name       : Timer2_RTC_Init
;  *    @Description         : T2 RTC模式
;  *    @IN_Parameter      	 :
;  *    @Return parameter    :
;  ***********************************************/
void Timer2_RTC_Init(void)
{
   	T2CR = 0x0C; //128分频 外部32K(RTC) 自动重载
   	T2C = 0;   	 //计数256
   	T2D = 0;
   	TC2EN = 1; //使能 计数器
   	T2IE = 1;  //使能T2中断
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
   	Timer2_RTC_Init();
   	GIE = 1;
}
void main(void)
{
   	u8 count1;
   	Sys_Init();
   	while (1)
   	{
   	   	//休眠前需要关闭外设
   	   	GIE = 0;
   	   	OSCM &= 0xE7;
   	   	OSCM |= 0x08;
   	   	Nop();
   	   	Nop();
   	   	GIE = 1;
   	   	//唤醒后开启外设
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

   	if (T2IF && T2IE) //T2中断
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
