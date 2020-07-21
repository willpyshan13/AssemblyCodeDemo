/******************************************************************************
;  *   	@MCU   	   	   	   	 : MC35P7040
;  *   	@Create Date         : 2019.12.29
;  *   	@Author/Corporation  : Martin/SinoMCU
;  *   	@����֧��QQȺ   	   	  : 814641858      
;  *    @����΢�ٷ���̳   	   	  : http://bbs.sinomcu.com/	 
;  *   	@Copyright           : 2019 SINOMCU Corporation,All Rights Reserved.
;  *----------------------Abstract Description--------------------------------- 
                        T0��ʱ1mS�ж� P54��ת
                        T1��P53�����PWM
                        T0��ʱ5S�������ߣ�P00����
                        P40.P41.VDD AD�ɼ�  
                        ����У׼ʵ��Ӧ���Ƕ�ѡһ
                        ƫ0   ѡ���У׼
                        ƫvdd ѡ����У׼
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
    OEP0 = 0xfe; //io�ڷ��� 1:out  0:in
    PUP0 = 0x01; //io����������   1:enable  0:disable

    IOP4 = 0x00; //io������λ
    OEP4 = 0xfC; //io�ڷ��� 1:out  0:in
    PUP4 = 0x00; //io����������   1:enable  0:disable

    IOP5 = 0x00; //io������λ
    OEP5 = 0xff; //io�ڷ��� 1:out  0:in
    PUP5 = 0x00; //io����������   1:enable  0:disable

    P4CON = 0x03;  	   	//P40 P41ģ��
}
/************************************************
;  *    @Function Name       : TIMER0_INT_Init
;  *    @Description         : ��ʱ����ʼ��
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/
void TIMER0_INT_Init(void)
{
    TMRCR = 0;   //T1CLK=FCPU/2      T0CLK=FCPU/2    �ر�T0�������
    T0CR = 0xA4; //����T0    32��Ƶ  T0CLK�ڲ�ʱ��  �Զ�����  �ر�PWM
    T0CNT = 256 - 125;
    T0LDR = 256 - 125; // 1ms
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
    T1CR = 0xf1;
    T1LDR = 0x80; //����T1    1��Ƶ  T1CLK�ڲ�ʱ��  ����PWM  256������
}
/************************************************
;  *    @Function Name       : ADC_Config
;  *    @Description         : ADC��ʼ��
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/
void ADC_Init(void)
{
    ADM &= 0x00;
    ADM |= 0x90;
    VREFCR = 0; //�ڲ�2V
    ADR = 0;    //adcʱ��  Fcpu/64
}
/************************************************
;  *    @Function Name       : ADC_Zero_ADJ
;  *    @Description         : ADC���У׼
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    : 0 У׼�ɹ�  1У׼ʧ��
;  ***********************************************/
uint8_t ADC_Zero_ADJ(void)
{
    //���У׼
    ADT = 0x80; //���У׼   ADTR[4:0]=0
    VREFCR = 0; //�ڲ�2V
    ADR = 0;    //64��Ƶ
    GCHS = 1;
    ADEN = 1;

    ADEOC = 0;
    ADSTR = 1;
    while (!ADEOC);
    if ((ADB == 0) && ((ADR & 0x0F) == 0)) //����Ƿ�Ϊ0
    {
        ADT |= 0x1F;
        ADEOC = 0;
        ADSTR = 1;
        while (!ADEOC);
        if ((ADB == 0) && ((ADR & 0x0F) == 0)) //����Ƿ�Ϊ0
        {
            ADT &= 0x3f; //����ģʽ
            ADEN=0;
            return PASS;         
        }
        else
        {
            while (1)
            {
                if (ADT & 0x0f)
                {
                    ADT--;
                    ADEOC = 0;
                    ADSTR = 1;
                    while (!ADEOC);
                    if ((ADB == 0) && ((ADR & 0x0F) == 0)) //����Ƿ�Ϊ0
                    {
                        ADT &= 0x3f; //����ģʽ
                        ADEN=0;
                        return PASS;
                    }
                }
                else 
                {
                    ADT &= 0x3f; //����ģʽ
                    ADEN=0;
                    return FAIL;
                }
            }
        }
    }
    else
    {
        while (1)
        {
            if ((ADT & 0x0f) == 0x0f) 
            {
                ADT &= 0x3f; //����ģʽ
                ADEN=0;
                return FAIL;
            }
            else
            {
                ADT++;
                ADEOC = 0;
                ADSTR = 1;
                while (!ADEOC);
                if ((ADB == 0) && ((ADR & 0x0F) == 0)) //����Ƿ�Ϊ0
                {
                    ADT &= 0x3f; //����ģʽ
                    ADEN=0;
                    return PASS;
                }
            }
        }
    }
}
/************************************************
;  *    @Function Name       : ADC_Vertex_ADJ
;  *    @Description         : ADC����У׼
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    : 0 У׼�ɹ�  1У׼ʧ��
;  ***********************************************/
uint8_t ADC_Vertex_ADJ(void)
{
    //����У׼
    ADT = 0xD0; //����У׼   ADTR[4:0]=0x10
    VREFCR = 0; //�ڲ�2V
    ADR = 0;    //64��Ƶ
    GCHS = 1;
    ADEN = 1;

    ADEOC = 0;
    ADSTR = 1;
    while (!ADEOC);
    if ((ADB == 0xff) && ((ADR & 0x0F) == 0x0f)) //����Ƿ�Ϊ0x0fff
    {
        ADT &= 0xE0;
        ADT |= 0x0F;
        ADEOC = 0;
        ADSTR = 1;
        while (!ADEOC);
        if ((ADB == 0xff) && ((ADR & 0x0F) == 0x0f)) //����Ƿ�Ϊ0x0fff
        {
            ADT &= 0x3f; //����ģʽ
            ADEN=0;
            return PASS;
        }
        else
        {
            while (1)
            {
                if (ADT & 0x0f)
                {
                    ADT--;
                    ADEOC = 0;
                    ADSTR = 1;
                    while (!ADEOC);
                    if ((ADB == 0xff) && ((ADR & 0x0F) == 0x0f)) //����Ƿ�Ϊ0x0fff
                    {
                        ADT &= 0x3f; //����ģʽ
                        ADEN=0;
                        return PASS;
                    }
                }
                else 
                {
                    ADT &= 0x3f; //����ģʽ
                    ADEN=0;
                    return FAIL;
                }
            }
        }
    }
    else
    {
        while (1)
        {
            if ((ADT & 0x0f) == 0x0f) 
            {
                ADT &= 0x3f; //����ģʽ
                ADEN=0;
                return FAIL;
            }
            else
            {
                ADT++;
                ADEOC = 0;
                ADSTR = 1;
                while (!ADEOC);
                if ((ADB == 0xff) && ((ADR & 0x0F) == 0x0f)) //����Ƿ�Ϊ0x0fff
                {
                    ADT &= 0x3f; //����ģʽ
                    ADEN=0;
                    return PASS;
                }
            }
        }
    }
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
/**************************
     ����У׼ʵ��Ӧ���Ƕ�ѡһ
    ƫ0   ѡ���У׼
    ƫvdd ѡ����У׼ 
***************************/
    while(ADC_Zero_ADJ()); 	   	//demo��ʾ,У׼ʧ��һֱУ׼
  //  while(ADC_Vertex_ADJ());        //ADCУ׼
    TIMER0_INT_Init();
    TIMER1_PWM_Init();
    ADC_Init();
    GIE = 1;
}
/************************************************
;  *    @Function Name       : ADC_Get_Value_Average
;  *    @Description         : ����ת��
;  *    @IN_Parameter      	 : ͨ��
;  *    @Return parameter    : ����ADC��ֵ
   	   	  ����ռ���ڴ�ϴ�180+�ֽڣ���
;  ***********************************************/
uint ADC_Get_Value_Average(u8 CHX)
{
    u16 temp_value = 0;
    u8 channel = 0;
    unsigned long int tmpbuff = 0;
    u16 ADCMAX = 0;
    u16 ADCMIN = 0xffff;

    ADM = (ADM & 0xf8) | CHX; // ADC ʹ��  ADת��ͨ������  ͨ��  CHX
    for (channel = 0; channel < 20; channel++)
    {
        ADEOC = 0;
        ADSTR = 1; // ��ʼת��
        while (!ADEOC); //�ȴ�ת�����
        temp_value = ADB;
        temp_value = temp_value << 4 | (ADR & 0x0f);
        if (channel < 2)
            continue; //����ǰ���β�����
        if (temp_value > ADCMAX)
            ADCMAX = temp_value; //���
        if (temp_value < ADCMIN)
            ADCMIN = temp_value; //��С
        tmpbuff += temp_value;
    }
    tmpbuff -= ADCMAX;           //ȥ��һ�����
    tmpbuff -= ADCMIN;           //ȥ��һ����С
    temp_value = (tmpbuff >> 4); //����16��ȡƽ��ֵ
    return temp_value;
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
            //д��һ
            FLAG_TIMER0_5000ms = 0;
            GIE = 0; //���߹ر�����
            ADEN = 0;
   	   	   	PWM1OE=0;
   	   	   	T1EN=0;
            IOP5 = 0;
            Nop();
            OSCM &= 0xE7;
            OSCM |= 0x08;
            Nop();
            Nop();
            Nop();
            GIE = 1;
   	   	   	PWM1OE=1;
   	   	   	T1EN=1;
            ADEN = 1; //���Ѻ�������

            /*д����
            FLAG_TIMER0_5000ms=0; 
   	   	   	GIE = 0; //���߹ر�����
            ADEN = 0;
   	   	   	PWM1OE=0;
   	   	   	T1EN=0;
            IOP5 = 0;
   	       	HFDE=1;
   	   	   	Nop();
   	   	   	Nop();
   	   	   	Nop();
   	        HFDE=0;
   	       	GIE = 1;
   	   	   	PWM1OE=1;
   	   	   	T1EN=1;
            ADEN = 1; //���Ѻ�������  */
        }
    }
}

void int_isr(void) __interrupt
{
    __asm 
    push
    __endasm;
    if (T0IF && T0IE)
    {
        T0IF = 0;
        P54D = !P54D;
        timer0_count1++;
        if (timer0_count1 >= 5000)
        {
            timer0_count1 = 0;
            FLAG_TIMER0_5000ms = 1;
        }
    }

    __asm 
    pop
    __endasm;
}
