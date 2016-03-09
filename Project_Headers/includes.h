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
#include "delay.h"
#include "Bluetooth.h"
#include "oled.h"

extern int PixelLeft[128];
extern int PixelRight[128];

extern int FLAG;
extern int pwm_num_max;
extern int pwm_num_precision;
extern int pwm_num;

/***************bee*****************/
#define Bee  SIU.GPDO[0].R

/***************led*****************/
#define D0  SIU.GPDO[12].R
#define D1  SIU.GPDO[13].R
#define D2  SIU.GPDO[14].R
#define D3  SIU.GPDO[15].R

///***************supersonic*****************/
//#define supersonic_0_trigger SIU.GPDO[31].R //³¬Éù0
//#define supersonic_1_trigger SIU.GPDO[28].R//³¬Éù1

#endif /* INCLUDES_H_ */


