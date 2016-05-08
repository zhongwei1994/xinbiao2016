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
  PIT.CH[1].LDVAL.R = 80000;      // PIT1 timeout = 80000 sysclks x 1sec/80M sysclks = 1 msec 
  PIT.CH[1].TCTRL.R = 0x000000003; // Enable PIT1 interrupt and make PIT active to count 
  INTC_InstallINTCInterruptHandler(PitISR,60,10); //10
}

void PitISR(void)//1ms一个控制周期
{
	pitcount0++;                                  //5ms一次清零
	if(pitcount0==2)
	{
		pitcount2++;
		if(pitcount2>=14)                          //75ms一次,超声波触发
		{
			pitcount2=0;
			if(BarrierJudge()==1)                  //障碍物判断，左转
			{
				BEE=1;
				barrier_delay++;
				if(barrier_delay>=4)				//延时后右转
				{
					SET_steer(RIGHT);
				}
				if(barrier_delay>=9)				//右转延时
				{
					barrier_delay=0;
					BEE=0;
					barrier_left_flag=0;
					barrier_right_flag=0;
				}
			}
			else if(BarrierJudge()==2)               //障碍物判断，右转
			{
				BEE=1;
				barrier_delay++;
				if(barrier_delay>=4)
				{
					SET_steer(LEFT);
				}
				if(barrier_delay>=9)
				{
					barrier_delay=0;
					BEE=0;
					barrier_left_flag=0;
					barrier_right_flag=0;
				}
			}
			else
			{
//				if(ss_delay_flag1==1)              //避障成功后延时
//				{
//					supson_delay1++;
//					if(supson_delay1>30)           //30*100ms=3s
//					{
//						supson_delay1=0;
//						ss_delay_flag1==0;
//					}
//						
//				}
//				else if(ss_delay_flag2==1)          //接近灯塔时延时
//				{
//					supson_delay2++;
//					if(supson_delay2>50)           //50*100ms=5s
//					{
//						supson_delay2=0;
//						ss_delay_flag2==0;
//					}
//						
//				}
//				else                               //不需要延时的时候，触发超声波
//				{
				if(close_supersonic==0)
				{
					trigger_supersonic_1();
					trigger_supersonic_2();
				}
//				}
			}
		}
	}
	if(pitcount0==3)
	{
		pitcount3++;
		if(pitcount3>=3)                          //15ms一次
		{
			pitcount3=0;
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
		}
	}
	if(pitcount0==4)
	{
		pitcount4++;
		if(pitcount4>=3)                          //25ms一次速度控制
		{
			pitcount4=0;
		}
	}
	if(pitcount0==5)
	{
		pitcount0=0;
		pitcount5++;
		if(pitcount5>=100)                         //1s一次
		{
			pitcount5=0;
			OLED_Fill(0x00);
			OLED_SetPointer(2,20);
			OLED_Num(straightspeed);
			OLED_SetPointer(3,20);
			OLED_Num((Speed_kp_Left*10));
			//OLED_Num(OLED_distance1);
			OLED_SetPointer(4,20);
			OLED_Num((Speed_kp_Right*10));
			//OLED_Num(OLED_distance2);
			OLED_SetPointer(5,20);
			OLED_Num(cyclespeed);
			OLED_SetPointer(6,20);
			OLED_Num(turnleft);
			OLED_SetPointer(7,20);
			OLED_Num(csl);
			OLED_SetPointer(7,50);
			OLED_Num(csr);
			OLED_SetPointer(7,80);
			OLED_Num(targetspeed);
		}
	}
	PIT.CH[1].TFLG.B.TIF = 1;//write 1 to clear PIT1 清除标志位
}
