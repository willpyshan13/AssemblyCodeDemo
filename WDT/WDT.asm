#include <mc30p011.inc>
 org		0x3ff
 goto		start        
 org		00h
 goto		start
 
start:
 clrr		P0
 movai		0x00
 movra		DDR0
 movai		0x0A
 movra		T0CR;WDT4·ÖÆµ,288ms*4=1152ms
 movai		0xff
 movra		P0
 bset		WDTEN
 goto		$
 end