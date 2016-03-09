/*
 * Bluetooth.c
 *
 *  Created on: Mar 7, 2016
 *      Author: zhongwei
 */
#include "includes.h"

int g_serial_port_0_f = 0;
unsigned int g_serial_port_0_data;

/*************************蓝牙初始化***********************/
void initLINFlex_0_UART(void) 
{
	LINFLEX_0.LINCR1.B.INIT=1;  //进入初始化模式
	LINFLEX_0.LINCR1.R=0x00000015; 
	//LINFLEX_0.LINIER.B.DTIE=0; //允许发送中断
	LINFLEX_0.LINIER.B.DRIE=1; //允许接收中断
	/*波特率算法baud=Fperiph_clk/(16*LFDIV)
	DIV_M=LFDIV整数部分
	DIV_F=LFDIV小数部分*16  */
      //38400:64M-104+3
	LINFLEX_0.LINIBRR.B.DIV_M =130;  	//波特率设置38400:80M-130+3 57600:80M-86+13 115200:80M-43+6 
	LINFLEX_0.LINFBRR.B.DIV_F =3;	//38400:64M-104+3
    LINFLEX_0.UARTCR.B.UART=1;
	LINFLEX_0.UARTCR.R=0x00000033;//8-bit data UART mode
	LINFLEX_0.LINCR1.B.INIT=0; //退出初始化模式
	
	SIU.PCR[18].R = 0x0400;    /* MPC56xxB: Configure port B2 as LIN0TX */
    SIU.PCR[19].R = 0x0103;    /* MPC56xxB: Configure port B3 as LIN0RX */
 	INTC_InstallINTCInterruptHandler(intc_serial_port_0_RX,79,2); 
}

void serial_port_0_TX(BYTE data)
{
	int i = 0;
	
	LINFLEX_0.BDRL.B.DATA0 = data;	//发送语句
	while(!LINFLEX_0.UARTSR.B.DTF)
	{
//		if (i++ >= 1000)
//		{
//			break;	/* 防止DTF置位失败 */
//		}
	}
	LINFLEX_0.UARTSR.B.DTF=1;
}


void serial_port_0_TX_array(const BYTE data[], WORD n)
{
	int i = 0;
	
	for (i=0; i<n; i++)
	{
		serial_port_0_TX(data[i]);
	}
}


void intc_serial_port_0_RX(void)
{
	unsigned int rev_ch;
	
	while(!LINFLEX_0.UARTSR.B.DRF){}
	rev_ch = (BYTE)LINFLEX_0.BDRM.B.DATA4;
	g_serial_port_0_f = 1;
	g_serial_port_0_data = rev_ch;
	LINFLEX_0.UARTSR.B.DRF=1;      //清空标志位
}



