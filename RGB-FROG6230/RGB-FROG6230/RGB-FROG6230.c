/******************************************************************************
;  *   	@MCU   	   	   	   	 : MC30P6080
;  *   	@Create Date         : 2020.5.3
;  *   	@Author/Corporation  : Martin/SinoMCU
;  *   	@晟矽微技术支持QQ群   : 814641858
;  *    @晟矽微官方论坛       : http://bbs.sinomcu.com/
;  *   	@Copyright           : 2019 SINOMCU Corporation,All Rights Reserved.
;  *----------------------Abstract Description---------------------------------
   	   	   	   	   	   	   	   	RGB青蛙不带呼吸效果
******************************************************************************/
#include "user.h"

//typedef u16 unsigned int ;       	  
//typedef u8 unsigned char ;
char second;
char led_Gear;
unsigned int msecond;
unsigned int duty;



/************************************************
;  *    @Function Name       : CLR_RAM
;  *    @Description         : 清RAM
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/
void CLR_RAM(void)
{      	       	
    __asm
           	movai  	0x40
           	movra  	FSR
           	movai  	48
           	movra  	0x07
           	decr   	FSR
           	clrr   	INDF
           	djzr   	0x07
           	goto   	$-3
           	clrr   	0x07
   	   	   	clrr   	0x05
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
   	P1 = 0x00;
   	DDR1 = 0x00;
   	PDCON = 0xff; //0:Effective 1:invalid
   	PUCON = 0xff; //0:Effective 1:invalid

   	
}

/************************************************
;  *    @Function Name       : WDT
;  *    @Description         : 
;  *    @IN_Parameter      	 :
;  *    @Return parameter    :
;  ***********************************************/
void WDT_Init(void)
{
WDTEN=1;
}
/************************************************
;  *    @Function Name       : WDT清零
;  *    @Description         : 
;  *    @IN_Parameter      	 :
;  *    @Return parameter    :
;  ***********************************************/
void CLRWDT_Init(void)
{
 __asm

CLRWDT
__endasm; 
}

/************************************************
;  *    @Function Name       : TIMER0_INT_Init
;  *    @Description         : 
;  *    @IN_Parameter      	 :
;  *    @Return parameter    :
;  ***********************************************/
void Timer_INT_Init(void)
{
   	T0CR=0x00;     //时钟为CPU时钟    定时器2分频  
   	T0CNT=256-144;      //200us 
   	T0IE=1;
}




void delay(int i)
{
   	while(i--);	
}
void NOP()
{  	
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
   	msecond=0;
   	second=0;
   	CLR_RAM();
   	IO_Init();
   	Timer_INT_Init();
   	WDT_Init();
   	GIE = 1;
}
void main (void)
   	{   
 
   	Sys_Init();
   	while(1)
   	{ 







   	
   	   	   	

           	

switch(second)
   	   	{
   	   	    case(0):
   	   	   	   	P12D=0;P11D=1;P10D=1;CLRWDT_Init();break;
   	   	    case(1):
   	   	   	   	P12D=1;P11D=0;P10D=1;CLRWDT_Init();break;
   	   	   	case(2):
   	   	   	   	P12D=1;P11D=1;P10D=0;CLRWDT_Init();break;
 
   	   	   	case(3):
   	   	   	   	P12D=0;P11D=1;P10D=1;CLRWDT_Init();break;
   	   	   	case(4):
   	   	   	   	P12D=1;P11D=0;P10D=1;CLRWDT_Init();break;
   	   	   	case(5):
   	   	   	   	P12D=1;P11D=1;P10D=0;CLRWDT_Init();break;

   	   	   	case(6):
   	   	   	   	P12D=0;P11D=1;P10D=1;CLRWDT_Init();break;
   	   	   	case(7):
   	   	   	    P12D=1;P11D=0;P10D=1;CLRWDT_Init();break;
   	   	    case(8):
   	   	   	   	P12D=1;P11D=1;P10D=0;CLRWDT_Init();break;

   	   	    case(9):
   	   	   	   	P12D=0;P11D=1;P10D=1;CLRWDT_Init();break;
   	   	   	case(10):
   	   	   	   	P12D=1;P11D=0;P10D=1;CLRWDT_Init();break;
   	   	   	case(11):
   	   	   	   	P12D=1;P11D=1;P10D=0;CLRWDT_Init();break;

   	   	   	case(12):
   	   	   	   	P12D=1;P11D=1;P10D=1;CLRWDT_Init();break;


   	   	   	case(13):
   	   	   	   	P12D=1;P11D=1;P10D=0;CLRWDT_Init();break;
   	   	   	case(14):
   	   	   	   	P12D=1;P11D=0;P10D=1;CLRWDT_Init();break;
   	   	   	case(15):
   	   	   	   	P12D=0;P11D=1;P10D=1;CLRWDT_Init();break;

   	   	   	case(16):
   	   	   	    P12D=1;P11D=1;P10D=0;CLRWDT_Init();break;
   	   	   	case(17):
   	   	   	   	P12D=1;P11D=0;P10D=1;CLRWDT_Init();break;
   	   	   	case(18):
   	   	   	    P12D=0;P11D=1;P10D=1;CLRWDT_Init();break;

   	   	    case(19):
   	   	   	   	P12D=1;P11D=1;P10D=0;CLRWDT_Init();break;
   	   	    case(20):
   	   	   	   	P12D=1;P11D=0;P10D=1;CLRWDT_Init();break;
   	   	   	case(21):
   	   	   	   	P12D=0;P11D=1;P10D=1;CLRWDT_Init();break;

   	   	   	case(22):
   	   	   	   	P12D=1;P11D=1;P10D=0;CLRWDT_Init();break;
   	   	   	case(23):
   	   	   	   	P12D=1;P11D=0;P10D=1;CLRWDT_Init();break;
   	   	   	case(24):
   	   	   	   	P12D=0;P11D=1;P10D=1;CLRWDT_Init();break;



   	   	   	case(25):
   	   	   	   	P12D=1;P11D=1;P10D=1;CLRWDT_Init();break;
   	   	   	case(26):
   	   	   	    P12D=0;P11D=0;P10D=0;CLRWDT_Init();break;
   	   	   	case(27):
   	   	   	   	P12D=1;P11D=1;P10D=1;CLRWDT_Init();break;
   	   	   	case(28):
   	   	   	   	P12D=0;P11D=0;P10D=0;CLRWDT_Init();break;
   	   	   	case(29):
   	   	   	   	P12D=1;P11D=1;P10D=1;CLRWDT_Init();break;





        
       	
 
   	   	   	   	
     
   	 }     	 






       	}





}

/************************************************
;  *    @Function Name       : Interrupt
;  *    @Description         : The interrupt function
;  *    @IN_Parameter          	 :
;  *    @Return parameter      	:
;  ***********************************************/        
void int_isr(void) __interrupt
{
__asm 
   	movra _abuf
   	swapar _STATUS
   	movra _statusbuf
__endasm;


    if((T0IF)&&(T0IE))
    {
   	   	T0CNT=131;
 
   	   	msecond++;
 
   	   	if(400==msecond)
   	   	{
   	   	msecond=0;
   	   	second++;

   	   	if(30==second)
   	   	second=0;
   	   	
   	   	
   	   	}
   	   	
   	   	T0IF=0;
    }

T0IF=0;


__asm 
   	swapar _statusbuf
   	movra _STATUS
   	swapr _abuf
   	swapar _abuf
__endasm;
}



/**************************** end of file *********************************************/