#ifndef _HEADER_H
#define _HEADER_H

#define bit0 0x01
#define bit1 0x02
#define bit2 0x04
#define bit3 0x08
#define bit4 0x10
#define bit5 0x20
#define bit6 0x40
#define bit7 0x80

//---------------------------- I/O define -----------------------------
//IO-pin define
#define SDA_read       P15D     //sda和scl  sensor i2c interface
#define SCL_read        P16D

#define SCL_H         P16OE=0       //设置为输入，上拉电阻将IO口置1
#define SCL_L          P16OE=1;P16D=0 //输出低电平 
    
#define SDA_H         P15OE=0
#define SDA_L         P15OE=1;P15D=0
//-------------------------constant define -------------------------
//Constant

//--------------------------variable define -------------------------
//Definition of variable
uchar pflagtemp;
uchar acctemp;
uchar read_temp;
uchar time_1ms;
uchar m;

uchar Array[124];

typedef union{
unsigned char byte;
struct{
	unsigned char flg0:1;
	unsigned char flg1:1;
	unsigned char flg2:1;
	unsigned char flg3:1;
	unsigned char flg4:1;
	unsigned char flg5:1;
	unsigned char flg6:1;
	unsigned char flg7:1;
}bits;
}flag;

//-------------------------KeyFlag  define -------------------------
//Flag bit
flag flg,flg1,flg2,flg3;
#define F_time20ms                 flg.bits.flg0
#define sys_50ms_flag                flg.bits.flg1
#define sys_100ms_flag               flg.bits.flg2
#define sys_500ms_flag               flg.bits.flg3


void RamInit(void);
void InitSub(void);
void IOPortInit(void);
void IRQInit(void);

void I2C_Delay10us();
void delay(uchar x);
/*******************************************/  
void I2C_delay(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Ack(void);
void I2C_NoAck(void); 
void I2C_SendByte(uchar SendByte);
uchar I2C_ReceiveByte();   
 
void IIC_write_onebyte(uchar write_add,uchar write_data);

void IIC_read_onebyte(uchar read_add);
void Delay10ms(unsigned int c);   //误差 0us

#endif


