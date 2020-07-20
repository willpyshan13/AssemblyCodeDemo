#ifndef FUNCTION_H
#define FUNCTION_H

void IOPortInit(void)
{
	OEP0 = 0;      
    OEP1 = 0xf7;      //P1,3设置为输入，其余P1口全为输出
    PUP1 = 0;         
    ANSEL0 = 0;
   	ANSEL1 = 0;         	
}
void IRQInit(void)
{
  	GIE = 1; 
    KBCR = bit1|bit2|bit3;     	       	
}

void RamInit(void)
{
  	RamInit:
    INDF0=0;
    ++FSR0;
    if (FSR0)
    {
        goto RamInit;
    }
}
void InitSub(void)
{
    RamInit();
    IOPortInit();
    IRQInit();     	  
}




#endif

