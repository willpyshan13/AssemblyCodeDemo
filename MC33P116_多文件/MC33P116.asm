;*********************************
;�����ܣ�
;���ߣ�
;����ʱ�䣺
;�汾��
;*********************************
#include "mc33p116.inc"
#include "macro.inc"
#include "IntISR.asm"
#include "TestFun.asm"
;---------------------------------
;��������
;---------------------------------
#define SYS_HIGH_SPEED 0x1
#define SYS_LOW_SPEED 0x2
#define SYS_SLEEP 0x3
#define SYS_HOLD1 0x4
#define SYS_HOLD2 0x5

;------- _SysFlag bitλ���� -------
#define FLAG_SYS_TIME_1MS 0

;-------------����---------------
#define KEY_PORT_P0N 0x1F         ;\  �����ڶ���
#define KEY_PORT_P0N_CNT 0x5      ;/  �����ڸ�����Ҫ�밴���ڶ����Ӧ
#define KEY_SUM (1+KEY_PORT_P0N_CNT)*KEY_PORT_P0N_CNT/2
#define KEY_DBC_CNT 0x01
#define KEY_LONG_CNT 0xF0
#define KEY_GND_MASK 0x7C             ;GND ����״̬��"KeyStatBufTemp+1" ����ռ��bit

;------- _IRFlag bit λ���� -------
#define FLAG_IR_SEND_CODE_START 7
#define FLAG_IR_SENDING_CODE_D 0        ; ��ʼ���־λ

;------- IR �������� ----------
#define CODE_S_CAR_CNT_H 0x00           ;\ ��ʼ��ߵ�ƽ
#define CODE_S_CAR_CNT_L 0xA7           ;/
#define CODE_S_NO_CAR_CNT_H 0x00        ;\ ��ʼ��͵�ƽ,4470us
#define CODE_S_NO_CAR_CNT_L 0xAA        ;/

#define CODE_D_0_CAR_CNT_H 0x00         ; ������ "0"
#define CODE_D_0_CAR_CNT_L 0x17
#define CODE_D_0_NO_CAR_CNT_H 0x00
#define CODE_D_0_NO_CAR_CNT_L 0x12

#define CODE_D_1_CAR_CNT_H 0x00         ; ������ "1"
#define CODE_D_1_CAR_CNT_L 0x17   
#define CODE_D_1_NO_CAR_CNT_H 0x00
#define CODE_D_1_NO_CAR_CNT_L 0x3C

#define CODE_C_CAR_CNT_H 0x00           ; ������
#define CODE_C_CAR_CNT_L 0x18
#define CODE_C_NO_CAR_CNT_H 0x03
#define CODE_C_NO_CAR_CNT_L 0x20

#define CODE_P_CAR_CNT_H 0x00            ; ������
#define CODE_P_CAR_CNT_L 0x17
#define CODE_P_NO_CAR_CNT_H 0x00
#define CODE_P_NO_CAR_CNT_L 0xC5


#define CODE_D_BIT_PART1_CNT 0x30   ; ������֮ǰ�������� bit ��
#define CODE_D_BIT_SUM_CNT 0x30     ; ȫ��������bit ��

;-------- UserFlag bit λ���� -----
#define FLAG_TIME_1MS 0


;-------- KeyFlag bit λ���� ------
#define FLAG_SCAN_GND_KEY_DOWN 0    ; ɨ��GNDʱ��ɨ�赽������������1��������0
#define FLAG_SCAN_GND 1             ; ɨ��GNDʱ��1��������0

;-------- ң���붨�� ---------
#define CODE_TEMP_INDEX_BASE 0           ; �¶�ң����������ʼֵ
#define CODE_MODE_INDEX_BASE 1           ; ģʽң����������ʼֵ


;---------------------------------
;��������
;---------------------------------
cblock 0x00

;----- SYS define -----
    _AccTemp           ; �ж�ר��
    _StatusTemp        ; �ж�ר��
    _WorkMode          ; ��¼ϵͳ���е�ģʽ
    _IntReg            ; �ж�ר��
    _ParaBuf:4         ; ��ź�������������ֵ
    _ParaCnt           ; ��Ų���������ֵ����
    _R0                ; ͨ�üĴ���,���������ʹ��
    _R1                ; ͨ�üĴ���,���������ʹ��
    _R2                ; ͨ�üĴ���,���������ʹ��
    _R3                ; ͨ�üĴ���,���������ʹ��
    _SysFlag  
    _IRFlag
    _IRSendState       ; ��¼����׶�
    _IRSendCodeBuf:10  ; �����뷢�� buffer
    _IRCarCnt:4        ; ����ʱ�����ز����ڣ���2�ֽڼ�¼�ز�ʱ�䣬��2�ֽڼ�¼���ز�ʱ��
    _IRBitCnt         
;--- Scan Key define---

    KeyBufTemp:2       ; ��¼�����˿�״̬
    KeyBuf:2
    KeyStatBufTemp:2     
    KeyFlag
    KeyChange:2        ; ��¼����״̬�仯
    TempCnt
    
    RowScanBit
    ColScanBit
    DBCCnt

;---- user define -----    
    R0
    R1
    R2
    
    UserFlag
    CurTemp                  ; �¶�
    CurMode    
endc

;---------------------------------
;�ⲿ�ж�0
;---------------------------------     
EXT_INT0:
    bclr INTF,2         ; �� �ⲿ�ж�0 ��־

    goto INT_EXIT
;---------------------------------
;�ⲿ�ж�1
;--------------------------------- 
EXT_INT1:
    bclr INTF,3         ;�� �ⲿ�ж�1 ��־

    goto INT_EXIT
;---------------------------------
;Timer0 �ж�
;--------------------------------- 
T0_INT:
    bclr INTF,0         ;�� T0 �жϱ�־
    bset _SysFlag,FLAG_SYS_TIME_1MS
              
    goto INT_EXIT
;---------------------------------
;Timer1 �ж�
;--------------------------------- 
T1_INT:                 ;ÿ�ж�1�Σ�˵��1���ز�������ϡ�ͨ���ز����ڸ���������ʱ�䡣
    bclr INTF,1         ;�� T1 �жϱ�־      

    goto INT_EXIT
;---------------------------------
;T0RF �ж�
;--------------------------------- 
T0RF_INT: 
    bclr INTF,6         ; �� T0RF �жϱ�־

    goto INT_EXIT
    
;---------------------------------
;����ʼ
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

 
 




        

     