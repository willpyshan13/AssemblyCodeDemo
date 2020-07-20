#ifndef MC30P6230_H
#define MC30P6230_H

#include <mc32-common.h>

//
// Register addresses.
//
#define INDF_ADDR       	0x0000
#define T0CNT_ADDR      	0x0001
#define PCL_ADDR        	0x0002
#define STATUS_ADDR     	0x0003
#define FSR_ADDR        	0x0004
#define GPR0_ADDR       	0x0005
#define P1_ADDR         	0x0006
#define GPR1_ADDR       	0x0007
#define MCR_ADDR        	0x0008
#define KBIM_ADDR       	0x0009
#define PCLATH_ADDR     	0x000A
#define PDCON_ADDR      	0x000B
#define ODCON_ADDR      	0x000C
#define PUCON_ADDR      	0x000D
#define INTE_ADDR       	0x000E
#define INTF_ADDR       	0x000F
#define T0CR_ADDR       	0x0041
#define DDR1_ADDR       	0x0046
#define TM0CR_ADDR      	0x004B

//----- Register Files -----------------------------------------------------

extern __sfr __at (INDF_ADDR)     	INDF;
extern __sfr __at (T0CNT_ADDR)    	T0CNT;
extern __sfr __at (PCL_ADDR)      	PCL;
extern __sfr __at (STATUS_ADDR)   	STATUS;
extern __sfr __at (FSR_ADDR)      	FSR;
extern __sfr __at (GPR0_ADDR)     	GPR0;
extern __sfr __at (P1_ADDR)       	P1;
extern __sfr __at (GPR1_ADDR)     	GPR1;
extern __sfr __at (MCR_ADDR)      	MCR;
extern __sfr __at (KBIM_ADDR)     	KBIM;
extern __sfr __at (PCLATH_ADDR)   	PCLATH;
extern __sfr __at (PDCON_ADDR)    	PDCON;
extern __sfr __at (ODCON_ADDR)    	ODCON;
extern __sfr __at (PUCON_ADDR)    	PUCON;
extern __sfr __at (INTE_ADDR)     	INTE;
extern __sfr __at (INTF_ADDR)     	INTF;
extern __sfr __at (T0CR_ADDR)     	T0CR;
extern __sfr __at (DDR1_ADDR)     	DDR1;
extern __sfr __at (TM0CR_ADDR)    	TM0CR;

//==========================================================================
//
//	Configuration Bits
//
//==========================================================================

//OPBIT1

//OPBIT0

// ----- INDF Bits --------------------------------------------
typedef union {
	 struct {
		unsigned char INDF0:1;
		unsigned char INDF1:1;
		unsigned char INDF2:1;
		unsigned char INDF3:1;
		unsigned char INDF4:1;
		unsigned char INDF5:1;
		unsigned char INDF6:1;
		unsigned char INDF7:1;
	};
} __INDFbits_t;
extern volatile __INDFbits_t __at(INDF_ADDR) INDFbits;

#define INDF0     	INDFbits.INDF0      	/* bit 0 */
#define INDF1     	INDFbits.INDF1      	/* bit 1 */
#define INDF2     	INDFbits.INDF2      	/* bit 2 */
#define INDF3     	INDFbits.INDF3      	/* bit 3 */
#define INDF4     	INDFbits.INDF4      	/* bit 4 */
#define INDF5     	INDFbits.INDF5      	/* bit 5 */
#define INDF6     	INDFbits.INDF6      	/* bit 6 */
#define INDF7     	INDFbits.INDF7      	/* bit 7 */

// ----- T0CNT Bits --------------------------------------------
typedef union {
	 struct {
		unsigned char T0CNT0:1;
		unsigned char T0CNT1:1;
		unsigned char T0CNT2:1;
		unsigned char T0CNT3:1;
		unsigned char T0CNT4:1;
		unsigned char T0CNT5:1;
		unsigned char T0CNT6:1;
		unsigned char T0CNT7:1;
	};
} __T0CNTbits_t;
extern volatile __T0CNTbits_t __at(T0CNT_ADDR) T0CNTbits;

#define T0CNT0    	T0CNTbits.T0CNT0    	/* bit 0 */
#define T0CNT1    	T0CNTbits.T0CNT1    	/* bit 1 */
#define T0CNT2    	T0CNTbits.T0CNT2    	/* bit 2 */
#define T0CNT3    	T0CNTbits.T0CNT3    	/* bit 3 */
#define T0CNT4    	T0CNTbits.T0CNT4    	/* bit 4 */
#define T0CNT5    	T0CNTbits.T0CNT5    	/* bit 5 */
#define T0CNT6    	T0CNTbits.T0CNT6    	/* bit 6 */
#define T0CNT7    	T0CNTbits.T0CNT7    	/* bit 7 */

// ----- PCL Bits --------------------------------------------
typedef union {
	 struct {
		unsigned char PC0:1;
		unsigned char PC1:1;
		unsigned char PC2:1;
		unsigned char PC3:1;
		unsigned char PC4:1;
		unsigned char PC5:1;
		unsigned char PC6:1;
		unsigned char PC7:1;
	};
} __PCLbits_t;
extern volatile __PCLbits_t __at(PCL_ADDR) PCLbits;

#define PC0       	PCLbits.PC0         	/* bit 0 */
#define PC1       	PCLbits.PC1         	/* bit 1 */
#define PC2       	PCLbits.PC2         	/* bit 2 */
#define PC3       	PCLbits.PC3         	/* bit 3 */
#define PC4       	PCLbits.PC4         	/* bit 4 */
#define PC5       	PCLbits.PC5         	/* bit 5 */
#define PC6       	PCLbits.PC6         	/* bit 6 */
#define PC7       	PCLbits.PC7         	/* bit 7 */

// ----- STATUS Bits --------------------------------------------
typedef union {
	 struct {
		unsigned char C:1;
		unsigned char DC:1;
		unsigned char Z:1;
		unsigned char PD:1;
		unsigned char TO:1;
		unsigned char :1;
		unsigned char :1;
		unsigned char RST:1;
	};
} __STATUSbits_t;
extern volatile __STATUSbits_t __at(STATUS_ADDR) STATUSbits;

#define C         	STATUSbits.C        	/* bit 0 */
#define DC        	STATUSbits.DC       	/* bit 1 */
#define Z         	STATUSbits.Z        	/* bit 2 */
#define PD        	STATUSbits.PD       	/* bit 3 */
#define TO        	STATUSbits.TO       	/* bit 4 */
#define RST       	STATUSbits.RST      	/* bit 7 */

// ----- FSR Bits --------------------------------------------
typedef union {
	 struct {
		unsigned char FSR0:1;
		unsigned char FSR1:1;
		unsigned char FSR2:1;
		unsigned char FSR3:1;
		unsigned char FSR4:1;
		unsigned char FSR5:1;
		unsigned char :1;
		unsigned char :1;
	};
} __FSRbits_t;
extern volatile __FSRbits_t __at(FSR_ADDR) FSRbits;

#define FSR0      	FSRbits.FSR0        	/* bit 0 */
#define FSR1      	FSRbits.FSR1        	/* bit 1 */
#define FSR2      	FSRbits.FSR2        	/* bit 2 */
#define FSR3      	FSRbits.FSR3        	/* bit 3 */
#define FSR4      	FSRbits.FSR4        	/* bit 4 */
#define FSR5      	FSRbits.FSR5        	/* bit 5 */

// ----- P1 Bits --------------------------------------------
typedef union {
	 struct {
		unsigned char P10D:1;
		unsigned char P11D:1;
		unsigned char P12D:1;
		unsigned char P13D:1;
		unsigned char P14D:1;
		unsigned char P15D:1;
		unsigned char :1;
		unsigned char :1;
	};
} __P1bits_t;
extern volatile __P1bits_t __at(P1_ADDR) P1bits;

#define P10D      	P1bits.P10D         	/* bit 0 */
#define P11D      	P1bits.P11D         	/* bit 1 */
#define P12D      	P1bits.P12D         	/* bit 2 */
#define P13D      	P1bits.P13D         	/* bit 3 */
#define P14D      	P1bits.P14D         	/* bit 4 */
#define P15D      	P1bits.P15D         	/* bit 5 */

// ----- MCR Bits --------------------------------------------
typedef union {
	 struct {
		unsigned char :1;
		unsigned char :1;
		unsigned char :1;
		unsigned char :1;
		unsigned char :1;
		unsigned char :1;
		unsigned char EIS:1;
		unsigned char WDTEN:1;
	};
} __MCRbits_t;
extern volatile __MCRbits_t __at(MCR_ADDR) MCRbits;

#define EIS       	MCRbits.EIS         	/* bit 6 */
#define WDTEN     	MCRbits.WDTEN       	/* bit 7 */

// ----- KBIM Bits --------------------------------------------
typedef union {
	 struct {
		unsigned char KBIM0:1;
		unsigned char KBIM1:1;
		unsigned char KBIM2:1;
		unsigned char KBIM3:1;
		unsigned char KBIM4:1;
		unsigned char KBIM5:1;
		unsigned char :1;
		unsigned char :1;
	};
} __KBIMbits_t;
extern volatile __KBIMbits_t __at(KBIM_ADDR) KBIMbits;

#define KBIM0     	KBIMbits.KBIM0      	/* bit 0 */
#define KBIM1     	KBIMbits.KBIM1      	/* bit 1 */
#define KBIM2     	KBIMbits.KBIM2      	/* bit 2 */
#define KBIM3     	KBIMbits.KBIM3      	/* bit 3 */
#define KBIM4     	KBIMbits.KBIM4      	/* bit 4 */
#define KBIM5     	KBIMbits.KBIM5      	/* bit 5 */

// ----- PCLATH Bits --------------------------------------------
typedef union {
	 struct {
		unsigned char PCH0:1;
		unsigned char PCH1:1;
		unsigned char :1;
		unsigned char :1;
		unsigned char :1;
		unsigned char :1;
		unsigned char :1;
		unsigned char :1;
	};
} __PCLATHbits_t;
extern volatile __PCLATHbits_t __at(PCLATH_ADDR) PCLATHbits;

#define PCH0      	PCLATHbits.PCH0     	/* bit 0 */
#define PCH1      	PCLATHbits.PCH1     	/* bit 1 */

// ----- PDCON Bits --------------------------------------------
typedef union {
	 struct {
		unsigned char :1;
		unsigned char :1;
		unsigned char :1;
		unsigned char :1;
		unsigned char P10PD:1;
		unsigned char P11PD:1;
		unsigned char P12PD:1;
		unsigned char :1;
	};
} __PDCONbits_t;
extern volatile __PDCONbits_t __at(PDCON_ADDR) PDCONbits;

#define P10PD     	PDCONbits.P10PD     	/* bit 4 */
#define P11PD     	PDCONbits.P11PD     	/* bit 5 */
#define P12PD     	PDCONbits.P12PD     	/* bit 6 */

// ----- ODCON Bits --------------------------------------------
typedef union {
	 struct {
		unsigned char P10OD:1;
		unsigned char P11OD:1;
		unsigned char P12OD:1;
		unsigned char :1;
		unsigned char P14OD:1;
		unsigned char P15OD:1;
		unsigned char :1;
		unsigned char :1;
	};
} __ODCONbits_t;
extern volatile __ODCONbits_t __at(ODCON_ADDR) ODCONbits;

#define P10OD     	ODCONbits.P10OD     	/* bit 0 */
#define P11OD     	ODCONbits.P11OD     	/* bit 1 */
#define P12OD     	ODCONbits.P12OD     	/* bit 2 */
#define P14OD     	ODCONbits.P14OD     	/* bit 4 */
#define P15OD     	ODCONbits.P15OD     	/* bit 5 */

// ----- PUCON Bits --------------------------------------------
typedef union {
	 struct {
		unsigned char P10PU:1;
		unsigned char P11PU:1;
		unsigned char P12PU:1;
		unsigned char P13PU:1;
		unsigned char P14PU:1;
		unsigned char P15PU:1;
		unsigned char :1;
		unsigned char :1;
	};
} __PUCONbits_t;
extern volatile __PUCONbits_t __at(PUCON_ADDR) PUCONbits;

#define P10PU     	PUCONbits.P10PU     	/* bit 0 */
#define P11PU     	PUCONbits.P11PU     	/* bit 1 */
#define P12PU     	PUCONbits.P12PU     	/* bit 2 */
#define P13PU     	PUCONbits.P13PU     	/* bit 3 */
#define P14PU     	PUCONbits.P14PU     	/* bit 4 */
#define P15PU     	PUCONbits.P15PU     	/* bit 5 */

// ----- INTE Bits --------------------------------------------
typedef union {
	 struct {
		unsigned char T0IE:1;
		unsigned char KBIE:1;
		unsigned char INTIE:1;
		unsigned char :1;
		unsigned char :1;
		unsigned char :1;
		unsigned char :1;
		unsigned char GIE:1;
	};
} __INTEbits_t;
extern volatile __INTEbits_t __at(INTE_ADDR) INTEbits;

#define T0IE      	INTEbits.T0IE       	/* bit 0 */
#define KBIE      	INTEbits.KBIE       	/* bit 1 */
#define INTIE     	INTEbits.INTIE      	/* bit 2 */
#define GIE       	INTEbits.GIE        	/* bit 7 */

// ----- INTF Bits --------------------------------------------
typedef union {
	 struct {
		unsigned char T0IF:1;
		unsigned char KBIF:1;
		unsigned char INTIF:1;
		unsigned char :1;
		unsigned char :1;
		unsigned char :1;
		unsigned char :1;
		unsigned char :1;
	};
} __INTFbits_t;
extern volatile __INTFbits_t __at(INTF_ADDR) INTFbits;

#define T0IF      	INTFbits.T0IF       	/* bit 0 */
#define KBIF      	INTFbits.KBIF       	/* bit 1 */
#define INTIF     	INTFbits.INTIF      	/* bit 2 */

// ----- T0CR Bits --------------------------------------------
typedef union {
	 struct {
		unsigned char T0PRS0:1;
		unsigned char T0PRS1:1;
		unsigned char T0PRS2:1;
		unsigned char T0PTA:1;
		unsigned char T0SE:1;
		unsigned char T0PTS:1;
		unsigned char INTM:1;
		unsigned char :1;
	};
} __T0CRbits_t;
extern volatile __T0CRbits_t __at(T0CR_ADDR) T0CRbits;

#define T0PRS0    	T0CRbits.T0PRS0     	/* bit 0 */
#define T0PRS1    	T0CRbits.T0PRS1     	/* bit 1 */
#define T0PRS2    	T0CRbits.T0PRS2     	/* bit 2 */
#define T0PTA     	T0CRbits.T0PTA      	/* bit 3 */
#define T0SE      	T0CRbits.T0SE       	/* bit 4 */
#define T0PTS     	T0CRbits.T0PTS      	/* bit 5 */
#define INTM      	T0CRbits.INTM       	/* bit 6 */

// ----- DDR1 Bits --------------------------------------------
typedef union {
	 struct {
		unsigned char DDR10:1;
		unsigned char DDR11:1;
		unsigned char DDR12:1;
		unsigned char DDR13:1;
		unsigned char DDR14:1;
		unsigned char DDR15:1;
		unsigned char :1;
		unsigned char :1;
	};
} __DDR1bits_t;
extern volatile __DDR1bits_t __at(DDR1_ADDR) DDR1bits;

#define DDR10     	DDR1bits.DDR10      	/* bit 0 */
#define DDR11     	DDR1bits.DDR11      	/* bit 1 */
#define DDR12     	DDR1bits.DDR12      	/* bit 2 */
#define DDR13     	DDR1bits.DDR13      	/* bit 3 */
#define DDR14     	DDR1bits.DDR14      	/* bit 4 */
#define DDR15     	DDR1bits.DDR15      	/* bit 5 */

// ----- TM0CR Bits --------------------------------------------
typedef union {
	 struct {
		unsigned char :1;
		unsigned char :1;
		unsigned char :1;
		unsigned char :1;
		unsigned char :1;
		unsigned char :1;
		unsigned char T0TBS:1;
		unsigned char :1;
	};
} __TM0CRbits_t;
extern volatile __TM0CRbits_t __at(TM0CR_ADDR) TM0CRbits;

#define T0TBS     	TM0CRbits.T0TBS     	/* bit 6 */

#endif
