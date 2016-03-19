/*
 * analysis.c

 *
 *  Created on: Mar 15, 2016
 *      Author: zhongwei
 */

#include "includes.h"

byte pix_x=0,pix_y=0;
byte pix_x2=0,pix_y2=0;
byte wrong_flag=0;

//a_pix 80*100

void lamp_search(byte *pix_i,byte *pix_j)
{
	byte i = 0,j = 0,wrong_flag = 0;
	for(i = 10;i < 80;i+=10)
	{
		for(j = 10;j < 100;j+=10)
		{
			if(a_pix[i][j] > video_t)
			{
				if(lamp_judge(i,j))
				{
					*pix_i = i;
				    *pix_j = j;
				    return;
				}
			}
		}
	}
	for(i = 5;i < 80;i+=10)
	{
		for(j = 5;j < 100;j+=5)
		{
			if(a_pix[i][j] > video_t)
			{
				if(lamp_judge(i,j))
				{
					*pix_i = i;
					*pix_j = j;
					return;
				}
			}	
		}
	}
	for(i = 10;i < 80;i+=10)
	{
		for(j = 5;j < 100;j+=10)
		{
			if(a_pix[i][j] > video_t)
			{
				if(lamp_judge(i,j))
				{
					*pix_i = i;
					*pix_j = j;
					return;
				}
			}	
		}
	}	
	
	for(i = 2;i < 80;i+=2)
	{
		for(j = 2;j < 100;j+=2)
		{
			if(a_pix[i][j] > video_t)
			{
				if(lamp_judge(i,j))
				{
					*pix_i = i;
					*pix_j = j;
					return;
				}
			}	
		}
	}
	wrong_flag=1;
}
int lamp_judge(byte pix_i,byte pix_j)
{
	
	//int m;
	//if(a_pix[i][j+4]>240&&a_pix[i][j-4]>240&&a_pix[i+4][j]>240&&a_pix[i-4][j]>240)
	//    m=4;
	//if((a_pix[i][j+4]>240&&a_pix[i][j-4]>240&&a_pix[i+4][j]>240&&a_pix[i-4][j]<240)||(a_pix[i][j+4]>240&&a_pix[i][j-4]>240&&a_pix[i+4][j]<240&&a_pix[i-4][j]>240)||(a_pix[i][j+4]>240&&a_pix[i][j-4]<240&&a_pix[i+4][j]>240&&a_pix[i-4][j]>240)||(a_pix[i][j+4]<240&&a_pix[i][j-4]>240&&a_pix[i+4][j]>240&&a_pix[i-4][j]>240))
	//	m=3;
	//if((a_pix[i][j+4]>240&&a_pix[i][j-4]>240&&a_pix[i+4][j]<240&&a_pix[i-4][j]<240)||(a_pix[i][j+4]>240&&a_pix[i][j-4]<240&&a_pix[i+4][j]>240&&a_pix[i-4][j]<240)||(a_pix[i][j+4]>240&&a_pix[i][j-4]<240&&a_pix[i+4][j]<240&&a_pix[i-4][j]>240)||(a_pix[i][j+4]<240&&a_pix[i][j-4]>240&&a_pix[i+4][j]>240&&a_pix[i-4][j]<240)||(a_pix[i][j+4]<240&&a_pix[i][j-4]>240&&a_pix[i+4][j]<240&&a_pix[i-4][j]>240)||(a_pix[i][j+4]<240&&a_pix[i][j-4]<240&&a_pix[i+4][j]>240&&a_pix[i-4][j]>240))
	//	m=2;
	//if((a_pix[i][j+4]>240&&a_pix[i][j-4]<240&&a_pix[i+4][j]<240&&a_pix[i-4][j]<240)||(a_pix[i][j+4]<240&&a_pix[i][j-4]>240&&a_pix[i+4][j]<240&&a_pix[i-4][j]<240)||(a_pix[i][j+4]<240&&a_pix[i][j-4]<240&&a_pix[i+4][j]>240&&a_pix[i-4][j]<240)||(a_pix[i][j+4]<240&&a_pix[i][j-4]<240&&a_pix[i+4][j]<240&&a_pix[i-4][j]>240))
	//	m=1;
	
	int i,j,p=0;
	int flag=0;
	for(i=pix_i-1;i<=pix_i+1;i++)
	{
		for(j=pix_j-2;j<=pix_j+2;j++)
		{
		if(a_pix[i][j]>video_t)
			p++;
		}	
	}
	if(p>3)
	{
		flag=1;
	}
	return flag;
}

void central_search(byte *pix_i,byte *pix_j,byte x,byte y)
{
	byte i,j;
	byte left,right,pix_deltax,up,down,pix_deltay;
	for(i=x;i<=100;i++)
	{
		if(a_pix[i+3][y] - a_pix[i][y] <- 80)
			if(a_pix[i+4][y] - a_pix[i+1][y] <- 80)
						right = i+1;
		break;
	}
	for(i=x;i>=0;i--)
	{
		if(a_pix[i-3][y] - a_pix[i][y] <- 80)
			if(a_pix[i-4][y] - a_pix[i+1][y] <- 80)
						left = i+1;
		break;
	}
	pix_deltax = (right+left)/2;
	for(j=y;j<=80;j++)
	{
		if(a_pix[x][j+3] - a_pix[x][j] <- 80)
			if(a_pix[x][j+4] - a_pix[x][j+1] <- 80)
					    up = j+1;
		break;
	}
	for(j=y;j>=0;j--)
	{
		if(a_pix[x][j-3] - a_pix[x][j] <- 80)
			if(a_pix[x][j-4] - a_pix[x][j+1] <- 80)
					    down = j+1;
		break;
	}
	pix_deltay=(up+down)/2;
	*pix_i=pix_deltax;
	*pix_j=pix_deltay;
}
byte point_search(byte *pix_i,byte *pix_j,byte m,byte n)
{
	//byte flag=0;
	byte i,j;
	for(i=m;i < 80;i+=8)
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
	i=7;j=7;
	if(point_search(pix_i,pix_j,i,j))
		return;
	i=3;j=3;
	if(point_search(pix_i,pix_j,i,j))
		return;
	i=7;j=3;
	if(point_search(pix_i,pix_j,i,j))
		return;
	i=3;j=7;
	if(point_search(pix_i,pix_j,i,j))
		return;
	i=5;j=5;
	if(point_search(pix_i,pix_j,i,j))
		return;
	i=1;j=1;
	if(point_search(pix_i,pix_j,i,j))
		return;
	i=1;j=5;
	if(point_search(pix_i,pix_j,i,j))
		return;
	i=5;j=1;
	if(point_search(pix_i,pix_j,i,j))
		return;
	i=3;j=5;
	if(point_search(pix_i,pix_j,i,j))
		return;
	i=3;j=1;
	if(point_search(pix_i,pix_j,i,j))
		return;
	i=5;j=3;
	if(point_search(pix_i,pix_j,i,j))
		return;
	i=1;j=3;
	if(point_search(pix_i,pix_j,i,j))
		return;
	i=5;j=7;
	if(point_search(pix_i,pix_j,i,j))
		return;
	i=7;j=5;
	if(point_search(pix_i,pix_j,i,j))
		return;
	i=7;j=1;
	if(point_search(pix_i,pix_j,i,j))
		return;
	i=1;j=7;
	if(point_search(pix_i,pix_j,i,j))
		return;
}
