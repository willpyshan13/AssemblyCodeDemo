
/******************************************************************************
;  *   	@File Name     	     : mc32F7343_main.c
;  *   	@Copyright           : 2018 SINOMCU Corporation,All Rights Reserved.
;  *   	@Module Name         : Standard Demo
;  *   	@MCU       	   	   	 : MC32F7343
 
;  *   	@Create Date         : 2018.06.30
;  *   	@Author/Corporation  : Martin/SinoMCU

;  *   	@Abstract Description: 
;  *   	           	 
;  *---------------------------Revision History---------------------------------   	
;  *   	No  Version  Date              Revised By   Item     Description
;  *    1   V1.0     2018.06.30	   	   	Timer,ADC,UART,ADC_offset,EEPROM,IIC
 
  ******************************************************************************/
#include "IIC.h"
#include "UART.h"
u8 ABuf,StatusBuf;
volatile Flag Flag1;
volatile Flag Flag2;
u8 UART_Buff;
u8 UART_Test;
u16 ADH_temp=0,ADL_temp=0,Data_OSADJCR=0;
u16 ADC_CH0_Value;
u16 ADC_Value;
u8 EEPROM_Num;
u16 Timer0_Num;
/************************************************
;  *    @Function Name       : main
;  *    @Description         : main function
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/  
void main(void)
{
   	InitSys();
   	EEPROM_Num=0x55;
   	EEPROM_Write_Byte(0x01,EEPROM_Num);
   	EEPROM_Num=0;
   	EEPROM_Num=EEPROM_Read_Byte(0x01);
   	while(1)
   	{  	 
   	   	if(Fre_Mode_Flag)
   	   	{
   	   	   	Fre_Mode_Flag=0;
   	   	   	SendString("Sinomcu_Test_code\r\n");
   	   	}  
   	   
   	}
}
/************************************************
;  *    @Function Name       : C_RAM
;  *    @Description         : 清RAM
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    : 
;  ***********************************************/ 
void C_RAM(void)
{
   	for(FSR0=0;FSR0<0xff;FSR0++) 
   	{
   	   	INDF0=0;
   	}
   	FSR0=0xFF;
   	INDF0=0;
   	for(FSR1=0;FSR1<0x7f;FSR1++) 
   	{
   	   	INDF1=0;
   	}
   	FSR1=0x7f;
   	INDF1=0; 
}
/************************************************
;  *    @Function Name       : ADC_Init_ADJ
;  *    @Description         : 每次上电时候调用此函数，可解决AD零点漂移问题
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/  
void  ADC_Init_ADJ(void)
{
   	ADCR0=0xe0;//2V参考电压 通道GND
   	OSADJEN=1;//使能 ADC 零点偏移修调模式
   	ADCR1=0x33;//FHIRC/64,15个ADCLK
   	OSADJCR&=0xc0;//修调值从零开始
 
   	ADEN=1;
   	ADEOC=0;
   	while(!ADEOC);
           	   	   	
   	ADH_temp=ADRH;
   	ADL_temp=ADRL;
   	 
   	if((ADH_temp==0)&&(ADL_temp==0))
   	{
   	   	OSADJCR|=0x3f;
   	   	Data_OSADJCR=OSADJCR&0x1f;
   	   	while(1)
   	   	{
   	   	   	if(Data_OSADJCR==0x00) return;
   	   	   	else
   	   	   	{
   	   	   	   	ADEOC=0;
   	   	   	   	while(!ADEOC);
   	   	   	   	ADH_temp=ADRH;
   	   	   	   	ADL_temp=ADRL;
   	   	   	   	if((ADH_temp==0)&&(ADL_temp==0)) return;
   	   	   	   	else;
   	   	   	}
   	   	   	OSADJCR--;
   	   	   	Data_OSADJCR=OSADJCR&0x1f;
   	   	}
   	}
   	else
   	{
   	   	Data_OSADJCR=OSADJCR&0x1f;
   	   	while(1)
   	   	{
   	   	   	if(Data_OSADJCR==0x1f) return;
   	   	   	else
   	   	   	{
   	   	   	   	ADEOC=0;
   	   	   	   	while(!ADEOC);
   	   	   	   	
   	   	   	   	ADH_temp=ADRH;
   	   	   	   	ADL_temp=ADRL;
   	   	   	   	if((ADH_temp==0)&&(ADL_temp==0)) return;
   	   	   	   	else;
   	   	   	   	
   	   	   	}
   	   	   	OSADJCR++;
   	   	   	Data_OSADJCR=OSADJCR&0x1f;
   	   	}
   	}  	   	   	       	    
}
/************************************************
;  *    @Function Name       : ADC_Repeat_ADJ
;  *    @Description         : ADC 校准后 重复几次
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/  
void  ADC_Repeat_ADJ(void)
{
   	u8 i,j,R_Zero,R_Zero_max;
   	R_Zero_max=0;
   	R_Zero=0;
   	Data_OSADJCR=OSADJCR&0x3f;
   	OSADJCR--;
   	
   	for(j=0;j<3;j++)
   	{
   	   	for(i=0;i<6;i++)
   	   	{
   	   	   	ADEOC=0;     
   	   	   	while(!ADEOC);
   	   	   	ADH_temp=ADRH;
   	   	   	ADL_temp=ADRL;
   	   	   	i++;
   	   	   	if((ADH_temp==0)&&(ADL_temp==0))
   	   	   	{
   	   	   	   	R_Zero++;
   	   	   	}
   	   	
   	   	}
   	   	if(R_Zero>R_Zero_max)
   	   	{
   	   	   	R_Zero_max=R_Zero;
   	   	   	Data_OSADJCR=OSADJCR&0x3f;
   	   	}
   	   	OSADJCR++;
   	   	R_Zero=0;
   	}
   	OSADJCR=Data_OSADJCR&0x3f;
   	
}
/************************************************
;  *    @Function Name       : IO_Config
;  *    @Description         : 普通IO配置
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/   
void IO_Config(void)
{
   	IOP0=0;
   	IOP1=0;
   	IOP2=0;
   	
   	OEP0=0xff; 	   	//P0  out
   	OEP1=0xff; 	   	//P1 out
   	OEP2=0xfC; 	   	//P21 P20 in
   	
   	ADIOS0=0;
   	ADIOS1=0;
   	
   	PUP0=0;
   	PUP1=0; 
   	PUP2=0x01; 	   	   	//P20  up
   	
   	PDP0=0;
   	PDP1=0;
   	PDP2=0;
}
/************************************************
;  *    @Function Name       : IO_ADC_Config
;  *    @Description         : ADC IO配置
;  *    @IN_Parameter      	 : CHX ADC IO通道    	
;  *    @Return parameter    :
;  ***********************************************/   
void IO_ADC_Config(u8 CHX)
{
   	uchar CHX_Temp=0;
   	CHX_Temp=CHX;
   	if(CHX<8)
   	{
   	   	ADIOS0=1<<CHX_Temp;	   	
   	}else 
   	{
   	   	CHX_Temp=CHX_Temp-8;
   	   	ADIOS1=1<<CHX_Temp;	
   	}  	
}
/************************************************
;  *    @Function Name       : ADC_Config
;  *    @Description         : ADC配置
;  *    @IN_Parameter      	 : 
   	   	   	   	   	   	   	   	ADC_CLK    	ADC转换时钟选择位
   	   	   	   	   	   	   	ADC_Ampling_Time  ADC采样时间选择位
   	   	   	   	   	   	   	   	ADC_VRS     ADC参考电压选择位   00 内部2v   11  VDD
   	
;  *    @Return parameter    :
;  ***********************************************/    	
void ADC_Config(u8 ADC_CLK,u8 ADC_Ampling_Time,u8 ADC_VRS)
{
   	ADCR1&=0xCC;
   	ADCR1|=ADC_CLK<<4;
   	ADCR1|=ADC_Ampling_Time;
   	ADCR0&=0xF3;
   	ADCR0|=ADC_VRS<<2;
   	ADRSEL=1;  	   	   	//高4位存入ADRH[3:0]、低8位存入ADRL[7:0]
   	OSADJCR=0x00;//关闭修调
   	ADEN=1;   //使能ADC  
   	//ADIE=1;  	
}
/************************************************
;  *    @Function Name       : Get_ADC_Value
;  *    @Description         : 获得ADC值  启动一次转换  查询方式
;  *    @IN_Parameter      	 : 通道
;  *    @Return parameter    : 返回ADC的值
;  ***********************************************/ 
u16 Get_ADC_Value(u16 CHX)
{
   	ADCR0&=0x0F;
   	ADCR0|=CHX<<4;
   	ADEOC=0;   	   	//使能转换
   	while(!ADEOC); 	   	   	//等待转换完成
   	ADC_Value=(ADRH<<8)+ADRL;
   	return ADC_Value;
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
   	u16 AdcMAX = 0;
   	u16 AdcMIN = 0xffff;

   	ADCR0&=0x0F;
   	ADCR0|=CHX<<4;
   	for (channel = 0; channel < 20; channel++)
   	{
   	   	ADEOC=0;   	   	//使能转换
   	   	while(!ADEOC); 	   	   	//等待转换完成
   	   	ADC_Value=(ADRH<<8)+ADRL;
   	   	if (channel < 2)
   	   	   	continue; //丢弃前两次采样的
   	   	if (ADC_Value > AdcMAX)
   	   	   	AdcMAX = ADC_Value; //最大
   	   	if (ADC_Value < AdcMIN)
   	   	   	AdcMIN = ADC_Value; //最小
   	   	tmpBuff += ADC_Value;
   	}
   	tmpBuff -= AdcMAX; 	   	   	//去掉一个最大
   	tmpBuff -= AdcMIN; 	   	   	//去掉一个最小
   	ADC_Value = (tmpBuff >> 4); //除以16，取平均值
   	return ADC_Value;
}
/************************************************
;  *    @Function Name       : EEPROM_Write_Byte
;  *    @Description         : 内部EEPROM写一个字节
;  *    @IN_Parameter      	 : 地址  数据
;  *    @Return parameter    :
;  ***********************************************/  
void EEPROM_Write_Byte(u8 Addr,u8 Data)
{
   	EECR=0;	   	//清除EETRIG
   	EEAR=Addr;
   	EEDR=Data;
   	GIE=0;
    ClrWdt();  	   	//清看门狗
   	EEMASK=0x5A;
   	EEMASK=0xA5;   	   	//解除保护
   	EECR=0xC0; 	   	   	//启动EEPROM读写  写数据操作
   	Nop();
   	GIE=1;
}
/************************************************
;  *    @Function Name       : EEPROM_Read_Byte
;  *    @Description         : 内部EEPROM读一个字节
;  *    @IN_Parameter      	 : Addr  地址
;  *    @Return parameter    : 读到的内容
;  ***********************************************/  
u8 EEPROM_Read_Byte(u8 Addr)
{
   	u8 Temp;
   	EECR=0;	   	//清除EETRIG
   	EEAR=Addr;
   	GIE=0;
   	EEMASK=0x5A;
   	EEMASK=0xA5;   	   	//解除保护
   	EECR=0x80; 	   	   	//启动EEPROM读写  读数据操作
   	Nop();
   	GIE=1;
   	Temp=EEDR;
   	return Temp;
}

/************************************************
;  *    @Function Name       : Timer_Init
;  *    @Description         : 定时器初始化
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/  
void Timer_Config(void)
{
    T0CR&=0x60;
    T0CR|=0x85;	   	//Fcpu  32分频
    T0CNT=124;
    T0LOAD=124;
    T0IE=1; 
    
    // T1CR&=0x20;
    // T1CR|=0xc0; 	   	//Fcpu  不分频
    // T1CNTH=0xff;
    // T1CNTL=0xff;
    // T1LOADH=0xff;
    // T1LOADL=0xff;
    // T1DATAH=0x10;
    // T1DATAL=0x00;       	    
}
/************************************************
;  *    @Function Name       : InitSys
;  *    @Description         : 系统初始化
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/  
void InitSys(void)
{
   	GIE = 0;
   	C_RAM();
   	IO_Config();
   	UART_Config();
   	ADC_Init_ADJ();
   	ADC_Repeat_ADJ();
   	Timer_Config();
   	IO_ADC_Config(0);  	   	   	   	//ADC_CH0 P21配置模拟
   	ADC_Config(0,3,0);     	   	   	//F/8 15ADCLK  in 2V
   	Init_I2C();
   	GIE  = 1;        
}

void int_isr(void)__interrupt
{
__asm
   	movra   _ABuf
   	swapar  _PFLAG
   	movra   _StatusBuf
__endasm;
   	if((T0IF)&&(T0IE))
   	{      	       	
   	   	T0IF=0;
   	   	P16D=!P16D;
   	   	Timer0_Num++;
   	   	if(Timer0_Num>=100)
   	   	{
   	   	   	Timer0_Num=0;
   	   	   	Fre_Mode_Flag=1;
   	   	}
   	}
   	if((T1IF)&&(T1IE))
   	{
   	   	T1IF  = 0; 	
   	}
   	if (RI)
    {
   	   	RI=0;
   	   	UART_Buff=SBUF;
   	   	UART_Flag=1;
    }
//    if (TI)
//    {
//        TI = 0;                 //清除TI位
//        UART_Busy = 0;               //清忙标志
//    }
   	if(UARTIF)
   	{
   	   	UARTIF  = 0;
   	   	TI=0;//发送中断标志位清零
   	   	UART_Busy=0;
   	}
   	if(IICIF)
   	{
   	   	IICIF  = 0;
   	   	TI=0;//发送中断标志位清零
   	   	F_I2C_done=1;
   	}

__asm
   	swapar  _StatusBuf
   	movra   _PFLAG
   	swapr   _ABuf
   	swapar  _ABuf
__endasm;
}







