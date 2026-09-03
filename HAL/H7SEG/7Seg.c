/*
 * 7Seg.c
 *
 * Created on: Aug 30, 2026
 * Author: Mohammed
 */

#include "../../LIB/BitMath.h"
#include "../../LIB/StdTypes.h"
#include "../../MCAL/MDIO/DIO.h"
#include "7Seg.h"

#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include <util/delay.h>

static u8 G_u8SegNumbers [] =
{
		0x3F ,
		0x06 ,
		0x5B ,
		0x4F ,
		0x66 ,
		0x6D ,
		0x7D ,
		0x07 ,
		0x7F ,
		0x6F
} ;

static u8* GP_u8Digits   = 0          ;
static u8  G_u8Active    = H7SEG_DIG0 ;

void H7SEG_voidInit (Seg_t A_xSeg)
{
	MDIO_voidInitPort(A_xSeg.Data_Port, 0xFF) ;
	MDIO_voidInitPort(A_xSeg.Comm_Port, 0xFF) ;

	MDIO_voidSetPortValue(A_xSeg.Data_Port, 0x00) ;

	if (A_xSeg.Type == COMM_CATHODE)
	{
		MDIO_voidSetPortValue(A_xSeg.Comm_Port, 0xFF) ;
	}
	else if (A_xSeg.Type == COMM_ANODE)
	{
		MDIO_voidSetPortValue(A_xSeg.Comm_Port, 0x00) ;
	}
}

void H7SEG_voidDisplay (Seg_t A_xSeg , u8* AP_u8Digits)
{
	GP_u8Digits = AP_u8Digits ;
	G_u8Active  = H7SEG_DIG0  ;
}

void H7SEG_voidRefresh (Seg_t A_xSeg)
{
	u8 L_u8CommValue = 0x00 ;
	u8 L_u8Number    = 0x00 ;

	if (GP_u8Digits == 0)
	{
		return ;
	}

	if (A_xSeg.Type == COMM_CATHODE)
	{
		L_u8CommValue = 0xFF ;
	}
	else if (A_xSeg.Type == COMM_ANODE)
	{
		L_u8CommValue = 0x00 ;
	}
	MDIO_voidSetPortValue(A_xSeg.Comm_Port, L_u8CommValue) ;

	L_u8Number = GP_u8Digits [G_u8Active] ;
	if (L_u8Number <= 9)
	{
		MDIO_voidSetPortValue(A_xSeg.Data_Port, G_u8SegNumbers [L_u8Number]) ;
	}
	else
	{
		MDIO_voidSetPortValue(A_xSeg.Data_Port, 0x00) ;
	}

	if (A_xSeg.Type == COMM_CATHODE)
	{
		CLR_BIT(L_u8CommValue , G_u8Active) ;
	}
	else if (A_xSeg.Type == COMM_ANODE)
	{
		SET_BIT(L_u8CommValue , G_u8Active) ;
	}
	MDIO_voidSetPortValue(A_xSeg.Comm_Port, L_u8CommValue) ;

	_delay_ms(2) ;

	G_u8Active ++ ;
	if (G_u8Active > H7SEG_DIG5)
	{
		G_u8Active = H7SEG_DIG0 ;
	}
}

void H7SEG_voidOff (Seg_t A_xSeg)
{
	GP_u8Digits = 0 ;
	MDIO_voidSetPortValue(A_xSeg.Data_Port, 0x00) ;
	if (A_xSeg.Type == COMM_CATHODE)
	{
		MDIO_voidSetPortValue(A_xSeg.Comm_Port, 0xFF) ;
	}
	else if (A_xSeg.Type == COMM_ANODE)
	{
		MDIO_voidSetPortValue(A_xSeg.Comm_Port, 0x00) ;
	}
}
