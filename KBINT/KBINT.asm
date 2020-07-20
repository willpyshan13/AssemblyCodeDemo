#include <mc30p011.inc>
cblock		10h
acctemp
statustemp
endc
 org  0x3ff
 goto start        
 org  00h
 goto start 
 org  08h
KBint: 
 movra  	acctemp
 swapar 	STATUS
 movra  	statustemp
 bclr		KBIF
 comr		P0
 
KBexit: 
 swapar 	statustemp
 movra  	STATUS
 swapr  	acctemp
 swapar 	acctemp
 retie

start:
 movai		0x00
 movra		DDR0;P0全部输出
 movai		0x0a
 movra		P0
 movai		0xf7;1111 0111
 movra		DDR1;P13输出，其余都输入。因为P13没有内部上拉，电平状态不确定
 movai		0x00
 movra		PUCON
 movai		0xff
 movra		KBIM;P1口均允许键盘中断
 bset		KBIE;开键盘中断
 bset		GIE;开总中断
 goto		$
 end