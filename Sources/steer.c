/*
 * steer.c
 *
 *  Created on: Mar 13, 2016
 *      Author: zhongwei
 */

#include "includes.h"

/*************************舵机参数***************************/
byte wrong_count=0;
byte aim=5,aim2=9;
byte close_supersonic=1,cycle_flag=0,start_flag=0;
byte success=0;
byte cycle_i=60,cycle_j=65,turnleft=65,edge=61;//turnleft为近处目标方向，不宜轻易改变
double target_offset=0,last_offset=0,target_center=0;	//舵机偏差值记录
double Steer_kp=4,Steer_kd=0.05;//舵机P、D值
unsigned int Steer_PWM[4]={0,0,0,CENTER};//舵机输出值记录
/*************************舵机接口函数***********************/
void SET_steer(unsigned int steer)
{EMIOS_0.CH[4].CBDR.R = steer;}
/*************************向左转时舵机error参数设置***********************/
void steer_error_left(void)
{
	if(pix_i<27)	//远处
	{
		target_center=0.375*pix_i+51.875+aim;
		//target_center=0.465*pix_i+50.745+aim;
		//target_center=0.3*pix_i+52.3;
		target_offset=pix_j-target_center;
	}
	else if(pix_i<40)
	{
		target_center=0.269*pix_i+54.74+aim;
		//target_center=0.169*pix_i+58.74+aim;
		//target_center=0.364*pix_i+50.44;
		target_offset=pix_j-target_center;
	}
	else
	{
		target_center=0.9*pix_i+29+aim;
		//target_center=0.85*pix_i+31.5+aim;
		//target_center=0.778*pix_i+33.88;
		target_offset=pix_j-target_center;
	}
}
/*************************向右转时舵机error参数设置***********************/
void steer_error_right(void)
{
	if(pix_i<27)	//远处
	{
		target_center=-0.235*pix_i+52.35+aim2;
		//target_center=-0.3*pix_i+56.7;
		target_offset=pix_j-target_center;
	}
	else if(pix_i<40)
	{
		target_center=-0.538*pix_i+60.52+aim2;
		//target_center=-0.364*pix_i+59.924;
		target_offset=pix_j-target_center;
	}
	else
	{
		target_center=-0.35*pix_i+53+aim2;
		//target_center=-0.778*pix_i+76.12;
		target_offset=pix_j-target_center;
	}
}
/*************************舵机PD参数设置***********************/
void Steer_PDSet(void)
{
	if(pix_i<40)
	{
		if(ABS(pix_j-target_center)<10)
		{
			Steer_kp=3+0.5*ABS(pix_j-target_center)+0.05*(pix_i-20);
		}
		else
			Steer_kp=3.5+0.1*(pix_i-20);
	}
	else
		Steer_kp=1*(pix_i-40)+4.5;
//	if(pix_i<30)		//远处
//		Steer_kp=0.167*pix_i-1.008;
//	else if(pix_i<43)
//		Steer_kp=0.154*pix_i-0.62;
//	else
//		Steer_kp=0.667-22.681;
}
/*************************舵机控制向左转U型弯，PD***********************/
void SteerControl_left(void)
{
	if(blf_cnt>=2||barrier_left_flag==1||barrier_right_flag==1||backflag==1)
	{
		return;
	}
	if(wrong_flag)		
	{
		close_supersonic=1;//触发关闭超声波标志
		wrong_count++;
		if(wrong_count<1)	//1次没看到灯塔，保持舵机值
		{
			cycle_flag=0;
			Steer_PWM[3]=(Steer_PWM[2]+Steer_PWM[1])/2;
		}
		else if(wrong_count>=2)	//2次没看到灯塔，向右打足转圈
		{
			cycle_flag=1;
			if(start_flag==0)
				Steer_PWM[3]=CENTER;
			else
				Steer_PWM[3]=LEFT;
//			if(success)
//				success=0;
		}
		SET_steer(Steer_PWM[3]);
		Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
	}
	else
	{
		start_flag=1;
		if(wrong_count>=2)
			switch_flag=1;
		wrong_count=0;
		cycle_flag=0;
		Steer_PDSet();
		steer_error_left();
		if(pix_i>cycle_i&&pix_j>cycle_j)		//靠近灯塔，位置符合灯塔在右下角条件，开始转向
		{
			cycle_flag=1;
			Steer_PWM[3]=LEFT;
			SET_steer(Steer_PWM[3]);
			//存舵机值
			Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
			return;
		}
		if(pix_i<30)		//在远处，现在超声全关了，所以close_supersonic=1;，正常close_supersonic=0；远处开超声
		{
			close_supersonic=0;
			targetspeed=straightspeed;
			Steer_PWM[3] = CENTER-Steer_kp*target_offset-Steer_kd*(target_offset-last_offset);
			if(Steer_PWM[3]>4020) Steer_PWM[3]=4020;
			else if(Steer_PWM[3]<3714) Steer_PWM[3]=3714;	
		}
		else if(pix_i<33)
		{
			close_supersonic=1;//触发关闭超声波标志
			targetspeed=turnspeed;
			Steer_PWM[3] = CENTER-Steer_kp*target_offset-Steer_kd*(target_offset-last_offset);
			if(Steer_PWM[3]>4020) Steer_PWM[3]=4020;
			else if(Steer_PWM[3]<3714) Steer_PWM[3]=3714;	
		}
		else if(pix_i<42)
		{
			close_supersonic=1;//触发关闭超声波标志
			targetspeed=turnspeed;
			Steer_PWM[3] = CENTER-Steer_kp*target_offset-Steer_kd*(target_offset-last_offset);
			if(Steer_PWM[3]>4100) Steer_PWM[3]=4100;
			else if(Steer_PWM[3]<3634) Steer_PWM[3]=3634;	
		}
		else
		{
			close_supersonic=1;//触发关闭超声波标志
			targetspeed=cyclespeed;
			Steer_PWM[3] = CENTER-Steer_kp*target_offset-Steer_kd*(target_offset-last_offset);
			if(Steer_PWM[3]>4150) Steer_PWM[3]=4150;
			else if(Steer_PWM[3]<3620) Steer_PWM[3]=3620;	
		}
		SET_steer(Steer_PWM[3]);
		//存舵机值和offset值
		Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
		last_offset=target_offset;
	}
}
/*************************舵机控制向右转U型弯，PD***********************/
void SteerControl_right(void)
{
	if(blf_cnt>=2||barrier_left_flag==1||barrier_right_flag==1||backflag==1)
	{
		return;
	}
	if(wrong_flag)		
	{
		close_supersonic=1;//触发关闭超声波标志
		wrong_count++;
		if(wrong_count<1)	//1次没看到灯塔，保持舵机值
		{
			cycle_flag=0;
			Steer_PWM[3]=(Steer_PWM[2]+Steer_PWM[1])/2;
		}
		else if(wrong_count>=2)	//2次没看到灯塔，向右打足转圈
		{
			cycle_flag=1;
			if(start_flag==0)
				Steer_PWM[3]=CENTER;
			else
				Steer_PWM[3]=RIGHT;
//			if(success)
//				success=0;
		}
		SET_steer(Steer_PWM[3]);
		Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
	}
	else
	{
		start_flag=1;
		if(wrong_count>=2)
			switch_flag=1;
		wrong_count=0;
		cycle_flag=0;
		Steer_PDSet();
		steer_error_right();
		if(pix_i>cycle_i&&pix_j<100-cycle_j)		//靠近灯塔，位置符合灯塔在左下角条件，开始转向
		{
			cycle_flag=1;
			Steer_PWM[3]=RIGHT;
			SET_steer(Steer_PWM[3]);
			//存舵机值
			Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
			return;
		}
		if(pix_i<30)		//在远处，现在超声全关了，所以close_supersonic=1;，正常close_supersonic=0；远处开超声
		{
			close_supersonic=0;
			targetspeed=straightspeed;
			Steer_PWM[3] = CENTER-Steer_kp*target_offset-Steer_kd*(target_offset-last_offset);
			if(Steer_PWM[3]>4020) Steer_PWM[3]=4020;
			else if(Steer_PWM[3]<3714) Steer_PWM[3]=3714;	
		}
		else if(pix_i<33)
		{
			close_supersonic=1;//触发关闭超声波标志
			targetspeed=turnspeed;
			Steer_PWM[3] = CENTER-Steer_kp*target_offset-Steer_kd*(target_offset-last_offset);
			if(Steer_PWM[3]>4020) Steer_PWM[3]=4020;
			else if(Steer_PWM[3]<3714) Steer_PWM[3]=3714;	
		}
		else if(pix_i<42)
		{
			close_supersonic=1;//触发关闭超声波标志
			targetspeed=turnspeed;
			Steer_PWM[3] = CENTER-Steer_kp*target_offset-Steer_kd*(target_offset-last_offset);
			if(Steer_PWM[3]>4100) Steer_PWM[3]=4100;
			else if(Steer_PWM[3]<3634) Steer_PWM[3]=3634;	
		}
		else
		{
			close_supersonic=1;//触发关闭超声波标志
			targetspeed=cyclespeed;
			Steer_PWM[3] = CENTER-Steer_kp*target_offset-Steer_kd*(target_offset-last_offset);
			if(Steer_PWM[3]>4150) Steer_PWM[3]=4150;
			else if(Steer_PWM[3]<3620) Steer_PWM[3]=3620;	
		}
		SET_steer(Steer_PWM[3]);
		//存舵机值和offset值
		Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
		last_offset=target_offset;
	}
}

byte BarrierJudge(void)	//超声优先级
{
	if(blf_cnt>=2)
	{
		targetspeed=cyclespeedright;
	}
	if(barrier_left_flag==1)
	{
		SET_steer(4150);
		return 1;
	}
//	else if(barrier_right_flag==1)
//	{
//		SET_steer(RIGHT);
//		return 2;
//	}
	else
		return 0;
}
