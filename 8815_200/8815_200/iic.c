
#include "iic.h"



#define SCL_H  	   	P14D=1 
#define SCL_L  	   	P14D=0
#define SDA_H  	   	P15D=1  
#define SDA_L  	   	P15D=0 
#define SDA_IN 	   	{DDR15 = 1; P15PU=0;}   
#define SDA_OUT    	DDR15 = 0





void Delay_5us(void)
{
 u8 i; //fcpu 8MHz 时
for (i=60; i>0; i--);
}


void iic_init(void)
{
   	DDR15 = 0;
   	P15OD=1; 
   	DDR14 =0;
   	P14OD=1;
   	 
}



//起始信号
void iic_start(void)
{
   	//数据线设置为输出
   	//iic_sda_mode(GPIO_MODE_OUT_OD_HIZ_FAST);
   	SDA_OUT;
   	//总线空闲
   	SCL_H;
   	SDA_H;
   	Delay_5us();
   	
   	//拉低数据线
   	SDA_L;
   	Delay_5us();
   	
   	//SCL拉低钳住总线
   	SCL_L;
}

//停止信号
void iic_stop(void)
{
   	//数据线设置为输出
   	//iic_sda_mode(GPIO_MODE_OUT_OD_HIZ_FAST);
   	SDA_OUT;
   	//SCL拉低钳住总线
   	SCL_L;
   	SDA_L;
   	Delay_5us();
   	
   	//拉高时钟线
   	SCL_H;
   	Delay_5us();
   	
   	//数据线由低向高跳变
   	SDA_H;
}

//等待ACK 1-无效 0-有效
u8 iic_wait_ack(void)
{
   	u8 ack = 0;
   	
   	//数据线设置为输入
   	//iic_sda_mode(GPIO_MODE_IN_PU_NO_IT);
   	SDA_IN;
   	//拉高时钟线,让从设备可以控制数据线
   	SCL_H;
   	Delay_5us();
   	
   	//获取数据线的电平
   	if(P15D){//无效应答
   	   	ack = 1;
   	   	iic_stop();
   	}
   	else{
   	   	ack = 0;
   	}
   	
   	//SCL拉低钳住总线
   	SCL_L;
   	Delay_5us();
   	
   	return ack;
}

//产生有效/无效应答 1-无效 0-有效
void iic_ack(u8 ack)
{
   	//数据线设置为输出
   	//iic_sda_mode(GPIO_MODE_OUT_OD_HIZ_FAST);
   	SDA_OUT;
   	SCL_L;
   	Delay_5us();
   	
   	//发送ACK/NACK
   	if(ack)
   	   	SDA_H;//无效应答
   	else
   	   	SDA_L;//有效应答
   	
   	Delay_5us();
   	SCL_H;
   	//保持数据稳定
   	Delay_5us();
   	//SCL拉低钳住总线
   	SCL_L;
}

//发送一个字节
void iic_send_byte(u8 txd)
{
   	u8 i;
   	//数据线设置为输出
   	//iic_sda_mode(GPIO_MODE_OUT_OD_HIZ_FAST);
   	SDA_OUT;
   	SCL_L;
   	Delay_5us();
   	
   	for(i=0;i<8;i++){
   	   	if(txd&1<<(7-i))
   	   	   	SDA_H;
   	   	else
   	   	   	SDA_L;
   	   	
   	   	Delay_5us();
   	   	//拉高时钟线
   	   	SCL_H;
   	   	Delay_5us();
   	   	
   	   	SCL_L;
   	   	Delay_5us();
   	}
}

//接收一个字节
u8 iic_read_byte(void)
{
   	u8 i,rxd = 0;
   	//数据线设置为输入
   	//iic_sda_mode(GPIO_MODE_IN_PU_NO_IT);
   	SDA_IN;
   	SCL_L;
   	Delay_5us();
   	
   	for(i=0;i<8;i++){
   	   	SCL_H;
   	   	Delay_5us();
   	   	
   	   	if(P15D)
   	   	   	rxd |= 1<<(7-i);

   	   	Delay_5us();
   	   	SCL_L;
   	   	Delay_5us();
   	}
   	
   	return rxd;
}




//写一页
void write_page(u8 addr,u8 *pdata,u8 len)
{
   	//起始信号
   	iic_start();
   	
   	//发送从设备地址和写信号 0x50<<1 | 0 = 0xa0
   	iic_send_byte(0x24);
   	//等待ACK
   	if(iic_wait_ack()){
   	   	//usart1_puts("no ack write_page 0x24");
   	   	return;
   	}
   	
   	//发送写入的字节地址
   	iic_send_byte(addr);
   	//等待ACK
   	if(iic_wait_ack()){
   	   	//usart1_puts("no ack write_page addr");
   	   	return;
   	}
   	
   	while(len--){
   	   	iic_send_byte(*pdata++);
   	   	
   	   	if(iic_wait_ack()){
   	   	   	//usart1_puts("no ack write_page pdata");
   	   	   	return;
   	   	}  	
   	}
   	
   	//停止信号
   	iic_stop();
}

//读一页
void read_page(u8 addr,u8 *pdata,u8 len)
{
   	//起始信号
   	iic_start();
   	
   	//发送从设备地址和写信号 0x50<<1 | 0 = 0xa0
   	iic_send_byte(0x24);
   	//等待ACK
   	if(iic_wait_ack()){
   	   	//usart1_puts("no ack read_page 0x24");
   	   	return;
   	}
   	
   	//发送读的字节地址
   	iic_send_byte(addr);
   	//等待ACK
   	if(iic_wait_ack()){
   	   	//usart1_puts("no ack read_page addr");
   	   	return;
   	}
   	
   	//起始信号
   	iic_start();
   	
   	//发送从设备地址和读信号 0x50<<1 | 1 = 0xa1
   	iic_send_byte(0x25);
   	//等待ACK
   	if(iic_wait_ack()){
   	   	//usart1_puts("no ack read_page 0x25");
   	   	return;
   	}
   	
   	while(len--){
   	   	*pdata++ = iic_read_byte();
   	   	
   	   	if(len>0){//有效应答
   	   	   	iic_ack(0);
   	   	   	//printf("11111\n");
   	   	}
   	   	else{
   	   	   	iic_ack(1);
   	   	   	//printf("222222\n");
   	   	}
   	}
   	
   	//停止信号
   	iic_stop();
}


u8 qmaX981_chip_id(void)
{
   	u8 chip_id = 0x00;
   	write_page(0x11, 0x80,1);

   	read_page(0x00, &chip_id, 1);

   	return chip_id;
}


