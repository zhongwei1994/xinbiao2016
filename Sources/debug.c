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

unsigned char RX_data=0;
unsigned char RX_flag=0;
unsigned char RX_i=0,RX_j=0;
int X[16]={0};
 unsigned char Y[25]={0},Z[11]={0};

unsigned char S3_last=1;
unsigned char S4_last=1;
unsigned char S5_last=1;
unsigned char S6_last=1;
unsigned char keymode=0;
unsigned long time1=0;
unsigned long time2=0;
unsigned long time3=0;
unsigned long time3_2=0;
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
	unsigned long temp; 
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
				Ts=4;
				break;}
	case 1:
		LINFlex_TX(video);
		Ts=2;
		break;
		//以下为发送图像数据
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
//		LINFlex_TX(SendHexHigh(pix_x));        //发送白点坐标
//		LINFlex_TX(SendHexLow(pix_x));
//		LINFlex_TX(SendHexHigh(pix_y));
//		LINFlex_TX(SendHexLow(pix_y));
//		LINFlex_TX(SendHexHigh(pix_x2));        //发送白点坐标
//		LINFlex_TX(SendHexLow(pix_x2));
//		LINFlex_TX(SendHexHigh(pix_y2));
//		LINFlex_TX(SendHexLow(pix_y2));
		LINFlex_TX(SendHexHigh(pix_i));
		LINFlex_TX(SendHexLow(pix_i));
		LINFlex_TX(SendHexHigh(pix_j));
		LINFlex_TX(SendHexLow(pix_j));
		//发送亮点周围10*10个点的灰度值
//		LINFlex_TX(SendHexHigh(a_pix[pix_i-1][pix_j-1]));
//		LINFlex_TX(SendHexLow(a_pix[pix_i-1][pix_j-1]));
//		LINFlex_TX(SendHexHigh(a_pix[pix_i-1][pix_j]));
//		LINFlex_TX(SendHexLow(a_pix[pix_i-1][pix_j]));
//		LINFlex_TX(SendHexHigh(a_pix[pix_i-1][pix_j+1]));
//		LINFlex_TX(SendHexLow(a_pix[pix_i-1][pix_j+1]));
//		LINFlex_TX(SendHexHigh(a_pix[pix_i][pix_j-1]));
//		LINFlex_TX(SendHexLow(a_pix[pix_i][pix_j-1]));
//		LINFlex_TX(SendHexHigh(a_pix[pix_i][pix_j]));
//		LINFlex_TX(SendHexLow(a_pix[pix_i][pix_j]));
//		LINFlex_TX(SendHexHigh(a_pix[pix_i][pix_j+1]));
//		LINFlex_TX(SendHexLow(a_pix[pix_i][pix_j+1]));
//		LINFlex_TX(SendHexHigh(a_pix[pix_i+1][pix_j-1]));
//		LINFlex_TX(SendHexLow(a_pix[pix_i+1][pix_j-1]));
//		LINFlex_TX(SendHexHigh(a_pix[pix_i+1][pix_j]));
//		LINFlex_TX(SendHexLow(a_pix[pix_i+1][pix_j]));
//		LINFlex_TX(SendHexHigh(a_pix[pix_i+1][pix_j+1]));
//		LINFlex_TX(SendHexLow(a_pix[pix_i+1][pix_j+1]));
		//发速度
		LINFlex_TX('Y'); 
		LINFlex_TX(SendInt1(csl));
		LINFlex_TX(SendInt2(csl));
		LINFlex_TX(SendInt3(csl));
		LINFlex_TX(SendInt4(csl));
		LINFlex_TX(SendInt1(csr));
		LINFlex_TX(SendInt2(csr));
		LINFlex_TX(SendInt3(csr));
		LINFlex_TX(SendInt4(csr));
//		LINFlex_TX(SendInt1(tsl));
//		LINFlex_TX(SendInt2(tsl));
//		LINFlex_TX(SendInt3(tsl));
//		LINFlex_TX(SendInt4(tsl));
		//发速度
//		LINFlex_TX(SendInt1(tsr));
//		LINFlex_TX(SendInt2(tsr));
//		LINFlex_TX(SendInt3(tsr));
//		LINFlex_TX(SendInt4(tsr));
		//发舵机值
//		CurrentSteer=TargetSteer;
//		LINFlex_TX(SendInt1(CurrentSteer));
//		LINFlex_TX(SendInt2(CurrentSteer));
//		LINFlex_TX(SendInt3(CurrentSteer));
//		LINFlex_TX(SendInt4(CurrentSteer));
		//发舵机值
//		LINFlex_TX(SendUnsignedLong1(time3));
//		LINFlex_TX(SendUnsignedLong2(time3));
//		LINFlex_TX(SendUnsignedLong3(time3));
//		LINFlex_TX(SendUnsignedLong4(time3));
//		LINFlex_TX(SendUnsignedLong5(time3));
//		LINFlex_TX(SendUnsignedLong6(time3));
//		LINFlex_TX(SendUnsignedLong7(time3));
//		LINFlex_TX(SendUnsignedLong8(time3));
//		LINFlex_TX(SendUnsignedLong1(time3_2));
//		LINFlex_TX(SendUnsignedLong2(time3_2));
//		LINFlex_TX(SendUnsignedLong3(time3_2));
//		LINFlex_TX(SendUnsignedLong4(time3_2));
//		LINFlex_TX(SendUnsignedLong5(time3_2));
//		LINFlex_TX(SendUnsignedLong6(time3_2));
//		LINFlex_TX(SendUnsignedLong7(time3_2));
//		LINFlex_TX(SendUnsignedLong8(time3_2));
		Ts=5;
		break;
	}
	}
}

void LINFlex_RX_Interrupt(void)
{
	RX_data=LINFLEX_0.BDRM.B.DATA4;
	if(RX_data==69)
	{
		switch(RX_flag){
		case 1:
			straightspeed=X[1]*100+X[2]*10+X[3];
			turnspeed=X[4]*100+X[4]*10+X[6];
			cyclespeed=X[7]*100+X[8]*10+X[9];
			cyclespeedleft=X[10]*100+X[11]*10+X[12];
			cyclespeedright=X[13]*100+X[14]*10+X[15];
			RX_flag=0;
			break;
		case 2:
			Speed_kp_Left=(double)(Y[1]*10+Y[2])+((double)(Y[3]*10+Y[4]))/100;
			Speed_ki_Left=(double)(Y[5]*10+Y[6])+((double)(Y[7]*10+Y[8]))/100;
			Speed_kd_Left=(double)(Y[9]*10+Y[10])+((double)(Y[11]*10+Y[12]))/100;
			Speed_kp_Right=(double)(Y[13]*10+Y[14])+((double)(Y[15]*10+Y[16]))/100;
			Speed_ki_Right=(double)(Y[17]*10+Y[18])+((double)(Y[19]*10+Y[20]))/100;
			Speed_kd_Right=(double)(Y[21]*10+Y[22])+((double)(Y[23]*10+Y[24]))/100;
			RX_flag=0;
			break;
		case 3:
			aim=Z[1]*10+Z[2];
			aim2=Z[3]*10+Z[4];
			cycle_i=Z[5]*10+Z[6];
			cycle_j=Z[7]*10+Z[8];
			s_data=Z[9]*10+Z[10];
			RX_flag=0;
			break;
		}
	}
	else if(RX_data==88)
	{
		RX_flag=1;
		RX_i=0;
	}
	else if(RX_data==89)
	{
		RX_flag=2;
		RX_i=0;
	}
	else if(RX_data==90)
	{
		RX_flag=3;
		RX_i=0;
	}
	switch(RX_flag){
	case 0:
		break;
	case 1:
		X[RX_i]=RX_data-48;
		RX_i++;
		break;
	case 2:
		Y[RX_i]=RX_data-48;
		RX_i++;
		break;
	case 3:
		Z[RX_i]=RX_data-48;
		RX_i++;
		break;
	}
	LINFLEX_0.UARTSR.B.DRF=1;
}

//********************************************************************************************************
//****************************************按键调试函数*****************************************************
//********************************************************************************************************

void KeyJudge(void)
{
	if(S3==0&&S3_last==1){   //按键S3按下
		keymode=1;
		aim-=1;
//		TargetSteer+=5;
		//straightspeed+=5;
		//SET_motor(straightspeed,straightspeed);
//		turnleft+=1;
		//tsr-=10;
		}
	if(S4==0&&S4_last==1){   //按键S4按下
	    keymode=2;
	    aim+=1;
//	    TargetSteer-=5;
//	    cyclespeed+=5;
//	    turnleft-=1;
	    //SET_motor(straightspeed,straightspeed);
	    //tsr+=10;
	    }
	if(S5==0&&S5_last==1){   //按键S5按下
		keymode=3;
		Steer_kp-=1;
//		cycle_j+=1;
		//SET_motor(straightspeed,straightspeed);
//		cyclespeedright+=10;
		//tsl-=10;
		}
	if(S6==0&&S6_last==1){   //按键S6按下
		keymode=4; 
		Steer_kp+=1;
//		cycle_j-=1;
		//SET_motor(straightspeed,straightspeed);
//		cyclespeedright-=10;
		//tsl+=10;
		}
	S3_last=S3;        //保存按键的状态
	S4_last=S4;
	S5_last=S5;
	S6_last=S6;
	
//	OLED_SetPointer(1,1);
//	OLED_Str("Motor: ");
//	OLED_Num(targetmotor);
}
//********************************************************************************************************
//****************************************程序计时函数*****************************************************
//********************************************************************************************************
unsigned long TimeMesure(void)
{
	if(time2<time1)
		return 0xFFFFFFFF+time2-time1;
	else
		return time2-time1;
}
