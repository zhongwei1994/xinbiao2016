/*
 * video.h
 *
 *  Created on: Mar 13, 2016
 *      Author: zhongwei
 */

#ifndef VIDEO_H_
#define VIDEO_H_

#define byte unsigned char
#define word unsigned int

#define ROWS 80
#define COLUMNS 100

extern byte fieldover;
extern byte a_pix[ROWS][COLUMNS];

void FieldInputCapture(void);
void RowInputCapture(void);
void FieldInputCapture_2(void);
void RowInputCapture_2(void);
extern void VideoCopy(byte a[ROWS][COLUMNS],byte b[ROWS][COLUMNS]);

#endif /* VIDEO_H_ */
