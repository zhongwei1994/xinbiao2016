/*
 * steer.c
 *
 *  Created on: Mar 13, 2016
 *      Author: zhongwei
 */

#include "includes.h"

/*************************舵机参数***************************/
byte wrong_count=0;
byte close_supersonic=1,cycle_flag=0;
byte success=0;
byte cycle_j=66,turnleft=60;
int target_offset=0,last_offset=0;	//舵机偏差值记录
double Steer_kp=0,Steer_kd=0;//舵机P、D值
unsigned int Steer_PWM[4]={0,0,0,CENTER};//舵机输出值记录
/*************************舵机接口函数***********************/
void SET_steer(unsigned int steer)
{EMIOS_0.CH[4].CBDR.R = steer;}
/*************************舵机PD参数设置***********************/
void Steer_PDSet(void)
{
	//target_offset=error;
	if(pix_i<40)
	{
		if(pix_j>58||pix_j<42)
		{
			if(targetspeed==straightspeed)
				Steer_kp=3+0.5*(ABS(pix_j-50)-8);
			else
				Steer_kp=8;
				Steer_kp=5+0.5*(ABS(pix_j-50)-8);
		}
		else
		{
			if(targetspeed==straightspeed)
				Steer_kp=3;
			else
				Steer_kp=5;
		}
	}
	else
	{
		if(targetspeed==straightspeed)
			Steer_kp=3;
		else
			Steer_kp=5;
	}
}
/*************************舵机控制，PD***********************/
void SteerControl(void)
{
	Steer_PDSet();
	if(barrier_left_flag==1||barrier_right_flag==1||backflag==1)
	{
		return;
	}
	if(wrong_flag==1)		
	{
		close_supersonic=1;//触发关闭超声波标志
		wrong_count++;
		if(success)		//判断到灯塔边上
		{
			cycle_flag=1;
			targetspeed=cyclespeed;
			BEE = 1;
			Steer_PWM[3]=RIGHT;
			SET_steer(Steer_PWM[3]);
			//存舵机值
			Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
			success=0;
			return;
		}
		else
		{
			if(wrong_count==1)	//1次没看到灯塔，保持舵机值
			{
				cycle_flag=0;
				Steer_PWM[3]=(Steer_PWM[2]+Steer_PWM[1])/2;
				SET_steer(Steer_PWM[3]);
				Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
				return;
			}
			else if(wrong_count>=2)	//2次没看到灯塔，向左打足转圈
			{
				cycle_flag=1;
				targetspeed=cyclespeed;
				BEE = 1;
				Steer_PWM[3]=RIGHT;
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
		if(pix_i<33)	
		{
			if(pix_i<29)		//在远处，现在超声全关了，所以close_supersonic=1;，正常close_supersonic=0；远处开超声
			{
				close_supersonic=1;
				targetspeed=straightspeed;
			}
			else				//在近处，现在超声全关了
			{  
				close_supersonic=1;//触发关闭超声波标志
				targetspeed=cyclespeed;
			}
			cycle_flag=0;
			target_offset=pix_j-46;
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
			close_supersonic=1;//触发关闭超声波标志
			if(pix_i>55)
			{
				success=1;
			}
			if(pix_i>53&&pix_j>cycle_j)		//靠近灯塔，位置符合灯塔在右下角条件，开始转向
			{
				cycle_flag=1;
				targetspeed=cyclespeed;
				BEE = 1;
				Steer_PWM[3]=RIGHT;
				SET_steer(Steer_PWM[3]);
				//存舵机值
				Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
				return;
			}
			else		//靠近灯塔，但位置不符合灯塔在右下角条件，稍微跑偏一点预转向
			{
				cycle_flag=0;
				targetspeed=cyclespeed;
				//小车离灯塔较近时为了使小车不直接朝灯塔跑，将目标值46进行修正如下
				target_offset=pix_j-turnleft;
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
byte BarrierJudge(void)	//超声优先级
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

