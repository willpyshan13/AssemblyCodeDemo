
#ifndef IIC
#define IIC

#include "mc30-common.h"
#include "mc30p6080.h"

//uchar ABuf,StatusBuf;


#define u8  unsigned char
#define u16 unsigned int
#define u32 unsigned long int
#define s32 long int
#define s16 int
#define s8  char




extern void iic_init(void);
extern void write_page(u8 addr,u8 *pdata,u8 len);
extern void read_page(u8 addr,u8 *pdata,u8 len);
extern void write_byte(u8 addr,u8 data);

u8 qmaX981_chip_id(void);





#endif
