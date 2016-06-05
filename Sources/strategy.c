/*
 * strategy.c
 *
 *  Created on: May 24, 2016
 *      Author: lenovo
 */

#include "includes.h"

unsigned char s_data=3,s_data1=3,s_data2=6,k_data=2,k_data1=2,k_data2=2;
unsigned char S[4]={0,0,0,0},S1[3]={0,0,0},S2[3]={0,0,0},k[4]={0,0,0,0},k1[3]={0,0,0},k2[3]={0,0,0};
unsigned char lamp_turn=10,lamp_turn1=0,lamp_turn2=0;   //灯的序号
unsigned char switch_flag=0;  //转换标志位

void Strategy_Switch(void)  //灯塔切换 
{
	if(switch_flag==1)
	{
		switch_flag=0;
		lamp_turn++;
		if(lamp_turn>=10)
			lamp_turn=0;
	}
}
void Strategy_Judge(void)  //判断左右转
{
	if(lamp_turn<=3)
	{
		if(S[lamp_turn]==0)     //左转
			SteerControl_left();
		else                    //右转
			SteerControl_right();
	}
	else if(lamp_turn<=6)
	{
		lamp_turn1=lamp_turn-4;
		if(S1[lamp_turn1]==0)     //左转
			SteerControl_left();
		else                    //右转
			SteerControl_right();
	}
	else
	{
		lamp_turn2=lamp_turn-7;
		if(S2[lamp_turn2]==0)     //左转
			SteerControl_left();
		else                    //右转
			SteerControl_right();
	}
}
void Strategy_Input(void)  //输入策略值
{
	switch(s_data)
	{
		case 0:
			{S[3]=0;S[2]=0;S[1]=0;S[0]=0;break;}
		case 1:
			{S[3]=0;S[2]=0;S[1]=0;S[0]=1;break;}
		case 2:
			{S[3]=0;S[2]=0;S[1]=1;S[0]=0;break;}
		case 3:
			{S[3]=0;S[2]=0;S[1]=1;S[0]=1;break;}
		case 4:
			{S[3]=0;S[2]=1;S[1]=0;S[0]=0;break;}
		case 5:
			{S[3]=0;S[2]=1;S[1]=0;S[0]=1;break;}
		case 6:
			{S[3]=0;S[2]=1;S[1]=1;S[0]=0;break;}
		case 7:
			{S[3]=0;S[2]=1;S[1]=1;S[0]=1;break;}
		case 8:
			{S[3]=1;S[2]=0;S[1]=0;S[0]=0;break;}
		case 9:
			{S[3]=1;S[2]=0;S[1]=0;S[0]=1;break;}
		case 10:
			{S[3]=1;S[2]=0;S[1]=1;S[0]=0;break;}
		case 11:
			{S[3]=1;S[2]=0;S[1]=1;S[0]=1;break;}
		case 12:
			{S[3]=1;S[2]=1;S[1]=0;S[0]=0;break;}
		case 13:
			{S[3]=1;S[2]=1;S[1]=0;S[0]=1;break;}
		case 14:
			{S[3]=1;S[2]=1;S[1]=1;S[0]=0;break;}
		case 15:
			{S[3]=1;S[2]=1;S[1]=1;S[0]=1;break;}
	}
}
void Strategy_Input2(void)
{
		switch(s_data1)
		{
		case 0:
		    {S1[2]=0;S1[1]=0;S1[0]=0;break;}
		case 1:
	    	{S1[2]=0;S1[1]=0;S1[0]=1;break;}
		case 2:
	    	{S1[2]=0;S1[1]=1;S1[0]=0;break;}
		case 3:
	    	{S1[2]=0;S1[1]=1;S1[0]=1;break;}
		case 4:
			{S1[2]=1;S1[1]=0;S1[0]=0;break;}
		case 5:
	    	{S1[2]=1;S1[1]=0;S1[0]=1;break;}
		case 6:
			{S1[2]=1;S1[1]=1;S1[0]=0;break;}
		case 7:
			{S1[2]=1;S1[1]=1;S1[0]=1;break;}
		}
}
void Strategy_Input3(void)
{
		switch(s_data2)
		{
		case 0:
		    {S2[2]=0;S2[1]=0;S2[0]=0;break;}
		case 1:
	    	{S2[2]=0;S2[1]=0;S2[0]=1;break;}
		case 2:
	    	{S2[2]=0;S2[1]=1;S2[0]=0;break;}
		case 3:
	    	{S2[2]=0;S2[1]=1;S2[0]=1;break;}
		case 4:
			{S2[2]=1;S2[1]=0;S2[0]=0;break;}
		case 5:
	    	{S2[2]=1;S2[1]=0;S2[0]=1;break;}
		case 6:
			{S2[2]=1;S2[1]=1;S2[0]=0;break;}
		case 7:
			{S2[2]=1;S2[1]=1;S2[0]=1;break;}
		}
}
void keep_Input(void)  //输入策略值
{
	switch(k_data)
	{
	case 0:
		{k[3]=0;k[2]=0;k[1]=0;k[0]=0;break;}
	case 1:
		{k[3]=0;k[2]=0;k[1]=0;k[0]=1;break;}
	case 2:
		{k[3]=0;k[2]=0;k[1]=1;k[0]=0;break;}
	case 3:
		{k[3]=0;k[2]=0;k[1]=1;k[0]=1;break;}
	case 4:
		{k[3]=0;k[2]=1;k[1]=0;k[0]=0;break;}
	case 5:
		{k[3]=0;k[2]=1;k[1]=0;k[0]=1;break;}
	case 6:
		{k[3]=0;k[2]=1;k[1]=1;k[0]=0;break;}
	case 7:
		{k[3]=0;k[2]=1;k[1]=1;k[0]=1;break;}
	case 8:
		{k[3]=1;k[2]=0;k[1]=0;k[0]=0;break;}
	case 9:
		{k[3]=1;k[2]=0;k[1]=0;k[0]=1;break;}
	case 10:
		{k[3]=1;k[2]=0;k[1]=1;k[0]=0;break;}
	case 11:
		{k[3]=1;k[2]=0;k[1]=1;k[0]=1;break;}
	case 12:
		{k[3]=1;k[2]=1;k[1]=0;k[0]=0;break;}
	case 13:
		{k[3]=1;k[2]=1;k[1]=0;k[0]=1;break;}
	case 14:
		{k[3]=1;k[2]=1;k[1]=1;k[0]=0;break;}
	case 15:
		{k[3]=1;k[2]=1;k[1]=1;k[0]=1;break;}
	}
}
void keep_Input1(void)
{
	switch(k_data1)
	{
	case 0:
		{k1[2]=0;k1[1]=0;k1[0]=0;break;}
	case 1:
		{k1[2]=0;k1[1]=0;k1[0]=1;break;}
	case 2:
		{k1[2]=0;k1[1]=1;k1[0]=0;break;}
	case 3:
		{k1[2]=0;k1[1]=1;k1[0]=1;break;}
	case 4:
		{k1[2]=1;k1[1]=0;k1[0]=0;break;}
	case 5:
		{k1[2]=1;k1[1]=0;k1[0]=1;break;}
	case 6:
		{k1[2]=1;k1[1]=1;k1[0]=0;break;}
	case 7:
		{k1[2]=1;k1[1]=1;k1[0]=1;break;}
	}
}
void keep_Input2(void)
{
	switch(k_data2)
	{
	case 0:
	    {k2[2]=0;k2[1]=0;k2[0]=0;break;}
	case 1:
    	{k2[2]=0;k2[1]=0;k2[0]=1;break;}
	case 2:
    	{k2[2]=0;k2[1]=1;k2[0]=0;break;}
	case 3:
    	{k2[2]=0;k2[1]=1;k2[0]=1;break;}
	case 4:
		{k2[2]=1;k2[1]=0;k2[0]=0;break;}
	case 5:
    	{k2[2]=1;k2[1]=0;k2[0]=1;break;}
	case 6:
		{k2[2]=1;k2[1]=1;k2[0]=0;break;}
	case 7:
		{k2[2]=1;k2[1]=1;k2[0]=1;break;}
	}
}
