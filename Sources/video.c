/*
 * video.c
 *
 *  Created on: Mar 13, 2016
 *      Author: zhongwei
 */

#include "includes.h"

//*************************************************************************
//*		 *************************采样变量*****************************   *
//*************************************************************************
//采样图像标号
word crow = 0;           //行计数器        
word trow = 1;            //选择采样行
word prow = 0;  	  	 //摄像头采样当前行
word pcolumn = 0;        //摄像头采样当前列
//采样结束标志
byte fieldover = 0;		//一场采样结束标志符 
//采样二维数组    
byte a_pix[ROWS][COLUMNS];   // 采集灰度数组

//*************************************************************************
//*   **************************中断函数****************************      *
//*************************************************************************
//void FieldInputCapture(void)	//捕捉场中断 
//{
//    EMIOS_0.CH[5].CCR.B.FEN=0;  //关闭场中断 
//	prow=0;pcolumn=0;
//	EMIOS_0.CH[6].CSR.B.FLAG = 1;
//	EMIOS_0.CH[6].CCR.B.FEN=1;  //开行中断
//}
//
//void RowInputCapture(void) 		//捕捉行中断
//{
//	EMIOS_0.CH[6].CSR.B.FLAG = 1;  //清除行中断
//	if(prow>ROWS-1)
//	{
//		EMIOS_0.CH[6].CCR.B.FEN=0; 	//关闭行中断
//		fieldover=1; //采样结束
//	}
//	else
//	{
//		for(pcolumn=0;pcolumn<COLUMNS;pcolumn++)
//		{
//			//a_pix[prow][pcolumn]=Y0+Y1<<1+Y2<<2+Y3<<3+Y4<<4+Y5<<5+Y6<<6+Y7<<7;
//			a_pix[prow][pcolumn]=Y0+Y1*2+Y2*4+Y3*8+Y4*16+Y5*32+Y6*64+Y7*128;
//		}
//		prow++;
//	}
//}

//*************************************************************************
//*   **************************中断函数2****************************      *
//*************************************************************************
void FieldInputCapture(void)	//捕捉场中断 
{
	EMIOS_0.CH[6].CSR.B.FLAG = 1;//清除场中断标志位
    EMIOS_0.CH[6].CCR.B.FEN=0;  //关闭场中断 
	prow=0;pcolumn=0;crow=0;trow=1;
	EMIOS_0.CH[5].CSR.B.FLAG = 1;  //清除行中断
	EMIOS_0.CH[5].CCR.B.FEN=1;  //开行中断
}

void RowInputCapture(void) 		//捕捉行中断
{
	crow++;
	EMIOS_0.CH[5].CSR.B.FLAG = 1;  //清除行中断
	if(prow>ROWS-1)
	{
		EMIOS_0.CH[5].CCR.B.FEN=0; 	//关闭行中断
		fieldover=1; //采样结束
	}
	else if(crow>trow)
	{
		for(pcolumn=0;pcolumn<COLUMNS;pcolumn++)
		{
			//a_pix[prow][pcolumn]=Y0+Y1<<1+Y2<<2+Y3<<3+Y4<<4+Y5<<5+Y6<<6+Y7<<7;
			a_pix[prow][pcolumn]=Y0+Y1*2+Y2*4+Y3*8+Y4*16+Y5*32+Y6*64+Y7*128;
			//a_pix[prow][pcolumn]=Y4*16+Y5*32+Y6*64+Y7*128;
			//a_pix[prow][pcolumn]=Y5*32+Y6*64+Y7*128;
		}
		prow++;
		trow+=3;
	}
	else
	{}
}
//*   **************************图像函数****************************      *
void VideoCopy(byte a[ROWS][COLUMNS],byte b[ROWS][COLUMNS])
{
	int i,j;
	for(i=0;i<ROWS;i++)
	{
		for(j=0;j<COLUMNS;j++)
		{
			a[i][j]=b[i][j];
		}
	}
}

