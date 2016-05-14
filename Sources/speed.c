/*
 * speed.c
 *
 *  Created on: Mar 13, 2016
 *      Author: zhongwei
 */

#include "includes.h"

byte backflag=0;
int csl=0,csr=0;//currentspeedleft=0,currentspeedright=0;
int tsl=0,tsr=0;//targetspeedleft=0,targetspeedright=0;
int targetspeed=0,Motor_PWM_MAX=400,Motor_PWM_MIN=-400;
int cyclespeed=180,turnspeed=130,straightspeed=270,cyclespeedleft=140,cyclespeedright=100;
unsigned int speedcounter1=0,speedcounter2=0,speedcounter3=0,speedcounter4=0;
//**********************���ٲ���***************************/
signed int Speed_kc=15000;
signed int wheel_distance=9;//�복��8
signed int RPID=0;
double r=0;
//**********************���PID����**********************************************;	
signed int ErrorLeft=0,PreErrorLeft=0,SumErrorLeft=0,ErrorRight=0,PreErrorRight=0,SumErrorRight=0;
double Speed_kp_Left=50,Speed_ki_Left=0.6,Speed_kd_Left=0;
double Speed_kp_Right=50,Speed_ki_Right=0.85,Speed_kd_Right=0;	//���PID
/*************************����ӿں���*********************/
void SET_motor(int leftSpeed,int rightSpeed)
{
	if(leftSpeed>=0) {EMIOS_0.CH[20].CBDR.R = 0;EMIOS_0.CH[19].CBDR.R =leftSpeed;}
		else {EMIOS_0.CH[20].CBDR.R = -leftSpeed;EMIOS_0.CH[19].CBDR.R =-0;}//����  E5����   E6���
	if(rightSpeed>=0) {EMIOS_0.CH[22].CBDR.R = rightSpeed;EMIOS_0.CH[21].CBDR.R = 0;}
		else {EMIOS_0.CH[22].CBDR.R = 0;EMIOS_0.CH[21].CBDR.R = -rightSpeed;}//����  E3�ҽ�   E4����
}
/*************************�ٶȿ��ƺ���*********************/
//void Speed_control(void)
//{
//	RPID=CENTER-Steer_PWM[3];
//	r=Speed_kc/RPID;
//	tsr=((r-wheel_distance)/r)*targetspeed;//���ּ���
//	tsl=((r+wheel_distance+2)/r)*targetspeed;//���ּ���
//	SET_motor(tsl,tsr);
//}

/*************************����������***********************/
void SpeedCount(void)
{
	speedcounter1=EMIOS_0.CH[8].CCNTR.R;              //��A8
	if(speedcounter1<speedcounter2)
		csl=speedcounter1+65535-speedcounter2;         //current speed left
	else 
		csl=speedcounter1-speedcounter2;
	if(backwardleft)
		csl=-csl;
	else 
		csl=csl;
	speedcounter2=speedcounter1;
	
	speedcounter3=EMIOS_0.CH[24].CCNTR.R;               //��D12
	if(speedcounter3<speedcounter4)
	{
		csr=speedcounter3+65535-speedcounter4;         //current speed right
	}
	else 
		csr=speedcounter3-speedcounter4;	
	if(backwardright) 
		csr=-csr;
	else 
		csr=csr;
	speedcounter4=speedcounter3;
//	if(csl==0||csr==0)
//		backflag=1;
}
//*****************************************************************************************************************
//************************************************���ֲ���PID�ٶȿ���************************************************    	  *
//*****************************************************************************************************************
void SpeedControl(void)//�ջ�,�Ӳ���,������
{
//	RPID=CENTER-Steer_PWM[3];
//	r=Speed_kc/RPID;
//	tsr=((r-wheel_distance)/r)*targetspeed;//���ּ���
//	tsl=((r+wheel_distance+2)/r)*targetspeed;//���ּ���
//	SET_motor(tsl,tsr);
	if(cycle_flag)
	{
		tsl=cyclespeedleft;
		tsr=cyclespeedright;
	}
	else
	{
		tsl=targetspeed;
		tsr=targetspeed;
	}
	ErrorLeft=(signed int)(tsl)-(signed int)(csl);
	ErrorRight=(signed int)(tsr)-(signed int)(csr);
	
	SumErrorLeft+=ErrorLeft;
	if(SumErrorLeft>350) SumErrorLeft=350;
	if(SumErrorLeft<-350) SumErrorLeft=-350;	    
	SumErrorRight+=ErrorRight;
	if(SumErrorRight>350) SumErrorRight=350;
	if(SumErrorRight<-350) SumErrorRight=-350;
	
	tsl=Speed_kp_Left*ErrorLeft+Speed_ki_Left*SumErrorLeft+Speed_kd_Left*(ErrorLeft-PreErrorLeft);
	tsr=Speed_kp_Right*ErrorRight+Speed_ki_Right*SumErrorRight+Speed_kd_Right*(ErrorRight-PreErrorRight);
	
	if(tsl>Motor_PWM_MAX)  tsl=Motor_PWM_MAX;
	else if(tsl<Motor_PWM_MIN)  tsl=Motor_PWM_MIN;	    
	if(tsr>Motor_PWM_MAX)  tsr=Motor_PWM_MAX;
	else if(tsr<Motor_PWM_MIN)  tsr=Motor_PWM_MIN;
	
	SET_motor(tsl,tsr);
	
	PreErrorLeft=ErrorLeft;
	PreErrorRight=ErrorRight;
}
