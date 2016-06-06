/*
 * capture.c
 *
 *  Created on: Jun 6, 2016
 *      Author: lenovo
 */

#include "includes.h"

int A[128]={0};
int C_error=80;
int barrier_error=0,barrier_steer=0,barrier_kp=5;
int  ccd_barrier_flag=0;

void ImageCapture(int R[]) 
{
  //initAD();
  int Result1;
  int i;
  CCDR_SI=1;
  SamplingDelay();     //600ns
  CCDR_CLK=1;
  SamplingDelay();      // SI=0;
  CCDR_SI=0;      // SI=0;
  udelay(1);           //延时1μs
  for(i=0;i<20;i++)
  {
     Cpu_Delay1us();
  }
  
  while (ADC.CDR[34].B.VALID != 1) {}; /* 等待最后一次扫描完成*/
  Result1= ADC.CDR[34].B.CDATA; /* 读取ANS1的转换结果数据*/

  R[0]=Result1;  //CLK=0
  CCDR_CLK=0;  //CLK=0
  
  for(i=0; i<127; i++) 
  {
     udelay(2);           //延时2μs
     udelay(2);    // CLK = 1 
     CCDR_CLK = 1;    // CLK = 1 
     udelay(2);
     udelay(2);
        
     //Sampling Pixel 2~128
     while (ADC.CDR[34].B.VALID != 1) {}; /* 等待最后一次扫描完成*/
     Result1= ADC.CDR[34].B.CDATA; /* 读取ANS1的转换结果数据*/
     R[i+1]=Result1;    // CLK = 0 
     CCDR_CLK = 0;    // CLK = 0 
  }
  udelay(2);
  udelay(2);       // CLK = 1
  CCDR_CLK = 1;       // CLK = 1 
  udelay(2);
  udelay(2);
  CCDR_CLK = 0;        // CLK = 0
  udelay(2);
  udelay(2); 
}
void ccd_capture(void)
{
	int up_error=0,down_error=0;
	int i=0,x=0;
	for(i=30;i<=110;i++)
	{
		up_error=A[i]-A[i-15];
		if(up_error>=C_error)
		{
			down_error=A[i]-A[i+15];
			if(down_error>=C_error)
			{
				x=i+5;
				if(x>=70)
					barrier_error=105-x;
				else
					barrier_error=35-x;
				ccd_barrier_flag=1;
				return;
			}
			else
				ccd_barrier_flag=0;
		}
		else
			ccd_barrier_flag=0;
	}
}
void barrier_avoid(void)
{
	ccd_capture();
	if(ccd_barrier_flag)
	{
		targetspeed=130;
		barrier_steer=CENTER+barrier_kp*barrier_error;
		SET_steer(barrier_steer);
		delay_ms(1);
		ccd_barrier_flag=0;
	}
}
