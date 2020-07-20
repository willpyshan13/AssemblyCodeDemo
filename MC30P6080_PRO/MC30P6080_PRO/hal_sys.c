#include "hal_sys.h"

static void InitRam(void);
static void config(void);

void HalSysInit (void)
{
	GIE = 0;
	InitRam();
	config();
	GIE = 1;
	MCR |= (10<<1)|(1<<0);//�����͵�ѹ��� 3.0V
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
	INTOM = 1;//�����ش���
	INTIF = 0;//����ⲿ�жϱ�־λ
	INTIE = 1;//ʹ���ⲿ�ж�
	EIS = 1;//ʹ���ⲿ�ж�Դ
}
*/
static void config(void)
{
 	P0 = 0x00;				//���ݼĴ����������ƽֵ
 	P1 = BV(2);
 	DDR0 = 0x00;   			//1:���� 0:���
 	DDR1 = BV(0)|BV(1);     	   	
 	PDCON = 0xFF;  			//������0:��Ч 1:��Ч
 	PUCON = 0xff;  			//������0:��Ч 1:��Ч    
 	ODCON = 0x00;			//�Ƿ�©��1ʹ�ܣ�0��ͨ������� ����P1���Ϊ�������
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




