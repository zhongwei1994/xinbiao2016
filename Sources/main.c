#include "MPC5604B.h"

#include "includes.h"

int main(void) {
	initALL();
	EMIOS_0.CH[6].CCR.B.FEN=1;  //�����ж� 
	for(;;) 
	{		
		if(fieldover)//��������������־
		{
			fieldover=0;         //��־����
			VideoCopy(A,a_pix);
			BlueTx();
			
			EMIOS_0.CH[6].CSR.B.FLAG = 1;//������жϱ�־λ
			EMIOS_0.CH[6].CCR.B.FEN=1;  //�����ж�
		}
	}
}



