/*
 * steer.h
 *
 *  Created on: Mar 13, 2016
 *      Author: zhongwei
 */

#ifndef STEER_H_
#define STEER_H_

#define RIGHT 3550
#define LEFT 4200

extern int target_offset,last_offset;
extern unsigned int Steer_PWM[4];

void SET_steer(unsigned int steer);
extern void Steer_PDSet(void);
extern void SteerControl(void);
extern byte BarrierJudge(void);


#endif /* STEER_H_ */
