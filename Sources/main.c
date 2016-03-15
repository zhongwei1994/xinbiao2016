#include "MPC5604B.h"

//3-14合作
//315
//mmmmm
//315531
//
#include "includes.h"

int main(void) {
	int x_duoji = 0;
	initALL();
	//EMIOS_0.CH[6].CCR.B.FEN=1;  //开场中断 
	for(;;) 
	{		
//		if(fieldover)//本场采样结束标志
//		{
//			fieldover=0;         //标志清零
//			VideoCopy(A,a_pix);
//			BlueTx();
//			
//			EMIOS_0.CH[6].CSR.B.FLAG = 1;//清除场中断标志位
//			EMIOS_0.CH[6].CCR.B.FEN=1;  //开场中断
//		}
		x_duoji = TargetSteer;
		//OLED_Num(x_duoji);
		OLED_SetPointer(2,2);
		OLED_Num(x_duoji);
		KeyJudge();
	}
}



