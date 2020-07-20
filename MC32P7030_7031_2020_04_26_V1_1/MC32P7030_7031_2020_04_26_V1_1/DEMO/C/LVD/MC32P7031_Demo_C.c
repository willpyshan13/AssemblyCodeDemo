/******************************************************************************
;  *   	@MCU				 : MC32P7031
;  *   	@Create Date         : 2019.12.29
;  *   	@Author/Corporation  : Martin/SinoMCU
;  *   	@����֧��QQȺ		  : 814641858      
;  *    @����΢�ٷ���̳		  : http://bbs.sinomcu.com/	 
;  *   	@Copyright           : 2019 SINOMCU Corporation,All Rights Reserved.
;  *----------------------Abstract Description---------------------------------
;  *	 				��¼ʱѡ��LVD3.0V 
						����3.0VʱLVD36��־��1  P01����ߣ���֮����ͣ�
						LVD˵����
						LVD���ֵ����¼ʱ��д�̶���
						����ѹС��2.7Vʱ�������м��LVD24�����־λ
						����ѹ���ڵ���2.7Vʱ�������м��LVD36�����־��
						�磺���3.0V��ȥ�ж�LVD36��Ϊ1�����3.0V����֮
						�磺���4.0V��ȥ�ж�LVD36��Ϊ1�����4.0V����֮
						ʹ��ע��LVD���

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
   	movai  	0x7F
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
;  *    @Description         : IO��ʼ��
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
   	ANSEL=0x00;    	   	//io����ѡ��  1:ģ������  0:ͨ��io
   	
   	IOP5=0x00; 	   	   	//io������λ
   	OEP5=0xff; 	   	   	//io�ڷ��� 1:out  0:in  
   	PUP5=0x00; 	   	   	//io����������   1:enable  0:disable
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
   	GIE=1;        
}
void main(void)
{
   	Sys_Init();
   	while(1)
   	{
   	   	if(LVD36)  	   	//LVD��¼ѡ��3.0V
   	   	{
   	   	   	P01D=1;
   	   	}else P01D=0;   
   	}
}

void int_isr(void) __interrupt
{

   	__asm
   	   	push
   	__endasm;

   	__asm
   	   	pop
   	__endasm;
}




















