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
extern int oled_csl,oled_csr;
extern double oled_cslcount,oled_csrcount;
extern int tsl,tsr;
extern int targetspeed;


#endif /* SPEED_H_ */
