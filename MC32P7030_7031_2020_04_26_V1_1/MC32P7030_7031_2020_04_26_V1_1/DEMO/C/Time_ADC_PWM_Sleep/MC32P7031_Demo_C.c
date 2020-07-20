/******************************************************************************
;  *   	@MCU   	   	   	   	 : MC32P7031
;  *   	@Create Date         : 2019.12.29
;  *   	@Author/Corporation  : Martin/SinoMCU
;  *   	@技术支持QQ群   	   	  : 814641858      
;  *    @晟矽微官方论坛   	   	  : http://bbs.sinomcu.com/	 
;  *   	@Copyright           : 2019 SINOMCU Corporation,All Rights Reserved.
;  *----------------------Abstract Description---------------------------------
;  *   	   	   	P54 1ms翻转  P53输出PWM  P00唤醒 P40.P41.VDDAD采集

   	   	   	   	注意 7031不能直接读IO某一位
   	   	   	   	   	如 if(P54D==x)
   	   	   	   	   	   	P54D=!P54D;
   	   	   	   	   	改为 将整组IO读出到一个变量
   	   	   	   	   	   	buff=IOP5;
   	   	   	   	   	   	在判断buff某一位
******************************************************************************/

#include "MC32P7031.h"
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
   	OEP4 = 0xfC;  //io口方向 1:out  0:in      	P40  41in
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
   	TXCR = 0x08; //T0时钟 T0 T2 Fcpu  T1 Fhosc 禁止T0唤醒

   	T0CR = 0xD4; //内部 8分频  允许自动重载
   	T0C = 256 - 125;
   	T0D = 256 - 125; //1ms
   	T0IF = 0;
   	T0IE = 1;
}
/************************************************
;  *    @Function Name       : TIMER1_PWM_Init
;  *    @Description         : 
;  *    @IN_Parameter        :
;  *    @Return parameter    :
;  ***********************************************/
void TIMER1_PWM_Init(void)
{
   	T1CR = 0xF1;
   	T1C = 0;
   	T1D = 127;
}
/************************************************
;  *    @Function Name       : ADC_Init
;  *    @Description         : ADC初始化
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/
void ADC_Init(void)
{
   	ANSEL |= 0x03; //P40 1  模拟输入  1 模拟输入  0  IO口
   	ADCR &= 0x00;
   	ADCR |= 0x90;
   	VREF = 0x00; //设置内部参考电压 为2.0V
   	ADRL &= 0x80;
   	ADRL |= 0x20; //adc时钟  Fcpu/16
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
   	TIMER1_PWM_Init();
   	ADC_Init();
   	GIE = 1;
}
/************************************************
;  *    @Function Name       : ADC_Get_Value
;  *    @Description         : ADC单次转换
;  *    @IN_Parameter      	 : CHX  ADC通道
;  *    @Return parameter    : 该通道ADC的值
;  ***********************************************/
uint ADC_Get_Value(uchar CHX)
{
   	u16 ADC_temp_value;

   	ADCR = (ADCR & 0xf8) | CHX; // ADC 使能  AD转换通道开启  通道  CHX

   	if (changl_Num != CHX) //通道切换了  舍去
   	{
   	   	changl_Num = CHX;
   	   	ADEOC = 0;
   	   	ADST = 1; // 开始转换
   	   	while (ADEOC == 0)
   	   	{ // 检查EOC的标志位   等待转换完毕
   	   	}
   	}
   	ADEOC = 0;
   	ADST = 1; // 开始转换
   	while (ADEOC == 0)
   	{ // 检查EOC的标志位   等待转换完毕
   	}
   	ADC_temp_value = ADRH;
   	ADC_temp_value = ADC_temp_value << 4 | (ADRL & 0x0f);

   	return ADC_temp_value; // 获得ADC转换的数据
}
/************************************************
;  *    @Function Name       : ADC_Get_Value_Average
;  *    @Description         : 连续转换
;  *    @IN_Parameter      	 : 通道
;  *    @Return parameter    : 返回ADC的值
;  ***********************************************/
uint ADC_Get_Value_Average(uchar CHX)
{
   	u8 channel = 0;
   	unsigned long int tmpBuff = 0;
   	u16 ADCMAX = 0;
   	u16 ADCMIN = 0xffff;
   	u16 ADC_temp_value;

   	ADCR = (ADCR & 0xf8) | CHX; // ADC 使能  AD转换通道开启  通道  CHX
   	for (channel = 0; channel < 20; channel++)
   	{
   	   	ADEOC = 0;
   	   	ADST = 1; // 开始转换
   	   	while (!ADEOC)
   	   	   	; //等待转换完成
   	   	ADC_temp_value = ADRH;
   	   	ADC_temp_value = ADC_temp_value << 4 | (ADRL & 0x0f);
   	   	if (channel < 2)
   	   	   	continue; //丢弃前两次采样的
   	   	if (ADC_temp_value > ADCMAX)
   	   	   	ADCMAX = ADC_temp_value; //最大
   	   	if (ADC_temp_value < ADCMIN)
   	   	   	ADCMIN = ADC_temp_value; //最小
   	   	tmpBuff += ADC_temp_value;
   	}
   	tmpBuff -= ADCMAX; 	   	   	   	 //去掉一个最大
   	tmpBuff -= ADCMIN; 	   	   	   	 //去掉一个最小
   	ADC_temp_value = (tmpBuff >> 4); //除以16，取平均值
   	return ADC_temp_value;
}
void main(void)
{
   	Sys_Init();
   	while (1)
   	{
   	   	ADC_num_value = ADC_Get_Value_Average(0);
   	   	ADC_num_value = ADC_Get_Value_Average(1);
   	   	ADC_num_value = ADC_Get_Value_Average(5); //VDD/4
   	   	if (FLAG_TIMER0_5000ms)
   	   	{
   	   	   	FLAG_TIMER0_5000ms = 0;
   	   	   	GIE = 0;
   	   	   	ADON = 0;
   	   	   	PWM1OE=0;
   	   	   	TC1EN=0;
   	   	   	IOP5 = 0;   	   	   	//关闭外设
   	   	   	Nop();
   	   	   	Nop();
   	   	   	OSCM &= 0xE7;
   	   	   	OSCM |= 0x08;
   	   	   	Nop();
   	   	   	Nop();
   	   	   	Nop(); 	   	   	
   	   	   	GIE = 1;
   	   	   	PWM1OE=1;
   	   	   	TC1EN=1;
   	   	   	ADON = 1;  	   	//唤醒后开启外设
   	   	}
   	}
}

void int_isr(void) __interrupt
{

   	__asm 
   	push
   	__endasm;
   	//=======T0========================
   	if (T0IF && T0IE)
   	{
   	   	T0IF = 0;
   	   	IO_buff.byte = IOP5;
   	   	IO_BIT4 = !IO_BIT4;
   	   	IOP5 = IO_buff.byte;
   	   	timer0_count1++;
   	   	if (timer0_count1 >= 5000) //5s
   	   	{
   	   	   	timer0_count1 = 0;
   	   	   	FLAG_TIMER0_5000ms = 1;
   	   	}
   	}
   	//=======ADC=======================
   	if (ADIF && ADIE)
   	{
   	   	ADIF = 0;
   	}
   	__asm 
   	pop
   	__endasm;
}
