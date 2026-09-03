/*
 * KP.c
 *
 *  Created on: Aug 29, 2026
 *      Author: Mohammed
 */
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <util/delay.h>
#include "../../LIB/BitMath.h"
#include "../../LIB/StdTypes.h"

#include "../../MCAL/MDIO/DIO.h"

#include "KP.h"

static u8 G_u8KpData [4][4] =
				  {
						  {'7' , '4' , '1' , 'D'} ,
						  {'8' , '5' , '2' , '0'} ,
						  {'9' , '6' , '3' , '='} ,
						  {'/' , '*' , '-' , '+'}
				  } ;

void HKP_voidInit          (u8 A_u8PortName)
{
	MDIO_voidInitPort(A_u8PortName, 0xF0) ;
	MDIO_voidSetPortValue(A_u8PortName, 0xFF) ;
}
u8   HKP_u8GetPressedValue (u8 A_u8PortName)
{
	u8 L_u8Row ;
	u8 L_u8Col ;
	for (L_u8Col = 0 ; L_u8Col < 4 ; L_u8Col ++)
	{
		MDIO_voidSetPinValue(A_u8PortName, L_u8Col + 4, DIO_LOW) ;
		for (L_u8Row = 0 ; L_u8Row < 4 ; L_u8Row ++)
		{
			if (MDIO_u8GetPinValue(A_u8PortName, L_u8Row) == KP_PRESSED)
			{
				_delay_ms(20) ;
				if (MDIO_u8GetPinValue(A_u8PortName, L_u8Row) == KP_PRESSED)
				{
					while (1)
					{
						while (MDIO_u8GetPinValue(A_u8PortName, L_u8Row) == KP_PRESSED) ;
						_delay_ms(20) ;
						if (MDIO_u8GetPinValue(A_u8PortName, L_u8Row) != KP_PRESSED)
						{
							break ;
						}
					}
					MDIO_voidSetPinValue(A_u8PortName, L_u8Col + 4, DIO_HIGH) ;
					return G_u8KpData [L_u8Col][L_u8Row] ;
				}
				else
				{
					MDIO_voidSetPinValue(A_u8PortName, L_u8Col + 4, DIO_HIGH) ;
					return KP_NOT_PRESSED ;
				}
			}
		}
		MDIO_voidSetPinValue(A_u8PortName, L_u8Col + 4, DIO_HIGH) ;
	}
	return KP_NOT_PRESSED ;
}
