/*
 * pit.c
 *
 *  Created on: Apr 1, 2016
 *      Author: lenovo
 */

#include "includes.h"

unsigned int pitcount0=0,pitcount1=0,pitcount2=0,pitcount3=0,pitcount4=0,pitcount5=0;
unsigned int barrier_delay=0;
unsigned int supson_delay1=0,supson_delay2=0,ss_delay_flag1=0,ss_delay_flag2=0;

void initPIT(void) 
{                                   //1msһ����������// NOTE:  DIVIDER FROM SYSCLK TO PIT ASSUMES DEFAULT DIVIDE BY 1 
  PIT.PITMCR.R = 0x00000001;       // Enable PIT and configure timers to stop in debug mode 
  PIT.CH[1].LDVAL.R = 80000;      // PIT1 timeout = 80000 sysclks x 1sec/80M sysclks = 1 msec 
  PIT.CH[1].TCTRL.R = 0x000000003; // Enable PIT1 interrupt and make PIT active to count 
  INTC_InstallINTCInterruptHandler(PitISR,60,10); 
}

void PitISR(void)//1msһ����������
{
	pitcount0++;                                  //5msһ������
	if(pitcount0==2)
	{
		pitcount2++;
		if(pitcount2>=20)                          //100msһ��,����������
		{
			pitcount2=0;
			OLED_SetPointer(5,20);
			OLED_Num(barrier_left_flag);
			OLED_SetPointer(6,20);
			OLED_Num(barrier_right_flag);
			if(pix_i<40&&pix_i>0)                           //�ӽ���������������ʱ
			{
				ss_delay_flag2=1;
			}
			if(BarrierJudge()==1)                  //�ϰ����жϣ���ת
			{
				BEE=1;
				barrier_delay++;
				if(barrier_delay>=4)
				{
					SET_steer(RIGHT);
				}
				if(barrier_delay>=8)
				{
					barrier_delay=0;
					BEE=0;
					barrier_left_flag=0;
					barrier_right_flag=0;
					ss_delay_flag1=1;
				}
			}
			else if(BarrierJudge()==2)               //�ϰ����жϣ���ת
			{
				BEE=1;
				barrier_delay++;
				if(barrier_delay>=8)
				{
					SET_steer(LEFT);
				}
				if(barrier_delay>=13)
				{
					barrier_delay=0;
					BEE=0;
					barrier_left_flag=0;
					barrier_right_flag=0;
					ss_delay_flag1=1;
				}
			}
			else
			{
//				if(ss_delay_flag1==1)              //���ϳɹ�����ʱ
//				{
//					supson_delay1++;
//					if(supson_delay1>30)           //30*100ms=3s
//					{
//						supson_delay1=0;
//						ss_delay_flag1==0;
//					}
//						
//				}
//				else if(ss_delay_flag2==1)          //�ӽ�����ʱ��ʱ
//				{
//					supson_delay2++;
//					if(supson_delay2>50)           //50*100ms=5s
//					{
//						supson_delay2=0;
//						ss_delay_flag2==0;
//					}
//						
//				}
//				else                               //����Ҫ��ʱ��ʱ�򣬴���������
//				{
					trigger_supersonic_1();
					trigger_supersonic_2();
//				}
			}
		}
	}
//	if(pitcount0==3)
//	{
//		pitcount3++;
//		if(pitcount3>=1)                          //100msһ�Σ�δ����
//		{
//			pitcount3=0;
//			
//			
//		}
//	}
	if(pitcount0==5)
	{
		pitcount0=0;
		pitcount5++;
		if(pitcount5>=100)                         //1sһ��
		{
			pitcount5=0;
			OLED_Fill(0x00);
			OLED_SetPointer(3,20);
			OLED_Num(OLED_distance1);
			OLED_SetPointer(4,20);
			OLED_Num(OLED_distance2);
		}
	}
	PIT.CH[1].TFLG.B.TIF = 1;//write 1 to clear PIT1 �����־λ
}
