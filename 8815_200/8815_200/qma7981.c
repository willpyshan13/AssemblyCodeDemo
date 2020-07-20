
#include "iic.h"
#include "qma7981.h"

void TIM1_DelayMs(void)
{
 u8 i,a; //fcpu 8MHz 时
for (i=60; i>0; i--){
   	for (a=120; a>0; a--);

};
}


void qma7981_init()
{
   	write_page(0x11,0x80,1);
   	write_page(0x36,0xb6,1);
   	TIM1_DelayMs();
   	write_page(0x36,0x00,1);  	
   	write_page(0x11,0x80,1);
   	write_page(0x0f,0x02,1);
   	write_page(0x10,0xe1,1);
   	write_page(0x5f,0x80,1);
   	write_page(0x5f,0x00,1);

   	TIM1_DelayMs();
}


void qma7981_read_raw_xyz(u16 *data)
{
             
   	u8 databuf[4] = {0};
    u16 data_raw[2];

   	read_page(0x01,databuf,4);

   	
   	data_raw[0]  = (short)((databuf[1]<<8) |( databuf[0]));
   	data_raw[1]  = (short)((databuf[3]<<8) |( databuf[2]));

   	data = data_raw[0]>>2;     //X轴原始数据
   // data[1] = data_raw[1]>>2;     //Y轴原始数据  	
}



