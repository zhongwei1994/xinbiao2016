/*
 * SD.h
 *
 *  Created on: Mar 24, 2016
 *      Author: zhongwei
 */

#ifndef SD_H_
#define SD_H_

#include "includes.h"

#define SD_select()        SIU.GPDO[15].B.PDO=0        //QS3低电平
#define SD_deselect()      SIU.GPDO[15].B.PDO=1        //QS3高电平


void SPI_Init(void); 
void SPI_4M(void); 
void clear_buffer(uint8_t buffer[]);
uint8_t SPI_Byte(uint8_t value);
void SD_Init(void);
uint8_t SD_send_command(uint8_t cmd, uint32_t arg);
uint8_t SD_Reset(void);
uint8_t read_block(uint32_t sector, uint8_t* buffer);
uint8_t write_block(uint32_t sector, uint8_t* buffer);

void SD_Test(void);

#endif /* SD_H_ */
