/*
 * SD.c
 *
 *  Created on: Mar 24, 2016
 *      Author: zhongwei
 */

#include "includes.h"

extern uint8_t BUFFER_A[512]; 
extern uint8_t BUFFER_B[512]; 
extern uint8_t BUFFER_C[512]; 
extern uint8_t BUFFER_3[1536]; 

/*************************************************************/
/*                      ��ʼ��SPIģ��                        */
/*************************************************************/
void SPI_Init(void) 
{
  
  DSPI_1.MCR.R = 0x80013001;     //����DSPI0Ϊ��ģʽ��CS�źŵ���Ч����ֹFIFO
  DSPI_1.CTAR[0].R = 0x3E0A7727; //����CTAR[0]������Ϊÿ֡����Ϊ8λ����λ��ǰ��������Ϊ100KHz
  DSPI_1.MCR.B.HALT = 0x0;	     //DSPI0��������״̬
}

/*************************************************************/
/*                    ����SPIʱ��Ϊ4MHz                      */
/*************************************************************/
void SPI_4M(void) 
{ 
  DSPI_1.MCR.B.HALT = 0x1;	     //DSPI0ֹͣ����
  DSPI_1.CTAR[0].R = 0x3E087723; //����CTAR[0]������Ϊÿ֡����Ϊ8λ����λ��ǰ��������Ϊ4MHz
  DSPI_1.MCR.B.HALT = 0x0;	     //DSPI0��������״̬
}

/*************************************************************/
/*                        ��ʼ��SD��                         */
/*************************************************************/
void SD_Init(void)
{
	SPI_Init();
	SD_deselect();
}

/*************************************************************/
/*                        ��ջ�����                         */
/*************************************************************/
void clear_buffer(uint8_t buffer[])
{
    uint16_t i=512-1;     
    while(i>0)
    {
    	buffer[i]=0;
    	i--;
    }	
}
 
/*************************************************************/
/*                      SPI��дһ���ֽ�                      */
/*************************************************************/
uint8_t SPI_Byte(uint8_t value)
{
	uint8_t input;
	DSPI_1.PUSHR.R = 0x08000000|value;    //��ֵ��Ҫ���͵�����		
	while(DSPI_1.SR.B.TCF==0)            //�ȴ��������
	{}
	DSPI_1.SR.B.TCF=1;                   //���������ɱ�־λ
	while(DSPI_1.SR.B.RFDF==0)           //�ȴ����յ�����
	{}
	input=(uint8_t)(DSPI_1.POPR.R);      //��ȡ���յ�������
	DSPI_1.SR.B.RFDF=1;                  //������ձ�־λ

	return(input);      //���ؽ��յ�������
}

/*************************************************************/
/* ��������SD_send_command*/
/* ���ܣ���SD��д������ */
/* ���룺cmd������      dat���������  */
/* �����None*/
/* return��r1��SD�����ص�����        0xff��ʾ����ʧ�� */
/*************************************************************/
uint8_t SD_send_command(uint8_t cmd, uint32_t arg)
{
	uint8_t a;
	uint8_t retry=0;
	
	//ȡ���ϴ�Ƭѡ
	SD_deselect();
	//�����ṩ8��ʱ��
	SPI_Byte(0xff);
	//ѡ��Ƭѡ
	SD_select();
	
	while(SPI_Byte(0xff)!=0xff)//�ȴ����Ƿ�׼����
	{
		retry++;
		if(retry>10)
			return 0xff;//�ȴ�ʧ�ܷ���
	}
	//��������
	SPI_Byte(cmd | 0x40);//�ֱ�д������
	SPI_Byte(arg>>24);//����arg�����8λ
	SPI_Byte(arg>>16);
	SPI_Byte(arg>>8);
	SPI_Byte(arg);
	SPI_Byte(0x95);//����CRC��֤��
	
	if(cmd==0x0c)//�����ֹͣ���ݴ�������CMD12������෢һ��ʱ��
		SPI_Byte(0xff);
	
	retry=0;
	do
	{
		a=SPI_Byte(0xff);
		retry++;    
		if(retry>10)
			return 0xff;//��ʱ�˳�
	}while((a&0xc0)!=0);//���ͳɹ������λӦ��0

	SD_deselect();

	return a;//����״ֵ̬
}

uint8_t SD_Reset(void)
{
	uint8_t retry;
	uint8_t a;
	uint8_t buf[4];
	
	SPI_Init();//SPIģʽ����
	SD_select();//ѡ��Ƭѡ
	
	for(retry=0;retry<10;retry++)
	{
		SPI_Byte(0xff);//�ṩ��80��ʱ��
	}
	
	retry = 0;
	while(SD_send_command(0,0)!=0x01)//����CMD0����λSD������Ӧ0x01��ʾ��ʼ���ɹ�������ʱ�˳�
	{
		retry++;
		if(retry>10)
			return 1;//��ʼ��ʧ�ܷ���1
	}
	
	//����CMD8������Ƿ�SD V2.0
	retry = 0;
	while(SD_send_command(0x08,0x01aa)!=0x01)
	{
		retry++;
		if(retry>10)
			break;//���ǳ������ʹ���������ѭ��
	}
	
	if(a==0x01)//���CMD8�л�Ӧ��˵����SD V2.0Э��
	{
		//��ȡCMD8�ķ���ֵ������Ƿ�֧�ֵ�ѹ
		for(retry=0;retry<4;retry++)
			buf[retry]=SPI_Byte(0xff);
		//����ѹ��֧�֣����ش���
		if((buf[2]!=0x01)||(buf[3]!=0xaa))
			return 1;
		//��ʼ��SD��
		retry = 0;
		do
		{
			SD_send_command(55, 0);  //����������
			a = SD_send_command(41, 0);  //����������
			retry++;
			if(retry>10) 
				return 1;      //��ʱ�˳�
		} while(a);//д��CMD41�ɹ��ˣ�����ʡ�Զ�ȡ��CMD41�Ƿ����óɹ�
	}
	
	//else//�������SD V1.0����MMC V3
	//{
		SD_send_command(55,0);
		a=SD_send_command(41,0);
		
		if(a<=1)//��CMD41�л�Ӧ˵����SD V1.0
		{
			retry=0;
			do
			{
				if(retry>10)
					return 1;
				SD_send_command(55,0);
				a=SD_send_command(41,0);
			}while(a!=0);
		}
	//}
		
	a = SD_send_command(59, 0);   

	a = SD_send_command(16, 512);//��������С512

	return 0;//��������
}

/*************************************************************/
/*                     ��SD����ȡһ������                    */
/*************************************************************/
uint8_t read_block(uint32_t sector, uint8_t* buffer)
{
	uint8_t a;          
	uint16_t i;
	a = SD_send_command(17, sector<<9);  //������ 	
	if(a != 0x00) 		return a;

	SD_select();
	//�����ݵĿ�ʼ
	while(SPI_Byte(0xff) != 0xfe)
	{ }

	for(i=0; i<512; i++)              //��512������
	{
		*buffer++ = SPI_Byte(0xff);
	}

	SPI_Byte(0xff);              
	SPI_Byte(0xff);  	
	SD_deselect();
 	SPI_Byte(0xff);              
	return 0;
	
	i=0;
	SD_select();//ѡ��Ƭѡ
	//�����ݵĿ�ʼ����ʼ������0xfe
	while(SPI_Byte(0xff) != 0xfe)
	{ 
		i++;
		if(i>100)
			return 1;
	}
	//��512������
	for(i=0; i<512; i++)              
	{
		*buffer++ = SPI_Byte(0xff);
	}
	//�������ݿ����ٶ���λУ�飬�������ǿ��Բ���Ҫ����
	SPI_Byte(0xff);              
	SPI_Byte(0xff); 
	
	return 0;//��ȡ�ɹ�������0
}

/*************************************************************/
/*                     ��SD��д��һ������                    */
/*************************************************************/
uint8_t write_block(uint32_t sector, uint8_t* buffer)
{
	uint8_t a;
	uint16_t i;
    if(sector<1) return 0xff;     //Ϊ�˱���SD������������������
	a = SD_send_command(24, sector<<9);//д����
	if(a != 0x00) return a;

	SD_select();
	
	SPI_Byte(0xff);
	SPI_Byte(0xff);
	SPI_Byte(0xff);

	SPI_Byte(0xfe);//����ʼ��
	
	for(i=0; i<512; i++)//��512�ֽ�����
	{
		SPI_Byte(*buffer++);
	}
	
	SPI_Byte(0xff);
	SPI_Byte(0xff);
	
	a = SPI_Byte(0xff); 	
	if( (a&0x1f) != 0x05)
	{
	  SD_deselect();
		return a;
	}
	//�ȴ�������
	while(!SPI_Byte(0xff))
	{}

  	SD_deselect();

	return 0;
} 

void SD_Test(void)
{
	//SD��������
	uint8_t BUFFER_A[512]; 
	uint8_t BUFFER_B[512]; 
	uint8_t BUFFER_C[512]; 
	uint8_t BUFFER_3[1536]; 
	uint16_t m;
	uint16_t error;
	
	OLED_SetPointer(1,2);
	OLED_Str("Hello! SD_TEST");
	
	//SD������
		while(SD_Reset()!=0)     //��ʼ��SD��
		{ 	  
			delay();    
		}

		SPI_4M(); 
		//��ȡSD������������
		if(read_block(0x00, BUFFER_A)) //��ȡ������ʧ�ܣ���ֹ��������������
		  for(;;)
		  {}

		clear_buffer(BUFFER_A);       //��ս��ջ�����  
		clear_buffer(BUFFER_B);       //��ս��ջ�����  
		clear_buffer(BUFFER_C);       //��ս��ջ�����  
		
		if((write_block(0x1FF,BUFFER_A)))   //�������������ʧ�ܣ���ֹ��������������
		   for(;;)
		   {}
		if((write_block(0x1FF+0x0200,BUFFER_A)))   //�������������ʧ�ܣ���ֹ��������������
		   for(;;)
		   {}

		if((write_block(0x1FF+0x0400,BUFFER_A)))   //�������������ʧ�ܣ���ֹ��������������
		   for(;;)
		   {}
		
		for(m=0;m<512;m++)
		   BUFFER_A[m]='A';     //��ֵ��д�������
		for(m=0;m<512;m++)
		   BUFFER_B[m]='B';     //��ֵ��д�������
		for(m=0;m<512;m++)
		   BUFFER_C[m]='C';     //��ֵ��д�������
		
		if((write_block(0x1FF,BUFFER_A)))      //д�����ݣ����ʧ�ܣ���ֹ��������������
		   for(;;)
		   {}
		if((write_block(0x1FF+0x0200,BUFFER_B)))      //д�����ݣ����ʧ�ܣ���ֹ��������������
		   for(;;)
		   {}
		if((write_block(0x1FF+0x0400,BUFFER_C)))      //д�����ݣ����ʧ�ܣ���ֹ��������������
		   for(;;)
		   {}
		
		read_block(0x1FF, BUFFER_3);
		OLED_SetPointer(2,2);
		OLED_Char(BUFFER_3[0]);
		read_block(0x1FF+0x0200, BUFFER_3+512);
		OLED_SetPointer(3,2);
		OLED_Char(BUFFER_3[512]);	
		read_block(0x1FF+0x0400, BUFFER_3+512*2);
		OLED_SetPointer(4,2);
		OLED_Char(BUFFER_3[1024]);
		
		OLED_SetPointer(5,2);
		OLED_Str("SD_OK Bye!");
}
