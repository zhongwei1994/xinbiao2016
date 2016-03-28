/*
 * steer.c
 *
 *  Created on: Mar 13, 2016
 *      Author: zhongwei
 */

#include "includes.h"

/*************************�������***************************/
int target_offset=0,last_offset=0;	//���ƫ��ֵ��¼
double Steer_kp=10,Steer_kd=0;//���P��Dֵ
unsigned int RIGHT=3750;
unsigned int LEFT=4150;
unsigned int Steer_PWM[4]={0,0,0,CENTER};//������ֵ��¼

/*************************����ӿں���***********************/
void SET_steer(unsigned int steer)
{EMIOS_0.CH[4].CBDR.R = steer;}
/*************************���PD��������***********************/
void Steer_PDSet(void)
{
	//target_offset=error;
	if(targetspeed<100)
	{
		Steer_kp=8;Steer_kd=0;
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
/*************************������ƣ�PD***********************/
void SteerControl(void)
{
	if(wrong_flag==1)
	{
		Steer_PWM[3]=(Steer_PWM[2]+Steer_PWM[1])/2;
		SET_steer(Steer_PWM[3]);
		//����ֵ
		Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
		return;
	}
	target_offset=pix_j-50;
	Steer_PWM[3] = CENTER-Steer_kp*target_offset-Steer_kd*(target_offset-last_offset); //λ��ʽPD

	if(Steer_PWM[3]>LEFT) Steer_PWM[3]=LEFT;
	else if(Steer_PWM[3]<RIGHT) Steer_PWM[3]=RIGHT;

	SET_steer(Steer_PWM[3]);
	
	//����ֵ��offsetֵ
	Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
	last_offset=target_offset;
}

