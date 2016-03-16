/*
 * analysis.c
 *
 *  Created on: Mar 15, 2016
 *      Author: zhongwei
 */

#include "includes.h"

//a_pix 80*100
void search_lamp(int *pix_x,int *pix_y)
{
	int pix_left,pix_right;
	int i = 0,j = 0,n = 0;
	int pix_delta[80] = {0},left[80] = {0},right[80] = {0},pix_delta_max = 0,i_max = 0;
	for(i = 80;i > 0;i--)
	{
		for(j = 0;j < 100;j++)
		{
			if(a_pix[i][j+4] - a_pix[i][j] > 80)
				if(a_pix[i][j+5] - a_pix[i][j+1] > 80)
					left[n] = j+4;
			
			if(a_pix[i][j+4] - a_pix[i][j] < -80)
				if(a_pix[i][j+5] - a_pix[i][j+1] < -80)
					right[n] = j;	
			pix_delta[n] = right[n] - left[n];
		}
		n++;
	}	
	pix_delta_max = pix_delta[0];
	i_max = 0;
	for(i = 0;i < 80;i++)
	{
		if(pix_delta_max < pix_delta[i])
		{
			pix_delta_max = pix_delta[i];
			i_max = i;		
		}
	}
	*pix_x = (right[i_max] + left[i_max])/2;
	*pix_y = i_max;
}
