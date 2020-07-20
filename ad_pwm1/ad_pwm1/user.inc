;==========================================
;********user ram********************
cblock                  0x00
ACCBUF       
PFLAGBUF  
;***********************************   
FLAG1   
r0              
r1                 
r2                
r3                 
r4                
r5                 
r6                 
r7
Filter_new                     ;新采样值
Filter_old                     ;上次采样值
Filter_temp       
Filter_const                   ;
Filter_adp                     ;
Filter_flag                    ;
   
endc
;************************************
#define       tm0flag           FLAG1,0
;============================================================
#define       directionflag     FLAG1,1          ;0=dec,1=inc
;---------------------------------------------
#define       filter_adp_max    5                ;消抖计数器最大值
#define       filter_1st_incr   5                
#define       filter_1st_max    250              
#define       THRESHOLD         5                ;变化阀值
                
;==============================================================
;********user io*********************
;************************************