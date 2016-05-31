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
void SpeedControl2(void);

extern byte backflag;
extern int csl,csr;
extern int tsl,tsr;
extern int targetspeed;
extern int cyclespeed,straightspeed,turnspeed;
extern int cyclespeedleft,cyclespeedright;
extern byte cycle_flag;

extern double Speed_kp_Left,Speed_ki_Left,Speed_kd_Left;
extern double Speed_kp_Right,Speed_ki_Right,Speed_kd_Right;	//µç»úPID


#endif /* SPEED_H_ */
