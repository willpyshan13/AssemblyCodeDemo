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
 movra		DDR0;P0ȫ�����
 movai		0x0a
 movra		P0
 movai		0xf7;1111 0111
 movra		DDR1;P13��������඼���롣��ΪP13û���ڲ���������ƽ״̬��ȷ��
 movai		0x00
 movra		PUCON
 movai		0xff
 movra		KBIM;P1�ھ���������ж�
 bset		KBIE;�������ж�
 bset		GIE;�����ж�
 goto		$
 end