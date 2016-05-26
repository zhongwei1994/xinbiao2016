/*
 * strategy.h
 *
 *  Created on: May 24, 2016
 *      Author: lenovo
 */

#ifndef STRATEGY_H_
#define STRATEGY_H_

extern unsigned char s_data,lamp_turn;
extern unsigned char switch_flag;  //转换标志位

void Strategy_Switch();
void Strategy_Judge();
void Strategy_Input();
#endif /* STRATEGY_H_ */
