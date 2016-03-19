/*
 * analysis.h
 *
 *  Created on: Mar 15, 2016
 *      Author: zhongwei
 */

#ifndef ANALYSIS_H_
#define ANALYSIS_H_

#define video_t 230 

extern byte pix_x,pix_y;
extern byte pix_x2,pix_y2;

extern void lamp_search(byte *pix_x,byte *pix_y);
int lamp_judge(byte pix_i,byte pix_j);
void central_search(byte *pix_i,byte *pix_j,byte x,byte y);

byte point_search(byte *pix_i,byte *pix_j,byte i,byte j);
extern void lamp_search_2(byte *pix_i,byte *pix_j);


#endif /* ANALYSIS_H_ */