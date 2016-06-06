/*
 * includes.h
 *
 *  Created on: Mar 7, 2016
 *      Author: zhongwei
 */
#ifndef INCLUDES_H_
#define INCLUDES_H_

#ifndef _TYPEDEF_BYTE_
#define _TYPEDEF_BYTE_
typedef unsigned char BYTE;
#endif

#ifndef _TYPEDEF_SBYTE_
#define _TYPEDEF_SBYTE_
typedef signed char SBYTE;
#endif

#ifndef _TYPEDEF_WORD_
#define _TYPEDEF_WORD_
typedef unsigned short WORD;
#endif

#ifndef _TYPEDEF_SWORD_
#define _TYPEDEF_SWORD_
typedef signed short SWORD;
#endif

#ifndef _TYPEDEF_DWORD_
#define _TYPEDEF_DWORD_
//typedef unsigned int DWORD;
typedef unsigned long int DWORD;
#endif

#include "MPC5604B.h"

#include "init.h"
#include "delay.h"
#include "IntcInterrupts.h"
#include "string.h"
#include "oled.h"
#include "video.h"
#include "debug.h"
#include "sci.h"
#include "speed.h"
#include "steer.h"
#include "analysis.h"
#include "supersonic.h"
#include "capture.h"
#include "pit.h"
#include "SD.h"
#include "strategy.h"

#define ABS(x)              ((x) > 0 ? (x) : 0-(x))

extern int PixelLeft[128];
extern int PixelRight[128];

extern int FLAG;
extern int pwm_num_max;
extern int pwm_num_precision;
extern int pwm_num;

/***************bee*****************/
#define BEE  SIU.GPDO[73].R

/***************keys*****************/
#define S6 SIU.GPDI[15].R
#define S5 SIU.GPDI[39].R
#define S4 SIU.GPDI[14].R	
#define S3 SIU.GPDI[13].R

/***************led*****************/
#define LED0 SIU.GPDO[12].R
#define LED1 SIU.GPDO[13].R
#define LED2 SIU.GPDO[14].R
#define LED3 SIU.GPDO[15].R

/***************BEE	*****************/
#define BEE	SIU.GPDO[73].R

#define Y0 SIU.GPDI[56].R
#define Y1 SIU.GPDI[55].R
#define Y2 SIU.GPDI[50].R
#define Y3 SIU.GPDI[49].R
#define Y4 SIU.GPDI[52].R
#define Y5 SIU.GPDI[51].R
#define Y6 SIU.GPDI[54].R
#define Y7 SIU.GPDI[53].R

#define X0 SIU.GPDI[11].R
#define X1 SIU.GPDI[10].R
#define X2 SIU.GPDI[6].R
#define X3 SIU.GPDI[66].R
#define X4 SIU.GPDI[76].R
#define X5 SIU.GPDI[5].R
#define X6 SIU.GPDI[9].R
#define X7 SIU.GPDI[3].R

/***************steer*****************/
#define TargetSteer EMIOS_0.CH[4].CBDR.R // ���ֵ
#define CENTER 3848//3827//3867//3845//3890
/***************speed*****************/
#define backwardleft SIU.GPDI[47].R		//����⳵ʵ�ʷ���: 0��ǰ�� 1����
#define backwardright SIU.GPDI[41].R	//����⳵ʵ�ʷ���: 0��ǰ�� 1�ҵ���
///***************supersonic*****************/
//#define supersonic_0_trigger SIU.GPDO[31].R //����0
//#define supersonic_1_trigger SIU.GPDO[28].R//����1
/***************stm*****************/
#define TIME STM.CNT.R

#endif /* INCLUDES_H_ */


