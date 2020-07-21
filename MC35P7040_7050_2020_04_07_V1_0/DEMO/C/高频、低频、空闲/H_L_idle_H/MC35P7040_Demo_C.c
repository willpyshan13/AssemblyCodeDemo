/******************************************************************************
;  *   	@MCU				 : MC35P7040
;  *   	@Create Date         : 2019.12.29
;  *   	@Author/Corporation  : Martin/SinoMCU
;  *   	@����֧��QQȺ		  : 814641858      
;  *    @����΢�ٷ���̳		  : http://bbs.sinomcu.com/	 
;  *   	@Copyright           : 2019 SINOMCU Corporation,All Rights Reserved.
;  *----------------------Abstract Description---------------------------------   	
;  *            ��Ƶ-��Ƶ-����ģʽ-��Ƶ-��Ƶ-IO��ת 2S T0����һ�Σ�  
                P01��ת200�����
                P54D 2S��ת
                ģʽ�л��ɸ��������ֲ� ģʽ�л�ʾ��ͼ �޸ģ�
******************************************************************************/

#include "user.h"

/************************************************
;  *    @Function Name       : CLR_RAM
;  *    @Description         : 
;  *    @IN_Parameter        :
;  *    @Return parameter    :
;  ***********************************************/
void CLR_RAM(void)
{
    __asm
   	movai  	0x3F
   	movra  	FSR0
   	clrr   	FSR1
   	clrr   	INDF
   	DJZR    FSR0
   	goto   	$-2
   	clrr   	INDF
__endasm;
}
/************************************************
;  *    @Function Name       : IO_Init
;  *    @Description         : 
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/  
void IO_Init(void)
{
   	IOP0=0x00; 	   	   	//io������λ
   	OEP0=0xff; 	   	   	//io�ڷ��� 1:out  0:in  
   	PUP0=0x00; 	   	   	//io����������   1:enable  0:disable
   	
   	IOP4=0x00; 	   	   	//io������λ
   	OEP4=0xff; 	   	   	//io�ڷ��� 1:out  0:in   
   	PUP4=0x00; 	   	   	//io����������   1:enable  0:disable
   	
   	IOP5=0x00; 	   	   	//io������λ
   	OEP5=0xff; 	   	   	//io�ڷ��� 1:out  0:in  
   	PUP5=0x00; 	   	   	//io����������   1:enable  0:disable

   	P4CON=0xff;
}
/************************************************
;  *    @Function Name       : TIMER0_INT_Init
;  *    @Description         : ��ʱ����ʼ��
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/  
void TIMER0_INT_Init(void)    	   	
{
    TMRCR=0x06;            //T1CLK=FCPU/2      T0CLK=Fosc    ����T0�������
    T0CR=0x04;          //����T0    128��Ƶ  T0CLK�ڲ�ʱ��  �Զ�����  �ر�PWM
    T0CNT=256-125;
    T0LDR=256-125;     // �����Ƶ��   32k/4/128=2s      //��Ƶģʽ�̶�4t
   //  	T0IE=1;
}
/************************************************
;  *    @Function Name       : Sys_Init
;  *    @Description         : ϵͳ��ʼ��
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/  
void Sys_Init(void)
{
   	GIE = 0;
    CLR_RAM();
    IO_Init();
   	TIMER0_INT_Init();
   	GIE=1;        
}
void main(void)
{
   	u8 num;
   	Sys_Init();
   	while(1)
   	{
   	    ADEN=0;	   	   	 //�ر�����    	
   	   	CLKS=1;	   	//�л�����Ƶ 4t
   	   	Nop();
   	   	HFDE=1;	   	//�رո�Ƶ
   	   	//������������(�����ڳ�ʼ���Ѿ�����)
   	   	T0CNT=256-125;     	   	   	   	   	   	   
   	   	T0EN=1;
   	   	T0IE=1;
   	   	INTF=0;
       	Nop();
   	   	Nop();
   	   	OSCM&=0xE7;   
   	   	OSCM|=0x10;	   	   	   	   	//��ɫģʽ
   	   	Nop();
   	   	Nop();
   	   	Nop(); 	   	   	  
   	   	T0IE=0;
   	   	T0EN=0;
       	HFDE=0;	   	//�򿪸�Ƶ  (�û��Լ�ѡ��)
   	   	Nop();
   	   	Nop();
       	CLKS=0;	   	//�л�����Ƶ	   	(�û��Լ�ѡ��)

   	   	ADEN=1;	   	//������Ӧ������  (�û��Լ�ѡ��)
   	   	
   	   	for(num=0;num<200;num++)
   	   	{
   	   	   	P01D=!P01D;
   	   	   	Nop();
   	   	   	Nop();
   	   	   	Nop();
            Nop();
   	   	   	Nop();
   	   	   	Nop();
            Nop();
   	   	   	Nop();
   	   	}
   	}
}
void int_isr(void) __interrupt  
{
   	__asm
   	   	push
   	__endasm;
    if(T0IF&&T0IE)
   	{
   	   	T0IF=0;
        P54D=!P54D;
   	}
   	__asm
   	   	pop
   	__endasm;
}




















