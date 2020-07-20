#ifndef _HAL_SYS_H_
#define _HAL_SYS_H_
#include "mc30-common.h"
#include "MC30P6060.h"

#define BV(n)		(1<<(n))

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long int u32;

#define CLRWDT						__asm \
													CLRWDT;\
													__endasm;
#define STOP							__asm \
													STOP;\
													__endasm;

#define NOP            		__asm\
													NOP;\
													__endasm;


/***********************定时器0配置*********************************/
//预分频选择
#define TIM0_PRS_2				0x00
#define TIM0_PRS_4				0x01
#define TIM0_PRS_8				0x02
#define TIM0_PRS_16				0x03
#define TIM0_PRS_32				0x04
#define TIM0_PRS_64				0x05
#define TIM0_PRS_128			0x06
#define TIM0_PRS_256			0x07

#define TIM0_INTM				0						//外部中断（INT）触发方式选择 0：下降沿 1：上升沿
#define TIM0_T0PTS				0						//时钟源选择 0：FCPU	1：TC0输入的外部时钟
#define TIM0_T0SE				0						//外部时钟TC0有效边沿选择 0：上升沿计数 1：下降沿计数
#define TIM0_T0PTA				0						//预分配器控制位 0：定时器0	1：看门狗
#define TIM0_T0PRS				TIM0_PRS_32				//预分频选择 FOSC(4MHz)/2=FCPU(2MHz) / 8 = 250KHz
#define TIM0_CNT				256 - 240			//计数值 250KHz/250=1KHz=1ms
//#define TIM0_CNT				256 - 25				//计数值 250KHz/25=10KHz=100us
#define TIM0_EN					1						//定时器开关


void HalSysInit (void);
void HalTim0Init (void);
void HalExtiInit (void);

#endif
