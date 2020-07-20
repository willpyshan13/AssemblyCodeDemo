/******************************************************************************
;  *   	@MCU				 : MC32P7031
;  *   	@Create Date         : 2019.12.29
;  *   	@Author/Corporation  : Martin/SinoMCU
;  *   	@技术支持QQ群		  : 814641858      
;  *    @晟矽微官方论坛		  : http://bbs.sinomcu.com/	 
;  *   	@Copyright           : 2019 SINOMCU Corporation,All Rights Reserved.
;  *----------------------Abstract Description---------------------------------
;  *		切换到低速进入绿色模式 1S T0唤醒一次，唤醒后高频模式IO翻转

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
	OEP0 = 0xfE; //io口方向 1:out  0:in
	PUP0 = 0x01; //io口上拉电阻   1:enable  0:disable

	IOP4 = 0x00;  //io口数据位
	OEP4 = 0xfC;  //io口方向 1:out  0:in    	P40  41in
	PUP4 = 0x00;  //io口上拉电阻   1:enable  0:disable
	ANSEL = 0x00; //io类型选择  1:模拟输入  0:通用io

	IOP5 = 0x00; //io口数据位
	OEP5 = 0xff; //io口方向 1:out  0:in
	PUP5 = 0x00; //io口上拉电阻   1:enable  0:disable
}
/************************************************
;  *    @Function Name       : TIMER0_INT_Init
;  *    @Description         : 
;  *    @IN_Parameter        :
;  *    @Return parameter    :
;  ***********************************************/
void TIMER0_INT_Init(void)    	   	
{
   	TXCR=0x0A; 	   	//T0时钟 T0 T2 Fcpu  T1 Fhosc 允许T0唤醒
//T0
   	T0CR=0x24; 	   	   	   	//内部 64分频  允许自动重载
   	T0C=256-125;
   	T0D=256-125;   	   	//1ms
   	T0IF=0; 	
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
	TIMER0_INT_Init();
	GIE = 1;
}
void main(void)
{
	u8 num;
   	Sys_Init();
   	while(1)
   	{
   	   	ADON=0;	   	   	 //关闭外设    	

   	   	CLKS=1;	   	//切换到低频
   	   	Nop();
   	   	HOFF=1;	   	//关闭高频
   	   	//开启唤醒条件(部分在初始化已经配置)
   	   	T0C=256-125;   	   	   	   	   	   	   
   	   	TC0EN=1;
   	   	T0IE=1;

   	   	INTF=0;

       	Nop();
   	   	Nop();
   	   	OSCM&=0xE7;   
		OSCM|=0x10;	  			  	//绿色模式
   	   	Nop();
   	   	Nop();
		Nop();
			  
   	   	T0IE=0;
   	   	TC0EN=0;
       	HOFF=0;	   	//打开高频  (用户自己选择)
   	   	Nop();
   	   	Nop();
       	CLKS=0;	   	//切换到高频	   	(用户自己选择)

   	   	ADON=1;	   	//开启相应的外设  (用户自己选择)
   	   	
   	   	for(num=0;num<100;num++)
   	   	{
   	   	   	IO_buff.byte=IOP5;
       	   	IO_BIT4=!IO_BIT4;
   	   	   	IOP5=IO_buff.byte;
   	   	   	Nop();
   	   	   	Nop();
   	   	   	Nop();
   	   	}
   	}
}
void int_isr(void) __interrupt
{
   	__asm
   	   	push
   	__endasm;
//=======T0========================
    if(T0IF&&T0IE)
   	{
   	   	T0IF=0;
   	}
//=======ADC=======================
   	if(ADIF&&ADIE)
   	{
   	   	ADIF=0;
   	}
   	__asm
   	   	pop
   	__endasm;
}




















