/*
 * Bluetooth.c
 *
 *  Created on: Mar 7, 2016
 *      Author: zhongwei
 */
#include "includes.h"

int g_serial_port_0_f = 0;
unsigned int g_serial_port_0_data;

/*************************������ʼ��***********************/
void initLINFlex_0_UART(void) 
{
	LINFLEX_0.LINCR1.B.INIT=1;  //�����ʼ��ģʽ
	LINFLEX_0.LINCR1.R=0x00000015; 
	//LINFLEX_0.LINIER.B.DTIE=0; //�������ж�
	LINFLEX_0.LINIER.B.DRIE=1; //��������ж�
	/*�������㷨baud=Fperiph_clk/(16*LFDIV)
	DIV_M=LFDIV��������
	DIV_F=LFDIVС������*16  */
      //38400:64M-104+3
	LINFLEX_0.LINIBRR.B.DIV_M =130;  	//����������38400:80M-130+3 57600:80M-86+13 115200:80M-43+6 
	LINFLEX_0.LINFBRR.B.DIV_F =3;	//38400:64M-104+3
    LINFLEX_0.UARTCR.B.UART=1;
	LINFLEX_0.UARTCR.R=0x00000033;//8-bit data UART mode
	LINFLEX_0.LINCR1.B.INIT=0; //�˳���ʼ��ģʽ
	
	SIU.PCR[18].R = 0x0400;    /* MPC56xxB: Configure port B2 as LIN0TX */
    SIU.PCR[19].R = 0x0103;    /* MPC56xxB: Configure port B3 as LIN0RX */
 	INTC_InstallINTCInterruptHandler(intc_serial_port_0_RX,79,2); 
}

void serial_port_0_TX(BYTE data)
{
	int i = 0;
	
	LINFLEX_0.BDRL.B.DATA0 = data;	//�������
	while(!LINFLEX_0.UARTSR.B.DTF)
	{
//		if (i++ >= 1000)
//		{
//			break;	/* ��ֹDTF��λʧ�� */
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
	LINFLEX_0.UARTSR.B.DRF=1;      //��ձ�־λ
}



