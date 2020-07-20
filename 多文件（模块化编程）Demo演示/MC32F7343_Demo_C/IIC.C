#include "IIC.h"

/************************************************
;  *    @Function Name       : Init_I2C
;  *    @Description         : 
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    : 
;  ***********************************************/ 
void Init_I2C(void)
{
   	IICCR=0x01; //1Mbps,开中断    	  
   	IICIE=1;
   	IICEN=1;   	   	   	       	       	    
}
/************************************************
;  *    @Function Name       : I2C_Start
;  *    @Description         : IIC起始信号
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/  
void I2C_Start(uchar R_Slave_addr,uchar CMD)
{
   	IICSTR=1;
   	while(F_I2C_done==0);
   	F_I2C_done=0;
   	if(CMD)
   	{
   	   	IICDR=R_Slave_addr+1;
   	}else
   	{
   	   	IICDR=R_Slave_addr;
   	}      	   	
   	IICWR=1;
   	while(F_I2C_done==0);
   	F_I2C_done=0;      	   	
}
/************************************************
;  *    @Function Name       : I2C_Stop
;  *    @Description         : IIC起始信号
;  *    @IN_Parameter      	 : 
;  *    @Return parameter    :
;  ***********************************************/ 
void I2C_Stop()
{
   	IICSTP=1;
   	while(F_I2C_done==0);
   	F_I2C_done=0;
}
/************************************************
;  *    @Function Name       : Write_Process
;  *    @Description         : 写数据
;  *    @IN_Parameter      	 : 器件地址 数据 长度
;  *    @Return parameter    : 
;  ***********************************************/
void  Write_Process(uchar Buf_addr,uchar *Vlaue,uchar Len)
{
   	I2C_Start(Buf_addr,I2C_Write_CMD);
   	if(RACK==0)
   	{
   	   	while(Len)
   	   	{
   	   	   	IICDR=*Vlaue++;
   	   	   	IICWR=1;
   	   	   	while(F_I2C_done==0);
   	   	   	F_I2C_done=0;
   	   	   	Len--;
   	   	}  	
   	}  	   	
   	I2C_Stop();
}
/************************************************
;  *    @Function Name       : Read_Process
;  *    @Description         : 读数据
;  *    @IN_Parameter      	 : 器件地址 数据 长度
;  *    @Return parameter    : 
;  ***********************************************/
void  Read_Process(uchar Buf_addr,uchar *Vlaue,uchar Len)
{
   	uchar temp=0;
   	I2C_Start(Buf_addr,I2C_Read_CMD);
   	if(RACK==0)
   	{
   	   	while(Len)
   	   	{
   	   	   	IICRD=1;
       	   	while(F_I2C_done==0);
       	   	F_I2C_done=0;
       	   	*Vlaue=IICDR;
       	   	if(Len==1)
       	   	{
       	   	   	SACK=1;
       	   	}
       	   	else
       	   	{
       	   	   	SACK=0;//继续接受数据
       	   	}
       	   	IICACK=1;
       	   	while(F_I2C_done==0);
       	   	F_I2C_done=0;
       	   	Vlaue++;
       	   	Len--;
   	   	}
   	}
   	I2C_Stop();
}
