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
   	       __asm(nop); __asm(nop); __asm(nop); __asm(nop); //_asm nop 1��ʱ������     1us
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
/* ��ʱ xus                                                              */
/* ��������80M                                                           */
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
/* ��ʱ xms                                                              */
/* ����delay_us()                                                        */
/*-----------------------------------------------------------------------*/
void delay_ms(DWORD ms)
{
	int i;
	
	for (i = 0; i < ms; i++)
	{
		delay_us(1000);
	}
}


