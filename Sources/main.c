#include "MPC5604B.h"

#include "includes.h"

int main(void) {
	initALL();
	EMIOS_0.CH[6].CCR.B.FEN=1;  //开场中断 
	for(;;) 
	{		
		if(fieldover)//本场采样结束标志
		{
			fieldover=0;         //标志清零
			VideoCopy(A,a_pix);
			BlueTx();
			
			EMIOS_0.CH[6].CSR.B.FLAG = 1;//清除场中断标志位
			EMIOS_0.CH[6].CCR.B.FEN=1;  //开场中断
		}
	}
}



