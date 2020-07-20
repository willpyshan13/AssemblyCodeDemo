
/******************************************************************************
;  *   	@MCU   	   	   	   	 : MC30P6240
;  *   	@Create Date         : 2019.12.27
;  *   	@Author/Corporation  : Martin/SinoMCU
;  *   	@晟矽微技术支持QQ群   : 814641858
;  *    @晟矽微官方论坛       : http://bbs.sinomcu.com/
;  *   	@Copyright           : 2019 SINOMCU Corporation,All Rights Reserved.
;  *----------------------Abstract Description---------------------------------
;  *    1   V1.0     2019.03.18	   	   	P16 1ms翻转 P10.11.12.15输出PWM
   	   	   	   	   	   	   	   	   	   	5s 休眠 P17唤醒
  ******************************************************************************/


#include "user.h"
#include "iic.h"
#include "qma7981.h"

 //  	int id;

/************************************************
;  *    @Function Name       : CLR_RAM
;  *    @Description         : 初始化RAM
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/  
void CLR_RAM(void)
{      	       	
    __asm

               	
          MOVAI     48
          MOVRA     0x07
          MOVAI     0X3F
          MOVRA     FSR
CLR_RAM:
          CLRWDT 
          CLRR      INDF
          DECR      FSR
          DJZR      0x07
          GOTO      CLR_RAM
 
    __endasm;          	
}

/************************************************
;  *    @Function Name       : IO_Init
;  *    @Description         : 初设置io 
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/ 
void IO_Init(void)
{
   	P0 = 0x00; 	   	   	   	
   	P1 = 0x00;

   	DDR0 = 0x00;   	//1:input 0:output
   	DDR1 = 0x1B;      //   	   	00011011
   	PDCON = 0x7E;      	//0:Effective 1:invalid 1111110
   	PUCON = 0xE5;  	//0:Effective 1:invalid   11100101
   	ODCON = 0x00;  	   	//0:推挽输出  1:开漏输出 

}

/************************************************
;  *    @Function Name       : TIMER0_INT_Init
;  *    @Description         : 
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/ 
void TIMER0_INT_Init(void)
{
       	T0CR=0x02;     //时钟为CPU时钟    定时器64分频  1ms
       	T0CNT=256-125;
       	T0IE=1;
}

/************************************************
;  *    @Function Name       : KBIE_Init
;  *    @Description         : 
;  *    @IN_Parameter        :
;  *    @Return parameter    :
;  ***********************************************/
void KBIE_Init(void)
{
   	//DDR1 = 0x80;         	   	//P17  in
   //  	PUCON=0x7f;        	   	//P17上拉 
   //  	P1KBCR=0x80;       	   	   	//使能P17的键盘中断位
// 	KBIE=1；
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
   //  	TIMER1_PWM_Init();
   	//KBIE_Init();
   	GIE  = 1;        
}
void main (void)
{    
 
   	u16 data;
  // 	u8 id;

   	Sys_Init();
   	iic_init();
   	qma7981_init();



   	while(1)
   	{  	 

   	   //  	LED_Scan();
   	   	if(FLAG_TIMER0_5000ms) 	   	//5s休眠
   	   	{
   	   	  //   	qmaX981_chip_id();
   	   	   	qma7981_read_raw_xyz(&data);
   	   	   	
   	   	   	 if(data)
   	   	   {
   	   	   	   	 DDR12 = 0;
   	   	   	   	 P12D = 1;
   	   	   }
   	   	   	else
   	   	   	{
   	   	   	   	DDR12 = 0;
   	   	   	   	P12D = 0;

   	   	   	}
   //	id=qmaX981_chip_id();
   	 //  	   if(id == 0xE7)
   	   //	   {
   	   	   	//   	 DDR12 = 0;
   	   	   //	   	 P12D = 1;
   	   	 //  }
   	   	   	FLAG_TIMER0_5000ms = 0;
   	   	}
   	}   
}   
void int_isr(void)__interrupt
{
   	__asm
   	   	movra   _abuf
    swapar  _STATUS
    movra   _statusbuf
__endasm;

    if((T0IF)&&(T0IE))
    {
       	T0CNT=256-125;
   	   	P16D=!P16D; 

   	     //	LED_Scan();
   	   
   	   	timer0_count1++;
   	   	if(timer0_count1>=1000)
   	   	{
   	   	   	timer0_count1=0;

/*
   	   	   	id=qmaX981_chip_id();
   	   	   if(id == 0xE7)
   	   	   {
   	   	   	   	 DDR12 = 0;
   	   	   	   	 P12D = 1;
   	   	   }
*/
   	   	   //  	 LCD_num_Scan();
   	   	   	FLAG_TIMER0_5000ms=1;
   	   	}
   	   	T0IF=0;
    }
__asm
       	swapar  _statusbuf
    movra   _STATUS
    swapr   _abuf
    swapar  _abuf
__endasm;
}


