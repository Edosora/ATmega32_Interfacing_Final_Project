/*
 * 7Seg.h
 *
 *  Created on: Aug 30, 2026
 *      Author: Mohammed
 */

#ifndef HAL_H7SEG_7SEG_H_
#define HAL_H7SEG_7SEG_H_

#include "../../LIB/StdTypes.h"

typedef struct
{
	u8 Data_Port ;
	u8 Comm_Port ;
	u8 Type      ;
}Seg_t;

#define COMM_ANODE    1
#define COMM_CATHODE  2

#define H7SEG_DIG0    0
#define H7SEG_DIG1    1
#define H7SEG_DIG2    2
#define H7SEG_DIG3    3
#define H7SEG_DIG4    4
#define H7SEG_DIG5    5

#define H7SEG_OFF    10

void H7SEG_voidInit     (Seg_t A_xSeg              ) ;
void H7SEG_voidDisplay  (Seg_t A_xSeg , u8* AP_u8Digits) ;
void H7SEG_voidRefresh  (Seg_t A_xSeg              ) ;
void H7SEG_voidOff      (Seg_t A_xSeg              ) ;

#endif /* HAL_H7SEG_7SEG_H_ */
