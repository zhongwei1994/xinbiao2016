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
//**********************���ٲ���***************************/
signed int Speed_kc=15000;
signed int wheel_distance=9;//�복��8
signed int RPID=0;	
double r=0;

/*************************����ӿں���*********************/
void SET_motor(int leftSpeed,int rightSpeed)
{
	if(leftSpeed>=0) {EMIOS_0.CH[21].CBDR.R = 0;EMIOS_0.CH[22].CBDR.R =leftSpeed;}
		else {EMIOS_0.CH[21].CBDR.R = -leftSpeed;EMIOS_0.CH[22].CBDR.R =-0;}//����  E5����   E6���
	if(rightSpeed>=0) {EMIOS_0.CH[19].CBDR.R = rightSpeed;EMIOS_0.CH[20].CBDR.R = 0;}
		else {EMIOS_0.CH[19].CBDR.R = 0;EMIOS_0.CH[20].CBDR.R = -rightSpeed;}//����  E3�ҽ�   E4����
}
/*************************�ٶȿ��ƺ���*********************/
void Speed_control(void)
{
	RPID=CENTER-Steer_PWM[3];
	r=Speed_kc/RPID;
	tsr=((r-wheel_distance)/r)*targetspeed;//���ּ���
	tsl=((r+wheel_distance+2)/r)*targetspeed;//���ּ���
	SET_motor(tsl,tsr);
}

