/*
 * capture.c
 *
 *  Created on: Jun 6, 2016
 *      Author: lenovo
 */

#include "includes.h"

int A[128]={0};

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
  udelay(1);           //��ʱ1��s
  for(i=0;i<20;i++)
  {
     Cpu_Delay1us();
  }
  
  while (ADC.CDR[34].B.VALID != 1) {}; /* �ȴ����һ��ɨ�����*/
  Result1= ADC.CDR[34].B.CDATA; /* ��ȡANS1��ת���������*/

  R[0]=Result1;  //CLK=0
  CCDR_CLK=0;  //CLK=0
  
  for(i=0; i<127; i++) 
  {
     udelay(2);           //��ʱ2��s
     udelay(2);    // CLK = 1 
     CCDR_CLK = 1;    // CLK = 1 
     udelay(2);
     udelay(2);
        
     //Sampling Pixel 2~128
     while (ADC.CDR[34].B.VALID != 1) {}; /* �ȴ����һ��ɨ�����*/
     Result1= ADC.CDR[34].B.CDATA; /* ��ȡANS1��ת���������*/
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
