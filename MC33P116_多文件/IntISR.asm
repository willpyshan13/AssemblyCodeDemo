
;---------------------------------
;复位向量
;---------------------------------
    org 0x0
    clrwdt
    goto    START
;---------------------------------
;中断向量
;---------------------------------   
    org 0x8
INT:
    movra   _AccTemp         ;save the ACC status
    swapar  STATUS              ;save the CPU status
    movra   _StatusTemp 

    movar INTE
    andar INTF
    movra _IntReg

    jbclr _IntReg,0
    goto T0_INT
    jbclr _IntReg,1
    goto T1_INT
    jbclr _IntReg,2
    goto EXT_INT0
    jbclr _IntReg,3
    goto EXT_INT1

INT_EXIT:        
    swapar  _StatusTemp
    movra   STATUS
    swapr   _AccTemp
    swapar  _AccTemp 
    retie    

    

 
 




        

     