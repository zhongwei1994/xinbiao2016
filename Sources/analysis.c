/*
 * analysis.c
 *
 *  Created on: Mar 15, 2016
 *      Author: zhongwei
 */

#include "includes.h"

//a_pix 80*100

int search_lamp(void)
{
	int pix_left,pix_right;
	int i = 0,j = 0,n = 0;
	int pix_delta[80] = {0},pix_delta_max = 0;
	for(i = 80;i > 0;i--)
	{
		for(j = 0;j < 100;j++)
		{
			if(a_pix[i][j+4] - a_pix[i][j] > 80)
				if(a_pix[i][j+5] - a_pix[i][j+1] > 80)
					if(a_pix[i][j+6] - a_pix[i][j+2] > 80)
						if(a_pix[i][j+7] - a_pix[i][j+3] > 80)
							pix_left = j+4;
			
			if(a_pix[i][j+4] - a_pix[i][j] < -80)
						if(a_pix[i][j+5] - a_pix[i][j+1] < -80)
							if(a_pix[i][j+6] - a_pix[i][j+2] < -80)
								if(a_pix[i][j+7] - a_pix[i][j+3] < -80)
									pix_right = j+3;	
			pix_delta[n] = pix_right - pix_left;
		}
		n++;
	}	
	pix_delta_max = pix_delta[0];
	for(i = 0;i < 80;i++)
	{
		if(pix_delta_max < pix_delta[i])
			pix_delta_max = pix_delta[i];
	}
	return pix_delta_max/2;
}



