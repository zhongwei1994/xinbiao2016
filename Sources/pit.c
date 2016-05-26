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
		BEE=1;
		barrier_delay++;
//		if(barrier_delay>=2)				
//		{
//			SET_steer(RIGHT);
//		}
		if(barrier_delay>=2)			
		{
			barrier_delay=0;
			BEE=0;
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
		OLED_Fill(0x00);
		OLED_SetPointer(2,20);
		OLED_Num((pix_i));
		//OLED_Num(OLED_distance1);
		OLED_SetPointer(2,60);
		OLED_Num((pix_j));
		OLED_SetPointer(3,20);
		OLED_Num((TargetSteer));
		OLED_SetPointer(3,60);
		OLED_Num((target_offset*100));
		//OLED_Num(OLED_distance2);
		OLED_SetPointer(4,20);
		OLED_Num(straightspeed);
		OLED_SetPointer(4,60);
		OLED_Num(Steer_kp*10);
		OLED_SetPointer(5,20);
		OLED_Char('d');
		OLED_SetPointer(5,40);
		OLED_Num(OLED_distance2);
//		OLED_Num(cyclespeed);
		OLED_SetPointer(6,20);
		OLED_Char('l');
		OLED_SetPointer(6,40);
		OLED_Num(lamp_turn);
		OLED_SetPointer(7,20);
		OLED_Num(targetspeed);
		//OLED_Num(cyclespeedright);
		OLED_SetPointer(7,50);
		OLED_Num(csl);
		OLED_SetPointer(7,80);
		OLED_Num(csr);	
//		OLED_Num(distance_T);
//		OLED_Num(targetspeed);
	}
	PIT.CH[1].TFLG.B.TIF = 1;//write 1 to clear PIT1 清除标志位
}

void PitISR2(void)
{
	SpeedCount();
	if(backflag)
	{
		if(pitcount6>20)
		{
			pitcount6=0;
			backflag=0;
		}
		else
		{
			pitcount6++;
			Steer_PWM[3]=4000;
			SET_steer(Steer_PWM[3]);
			Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
			SET_motor(-255,-255);
		}

	}
	else
	{
			SpeedControl();
	}
	PIT.CH[2].TFLG.B.TIF = 1;
}
