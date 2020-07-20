#include "hal_sys.h"

static void InitRam(void);
static void config(void);

void HalSysInit (void)
{
	GIE = 0;
	InitRam();
	config();
	GIE = 1;
	MCR |= (10<<1)|(1<<0);//开启低电压检测 3.0V
}

void HalTim0Init (void)
{
	T0CR  = (TIM0_INTM<<6)|(TIM0_T0PTS<<5)|(TIM0_T0SE<<4)|(TIM0_T0PTA<<3)|(TIM0_T0PRS<<0);
 	T0CNT = TIM0_CNT;
 	T0IE  = TIM0_EN;
}
/*
void HalExtiInit (void)
{
	INTOM = 1;//上升沿触发
	INTIF = 0;//清楚外部中断标志位
	INTIE = 1;//使能外部中断
	EIS = 1;//使能外部中断源
}
*/
static void config(void)
{
 	P0 = 0x00;				//数据寄存器：输出电平值
 	P1 = BV(2);
 	DDR0 = 0x00;   			//1:输入 0:输出
 	DDR1 = BV(0)|BV(1);     	   	
 	PDCON = 0xFF;  			//上拉：0:有效 1:无效
 	PUCON = 0xff;  			//下拉：0:有效 1:无效    
 	ODCON = 0x00;			//是否开漏：1使能：0普通推挽输出 所有P1输出为推完输出
}


static void InitRam(void)
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
	clrr   	INDF
	clrr   	0x07
	__endasm;	   	
}




