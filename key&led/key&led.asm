;====P00ΪOUT,P10ΪIN===
#include <mc30p011.inc>
#define		led		P0,0
#define		key		P1,0

 org	0x03ff
 goto	start	
 org	0x00
 goto	start

start:
 	clrr	P0
    clrr	P1			;��P0��P1��
  	movai		0x00			
    movra	DDR0		;����P0�ڵĶ˿ڷ���
    movai	0x01
    movra	DDR1		;����P1�ڵĶ˿ڷ���
    movai	0xfe
    movra	PUCON		;������������
check:
    jbclr	key			;����ֻ�Ǽ򵥵��жϰ�����û�а��£�δ��������
    goto	close
    goto	open
close:    
    bclr	led
    goto	check
open:
 	bset	led
	goto	check
	end	