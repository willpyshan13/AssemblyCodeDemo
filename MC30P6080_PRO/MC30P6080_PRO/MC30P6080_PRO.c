#include "hal_sys.h"
uchar ABuf,StatusBuf;  	   	//这是汇编系统必须要的变量不能删除


#define KEY	   	   	   	   	   	   	P10D
#define	HALL   	   	   	   	   	   	P11D
#define	LED	   	   	   	   	   	   	P12D
#define	BOOST_EN   	   	   	   	   	P14D

#define HALL_ON_TIME   	   	   	   	20
#define	KEY_ON_TIME	   	   	   	   	500
#define HALL_OFF_TIME  	   	   	   	20
#define KEY_LOOSE_TIME 	   	   	   	20
#define BLANK_TIME 	   	   	   	   	500
#define	SLEEP_TIME 	   	   	   	   	10000

#define STA_KEY_ON 	   	   	   	   	0x0001
#define STA_HALL_ON	   	   	   	   	0x0002
#define STA_FLASH_ON   	   	   	   	0x0004


u16	state; 	   	   	   	   	   	   	// 状态
u16	sleepTime; 	   	   	   	   	   	// 睡眠时间


struct bs
{
u8 testflg:1;
}bts;

void funInit(void)
{
   	bts.testflg=0;
}

void control(void)
{

}

void sleepManage(void)
{
   	if(BOOST_EN || (state & STA_HALL_ON))
   	   	sleepTime = SLEEP_TIME;

   	if(sleepTime == 0)
   	{
   	   	LED = 1;
    KBIE = 1;  	   	// 使能键盘中断
    KBIM = BV(0);
   	   	T0IE = 0;
    STOP;      	   	// 执行STOP指令

    NOP;
    NOP;
    NOP;
    NOP;

    sleepTime = SLEEP_TIME;
    KBIE = 0;
   	T0IE = 1;
  }
}

void main()
{
   	HalSysInit();
   	HalTim0Init();
   	funInit();
   	   	
   	while(1)
   	{
   	   	   	control();
   	   	   	sleepManage();
   	}
}

void int_isr(void)__interrupt
{
   	__asm
   	  movra   _ABuf
   	  swapar  _STATUS
   	  movra   _StatusBuf
   	__endasm;

   	//T0
   	if(T0IE && T0IF)//1ms
   	{
   	   	T0CNT=TIM0_CNT;
   	   	T0IF = 0;
   	   	bts.testflg=!bts.testflg;

   	   	if(BOOST_EN)
   	   	{

   	   	}
   	   	LED=bts.testflg;
   	   	BOOST_EN=bts.testflg;
   	}
   	//T1
   	/*if(T1IE && T1IF)
   	{
    T1IF = 0;          	  
   	}*/
   	//INT
   	/*if(INTIE && INTIF)
   	{
    INTIF = 0;
   	   	CLRWDT;//清除看门狗计数
   	}*/
   	//KEY
   	if(KBIE && KBIF)
   	{
       	KBIF = 0;
   	}
   	
   	__asm
   	swapar  _StatusBuf
   	movra   _STATUS
   	swapr   _ABuf
   	swapar  _ABuf
   	__endasm;
}

