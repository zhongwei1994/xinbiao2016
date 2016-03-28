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
/*                      初始化SPI模块                        */
/*************************************************************/
void SPI_Init(void) 
{
  
  DSPI_1.MCR.R = 0x80013001;     //设置DSPI0为主模式，CS信号低有效，禁止FIFO
  DSPI_1.CTAR[0].R = 0x3E0A7727; //配置CTAR[0]，设置为每帧数据为8位，高位在前，波特率为100KHz
  DSPI_1.MCR.B.HALT = 0x0;	     //DSPI0处于运行状态
}

/*************************************************************/
/*                    设置SPI时钟为4MHz                      */
/*************************************************************/
void SPI_4M(void) 
{ 
  DSPI_1.MCR.B.HALT = 0x1;	     //DSPI0停止运行
  DSPI_1.CTAR[0].R = 0x3E087723; //配置CTAR[0]，设置为每帧数据为8位，高位在前，波特率为4MHz
  DSPI_1.MCR.B.HALT = 0x0;	     //DSPI0处于运行状态
}

/*************************************************************/
/*                        初始化SD卡                         */
/*************************************************************/
void SD_Init(void)
{
	SPI_Init();
	SD_deselect();
}

/*************************************************************/
/*                        清空缓冲区                         */
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
/*                      SPI读写一个字节                      */
/*************************************************************/
uint8_t SPI_Byte(uint8_t value)
{
	uint8_t input;
	DSPI_1.PUSHR.R = 0x08000000|value;    //赋值需要发送的数据		
	while(DSPI_1.SR.B.TCF==0)            //等待发送完成
	{}
	DSPI_1.SR.B.TCF=1;                   //清除发送完成标志位
	while(DSPI_1.SR.B.RFDF==0)           //等待接收到数据
	{}
	input=(uint8_t)(DSPI_1.POPR.R);      //读取接收到的数据
	DSPI_1.SR.B.RFDF=1;                  //清除接收标志位

	return(input);      //返回接收到的数据
}

/*************************************************************/
/* 函数名：SD_send_command*/
/* 功能：向SD卡写入命令 */
/* 输入：cmd：命令      dat：命令参数  */
/* 输出：None*/
/* return：r1：SD卡返回的数据        0xff表示发送失败 */
/*************************************************************/
uint8_t SD_send_command(uint8_t cmd, uint32_t arg)
{
	uint8_t a;
	uint8_t retry=0;
	
	//取消上次片选
	SD_deselect();
	//额外提供8个时钟
	SPI_Byte(0xff);
	//选择片选
	SD_select();
	
	while(SPI_Byte(0xff)!=0xff)//等待卡是否准备好
	{
		retry++;
		if(retry>10)
			return 0xff;//等待失败返回
	}
	//发送数据
	SPI_Byte(cmd | 0x40);//分别写入命令
	SPI_Byte(arg>>24);//发送arg的最高8位
	SPI_Byte(arg>>16);
	SPI_Byte(arg>>8);
	SPI_Byte(arg);
	SPI_Byte(0x95);//发送CRC验证码
	
	if(cmd==0x0c)//如果是停止数据传输命令CMD12，额外多发一个时钟
		SPI_Byte(0xff);
	
	retry=0;
	do
	{
		a=SPI_Byte(0xff);
		retry++;    
		if(retry>10)
			return 0xff;//超时退出
	}while((a&0xc0)!=0);//发送成功最高两位应是0

	SD_deselect();

	return a;//返回状态值
}

uint8_t SD_Reset(void)
{
	uint8_t retry;
	uint8_t a;
	uint8_t buf[4];
	
	SPI_Init();//SPI模式启动
	SD_select();//选择片选
	
	for(retry=0;retry<10;retry++)
	{
		SPI_Byte(0xff);//提供了80个时钟
	}
	
	retry = 0;
	while(SD_send_command(0,0)!=0x01)//发送CMD0，复位SD卡，回应0x01表示初始化成功，否则超时退出
	{
		retry++;
		if(retry>10)
			return 1;//初始化失败返回1
	}
	
	//发送CMD8，检测是否SD V2.0
	retry = 0;
	while(SD_send_command(0x08,0x01aa)!=0x01)
	{
		retry++;
		if(retry>10)
			break;//若是超出发送次数，跳出循环
	}
	
	if(a==0x01)//如果CMD8有回应，说明是SD V2.0协议
	{
		//读取CMD8的返回值，检测是否支持电压
		for(retry=0;retry<4;retry++)
			buf[retry]=SPI_Byte(0xff);
		//卡电压不支持，返回错误
		if((buf[2]!=0x01)||(buf[3]!=0xaa))
			return 1;
		//初始化SD卡
		retry = 0;
		do
		{
			SD_send_command(55, 0);  //发触发命令
			a = SD_send_command(41, 0);  //发触发命令
			retry++;
			if(retry>10) 
				return 1;      //超时退出
		} while(a);//写入CMD41成功了，这里省略读取了CMD41是否设置成功
	}
	
	//else//否则就是SD V1.0或者MMC V3
	//{
		SD_send_command(55,0);
		a=SD_send_command(41,0);
		
		if(a<=1)//对CMD41有回应说明是SD V1.0
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

	a = SD_send_command(16, 512);//设扇区大小512

	return 0;//正常返回
}

/*************************************************************/
/*                     由SD卡读取一个扇区                    */
/*************************************************************/
uint8_t read_block(uint32_t sector, uint8_t* buffer)
{
	uint8_t a;          
	uint16_t i;
	a = SD_send_command(17, sector<<9);  //读命令 	
	if(a != 0x00) 		return a;

	SD_select();
	//等数据的开始
	while(SPI_Byte(0xff) != 0xfe)
	{ }

	for(i=0; i<512; i++)              //读512个数据
	{
		*buffer++ = SPI_Byte(0xff);
	}

	SPI_Byte(0xff);              
	SPI_Byte(0xff);  	
	SD_deselect();
 	SPI_Byte(0xff);              
	return 0;
	
	i=0;
	SD_select();//选择片选
	//等数据的开始，起始令牌是0xfe
	while(SPI_Byte(0xff) != 0xfe)
	{ 
		i++;
		if(i>100)
			return 1;
	}
	//读512个数据
	for(i=0; i<512; i++)              
	{
		*buffer++ = SPI_Byte(0xff);
	}
	//读完数据可以再度两位校验，但是我们可以不需要它们
	SPI_Byte(0xff);              
	SPI_Byte(0xff); 
	
	return 0;//读取成功，返回0
}

/*************************************************************/
/*                     向SD卡写入一个扇区                    */
/*************************************************************/
uint8_t write_block(uint32_t sector, uint8_t* buffer)
{
	uint8_t a;
	uint16_t i;
    if(sector<1) return 0xff;     //为了保护SD卡引导区，跳过该区
	a = SD_send_command(24, sector<<9);//写命令
	if(a != 0x00) return a;

	SD_select();
	
	SPI_Byte(0xff);
	SPI_Byte(0xff);
	SPI_Byte(0xff);

	SPI_Byte(0xfe);//发开始符
	
	for(i=0; i<512; i++)//送512字节数据
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
	//等待操作完
	while(!SPI_Byte(0xff))
	{}

  	SD_deselect();

	return 0;
} 

void SD_Test(void)
{
	//SD卡测试用
	uint8_t BUFFER_A[512]; 
	uint8_t BUFFER_B[512]; 
	uint8_t BUFFER_C[512]; 
	uint8_t BUFFER_3[1536]; 
	uint16_t m;
	uint16_t error;
	
	OLED_SetPointer(1,2);
	OLED_Str("Hello! SD_TEST");
	
	//SD卡测试
		while(SD_Reset()!=0)     //初始化SD卡
		{ 	  
			delay();    
		}

		SPI_4M(); 
		//读取SD卡引导区数据
		if(read_block(0x00, BUFFER_A)) //读取引导区失败，中止，否则向下运行
		  for(;;)
		  {}

		clear_buffer(BUFFER_A);       //清空接收缓冲器  
		clear_buffer(BUFFER_B);       //清空接收缓冲器  
		clear_buffer(BUFFER_C);       //清空接收缓冲器  
		
		write_block(0x1FF,BUFFER_A);  //擦除扇区，如果失败，中止，否则向下运行	
		write_block(0x1FF+0x0200,BUFFER_A);  //擦除扇区，如果失败，中止，否则向下运行
		write_block(0x1FF+0x0400,BUFFER_A);  //擦除扇区，如果失败，中止，否则向下运行
		
		for(m=0;m<512;m++)
		   BUFFER_A[m]='A';     //赋值待写入的数据
		for(m=0;m<512;m++)
		   BUFFER_B[m]='B';     //赋值待写入的数据
		for(m=0;m<512;m++)
		   BUFFER_C[m]='C';     //赋值待写入的数据
		
		write_block(0x1FF,BUFFER_A);     //写入数据，如果失败，中止，否则向下运行
		write_block(0x1FF+0x0200,BUFFER_B);     //写入数据，如果失败，中止，否则向下运行
		write_block(0x1FF+0x0400,BUFFER_C);     //写入数据，如果失败，中止，否则向下运行
		
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
