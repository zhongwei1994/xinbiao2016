#include "MPC5604B.h"

//315
//
#include "includes.h"


int main(void) {
	int x_duoji = 0;
	initALL();	
	SET_motor(55,55);	
	EMIOS_0.CH[6].CCR.B.FEN=1;  //�����ж� 
	SET_steer(CENTER);
	for(;;) 
	{		
		if(fieldover)//��������������־
		{
			fieldover=0;         //��־����
			wrong_flag=0;
			//pix_x=0;pix_y=0;
			pix_x2=0;pix_y2=0;
			lamp_search_2(&pix_x2,&pix_y2);
			central_search_2(&pix_i,&pix_j,pix_x2,pix_y2);
			//TargetSteer=3900-24*(pix_j-50);
			SteerControl();
			BlueTx();
			EMIOS_0.CH[6].CSR.B.FLAG = 1;//������жϱ�־λ
			EMIOS_0.CH[6].CCR.B.FEN=1;  //�����ж�
		}
//		x_duoji = TargetSteer;
//		//OLED_Num(x_duoji);
//		OLED_SetPointer(2,2);
//		OLED_Num(x_duoji);
//		KeyJudge();
	}
}



