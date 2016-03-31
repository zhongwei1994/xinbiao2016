/*
 * supersonic.c
 *
 *  Created on: Mar 31, 2016
 *      Author: lenovo
 */

#include "includes.h"

int distance=0;

void intc_get_supersonic_time_0(void)
{
	int tmp_a, tmp_b;
	tmp_a = EMIOS_0.CH[7].CADR.R;
	tmp_b = EMIOS_0.CH[7].CBDR.R;
	if(tmp_a >= tmp_b)
	{
		distance = tmp_a - tmp_b;
	}
	else
	{
		distance = 0xffff - tmp_b + tmp_a;
	}
	EMIOS_0.CH[7].CSR.B.FLAG = 1;	
}

void trigger_supersonic_0(void)
{
	SIU.GPDO[31].R = 0;
	delay_us(5);
	SIU.GPDO[31].R = 1;
	delay_us(30);
	SIU.GPDO[31].R = 0;
}
