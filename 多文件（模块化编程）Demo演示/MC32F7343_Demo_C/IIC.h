#ifndef IIC_H
#define IIC_H
#include "User_Def.h"

#define IIC_Addr_Define 0x50
#define I2C_Write_CMD  	0
#define I2C_Read_CMD   	1


void InitSys(void);
void Init_I2C(void);
void I2C_Start(uchar R_Slave_addr,uchar CMD);
void I2C_Stop();
void I2C_Byte_Write(uchar Vlaue);
uchar I2C_Byte_Read(void);
void  Write_Process(uchar Buf_addr,uchar *Vlaue,uchar Len);
void  Read_Process(uchar Buf_addr,uchar *Vlaue,uchar Len);





#endif