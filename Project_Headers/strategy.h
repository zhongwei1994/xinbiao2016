/*
 * strategy.h
 *
 *  Created on: May 24, 2016
 *      Author: lenovo
 */

#ifndef STRATEGY_H_
#define STRATEGY_H_

extern unsigned char s_data,lamp_turn,s_data1,s_data2,k_data,k_data1,k_data2,str[10],t[10];
extern unsigned char switch_flag;  //转换标志位

void Strategy_Switch();
void Strategy_Judge();
void Strategy_Input();
void Strategy_Input2();
void Strategy_Input3();
void keep_Input(void);
void keep_Input1(void);
void keep_Input2(void);
void straight(void);
#endif /* STRATEGY_H_ */
