/*
 * steer.c
 *
 *  Created on: Mar 13, 2016
 *      Author: zhongwei
 */

#include "includes.h"

/*************************舵机参数***************************/
byte wrong_count=0;
byte aim=0,aim2=4;
byte close_supersonic=1,cycle_flag=0,start_flag=0,menu=0;
byte success=0,straight_flag=10;
byte cycle_i=55,cycle_j=65,turnleft=65,edge=61;//turnleft为近处目标方向，不宜轻易改变//52/65
double target_offset=0,last_offset=0,target_center=0;	//舵机偏差值记录
double Steer_kp=4,Steer_kd=0.05;//舵机P、D值
unsigned int Steer_PWM[4]={0,0,0,CENTER};//舵机输出值记录
/*************************舵机接口函数***********************/
void SET_steer(unsigned int steer)
{EMIOS_0.CH[4].CBDR.R = steer;}
/*************************向左转时舵机error参数设置***********************/
void steer_error_left(void)
{
//	if(pix_i<27)	//远处
//	{
//		target_center=0.364*pix_i+51.172+aim;
//		target_offset=pix_j-target_center;
//	}
//	else if(pix_i<40)
//	{
//		target_center=0.385*pix_i+50.6+aim;
//		target_offset=pix_j-target_center;
//	}
//	else if(pix_i<50)
//	{
//		target_center=1*pix_i+26+aim;
//		target_offset=pix_j-target_center;
//	}
	if(pix_i<50)
	{
		target_center=0.01369*pix_i*pix_i-0.3581*pix_i+57.69+aim;//57.69
		target_offset=pix_j-target_center;
	}
	else
	{
		target_offset=0;
	}
}
/*************************向右转时舵机error参数设置***********************/
void steer_error_right(void)
{
//	if(pix_i<27)	//远处
//	{
//		target_center=-0.235*pix_i+50.35+aim2;
//		//target_center=-0.3*pix_i+56.7;
//		target_offset=pix_j-target_center;
//	}
//	else if(pix_i<40)
//	{
//		target_center=-0.538*pix_i+58.52+aim2;
//		//target_center=-0.364*pix_i+59.924;
//		target_offset=pix_j-target_center;
//	}
//	else if(pix_i<50)
//	{
//		target_center=-0.35*pix_i+51+aim2;
//		//target_center=-0.778*pix_i+76.12;
//		target_offset=pix_j-target_center;
//	}
	if(pix_i<50)
	{
		target_center=-0.009277*pix_i*pix_i+0.1892*pix_i+47.56+aim;//45.56
		target_offset=pix_j-target_center;
	}
	else
	{
			target_offset=0;
	}
}
/*************************舵机PD参数设置***********************/
void Steer_PDSet(void)
{
	if(pix_i<40)
	{
		if(ABS(pix_j-target_center)<10)
		{
			Steer_kp=2.7+0.3*ABS(pix_j-target_center)+0.08*(pix_i-20);
		}
		else
			Steer_kp=5.7+0.08*(pix_i-20);
	}
	else
		Steer_kp=1*(pix_i-40)+4.3;//4.5
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
//	target_offset=3000+straightspeed;
//	SET_steer(target_offset);
//	return;
	if(blf_cnt>=1||barrier_left_flag==1)
		return;
	if(wrong_flag)		
	{
		close_supersonic=1;//触发关闭超声波标志
		wrong_count++;
		if(wrong_count<=1)	//1次没看到灯塔，保持舵机值
		{
			if(success)
			{
				cycle_flag=1;
				Steer_PWM[3]=LEFT;
				success=0;
			}
			else
			{
				cycle_flag=0;
				Steer_PWM[3]=(Steer_PWM[2]+Steer_PWM[1])/2;
			}
		}
		else if(wrong_count>=2)	//2次没看到灯塔，向右打足转圈
		{
			cycle_flag=1;
			if(start_flag==0)
				Steer_PWM[3]=CENTER;
			else
				Steer_PWM[3]=LEFT;
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
		if(pix_i>cycle_i&&pix_j>cycle_j&&lamp_turn!=straight_flag)		//靠近灯塔，位置符合灯塔在右下角条件，开始转向
		{
			cycle_flag=1;
			Steer_PWM[3]=LEFT;
			SET_steer(Steer_PWM[3]);
			//存舵机值
			Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
			success=1;
			return;
		}
		if(pix_i<33)		//在远处，现在超声全关了，所以close_supersonic=1;，正常close_supersonic=0；远处开超声
		{
			if(pix_i<24)
				close_supersonic=0;
			else
				close_supersonic=1;
			if(Steer_PWM[3]>3948||Steer_PWM[3]<3748)
				targetspeed=turnspeed;
			else
				targetspeed=straightspeed;
			Steer_PWM[3] = CENTER-Steer_kp*target_offset-Steer_kd*(target_offset-last_offset);
		}
		else if(pix_i<42)
		{
//			if(pix_i<33)
//				close_supersonic=0;
//			else
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
	if(blf_cnt>=1||barrier_left_flag==1)
	{
		return;
	}
	if(wrong_flag)		
	{
		close_supersonic=1;//触发关闭超声波标志
		wrong_count++;
		if(wrong_count<=1)	//1次没看到灯塔，保持舵机值
		{
			if(success)
			{
				cycle_flag=1;
				Steer_PWM[3]=RIGHT;
				success=0;
			}
			else
			{
				cycle_flag=0;
				Steer_PWM[3]=(Steer_PWM[2]+Steer_PWM[1])/2;
			}
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
		if(pix_i>cycle_i&&pix_j<100-cycle_j&&lamp_turn!=straight_flag)		//靠近灯塔，位置符合灯塔在左下角条件，开始转向
		{
			cycle_flag=1;
			Steer_PWM[3]=RIGHT;
			SET_steer(Steer_PWM[3]);
			//存舵机值
			Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
			success=1;
			return;
		}
		if(pix_i<33)		//在远处，现在超声全关了，所以close_supersonic=1;，正常close_supersonic=0；远处开超声
		{
			if(pix_i<24)
				close_supersonic=0;
			else
				close_supersonic=1;
			if(Steer_PWM[3]>3948||Steer_PWM[3]<3748)
				targetspeed=turnspeed;
			else
				targetspeed=straightspeed;
			Steer_PWM[3] = CENTER-Steer_kp*target_offset-Steer_kd*(target_offset-last_offset);
		}
//		else if(pix_i<33)
//		{
//			close_supersonic=1;//触发关闭超声波标志
//			targetspeed=turnspeed;
//			Steer_PWM[3] = CENTER-Steer_kp*target_offset-Steer_kd*(target_offset-last_offset);
//			if(Steer_PWM[3]>4000) Steer_PWM[3]=4000;
//			else if(Steer_PWM[3]<3690) Steer_PWM[3]=3690;	
//		}
		else if(pix_i<42)
		{
//			if(pix_i<33)
//				close_supersonic=0;
//			else
				close_supersonic=1;//触发关闭超声波标志
			targetspeed=turnspeed;
			Steer_PWM[3] = CENTER-Steer_kp*target_offset-Steer_kd*(target_offset-last_offset);
			if(Steer_PWM[3]>4000) Steer_PWM[3]=4000;
			else if(Steer_PWM[3]<3690) Steer_PWM[3]=3690;	
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
	if(blf_cnt>=1)
		targetspeed=cyclespeedright;
	if(barrier_left_flag==1)
	{
		SET_steer(3648);
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
