/*
 * DIO.h
 *
 *  Created on: Aug 29, 2026
 *      Author: Mohammed
 */

#ifndef MCAL_MDIO_DIO_H_
#define MCAL_MDIO_DIO_H_

#include "../../LIB/StdTypes.h"

#define DIO_PORTA   0
#define DIO_PORTB   1
#define DIO_PORTC   2
#define DIO_PORTD   3

#define DIO_PIN0   0
#define DIO_PIN1   1
#define DIO_PIN2   2
#define DIO_PIN3   3
#define DIO_PIN4   4
#define DIO_PIN5   5
#define DIO_PIN6   6
#define DIO_PIN7   7

#define DIO_INPUT  0
#define DIO_OUTPUT 1

#define DIO_LOW    0
#define DIO_HIGH   1

#define DDRA     (*(volatile u8*)(0x3A))
#define PORTA    (*(volatile u8*)(0x3B))
#define PINA     (*(volatile u8*)(0x39))
#define DDRB     (*(volatile u8*)(0x37))
#define PORTB    (*(volatile u8*)(0x38))
#define PINB     (*(volatile u8*)(0x36))
#define DDRC     (*(volatile u8*)(0x34))
#define PORTC    (*(volatile u8*)(0x35))
#define PINC     (*(volatile u8*)(0x33))
#define DDRD     (*(volatile u8*)(0x31))
#define PORTD    (*(volatile u8*)(0x32))
#define PIND     (*(volatile u8*)(0x30))


void MDIO_voidInitPin     (u8 A_u8PortName , u8 A_u8PinNumber , u8 A_u8Mode ) ;
void MDIO_voidSetPinValue (u8 A_u8PortName , u8 A_u8PinNumber , u8 A_u8Value) ;
void MDIO_voidTogPinValue (u8 A_u8PortName , u8 A_u8PinNumber               ) ;
u8   MDIO_u8GetPinValue   (u8 A_u8PortName , u8 A_u8PinNumber               ) ;

void MDIO_voidInitPort    (u8 A_u8PortName , u8 A_u8Mode                    ) ;
void MDIO_voidSetPortValue(u8 A_u8PortName , u8 A_u8Value                   ) ;
void MDIO_voidTogPortValue(u8 A_u8PortName                                  ) ;
u8   MDIO_u8GetPortValue  (u8 A_u8PortName                                  ) ;
#endif // MCAL_MDIO_DIO_H_
