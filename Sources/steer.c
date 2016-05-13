/*
 * steer.c
 *
 *  Created on: Mar 13, 2016
 *      Author: zhongwei
 */

#include "includes.h"

/*************************�������***************************/
byte wrong_count=0;
byte close_supersonic=1,cycle_flag=0;
byte success=0;
byte cycle_j=64,turnleft=65;//turnleftΪ����Ŀ�귽�򣬲������׸ı�
int target_offset=0,last_offset=0;	//���ƫ��ֵ��¼
double Steer_kp=3,Steer_kd=0;//���P��Dֵ
unsigned int Steer_PWM[4]={0,0,0,CENTER};//������ֵ��¼
/*************************����ӿں���***********************/
void SET_steer(unsigned int steer)
{EMIOS_0.CH[4].CBDR.R = steer;}
/*************************���PD��������***********************/
void Steer_PDSet(void)
{
	//target_offset=error;
	if(pix_i<55)
	{
		if(pix_j>60||pix_j<40)
		{
			if(pix_j<75&&pix_j>25)
			{
				if(targetspeed==straightspeed)
//					Steer_kp=4.6-0.025*(ABS(pix_j-50)-8);//��
//					Steer_kp=5.2-0.1*(ABS(pix_j-50)-8);
					Steer_kp=2.5+0.25*(ABS(pix_j-50)-10);
				else
//					Steer_kp=5.5-0.08*(ABS(pix_j-50)-8);//��
//					Steer_kp=7.2-0.10*(ABS(pix_j-50)-8);
					Steer_kp=3+0.6*(ABS(pix_j-50)-10);
			}
			else
			{
				if(targetspeed==straightspeed)
					Steer_kp=6.25;//Ϊ����kpĩֵ
				else
					Steer_kp=12;//Ϊ����kpĩֵ
			}
		}
		else
		{
			if(targetspeed==straightspeed)
				Steer_kp=3.5;//Ϊ������ֵ
			else
				Steer_kp=2+0.9*(ABS(pix_j-50));
//				Steer_kp=10;//Ϊ������ֵ
		}
	}
	else
	{
		if(targetspeed==straightspeed)
			Steer_kp=5;//ԼΪ������ֵ
		else
			Steer_kp=7;//ԼΪ������ֵ
	}
}
/*************************������ƣ�PD***********************/
void SteerControl(void)
{
	Steer_PDSet();
	if(barrier_left_flag==1||barrier_right_flag==1||backflag==1)
	{
		return;
	}
	if(wrong_flag==1)		
	{
		close_supersonic=1;//�����رճ�������־
		wrong_count++;
		if(success)		//�жϵ���������
		{
			cycle_flag=1;
			targetspeed=cyclespeed;
			BEE = 1;
			Steer_PWM[3]=RIGHT;
			SET_steer(Steer_PWM[3]);
			//����ֵ
			Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
			success=0;
			return;
		}
		else
		{
			if(wrong_count<=2)	//1��2��û�������������ֶ��ֵ
			{
				cycle_flag=0;
				Steer_PWM[3]=(Steer_PWM[2]+Steer_PWM[1])/2;
				SET_steer(Steer_PWM[3]);
				Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
				return;
			}
			else if(wrong_count>=3)	//3��û�����������������תȦ
			{
				cycle_flag=1;
				targetspeed=cyclespeed;
				BEE = 1;
				Steer_PWM[3]=RIGHT;
				SET_steer(Steer_PWM[3]);
				//����ֵ
				Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
				return;
			}
		}
	}
	else
	{
		wrong_count=0;
		BEE=0;
		if(pix_i<27)	
		{
			if(pix_i<27)		//��Զ�������ڳ���ȫ���ˣ�����close_supersonic=1;������close_supersonic=0��Զ��������
			{
				close_supersonic=1;
				targetspeed=straightspeed;
			}
			else				//�ڽ��������ڳ���ȫ����
			{  
				close_supersonic=1;//�����رճ�������־
				targetspeed=cyclespeed;
			}
			cycle_flag=0;
			target_offset=pix_j-50;
			Steer_PWM[3] = CENTER-Steer_kp*target_offset-Steer_kd*(target_offset-last_offset); //λ��ʽPD
//			if(Steer_PWM[3]>LEFT) Steer_PWM[3]=LEFT;
//			else if(Steer_PWM[3]<RIGHT) Steer_PWM[3]=RIGHT;
			//*****5.12�¼ӣ���ֵ���ת��*****//
			if(targetspeed==straightspeed)
			{
				if(Steer_PWM[3]>4025)
					Steer_PWM[3]=4025;
				else if(Steer_PWM[3]<3765)
					Steer_PWM[3]=3765;	
			}
			else
			{
				if(Steer_PWM[3]>4065)
					Steer_PWM[3]=4065;
				else if(Steer_PWM[3]<3725)
					Steer_PWM[3]=3725;	
			}
			//*****5.12�¼ӣ���ֵ���ת��*****//
			SET_steer(Steer_PWM[3]);
			//����ֵ��offsetֵ
			Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
			last_offset=target_offset;
		}
		else
		{
			close_supersonic=1;//�����رճ�������־
			if(pix_i>55)
			{
				success=1;
			}
			if(pix_i>53&&pix_j>cycle_j)		//����������λ�÷��ϵ��������½���������ʼת��
			{
				cycle_flag=1;
				targetspeed=cyclespeed;
				BEE = 1;
				Steer_PWM[3]=RIGHT;
				SET_steer(Steer_PWM[3]);
				//����ֵ
				Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
				return;
			}
			else		//������������λ�ò����ϵ��������½���������΢��ƫһ��Ԥת��
			{
				cycle_flag=0;
				targetspeed=cyclespeed;
				//С��������Ͻ�ʱΪ��ʹС����ֱ�ӳ������ܣ���Ŀ��ֵ46������������
				target_offset=pix_j-turnleft;
				Steer_PWM[3] = CENTER-Steer_kp*target_offset-Steer_kd*(target_offset-last_offset); //λ��ʽPD
//				if(Steer_PWM[3]>LEFT) Steer_PWM[3]=LEFT;
//				else if(Steer_PWM[3]<RIGHT) Steer_PWM[3]=RIGHT;
				//*****5.12�¼ӣ���ֵ���ת��*****//
				if(Steer_PWM[3]>4150)
					Steer_PWM[3]=4150;
				else if(Steer_PWM[3]<3620)
					Steer_PWM[3]=3620;	
				//*****5.12�¼ӣ���ֵ���ת��*****//
				SET_steer(Steer_PWM[3]);
				//����ֵ��offsetֵ
				Steer_PWM[0]=Steer_PWM[1];Steer_PWM[1]=Steer_PWM[2];Steer_PWM[2]=Steer_PWM[3];
				last_offset=target_offset;
			}
		}
	}	
}
byte BarrierJudge(void)	//�������ȼ�
{
	if(barrier_left_flag==1)
	{
		SET_steer(LEFT);
		return 1;
	}
	else if(barrier_right_flag==1)
	{
		SET_steer(RIGHT);
		return 2;
	}
	else
		return 0;
}

