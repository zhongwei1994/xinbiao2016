/*
 * speed.h
 *
 *  Created on: Mar 13, 2016
 *      Author: zhongwei
 */

#ifndef SPEED_H_
#define SPEED_H_

void SET_motor(int leftSpeed,int rightSpeed);
void SpeedCount(void);
void SpeedControl(void);

extern int csl,csr;
extern int tsl,tsr;
extern int targetspeed;
extern byte cyclespeed,straightspeed;;

extern double Speed_kp_Left,Speed_ki_Left,Speed_kd_Left;
extern double Speed_kp_Right,Speed_ki_Right,Speed_kd_Right;	//���PID


#endif /* SPEED_H_ */
