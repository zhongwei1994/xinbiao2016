/*
 * strategy.c
 *
 *  Created on: May 24, 2016
 *      Author: lenovo
 */

#include "includes.h"

unsigned char s_data=31;
unsigned char S[5]={0,0,0,0,0};
unsigned char lamp_turn=5;   //灯的序号
unsigned char switch_flag=0;  //转换标志位

void Strategy_Switch(void)  //灯塔切换
{
	if(switch_flag==1)
	{
		switch_flag=0;
		lamp_turn++;
		if(lamp_turn>=5)
			lamp_turn=0;
	}
}
void Strategy_Judge(void)  //判断左右转
{
	if(S[lamp_turn]==0)     //左转
	{
		SteerControl_left();
	}
	else                    //右转
	{
		SteerControl_right();
	}
}

void Strategy_Input(void)  //输入策略值
{
	switch(s_data){
	case 0:
	    {S[4]=0;S[3]=0;S[2]=0;S[1]=0;S[0]=0;break;}
	case 1:
		{S[4]=0;S[3]=0;S[2]=0;S[1]=0;S[0]=1;break;}
	case 2:
	    {S[4]=0;S[3]=0;S[2]=0;S[1]=1;S[0]=0;break;}
	case 3:
		{S[4]=0;S[3]=0;S[2]=0;S[1]=1;S[0]=1;break;}
	case 4:
		{S[4]=0;S[3]=0;S[2]=1;S[1]=0;S[0]=0;break;}
	case 5:
		{S[4]=0;S[3]=0;S[2]=1;S[1]=0;S[0]=1;break;}
	case 6:
		{S[4]=0;S[3]=0;S[2]=1;S[1]=1;S[0]=0;break;}
	case 7:
		{S[4]=0;S[3]=0;S[2]=1;S[1]=1;S[0]=1;break;}
	case 8:
		{S[4]=0;S[3]=1;S[2]=0;S[1]=0;S[0]=0;break;}
	case 9:
		{S[4]=0;S[3]=1;S[2]=0;S[1]=0;S[0]=1;break;}
	case 10:
		{S[4]=0;S[3]=1;S[2]=0;S[1]=1;S[0]=0;break;}
	case 11:
		{S[4]=0;S[3]=1;S[2]=0;S[1]=1;S[0]=1;break;}
	case 12:
		{S[4]=0;S[3]=1;S[2]=1;S[1]=0;S[0]=0;break;}
	case 13:
		{S[4]=0;S[3]=1;S[2]=1;S[1]=0;S[0]=1;break;}
	case 14:
		{S[4]=0;S[3]=1;S[2]=1;S[1]=1;S[0]=0;break;}
	case 15:
		{S[4]=0;S[3]=1;S[2]=1;S[1]=1;S[0]=1;break;}
	case 16:
		{S[4]=1;S[3]=0;S[2]=0;S[1]=0;S[0]=0;break;}
	case 17:
		{S[4]=1;S[3]=0;S[2]=0;S[1]=0;S[0]=1;break;}
	case 18:
		{S[4]=1;S[3]=0;S[2]=0;S[1]=1;S[0]=0;break;}
	case 19:
		{S[4]=1;S[3]=0;S[2]=0;S[1]=1;S[0]=1;break;}
	case 20:
		{S[4]=1;S[3]=0;S[2]=1;S[1]=0;S[0]=0;break;}
	case 21:
		{S[4]=1;S[3]=0;S[2]=1;S[1]=0;S[0]=1;break;}
	case 22:
		{S[4]=1;S[3]=0;S[2]=1;S[1]=1;S[0]=0;break;}
	case 23:
		{S[4]=1;S[3]=0;S[2]=1;S[1]=1;S[0]=1;break;}
	case 24:
		{S[4]=1;S[3]=1;S[2]=0;S[1]=0;S[0]=0;break;}
	case 25:
		{S[4]=1;S[3]=1;S[2]=0;S[1]=0;S[0]=1;break;}
	case 26:
		{S[4]=1;S[3]=1;S[2]=0;S[1]=1;S[0]=0;break;}
	case 27:
		{S[4]=1;S[3]=1;S[2]=0;S[1]=1;S[0]=1;break;}
	case 28:
		{S[4]=1;S[3]=1;S[2]=1;S[1]=0;S[0]=0;break;}
	case 29:
		{S[4]=1;S[3]=1;S[2]=1;S[1]=0;S[0]=1;break;}
	case 30:
		{S[4]=1;S[3]=1;S[2]=1;S[1]=1;S[0]=0;break;}
	case 31:
		{S[4]=1;S[3]=1;S[2]=1;S[1]=1;S[0]=1;break;}
		
	}
}
