;4M,4T
#include <mc30p011.inc>

 org		0x3ff
 goto		start        
 org		00h
 goto		start 

start:
 movai		0x00
 movra		DDR1;P12һ��Ҫ����Ϊ���
 movai		0xC0;110 00 000,��T1��PWM��Fcpu��1��Ƶ
 movra		T1CR
 
 movai		199;199+1
 movra		T1LOAD
 movai		100
 movra		T1DATA
 
 goto		$
 end