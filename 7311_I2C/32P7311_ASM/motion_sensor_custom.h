#ifndef _MOTION_SENSOR_CUSTOM_H_
#define _MOTION_SENSOR_CUSTOM_H_
//#include "motion_sensor.h"

//define this macro to enable MEMSIC accelerometer auto-detect
//#define MXC_SENSOR_AUTO_DETECT

#ifdef MXC_SENSOR_AUTO_DETECT

//config slave address manually for sensor auto-detect
#define MEMSIC_ACC_SLAVE_ADDR		0x2A

#else //MXC_SENSOR_AUTO_DETECT

#define __MEMSIC_HW_IIC__			//使用硬件IIC接口

/******************************************************************************
* Sensor select
******************************************************************************/

/****** 2-axis MP G sensor *******/
//#define MXC62020
//#define MXC62021
//#define MXC62022
//#define MXC62023
//#define MXC62024
//#define MXC62025
//#define MXC62026
//#define MXC62027

/****** DTOS ******/
//#define MXC6220
//#define MXC6221
//#define MXC6222
//#define MXC6223
//#define MXC6224
#undef MXC62020
//#define MXC6225

#define MXC4005
//#define MXC6226
//#define MXC6227

/*
* DTOS Wafer Level Package
*
* Enable this definition for DTOS WLP (MXC622xXC)
*/
//#define DTOS_WLP

#if (defined(MXC62020)||defined(MXC62021)||defined(MXC62022)||defined(MXC62023)||defined(MXC62024)||defined(MXC62025)||defined(MXC62026)||defined(MXC62027))
#define MXC_2D_MP
#elif (defined(MXC6220)||defined(MXC6221)||defined(MXC6222)||defined(MXC6223)||defined(MXC6224)||defined(MXC6225)||defined(MXC6226)||defined(MXC6227))
#define MXC_2D_DTOS
#elif defined(MXC4005)
#define MXC_3D
#endif

/*
* MEMSIC acc sensor slave address
*/
#if (defined(MXC62020))
#define MEMSIC_ACC_SLAVE_ADDR	0x20
#elif (defined(MXC62021))
#define MEMSIC_ACC_SLAVE_ADDR	0x22
#elif (defined(MXC62022))
#define MEMSIC_ACC_SLAVE_ADDR	0x24
#elif (defined(MXC62023))
#define MEMSIC_ACC_SLAVE_ADDR	0x26
#elif (defined(MXC62024))
#define MEMSIC_ACC_SLAVE_ADDR	0x28
#elif (defined(MXC62025))
#define MEMSIC_ACC_SLAVE_ADDR	0x2A
#elif (defined(MXC62026))
#define MEMSIC_ACC_SLAVE_ADDR	0x2C
#elif (defined(MXC62027))
#define MEMSIC_ACC_SLAVE_ADDR	0x2E
#elif (defined(MXC6220))
#define MEMSIC_ACC_SLAVE_ADDR	0x20
#elif (defined(MXC6221))
#define MEMSIC_ACC_SLAVE_ADDR	0x22
#elif (defined(MXC6222))
#define MEMSIC_ACC_SLAVE_ADDR	0x24
#elif (defined(MXC6223))
#define MEMSIC_ACC_SLAVE_ADDR	0x26
#elif (defined(MXC6224))
#define MEMSIC_ACC_SLAVE_ADDR	0x28
#elif (defined(MXC6225))
#define MEMSIC_ACC_SLAVE_ADDR	0x2A
#elif (defined(MXC6226))
#define MEMSIC_ACC_SLAVE_ADDR	0x2C
#elif (defined(MXC6227))
#define MEMSIC_ACC_SLAVE_ADDR	0x2E
#elif defined(MXC4005)
#define MEMSIC_ACC_SLAVE_ADDR	(0x15<<1)
#else
#error Undefined MEMSIC_ACC_SLAVE_ADDR
#endif

#endif //MXC_SENSOR_AUTO_DETECT

#define ACC_0G_X		(2048) 
#define ACC_1G_X		(2048+512)
#define ACC_MINUS1G_X	(2048-512)
#define ACC_0G_Y		(2048)
#define ACC_1G_Y		(2048+512)
#define ACC_MINUS1G_Y	(2048-512)
#define ACC_0G_Z			(0)
#define ACC_1G_Z			(0)
#define ACC_MINUS1G_Z	(0)

enum
{
	DTOS_CTRL_POWER = 0x80,
	DTOS_CTRL_SHAKEMODE	= 0x40,
	DTOS_CTRL_SHAKETHRESHOLD = 0x30,
	DTOS_CTRL_SHAKECOUNT = 0x0C,
	DTOS_CTRL_ORIENTCOUNT = 0x03,
	DTOS_CTRL_ALL = 0xFF
};

//Acceleration sensor category
typedef enum
{
	MXC_SENSOR_UNKOWN,
	MXC_SENSOR_2D_XVMP,
	MXC_SENSOR_2D_DTOS
} mxc_sensor_category_t;

#ifdef MXC_SENSOR_AUTO_DETECT
extern mxc_sensor_category_t mxc_sensor_category;
#endif //MXC_SENSOR_AUTO_DETECT

extern void acc_sensor_pwr_up(void);
extern void acc_sensor_pwr_down(void);
extern void acc_sensor_get_5bytes(kal_uint16 *acc_x_adc, kal_uint16 *acc_y_adc,kal_uint16 *acc_z_adc);
#if (defined(MXC_2D_DTOS) || defined(MXC_SENSOR_AUTO_DETECT))
kal_uint8 DTOS_get_status(void);
void DTOS_get_data_and_status(kal_uint16* acc_adc_ptr, kal_uint8* status_ptr);
void DTOS_get_serial_ID(kal_uint8* serial_ID_ptr);
void DTOS_set_detection(kal_uint8 detection, kal_uint8 ctrl_code);
#endif //
extern void acc_sensor_init(void);
//extern MotionSensor_customize_function_struct *ms_GetFunc(void);
//extern MotionSensor_custom_data_struct *ms_get_data(void);

#endif //_MOTION_SENSOR_CUSTOM_H_

