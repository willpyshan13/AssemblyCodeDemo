M_DISGIE macro
    bclr MCR,7         ;关总中断
    endm
    
M_GIE macro
    bset MCR,7         ;开总中断
    endm    