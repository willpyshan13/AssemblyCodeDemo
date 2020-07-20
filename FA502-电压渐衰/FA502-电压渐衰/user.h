//��д����
//��ѹ��λ2.3V
//�ڲ���Ƶ����8M 2��Ƶ+RTC


//Ӳ����������
#define Fosc 8000000UL
#define FINTOSC 4000000UL
#define Fcpu 4000000UL
#define T0_DIV 256
#define T0_Time_us 5000UL
#define T0_DAT_5mS  0xFF-(u8)(Fcpu/100*T0_Time_us/T0_DIV/10000)+1   //

#define Det_VDD_Time_10ms  2//ÿ10ms���һ��  
#define Time_100ms     	   	20//ÿ100ms���һ��  

//#define T1_Time_us 100UL
#define T1_DIV 2
#define T1_DAT  (u8)(Fcpu/100*T1_Time_us/T1_DIV/10000)-1   //


//PWM
#define Fpwm   	20000UL//PMWƵ��Hz
#define	PWM_DAT (u8)(Fcpu/T1_DIV/Fpwm)-1//��ֵ��125
#define	PWM_PERCENT(a)  (PWM_DAT)*a/100

u8     	PWM_Value;
u8     	PWM_Value_Buf;


//EVD��ѹ������ֵ��Χ
#define EVD_VDD_MIN    0x20    //��Ӧ��ѹֵ2.80v
#define EVD_VDD_MAX    0x36    //��Ӧ��ѹֵ4.34v
#define EVD_VDD_H_CONST  120    //���ߵ�ƽ����
#define EVD_VDD_L_CONST  -120   //���͵�ƽ����


#define EVD_VSolar_MIN    0x00    //��Ӧ��ѹֵ0.56v
#define EVD_VSolar_MAX    0x3F    //��Ӧ��ѹֵ4.97v
#define EVD_VSolar_H_CONST  5    //���ߵ�ƽ����
#define EVD_VSolar_L_CONST  -5   //���͵�ƽ����



#define EVD_301   0x23    //��Ӧ��ѹֵ3.01v
#define EVD_329   0x27    //��Ӧ��ѹֵ3.29v
#define EVD_343   0x29    //��Ӧ��ѹֵ3.43v
#define EVD_350   0x2A    //��Ӧ��ѹֵ3.50v
#define EVD_364   0x2C    //��Ӧ��ѹֵ3.64v
#define EVD_371   0x2D    //��Ӧ��ѹֵ3.71v
#define EVD_392   0x30    //��Ӧ��ѹֵ3.92v
#define EVD_406   0x32    //��Ӧ��ѹֵ3.06v
//POWER_ON/OFF
#define  POWER_ON_VALUE    	0x20    //��Ӧ��ѹֵ2.8v
#define  POWER_OFF_VALUE   	0x1A    //��Ӧ��ѹֵ2.38v

//IO����
#define SW_IN  	  P10D
#define V_Solar  P15D

#define LED1_OFF() P12D=0
#define LED1_ON()  P12D=1


typedef union 
{
   	u8  a;
   	u16 b;
} U8_U16;
volatile U8_U16  dely;
#define  a_u8  	 dely.a
#define  b_u16   dely.b

typedef struct 
{
   	u8 bit0:1;
   	u8 bit1:1;
   	u8 bit2:1;
   	u8 bit3:1;
   	u8 bit4:1;
   	u8 bit5:1;
   	u8 bit6:1;
   	u8 bit7:1;
}Bit_Flag;
volatile Bit_Flag     Flag1;
#define  Det_VSolar_EN      Flag1.bit1//0--��ؼ��Ϊ�͵�ѹ,1--��ؼ��Ϊ�ߵ�ѹ
#define  PWM_EN        	   	   	Flag1.bit2//0--��ؼ��Ϊ�͵�ѹ,1--��ؼ��Ϊ�ߵ�ѹ
#define  Bat1_U_D      	   	Flag1.bit3//0--��ص�ѹΪ��λ��ѹ,1--���Ϊ��λ��ѹ
#define  Bat2_U_D      	   	Flag1.bit4//0--��ص�ѹΪ��λ��ѹ,1--���Ϊ��λ��ѹ
#define  LED_Running_Falg   Flag1.bit5//0--LEDֹͣ����,1--LED��������
#define  Det_VDD_EN        	Flag1.bit6//0--ֹͣ���VDD��ѹ,1--��ʼ���VDD��ѹ
#define  CMPOF_Buf         	Flag1.bit7


vu8 	   	Det_VDD_Value;
vu8 	   	Det_VDD_NUM;//CMPOF_Buf=1,Det_VDD_NUM++;CMPOF_Buf=0,Det_VDD_NUM--;
vu8 	   	Det_VDD_Time;//���ʱ��
vu8 	   	Det_VDD_Value_Buf0;
vu8 	   	Det_VDD_Value_Buf1;
vu8 	   	VDD_Value;


u8 	   	Det_VSolar_Value;
u8 	   	Det_VSolar_NUM;//CMPOF_Buf=1,Det_VDD_NUM++;CMPOF_Buf=0,Det_VDD_NUM--;
u8 	   	Det_VSolar_Time;//���ʱ��
u8 	   	Det_VSolar_Value_Buf0;
u8 	   	Det_VSolar_Value_Buf1;


u8     	Sleep_Time;
u8     	Timing_Value1;
vu8    	Temp8;
vu8    	Temp8_i;
vu8    	Temp8_j;

//u8 __at 0x3C             	Sleep_Time;

