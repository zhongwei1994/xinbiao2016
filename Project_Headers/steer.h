/*
 * steer.h
 *
 *  Created on: Mar 13, 2016
 *      Author: zhongwei
 */

#ifndef STEER_H_
#define STEER_H_

#define RIGHT 3470//右极限角度为3750
#define LEFT 4345//左极限角度为4200

extern byte wrong_count;
extern byte success;
extern byte close_supersonic;
extern byte cyclespeed;
extern int target_offset,last_offset;
extern unsigned int Steer_PWM[4];

void SET_steer(unsigned int steer);
extern void Steer_PDSet(void);
extern void SteerControl(void);
extern byte BarrierJudge(void);


#endif /* STEER_H_ */
