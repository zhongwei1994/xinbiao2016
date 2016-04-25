/*
 * speed.c
 *
 *  Created on: Mar 13, 2016
 *      Author: zhongwei
 */

#include "includes.h"

int csl=0,csr=0;//currentspeedleft=0,currentspeedright=0;
int tsl=0,tsr=0;//targetspeedleft=0,targetspeedright=0;
int targetspeed=0;
//**********************差速参数***************************/
signed int Speed_kc=15000;
signed int wheel_distance=9;//半车距8
signed int RPID=0;	
double r=0;

/*************************电机接口函数*********************/
void SET_motor(int leftSpeed,int rightSpeed)
{
	if(leftSpeed>=0) {EMIOS_0.CH[21].CBDR.R = 0;EMIOS_0.CH[22].CBDR.R =leftSpeed;}
		else {EMIOS_0.CH[21].CBDR.R = -leftSpeed;EMIOS_0.CH[22].CBDR.R =-0;}//左轮  E5左退   E6左进
	if(rightSpeed>=0) {EMIOS_0.CH[19].CBDR.R = rightSpeed;EMIOS_0.CH[20].CBDR.R = 0;}
		else {EMIOS_0.CH[19].CBDR.R = 0;EMIOS_0.CH[20].CBDR.R = -rightSpeed;}//右轮  E3右进   E4右退
}
/*************************速度控制函数*********************/
void Speed_control(void)
{
	RPID=CENTER-Steer_PWM[3];
	r=Speed_kc/RPID;
	tsr=((r-wheel_distance)/r)*targetspeed;//右轮减速
	tsl=((r+wheel_distance+2)/r)*targetspeed;//左轮加速
	SET_motor(tsl,tsr);
}

