//315
//
#include "includes.h"

int main(void) {
//	int x_duoji = 0,i=0;
	initALL();
	initPIT();
	BEE = 1;
	delay_ms(1000);
	BEE = 0;
	//targetspeed=170;
	EMIOS_0.CH[6].CCR.B.FEN=1;  //�����ж� 
	//EMIOS_0.CH[26].CCR.B.FEN=1;  //�����ж� _viedo2
	for(;;) 	
	{		
		if(fieldover)//��������������־
		{
			fieldover=0;         //��־����
			wrong_flag=0;
			//pix_x=0;pix_y=0;
			pix_x2=0;pix_y2=0;
			//lamp_search(&pix_x,&pix_y);
			lamp_search(&pix_i,&pix_x2,&pix_y2);
			central_search_2(&pix_i,&pix_j,pix_x2,pix_y2);
			//TargetSteer=3900-24*(pix_j-50);
			SteerControl();
			//BlueTx();
			EMIOS_0.CH[6].CSR.B.FLAG = 1;//������жϱ�־λ
			EMIOS_0.CH[6].CCR.B.FEN=1;  //�����ж�
//			EMIOS_0.CH[26].CSR.B.FLAG = 1;//������жϱ�־λ_video2
//			EMIOS_0.CH[26].CCR.B.FEN=1;  //�����ж�_viedo2
		}
//		x_duoji = TargetSteer;
//		//OLED_Num(x_duoji);
		KeyJudge();
		//BlueTx();
	}
}



