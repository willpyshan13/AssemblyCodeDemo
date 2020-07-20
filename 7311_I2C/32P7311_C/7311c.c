/******************************************************************************
  * @file    I2C communication
  * @author  YB
  * @version V1.0
  * @date    2016-12-7
  * @brief   
  ******************************************************************************
  * @attention 
  *    	 
  *  platform:sinomcu MC32P7311  SOP8
  *  web: www.sinimcu.com
  *
 ******************************************************************************/

#include "mc32p7311.h"
#include "header.h"

uchar n = 0;
void IOPortInit(void)
{
   	OEP0 = 0;      
    OEP1 = 0xf7;      //P1,3����Ϊ���룬����P1��ȫΪ���
    PUP1 = 0;         
    ANSEL0 = 0;
   	ANSEL1 = 0;            	
}
void IRQInit(void)
{
   	T0CR = 0xe0;
   	T0CNT = 6;
   	T0IE = 1;      	       	
}

void RamInit(void)
{
   	RamInit:
    INDF0=0;
    ++FSR0;
    if (FSR0)
    {
        goto RamInit;
    }
}
void InitSub(void)
{
    RamInit();
    IOPortInit();
    IRQInit();     	  
}


void delay(uchar x)
{
   	uchar a,b;
   	for(a=x;a>0;a--)
    for(b=110;b>0;b--);
}

/***************************************************
IIC
****************************************************/
void I2C_delay(void) 
{      	
   uchar i=150; //��������Ż��ٶ�     	����������͵�5����д�� 
   while(i)  
   {  
     i--;  
   }  
} 
/***************************************************
       	       	SCL=1  SDA�½���
****************************************************/
void I2C_Start(void) 
{ 
   	SDA_H; 
    I2C_delay();
   	SCL_H; 
   	I2C_delay();   	  
   	SDA_L; 
   	I2C_delay();   	       	       	       	       	               	
   	SCL_L; 
    I2C_delay();
} 
/***************************************************
   	       	SCL=1  SDA������
****************************************************/
void I2C_Stop(void) 
{ 
    SDA_L;
    I2C_delay(); 
    SCL_H; 
   	I2C_delay(); 
   	SDA_H; 
   	I2C_delay(); 
   	SCL_L; 
    I2C_delay();
} 
/***************************************************
ACK��   	       	SDA=0  SCL������
****************************************************/
void I2C_Ack(void) 
{      	
   	SCL_L; 
   	I2C_delay(); 
   	SDA_L; 
   	I2C_delay(); 
   	SCL_H; 
   	I2C_delay(); 
   	SCL_L; 
   	I2C_delay(); 
} 
/***************************************************
NOACK�� 	       	SDA=1  SCL������
****************************************************/
void I2C_NoAck(void) 
{      	
   	SCL_L; 
   	I2C_delay(); 
   	SDA_H; 
   	I2C_delay(); 
   	SCL_H; 
   	I2C_delay(); 
   	SCL_L; 
   	I2C_delay(); 
} 

/********************************************
       ����һ�ֽ�����     	  
*********************************************/
void I2C_SendByte(uchar SendByte) //���ݴӸ�λ����λ// 
{ 
uchar i; 
for(i=0;i<8;i++)
{ 
    SCL_L; 	       	       	  //SCL�͵�ƽ�ڼ䣬���ݿɸı�
    I2C_delay(); 
   	if((SendByte)&0x80) 
           	SDA_H;  
   	else  
           	SDA_L;    
    SendByte<<=1; 
    I2C_delay(); 
   	SCL_H; 	       	        //�������͵�SDA�Ϻ�����
    I2C_delay(); 
} 
SCL_L;     	       	       	//�����ͳ���SCL����
} 

/********************************************
       ����һ�ֽ�����     	  
*********************************************/
uchar I2C_ReceiveByte()  //���ݴӸ�λ����λ// 
{  
uchar i; 
uchar ReceiveByte=0; 
SDA_H;     	       	           	       	       	  
for(i=0;i<8;i++)
{ 
   	ReceiveByte<<=1;       
   	SCL_L; 
   	I2C_delay(); 
   	SCL_H; 	       	       	       	    //��SCL�ߵ�ƽ�ڼ��ȡ����
   	I2C_delay();   	       	       	
   	if(SDA_read) 
       ReceiveByte|=0x01; 
  
} 
SCL_L;     	       	       	       	   //���ݶ���󣬽�SCL���ͣ��ȴ���һλ����
return ReceiveByte; 
}      	   

void IIC_write_onebyte(uchar write_add,uchar write_data)
{
   	I2C_Start();
    I2C_SendByte(0x2a);       //������ַ
    I2C_Ack();
    
    I2C_SendByte(write_add);  //���ö��ڵ�ַ 
    I2C_Ack();
    
    I2C_SendByte(write_data);  //д������
    I2C_Ack();
    I2C_Stop();      
}

void IIC_read_onebyte(uchar read_add)
{
    //uchar read_temp=0;
   	uchar i = 0;

   	I2C_Start();
    I2C_SendByte(0x2a);       //������ַ
    I2C_Ack();
    
    I2C_SendByte(read_add);   //���ö��ڵ�ַ 
    I2C_Ack();
    
    I2C_Start();
    I2C_SendByte(0x2b); //������
    I2C_Ack();
//
   	for(i=0;i<5;i++)
   	{

       	Array[i+n] = I2C_ReceiveByte();
   	   	if(i == 4)
   	   	{
   	   	   	I2C_NoAck();
   	   	}
   	   	else
   	   	{
   	   	   	I2C_Ack();
   	   	}
   	}
   	n = n+5;
    //I2C_ReceiveByte();
   //	I2C_Ack();
    //read_temp=I2C_ReceiveByte();

    I2C_NoAck();
    I2C_Stop();   
    //return   read_temp;     
}


void URAT_SendData(void)
{



}

/************************************************
  * @brief   main
  * @param      
  * @retval
  ***********************************************/

void main(void)
{   
   	SCL28 = 0; 
   	GIE = 0;   
   	InitSub();
   	GIE = 1;
   	SCL28 = 1;
    //IIC_write_onebyte(0x04,0x04);
    delay(200);
   	
   	while(1)   	
   	{
   	   	if(F_time20ms)
   	   	{
   	   	   	F_time20ms = 0;
   	   	   	for(m=0;m<25;m++)
   	   	   	{   	   	   	
   	   	   	   	IIC_read_onebyte(0x00);
   	   	   	   	
   	   	   	}
   	   	}   	   	
   	   	if(!GPIO12_MCU_EN)
   	   	{
   	   	   	URAT_SendData();


   	   	}






   	}   	

    

}

/************************************************
  * @brief   IRQ
  * @param      
  * @retval
  ***********************************************/
void int_isr(void)__interrupt
{
    __asm
    movra _acctemp
    swapar _PFLAG
    movra _pflagtemp
    __endasm;

   	if(T0IF)
   	{
       	T0IF=0;
   	   	if(++time_1ms >= 40)
   	    {
   	       time_1ms = 0;
   	   	   F_time20ms = 1;
   // __asm
   //	movai  	0x02
   //	xorra   IOP1	
   // __endasm;
   	   	}
   	}
    __asm
    swapar _pflagtemp
    movra _PFLAG
    movar _acctemp
    __endasm;
}
