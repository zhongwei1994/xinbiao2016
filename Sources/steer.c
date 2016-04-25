/*
 * steer.c
 *
 *  Created on: Mar 13, 2016
 *      Author: zhongwei
 */

#include "includes.h"

/*************************舵机参数***************************/
byte wrong_count=0;
byte close_supersonic=1;
byte success=0;
byte cyclespeed=95;
int target_offset=0,last_offset=0;	//舵机偏差值记录
double Steer_kp=8,Steer_kd=0;//舵机P、D值
unsigned int Steer_PWM[4]={0,0,0,CENTER};//舵机输出值记录
/*************************舵机接口函数***********************/
void SET_steer(unsigned int steer)
{EMIOS_0.CH[4].CBDR.R = steer;}
/*************************舵机PD参数设置***********************/
void Steer_PDSet(void)
{
	//target_offset=error;
	if(targetspeed<100)
	{
		Steer_kp=6;Steer_kd=0;
		return;
	}
	else if(targetspeed<130)//120-5 8 8 12 12 10//125
	{
		if(ABS(target_offset)<5)        {Steer_kp=5;Steer_kd=0;}
		else if(ABS(target_offset)<10)  {Steer_kp=8;Steer_kd=0;}
		else if(ABS(target_offset)<30)  {Steer_kp=8;Steer_kd=0;}
		else if(ABS(target_offset)<35)  {Steer_kp=12;Steer_kd=0;}
		else if(ABS(target_offset)<40)  {Steer_kp=12;Steer_kd=0;}
		else							{Steer_kp=10;Steer_kd=0;}
		return;
	}
	else if(targetspeed<150)
	{
		if(ABS(target_offset)<5)        {Steer_kp=5;Steer_kd=5;}
		else if(ABS(target_offset)<10)  {Steer_kp=8;Steer_kd=5;}
		else if(ABS(target_offset)<30)  {Steer_kp=8;Steer_kd=6;}
		else if(ABS(target_offset)<35)  {Steer_kp=11;Steer_kd=5;}
		else if(ABS(target_offset)<40)  {Steer_kp=12;Steer_kd=5;}
		else                            {Steer_kp=10;Steer_kd=5;}
		return;
	}
	else if(targetspeed<200)
	{
		if(ABS(target_offset)<5)        {Steer_kp=8;Steer_kd=0;}
		else if(ABS(target_offset)<10)  {Steer_kp=10;Steer_kd=0;}
		else if(ABS(target_offset)<20)  {Steer_kp=12;Steer_kd=0;}
		else if(ABS(target_offset)<30)  {Steer_kp=13;Steer_kd=0;}
		else if(ABS(target_offset)<40)  {Steer_kp=14;Steer_kd=0;}
		else                            {Steer_kp=14;Steer_kd=0;}
		return;
	}
	else
	{
		if(ABS(target_offset)<5)        {Steer_kp=8;Steer_kd=0;}
		else if(ABS(target_offset)<10)  {Steer_kp=10;Steer_kd=0;}
		else if(ABS(target_offset)<20)  {Steer_kp=12;Steer_kd=0;}
		else if(ABS(target_offset)<30)  {Steer_kp=13;Steer_kd=0;}
		else if(ABS(target_offset)<40)  {Steer_kp=14;Steer_kd=0;}
		else                            {Steer_kp=15;Steer_kd=0;}	
	}
}
/*************************舵机控制，PD***********************/
void SteerControl(void)
{
	if(barrier_left_flag==1||barrier_right_flag==1)
	{
		return;
	}
	if(wrong_flag==1)
	{
		wrong_count++;
		if(success)
		{
			close_supersonic=1;
			SET_motor(cyclespeed,cyclespeed);
			BEE = 1;
			Steer_PWM[3]=LEFT;
			SET_steer(Steer_PWM[3]);
			//存舵机值
			Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
			success=0;
			return;
		}
		else
		{
			if(wrong_count==1)
			{
				Steer_PWM[3]=(Steer_PWM[2]+Steer_PWM[1])/2;
				SET_steer(Steer_PWM[3]);
				Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
				return;
			}
			else if(wrong_count>=2)
			{
				close_supersonic=1;
				SET_motor(cyclespeed,cyclespeed);
				BEE = 1;
				Steer_PWM[3]=LEFT;
				SET_steer(Steer_PWM[3]);
				//存舵机值
				Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
				return;
			}
		}
	}
	else
	{
		wrong_count=0;
		BEE=0;

		if(pix_i<39)
		{
			if(pix_i<33)
			{
					close_supersonic=1;
					SET_motor(targetmotor,targetmotor);
			}
			else
			{  
				close_supersonic=1;//触发关闭超声波标志
				SET_motor(targetmotor,targetmotor);
			}
			target_offset=pix_j-44;
			Steer_PWM[3] = CENTER-Steer_kp*target_offset-Steer_kd*(target_offset-last_offset); //位置式PD
			if(Steer_PWM[3]>LEFT) Steer_PWM[3]=LEFT;
			else if(Steer_PWM[3]<RIGHT) Steer_PWM[3]=RIGHT;
			SET_steer(Steer_PWM[3]);
			//存舵机值和offset值
			Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
			last_offset=target_offset;
		}
		else
		{
			if(pix_i>55)
			{
				success=1;
			}
			if(pix_i>64&&pix_j<18)
			{
				close_supersonic=1;
				SET_motor(cyclespeed,cyclespeed);
				BEE = 1;
				Steer_PWM[3]=LEFT;
				SET_steer(Steer_PWM[3]);
				//存舵机值
				Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
				return;
			}
			else
			{
				close_supersonic=1;//触发关闭超声波标志
				SET_motor(cyclespeed,cyclespeed);
				//小车离灯塔较近时为了使小车不直接朝灯塔跑，将目标值46进行修正如下
				target_offset=pix_j-20;
				Steer_PWM[3] = CENTER-Steer_kp*target_offset-Steer_kd*(target_offset-last_offset); //位置式PD

				if(Steer_PWM[3]>LEFT) Steer_PWM[3]=LEFT;
				else if(Steer_PWM[3]<RIGHT) Steer_PWM[3]=RIGHT;

				SET_steer(Steer_PWM[3]);
				
				//存舵机值和offset值
				Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
				last_offset=target_offset;
			}
		}
	}	
}
byte BarrierJudge(void)
{
	if(barrier_left_flag==1)
	{
		SET_steer(LEFT);
		return 1;
	}
	else if(barrier_right_flag==1)
	{
		SET_steer(RIGHT);
		return 2;
	}
	else
		return 0;
}

