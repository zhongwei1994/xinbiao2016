/*
 * analysis.c
 *
 *  Created on: Mar 15, 2016
 *      Author: zhongwei
 */

#include "includes.h"

byte pix_x=0,pix_y=0;
byte pix_x2=0,pix_y2=0;

//a_pix 80*100

void lamp_search(byte *pix_i,byte *pix_j)
{
	byte i = 0,j = 0,search_flag = 0;
	for(i = 10;i < 80;i+=10)
	{
		for(j = 10;j < 100;j+=10)
		{
			if(a_pix[i][j] > video_t)
			{
				*pix_i = i;
				*pix_j = j;
				return;
			}
		}
	}
	for(i = 5;i < 80;i+=10)
	{
		for(j = 5;j < 100;j+=5)
		{
			if(a_pix[i][j] > video_t)
			{
				*pix_i = i;
				*pix_j = j;
				return;
			}	
		}
	}
	for(i = 10;i < 80;i+=10)
	{
		for(j = 5;j < 100;j+=10)
		{
			if(a_pix[i][j] > video_t)
			{
				*pix_i = i;
				*pix_j = j;
				return;
			}	
		}
	}	
	
	for(i = 2;i < 80;i+=2)
	{
		for(j = 2;j < 100;j+=2)
		{
			if(a_pix[i][j] > video_t)
			{
				*pix_i = i;
				*pix_j = j;
				return;
			}	
		}
	}
}
void lamp_judge(byte *pix_x,byte *pix_y)
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
	for(i=pix_x-3;i<=pix_x+3;i++)
	{
		for(j=n-3;j<=n+3;j++)
		{
		if(a_pix[i][j]>240)
			p++;
		}	
	}
	if(p>5)
	{
		*pix_i=m;
		*pix_y=n;
	}

