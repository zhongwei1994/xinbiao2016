/*
 * delay.c
 *
 *  Created on: Mar 7, 2016
 *      Author: zhongwei
 */
#include "includes.h"

void udelay(int us)
{
   int udelay_i;
   for(udelay_i=0;udelay_i<us; udelay_i++)
   {
   	       __asm(nop); __asm(nop); __asm(nop); __asm(nop); //_asm nop 1个时钟周期     1us
   	       __asm(nop); __asm(nop); __asm(nop); __asm(nop);
   	       __asm(nop); __asm(nop); __asm(nop); __asm(nop);
   	       __asm(nop); __asm(nop); __asm(nop); __asm(nop);
   	       __asm(nop); __asm(nop); __asm(nop); __asm(nop);
   	       __asm(nop); __asm(nop); __asm(nop); __asm(nop);
   	       __asm(nop); __asm(nop); __asm(nop); __asm(nop);
   	       __asm(nop); __asm(nop); __asm(nop); __asm(nop);
   	       __asm(nop); __asm(nop); __asm(nop); __asm(nop);
   	       __asm(nop); __asm(nop); __asm(nop); __asm(nop);
   	       __asm(nop); __asm(nop); __asm(nop); __asm(nop);
   	       __asm(nop); __asm(nop); __asm(nop); __asm(nop);
   	       __asm(nop); __asm(nop); __asm(nop); __asm(nop);
   	       __asm(nop); __asm(nop); __asm(nop); __asm(nop);
   	       __asm(nop); __asm(nop); __asm(nop); __asm(nop);
   	       __asm(nop); __asm(nop); __asm(nop); __asm(nop);
   	       __asm(nop); __asm(nop); __asm(nop); __asm(nop);
   	       __asm(nop); __asm(nop); __asm(nop); __asm(nop);
   	       __asm(nop); __asm(nop); __asm(nop); __asm(nop);
   	       __asm(nop); __asm(nop); __asm(nop); __asm(nop);
   }
}

/*-----------------------------------------------------------------------*/
/* 延时 xus                                                              */
/* 依赖总线80M                                                           */
/*-----------------------------------------------------------------------*/
void delay_us(DWORD us)
{
	volatile int i, j;
	
	for (i = 0; i < us; i++)
	{
		for (j = 0; j < 9; j++) {}
	}
}


/*-----------------------------------------------------------------------*/
/* 延时 xms                                                              */
/* 依赖delay_us()                                                        */
/*-----------------------------------------------------------------------*/
void delay_ms(DWORD ms)
{
	int i;
	
	for (i = 0; i < ms; i++)
	{
		delay_us(1000);
	}
}

void delay(void)
{
	uint32_t j;
	for(j=0;j<10000;j++)
	{}
}

