/******************************************************************************
;  *   	@MCU   	   	   	   	 : MC35P7040
;  *   	@Create Date         : 2019.12.29
;  *   	@Author/Corporation  : Martin/SinoMCU
;  *   	@技术支持QQ群   	   	  : 814641858      
;  *    @晟矽微官方论坛   	   	  : http://bbs.sinomcu.com/	 
;  *   	@Copyright           : 2019 SINOMCU Corporation,All Rights Reserved.
;  *----------------------Abstract Description---------------------------------
;  *   	   	   	   	   	   	定义
******************************************************************************/

#ifndef USER
#define USER

#include <mc35-common.h>
#include "MC35P7040.h"


#define u8  unsigned char
#define u16 unsigned int
#define u32 unsigned long int
#define uint8_t  unsigned char
#define uint16_t unsigned int
#define uint32_t unsigned long int

#define PASS   	0
#define FAIL   	1

uint16_t ADC_num_value;
uint16_t timer0_count1;

void CLR_RAM(void);
void IO_Init(void);
void TIMER0_INT_Init(void);
void TIMER1_PWM_Init(void);
void ADC_Init(void);
uint8_t ADC_Zero_ADJ(void);
uint8_t ADC_Vertex_ADJ(void);
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


#define    	FLAG_TIMER0_5000ms     	flag1.bits.bit0	   	 

#endif


/**************************** end of file *********************************************/



