#include "UART.h"

/************************************************
;  *    @Function Name       : UART_Config
;  *    @Description         : 串口配置  包括IO口
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/  
void UART_Config(void)
{
   	IOP1|=0x02;
   	OEP1|=0x02;    	   	//P11out
   	PUP1|=0x01;    	   	 //P10上拉
   	
   	T2CR=0x80; 	   	//FCPU   不分频
   	T2LOADH=0x00;
   	T2LOADL=51;	   	   	//Baud=FT2/(16*(T2LOAD+1))  4800
   	
   	SCON=0x54; 	   	   	   	//方式1  
   	GIE=1;
   	UARTIE=1;
}
/************************************************
;  *    @Function Name       : SendData
;  *    @Description         : 串口输出
;  *    @IN_Parameter      	 : 输入数据
;  *    @Return parameter    :
;  ***********************************************/  
void SendData(u8 dat)
{
    while (UART_Busy);               //等待前面的数据发送完成
    UART_Busy = 1;
    SBUF = dat;                 //写数据到UART数据寄存器
}
/************************************************
;  *    @Function Name       : Uart_Send_Data
;  *    @Description         : 连续串口输出
;  *    @IN_Parameter      	 : 输入数据
;  *    @Return parameter    :
;  ***********************************************/
void Uart_Send_Data(char *s, uchar len)
{
   	while (len)
   	{
   	   	SendData(*s++);
   	   	len--;
   	}
}
/************************************************
;  *    @Function Name       : SendString
;  *    @Description         : 
;  *    @IN_Parameter      	 : 输入数据
;  *    @Return parameter    :
;  ***********************************************/  
void SendString(char *s)
{
    while (*s)              //Check the end of the string
    {
        SendData(*s++);     //Send current char and increment string ptr
    }
}