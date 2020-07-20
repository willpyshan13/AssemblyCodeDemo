;====P00为OUT,P10为IN===
#include <mc30p011.inc>
#define		led		P0,0
#define		key		P1,0

 org	0x03ff
 goto	start	
 org	0x00
 goto	start

start:
 	clrr	P0
    clrr	P1			;清P0和P1口
  	movai		0x00			
    movra	DDR0		;设置P0口的端口方向
    movai	0x01
    movra	DDR1		;设置P1口的端口方向
    movai	0xfe
    movra	PUCON		;设置上拉电阻
check:
    jbclr	key			;这里只是简单的判断按键有没有按下，未进行消抖
    goto	close
    goto	open
close:    
    bclr	led
    goto	check
open:
 	bset	led
	goto	check
	end	