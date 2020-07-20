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


/***********************��ʱ��0����*********************************/
//Ԥ��Ƶѡ��
#define TIM0_PRS_2				0x00
#define TIM0_PRS_4				0x01
#define TIM0_PRS_8				0x02
#define TIM0_PRS_16				0x03
#define TIM0_PRS_32				0x04
#define TIM0_PRS_64				0x05
#define TIM0_PRS_128			0x06
#define TIM0_PRS_256			0x07

#define TIM0_INTM				0						//�ⲿ�жϣ�INT��������ʽѡ�� 0���½��� 1��������
#define TIM0_T0PTS				0						//ʱ��Դѡ�� 0��FCPU	1��TC0������ⲿʱ��
#define TIM0_T0SE				0						//�ⲿʱ��TC0��Ч����ѡ�� 0�������ؼ��� 1���½��ؼ���
#define TIM0_T0PTA				0						//Ԥ����������λ 0����ʱ��0	1�����Ź�
#define TIM0_T0PRS				TIM0_PRS_32				//Ԥ��Ƶѡ�� FOSC(4MHz)/2=FCPU(2MHz) / 8 = 250KHz
#define TIM0_CNT				256 - 240			//����ֵ 250KHz/250=1KHz=1ms
//#define TIM0_CNT				256 - 25				//����ֵ 250KHz/25=10KHz=100us
#define TIM0_EN					1						//��ʱ������


void HalSysInit (void);
void HalTim0Init (void);
void HalExtiInit (void);

#endif
