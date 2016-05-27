/*
 * steer.h
 *
 *  Created on: Mar 13, 2016
 *      Author: zhongwei
 */

#ifndef STEER_H_
#define STEER_H_

#define RIGHT 3630//3430//右极限角度为3750   //3470
#define LEFT 4130//4330//左极限角度为4200 //4320

extern byte wrong_count;
extern byte aim,aim2;
extern byte success;
extern byte start_flag;
extern byte close_supersonic;
extern byte cycle_i,cycle_j,turnleft;
extern double target_offset,last_offset,Steer_kp;
extern unsigned int Steer_PWM[4];

void SET_steer(unsigned int steer);
void steer_error_left(void);
void steer_error_right(void);
extern void Steer_PDSet(void);
extern void SteerControl_left(void);
extern void SteerControl_right(void);
extern byte BarrierJudge(void);


#endif /* STEER_H_ */
