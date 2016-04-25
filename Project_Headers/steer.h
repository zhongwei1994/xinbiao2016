/*
 * steer.h
 *
 *  Created on: Mar 13, 2016
 *      Author: zhongwei
 */

#ifndef STEER_H_
#define STEER_H_

#define RIGHT 3470//�Ҽ��޽Ƕ�Ϊ3750
#define LEFT 4345//���޽Ƕ�Ϊ4200

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
