/*
 * LCD.c
 *
 *  Created on: Aug 29, 2026
 *      Author: Mohammed
 */
#include "../../LIB/BitMath.h"
#include "../../LIB/StdTypes.h"

#include "../../MCAL/MDIO/DIO.h"
#include "LCD.h"

#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include <util/delay.h>
void HLCD_voidInit      (void)
{
#if LCD_MODE == 8
	_delay_ms(50) ;
	MDIO_voidInitPort(LCD_PORT, 0xFF) ;
	MDIO_voidInitPin(LCD_RS_PORT, LCD_RS_PIN, DIO_OUTPUT) ;
	MDIO_voidInitPin(LCD_RW_PORT, LCD_RW_PIN, DIO_OUTPUT) ;
	MDIO_voidInitPin(LCD_E_PORT , LCD_E_PIN , DIO_OUTPUT) ;
	HLCD_voidWriteCmd(0x38) ;
	_delay_ms(1) ;
	HLCD_voidWriteCmd(0x0E) ;
	_delay_ms(1) ;
	HLCD_voidWriteCmd(0x01) ;
	_delay_ms(3) ;
	HLCD_voidWriteCmd(0x06) ;
	_delay_ms(1) ;
#elif LCD_MODE == 4
	_delay_ms(50) ;
	MDIO_voidInitPin(LCD_PORT, DIO_PIN4, DIO_OUTPUT) ;
	MDIO_voidInitPin(LCD_PORT, DIO_PIN5, DIO_OUTPUT) ;
	MDIO_voidInitPin(LCD_PORT, DIO_PIN6, DIO_OUTPUT) ;
	MDIO_voidInitPin(LCD_PORT, DIO_PIN7, DIO_OUTPUT) ;
	MDIO_voidInitPin(LCD_RS_PORT, LCD_RS_PIN, DIO_OUTPUT) ;
	MDIO_voidInitPin(LCD_RW_PORT, LCD_RW_PIN, DIO_OUTPUT) ;
	MDIO_voidInitPin(LCD_E_PORT , LCD_E_PIN , DIO_OUTPUT) ;
	HLCD_voidWriteCmd(0x02) ;
	_delay_ms(1) ;
	HLCD_voidWriteCmd(0x28) ;
	_delay_ms(1) ;
	HLCD_voidWriteCmd(0x0E) ;
	_delay_ms(1) ;
	HLCD_voidWriteCmd(0x01) ;
	_delay_ms(3) ;
	HLCD_voidWriteCmd(0x06) ;
	_delay_ms(1) ;
#endif
}
void HLCD_voidWriteData (u8 A_u8Data)
{
#if LCD_MODE == 8
	MDIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_HIGH) ;
	MDIO_voidSetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_LOW) ;
	MDIO_voidSetPortValue(LCD_PORT, A_u8Data) ;
	MDIO_voidSetPinValue(LCD_E_PORT , LCD_E_PIN, DIO_HIGH) ;
	_delay_ms(1) ;
	MDIO_voidSetPinValue(LCD_E_PORT , LCD_E_PIN, DIO_LOW) ;
	_delay_ms(1) ;
#elif LCD_MODE == 4
	MDIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_HIGH) ;
	MDIO_voidSetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_LOW) ;

	MDIO_voidSetPinValue(LCD_PORT, DIO_PIN4, READ_BIT(A_u8Data , 4)) ;
	MDIO_voidSetPinValue(LCD_PORT, DIO_PIN5, READ_BIT(A_u8Data , 5)) ;
	MDIO_voidSetPinValue(LCD_PORT, DIO_PIN6, READ_BIT(A_u8Data , 6)) ;
	MDIO_voidSetPinValue(LCD_PORT, DIO_PIN7, READ_BIT(A_u8Data , 7)) ;

	MDIO_voidSetPinValue(LCD_E_PORT , LCD_E_PIN, DIO_HIGH) ;
	_delay_ms(1) ;
	MDIO_voidSetPinValue(LCD_E_PORT , LCD_E_PIN, DIO_LOW) ;
	_delay_ms(1) ;

	MDIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_HIGH) ;
	MDIO_voidSetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_LOW) ;

	MDIO_voidSetPinValue(LCD_PORT, DIO_PIN4, READ_BIT(A_u8Data , 0)) ;
	MDIO_voidSetPinValue(LCD_PORT, DIO_PIN5, READ_BIT(A_u8Data , 1)) ;
	MDIO_voidSetPinValue(LCD_PORT, DIO_PIN6, READ_BIT(A_u8Data , 2)) ;
	MDIO_voidSetPinValue(LCD_PORT, DIO_PIN7, READ_BIT(A_u8Data , 3)) ;

	MDIO_voidSetPinValue(LCD_E_PORT , LCD_E_PIN, DIO_HIGH) ;
	_delay_ms(1) ;
	MDIO_voidSetPinValue(LCD_E_PORT , LCD_E_PIN, DIO_LOW) ;
	_delay_ms(1) ;
#endif
}
void HLCD_voidWriteCmd  (u8 A_u8Cmd)
{
#if LCD_MODE == 8
	MDIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_LOW) ;
	MDIO_voidSetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_LOW) ;
	MDIO_voidSetPortValue(LCD_PORT, A_u8Cmd) ;
	MDIO_voidSetPinValue(LCD_E_PORT , LCD_E_PIN, DIO_HIGH) ;
	_delay_ms(1) ;
	MDIO_voidSetPinValue(LCD_E_PORT , LCD_E_PIN, DIO_LOW) ;
	_delay_ms(1) ;
#elif LCD_MODE == 4
	MDIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_LOW) ;
	MDIO_voidSetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_LOW) ;

	MDIO_voidSetPinValue(LCD_PORT, 4, READ_BIT(A_u8Cmd , 4)) ;
	MDIO_voidSetPinValue(LCD_PORT, 5, READ_BIT(A_u8Cmd , 5)) ;
	MDIO_voidSetPinValue(LCD_PORT, 6, READ_BIT(A_u8Cmd , 6)) ;
	MDIO_voidSetPinValue(LCD_PORT, 7, READ_BIT(A_u8Cmd , 7)) ;

	MDIO_voidSetPinValue(LCD_E_PORT , LCD_E_PIN, DIO_HIGH) ;
	_delay_ms(1) ;
	MDIO_voidSetPinValue(LCD_E_PORT , LCD_E_PIN, DIO_LOW) ;
	_delay_ms(1) ;

	MDIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_LOW) ;
	MDIO_voidSetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_LOW) ;

	MDIO_voidSetPinValue(LCD_PORT, 4, READ_BIT(A_u8Cmd , 0)) ;
	MDIO_voidSetPinValue(LCD_PORT, 5, READ_BIT(A_u8Cmd , 1)) ;
	MDIO_voidSetPinValue(LCD_PORT, 6, READ_BIT(A_u8Cmd , 2)) ;
	MDIO_voidSetPinValue(LCD_PORT, 7, READ_BIT(A_u8Cmd , 3)) ;

	MDIO_voidSetPinValue(LCD_E_PORT , LCD_E_PIN, DIO_HIGH) ;
	_delay_ms(1) ;
	MDIO_voidSetPinValue(LCD_E_PORT , LCD_E_PIN, DIO_LOW) ;
	_delay_ms(1) ;
#endif
}
void HLCD_voidDisplayStr(u8* AP_u8Str)
{
	u8 L_u8Iterator = 0 ;
	while (AP_u8Str [L_u8Iterator] != '\0')
	{
		HLCD_voidWriteData(AP_u8Str [L_u8Iterator]) ;
		L_u8Iterator ++ ;
	}
}
void HLCD_voidClrScreen (void)
{
	HLCD_voidWriteCmd(0x01) ;
	_delay_ms(3) ;
}
void HLCD_voidShiftLeft (void)
{
	HLCD_voidWriteCmd(0x18) ;
		_delay_ms(1) ;
}
void HLCD_voidShiftRight(void)
{
	HLCD_voidWriteCmd(0x1C) ;
	_delay_ms(1) ;
}
void HLCD_voidMoveCursor(u8 A_u8Row , u8 A_u8Col)
{
	u8 L_u8DDRAMAddress ;
	if (A_u8Row == LCD_ROW0)
	{
		L_u8DDRAMAddress = A_u8Col ;
	}
	else if (A_u8Row == LCD_ROW1)
	{
		L_u8DDRAMAddress = A_u8Col + 0x40;
	}
	HLCD_voidWriteCmd(L_u8DDRAMAddress + 0x80) ;
}
void HLCD_voidDisplayCustomChar (u8 AR_u8Pattern [] , u8 A_u8BlockNumber , u8 A_u8Row , u8 A_u8Col)
{
	u8 L_u8Iterator ;
	u8 L_u8CGRAMAddress = 0x40 + A_u8BlockNumber*8 ;
	HLCD_voidWriteCmd(L_u8CGRAMAddress) ;
	for (L_u8Iterator = 0 ; L_u8Iterator < 8 ; L_u8Iterator++)
	{
		HLCD_voidWriteData(AR_u8Pattern [L_u8Iterator]) ;
	}
	HLCD_voidMoveCursor(A_u8Row, A_u8Col) ;
	HLCD_voidWriteData(A_u8BlockNumber) ;
}
