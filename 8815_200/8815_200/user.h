
#ifndef USER
#define USER


#include "extern.h"



u8 abuf;
u8 statusbuf;

u16 timer0_count1;

void CLR_RAM(void);
void IO_Init(void);
void TIMER0_INT_Init(void);
void TIMER1_PWM_Init(void);
void KBIE_Init(void);
void Sys_Init(void);

//============Define  Flag=================
typedef union {
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
}bit_flag;
volatile bit_flag flag1;

#define    	FLAG_TIMER0_5000ms     	flag1.bits.bit0	   	 // 按键扫描标志位

#endif


/**************************** end of file *********************************************/

