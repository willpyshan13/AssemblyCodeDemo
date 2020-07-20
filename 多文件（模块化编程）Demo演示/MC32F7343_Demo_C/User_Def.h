#ifndef User_Def_H
#define User_Def_H
#include "MC32F7343.h"

#define u8  unsigned char
#define u16 unsigned int
#define u32 unsigned long int

extern u8 ABuf,StatusBuf;

void C_RAM(void);
void ADC_Init_ADJ(void);
void ADC_Repeat_ADJ(void);
void IO_Config(void);
void IO_ADC_Config(u8 CHX);
void ADC_Config(u8 ADC_CLK,u8 ADC_Ampling_Time,u8 ADC_VRS);
u16 Get_ADC_Value(u16 CHX);
uint ADC_Get_Value_Average(uchar CHX);

void EEPROM_Write_Byte(u8 Addr,u8 Data);
u8 EEPROM_Read_Byte(u8 Addr);
void  Timer_Config(void);



//位域操作
typedef union
{
   	unsigned char byte;
   	struct
   	{
   	   	u8 bit0 : 1;
   	   	u8 bit1 : 1;
   	   	u8 bit2 : 1;
   	   	u8 bit3 : 1;
   	   	u8 bit4 : 1;
   	   	u8 bit5 : 1;
   	   	u8 bit6 : 1;
   	   	u8 bit7 : 1;
   	} bits;
}Flag; 	
extern volatile Flag Flag1;
extern volatile Flag Flag2;
//标志定义

#define UART_Busy  	Flag1.bits.bit0
#define UART_Flag  	Flag1.bits.bit1
#define F_I2C_done  Flag1.bits.bit2
#define F_write    	Flag1.bits.bit3
#define D_read 	   	Flag1.bits.bit4
#define D_write    	Flag1.bits.bit5
#define F_erro 	   	Flag1.bits.bit6
#define F_read 	   	Flag1.bits.bit7

#define Fre_Mode_Flag  	   	Flag2.bits.bit0

#endif
