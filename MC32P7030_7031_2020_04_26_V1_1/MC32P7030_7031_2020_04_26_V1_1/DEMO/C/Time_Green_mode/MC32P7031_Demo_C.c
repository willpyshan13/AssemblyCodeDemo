/******************************************************************************
;  *   	@MCU				 : MC32P7031
;  *   	@Create Date         : 2019.12.29
;  *   	@Author/Corporation  : Martin/SinoMCU
;  *   	@����֧��QQȺ		  : 814641858      
;  *    @����΢�ٷ���̳		  : http://bbs.sinomcu.com/	 
;  *   	@Copyright           : 2019 SINOMCU Corporation,All Rights Reserved.
;  *----------------------Abstract Description---------------------------------
;  *		�л������ٽ�����ɫģʽ 1S T0����һ�Σ����Ѻ��ƵģʽIO��ת

				ע�� 7031����ֱ�Ӷ�IOĳһλ
					�� if(P54D==x)
						P54D=!P54D;
					��Ϊ ������IO������һ������
						buff=IOP5;
						���ж�buffĳһλ
******************************************************************************/

#include "user.h"

/************************************************
;  *    @Function Name       : CLR_RAM
;  *    @Description         : �ϵ���RAM
;  *    @IN_Parameter        :
;  *    @Return parameter    :
;  ***********************************************/
void CLR_RAM(void)
{
	__asm 
	movai 0x7F 
	movra FSR0
	clrr FSR1
	clrr INDF
	DJZR FSR0 
	goto $ -2 
	clrr INDF
	__endasm;
}
/************************************************
;  *    @Function Name       : IO_Init
;  *    @Description         : IO��ʼ��
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/
void IO_Init(void)
{
	IOP0 = 0x00; //io������λ
	OEP0 = 0xfE; //io�ڷ��� 1:out  0:in
	PUP0 = 0x01; //io����������   1:enable  0:disable

	IOP4 = 0x00;  //io������λ
	OEP4 = 0xfC;  //io�ڷ��� 1:out  0:in    	P40  41in
	PUP4 = 0x00;  //io����������   1:enable  0:disable
	ANSEL = 0x00; //io����ѡ��  1:ģ������  0:ͨ��io

	IOP5 = 0x00; //io������λ
	OEP5 = 0xff; //io�ڷ��� 1:out  0:in
	PUP5 = 0x00; //io����������   1:enable  0:disable
}
/************************************************
;  *    @Function Name       : TIMER0_INT_Init
;  *    @Description         : 
;  *    @IN_Parameter        :
;  *    @Return parameter    :
;  ***********************************************/
void TIMER0_INT_Init(void)    	   	
{
   	TXCR=0x0A; 	   	//T0ʱ�� T0 T2 Fcpu  T1 Fhosc ����T0����
//T0
   	T0CR=0x24; 	   	   	   	//�ڲ� 64��Ƶ  �����Զ�����
   	T0C=256-125;
   	T0D=256-125;   	   	//1ms
   	T0IF=0; 	
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
	GIE = 1;
}
void main(void)
{
	u8 num;
   	Sys_Init();
   	while(1)
   	{
   	   	ADON=0;	   	   	 //�ر�����    	

   	   	CLKS=1;	   	//�л�����Ƶ
   	   	Nop();
   	   	HOFF=1;	   	//�رո�Ƶ
   	   	//������������(�����ڳ�ʼ���Ѿ�����)
   	   	T0C=256-125;   	   	   	   	   	   	   
   	   	TC0EN=1;
   	   	T0IE=1;

   	   	INTF=0;

       	Nop();
   	   	Nop();
   	   	OSCM&=0xE7;   
		OSCM|=0x10;	  			  	//��ɫģʽ
   	   	Nop();
   	   	Nop();
		Nop();
			  
   	   	T0IE=0;
   	   	TC0EN=0;
       	HOFF=0;	   	//�򿪸�Ƶ  (�û��Լ�ѡ��)
   	   	Nop();
   	   	Nop();
       	CLKS=0;	   	//�л�����Ƶ	   	(�û��Լ�ѡ��)

   	   	ADON=1;	   	//������Ӧ������  (�û��Լ�ѡ��)
   	   	
   	   	for(num=0;num<100;num++)
   	   	{
   	   	   	IO_buff.byte=IOP5;
       	   	IO_BIT4=!IO_BIT4;
   	   	   	IOP5=IO_buff.byte;
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
//=======T0========================
    if(T0IF&&T0IE)
   	{
   	   	T0IF=0;
   	}
//=======ADC=======================
   	if(ADIF&&ADIE)
   	{
   	   	ADIF=0;
   	}
   	__asm
   	   	pop
   	__endasm;
}




















