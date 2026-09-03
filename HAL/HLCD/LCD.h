/*
 * LCD.h
 *
 *  Created on: Aug 29, 2026
 *      Author: Mohammed
 */

#ifndef HAL_HLCD_LCD_H_
#define HAL_HLCD_LCD_H_

#include "../../LIB/StdTypes.h"

#define LCD_PORT    DIO_PORTB

#define LCD_RS_PORT DIO_PORTB
#define LCD_RS_PIN  DIO_PIN0

#define LCD_RW_PORT DIO_PORTB
#define LCD_RW_PIN  DIO_PIN1

#define LCD_E_PORT  DIO_PORTB
#define LCD_E_PIN   DIO_PIN2

#define LCD_MODE     4

#define LCD_ROW0    0
#define LCD_ROW1    1

#define LCD_COL0    0
#define LCD_COL1    1
#define LCD_COL2    2
#define LCD_COL3    3
#define LCD_COL4    4
#define LCD_COL5    5
#define LCD_COL6    6
#define LCD_COL7    7
#define LCD_COL8    8
#define LCD_COL9    9
#define LCD_COL10   10
#define LCD_COL11   11
#define LCD_COL12   12
#define LCD_COL13   13
#define LCD_COL14   14
#define LCD_COL15   15

#define LCD_BLOCK0  0
#define LCD_BLOCK1  1
#define LCD_BLOCK2  2
#define LCD_BLOCK3  3
#define LCD_BLOCK4  4
#define LCD_BLOCK5  5
#define LCD_BLOCK6  6
#define LCD_BLOCK7  7

void HLCD_voidInit      (void) ;
void HLCD_voidWriteData (u8 A_u8Data) ;
void HLCD_voidWriteCmd  (u8 A_u8Cmd) ;
void HLCD_voidDisplayStr(u8* AP_u8Str) ;
void HLCD_voidClrScreen (void) ;
void HLCD_voidShiftLeft (void) ;
void HLCD_voidShiftRight(void) ;
void HLCD_voidMoveCursor(u8 A_u8Row , u8 A_u8Col) ;
void HLCD_voidDisplayCustomChar (u8 AR_u8Pattern [] , u8 A_u8BlockNumber , u8 A_u8Row , u8 A_u8Col) ;
#endif // HAL_HLCD_LCD_H_
