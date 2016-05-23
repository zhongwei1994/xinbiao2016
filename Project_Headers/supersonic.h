/*
 * supersonic.h
 *
 *  Created on: Mar 31, 2016
 *      Author: lenovo
 */

#ifndef SUPERSONIC_H_
#define SUPERSONIC_H_

extern unsigned long distance1;
extern int OLED_distance1;
extern unsigned long distance2;
extern int OLED_distance2;
extern word distance_T;
extern byte barrier_left_flag,barrier_right_flag,blf_cnt;

void intc_get_supersonic_time_1(void);
void intc_get_supersonic_time_2(void);
extern void trigger_supersonic_1(void);
extern void trigger_supersonic_2(void);

#endif /* SUPERSONIC_H_ */
