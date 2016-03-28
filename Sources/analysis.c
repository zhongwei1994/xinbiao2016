/*
 * analysis.c

 *
 *  Created on: Mar 15, 2016
 *      Author: zhongwei
 */

#include "includes.h"

byte pix_x=0,pix_y=0;
byte pix_x2=0,pix_y2=0;
byte pix_i=0,pix_j=0;
byte wrong_flag=0;

//a_pix 80*100

int lamp_judge(byte pix_i,byte pix_j)
{	
	int i,j,p=0,p2=0;
	int flag=0;
	for(i=pix_i-1;i<=pix_i+1;i++)
	{
		for(j=pix_j-2;j<=pix_j+2;j++)
		{
			if(a_pix[i][j]>video_t2)
				p2++;
			if(a_pix[i][j]>video_t)
				p++;
		}	
	}
	if(p2>2)
	{
		flag=1;
	}
	return flag;
}
void central_search_2(byte *pix_i,byte *pix_j,byte x,byte y)
{
	byte left,right,up,down;
	byte i,j;
	if(x<40)
	{
		*pix_i=x;
		*pix_j=y;
	}
	else
	{
		for(j=y;j<=100;j++)
		{
			if(a_pix[x][j]<video_t)//130为判断黑白交界的阈值，可更改，下同
			{
				right=j-1;
				break;
			}
		}
		for(j=y;j>=0;j--)
		{
			if(a_pix[x][j]<video_t)
			{
				left=j+1;
				break;
			}
		}
		for(i=x;i<=80;i++)
		{
			if(a_pix[i][y]<130)
			{
				down=i-1;
				break;
			}
		}
		for(i=x;i>=0;i--)
		{
			if(a_pix[i][y]<130)
			{
				up=i+1;
				break;
			}
		}
		*pix_i=(up+down)/2;
		*pix_j=(left+right)/2;
	}
}
byte point_search(byte *pix_i,byte *pix_j,byte m,byte n,byte line)
{
	//byte flag=0;
	byte i,j;
	for(i=m;i < line;i+=8)
	{
		for(j=n;j < 100;j+=8)
		{
			if(a_pix[i][j] > video_t)
			{
				if(lamp_judge(i,j))
				{
					*pix_i = i;
				    *pix_j = j;
				    return 1;
				}
			}
		}
	}
	return 0;
}
void lamp_search_2(byte *pix_i,byte *pix_j)
{
	byte i,j;
	//line的值的调试依据：该次扫描的Line为前一次刚好能扫描到时的白色区域上限值
	if(point_search(pix_i,pix_j,7,7,80))
		return;
	if(point_search(pix_i,pix_j,3,3,80))
		return;
	if(point_search(pix_i,pix_j,7,3,70))
		return;
	if(point_search(pix_i,pix_j,3,7,70))
		return;
	if(point_search(pix_i,pix_j,5,5,60))
		return;
	if(point_search(pix_i,pix_j,1,1,60))
		return;
	if(point_search(pix_i,pix_j,1,5,50))
		return;
	if(point_search(pix_i,pix_j,5,1,50))
		return;
	if(point_search(pix_i,pix_j,3,5,50))
		return;
	if(point_search(pix_i,pix_j,3,1,40))
		return;
	if(point_search(pix_i,pix_j,5,3,40))
		return;
	if(point_search(pix_i,pix_j,1,3,40))
		return;
	if(point_search(pix_i,pix_j,5,7,40))
		return;
	if(point_search(pix_i,pix_j,7,5,40))
		return;
	if(point_search(pix_i,pix_j,7,1,40))
		return;
	if(point_search(pix_i,pix_j,1,7,40))
		return;
	wrong_flag=1;
	return;	
}
