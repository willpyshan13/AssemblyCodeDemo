
#include "iic.h"



#define SCL_H  	   	P14D=1 
#define SCL_L  	   	P14D=0
#define SDA_H  	   	P15D=1  
#define SDA_L  	   	P15D=0 
#define SDA_IN 	   	{DDR15 = 1; P15PU=0;}   
#define SDA_OUT    	DDR15 = 0





void Delay_5us(void)
{
 u8 i; //fcpu 8MHz ʱ
for (i=60; i>0; i--);
}


void iic_init(void)
{
   	DDR15 = 0;
   	P15OD=1; 
   	DDR14 =0;
   	P14OD=1;
   	 
}



//��ʼ�ź�
void iic_start(void)
{
   	//����������Ϊ���
   	//iic_sda_mode(GPIO_MODE_OUT_OD_HIZ_FAST);
   	SDA_OUT;
   	//���߿���
   	SCL_H;
   	SDA_H;
   	Delay_5us();
   	
   	//����������
   	SDA_L;
   	Delay_5us();
   	
   	//SCL����ǯס����
   	SCL_L;
}

//ֹͣ�ź�
void iic_stop(void)
{
   	//����������Ϊ���
   	//iic_sda_mode(GPIO_MODE_OUT_OD_HIZ_FAST);
   	SDA_OUT;
   	//SCL����ǯס����
   	SCL_L;
   	SDA_L;
   	Delay_5us();
   	
   	//����ʱ����
   	SCL_H;
   	Delay_5us();
   	
   	//�������ɵ��������
   	SDA_H;
}

//�ȴ�ACK 1-��Ч 0-��Ч
u8 iic_wait_ack(void)
{
   	u8 ack = 0;
   	
   	//����������Ϊ����
   	//iic_sda_mode(GPIO_MODE_IN_PU_NO_IT);
   	SDA_IN;
   	//����ʱ����,�ô��豸���Կ���������
   	SCL_H;
   	Delay_5us();
   	
   	//��ȡ�����ߵĵ�ƽ
   	if(P15D){//��ЧӦ��
   	   	ack = 1;
   	   	iic_stop();
   	}
   	else{
   	   	ack = 0;
   	}
   	
   	//SCL����ǯס����
   	SCL_L;
   	Delay_5us();
   	
   	return ack;
}

//������Ч/��ЧӦ�� 1-��Ч 0-��Ч
void iic_ack(u8 ack)
{
   	//����������Ϊ���
   	//iic_sda_mode(GPIO_MODE_OUT_OD_HIZ_FAST);
   	SDA_OUT;
   	SCL_L;
   	Delay_5us();
   	
   	//����ACK/NACK
   	if(ack)
   	   	SDA_H;//��ЧӦ��
   	else
   	   	SDA_L;//��ЧӦ��
   	
   	Delay_5us();
   	SCL_H;
   	//���������ȶ�
   	Delay_5us();
   	//SCL����ǯס����
   	SCL_L;
}

//����һ���ֽ�
void iic_send_byte(u8 txd)
{
   	u8 i;
   	//����������Ϊ���
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
   	   	//����ʱ����
   	   	SCL_H;
   	   	Delay_5us();
   	   	
   	   	SCL_L;
   	   	Delay_5us();
   	}
}

//����һ���ֽ�
u8 iic_read_byte(void)
{
   	u8 i,rxd = 0;
   	//����������Ϊ����
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




//дһҳ
void write_page(u8 addr,u8 *pdata,u8 len)
{
   	//��ʼ�ź�
   	iic_start();
   	
   	//���ʹ��豸��ַ��д�ź� 0x50<<1 | 0 = 0xa0
   	iic_send_byte(0x24);
   	//�ȴ�ACK
   	if(iic_wait_ack()){
   	   	//usart1_puts("no ack write_page 0x24");
   	   	return;
   	}
   	
   	//����д����ֽڵ�ַ
   	iic_send_byte(addr);
   	//�ȴ�ACK
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
   	
   	//ֹͣ�ź�
   	iic_stop();
}

//��һҳ
void read_page(u8 addr,u8 *pdata,u8 len)
{
   	//��ʼ�ź�
   	iic_start();
   	
   	//���ʹ��豸��ַ��д�ź� 0x50<<1 | 0 = 0xa0
   	iic_send_byte(0x24);
   	//�ȴ�ACK
   	if(iic_wait_ack()){
   	   	//usart1_puts("no ack read_page 0x24");
   	   	return;
   	}
   	
   	//���Ͷ����ֽڵ�ַ
   	iic_send_byte(addr);
   	//�ȴ�ACK
   	if(iic_wait_ack()){
   	   	//usart1_puts("no ack read_page addr");
   	   	return;
   	}
   	
   	//��ʼ�ź�
   	iic_start();
   	
   	//���ʹ��豸��ַ�Ͷ��ź� 0x50<<1 | 1 = 0xa1
   	iic_send_byte(0x25);
   	//�ȴ�ACK
   	if(iic_wait_ack()){
   	   	//usart1_puts("no ack read_page 0x25");
   	   	return;
   	}
   	
   	while(len--){
   	   	*pdata++ = iic_read_byte();
   	   	
   	   	if(len>0){//��ЧӦ��
   	   	   	iic_ack(0);
   	   	   	//printf("11111\n");
   	   	}
   	   	else{
   	   	   	iic_ack(1);
   	   	   	//printf("222222\n");
   	   	}
   	}
   	
   	//ֹͣ�ź�
   	iic_stop();
}


u8 qmaX981_chip_id(void)
{
   	u8 chip_id = 0x00;
   	write_page(0x11, 0x80,1);

   	read_page(0x00, &chip_id, 1);

   	return chip_id;
}


