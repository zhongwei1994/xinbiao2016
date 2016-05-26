/*
 * analysis.c

 *
 *  Created on: Mar 15, 2016
 *      Author: wushun
 */
//Ŀ��׷Ѱ
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
	for(i=pix_i-2;i<=pix_i+2;i++)
	{
		for(j=pix_j-1;j<=pix_j+1;j++)
		{
			if(a_pix[i][j]>video_t2)
				p2++;
//			if(a_pix[i][j]>video_t)
//				p++;
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
	if(x<10)
	{
		*pix_i=x;
		*pix_j=y;
	}
	else
	{
		for(j=y;j<=100;j++)
		{
			if(a_pix[x][j]<video_t)//130Ϊ�жϺڰ׽������ֵ���ɸ��ģ���ͬ
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
			if(a_pix[i][y]<video_t)
			{
				down=i-1;
				break;
			}
		}
		for(i=x;i>=0;i--)
		{
			if(a_pix[i][y]<video_t)
			{
				up=i+1;
				break;
			}
		}
//		if(*pix_i>=40&&(up+down)/2<40)//��������⵽40����ʱ�����������½���40���£���ֹ���pֵ���ٶȲ���
//		{
//			*pix_i=40;
//		}
//		else
//		{
			*pix_i=(up+down)/2;
			*pix_j=(left+right)/2;
//		}
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
byte point_search_2(byte *pix_i,byte *pix_j)
{
	//byte flag=0;
	byte i,j;
	for(i=0;i < 40;i+=2)
	{
		for(j=0;j < 100;j++)
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
//����Ϊ������ʱ��������ɨ��
byte point_search_3(byte *pix_i,byte *pix_j,byte m,byte n)
{
	//byte flag=0;
	byte i,j;
	for(i=80-m;i > 32;i-=8)
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
void lamp_search(byte *pix_i,byte *pix_x2,byte *pix_y2)
{
	if(*pix_i>35)
	{
		lamp_search_1(pix_x2,pix_y2);
		if(wrong_flag)
			lamp_search_2(pix_x2,pix_y2);
	}
	else
		lamp_search_2(pix_x2,pix_y2);
	
}
void lamp_search_1(byte *pix_i,byte *pix_j)
{
	if(point_search_3(pix_i,pix_j,7,7))
		return;
	if(point_search_3(pix_i,pix_j,3,3))
		return;
	if(point_search_3(pix_i,pix_j,7,3))
		return;
	if(point_search_3(pix_i,pix_j,3,7))
		return;
	if(point_search_3(pix_i,pix_j,5,5))
		return;
	if(point_search_3(pix_i,pix_j,1,1))
		return;
	if(point_search_3(pix_i,pix_j,1,5))
		return;
	if(point_search_3(pix_i,pix_j,5,1))
		return;
	wrong_flag=1;
}
void lamp_search_2(byte *pix_i,byte *pix_j)
{
	//line��ֵ�ĵ������ݣ��ô�ɨ���LineΪǰһ�θպ���ɨ�赽ʱ�İ�ɫ��������ֵ
	if(point_search(pix_i,pix_j,7,7,80))
		return;
	if(point_search(pix_i,pix_j,3,3,80))
		return;
	if(point_search(pix_i,pix_j,7,3,70))
		return;
	if(point_search(pix_i,pix_j,3,7,70))
		return;
	if(point_search(pix_i,pix_j,5,4,60))
		return;
	if(point_search(pix_i,pix_j,1,0,60))
		return;
	if(point_search(pix_i,pix_j,1,4,50))
		return;
	if(point_search(pix_i,pix_j,5,0,50))
		return;
	if(point_search(pix_i,pix_j,3,5,50))
		return;
	if(point_search(pix_i,pix_j,3,1,40))
		return;
	if(point_search(pix_i,pix_j,7,1,40))
		return;
	if(point_search(pix_i,pix_j,7,5,40))
		return;
	if(point_search(pix_i,pix_j,1,2,40))
		return;
	if(point_search(pix_i,pix_j,1,6,40))
		return;
	if(point_search(pix_i,pix_j,5,2,40))
		return;
	if(point_search(pix_i,pix_j,5,6,40))
		return;
	//����ʮ�����ʼ������ȻѰ�Ҳ���ʱ������ʮ�������꽫��Ϊ����
	if(point_search(pix_i,pix_j,1,1,40))
		return;
	if(point_search(pix_i,pix_j,1,3,40))
		return;
	if(point_search(pix_i,pix_j,1,5,40))
		return;
	if(point_search(pix_i,pix_j,1,7,40))
		return;
	if(point_search(pix_i,pix_j,3,0,40))
		return;
	if(point_search(pix_i,pix_j,3,2,40))
		return;
	if(point_search(pix_i,pix_j,3,4,40))
		return;
	if(point_search(pix_i,pix_j,3,6,40))
		return;
	if(point_search(pix_i,pix_j,5,1,40))
		return;
	if(point_search(pix_i,pix_j,5,3,40))
		return;
	if(point_search(pix_i,pix_j,5,5,40))
		return;
	if(point_search(pix_i,pix_j,5,7,40))
		return;
	if(point_search(pix_i,pix_j,7,0,40))
		return;
	if(point_search(pix_i,pix_j,7,2,40))
		return;
	if(point_search(pix_i,pix_j,7,4,40))
		return;
	if(point_search(pix_i,pix_j,7,6,40))
		return;
	//�������16��������Ȼ�Ҳ����������ǰ40��ʣ�����е�
	if(point_search_2(pix_i,pix_j))
		return;
	wrong_flag=1;
}
//void lamp_search_far_near(byte *pix_i,byte *pix_j)
//{
//	lamp_search_2(&pix_x2,&pix_y2,video_t);
//	if(pix_x2==79&&pix_y2==0)
//	{
//		lamp_search_2(&pix_x2,&pix_y2,video_t2);
//		if(pix_x2==79&&pix_y2==0)
//		{
//				
//		}		
//	}
//}
