/*
 * pit.h
 *
 *  Created on: Apr 1, 2016
 *      Author: lenovo
 */

#ifndef PIT_H_
#define PIT_H_

void initPIT(void);
void PitISR(void);
void PitISR2(void);

extern unsigned int pitcount0,pitcount1,pitcount2,pitcount3,pitcount4,pitcount5,pitcount6;
extern byte OLEDdisplay_flag;
extern byte CCD_flag;


#endif /* PIT_H_ */
