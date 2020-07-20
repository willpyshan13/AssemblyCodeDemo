;4M,4T
#include <mc30p011.inc>

 org		0x3ff
 goto		start        
 org		00h
 goto		start 

start:
 movai		0x00
 movra		DDR1;P12一定要设置为输出
 movai		0xC0;110 00 000,开T1和PWM，Fcpu，1分频
 movra		T1CR
 
 movai		199;199+1
 movra		T1LOAD
 movai		100
 movra		T1DATA
 
 goto		$
 end