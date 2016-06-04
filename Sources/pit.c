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
		OLED_Fill(0x00);
		//1
		OLED_SetPointer(1,0);
		OLED_Str("r: ");
		OLED_Num(RX_data);
		OLED_Str("z6: ");
		OLED_Num(Speed_kd_Left*100);
		OLED_Str("  ");
		OLED_Num(Speed_ki_Right*100);
		//2
		OLED_SetPointer(2,0);
		OLED_Str("pix_i: ");
		OLED_SetPointer(2,40);
		OLED_Num((pix_i));
		//OLED_Num(OLED_distance1);
		OLED_SetPointer(2,55);
		OLED_Str("pix_j: ");
		OLED_SetPointer(2,95);
		OLED_Num((pix_j));
		//3
		OLED_SetPointer(3,0);
		OLED_Str("TStr: ");
		OLED_SetPointer(3,35);
		OLED_Num((TargetSteer));
		OLED_SetPointer(3,65);
		OLED_Str("Toff: ");
		OLED_SetPointer(3,95);
		OLED_Num((target_offset*100));
		//OLED_Num(OLED_distance2);
		//4
		OLED_SetPointer(4,0);
		OLED_Str("SSpd: ");
		OLED_SetPointer(4,35);
		OLED_Num(straightspeed);
		OLED_SetPointer(4,60);
		OLED_Str("StrKp: ");
		OLED_Num(Steer_kp*10);
		//5
//		OLED_SetPointer(5,20);
//		OLED_Char('d');
		OLED_SetPointer(5,0);
		OLED_Str("aim: ");
		OLED_Num(aim);
//		OLED_Num(cyclespeed);
		//6
		OLED_SetPointer(6,0);
		OLED_Str("No: ");
		OLED_Num(lamp_turn);
		OLED_SetPointer(6,40);
		OLED_Str("TarSpd: ");
		OLED_Num(targetspeed);
		//OLED_Num(cyclespeedright);
		//7
		OLED_SetPointer(7,0);
		OLED_Str("kp: ");
		OLED_Num(Speed_kp_Left);
		OLED_SetPointer(7,40);
		OLED_Str("ki: ");
		OLED_Num(Speed_ki_Left);	
		OLED_SetPointer(7,80);
		OLED_Str("kd: ");
//		OLED_Num(target_offset);
		OLED_Num(Speed_kd_Left);	
//		OLED_Num(distance_T);
//		OLED_Num(targetspeed);
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
