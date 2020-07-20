#include "kal_release.h"
#include "motion_sensor.h"
#include "gpio_sw.h"
#include "motion_sensor_custom.h"
#include "drvsignals.h"
#include "dcl_i2c.h"
void (*FallDownEintCallBack)(void) = NULL;
kal_uint8 SnesorStatue = 0x00;
kal_bool senseor_enit_statue = KAL_TRUE;
kal_uint8 SensorIsFallDown = 0;
extern  const char gpio_ms_i2c_data_pin;
extern  const char gpio_ms_i2c_clk_pin ;
/*
* GPIO configuration
*/
#define ACC_SENSOR_SCK  1
#define ACC_SENSOR_SDA  2//45
#if defined(__MEMSIC_HW_IIC__)
DCL_HANDLE memsic_i2c_handle = 0xFF;
#endif
/*
* I2C bus control
*/
#define ACC_SET_I2C_CLK_OUTPUT		GPIO_InitIO(OUTPUT,ACC_SENSOR_SCK)
#define ACC_SET_I2C_CLK_INPUT			GPIO_InitIO(INPUT,ACC_SENSOR_SCK)
#define ACC_SET_I2C_DATA_OUTPUT		GPIO_InitIO(OUTPUT,ACC_SENSOR_SDA)
#define ACC_SET_I2C_DATA_INPUT			GPIO_InitIO(INPUT,ACC_SENSOR_SDA)
#define ACC_SET_I2C_CLK_HIGH			GPIO_WriteIO(1,ACC_SENSOR_SCK)
#define ACC_SET_I2C_CLK_LOW			GPIO_WriteIO(0,ACC_SENSOR_SCK)
#define ACC_SET_I2C_DATA_HIGH			GPIO_WriteIO(1,ACC_SENSOR_SDA)
#define ACC_SET_I2C_DATA_LOW			GPIO_WriteIO(0,ACC_SENSOR_SDA)
#define ACC_GET_I2C_DATA_BIT			GPIO_ReadIO(ACC_SENSOR_SDA)

/*
* Loop duration in nanosecond
*/
#ifdef MCU_208M
#define LOOP_DURATION_NS	25
#elif MCU_104M
#define LOOP_DURATION_NS	50
#else
#define LOOP_DURATION_NS	25
#endif

/*
* Delay loop for I2C bus driver
*/
enum
{
	//start setup time, >= 0.6 uS
	DELAY_LOOP_START_SETUP = 600/LOOP_DURATION_NS,

	//start hold time, >= 0.6 uS
	DELAY_LOOP_START_HOLD = 600/LOOP_DURATION_NS,

	//LOW period of SCL, >= 1.3 uS
	DELAY_LOOP_SCL_LOW = 1300/LOOP_DURATION_NS,

	//HIGH period of SCL, >= 0.6 uS
	DELAY_LOOP_SCL_HIGH = 600/LOOP_DURATION_NS,

	//data hold time, <= 0.9 uS
	DELAY_LOOP_DATA_HOLD = 100/LOOP_DURATION_NS,

	//data setup time, >= 0.1 uS
	DELAY_LOOP_DATA_SETUP = DELAY_LOOP_SCL_LOW - DELAY_LOOP_DATA_HOLD,

	//stop setup time, >= 0.6 uS
	DELAY_LOOP_STOP_SETUP = DELAY_LOOP_START_SETUP,

	//bus free time between STOP and START, >= 1.3 uS
	DELAY_LOOP_BUS_FREE = 1300/LOOP_DURATION_NS
};

/*
* macro function for i2c delay
*/
#define memsic_acc_i2c_delay_loop(loop)	\
{	\
	kal_uint8 i;	\
	for (i=0; i<(loop); i++);	\
}

/*
* macro function for i2c start/restart
*/
#define memsic_acc_i2c_start()	\
{	\
	ACC_SET_I2C_DATA_OUTPUT;	\
	ACC_SET_I2C_CLK_OUTPUT; 	\
	ACC_SET_I2C_DATA_HIGH;		\
	ACC_SET_I2C_CLK_HIGH;		\
	memsic_acc_i2c_delay_loop(DELAY_LOOP_START_SETUP);	\
	ACC_SET_I2C_DATA_LOW;	\
	memsic_acc_i2c_delay_loop(DELAY_LOOP_START_HOLD);	\
	ACC_SET_I2C_CLK_LOW;	\
}

/*
* macro function for i2c write
*/
#define memsic_acc_i2c_write(data)	\
{	\
	kal_int8 i;	\
	ACC_SET_I2C_DATA_OUTPUT;	\
	ACC_SET_I2C_CLK_LOW;	\
	for (i=7;i>=0;i--)	\
	{	\
		memsic_acc_i2c_delay_loop(DELAY_LOOP_DATA_HOLD);		\
		if ((data) & (1<<i))	\
		{	\
			ACC_SET_I2C_DATA_HIGH;	\
		}	\
		else	\
		{	\
			ACC_SET_I2C_DATA_LOW;	\
		}	\
		memsic_acc_i2c_delay_loop(DELAY_LOOP_DATA_SETUP);		\
		ACC_SET_I2C_CLK_HIGH;	\
		memsic_acc_i2c_delay_loop(DELAY_LOOP_SCL_HIGH);		\
		ACC_SET_I2C_CLK_LOW;	\
	}	\
}

/*
* macro function for i2c read
*/
#define memsic_acc_i2c_read(data)	\
{	\
	kal_int8 i;	\
	(data) = 0;	\
	ACC_SET_I2C_CLK_LOW;	\
	ACC_SET_I2C_DATA_INPUT;	\
	for (i=7;i>=0;i--)	\
	{	\
		memsic_acc_i2c_delay_loop(DELAY_LOOP_SCL_LOW);		\
		ACC_SET_I2C_CLK_HIGH;	\
		memsic_acc_i2c_delay_loop(DELAY_LOOP_SCL_HIGH);		\
		if (ACC_GET_I2C_DATA_BIT)	\
		{	\
			(data) |= (1<<i);	\
		}	\
		ACC_SET_I2C_CLK_LOW;	\
	}	\
}

/*
* macro function for i2c slave acknowledge
*/
#define memsic_acc_i2c_slave_ack(ack)	\
{	\
	ACC_SET_I2C_CLK_LOW;	\
	ACC_SET_I2C_DATA_INPUT;	\
	memsic_acc_i2c_delay_loop(DELAY_LOOP_SCL_LOW);		\
	ACC_SET_I2C_CLK_HIGH;	\
	memsic_acc_i2c_delay_loop(DELAY_LOOP_SCL_HIGH);		\
	(ack) = ACC_GET_I2C_DATA_BIT;	\
	ACC_SET_I2C_CLK_LOW;	\
}

/*
* macro function for master acknowledge
*/
#define memsic_acc_i2c_master_ack()	\
{	\
	ACC_SET_I2C_CLK_LOW;	\
	ACC_SET_I2C_DATA_OUTPUT;	\
	memsic_acc_i2c_delay_loop(DELAY_LOOP_DATA_HOLD);		\
	ACC_SET_I2C_DATA_LOW;	\
	memsic_acc_i2c_delay_loop(DELAY_LOOP_DATA_SETUP);		\
	ACC_SET_I2C_CLK_HIGH;	\
	memsic_acc_i2c_delay_loop(DELAY_LOOP_SCL_HIGH);		\
	ACC_SET_I2C_CLK_LOW;	\
}

/*
* macro function for i2c stop
*/
#define memsic_acc_i2c_stop()	\
{	\
	ACC_SET_I2C_CLK_LOW;	\
	ACC_SET_I2C_DATA_OUTPUT;	\
	ACC_SET_I2C_DATA_LOW;	\
	memsic_acc_i2c_delay_loop(DELAY_LOOP_SCL_LOW);		\
	ACC_SET_I2C_CLK_HIGH;	\
	memsic_acc_i2c_delay_loop(DELAY_LOOP_STOP_SETUP);		\
	ACC_SET_I2C_DATA_HIGH;	\
}

/*customizaton function pointer*/
/*MotionSensor_customize_function_struct ms_custom_func=
{
	ms_get_data,
	acc_sensor_get_5bytes,
	acc_sensor_init,
	acc_sensor_pwr_up,
	acc_sensor_pwr_down
};*/

/*customizaton data*/
#if 0
MotionSensor_custom_data_struct  ms_custom_data_def = 
{          
	/*X axis*/
	ACC_0G_X,
	ACC_1G_X,
	ACC_MINUS1G_X,
	/*Y axis*/
	ACC_0G_Y,
	ACC_1G_Y,
	ACC_MINUS1G_Y,
	/*Z axis*/
	ACC_0G_Z,
	ACC_1G_Z,
	ACC_MINUS1G_Z
};
#endif
static void XXXDelayms(kal_uint16 data)
{
	kal_uint32 time1=0, diff=0;
	
	time1=drv_get_current_time();

	while(drv_get_duration_ms(time1) < data);
}
#ifdef MXC_SENSOR_AUTO_DETECT
//MXC sensor category indicator to indentify which sensor on board
mxc_sensor_category_t mxc_sensor_category = MXC_SENSOR_UNKOWN;
#endif //MXC_SENSOR_AUTO_DETECT
#if defined(__MEMSIC_HW_IIC__)
kal_bool memsic_open_i2c()
{
	DCL_STATUS Open_status;
	I2C_CONFIG_T HWSccbPara;

	HWSccbPara.eOwner = DCL_I2C_OWNER_GS;
	HWSccbPara.fgGetHandleWait = KAL_TRUE;
	HWSccbPara.eTransactionMode = DCL_I2C_TRANSACTION_FAST_MODE;
	HWSccbPara.u1SlaveAddress = (MEMSIC_ACC_SLAVE_ADDR);
	HWSccbPara.u1DelayLen = 0;
	HWSccbPara.u4FastModeSpeed = 100;
	HWSccbPara.u4HSModeSpeed = 0;
	HWSccbPara.fgEnableDMA = KAL_FALSE;
	memsic_i2c_handle = DclSI2C_Open(DCL_I2C, HWSccbPara.eOwner);
	Open_status = DclSI2C_Configure(memsic_i2c_handle, (DCL_CONFIGURE_T *)&HWSccbPara);
	if ( STATUS_OK != Open_status )
	{
		kal_prompt_trace(MOD_ENG, "memsic I2C Open Failed! error:%d", Open_status);
		return KAL_FALSE;
	}
	else
	{
		return KAL_TRUE;
	}
}
void Memsic_Close_i2c()
{
	if(memsic_i2c_handle != 0xFF)
	{
		DclSI2C_Close(memsic_i2c_handle);
		memsic_i2c_handle = 0xFF;
	}
}
char Memsic_I2C_write(unsigned char SlaveAddr, unsigned char reg, unsigned char *buf, unsigned char buf_size)
{
	DCL_STATUS rt;
	I2C_CTRL_SINGLE_WRITE_T WriteData;
	kal_uint8 WriteBuff[10];
	int i = 0;

	kal_prompt_trace(MOD_ENG, "reg=%x", reg);

	if(memsic_i2c_handle == 0xFF)
	{
		memsic_open_i2c();
	}
	
	WriteData.u4DataLen = 0;
	
	WriteBuff[WriteData.u4DataLen++] = reg;
	
	do
	{
		WriteBuff[WriteData.u4DataLen++] = *(buf+i++);
		
	}while(i < buf_size);
	
	WriteData.pu1Data = WriteBuff;
	
	rt = DclSI2C_Control(memsic_i2c_handle, I2C_CMD_SINGLE_WRITE, (DCL_CTRL_DATA_T *)&WriteData);
	if(rt != STATUS_OK)
	{
		kal_prompt_trace(MOD_ENG, "Memsic_I2C_write: I2C Write Error:%d, %x", rt, memsic_i2c_handle);
		return 0;
	}
	return 1;
}

char Memsic_I2C_read(unsigned char SlaveAddr, unsigned char reg, unsigned char *buf, unsigned char buf_size)
{
	DCL_STATUS status;
    kal_uint8 WriteBuff[2] = {0x00};
	I2C_CTRL_SINGLE_WRITE_T WriteData;
	I2C_CTRL_SINGLE_READ_T ReadData;

	if(memsic_i2c_handle == 0xFF)
	{
		memsic_open_i2c();
	}
	
	WriteData.u4DataLen = 0;
	
	WriteBuff[WriteData.u4DataLen++] = reg;
	
	WriteData.pu1Data = WriteBuff;
	
	status = DclSI2C_Control(memsic_i2c_handle, I2C_CMD_SINGLE_WRITE, (DCL_CTRL_DATA_T *)&WriteData);
	
	if ( STATUS_OK != status )
	{
	    kal_prompt_trace(MOD_ENG,"Memsic_I2C_read:I2C Write error = %d, %x",status, memsic_i2c_handle);
	    return 0;
	}
	
	ReadData.pu1Data = buf;
	
	ReadData.u4DataLen = buf_size;
	
	status = DclSI2C_Control(memsic_i2c_handle, I2C_CMD_SINGLE_READ, (DCL_CTRL_DATA_T *)&ReadData);

	if ( STATUS_OK != status )
	{
	    kal_prompt_trace(MOD_ENG,"Memsic_I2C_read:I2C read error = %d, %x",status, memsic_i2c_handle);
	    return 0;
	}
	else
	{
	    return 1;
	}
}

#endif
#if (defined(MXC_2D_MP) || defined(MXC_SENSOR_AUTO_DETECT))

static void XVMP_pwr_up(void)
{
	kal_uint8 ack;
#if defined(__MEMSIC_HW_IIC__)
	kal_uint8 reg = 0x00;
	kal_uint8 data = 0x00;
	Memsic_I2C_write(MEMSIC_ACC_SLAVE_ADDR, reg, &data, 1);
#else
	//bus start
	memsic_acc_i2c_start();
	//send slave address with WRITE
	memsic_acc_i2c_write(MEMSIC_ACC_SLAVE_ADDR);
	memsic_acc_i2c_slave_ack(ack);
	//sub-address
	memsic_acc_i2c_write(0x00);
	memsic_acc_i2c_slave_ack(ack);
	//send command
	memsic_acc_i2c_write(0x00);
	memsic_acc_i2c_slave_ack(ack);
	//bus stop
	memsic_acc_i2c_stop();
#endif	
}

static void XVMP_pwr_down(void)
{
	kal_uint8 ack;
	#if defined(__MEMSIC_HW_IIC__)
	kal_uint8 reg = 0x00;
	kal_uint8 data = 0x01;
	Memsic_I2C_write(MEMSIC_ACC_SLAVE_ADDR, reg, &data, 1);
	#else
	//bus start
	memsic_acc_i2c_start();
	//send slave address with WRITE
	memsic_acc_i2c_write(MEMSIC_ACC_SLAVE_ADDR);
	memsic_acc_i2c_slave_ack(ack);
	//sub-address
	memsic_acc_i2c_write(0x00);
	memsic_acc_i2c_slave_ack(ack);
	//send command
	memsic_acc_i2c_write(0x01);
	memsic_acc_i2c_slave_ack(ack);
	//bus stop
	memsic_acc_i2c_stop();
	#endif
}

static void XVMP_get_data(kal_uint16 *acc_x_adc, kal_uint16 *acc_y_adc)
{
	kal_uint8 get_byte[4];
	kal_uint8 ack;
	#if defined(__MEMSIC_HW_IIC__)
	Memsic_I2C_read(MEMSIC_ACC_SLAVE_ADDR, 0x01, get_byte, 4);
	#else
	//bus start
	memsic_acc_i2c_start();
	//send slave address with WRITE
	memsic_acc_i2c_write(MEMSIC_ACC_SLAVE_ADDR);
	memsic_acc_i2c_slave_ack(ack);
	
	//sub-address
	memsic_acc_i2c_write(0x01);
	memsic_acc_i2c_slave_ack(ack);
	//bus restart
	memsic_acc_i2c_start();
	//send slave address with READ
	memsic_acc_i2c_write(MEMSIC_ACC_SLAVE_ADDR+1);
	memsic_acc_i2c_slave_ack(ack);
	//read MSB X-axis
	memsic_acc_i2c_read(get_byte[0]);
	memsic_acc_i2c_master_ack();
	//read LSB X-axis
	memsic_acc_i2c_read(get_byte[1]);
	memsic_acc_i2c_master_ack();
	//read MSB Y-axis
	memsic_acc_i2c_read(get_byte[2]);
	memsic_acc_i2c_master_ack();
	//read LSB Y-axis
	memsic_acc_i2c_read(get_byte[3]);

	//bus stop
	memsic_acc_i2c_stop();
	#endif
	*acc_x_adc=(get_byte[0]<<8)|get_byte[1];
	*acc_y_adc=(get_byte[2]<<8)|get_byte[3];
}

#endif //

#if (defined(MXC_2D_DTOS) || defined(MXC_SENSOR_AUTO_DETECT))

static void DTOS_get_data(kal_uint16 *acc_x_adc, kal_uint16 *acc_y_adc)
{
	kal_int8 get_byte[2];
	kal_uint8 ack;
	#if defined(__MEMSIC_HW_IIC__)
	Memsic_I2C_read(MEMSIC_ACC_SLAVE_ADDR, 0x00, get_byte, 2);
	#else
	//bus start
	memsic_acc_i2c_start();
	//send slave address with WRITE
	memsic_acc_i2c_write(MEMSIC_ACC_SLAVE_ADDR);
	memsic_acc_i2c_slave_ack(ack);
	
	//sub-address
	memsic_acc_i2c_write(0x00);
	memsic_acc_i2c_slave_ack(ack);
	//bus restart
	memsic_acc_i2c_start();
	//send slave address with READ
	memsic_acc_i2c_write(MEMSIC_ACC_SLAVE_ADDR+1);
	memsic_acc_i2c_slave_ack(ack);
	//read X-axis
	memsic_acc_i2c_read(get_byte[0]);
	memsic_acc_i2c_master_ack();
	//read Y-axis
	memsic_acc_i2c_read(get_byte[1]);

	//bus stop
	memsic_acc_i2c_stop();
	#endif
	//scale to unsigned 16 bits integer format, 2048 is 0 g offset, 512 is sensitivity	
	*acc_x_adc = (kal_uint16)(2048 + (get_byte[0] * 8));
	#ifdef DTOS_WLP
	*acc_y_adc = (kal_uint16)(2048 + (get_byte[1] * 8));
	#else //DTOS_WLP
	*acc_y_adc = (kal_uint16)(2048 + (get_byte[1] * 8));
	#endif //DTOS_WLP
}

/*
* FUNCTION                                                            
*	DTOS_get_status
*
* DESCRIPTION                                                           
*   	This function is to read DTOS sensor status
*
* CALLS  
*
* PARAMETERS
*  	None
*	
* RETURNS
*	status
*/    
kal_uint8 DTOS_get_status(void)
{
	kal_uint8 get_byte;
	kal_uint8 ack;
	#if defined(__MEMSIC_HW_IIC__)
	Memsic_I2C_read(MEMSIC_ACC_SLAVE_ADDR, 0x02, &get_byte, 1);
	#else
	//bus start
	memsic_acc_i2c_start();
	//send slave address with WRITE
	memsic_acc_i2c_write(MEMSIC_ACC_SLAVE_ADDR);
	memsic_acc_i2c_slave_ack(ack);
	
	//sub-address
	memsic_acc_i2c_write(0x02);
	memsic_acc_i2c_slave_ack(ack);
	//bus restart
	memsic_acc_i2c_start();
	//send slave address with READ
	memsic_acc_i2c_write(MEMSIC_ACC_SLAVE_ADDR+1);
	memsic_acc_i2c_slave_ack(ack);
	//read status register
	memsic_acc_i2c_read(get_byte);

	//bus stop
	memsic_acc_i2c_stop();
	#endif
	return get_byte;
}

/*
* FUNCTION                                                            
*	DTOS_get_data_and_status
*
* DESCRIPTION                                                           
*   	This function is to read DTOS sensor x/y axes data and status
*
* CALLS  
*
* PARAMETERS
*  	acc_adc_ptr
*		pointer to caller's buffer to return x/y/z axes data
*		NOTE: the buffer must be at least 3 elements array
*	status_ptr
*		pointer to caller's buffer to return DTOS native detection status
*	
* RETURNS
*	None
*/    
void DTOS_get_data_and_status(kal_uint16* acc_adc_ptr, kal_uint8* status_ptr)
{
	kal_uint8 get_byte[3];
	kal_uint8 ack;
	#if defined(__MEMSIC_HW_IIC__)
	Memsic_I2C_read(MEMSIC_ACC_SLAVE_ADDR, 0x00, get_byte, 3);
	#else
	//bus start
	memsic_acc_i2c_start();
	//send slave address with WRITE
	memsic_acc_i2c_write(MEMSIC_ACC_SLAVE_ADDR);
	memsic_acc_i2c_slave_ack(ack);
	
	//sub-address
	memsic_acc_i2c_write(0x00);
	memsic_acc_i2c_slave_ack(ack);
	//bus restart
	memsic_acc_i2c_start();
	//send slave address with READ
	memsic_acc_i2c_write(MEMSIC_ACC_SLAVE_ADDR+1);
	memsic_acc_i2c_slave_ack(ack);
	//read X-axis
	memsic_acc_i2c_read(get_byte[0]);
	memsic_acc_i2c_master_ack();
	//read Y-axis
	memsic_acc_i2c_read(get_byte[1]);
	memsic_acc_i2c_master_ack();
	//read status register
	memsic_acc_i2c_read(get_byte[2]);

	//bus stop
	memsic_acc_i2c_stop();
	#endif
	//scale to unsigned 16 bits integer format, 2048 is 0 g offset, 512 is sensitivity	
	//x-axis
	acc_adc_ptr[0] = (kal_uint16)(2048 - (((kal_int8)get_byte[0]) * 8));
	//y-axis
	#ifdef DTOS_WLP
	acc_adc_ptr[1] = (kal_uint16)(2048 + (((kal_int8)get_byte[1]) * 8));
	#else //DTOS_WLP
	acc_adc_ptr[1] = (kal_uint16)(2048 - (((kal_int8)get_byte[1]) * 8));
	#endif //DTOS_WLP
	//z-axis
	acc_adc_ptr[2] = 2048;

	*status_ptr = get_byte[2];
}

/*
* FUNCTION                                                            
*	DTOS_get_serial_ID
*
* DESCRIPTION                                                           
*   	This function is to read DTOS serial ID
*
* CALLS  
*
* PARAMETERS
*  	serial_ID_ptr
*		pointer to caller's buffer to return 3 bytes serial ID
*		NOTE: the buffer must be at least 3 elements array
*	
* RETURNS
*	None
*/    
void DTOS_get_serial_ID(kal_uint8* serial_ID_ptr)
{
	kal_uint8 get_byte[3];
	kal_uint8 ack;
	#if defined(__MEMSIC_HW_IIC__)
	Memsic_I2C_read(MEMSIC_ACC_SLAVE_ADDR, 0x08, &get_byte[0], 1);
	Memsic_I2C_read(MEMSIC_ACC_SLAVE_ADDR, 0x0e, &get_byte[1], 1);
	#else
	//bus start
	memsic_acc_i2c_start();
	//send slave address with WRITE
	memsic_acc_i2c_write(MEMSIC_ACC_SLAVE_ADDR);
	memsic_acc_i2c_slave_ack(ack);
	
	//sub-address
	memsic_acc_i2c_write(0x08);
	memsic_acc_i2c_slave_ack(ack);
	//bus restart
	memsic_acc_i2c_start();
	//send slave address with READ
	memsic_acc_i2c_write(MEMSIC_ACC_SLAVE_ADDR+1);
	memsic_acc_i2c_slave_ack(ack);
	//read ID0
	memsic_acc_i2c_read(get_byte[0]);
	memsic_acc_i2c_master_ack();
	//read ID1
	memsic_acc_i2c_read(get_byte[1]);
	memsic_acc_i2c_master_ack();
	//read ID2
	memsic_acc_i2c_read(get_byte[2]);

	//bus stop
	memsic_acc_i2c_stop();
	#endif
	//ID0
	serial_ID_ptr[0] = get_byte[0];
	//ID1
	serial_ID_ptr[1] = get_byte[1];
	//ID2
	serial_ID_ptr[2] = get_byte[2] >> 4;
}

/*
* FUNCTION                                                            
*	DTOS_set_detection
*
* DESCRIPTION                                                           
*   	This function is to set DTOS sensor detection register
*
* CALLS  
*
* PARAMETERS
*  	detection - value to be write corresponding bits of detect register
*	ctrl_code - specify which bits to be modified
*	
* RETURNS
*	None
*/    
void DTOS_set_detection(kal_uint8 detection, kal_uint8 ctrl_code)
{
	//mirror of DTOS detection register
	static kal_uint8 dtos_detection_reg = 0x00;
	kal_uint8 ack;

	//clear bits to be updated
	dtos_detection_reg &= ~ctrl_code;
	//update corresponding bits
	dtos_detection_reg |= (detection & ctrl_code);
	//bus start
	#if defined(__MEMSIC_HW_IIC__)
	Memsic_I2C_write(MEMSIC_ACC_SLAVE_ADDR, 0x04, &dtos_detection_reg, 1);
	#else
	memsic_acc_i2c_start();
	//send slave address with WRITE
	memsic_acc_i2c_write(MEMSIC_ACC_SLAVE_ADDR);
	memsic_acc_i2c_slave_ack(ack);
	
	//sub-address
	memsic_acc_i2c_write(0x04);
	memsic_acc_i2c_slave_ack(ack);
	//send command
	memsic_acc_i2c_write(dtos_detection_reg);
	memsic_acc_i2c_slave_ack(ack);
	//bus stop
	memsic_acc_i2c_stop();
	#endif
}

#endif //
#if defined(MXC_3D)
void MXC_3D_write(unsigned char SlaveAddr, unsigned char reg, unsigned char *buf, unsigned char buf_size)
{
	#if defined(__MEMSIC_HW_IIC__)
	Memsic_I2C_write(MEMSIC_ACC_SLAVE_ADDR, reg, buf, buf_size);
	#else
	kal_uint8 ack;
	memsic_acc_i2c_start();
	//send slave address with WRITE
	memsic_acc_i2c_write(MEMSIC_ACC_SLAVE_ADDR);
	memsic_acc_i2c_slave_ack(ack);
	
	//sub-address
	memsic_acc_i2c_write(reg);
	memsic_acc_i2c_slave_ack(ack);
	//send command
	memsic_acc_i2c_write(*buf);
	memsic_acc_i2c_slave_ack(ack);
	//bus stop
	memsic_acc_i2c_stop();
	#endif
}
void MXC_3D_read(unsigned char SlaveAddr, unsigned char reg, unsigned char *buf, unsigned char buf_size)
{
	#if defined(__MEMSIC_HW_IIC__)
	Memsic_I2C_read(MEMSIC_ACC_SLAVE_ADDR, reg, buf, buf_size);
	#else
	int i = 0;
	kal_uint8 ack;
	//bus start
	memsic_acc_i2c_start();
	//send slave address with WRITE
	memsic_acc_i2c_write(MEMSIC_ACC_SLAVE_ADDR);
	memsic_acc_i2c_slave_ack(ack);
	
	//sub-address
	memsic_acc_i2c_write(0x00);
	memsic_acc_i2c_slave_ack(ack);
	//bus restart
	memsic_acc_i2c_start();
	//send slave address with READ
	memsic_acc_i2c_write(MEMSIC_ACC_SLAVE_ADDR+1);
	memsic_acc_i2c_slave_ack(ack);
	for (i = 0; i < buf_size - 1; i++)
	{
		//read X-axis
		memsic_acc_i2c_read(buf[i]);
		memsic_acc_i2c_master_ack();
	}
	//read status register
	memsic_acc_i2c_read(buf[i]);

	//bus stop
	memsic_acc_i2c_stop();
	#endif
}
void MXC_3D_Power_Up()
{
	kal_uint8 data = 0x00;
	
	MXC_3D_write(MEMSIC_ACC_SLAVE_ADDR, 0x0D, &data, 1);

	//ta = 0x3;		//开启方向检测

	//msic_I2C_write(MEMSIC_ACC_SLAVE_ADDR, 0x0C, &data, 1);

	//data = 0xFF;	//启动中断
			
	//Memsic_I2C_write(MEMSIC_ACC_SLAVE_ADDR, 0x0A, &data, 1);

	XXXDelayms(500);

	//Memsic_I2C_read(MEMSIC_ACC_SLAVE_ADDR, 0x0E, &data, 1);

	//kal_prompt_trace(MOD_ENG, "3d Sensor : %x", data);
}
void MXC_3D_Power_Down()
{
	kal_uint8 data = 0x01;
	MXC_3D_write(MEMSIC_ACC_SLAVE_ADDR, 0x0D, &data, 1);
}
void MXC_3D_get_data(kal_uint16 *x, kal_uint16*y, kal_uint16 *z)
{
	kal_uint8 data[2];
	kal_uint16 _x, _y, _z;
	int a_x, a_y, a_z;
	
	MXC_3D_read(MEMSIC_ACC_SLAVE_ADDR, 0x03, &data[0], 1);			//x msb
	MXC_3D_read(MEMSIC_ACC_SLAVE_ADDR, 0x04, &data[1], 1);			//x lsb
	_x = (kal_uint16)(((data[0]<<8)|data[1])>>4);

	if (_x >= 0x800)
		a_x = -(4095 - _x);
	else
		a_x = _x;
//	kal_prompt_trace(MOD_ENG, "x = %x, %x", data[0], data[1]);
	
	MXC_3D_read(MEMSIC_ACC_SLAVE_ADDR, 0x05, &data[0], 1);			//y msb
	MXC_3D_read(MEMSIC_ACC_SLAVE_ADDR, 0x06, &data[1], 1);			//y lsb
	_y = (kal_uint16)(((data[0]<<8)|data[1])>>4);
	
	if (_y >= 0x800)
		a_y = -(4095 - _y);
	else
		a_y = _y;
//	kal_prompt_trace(MOD_ENG, "y = %x, %x", data[0], data[1]);
	
	MXC_3D_read(MEMSIC_ACC_SLAVE_ADDR, 0x07, &data[0], 1);			//z msb
	MXC_3D_read(MEMSIC_ACC_SLAVE_ADDR, 0x08, &data[1], 1);			//z lsb
	_z = (kal_uint16)(((data[0]<<8)|data[1])>>4);
	if (_z >= 0x800)
		a_z = -(4095 - _z);
	else
		a_z = _z;
//	kal_prompt_trace(MOD_ENG, "z = %x, %x", data[0], data[1]);
	
	*x = (kal_uint16)(2048 + (a_x / 2));
	*y = (kal_uint16)(2048 + (a_y / 2));
	*z = (kal_uint16)(2048 + (a_z / 2));
	
//	kal_prompt_trace(MOD_ENG, "_x = %d, _y = %d, _z = %d", _x, _y, _z);
//	kal_prompt_trace(MOD_ENG, "a_x = %d, a_y = %d, a_z = %d", a_x, a_y, a_z);
}
#endif
#ifdef MXC_SENSOR_AUTO_DETECT

static mxc_sensor_category_t mxc_sensor_auto_detect(void)
{
	kal_uint8 get_byte[3];
	kal_uint8 ack;

	//bus start
	memsic_acc_i2c_start();
	//send slave address with WRITE
	memsic_acc_i2c_write(MEMSIC_ACC_SLAVE_ADDR);
	memsic_acc_i2c_slave_ack(ack);
	
	//sub-address
	memsic_acc_i2c_write(0x05);
	memsic_acc_i2c_slave_ack(ack);
	//bus restart
	memsic_acc_i2c_start();
	//send slave address with READ
	memsic_acc_i2c_write(MEMSIC_ACC_SLAVE_ADDR+1);
	memsic_acc_i2c_slave_ack(ack);
	//read X-axis
	memsic_acc_i2c_read(get_byte[0]);
	memsic_acc_i2c_master_ack();
	//read Y-axis
	memsic_acc_i2c_read(get_byte[1]);
	memsic_acc_i2c_master_ack();
	//read Y-axis
	memsic_acc_i2c_read(get_byte[2]);

	//bus stop
	memsic_acc_i2c_stop();

	#define DTOS_MAGIC_CODE_1 (MEMSIC_ACC_SLAVE_ADDR+1)
	#define DTOS_MAGIC_CODE_2 (MEMSIC_ACC_SLAVE_ADDR+1)
	#define DTOS_MAGIC_CODE_3 (MEMSIC_ACC_SLAVE_ADDR+1)
	#define XVMP_MAGIC_CODE_1 0x00
	#define XVMP_MAGIC_CODE_2 0x00
	#define XVMP_MAGIC_CODE_3 0x00
	//check the three magic bytes
	if ((get_byte[0] == DTOS_MAGIC_CODE_1)
		&& (get_byte[1] == DTOS_MAGIC_CODE_2)
		&& (get_byte[2] == DTOS_MAGIC_CODE_3))
	{
		return MXC_SENSOR_2D_DTOS;
	}
	else if ((get_byte[0] == XVMP_MAGIC_CODE_1)
		&& (get_byte[1] == XVMP_MAGIC_CODE_2)
		&& (get_byte[2] == XVMP_MAGIC_CODE_3))
	{
		return MXC_SENSOR_2D_XVMP;
	}
	else
	{
		return MXC_SENSOR_UNKOWN;
	}
}

#endif //MXC_SENSOR_AUTO_DETECT

/*
* FUNCTION                                                            
*	acc_sensor_pwr_up
*
* DESCRIPTION                                                           
*   	This function is to set sensor at power on mode.
*
* CALLS  
*
* PARAMETERS
*  None
*	
* RETURNS
*	None
*/
void memsic_sensor_pwr_up_fall_down(void (*CallBack)(void))
{
	void acc_sensor_pwr_up(void);
	kal_prompt_trace(MOD_ENG, "Fall Down Power On!!!!");
	FallDownEintCallBack = CallBack;
	acc_sensor_pwr_up();
	//DTOS_set_detection(0x00, DTOS_CTRL_ALL);
	SensorIsFallDown = 1;
}
void memsic_sensor_pwr_down_fall_down()
{
	kal_prompt_trace(MOD_ENG, "Fall Down Power Down!!!!");
	FallDownEintCallBack = NULL;
	acc_sensor_pwr_down();
	SensorIsFallDown = 0;
}
void acc_sensor_pwr_up(void)
{
if(SensorIsFallDown == 1)
	return;
#ifdef MXC_SENSOR_AUTO_DETECT

	switch (mxc_sensor_category)
	{
	case MXC_SENSOR_2D_XVMP:
		XVMP_pwr_up();
		break;
	case MXC_SENSOR_2D_DTOS:
		DTOS_set_detection(0x00, DTOS_CTRL_POWER);
		break;
	}
	
#else //MXC_SENSOR_AUTO_DETECT

	#if (defined(MXC_2D_MP))

	XVMP_pwr_up();

	#elif defined(MXC_2D_DTOS)

	DTOS_set_detection(0x00, DTOS_CTRL_POWER);

	#elif defined(MXC_3D)
	MXC_3D_Power_Up();
	#endif
	
#endif //MXC_SENSOR_AUTO_DETECT
}
kal_bool sn_acc_sensor_pwr_up()
{
	kal_bool result = KAL_FALSE;

	kal_uint8 sensor_id;

	acc_sensor_pwr_up();

	#if defined(MXC_3D)
	//检测ID，判断是否开启成功
	MXC_3D_read(MEMSIC_ACC_SLAVE_ADDR, 0x0E, &sensor_id, 1);
	
	if(sensor_id == 0x02)
		result = KAL_TRUE;
	#endif

	return result;
}
/*
* FUNCTION                                                            
*	acc_sensor_pwr_down
*
* DESCRIPTION                                                           
*   	This function is to set sensor at power down mode.
*
* CALLS  
*
* PARAMETERS
*  None
*	
* RETURNS
*	None
*/
void acc_sensor_pwr_down(void)
{
#ifdef MXC_SENSOR_AUTO_DETECT

	switch (mxc_sensor_category)
	{
	case MXC_SENSOR_2D_XVMP:
		XVMP_pwr_down();
		break;
	case MXC_SENSOR_2D_DTOS:
		DTOS_set_detection(0x80, DTOS_CTRL_POWER);
		break;
	}

#else //MXC_SENSOR_AUTO_DETECT

	#if (defined(MXC_2D_MP))

	XVMP_pwr_down();

	#elif defined(MXC_2D_DTOS)

	DTOS_set_detection(0x80, DTOS_CTRL_POWER);

	#elif defined(MXC_3D)
	MXC_3D_Power_Down();
	#endif

#endif //MXC_SENSOR_AUTO_DETECT
#if defined(__MEMSIC_HW_IIC__)
	Memsic_Close_i2c();
#endif
}

/*
* FUNCTION                                                            
*	acc_sensor_get_5bytes
*
* DESCRIPTION                                                           
*   	This function is to read data measured by the acc sensor
*
* CALLS  
*
* PARAMETERS
*  	acc_x_adc
*	pointer to caller's buffer to return acc data of X-axis
*	acc_y_adc
*	pointer to caller's buffer to return acc data of Y-axis
*	acc_z_adc
*	pointer to caller's buffer to return acc data of Z-axis
*	
* RETURNS
*	None
*/    
void acc_sensor_get_5bytesx(kal_uint16 *acc_x_adc, kal_uint16 *acc_y_adc,kal_uint16 *acc_z_adc)
{

	 kal_int16 x,y,z;
	//acc_sensor_pwr_up();
	//memsic_acc_i2c_delay_loop(200);
#ifdef MXC_SENSOR_AUTO_DETECT

	switch (mxc_sensor_category)
	{
	case MXC_SENSOR_2D_XVMP:
		XVMP_get_data(acc_x_adc, acc_y_adc);
		break;
	case MXC_SENSOR_2D_DTOS:
		DTOS_get_data(acc_x_adc, acc_y_adc);
		break;
	}

#else

	#if defined(MXC_2D_MP)

	XVMP_get_data(acc_x_adc, acc_y_adc);

	#elif defined(MXC_2D_DTOS)

	DTOS_get_data(acc_x_adc, acc_y_adc);
	#elif defined(MXC_3D)

	MXC_3D_get_data(acc_x_adc, acc_y_adc, acc_z_adc);
	
	#endif

#endif //MXC_SENSOR_AUTO_DETECT

        x= *acc_x_adc ;
        y=*acc_y_adc;
		#if defined(MXC_3D)
		z=*acc_z_adc;
		#endif
	//180
	//*acc_x_adc= 2*ACC_0G_X-x;
	//*acc_y_adc= 2*ACC_0G_Y-y;
#define MOTION_SENSOR_BACK_0	
//#define MOTION_SENSOR_BACK_0
//#define MOTION_SENSOR_BACK_270

#if defined(MOTION_SENSOR_BACK_0)	
	*acc_x_adc= x;
	*acc_y_adc= y;
#if defined(MXC_3D)
	*acc_z_adc= z;
#endif
#elif defined(MOTION_SENSOR_BACK_90)
	*acc_x_adc= y;
	*acc_y_adc= 2*ACC_0G_X-x;
#elif defined(MOTION_SENSOR_BACK_180)
	*acc_x_adc= 2*ACC_0G_X-x;
	*acc_y_adc= 2*ACC_0G_Y-y;
#elif defined(MOTION_SENSOR_BACK_270)
	*acc_x_adc= 2*ACC_0G_Y-y;
	*acc_y_adc= x;
#elif defined(MOTION_SENSOR_FRONT_0)
	*acc_x_adc= 2*ACC_0G_X-x;
	*acc_y_adc= y;
#elif defined(MOTION_SENSOR_FRONT_90)
	*acc_x_adc= 2*ACC_0G_Y-y;
	*acc_y_adc= 2*ACC_0G_X-x;
#elif defined(MOTION_SENSOR_FRONT_180)
	*acc_x_adc= x;
	*acc_y_adc= 2*ACC_0G_Y-y;
#elif defined(MOTION_SENSOR_FRONT_270)
	*acc_x_adc= y;
	*acc_y_adc= x;
#endif

       // *acc_x_adc = y;
	//*acc_y_adc= 2*ACC_0G_X-x;


   // kal_prompt_trace(MOD_CC,"----MXC6225----acc_sensor_get_5bytes--- *acc_x_adc=%d ------------------", *acc_x_adc);
  //   kal_prompt_trace(MOD_CC,"----MXC6225----acc_sensor_get_5bytes--- *acc_y_adc=%d ------------------", *acc_y_adc);
	#if !defined(MXC_3D)
	*acc_z_adc = 2048;
	#endif
	//acc_sensor_pwr_down();
}
#define MAX_AND_MIN(_max, _min, _data) {\
	if(_data < _min)	\
		_min = _data;	\
	if(_data > _max)\
		_max = _data;}
	
void sn_falldown_get_acc_data(kal_uint16 *x, kal_uint16 *y, kal_uint16 *z)
{
	kal_uint16 i = 0;
	kal_uint16 x_max = 0, x_min, y_max = 0, y_min, x_sum = 0, y_sum = 0;
	kal_uint16 z_max = 0, z_min = 0, z_sum = 0;
	kal_uint16 _x, _y, _z;
#if 0
	acc_sensor_get_5bytesx(x, y, &_z);
#else
	for(i = 0; i < 7; i++)
	{
		acc_sensor_get_5bytesx(&_x, &_y, &_z);
		x_sum += _x;
		y_sum += _y;
		z_sum += _z;
		
		if(i == 0)
		{
			x_min = _x;
			y_min = _y;
			z_min = _z;
		}
		MAX_AND_MIN(x_max, x_min, _x);
		MAX_AND_MIN(y_max, y_min, _y);
		MAX_AND_MIN(z_max, z_min, _z);
	}
	x_sum = x_sum - (x_max + x_min);
	y_sum = y_sum - (y_max + y_min);
	z_sum = z_sum - (z_max + z_min);
	*x = x_sum/5;
	*y = y_sum/5;
	*z = z_sum/5;
#endif	
}
/*
* FUNCTION                                                            
*	acc_sensor_init
*
* DESCRIPTION                                                           
*   	This function is to initialize I2C bus and acc sensor
*
* CALLS  
*
* PARAMETERS
*  None
*	
* RETURNS
*	None
*/    
extern const kal_uint8 MOTION_SENSOR_EINT_NO;
void memsic_sensor_read_statue(kal_uint8 *statue)
{
	kal_uint8 data;
	kal_uint8 ack;
	#if defined(__MEMSIC_HW_IIC__)
	Memsic_I2C_read(MEMSIC_ACC_SLAVE_ADDR, 0x02, &data, 1);
	#else
	memsic_acc_i2c_start();
	//send slave address with WRITE
	memsic_acc_i2c_write(MEMSIC_ACC_SLAVE_ADDR);
	memsic_acc_i2c_slave_ack(ack);
	
	//sub-address
	memsic_acc_i2c_write(0x02);
	memsic_acc_i2c_slave_ack(ack);
	//bus restart
	memsic_acc_i2c_start();
	//send slave address with READ
	memsic_acc_i2c_write(MEMSIC_ACC_SLAVE_ADDR+1);
	
	memsic_acc_i2c_slave_ack(ack);
	
	memsic_acc_i2c_read(data);
	//bus stop
	memsic_acc_i2c_stop();
	#endif
	*statue = data;
}
void memsic_sensor_eint_hisr()
{
	ilm_struct           *clam_ilm;
	aux_id_struct        *aux_id_data;
	kal_uint32 savedMask;
	kal_uint8 statue;
	//savedMask = SaveAndSetIRQMask();
	memsic_sensor_read_statue(&SnesorStatue);
	//SnesorStatue = statue;
	aux_id_data = (aux_id_struct*)
		   construct_local_para(sizeof(aux_id_struct), TD_CTRL);

	aux_id_data->aux_id = AUX_ID_TVOUT;     

	DRV_BuildPrimitive(clam_ilm,
	                MOD_EINT_HISR,
	                MOD_UEM,
	                MSG_ID_AUX_ID,
	                aux_id_data);
	//if(FallDownEintCallBack)
	//	FallDownEintCallBack();
	msg_send_ext_queue(clam_ilm);
	//RestoreIRQMask(savedMask);
	senseor_enit_statue = !senseor_enit_statue;
	EINT_Set_Polarity(MOTION_SENSOR_EINT_NO,senseor_enit_statue);
	kal_prompt_trace(MOD_ENG, "memsic_sensor_eint_hisr:%x", SnesorStatue);
}
kal_uint8 memsic_sensor_get_eint_data()
{
	return SnesorStatue;
}
void acc_sensor_init(void)
{
	static kal_uint8 isInit = 0;
	if(isInit)
		return;
	isInit = 1;

	#if defined(__MEMSIC_HW_IIC__)
	//memsic_open_i2c();
	#else
	/* Initialize GPIO */
	GPIO_ModeSetup(ACC_SENSOR_SCK, 0x00);

	ACC_SET_I2C_CLK_OUTPUT;
	ACC_SET_I2C_CLK_HIGH;
 
	GPIO_ModeSetup(ACC_SENSOR_SDA, 0x00);
	ACC_SET_I2C_DATA_OUTPUT;
	ACC_SET_I2C_DATA_HIGH;
	#endif
#ifdef MXC_SENSOR_AUTO_DETECT
	//auto-detect mxc sensor on board
	mxc_sensor_category = mxc_sensor_auto_detect();
#endif //MXC_SENSOR_AUTO_DETECT

	acc_sensor_pwr_down();

	//EINT_Registration(MOTION_SENSOR_EINT_NO, KAL_TRUE, 
	//       (kal_bool)senseor_enit_statue,memsic_sensor_eint_hisr, KAL_TRUE);    
	
	//EINT_SW_Debounce_Modify(MOTION_SENSOR_EINT_NO, 10);
	
	//EINT_Mask(MOTION_SENSOR_EINT_NO);
}

/*
* FUNCTION
*	ms_GetFunc
*
* DESCRIPTION
*   	This function is to enable to customization function pointer
*
* CALLS
*
* PARAMETERS
*	None
*
* RETURNS
*	function pointer
*/
//MotionSensor_customize_function_struct *ms_GetFunc(void)
//{
//	return (&ms_custom_func);
//}

/*
* FUNCTION
*	ms_get_data
*
* DESCRIPTION
*   	This function is to initialize I2C bus and acc sensor
*
* CALLS
*
* PARAMETERS
*  None
*
* RETURNS
*	None
*/
/*MotionSensor_custom_data_struct* ms_get_data(void)
{
	return (&ms_custom_data_def);
}*/




