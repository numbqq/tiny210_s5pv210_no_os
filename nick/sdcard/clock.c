#include "clock.h"

#define CLK_DIV0_MASK		0x7fffffff

#define APLL_MDIV       	0x7d
#define APLL_PDIV       	0x3
#define APLL_SDIV      	 	0x1
#define MPLL_MDIV			0x29b
#define MPLL_PDIV			0xc
#define MPLL_SDIV			0x1
#define EPLL_MDIV			0x30
#define EPLL_PDIV			0x3
#define EPLL_SDIV			0x2

#define set_pll(mdiv, pdiv, sdiv)	(1<<31 | mdiv<<16 | pdiv<<8 | sdiv)
#define APLL_VAL		set_pll(APLL_MDIV,APLL_PDIV,APLL_SDIV)
#define MPLL_VAL		set_pll(MPLL_MDIV,MPLL_PDIV,MPLL_SDIV)
#define EPLL_VAL		(1 << 31 | 0 << 27 | EPLL_MDIV << 16 | EPLL_PDIV << 8 | EPLL_SDIV)


void clock_init()
{
	// 1 设置各种时钟开关，暂时不使用PLL
	CLK_SRC0 = 0x0;

	
	// 2 设置锁定时间，使用默认值即可
	// 设置PLL后，时钟从Fin提升到目标频率时，需要一定的时间，即锁定时间 			
	APLL_LOCK = 0x0000FFFF;          			
	MPLL_LOCK = 0x0000FFFF;	
	EPLL_LOCK = 0x0000FFFF;	

	
	// 3 设置分频
	CLK_DIV0 = 0x14131440;

	// 4 设置PLL
	// FOUT= MDIV * FIN / (PDIV*2^(SDIV-1)) = 0x7d*24/(0x3*2^(1-1))=1000 MHz
	APLL_CON0 = APLL_VAL;
	// FOUT = MDIV*FIN/(PDIV*2^SDIV)=0x29b*24/(0xc*2^1)= 667 MHz
	MPLL_CON  = MPLL_VAL;
	// FOUT = MDIV*FIN/(PDIV*2^SDIV)=0x30*24/(0x3*2^1)= 96 MHz
	EPLL_CON1 = 0;
	EPLL_CON1 = EPLL_VAL;	

	// 5 设置各种时钟开关，使用PLL
	CLK_SRC0 = 0x10001111;
}
