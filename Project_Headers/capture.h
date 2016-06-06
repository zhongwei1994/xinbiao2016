/*
 * capture.h
 *
 *  Created on: Jun 6, 2016
 *      Author: lenovo
 */

#ifndef CAPTURE_H_
#define CAPTURE_H_

#define CCDR_SI  SIU.GPDO[34].R   //定义右线性传感器的端口 SI  C2
#define CCDR_CLK SIU.GPDO[36].R   //定义右线性传感器的端口 CLK C4

extern int A[128];
extern int ccd_barrier_flag;

void ImageCapture(int R[]);
void ccd_capture(void);
void barrier_avoid(void);

#endif /* CAPTURE_H_ */
