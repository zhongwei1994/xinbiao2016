/*
 * init.h
 *
 *  Created on: Mar 7, 2016
 *      Author: zhongwei
 */

#ifndef INIT_H_
#define INIT_H_

void initALL(void);
void disableWatchdog(void);				//�ؿ��Ź�
void initModesAndClock(void);			//ʱ�ӳ�ʼ��80M
void initEMIOS_0MotorAndSteer(void);    //PWM��ʼ��:�������תE3��E4��E5��E6��������A11
void initEMIOS_0Image(void);
void enableIrq(void);
void initLINFlex_0_UART(void);
void init_supersonic(void);
void initTestIO(void);
void init_TFcard(void);
void initEMIOS_0ModulusCounter(void);
void initSTM(); 


#endif /* INIT_H_ */
