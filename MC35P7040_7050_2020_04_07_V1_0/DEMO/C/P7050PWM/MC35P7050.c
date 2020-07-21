/******************************************************************************
;  *   	@MCU   	   	   	   	 : MC35P7050
;  *   	@Create Date         : 2019.12.29
;  *   	@Author/Corporation  : Martin/SinoMCU
;  *   	@����֧��QQȺ   	   	  : 814641858      
;  *    @����΢�ٷ���̳   	   	  : http://bbs.sinomcu.com/	 
;  *   	@Copyright           : 2019 SINOMCU Corporation,All Rights Reserved.
;  *----------------------Abstract Description--------------------------------- 
       	    	P44��P53 PWM���   	   	
   	    	7050����ʹ��7040�����
            ���PWM��Ҫ����ӳ�书��
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
    movai 0x3F 
    movra FSR0
    clrr FSR1
    clrr INDF
    DJZR FSR0 
    goto $ -2
    clrr INDF
__endasm;
}
/************************************************
;  *    @Function Name       : IO_Config
;  *    @Description         : io�ڳ�ʼ��
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/
void IO_Init(void)
{
    IOP0 = 0x00; //io������λ
    OEP0 = 0xff; //io�ڷ��� 1:out  0:in
    PUP0 = 0x00; //io����������   1:enable  0:disable

    IOP4 = 0x00; //io������λ
    OEP4 = 0xff; //io�ڷ��� 1:out  0:in
    PUP4 = 0x00; //io����������   1:enable  0:disable

    IOP5 = 0x00; //io������λ
    OEP5 = 0xff; //io�ڷ��� 1:out  0:in
    PUP5 = 0x00; //io����������   1:enable  0:disable

    P4CON = 0x00;
}
/************************************************
;  *    @Function Name       : TIMER0_PWM_Init
;  *    @Description         : ��ʱ����ʼ��
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/
void TIMER0_PWM_Init(void)
{
    TMRCR = 0;   //T1CLK=FCPU/2      T0CLK=FCPU/2    �ر�T0�������
    T0CR = 0xF1; //����T0 1��Ƶ  T0CLK�ڲ�ʱ��  �Զ�����  ����PWM  256ʱ��
    //T0CNT = 256 - 125;
    T0LDR = 0x7f; 
}
/************************************************
;  *    @Function Name       : TIMER1_PWM_Init
;  *    @Description         : 
;  *    @IN_Parameter        :
;  *    @Return parameter    :
;  ***********************************************/
void TIMER1_PWM_Init(void)
{
    T1CR = 0xf1;
    T1LDR = 0x80; //����T1    1��Ƶ  T1CLK�ڲ�ʱ��  ����PWM  256������
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
    TIMER0_PWM_Init();
    TIMER1_PWM_Init();
    GIE = 1;
}
void main(void)
{
    Sys_Init();
    while (1)
    {

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
