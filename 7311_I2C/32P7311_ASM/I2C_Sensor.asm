
;  ******************************************************************************
;  * @file    I2C communication
;  * @author  YB
;  * @version V1.0
;  * @date    2016-11-27
;  * @brief   
;  ******************************************************************************
;  * @attention 
;  *   	 
;  *  platform:sinomcu MC30P6060  SOP8
;  *  web: www.sinimcu.com
;  *
;  ******************************************************************************

#include "mc32p7311.inc"


;---------------------------- I/O define -----------------------------
;IO-pin define
GPR   EQU   0x07

#define	I2C_SDA       IOP1,5   ;sda��scl  sensor i2c interface
#define	I2C_SCL       IOP1,6
;-------------------------constant define -------------------------
;Constant
;--------------------------variable define -------------------------
;Definition of variable

cblock     0x10
                  
   	acc_temp             ;���ACC��ֵ
   	status_temp          ;��� STATES��ֵ 
   	key_count1    
    time_base_1ms        ;����ʱ�������
    time_base_30ms
   	time_base_100ms
    time_base_10ms                         	                       	
   	KeyFlag              ;������־λ�Ĵ���                        
   	address              ;�ӻ�������ַ
   	write_value          ;д��24C02�����ֵ
   	read_value           ;��24C02���ص���ֵ
   	responsnum           ;Ӧ��ȴ�ʱ��
   	data                 ;���ݻ����������ݵĴ��ͣ�
   	temp                 ;�����ݴ��������ݵı�����
   	w8num                ;д8λ��һ���ֽڣ���ѭ������
   	r8num                ;��8λ��һ���ֽڣ���ѭ������
   	read_temp            ;���ص���ֵ���ݴ�
   	delay_num            ;��ʱѭ������
   	read_back            ;��������ֵ�������ڡ��۲촰���п���ֵ                                                                                               

   	Array:124
   	_status
   	Xout_M
   	Xout_L
   	Yout_M
   	Yout_L
   	ArrayCnt
   	R1
   	R2
   	R3
   	R7
   	R8
   	R9
   	RA
   	RB
   	RC
   	RD
   	RE
   	RF
  endc

;-------------------------KeyFlag  define -------------------------
;Flag bit

#define	F_tim_20ms    KeyFlag,0
#define	F_tim_500ms   KeyFlag,1

;++++++++++++++++++++++++
;ROM��
;++++++++++++++++++++++++

   	ORG	   	0x3ff 
    bclr   	GIE
   	ORG	   	0x00
   	goto    START

;/************************************************
;  * @brief          IRQ
;  * @param      
;  * @retval
;  ***********************************************/
   	org	   	0x08      
                   
InterruptVector:

    movra   acc_temp                                       
    swapar  STATUS               
    movra   status_temp                                     
            
TIM0_IRQ: 
                                                                                                                                           
    jbset   T0IF                          
    goto    ExitInterrupt
   	bclr    T0IF 
                                                                                
ExitInterrupt:

    swapar  status_temp                               
    movra   STATUS                                       
    swapr   acc_temp
    swapar  acc_temp
    movar   acc_temp
    retie

START:   
   	bclr   	GIE
    call    IOPortInit
    call    RamInit
    call    SysInit
   	clrr   	ArrayCnt 
    bset    GIE

MAIN:            
    call    WriteValue
   	nop  
   	call    ReadValue 
   	call   	DataStorage        	                                              
    goto    MAIN     
            
ReadValue:
    bclr    GIE
    call    read_add
    bset    GIE
    return

DataStorage:

   	movai  	0x0a ;125
   	rsubar 	ArrayCnt
   	jbclr  	C
   	return
   	movar  	ArrayCnt
   	addai  	(Array+0)
   	movra  	R1
   	movai  	high(Array+0)
   	jbclr  	C
   	addai  	0x01
   	movra  	R2
   	movar  	R1
   	movra  	FSR0
   	
   	movai  	0
   	xorar  	R3
   	jbclr  	Z
   	goto   	Data_0
   	movai  	1
   	xorar  	R3
   	jbclr  	Z
   	goto   	Data_1
   	movai  	2
   	xorar  	R3
   	jbclr  	Z
   	goto   	Data_2
   	movai  	3
   	xorar  	R3
   	jbclr  	Z
   	goto   	Data_3
   	movai  	4
   	xorar  	R3
   	jbclr  	Z
   	goto   	Data_4
   	return

Data_0:
   	movar  	_status
   	movra  	INDF0
   	incr   	ArrayCnt
   	incr   	R3
   	goto   	DataStorage    	

Data_1:
   ;   	movar  	Xout_M
   	movai  	1
   	movra  	INDF0
   	incr   	ArrayCnt
   	incr   	R3
   	goto   	DataStorage

Data_2:
   	;movar     	Xout_L
   	movai  	2
   	movra  	INDF0
   	incr   	ArrayCnt
   	incr   	R3
   	goto   	DataStorage

Data_3:
   	;movar     	Yout_M
   	movai  	3
   	movra  	INDF0
   	incr   	ArrayCnt
   	incr   	R3
   	goto   	DataStorage 

Data_4:
   	;movar     	Yout_L
   	movai  	4
   	movra  	INDF0
   	incr   	ArrayCnt
   	clrr   	R3
   	return 


;/************************************************
;  * @brief   IOPortInit
;  * @param      
;  * @retval
;  ***********************************************/
IOPortInit:

   	clrr    OEP0      
    movai   0xf7          ;
    movra   OEP1          ;P1,3����Ϊ���룬����P1��ȫΪ���
    movai   0x00
    movra   PUP1
    movai   0x00          
    movra   ANSEL0
   	movra  	ANSEL1                               
    return
                   
;/************************************************
;  * @brief   RamInit
;  * @param      
;  * @retval
;  ***********************************************/ 
  
RamInit:
   	clrr   	FSR1   	       
   	movai  	0xff
   	movra  	FSR0
clrram_loop:
   	clrr   	INDF
   	djzr   	FSR0 
   	goto   	clrram_loop 
   	return
       
;/************************************************
;  * @brief   SysInit
;  * @param      
;  * @retval
;  ***********************************************/  

SysInit:

    movai  	0x02        ;Ԥ��Ƶ��T0����Ƶ��Ϊ8   
    movra   T0CR        ;250*2T/4M*8=1ms
    movai   6
    movra   T0CNT 
    bset    T0IE 
    movai   0x04
    return                        

;/************************************************
;  * @brief    WriteValue
;  * @param      
;  * @retval
;  ***********************************************/
    
WriteValue:
   	bclr    GIE
   	call    initSig
   	movai   0x0d
   	movra   address
   	movai  	0x00
   	movra   write_value         
   	call    write_add
   	call    delay1;�������д���ݣ�Ȼ���ٶ����ݣ������ʱһ������Ҫ�ģ�������ms����ʱ
   	call   	delay1
   	call   	delay1
   	bset    GIE                     
   	return 

;************************
;Function Name: ��24C02����д�ֽ�
;Description: ��ʼ�ź�֮����д������ַ+0����д24C02�ڴ洢��ַ��Ȼ��д�洢���ݣ����дֹͣ�ź�
;@register: 
;@param:          
;@param:     
;************************ 

write_add:
    call   	startSig
    movai   0xa0;1010 0000
    movra   data
    call    write_byte
    call    ackSig
    movar   address
    movra   data
    call    write_byte
    call    ackSig
    movar   write_value
    movra   data
    call    write_byte
    call    ackSig
    call    stopSig
   	nop
    return  

;************************
;Function Name: ��24C02������ֽ�
;Description: ��ʼ�ź�֮����д������ַ+0����д24C02�ڴ洢��ַ��Ȼ��д��ʼ�ź�
;             ��д������ַ+1���ٶ��ֽڣ����дֹͣ�ź�
;@register: 
;@param:          
;@param:     
;************************ 

read_add:
    call   	startSig
    movai   0x2a
    movra   data
    call    write_byte
    call    ackSig
    movai   0x02
    movra   address
    movar   address
    movra   data       	       	
    call    write_byte
    call    ackSig
    call    startSig
    movai   0x2b
    movra   data
    call    write_byte
    call    ackSig

    call    read_byte
    call    ackSig
    movar   read_temp
    movra   _status

    call    read_byte
    call    ackSig
    movar   read_temp
    movra   Xout_M

    call    read_byte
    call    ackSig
    movar   read_temp
    movra   Xout_L

    call    read_byte
    call    ackSig
    movar   read_temp
    movra   Yout_M

    call    read_byte
    ;call    ackSig
    movar   read_temp
    movra   Yout_L

    call    noackSig
    call    stopSig
   	nop 
    return                                                          
;/************************************************
;  * @brief    initSig
;  * @param      
;  * @retval
;  ***********************************************/ 
initSig:
    bset   	I2C_SDA
    call    delay
    bset    I2C_SCL
    call    delay
    return 
            
;************************
;Function Name: startSig
;Description: ��ʼ�ź�
;@register: 
;@param:          
;@param:     
;************************  
startSig:
    bset   	I2C_SDA
    call    delay
    bset    I2C_SCL
    call    delay
    bclr    I2C_SDA
    call    delay
    return
            
;************************
;Function Name: stopSig
;Description: ֹͣ�ź�
;@register: 
;@param:          
;@param:     
;************************  

stopSig:
    bclr    I2C_SDA
    call    delay
    bset    I2C_SCL
    call    delay
    bset    I2C_SDA
    call    delay
    return
            
;************************
;Function Name: ackSig
;Description: ֹͣ�ź�
;@register: 
;@param:          
;@param:     
;************************
ackSig:
    bclr   	I2C_SCL
    call    delay
    bclr    I2C_SDA
    call    delay
    bset    I2C_SCL
    call    delay
    bclr    I2C_SCL
    call    delay
    return
;************************
;Function Name: noackSig
;Description: ֹͣ�ź�
;@register: 
;@param:          
;@param:     
;************************
noackSig:
    bclr    I2C_SCL
    call    delay
    bset    I2C_SDA
    call    delay
    bset    I2C_SCL
    call    delay
    bclr    I2C_SCL
    call    delay
    return
             
;************************
;Function Name: responsSig
;Description: ;Ӧ���źţ����sda�ź�Ϊ�ͣ�ֱ��Ӧ�����sda�ź�Ϊ�ߣ�ѭ��һ��ʱ�䣬Ӧ��
;@register: 
;@param:          
;@param:     
;************************           

responsSig:
    bset   	I2C_SCL
    call    delay
responsCheck:
    jbset   I2C_SDA
    goto    responsOK
    incr    responsnum
    movai   250
    rsubar  responsnum
    jbset   C
    goto    responsCheck
responsOK:
    clrr    responsnum
    bclr    I2C_SCL
    call    delay
    return
            
;************************
;Function Name: write_byte
;Description: д�ֽ�
;@register: 
;@param:          
;@param:     
;************************  

write_byte:
    movar  	data
    movra   temp
w8begin:
    incr    w8num
    movai   9
    rsubar  w8num
    jbclr   C
    goto    w8end
    bclr    I2C_SCL
    call    delay
    rlr     temp
    jbclr   C
    goto    $+3
    bclr    I2C_SDA
    goto    $+2
    bset    I2C_SDA
    call    delay
    bset    I2C_SCL
    call    delay
    goto    w8begin    	
w8end:
    clrr    w8num
    bclr    I2C_SCL
    call    delay
    bset    I2C_SDA
    call    delay
    return
            
;************************
;Function Name: read_byte
;Description: ���ֽ���Ҫ�Ƚ�P15��sda�����ó����룬����֮��P15�����ó����
;@register: 
;@param:          
;@param:     
;************************  

read_byte:
    movai  	0xD7;
    movra   OEP1

    bclr   	I2C_SCL
    call    delay
    bset    I2C_SDA
    call    delay
r8begin: 
    incr    r8num
    movai   9
    rsubar  r8num
    jbclr   C
    goto    r8end
    bset    I2C_SCL
    call    delay
    jbset   I2C_SDA
    goto    $+2
    goto    $+3
    bclr    C
    goto    $+2
    bset    C
    rlr     read_temp
    bclr    I2C_SCL
    call    delay
    goto    r8begin
r8end:
    clrr    r8num
    ;movar   read_temp
    ;movra   read_value
    movai  	0xF7;
    movra   OEP1
    return
    

            
  

;************************
;Function Name: delay
;Description: us����ʱ
;@register: 
;@param:          
;@param:     
;************************             

delay:
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    NOP
    ;nop
    ;NOP
    ;nop
    nop
    nop
    nop
    return
    
;************************
;Function Name: delay1
;Description: ms����ʱ
;�������д���ݣ�Ȼ���ٶ����ݣ������ʱһ������Ҫ�ģ�������ms����ʱ
;�����ʱռ��CPU��Դ������ʹ�ö�ʱ����ע�ⶨʱ�жϵĿ�������
;@register: 
;@param:          
;@param:     
;************************     

delay1:
    movai  	255
    movra   delay_num
delay11:
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop 
 
    djzr   	delay_num
    goto    delay11
    return             	       	          
                   
   end