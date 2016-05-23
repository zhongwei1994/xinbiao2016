/*
 * supersonic.c
 *
 *  Created on: Mar 31, 2016
 *      Author: lenovo
 */

#include "includes.h"

unsigned long distance1=0;
int OLED_distance1=0;
unsigned long distance2=0;
int OLED_distance2=0;
word distance_T1=6500,distance_T2=5200;
byte barrier_left_flag=0,barrier_right_flag=0;
byte blf_cnt=0,brf_cnt=0,judge_cnt=0;

//void intc_get_supersonic_time_1(void)
//{
//	unsigned long tmp_a, tmp_b;
//	tmp_a = EMIOS_0.CH[1].CADR.R;		//tmp_a为超声波脉冲下降沿，tmp_b为上升沿
//	tmp_b = EMIOS_0.CH[1].CBDR.R;
//	if(tmp_a >= tmp_b)
//	{
//		distance1 = tmp_a - tmp_b;
//	}
//	else
//	{
//		distance1 = 0xffffffff - tmp_b + tmp_a;
//	}
//	if(distance1<distance_T&&distance1>0)
//	{
//		brf_cnt++;
//		if(brf_cnt>=2)//3为判断障碍物的次数（time_2中也是）
//		{
//			brf_cnt=0;
//			barrier_right_flag=1;
//		}
//	}
//	else
//	{
//		brf_cnt=0;
//	}
//	OLED_distance1=distance1;
//	EMIOS_0.CH[1].CSR.B.FLAG = 1;	
//}

void intc_get_supersonic_time_2(void)
{
	unsigned long tmp_a, tmp_b;
	tmp_a = EMIOS_0.CH[3].CADR.R;
	tmp_b = EMIOS_0.CH[3].CBDR.R;
	if(tmp_a >= tmp_b)
	{
		distance2 = tmp_a - tmp_b;
	}
	else
	{
		distance2 = 0xffffffff - tmp_b + tmp_a;
	}
	if(distance2<distance_T1&&distance2>0)
	{
		blf_cnt++;
		if(blf_cnt>=3)//3为判断障碍物的次数
		{
			if(distance2<distance_T2&&distance2>0)
			{
				blf_cnt=0;
				barrier_left_flag=1;
			}
		}
	}
	else
	{
		judge_cnt++;
		if(judge_cnt>=1)
		{
			blf_cnt=0;
			judge_cnt=0;
		}
	}
	OLED_distance2=distance2;
	EMIOS_0.CH[3].CSR.B.FLAG = 1;	
}

void trigger_supersonic_1(void)
{
	SIU.GPDO[31].R = 0;
	delay_us(5);
	SIU.GPDO[31].R = 1;
	delay_us(30);
	SIU.GPDO[31].R = 0;
}

void trigger_supersonic_2(void)
{
	SIU.GPDO[28].R = 0;
	delay_us(5);
	SIU.GPDO[28].R = 1;
	delay_us(30);
	SIU.GPDO[28].R = 0;
}
