;*********************************
;程序功能：
;作者：
;创建时间：
;版本：
;*********************************
#include "mc33p116.inc"
#include "macro.inc"
#include "IntISR.asm"
#include "TestFun.asm"
;---------------------------------
;常量定义
;---------------------------------
#define SYS_HIGH_SPEED 0x1
#define SYS_LOW_SPEED 0x2
#define SYS_SLEEP 0x3
#define SYS_HOLD1 0x4
#define SYS_HOLD2 0x5

;------- _SysFlag bit位定义 -------
#define FLAG_SYS_TIME_1MS 0

;-------------按键---------------
#define KEY_PORT_P0N 0x1F         ;\  按键口定义
#define KEY_PORT_P0N_CNT 0x5      ;/  按键口个数，要与按键口定义对应
#define KEY_SUM (1+KEY_PORT_P0N_CNT)*KEY_PORT_P0N_CNT/2
#define KEY_DBC_CNT 0x01
#define KEY_LONG_CNT 0xF0
#define KEY_GND_MASK 0x7C             ;GND 按键状态在"KeyStatBufTemp+1" 中所占的bit

;------- _IRFlag bit 位定义 -------
#define FLAG_IR_SEND_CODE_START 7
#define FLAG_IR_SENDING_CODE_D 0        ; 起始码标志位

;------- IR 常量定义 ----------
#define CODE_S_CAR_CNT_H 0x00           ;\ 起始码高电平
#define CODE_S_CAR_CNT_L 0xA7           ;/
#define CODE_S_NO_CAR_CNT_H 0x00        ;\ 起始码低电平,4470us
#define CODE_S_NO_CAR_CNT_L 0xAA        ;/

#define CODE_D_0_CAR_CNT_H 0x00         ; 数据码 "0"
#define CODE_D_0_CAR_CNT_L 0x17
#define CODE_D_0_NO_CAR_CNT_H 0x00
#define CODE_D_0_NO_CAR_CNT_L 0x12

#define CODE_D_1_CAR_CNT_H 0x00         ; 数据码 "1"
#define CODE_D_1_CAR_CNT_L 0x17   
#define CODE_D_1_NO_CAR_CNT_H 0x00
#define CODE_D_1_NO_CAR_CNT_L 0x3C

#define CODE_C_CAR_CNT_H 0x00           ; 连接码
#define CODE_C_CAR_CNT_L 0x18
#define CODE_C_NO_CAR_CNT_H 0x03
#define CODE_C_NO_CAR_CNT_L 0x20

#define CODE_P_CAR_CNT_H 0x00            ; 结束码
#define CODE_P_CAR_CNT_L 0x17
#define CODE_P_NO_CAR_CNT_H 0x00
#define CODE_P_NO_CAR_CNT_L 0xC5


#define CODE_D_BIT_PART1_CNT 0x30   ; 连接码之前的数据码 bit 数
#define CODE_D_BIT_SUM_CNT 0x30     ; 全部数据码bit 数

;-------- UserFlag bit 位定义 -----
#define FLAG_TIME_1MS 0


;-------- KeyFlag bit 位定义 ------
#define FLAG_SCAN_GND_KEY_DOWN 0    ; 扫描GND时，扫描到按键按下则置1，否则置0
#define FLAG_SCAN_GND 1             ; 扫描GND时置1，否则置0

;-------- 遥控码定义 ---------
#define CODE_TEMP_INDEX_BASE 0           ; 温度遥控码索引起始值
#define CODE_MODE_INDEX_BASE 1           ; 模式遥控码索引起始值


;---------------------------------
;变量定义
;---------------------------------
cblock 0x00

;----- SYS define -----
    _AccTemp           ; 中断专用
    _StatusTemp        ; 中断专用
    _WorkMode          ; 记录系统运行的模式
    _IntReg            ; 中断专用
    _ParaBuf:4         ; 存放函数参数及返回值
    _ParaCnt           ; 存放参数及返回值个数
    _R0                ; 通用寄存器,函数或宏中使用
    _R1                ; 通用寄存器,函数或宏中使用
    _R2                ; 通用寄存器,函数或宏中使用
    _R3                ; 通用寄存器,函数或宏中使用
    _SysFlag  
    _IRFlag
    _IRSendState       ; 记录发码阶段
    _IRSendCodeBuf:10  ; 红外码发送 buffer
    _IRCarCnt:4        ; 发码时计数载波周期，高2字节记录载波时间，低2字节记录无载波时间
    _IRBitCnt         
;--- Scan Key define---

    KeyBufTemp:2       ; 记录按键端口状态
    KeyBuf:2
    KeyStatBufTemp:2     
    KeyFlag
    KeyChange:2        ; 记录按键状态变化
    TempCnt
    
    RowScanBit
    ColScanBit
    DBCCnt

;---- user define -----    
    R0
    R1
    R2
    
    UserFlag
    CurTemp                  ; 温度
    CurMode    
endc

;---------------------------------
;外部中断0
;---------------------------------     
EXT_INT0:
    bclr INTF,2         ; 清 外部中断0 标志

    goto INT_EXIT
;---------------------------------
;外部中断1
;--------------------------------- 
EXT_INT1:
    bclr INTF,3         ;清 外部中断1 标志

    goto INT_EXIT
;---------------------------------
;Timer0 中断
;--------------------------------- 
T0_INT:
    bclr INTF,0         ;清 T0 中断标志
    bset _SysFlag,FLAG_SYS_TIME_1MS
              
    goto INT_EXIT
;---------------------------------
;Timer1 中断
;--------------------------------- 
T1_INT:                 ;每中断1次，说明1个载波周期完毕。通过载波周期个数来计算时间。
    bclr INTF,1         ;清 T1 中断标志      

    goto INT_EXIT
;---------------------------------
;T0RF 中断
;--------------------------------- 
T0RF_INT: 
    bclr INTF,6         ; 清 T0RF 中断标志

    goto INT_EXIT
    
;---------------------------------
;程序开始
;--------------------------------- 
START:  
    NOP
    NOP

MAIN:
    call FunTest1
    call FunTest2
    call FunTest3
    call FunTest4
    call FunTest5
    call FunTest6
    call FunTest7
    call FunTest8
    
    goto MAIN
        






    end

 
 




        

     