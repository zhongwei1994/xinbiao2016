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
					if(a_pix[i][j+6] - a_pix[i][j+2] > 80)
						if(a_pix[i][j+7] - a_pix[i][j+3] > 80)
							left[n] = j+4;
			
			if(a_pix[i][j+4] - a_pix[i][j] < -80)
						if(a_pix[i][j+5] - a_pix[i][j+1] < -80)
							if(a_pix[i][j+6] - a_pix[i][j+2] < -80)
								if(a_pix[i][j+7] - a_pix[i][j+3] < -80)
									right[n] = j+3;	
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

void search_central(int *pix_x,int *pix_y)
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
	
	int i,j,m,n,p=0;
	for(i=m-3;i<=m+3;i++)
	{
		for(j=n-3;j<=n+3;j++)
		{
		if(a_pix[i][j]>240)
			p++;
		}	
	}
	if(p>5)
	{
		*pix_x=m;
		*pix_y=n;
	}
	
}

