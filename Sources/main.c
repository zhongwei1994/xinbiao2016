#include "MPC5604B.h"

//315
//
#include "includes.h"

int main(void) {
	int x_duoji = 0;
	initALL();
	
	SET_motor(50,50);
	
	EMIOS_0.CH[6].CCR.B.FEN=1;  //�����ж� 
	for(;;) 
	{		
		if(fieldover)//��������������־
		{
			fieldover=0;         //��־����
			pix_x=0;pix_y=0;
			pix_x2=0;pix_y2=0;
			lamp_search(&pix_x,&pix_y);
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



