;��ʱ����ʹ�ã�
#include <mc30p011.inc>
;
cblock  0x10
acctemp			;��ʾ0x10��ַ����ͬ�� acctemp     equ		0x10
statustemp		;��ʾ0x11��ַ����ͬ�� statustemp  equ	0x11
endc

 org  0x3ff
 goto start        
 org  00h
 goto start        
 org  08h      	
timer0int: movra  acctemp
       	   swapar STATUS
       	   movra  statustemp
      	   bclr   T0IF
           movai  6
           movra  T0CNT
           comr	  P1
        
timer0exit: swapar statustemp
            movra  STATUS
       	    swapr  acctemp
       	    swapar acctemp
            retie
            
start:
;========���0x10��0x3F��ͨ�üĴ������������=======
          movai       0x3f
          movra       FSR
          movai       47
          movra       GPR
          decr        FSR
          clrr        INDF
          djzr        GPR
          goto        $-3
          clrr        INDF
          clrr        GPR
;=============I/O====================== 
		  clrr		P1
   		movai		  0x00
   		  movra		DDR1
;==============timer===================
  		   movai		  6
  		  movra		  T0CNT
   		  movai		0x07
   		  movra		  T0CR
;==============���ж�=====================
		  bset		  GIE		;�����ж�
		  bset		T0IE   	;����ʱ���ж�
main:
   		  goto		$			;һֱ�ڴ�ѭ�����൱�ڳ�ʼ�����֮�󣬾�ͣ������
   end