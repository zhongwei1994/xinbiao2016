/*
 * analyse.c


 *
 *  Created on: Mar 14, 2016
 *      Author: WUSHUN
 */
#include "includes.h"
void central_point(int * pointx,int * pointy)
{
	int up=80,down,left=100,right=0,downflag=0;
	int i = 0,j = 0,n = 0;
	for(i = 80;i > 0;i--)
	{
		for(j = 0;j < 100;j++)
		{
			if(a_pix[i][j] > 200&&downflag==0)
				if(a_pix[i][j+2] < 150&&a_pix[i][j+3] < 150&&a_pix[i][j+4]<150
				       &&a_pix[i+1][j] >200&&a_pix[i+2][j] >200&&a_pix[i+3][j] >200)
					{
					down=i;
					downflag=1;
					}
				else if(a_pix[i][j] > 200)
				if(a_pix[i][j+1] >200&&a_pix[i][j+2] >200&&a_pix[i][j+3]>200
					   &&a_pix[i+2][j] <150&&a_pix[i+3][j] <150&&a_pix[i+4][j] <150)
					{
					if(left>j)
						left=j;
					}
				else if(a_pix[i][j] > 200)
				if(a_pix[i][j+1] <150&&a_pix[i][j+2] <150&&a_pix[i][j+3]<150
						&&a_pix[i+2][j] <150&&a_pix[i+3][j] <150&&a_pix[i+4][j] <150)
					{
					if(right<j)
						right=j;
					}	
				else if(a_pix[i][j] > 200)
								if(a_pix[i][j+1] <150&&a_pix[i][j+2] <150&&a_pix[i][j+3]<150
										&&a_pix[i+2][j] <150&&a_pix[i+3][j] <150&&a_pix[i+4][j] <150)
									{
									if(up>i)
										up=i;
									}
		}
	}
	*pointx=(left+right)/2;
	*pointy=(up+down)/2;
}


