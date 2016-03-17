/*
 * debug.c
 *
 *  Created on: Mar 13, 2016
 *      Author: zhongwei
 */

#include "includes.h"

unsigned char *send;
unsigned char putstring[]="Image";
unsigned int Ts=0;
unsigned int Ti=ROWS-1;
unsigned int Tj=0;
int CurrentSteer=0;

unsigned char S3_last=1;
unsigned char S4_last=1;
unsigned char S5_last=1;
unsigned char S6_last=1;
unsigned char keymode=0;

//********************************************************************************************************
//****************************************拨码开关函数*****************************************************
//********************************************************************************************************
//void ChooseMode(void)
//{
//	mode=15-(switch1*8+switch2*4+switch3*2+switch4);
//}
//********************************************************************************************************
//****************************************蓝牙发送函数*****************************************************
//********************************************************************************************************

///*************************蓝牙发送函数*********************/
//void BlueTx(void)                             //蓝牙发数据
//{
//	Ts=0;
//	send = putstring;
//	LINFlex_TX(*send++);
//}
///*************************蓝牙接口函数*********************/
//void LINFlex_TX(unsigned char data)
//{
//	LINFLEX_0.UARTSR.B.DTF=1;
//	LINFLEX_0.BDRL.B.DATA0=data;       //发送语句
//}
/////*************************蓝牙中断函数*********************/
//void LINFlex_TX_Interrupt(void)
//{
//	
//	unsigned char video='V';
//	switch(Ts){
//	case 0: if(*send!=0x00){
//				LINFlex_TX(*send++);
//				break;}
//			else{
//				Ts=1;
//				break;}
//	case 1:
//		LINFlex_TX(video);
//		Ts=2;
//		break;
//	case 2: 
//		LINFlex_TX(SendHexHigh(A[Ti][Tj]));        //发送左CCD图像
//		Ts=3;
//		break;
//	case 3: 
//		LINFlex_TX(SendHexLow(A[Ti][Tj]));
//		if(Ti>0)
//		{
//			Ti--;
//			Ts=2;
//		}
//		else
//		{
//			Ti=ROWS-1;
//			if(Tj<COLUMNS-1)
//			{
//				Tj++;
//				Ts=2;
//			}
//			else
//			{
//				Tj=0;
//				Ts=4;
//			}
//		}
//		break;
//	case 4:
////		send = putstring;
////		Ts=0;
//		break;	
//	}
//}


//********************************************************************************************************
//****************************************蓝牙发送函数2*****************************************************
//********************************************************************************************************
/*************************蓝牙接口函数*********************/
void LINFlex_TX(unsigned char data)
{
	LINFLEX_0.BDRL.B.DATA0=data;       //发送语句
	while(!LINFLEX_0.UARTSR.B.DTF){}
	LINFLEX_0.UARTSR.B.DTF=1;
}

void BlueTx(void)                             //蓝牙发数据
{
	unsigned char video='V';
	Ts=0;
	send = putstring;
	LINFlex_TX(*send++);
	for(Ts=0;Ts<5;)
	{
	switch(Ts){
	case 0: if(*send!=0x00){
				LINFlex_TX(*send++);
				break;}
			else{
				Ts=1;
				break;}
	case 1:
		LINFlex_TX(video);
		Ts=2;
		break;
	case 2: 
		LINFlex_TX(SendHexHigh(a_pix[Ti][Tj]));        //发送左CCD图像
		Ts=3;
		break;
	case 3: 
		LINFlex_TX(SendHexLow(a_pix[Ti][Tj]));
		if(Ti>0)
		{
			Ti--;
			Ts=2;
		}
		else
		{
			Ti=ROWS-1;
			if(Tj<COLUMNS-1)
			{
				Tj++;
				Ts=2;
			}
			else
			{
				Tj=0;
				Ts=4;
			}
		}
		break;
	case 4: 
		LINFlex_TX('X'); 
		LINFlex_TX(SendHexHigh(pix_x));        //发送白点坐标
		LINFlex_TX(SendHexLow(pix_x));
		LINFlex_TX(SendHexHigh(pix_y));
		LINFlex_TX(SendHexLow(pix_y));
		LINFlex_TX(SendHexHigh(pix_x2));        //发送白点坐标
		LINFlex_TX(SendHexLow(pix_x2));
		LINFlex_TX(SendHexHigh(pix_y2));
		LINFlex_TX(SendHexLow(pix_y2));
		Ts=5;
		break;
	}
	}
}

//********************************************************************************************************
//****************************************按键调试函数*****************************************************
//********************************************************************************************************

void KeyJudge(void)
{
	if(S3==0&&S3_last==1){   //按键S3按下
		keymode=1;
		TargetSteer+=100;
		//tsr-=10;
		}
	if(S4==0&&S4_last==1){   //按键S4按下
	    keymode=2;
	    TargetSteer-=100;
	    //tsr+=10;
	    }
	if(S5==0&&S5_last==1){   //按键S5按下
		keymode=3;
		TargetSteer+=5;
		//tsl-=10;
		}
	if(S6==0&&S6_last==1){   //按键S6按下
		keymode=4; 
		TargetSteer-=5;
		//tsl+=10;
		}
	S3_last=S3;             //保存按键的状态
	S4_last=S4;
	S5_last=S5;
	S6_last=S6;
}

