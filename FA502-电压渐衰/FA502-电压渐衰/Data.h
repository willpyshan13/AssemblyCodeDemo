//MC30P6250_Data_2020_04_20//
//注意事项//
//P13口作为输出口时为集电极开路//

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




volatile u8 ABuf,StatusBuf;//中断堆栈变量


#define	   	Set_P10_IN()   	DDR10=1 // 设置P10为输入
#define	   	Set_P11_IN()   	DDR11=1 // 设置P11为输入
#define	   	Set_P12_IN()   	DDR12=1 // 设置P12为输入
#define	   	Set_P13_IN()   	DDR13=1 // 设置P13为输入
#define	   	Set_P14_IN()   	DDR14=1 // 设置P14为输入
#define	   	Set_P15_IN()   	DDR15=1 // 设置P15为输入

#define	   	Set_P10_OUT()   DDR10=0 // 设置P10为输出
#define	   	Set_P11_OUT()   DDR11=0 // 设置P11为输出
#define	   	Set_P12_OUT()   DDR12=0 // 设置P12为输出
#define	   	Set_P13_OUT()   DDR13=0 // 设置P13为输出
#define	   	Set_P14_OUT()   DDR14=0 // 设置P14为输出
#define	   	Set_P15_OUT()   DDR15=0 // 设置P15为输出


#define	   	Enable_P10_IPU()   P10PU=0// 设置P10上拉电阻
#define	   	Enable_P11_IPU()   P11PU=0// 设置P11上拉电阻
#define	   	Enable_P12_IPU()   P12PU=0// 设置P12上拉电阻
#define	   	Enable_P13_IPU()   P13PU=0// 设置P13上拉电阻
#define	   	Enable_P14_IPU()   P14PU=0// 设置P14上拉电阻
#define	   	Enable_P15_IPU()   P15PU=0// 设置P15上拉电阻

#define	   	Disable_P10_IPU()  P10PU=1// 设置P10上拉电阻无效
#define	   	Disable_P11_IPU()  P11PU=1// 设置P11上拉电阻无效
#define	   	Disable_P12_IPU()  P12PU=1// 设置P12上拉电阻无效
#define	   	Disable_P13_IPU()  P13PU=1// 设置P13上拉电阻无效
#define	   	Disable_P14_IPU()  P14PU=1// 设置P14上拉电阻无效
#define	   	Disable_P15_IPU()  P15PU=1// 设置P15上拉电阻无效

#define	   	Enable_P10_IPD()  P10PD=0// 设置P10下拉电阻
#define	   	Enable_P11_IPD()  P11PD=0// 设置P11下拉电阻
#define	   	Enable_P12_IPD()  P12PD=0// 设置P12下拉电阻

#define	   	Disable_P10_IPD()  P10PUD=1// 设置P10下拉电阻无效
#define	   	Disable_P11_IPD()  P11PUD=1// 设置P11下拉电阻无效
#define	   	Disable_P12_IPD()  P12PUD=1// 设置P12下拉电阻无效

#define	   	Set_P10_OpenDrain()   P10OD=1 // 使能端口p10开漏输出
#define	   	Set_P11_OpenDrain()   P11OD=1 // 使能端口p11开漏输出
#define	   	Set_P12_OpenDrain()   P12OD=1 // 使能端口p12开漏输出
#define	   	Set_P14_OpenDrain()   P14OD=1 // 使能端口p14开漏输出
#define	   	Set_P15_OpenDrain()   P15OD=1 // 使能端口p15开漏输出
#define	   	Set_P1_OpenDrain()    ODCON=0xFF // 使能p1端口开漏输出

#define	   	Set_P10_Push_Pull()   P10OD=0 // 使能端口p10推完输出
#define	   	Set_P11_Push_Pull()   P11OD=0 // 使能端口p11推完输出
#define	   	Set_P12_Push_Pull()   P12OD=0 // 使能端口p12推完输出
#define	   	Set_P14_Push_Pull()   P14OD=0 // 使能端口p14推完输出
#define	   	Set_P15_Push_Pull()   P15OD=0 // 使能端口p15推完输出
#define	    Set_P1_Push_Pull()    ODCON=0x00 // 使能p1端口推完输出

#define	 INT_trigger_fall() INTOM=0//外部中断 INT 下降沿触发
#define	 INT_trigger_rise() INTOM=1//外部中断 INT 上升沿触发

#define	 T0IE_Enable()  T0IE=1//使能定时器 T0 中
#define	 T0IE_Disable() T0IE=0//屏蔽定时器 T0 中断
#define	 CLR_T0IF()  T0IF=0//清除定时器 T0 中断标志位
#define	 SET_T0IF()  T0IF=1//设置定时器 T0 中断标志位

#define	 T0CLK_Select_T0PTS() T0TBS=0//T0 时钟源由 T0PTS 决定
#define	 T0CLK_Select_Flosc() T0TBS=1//T0 时钟源为Flosc时钟源；

#define	 T0CLK_IN_Fcpu() T0TBS=0; T0PTS=0//T0 时钟源为 FCPU；
#define	 T0CLK_IN_Tc0()  T0TBS=0; T0PTS=1 //T0 时钟源为 TC0 输入的外部时钟；
#define	 T0COUNT_rise() T0CSE=0//输入脉冲上升沿计数；
#define	 T0COUNT_fall() T0CSE=1//输入脉冲下降沿计数；

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

#define	 T1IE_Enable()  T1IE=1//使能定时器 T1 中
#define	 T1IE_Disable() T1IE=0//屏蔽定时器 T1 中断
#define	 CLR_T1IF()  T1IF=0//清除定时器 T1 中断标志位
#define	 SET_T1IF()  T1IF=1//设置定时器 T1 中断标志位


#define	 T1_Stop() T1EN=0//使能控制位,关闭 T1
#define	 T1_Star() T1EN=1//使能控制位,开启 T1
//#define  	 PWM0_Disable() PWM0E=0//PWM0 使能位,关闭 PWM0 功能
//#define  	 PWM0_Enable()  PWM0E=1//PWM0 使能位,开启 PWM0 功能
//#define  	 BUZE_Disable() BUZE=0//BUZ 输出使能位,禁止 BUZ 输出
//#define  	 BUZE_Eable()  BUZE=1//BUZ 输出使能位,允许 BUZ 输出；


#define	 T1CLK_IN_Fcpu() T1CR=(T1CR&0xE7)//T1时钟源为 FCPU；
#define	 T1CLK_IN_FOSC()  T1CR=(T1CR&0xE7)|0x8 //T0 时钟源为 FOSC；
#define	 T1COUNT_rise() T1CR=(T1CR&0xE7)|0x10//外部时钟上升沿计数；
#define	 T1COUNT_fall() T1CR=(T1CR&0xE7)|0x18//外部时钟下降沿计数；

#define	 T1CLK_DIV1() T1CR=T1CR&0xF8
#define	 T1CLK_DIV2() T1CR=(T1CR&0xF8)|0x01
#define	 T1CLK_DIV4() T1CR=(T1CR&0xF8)|0x02
#define	 T1CLK_DIV8() T1CR=(T1CR&0xF8)|0x03
#define	 T1CLK_DIV16() T1CR=(T1CR&0xF8)|0x4
#define	 T1CLK_DIV32() T1CR=(T1CR&0xF8)|0x05
#define	 T1CLK_DIV64() T1CR=(T1CR&0xF8)|0x06
#define	 T1CLK_DIV128() T1CR=(T1CR&0xF8)|0x07

#define	 T1CLK_DBCLK_Disable() DBCLK=0//T1 时钟不倍频；
#define	 T1CLK_DBCLK_Enable() DBCLK=0//T1 时钟倍频（仅 T1PR=000 时有效）；



#define	 PWM1A_Stop()  	PWM1AOC=1//PWM1A 输出使能位,禁止 PWM1A 输出，端口作为 I/O 端口 
#define	 PWM1A_Star()  	PWM1AOC=0//PWM1A 输出使能位,允许 PWM1A 输出
#define	 PWM1B_Stop()  	PWM1BOE=0//PWM1B 输出使能位,禁止 PWM1B 输出，端口作为 I/O 端口 
#define	 PWM1B_Star()  	PWM1BOE=1//PWM1B 输出使能位,允许 PWM1B 输出
#define	 PWM1C_Stop()  	PWM1COE=0//PWM1B 输出使能位,禁止 PWM1B 输出，端口作为 I/O 端口 
#define	 PWM1C_Star()  	PWM1COE=1//PWM1B 输出使能位,允许 PWM1B 输出
#define	 PWM1D_Stop()  	PWM1DOE=0//PWM1B 输出使能位,禁止 PWM1B 输出，端口作为 I/O 端口 
#define	 PWM1D_Star()  	PWM1DOE=1//PWM1B 输出使能位,允许 PWM1B 输出

#define	 T1DBCLK_Open()  T1DBCLK=1;//时钟倍频（仅T1PRS=000 时有效）；
#define	 T1DBCLK_Close() T1DBCLK=0;//时钟不倍频；

#define	 PWM1A_Disable() PWM1AEN=0//PWM1A 输出使能位,关闭 PWM1A 输出
#define	 PWM1A_Enable()  PWM1AEN=1//PWM1A 输出使能位,使能 PWM1A 输出
#define	 PWM1B_Disable() PWM1BEN=0//PWM1B 输出使能位,关闭 PWM1B 输出
#define	 PWM1B_Enable()  PWM1BEN=1//PWM1B 输出使能位,使能 PWM1B 输出
#define	 PWM1C_Disable() PWM1CEN=0//PWM1C 输出使能位,关闭 PWM1C 输出
#define	 PWM1C_Enable()  PWM1CEN=1//PWM1C 输出使能位,使能 PWM1C 输出
#define	 PWM1D_Disable() PWM1DEN=0//PWM1D 输出使能位,关闭 PWM1D 输出
#define	 PWM1D_Enable()  PWM1DEN=1//PWM1D 输出使能位,使能 PWM1D 输出

#define	 CLR_PWM1AOS() 	 PWM1AOS=0//输出T1PWMD信号
#define	 SETB_PWM1AOS()  PWM1AOS=1//输出T1PWMD的反向信号
#define	 CLR_PWM1DOS() 	 PWM1DOS=0//输出T1PWMD信号
#define	 SETB_PWM1DOS()  PWM1DOS=1//输出T1PWMB和T1PWMC的组合逻辑反向信号

#define	   	PMW1A_DATA     	T1DATA
#define	   	PMW1B_DATA     	T1DATB
#define	   	PMW1C_DATA     	T1DATC
#define	   	PMW1D_DATA     	T1DATD


//键盘中断设置
#define	 KBIE_Enable()   KBIE=1// 使能键盘中断
#define	 KBIE_Disable()  KBIE=0//屏蔽键盘中断

#define	 P15KE_Enable()  P15KE=1// 使能端口键盘中断功
#define	 P15KE_Disable() P15KE=0//屏蔽端口键盘中断功能
#define	 P14KE_Enable()  P14KE=1// 使能端口键盘中断功
#define	 P14KE_Disable() P14KE=0//屏蔽端口键盘中断功能
#define	 P13KE_Enable()  P13KE=1// 使能端口键盘中断功
#define	 P13KE_Disable() P13KE=0//屏蔽端口键盘中断功能
#define	 P12KE_Enable()  P12KE=1// 使能端口键盘中断功
#define	 P12KE_Disable() P12KE=0//屏蔽端口键盘中断功能
#define	 P11KE_Enable()  P11KE=1// 使能端口键盘中断功
#define	 P11KE_Disable() P11KE=0//屏蔽端口键盘中断功能
#define	 P10KE_Enable()  P10KE=1// 使能端口键盘中断功
#define	 P10KE_Disable() P10KE=0//屏蔽端口键盘中断功能

#define	 GIE_Enable()  GIE=1// 中断源是否产生由相应的控制位决定
#define	 GIE_Disable() GIE=0//屏蔽所有中断

//CMP比较器
#define	 CMP_Disable() CMPEN=0//比较器CMP使能位 关闭
#define	 CMP_Enable()  CMPEN=1//比较器CMP使能位 开启

#define	 CMPPS_VIR()   CMPPS=0//比较器CMP正端输入Vir
#define	 CMPPS_EVN0()  CMPPS=1//比较器CMP正端输入EVN0
#define	 CMPNS_RES()   CMPNS=0//比较器CMP负端输入电阻分压
#define	 CMPNS_CMPN()  CMPNS=1//比较器CMP负端输入CMPN
#define	 CMPNS_RES_VDD()    CMPCR0=(CMPCR0&0xC7)//电压检测输入VDD
#define	 CMPNS_RES_EVN0()   CMPCR0=(CMPCR0&0xC7)|0x08//电压检测输入EVN0
#define	 CMPNS_RES_EVN1()   CMPCR0=(CMPCR0&0xC7)|0x10//电压检测输入EVN1
#define	 CMPNS_RES_EVN2()   CMPCR0=(CMPCR0&0xC7)|0x18//电压检测输入EVN2
#define	 CMPO_Forward()     CMPNV=0  //端口输出正向电平
#define	 CMPO_Reverse()     CMPNV=1  //端口输出反向电平
#define	 CMPOE_Disable()    CMPOE=0  //禁止端口输出
#define	 CMPOE_Enable()     CMPOE=1  //允许端口输出
#define	 CMPIM_rise()       CMPIM=0  //输出上升沿触发
#define	 CMPIM_fall()       CMPIM=1  //输出下升沿触发
#define	 CMPIE_Disable()    CMPCR2=(CMPCR2&0xFC)       //屏蔽中断,清除中断标志位
#define	 CMPIE_Enable()    	CMPCR2=(CMPCR2&0xFC)|0xFE  //使能中断,清除中断标志位断
#define	 CLR_CMPIF()       	CMPIF=0  //清除中断标志位


#define NOP()  __asm   NOP  __endasm
 
#define Nop()  	   	   	__asm__("nop")
#define ClrWdt()   	   	__asm__("clrwdt")
#define Stop() 	   	   	__asm__("stop")










