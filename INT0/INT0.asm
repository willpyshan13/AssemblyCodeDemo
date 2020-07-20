#include <mc30p011.inc>
cblock  10h
acctemp
statustemp
endc
 org		0x3ff
 goto		start        
 org		00h
 goto		start
 org		08h
INT0int: 
 movra		acctemp
 swapar		STATUS
 movra		statustemp
 bclr		INT0IF 
 comr		P0 
INT0exit: 
 swapar		statustemp
 movra		STATUS
 swapr		acctemp
 swapar		acctemp
 retie
 
start:
 movai		0x01;P10����Ϊ����
 movra		DDR1
 movai		0xFE;P10������
 movra		PUCON
 movai		0x00
 movra		DDR0;P0��Ϊ����ڣ�����LED
 movai		0x0a;0000 1010
 movra		P0
 bset		INT0M;�����ش���
 bset		GIE;�����ж�
 bset		INT0IE;�����ж�
 bset		EIS;�����ж�
 goto		$
 end 