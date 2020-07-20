/******************************************************************************
;  *   	@MCU   	   	   	   	 : MC32P7031
;  *   	@Create Date         : 2019.12.29
;  *   	@Author/Corporation  : Martin/SinoMCU
;  *   	@����֧��QQȺ   	   	  : 814641858      
;  *    @����΢�ٷ���̳   	   	  : http://bbs.sinomcu.com/	 
;  *   	@Copyright           : 2019 SINOMCU Corporation,All Rights Reserved.
;  *----------------------Abstract Description---------------------------------
;  *   	   	   	P54 1ms��ת  P53���PWM  P00���� P40.P41.VDDAD�ɼ�

   	   	   	   	ע�� 7031����ֱ�Ӷ�IOĳһλ
   	   	   	   	   	�� if(P54D==x)
   	   	   	   	   	   	P54D=!P54D;
   	   	   	   	   	��Ϊ ������IO������һ������
   	   	   	   	   	   	buff=IOP5;
   	   	   	   	   	   	���ж�buffĳһλ
******************************************************************************/

#include "MC32P7031.h"
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
   	OEP4 = 0xfC;  //io�ڷ��� 1:out  0:in      	P40  41in
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
   	TXCR = 0x08; //T0ʱ�� T0 T2 Fcpu  T1 Fhosc ��ֹT0����

   	T0CR = 0xD4; //�ڲ� 8��Ƶ  �����Զ�����
   	T0C = 256 - 125;
   	T0D = 256 - 125; //1ms
   	T0IF = 0;
   	T0IE = 1;
}
/************************************************
;  *    @Function Name       : TIMER1_PWM_Init
;  *    @Description         : 
;  *    @IN_Parameter        :
;  *    @Return parameter    :
;  ***********************************************/
void TIMER1_PWM_Init(void)
{
   	T1CR = 0xF1;
   	T1C = 0;
   	T1D = 127;
}
/************************************************
;  *    @Function Name       : ADC_Init
;  *    @Description         : ADC��ʼ��
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/
void ADC_Init(void)
{
   	ANSEL |= 0x03; //P40 1  ģ������  1 ģ������  0  IO��
   	ADCR &= 0x00;
   	ADCR |= 0x90;
   	VREF = 0x00; //�����ڲ��ο���ѹ Ϊ2.0V
   	ADRL &= 0x80;
   	ADRL |= 0x20; //adcʱ��  Fcpu/16
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
   	TIMER1_PWM_Init();
   	ADC_Init();
   	GIE = 1;
}
/************************************************
;  *    @Function Name       : ADC_Get_Value
;  *    @Description         : ADC����ת��
;  *    @IN_Parameter      	 : CHX  ADCͨ��
;  *    @Return parameter    : ��ͨ��ADC��ֵ
;  ***********************************************/
uint ADC_Get_Value(uchar CHX)
{
   	u16 ADC_temp_value;

   	ADCR = (ADCR & 0xf8) | CHX; // ADC ʹ��  ADת��ͨ������  ͨ��  CHX

   	if (changl_Num != CHX) //ͨ���л���  ��ȥ
   	{
   	   	changl_Num = CHX;
   	   	ADEOC = 0;
   	   	ADST = 1; // ��ʼת��
   	   	while (ADEOC == 0)
   	   	{ // ���EOC�ı�־λ   �ȴ�ת�����
   	   	}
   	}
   	ADEOC = 0;
   	ADST = 1; // ��ʼת��
   	while (ADEOC == 0)
   	{ // ���EOC�ı�־λ   �ȴ�ת�����
   	}
   	ADC_temp_value = ADRH;
   	ADC_temp_value = ADC_temp_value << 4 | (ADRL & 0x0f);

   	return ADC_temp_value; // ���ADCת��������
}
/************************************************
;  *    @Function Name       : ADC_Get_Value_Average
;  *    @Description         : ����ת��
;  *    @IN_Parameter      	 : ͨ��
;  *    @Return parameter    : ����ADC��ֵ
;  ***********************************************/
uint ADC_Get_Value_Average(uchar CHX)
{
   	u8 channel = 0;
   	unsigned long int tmpBuff = 0;
   	u16 ADCMAX = 0;
   	u16 ADCMIN = 0xffff;
   	u16 ADC_temp_value;

   	ADCR = (ADCR & 0xf8) | CHX; // ADC ʹ��  ADת��ͨ������  ͨ��  CHX
   	for (channel = 0; channel < 20; channel++)
   	{
   	   	ADEOC = 0;
   	   	ADST = 1; // ��ʼת��
   	   	while (!ADEOC)
   	   	   	; //�ȴ�ת�����
   	   	ADC_temp_value = ADRH;
   	   	ADC_temp_value = ADC_temp_value << 4 | (ADRL & 0x0f);
   	   	if (channel < 2)
   	   	   	continue; //����ǰ���β�����
   	   	if (ADC_temp_value > ADCMAX)
   	   	   	ADCMAX = ADC_temp_value; //���
   	   	if (ADC_temp_value < ADCMIN)
   	   	   	ADCMIN = ADC_temp_value; //��С
   	   	tmpBuff += ADC_temp_value;
   	}
   	tmpBuff -= ADCMAX; 	   	   	   	 //ȥ��һ�����
   	tmpBuff -= ADCMIN; 	   	   	   	 //ȥ��һ����С
   	ADC_temp_value = (tmpBuff >> 4); //����16��ȡƽ��ֵ
   	return ADC_temp_value;
}
void main(void)
{
   	Sys_Init();
   	while (1)
   	{
   	   	ADC_num_value = ADC_Get_Value_Average(0);
   	   	ADC_num_value = ADC_Get_Value_Average(1);
   	   	ADC_num_value = ADC_Get_Value_Average(5); //VDD/4
   	   	if (FLAG_TIMER0_5000ms)
   	   	{
   	   	   	FLAG_TIMER0_5000ms = 0;
   	   	   	GIE = 0;
   	   	   	ADON = 0;
   	   	   	PWM1OE=0;
   	   	   	TC1EN=0;
   	   	   	IOP5 = 0;   	   	   	//�ر�����
   	   	   	Nop();
   	   	   	Nop();
   	   	   	OSCM &= 0xE7;
   	   	   	OSCM |= 0x08;
   	   	   	Nop();
   	   	   	Nop();
   	   	   	Nop(); 	   	   	
   	   	   	GIE = 1;
   	   	   	PWM1OE=1;
   	   	   	TC1EN=1;
   	   	   	ADON = 1;  	   	//���Ѻ�������
   	   	}
   	}
}

void int_isr(void) __interrupt
{

   	__asm 
   	push
   	__endasm;
   	//=======T0========================
   	if (T0IF && T0IE)
   	{
   	   	T0IF = 0;
   	   	IO_buff.byte = IOP5;
   	   	IO_BIT4 = !IO_BIT4;
   	   	IOP5 = IO_buff.byte;
   	   	timer0_count1++;
   	   	if (timer0_count1 >= 5000) //5s
   	   	{
   	   	   	timer0_count1 = 0;
   	   	   	FLAG_TIMER0_5000ms = 1;
   	   	}
   	}
   	//=======ADC=======================
   	if (ADIF && ADIE)
   	{
   	   	ADIF = 0;
   	}
   	__asm 
   	pop
   	__endasm;
}
