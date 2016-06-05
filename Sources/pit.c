/*
 * pit.c
 *
 *  Created on: Apr 1, 2016
 *      Author: lenovo
 */

#include "includes.h"

unsigned int pitcount0=0,pitcount1=0,pitcount2=0,pitcount3=0,pitcount4=0,pitcount5=0,pitcount6=0;
unsigned int barrier_delay=0;
unsigned int supson_delay1=0,supson_delay2=0;
byte OLEDdisplay_flag=1;

void initPIT(void) 
{                                   //1ms一个控制周期// NOTE:  DIVIDER FROM SYSCLK TO PIT ASSUMES DEFAULT DIVIDE BY 1 
	PIT.PITMCR.R = 0x00000001;       // Enable PIT and configure timers to stop in debug mode 
	PIT.CH[2].LDVAL.R = 800000;      // PIT2 timeout = 800000 sysclks x 1sec/80M sysclks = 10 msec 
	PIT.CH[2].TCTRL.R = 0x000000003; // Enable PIT2 interrupt and make PIT active to count 
	INTC_InstallINTCInterruptHandler(PitISR2,61,12); 
	udelay(1);
	PIT.CH[1].LDVAL.R = 6000000;      // PIT1 timeout = 6000000 sysclks x 1sec/80M sysclks = 75 msec 
	PIT.CH[1].TCTRL.R = 0x000000003; // Enable PIT1 interrupt and make PIT active to count 
	INTC_InstallINTCInterruptHandler(PitISR,60,12); 
}

void PitISR(void)//1ms一个控制周期
{
	pitcount0++;                                  //5ms一次清零
	if(BarrierJudge()==1)                  //障碍物判断，左转
	{
		barrier_delay++;
//		if(barrier_delay>=2)				
//		{
//			SET_steer(RIGHT);
//		}
		if(barrier_delay>=2)			
		{
			barrier_delay=0;
			barrier_left_flag=0;
//			barrier_right_flag=0;
		}
	}
//	else if(BarrierJudge()==2)               //障碍物判断，右转
//	{
//		BEE=1;
//		barrier_delay++;
//		if(barrier_delay>=4)
//		{
//			SET_steer(LEFT);
//		}
//		if(barrier_delay>=9)
//		{
//			barrier_delay=0;
//			BEE=0;
//			barrier_left_flag=0;
//			barrier_right_flag=0;
//		}
//	}
	else
	{
		if(close_supersonic==0)
		{
			//trigger_supersonic_1();
			trigger_supersonic_2();
		}
	}
	if(pitcount0>13)
	{
		pitcount0=0;
		if(OLEDdisplay_flag)
			OLED_display();
	}
	PIT.CH[1].TFLG.B.TIF = 1;//write 1 to clear PIT1 清除标志位
}

void PitISR2(void)
{
//	if(csl!=0)
//	{
//		pitcount1++;
//	}
//	if(pitcount1>=300)
//	{
//		targetspeed=0;
//		pitcount1=0;
//	}
	SpeedCount();
	SpeedControl2();
	PIT.CH[2].TFLG.B.TIF = 1;
}
