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


#endif /* SPEED_H_ */
