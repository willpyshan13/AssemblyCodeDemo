#include     "mc32p21.inc"
#include     "user.inc"

        org                 00h
        bclr                GIE
        goto                start
        org                 08h
intter:
        movra               ACCBUF
        swapar              STATUS
        movra               PFLAGBUF        
        ;**************************************        
        bclr                T0IF
        
        ;**************************************
interrexit:        
        swapar              PFLAGBUF       
        movra               STATUS
        swapr               ACCBUF
        swapar              ACCBUF
        retie                       
start:  
        ;============io======================
        clrr               OSCM
        movai              0
        movra              OEP0
        movai              0xff
        movra              PUP0
        ;====================================
        movai              0x08
        movra              OEP1                        
        ;====================================
        movai              0
        movra              T0CR
        movai              250
        movra              T0LOAD
        ;=====================================
        movai              0x43
        movra              T1CR
        movai              255
        movra              T1LOAD
        movai              0
        movra              T1DATA
        ;======================================
        movai           0x20
        movra           ANSEL
        movai           01010010b
        movra           ADCR0  
        movai           0x03
        movra           ADCR1      
        ;*********clr  ram**************00-7f
        movai  		0x07f
        movra  		FSR0
        clrr   		INDF0
        djzr   		FSR0
        goto   		$-2
        clrr   		INDF0       
        bset            ADON 
        bset            TC1EN
        ;=================================                 
main:
        clrwdt
        call            get_ad
        movar           ADRH
        movra           Filter_new
        call            filter            
        movai           10
        rsubar          Filter_old
        jbclr           C
        goto            mainloop            
        movai           0
        movra           T1DATA
        goto            main 
mainloop:
        movar           Filter_old
        movra           T1DATA        
        goto            main                 
;********************************************                      
;********user  function**********************
;==========================================================
get_ad:

       bclr            ADEOC
       jbset           ADEOC
       goto            $-1
       return
;==========================================================
FUNCTION_MUL:
	movai	8
	movra	r2	
	clrr	r0
	clrr	r1
mul_loop:
	rrr	r3	
	jbset	C  
	goto	result_shift
	movar	r4
	addra	r1	
result_shift:	   	       	       	  			             
	rrr	r1	
	rrr	r0	
	djzr	r2
	goto	mul_loop
	return	 
;===============================================
FUNCTION_DIV:
        clrr	    r0	
        clrr	    r1
        clrr	    r2	
        movr	    r5
        jbclr	    Z
        return					         
        movai	    16
   	movra	    r6	
        movr	    r3
        jbset	    Z
        goto	    div_loop
        movr	    r4
	jbclr	    Z
	return					         
div_loop:
	bclr		C
	rlr		r4	
	rlr	        r3	
	rlr	        r2	
	rlr	        r7
	movar	        r5
	rsubar		 r2
	jbclr		C
	goto 		 updata_div
	jbclr	         r7,0
	goto		$+3
	bclr		C
	goto	        r0_shift
updata_div:	   	       	       	  				          
	movra		 r2
	bset	        C
r0_shift:
	rlr		r0
	rlr		r1
	djzr		r6
	goto		div_loop
	return         
;********************************************                           
filter:
          call                filterconst
          movar               Filter_old
          rsubar              Filter_new
          jbset               C
          goto                xiaoyu
          movra               r3
          movar               Filter_const
          movra               r4
          call                FUNCTION_MUL
          movar               r1
          addra               Filter_old
          return          
xiaoyu:          
          movar               Filter_new
          rsubar              Filter_old          
          ;(Filter_old-Filter_new)*Filter_const/256
          movra               r3
          movar               Filter_const
          movra               r4
          call                FUNCTION_MUL
          movar               r1
          rsubra              Filter_old
          return
;------------------------------------------------------------------
filterconst:
          movar               Filter_old
          rsubar              Filter_new     ;
          movra               Filter_temp
          jbclr               C
          goto                directionset
          ;-----Filter_new<Filter_old-------------
          jbset               directionflag
          goto                filterloop
          bclr                directionflag
          goto                noise           
directionset:;-----Filter_new>Filter_old-------------
          jbclr               directionflag
          goto                filterloop
          bset                directionflag
          goto                noise
filterloop:
          incr                Filter_adp
          isubai              THRESHOLD    ;
          jbclr               C
          goto                filterbijiao
          incr                Filter_adp
          incr                Filter_adp
filterbijiao:  
          movai               filter_adp_max
          rsubar              Filter_adp   
          jbset               C
          return
          clrr                Filter_adp
          movai               filter_1st_incr
          addra               Filter_const
          movai               filter_1st_max
          rsubar              Filter_const 
          jbset               C
          return
          movai               filter_1st_max
          movra               Filter_const
          return
noise:                
          clrr                Filter_adp 
          clrr                Filter_const
          return                
;********************************************
          end