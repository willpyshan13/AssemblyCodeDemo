//MC30P6250_Data_2020_04_20//
//ע������//
//P13����Ϊ�����ʱΪ���缫��·//

typedef  unsigned char u8;
typedef  char s8;
typedef  unsigned int u16; 
typedef  int s16; 
typedef  unsigned long u32; 
typedef  signed long s32;

typedef  volatile unsigned char vu8;
typedef  volatile char vs8;
typedef  volatile unsigned int vu16; 
typedef  volatile int vs16; 
typedef  volatile unsigned long vu32; 
typedef  volatile signed long vs32;




volatile u8 ABuf,StatusBuf;//�ж϶�ջ����


#define	   	Set_P10_IN()   	DDR10=1 // ����P10Ϊ����
#define	   	Set_P11_IN()   	DDR11=1 // ����P11Ϊ����
#define	   	Set_P12_IN()   	DDR12=1 // ����P12Ϊ����
#define	   	Set_P13_IN()   	DDR13=1 // ����P13Ϊ����
#define	   	Set_P14_IN()   	DDR14=1 // ����P14Ϊ����
#define	   	Set_P15_IN()   	DDR15=1 // ����P15Ϊ����

#define	   	Set_P10_OUT()   DDR10=0 // ����P10Ϊ���
#define	   	Set_P11_OUT()   DDR11=0 // ����P11Ϊ���
#define	   	Set_P12_OUT()   DDR12=0 // ����P12Ϊ���
#define	   	Set_P13_OUT()   DDR13=0 // ����P13Ϊ���
#define	   	Set_P14_OUT()   DDR14=0 // ����P14Ϊ���
#define	   	Set_P15_OUT()   DDR15=0 // ����P15Ϊ���


#define	   	Enable_P10_IPU()   P10PU=0// ����P10��������
#define	   	Enable_P11_IPU()   P11PU=0// ����P11��������
#define	   	Enable_P12_IPU()   P12PU=0// ����P12��������
#define	   	Enable_P13_IPU()   P13PU=0// ����P13��������
#define	   	Enable_P14_IPU()   P14PU=0// ����P14��������
#define	   	Enable_P15_IPU()   P15PU=0// ����P15��������

#define	   	Disable_P10_IPU()  P10PU=1// ����P10����������Ч
#define	   	Disable_P11_IPU()  P11PU=1// ����P11����������Ч
#define	   	Disable_P12_IPU()  P12PU=1// ����P12����������Ч
#define	   	Disable_P13_IPU()  P13PU=1// ����P13����������Ч
#define	   	Disable_P14_IPU()  P14PU=1// ����P14����������Ч
#define	   	Disable_P15_IPU()  P15PU=1// ����P15����������Ч

#define	   	Enable_P10_IPD()  P10PD=0// ����P10��������
#define	   	Enable_P11_IPD()  P11PD=0// ����P11��������
#define	   	Enable_P12_IPD()  P12PD=0// ����P12��������

#define	   	Disable_P10_IPD()  P10PUD=1// ����P10����������Ч
#define	   	Disable_P11_IPD()  P11PUD=1// ����P11����������Ч
#define	   	Disable_P12_IPD()  P12PUD=1// ����P12����������Ч

#define	   	Set_P10_OpenDrain()   P10OD=1 // ʹ�ܶ˿�p10��©���
#define	   	Set_P11_OpenDrain()   P11OD=1 // ʹ�ܶ˿�p11��©���
#define	   	Set_P12_OpenDrain()   P12OD=1 // ʹ�ܶ˿�p12��©���
#define	   	Set_P14_OpenDrain()   P14OD=1 // ʹ�ܶ˿�p14��©���
#define	   	Set_P15_OpenDrain()   P15OD=1 // ʹ�ܶ˿�p15��©���
#define	   	Set_P1_OpenDrain()    ODCON=0xFF // ʹ��p1�˿ڿ�©���

#define	   	Set_P10_Push_Pull()   P10OD=0 // ʹ�ܶ˿�p10�������
#define	   	Set_P11_Push_Pull()   P11OD=0 // ʹ�ܶ˿�p11�������
#define	   	Set_P12_Push_Pull()   P12OD=0 // ʹ�ܶ˿�p12�������
#define	   	Set_P14_Push_Pull()   P14OD=0 // ʹ�ܶ˿�p14�������
#define	   	Set_P15_Push_Pull()   P15OD=0 // ʹ�ܶ˿�p15�������
#define	    Set_P1_Push_Pull()    ODCON=0x00 // ʹ��p1�˿��������

#define	 INT_trigger_fall() INTOM=0//�ⲿ�ж� INT �½��ش���
#define	 INT_trigger_rise() INTOM=1//�ⲿ�ж� INT �����ش���

#define	 T0IE_Enable()  T0IE=1//ʹ�ܶ�ʱ�� T0 ��
#define	 T0IE_Disable() T0IE=0//���ζ�ʱ�� T0 �ж�
#define	 CLR_T0IF()  T0IF=0//�����ʱ�� T0 �жϱ�־λ
#define	 SET_T0IF()  T0IF=1//���ö�ʱ�� T0 �жϱ�־λ

#define	 T0CLK_Select_T0PTS() T0TBS=0//T0 ʱ��Դ�� T0PTS ����
#define	 T0CLK_Select_Flosc() T0TBS=1//T0 ʱ��ԴΪFloscʱ��Դ��

#define	 T0CLK_IN_Fcpu() T0TBS=0; T0PTS=0//T0 ʱ��ԴΪ FCPU��
#define	 T0CLK_IN_Tc0()  T0TBS=0; T0PTS=1 //T0 ʱ��ԴΪ TC0 ������ⲿʱ�ӣ�
#define	 T0COUNT_rise() T0CSE=0//�������������ؼ�����
#define	 T0COUNT_fall() T0CSE=1//���������½��ؼ�����

#define	 T0CLK_DIV2() T0CR=(T0CR&0xF0)
#define	 T0CLK_DIV4() T0CR=(T0CR&0xF0)|0x01
#define	 T0CLK_DIV8() T0CR=(T0CR&0xF0)|0x02
#define	 T0CLK_DIV16() T0CR=(T0CR&0xF0)|0x03
#define	 T0CLK_DIV32() T0CR=(T0CR&0xF0)|0x04
#define	 T0CLK_DIV64() T0CR=(T0CR&0xF0)|0x05
#define	 T0CLK_DIV128() T0CR=(T0CR&0xF0)|0x06
#define	 T0CLK_DIV256() T0CR=(T0CR&0xF0)|0x07


#define	 WDTCLK_DIV1() T0CR=(T0CR&0xF8)
#define	 WDTCLK_DIV2() T0CR=(T0CR&0xF8)|0x09
#define	 WDTCLK_DIV4() T0CR=(T0CR&0xF8)|0x0A
#define	 WDTCLK_DIV8() T0CR=(T0CR&0xF8)|0x0B
#define	 WDTCLK_DIV16() T0CR=(T0CR&0xF8)|0x0C
#define	 WDTCLK_DIV32() T0CR=(T0CR&0xF8)|0x0D
#define	 WDTCLK_DIV64() T0CR=(T0CR&0xF8)|0x0E
#define	 WDTCLK_DIV128() T0CR=(T0CR&0xF8)|0x0F
#define	 Open_WDT() WDTEN=1
#define	 Close_WDT() WDTEN=0

#define	 T1IE_Enable()  T1IE=1//ʹ�ܶ�ʱ�� T1 ��
#define	 T1IE_Disable() T1IE=0//���ζ�ʱ�� T1 �ж�
#define	 CLR_T1IF()  T1IF=0//�����ʱ�� T1 �жϱ�־λ
#define	 SET_T1IF()  T1IF=1//���ö�ʱ�� T1 �жϱ�־λ


#define	 T1_Stop() T1EN=0//ʹ�ܿ���λ,�ر� T1
#define	 T1_Star() T1EN=1//ʹ�ܿ���λ,���� T1
//#define  	 PWM0_Disable() PWM0E=0//PWM0 ʹ��λ,�ر� PWM0 ����
//#define  	 PWM0_Enable()  PWM0E=1//PWM0 ʹ��λ,���� PWM0 ����
//#define  	 BUZE_Disable() BUZE=0//BUZ ���ʹ��λ,��ֹ BUZ ���
//#define  	 BUZE_Eable()  BUZE=1//BUZ ���ʹ��λ,���� BUZ �����


#define	 T1CLK_IN_Fcpu() T1CR=(T1CR&0xE7)//T1ʱ��ԴΪ FCPU��
#define	 T1CLK_IN_FOSC()  T1CR=(T1CR&0xE7)|0x8 //T0 ʱ��ԴΪ FOSC��
#define	 T1COUNT_rise() T1CR=(T1CR&0xE7)|0x10//�ⲿʱ�������ؼ�����
#define	 T1COUNT_fall() T1CR=(T1CR&0xE7)|0x18//�ⲿʱ���½��ؼ�����

#define	 T1CLK_DIV1() T1CR=T1CR&0xF8
#define	 T1CLK_DIV2() T1CR=(T1CR&0xF8)|0x01
#define	 T1CLK_DIV4() T1CR=(T1CR&0xF8)|0x02
#define	 T1CLK_DIV8() T1CR=(T1CR&0xF8)|0x03
#define	 T1CLK_DIV16() T1CR=(T1CR&0xF8)|0x4
#define	 T1CLK_DIV32() T1CR=(T1CR&0xF8)|0x05
#define	 T1CLK_DIV64() T1CR=(T1CR&0xF8)|0x06
#define	 T1CLK_DIV128() T1CR=(T1CR&0xF8)|0x07

#define	 T1CLK_DBCLK_Disable() DBCLK=0//T1 ʱ�Ӳ���Ƶ��
#define	 T1CLK_DBCLK_Enable() DBCLK=0//T1 ʱ�ӱ�Ƶ���� T1PR=000 ʱ��Ч����



#define	 PWM1A_Stop()  	PWM1AOC=1//PWM1A ���ʹ��λ,��ֹ PWM1A ������˿���Ϊ I/O �˿� 
#define	 PWM1A_Star()  	PWM1AOC=0//PWM1A ���ʹ��λ,���� PWM1A ���
#define	 PWM1B_Stop()  	PWM1BOE=0//PWM1B ���ʹ��λ,��ֹ PWM1B ������˿���Ϊ I/O �˿� 
#define	 PWM1B_Star()  	PWM1BOE=1//PWM1B ���ʹ��λ,���� PWM1B ���
#define	 PWM1C_Stop()  	PWM1COE=0//PWM1B ���ʹ��λ,��ֹ PWM1B ������˿���Ϊ I/O �˿� 
#define	 PWM1C_Star()  	PWM1COE=1//PWM1B ���ʹ��λ,���� PWM1B ���
#define	 PWM1D_Stop()  	PWM1DOE=0//PWM1B ���ʹ��λ,��ֹ PWM1B ������˿���Ϊ I/O �˿� 
#define	 PWM1D_Star()  	PWM1DOE=1//PWM1B ���ʹ��λ,���� PWM1B ���

#define	 T1DBCLK_Open()  T1DBCLK=1;//ʱ�ӱ�Ƶ����T1PRS=000 ʱ��Ч����
#define	 T1DBCLK_Close() T1DBCLK=0;//ʱ�Ӳ���Ƶ��

#define	 PWM1A_Disable() PWM1AEN=0//PWM1A ���ʹ��λ,�ر� PWM1A ���
#define	 PWM1A_Enable()  PWM1AEN=1//PWM1A ���ʹ��λ,ʹ�� PWM1A ���
#define	 PWM1B_Disable() PWM1BEN=0//PWM1B ���ʹ��λ,�ر� PWM1B ���
#define	 PWM1B_Enable()  PWM1BEN=1//PWM1B ���ʹ��λ,ʹ�� PWM1B ���
#define	 PWM1C_Disable() PWM1CEN=0//PWM1C ���ʹ��λ,�ر� PWM1C ���
#define	 PWM1C_Enable()  PWM1CEN=1//PWM1C ���ʹ��λ,ʹ�� PWM1C ���
#define	 PWM1D_Disable() PWM1DEN=0//PWM1D ���ʹ��λ,�ر� PWM1D ���
#define	 PWM1D_Enable()  PWM1DEN=1//PWM1D ���ʹ��λ,ʹ�� PWM1D ���

#define	 CLR_PWM1AOS() 	 PWM1AOS=0//���T1PWMD�ź�
#define	 SETB_PWM1AOS()  PWM1AOS=1//���T1PWMD�ķ����ź�
#define	 CLR_PWM1DOS() 	 PWM1DOS=0//���T1PWMD�ź�
#define	 SETB_PWM1DOS()  PWM1DOS=1//���T1PWMB��T1PWMC������߼������ź�

#define	   	PMW1A_DATA     	T1DATA
#define	   	PMW1B_DATA     	T1DATB
#define	   	PMW1C_DATA     	T1DATC
#define	   	PMW1D_DATA     	T1DATD


//�����ж�����
#define	 KBIE_Enable()   KBIE=1// ʹ�ܼ����ж�
#define	 KBIE_Disable()  KBIE=0//���μ����ж�

#define	 P15KE_Enable()  P15KE=1// ʹ�ܶ˿ڼ����жϹ�
#define	 P15KE_Disable() P15KE=0//���ζ˿ڼ����жϹ���
#define	 P14KE_Enable()  P14KE=1// ʹ�ܶ˿ڼ����жϹ�
#define	 P14KE_Disable() P14KE=0//���ζ˿ڼ����жϹ���
#define	 P13KE_Enable()  P13KE=1// ʹ�ܶ˿ڼ����жϹ�
#define	 P13KE_Disable() P13KE=0//���ζ˿ڼ����жϹ���
#define	 P12KE_Enable()  P12KE=1// ʹ�ܶ˿ڼ����жϹ�
#define	 P12KE_Disable() P12KE=0//���ζ˿ڼ����жϹ���
#define	 P11KE_Enable()  P11KE=1// ʹ�ܶ˿ڼ����жϹ�
#define	 P11KE_Disable() P11KE=0//���ζ˿ڼ����жϹ���
#define	 P10KE_Enable()  P10KE=1// ʹ�ܶ˿ڼ����жϹ�
#define	 P10KE_Disable() P10KE=0//���ζ˿ڼ����жϹ���

#define	 GIE_Enable()  GIE=1// �ж�Դ�Ƿ��������Ӧ�Ŀ���λ����
#define	 GIE_Disable() GIE=0//���������ж�

//CMP�Ƚ���
#define	 CMP_Disable() CMPEN=0//�Ƚ���CMPʹ��λ �ر�
#define	 CMP_Enable()  CMPEN=1//�Ƚ���CMPʹ��λ ����

#define	 CMPPS_VIR()   CMPPS=0//�Ƚ���CMP��������Vir
#define	 CMPPS_EVN0()  CMPPS=1//�Ƚ���CMP��������EVN0
#define	 CMPNS_RES()   CMPNS=0//�Ƚ���CMP������������ѹ
#define	 CMPNS_CMPN()  CMPNS=1//�Ƚ���CMP��������CMPN
#define	 CMPNS_RES_VDD()    CMPCR0=(CMPCR0&0xC7)//��ѹ�������VDD
#define	 CMPNS_RES_EVN0()   CMPCR0=(CMPCR0&0xC7)|0x08//��ѹ�������EVN0
#define	 CMPNS_RES_EVN1()   CMPCR0=(CMPCR0&0xC7)|0x10//��ѹ�������EVN1
#define	 CMPNS_RES_EVN2()   CMPCR0=(CMPCR0&0xC7)|0x18//��ѹ�������EVN2
#define	 CMPO_Forward()     CMPNV=0  //�˿���������ƽ
#define	 CMPO_Reverse()     CMPNV=1  //�˿���������ƽ
#define	 CMPOE_Disable()    CMPOE=0  //��ֹ�˿����
#define	 CMPOE_Enable()     CMPOE=1  //����˿����
#define	 CMPIM_rise()       CMPIM=0  //��������ش���
#define	 CMPIM_fall()       CMPIM=1  //��������ش���
#define	 CMPIE_Disable()    CMPCR2=(CMPCR2&0xFC)       //�����ж�,����жϱ�־λ
#define	 CMPIE_Enable()    	CMPCR2=(CMPCR2&0xFC)|0xFE  //ʹ���ж�,����жϱ�־λ��
#define	 CLR_CMPIF()       	CMPIF=0  //����жϱ�־λ


#define NOP()  __asm   NOP  __endasm
 
#define Nop()  	   	   	__asm__("nop")
#define ClrWdt()   	   	__asm__("clrwdt")
#define Stop() 	   	   	__asm__("stop")










