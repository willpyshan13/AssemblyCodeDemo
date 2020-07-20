#include "mc30p6250.h"
#include "Data.h"
#include "user.h"
void C_RAM(void);
void T0_ConfigSet(void);
//void T0_Flosc_ConfigSet(void);
void T1_ConfigSet(void);
void PWM_ConfigSet(void);
void CMP_ConfigSet(void);
void IO_initialize(void);
void Delay10us(void);
void Delay_N_5nop(u16 Delay_N);
//void Det_EVN0(void);
//void Det_EVN1(void);
void Det_VDD(void);
void Det_VDD_FAST(void);
void Det_VSolar(void);

//void Power_Changing(void);
void Power_OFF(void);
void Sleep(void);
void PWM_Running(void);
void LED_Running(void);

/*****************************************************************
* 函数名      : void C_RAM(void)
* 函数功能 	  : 初始化RAM
* 输入        : 无
* 输出       	: 无
******************************************************************/
void C_RAM(void)
{
   	__asm 
   	movai 0x40 
   	movra FSR
   	movai 48 
   	movra 0x07 
   	decr FSR
   	clrr INDF
   	djzr 0x07 
   	goto $ -3;
;  	clrr INDF
   	clrr 0x07 
   	__endasm;
}
/*****************************************************************
延时程序 :Delay10us( void)
函数功能   	   
输入
输出
******************************************************************/
void Delay10us(void)
{
   	for(a_u8=1;a_u8>0;a_u8--)
   	{
   	   	NOP();
   	}

}

/*****************************************************************
延时程序 :Delay_N_5nop(viod)
函数功能   	   
输入
输出
******************************************************************/
void Delay_N_5nop(u16 Delay_N)
{
   	for(b_u16=Delay_N;b_u16>0;b_u16--)
   	{  
   	   	NOP();
   	   	NOP();
   	   	NOP();
   	   	NOP();
   	   	NOP();
   	}
}
/*****************************************************************
* 函数名      : void T0_ConfigSet(void)
* 函数功能 	  : T0设置
* 输入        : 无
* 输出       	: 无
******************************************************************/
void T0_ConfigSet(void)
{          	
   	T0CLK_IN_Fcpu();
   	T0CLK_DIV256();
   	T0CNT=T0_DAT_5mS;          	//5mS中断一次 
   	T0IE=1;    	
}


/*****************************************************************
* 函数名      : void T0_Flosc_ConfigSet(void)
* 函数功能 	  : T0设置
* 输入        : 无
* 输出       	: 无
******************************************************************/
/*void T0_Flosc_ConfigSet(void)
{          	
   	T0CLK_Select_Flosc();
   	T0CLK_DIV256();
   	T0CNT=0;         //2秒定时  
   	T0IE=1;    	
}*/




/*****************************************************************
* 函数名      : void T1_ConfigSet(void)
* 函数功能 	  : T0设置
* 输入        : 无
* 输出       	: 无
******************************************************************/
void T1_ConfigSet(void)
{      	
   	T1CLK_IN_Fcpu();
   	T1CLK_DIV2();
   	T1LOAD=PWM_DAT;
   	T1CNT=PWM_DAT;
   	T1_Star();         	           	 
   	T1IE=1;    	
}

/*****************************************************************
* 函数名      : void PWM_ConfigSet(void)
* 函数功能 	  : T0设置
* 输入        : 无
* 输出       	: 无
******************************************************************/
void PWM_ConfigSet(void)
{      	
   	PWM1A_Enable();    	       	
   	PWM1B_Disable();
   	PWM1C_Disable();   	
   	PWM1D_Disable();
   	PWM1A_Stop();
   	PWM1B_Stop();
   	PWM1C_Stop();
   	PWM1D_Stop();          	
}


/*****************************************************************
* 函数名      : void CMP_ConfigSet(void)
* 函数功能 	  : CMP设置
* 输入        : 无
* 输出       	: 无
******************************************************************/
void CMP_ConfigSet(void)
{ 
   	CMP_Enable();
   	CMPPS_VIR();
//     	CMPNS_RES_EVN1();//        	
//     	CMPO_Forward();//正向输出
   	CMPOE_Disable();//禁止端口输出
   	CMPIE_Disable();//     	   	
}
/*****************************************************************
* 函数名      : void Det_VDD_FAST(void)
* 函数功能 	  : VDD输入信号检测
* 输入        : 无
* 输出       	: 无
******************************************************************/
void Det_VDD_FAST(void)
{
   	CMPNS_RES_VDD(); 
   	CMPCR1=Det_VDD_Value;
   	Delay_N_5nop(100); 
   	while(!CMPOF)
   	{
   	   	Det_VDD_Value++;
   	   	if(Det_VDD_Value>EVD_VDD_MAX)
   	   	{
   	   	   	Det_VDD_Value=EVD_VDD_MAX;
   	   	   	break;
   	   	} 
   	   	CMPCR1=Det_VDD_Value;
   	   	Delay_N_5nop(100);     	   	   	   	
   	}
   	Det_VDD_Value_Buf0=Det_VDD_Value;
   	Det_VDD_Value_Buf1=Det_VDD_Value;      	
}

/*****************************************************************
* 函数名      : void Det_VDD(void)
* 函数功能 	  : VDD输入信号检测
* 输入        : 无
* 输出       	: 无
******************************************************************/
void Det_VDD(void)
{
   	if(Det_VDD_EN)
   	{
   	   	CMPNS_RES_VDD(); 
   	   	CMPCR1=Det_VDD_Value;
   	   	Delay_N_5nop(100);     	   	
   	   	CMPOF_Buf=CMPOF;
   	   	Delay_N_5nop(20);
   	   	if(CMPOF&&CMPOF_Buf)
   	   	{
   	   	   	Det_VDD_NUM++;
   	   	   	if(Det_VDD_NUM>EVD_VDD_H_CONST)
   	   	   	{
   	   	   	   	Det_VDD_NUM=EVD_VDD_H_CONST;
   	   	   	}
   	   	}

   	   	if((CMPOF||CMPOF_Buf)==0)
   	   	{
   	   	   	Det_VDD_NUM--;
   	   	   	if(Det_VDD_NUM<EVD_VDD_L_CONST)
   	   	   	{
   	   	   	   	Det_VDD_NUM=EVD_VDD_L_CONST;
   	   	   	}
   	   	}
   	   	
   	   	if(Det_VDD_NUM==EVD_VDD_H_CONST)//
   	   	{  	   	   	
   	   	   	Det_VDD_Value--;
   	   	   	if(Det_VDD_Value<EVD_VDD_MIN)
   	   	   	{
   	   	   	   	Det_VDD_Value=EVD_VDD_MIN;
   	   	   	}
   	   	   	Det_VDD_Value_Buf1=Det_VDD_Value_Buf0;
   	   	   	Det_VDD_Value_Buf0=Det_VDD_Value;
   	   	   	Det_VDD_NUM=0;     	   	   	
   	   	}

   	   	if(Det_VDD_NUM==EVD_VDD_L_CONST)
   	   	{
   	   	   	Det_VDD_Value++;
   	   	   	if(Det_VDD_Value>EVD_VDD_MAX)
   	   	   	{
   	   	   	   	Det_VDD_Value=EVD_VDD_MAX;
   	   	   	}
   	   	   	Det_VDD_Value_Buf1=Det_VDD_Value_Buf0;
   	   	   	Det_VDD_Value_Buf0=Det_VDD_Value;
   	   	   	Det_VDD_NUM=0;     	   	   	   	   	   	
   	   	}
   	   	
   	   	if(Det_VDD_Value_Buf1>=Det_VDD_Value_Buf0)
   	   	{
   	   	   	VDD_Value=Det_VDD_Value_Buf0;
   	   	}
   	   	else
   	   	{
   	   	   	VDD_Value=Det_VDD_Value_Buf1;      	   	
   	   	}
   	   	Det_VDD_EN=0;  	   	
   	}
   	       	   	   
       	       	   	 
}


/*****************************************************************
* 函数名      : void Det_VSolar(void)
* 函数功能 	  : VDD输入信号检测
* 输入        : 无
* 输出       	: 无
******************************************************************/
void Det_VSolar(void)
{
   	if(Det_VSolar_EN)
   	{
   	   	CMPNS_RES_EVN1(); 
   	   	CMPCR1=Det_VSolar_Value;
   	   	Delay_N_5nop(100);     	   	
   	   	CMPOF_Buf=CMPOF;
   	   	Delay_N_5nop(20);
   	   	if(CMPOF&&CMPOF_Buf)
   	   	{
   	   	   	Det_VSolar_NUM++;
   	   	   	if(Det_VSolar_NUM>EVD_VSolar_H_CONST)
   	   	   	{
   	   	   	   	Det_VSolar_NUM=EVD_VSolar_H_CONST;
   	   	   	}
   	   	}

   	   	if((CMPOF||CMPOF_Buf)==0)
   	   	{
   	   	   	Det_VSolar_NUM--;
   	   	   	if(Det_VSolar_NUM<EVD_VSolar_L_CONST)
   	   	   	{
   	   	   	   	Det_VSolar_NUM=EVD_VSolar_L_CONST;
   	   	   	}
   	   	}
   	   	
   	   	if(Det_VSolar_NUM==EVD_VSolar_H_CONST)//
   	   	{  	   	   	
   	   	   	Det_VSolar_Value--;
   	   	   	if(Det_VSolar_Value<EVD_VSolar_MIN)
   	   	   	{
   	   	   	   	Det_VSolar_Value=EVD_VSolar_MIN;
   	   	   	}
   	   	   	Det_VSolar_Value_Buf1=Det_VSolar_Value_Buf0;
   	   	   	Det_VSolar_Value_Buf0=Det_VSolar_Value;
   	   	   	Det_VSolar_NUM=0;      	   	   	
   	   	}

   	   	if(Det_VSolar_NUM==EVD_VSolar_L_CONST)
   	   	{
   	   	   	Det_VSolar_Value++;
   	   	   	if(Det_VSolar_Value>EVD_VSolar_MAX)
   	   	   	{
   	   	   	   	Det_VSolar_Value=EVD_VSolar_MAX;
   	   	   	}
   	   	   	Det_VSolar_Value_Buf1=Det_VSolar_Value_Buf0;
   	   	   	Det_VSolar_Value_Buf0=Det_VSolar_Value;
   	   	   	Det_VSolar_NUM=0;      	   	   	   	   	   	
   	   	}
   	   	Det_VSolar_EN=0;   	   	
   	}          	       	   	 
}



/*****************************************************************
* 函数名      : void LED_Running(void)
* 函数功能 	  : 
* 输入        : 无
* 输出       	: 无
******************************************************************/
void LED_Running(void)
{
   	if(VDD_Value>=0x32)
   	{
   	   	PWM_Value=PWM_PERCENT(80);
   	   	return;    	   	
   	}
   	if(VDD_Value>=EVD_392)
   	{
   	   	PWM_Value=PWM_PERCENT(90);
   	   	return;        	   	
   	}
   	if(VDD_Value>=EVD_364)
   	{
   	   	PWM_Value=PWM_PERCENT(100);
   	   	return;        	   	
   	}
   	if(VDD_Value>=EVD_343)
   	{
   	   	PWM_Value=PWM_PERCENT(80);
   	   	return;        	   	
   	}
   	if(VDD_Value>=EVD_329)
   	{
   	   	PWM_Value=PWM_PERCENT(50);
   	   	return;        	   	
   	}
   	if(VDD_Value>=EVD_301)
   	{
   	   	PWM_Value=PWM_PERCENT(20);
   	   	return;        	   	
   	}

}      	




/*****************************************************************
延时程序       void IO_initialize()
函数功能      IO初始化    	   
输入
输出
******************************************************************/
void IO_initialize(void)
{

   	Set_P10_IN();
   	Enable_P10_IPU();// 设置上拉电阻

       	Set_P11_Push_Pull();
       	Set_P11_OUT();

   	Set_P12_Push_Pull();
   	Set_P12_OUT();
//     	Set_P13_IN();
//     	Enable_P13_IPU();
//     	Set_P14_IN();
//     	Disable_P14_IPU();
   	
   	Set_P15_IN();
   	Disable_P15_IPU();
   	LED1_OFF();
   	Open_WDT();

   	Det_VDD_Value=EVD_VDD_MIN;
   	Det_VDD_Value_Buf0=EVD_VDD_MIN;
   	Det_VDD_Value_Buf1=EVD_VDD_MIN;
   	Det_VDD_Time=0;
//     	PWM_Value=PWM_PERCENT(80);
   	PWM_Value_Buf=PWM_PERCENT(80);             	
}

/*****************************************************************
显示程序      void Sleep(void)
函数功能        
输入
输出
******************************************************************/
void Sleep(void)
{
/*     	if(PIR_IN==1) 
   	{
   	   	Sleep_Time=0;      	   	
   	}
   	else 
   	{      	
   	   	if(Sleep_Time>100)//500ms
   	   	{      	   	
   	   	   	GIE_Disable();     	   	   	
   	   	   	T1IE_Disable();
   	   	   	CLR_T1IF();
   	   	   	Close_WDT();
   	   	   	KBIF=0;
   	   	   	KBIE_Enable();
   	   	   	P13KE_Enable();
   	   	   	Nop();
   	   `   	Nop();
   	   	   	Stop();
   	   	   	Nop();
   	   	   	Nop();
   	   	   	P13KE_Enable();
   	   	   	KBIE_Disable();
   	   	   	KBIF = 0;
   	   	   	GIE_Enable();
   	   	   	T0_ConfigSet();
   	   	   	T1IE_Enable();
       	   	  Open_WDT();
   	   	}
   	}*/        	           	   	   	
}


/*****************************************************************
* 函数名      : void PWM_Running(void)
* 函数功能 	  : PWM运行
* 输入        : PWM_Value
* 输出       	: LED1
******************************************************************/
void PWM_Running(void)
{
   	if(PWM_EN)
   	{
   	   	PWM_EN=0;
   	   	if((PWM_Value_Buf==PWM_PERCENT(100))&&(PWM_Value>=PWM_PERCENT(100)))
   	   	{
   	   	   	PWM1A_Stop();
   	   	   	LED1_ON();
   	   	   	return;        	
   	   	}

   	   	if((PWM_Value_Buf==PWM_PERCENT(0))&&(PWM_Value==PWM_PERCENT(0)))
   	   	{
   	   	   	PWM1A_Stop();
   	   	   	LED1_OFF();
   	   	   	return;        	
   	   	}

   	   	if(PWM_Value>PWM_Value_Buf)
   	   	{
   	   	   	PWM1A_Star();
   	   	   	PWM_Value_Buf++;
   	   	   	PMW1A_DATA=PWM_Value_Buf; 
   	   	}
   	   	if(PWM_Value==PWM_Value_Buf)
   	   	{
   	   	   	PWM1A_Star();
   	   	   	PMW1A_DATA=PWM_Value_Buf; 
   	   	}      	   	
   	   	if(PWM_Value<PWM_Value_Buf)
   	   	{
   	   	   	 PWM1A_Star();
   	   	   	 PWM_Value_Buf--;
   	   	   	 PMW1A_DATA=PWM_Value_Buf;     	   	   	
   	   	}
   	}

}










/*****************************************************************
* 函数名      : void int_isr(void)__interrupt
* 函数功能 	  : 中断程序
* 输入        : 无
* 输出       	: 无
******************************************************************/

void int_isr(void)__interrupt
{
__asm
   	movra   _ABuf
    swapar  _STATUS
    movra   _StatusBuf
__endasm;


    if((T0IF)&&(T0IE))
    {
   	   	CLR_T0IF();
   	   	T0CNT=T0_DAT_5mS;  //5mS定时器 
   	   	Det_VDD_Time++;
   	   	if(Det_VDD_Time>=Det_VDD_Time_10ms)
   	   	{
   	   	   	Det_VDD_Time=0;
   	   	   	Det_VDD_EN=1;
   	   	   	Det_VSolar_EN=1;   	
   	   	}

   	   	Timing_Value1++;
   	   	if(Timing_Value1>=Time_100ms)
   	   	{
   	   	   	Timing_Value1=0;
   	   	   	PWM_EN=1;      	
   	   	}
   	   	
       	   	
    }

   	if ((T1IF) && (T1IE))
   	{
   	   	CLR_T1IF();
//     	   	P11D=!P11D; 
   	}
   	if ((CMPIE) && (CMPIF))
   	{
   	   	
   	   	CLR_CMPIF();
   	}

__asm
    swapar  _StatusBuf
    movra   _STATUS
    swapr   _ABuf
    swapar  _ABuf
__endasm;

}


void main(void)
{
   	C_RAM();
   	GIE_Disable();
   	IO_initialize();
   	CMP_ConfigSet();
   	T0_ConfigSet();
   	T1_ConfigSet();
   	PWM_ConfigSet();
   	GIE_Enable();
   	Det_VDD_FAST();
   	while(1)
   	{

   	VDD_Value=0x55;
   	VDD_Value=0x58;
   	if(VDD_Value>=0x32)
   	{
   	   	PWM_Value=PWM_PERCENT(80);   	   	
   	}



   	   	ClrWdt();
//     	   	Det_VDD();
   	   	Det_VSolar();
   	   	PWM_Running();
   	   	LED_Running();
//     	   	PWM_Value=PWM_PERCENT(100);
//         	Power_OFF();
//         	Sleep();
   	}
}

