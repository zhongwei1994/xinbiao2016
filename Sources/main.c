#include "MPC5604B.h"

//3-14����
//315
//mmmmm
//315531
//
#include "includes.h"

int main(void) {
	int x_duoji = 0;
	initALL();
	//EMIOS_0.CH[6].CCR.B.FEN=1;  //�����ж� 
	for(;;) 
	{		
//		if(fieldover)//��������������־
//		{
//			fieldover=0;         //��־����
//			VideoCopy(A,a_pix);
//			BlueTx();
//			
//			EMIOS_0.CH[6].CSR.B.FLAG = 1;//������жϱ�־λ
//			EMIOS_0.CH[6].CCR.B.FEN=1;  //�����ж�
//		}
		x_duoji = TargetSteer;
		//OLED_Num(x_duoji);
		OLED_SetPointer(2,2);
		OLED_Num(x_duoji);
		KeyJudge();
	}
}



