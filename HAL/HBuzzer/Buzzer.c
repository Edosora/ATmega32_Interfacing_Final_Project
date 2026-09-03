/*
 * Buzzer.c
 *
 *  Created on: Aug 29, 2026
 *      Author: Mohammed
 */
#include "../../LIB/BitMath.h"
#include "../../LIB/StdTypes.h"

#include "../../MCAL/MDIO/DIO.h"
#include "Buzzer.h"

void HBuzzer_voidBuzzerInit  (u8 A_u8PortName , u8 A_u8PinNumber)
{
	MDIO_voidInitPin(A_u8PortName, A_u8PinNumber, DIO_OUTPUT) ;
}
void HBuzzer_voidBuzzerOn    (u8 A_u8PortName , u8 A_u8PinNumber)
{
	MDIO_voidSetPinValue(A_u8PortName, A_u8PinNumber, DIO_HIGH) ;
}
void HBuzzer_voidBuzzerOff   (u8 A_u8PortName , u8 A_u8PinNumber)
{
	MDIO_voidSetPinValue(A_u8PortName, A_u8PinNumber, DIO_LOW) ;
}
void HBuzzer_voidBuzzerTog   (u8 A_u8PortName , u8 A_u8PinNumber)
{
	MDIO_voidTogPinValue(A_u8PortName , A_u8PinNumber) ;
}


