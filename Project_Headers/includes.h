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
#include "SD.h"

#define ABS(x)              ((x) > 0 ? (x) : 0-(x))

extern int PixelLeft[128];
extern int PixelRight[128];

extern int FLAG;
extern int pwm_num_max;
extern int pwm_num_precision;
extern int pwm_num;

/***************bee*****************/
#define Bee  SIU.GPDO[0].R

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

#define Y0 SIU.GPDI[56].R
#define Y1 SIU.GPDI[55].R
#define Y2 SIU.GPDI[50].R
#define Y3 SIU.GPDI[49].R
#define Y4 SIU.GPDI[52].R
#define Y5 SIU.GPDI[51].R
#define Y6 SIU.GPDI[54].R
#define Y7 SIU.GPDI[53].R

/***************steer*****************/
#define TargetSteer EMIOS_0.CH[4].CBDR.R // ¶æ»úÖµ
#define CENTER 3905

///***************supersonic*****************/
//#define supersonic_0_trigger SIU.GPDO[31].R //³¬Éù0
//#define supersonic_1_trigger SIU.GPDO[28].R//³¬Éù1
/***************stm*****************/
#define TIME STM.CNT.R

#endif /* INCLUDES_H_ */


