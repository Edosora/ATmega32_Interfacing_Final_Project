/*
 * Timer1.c
 *
 *  Created on: Aug 30, 2026
 *      Author: Mohammed
 */

#include "../../LIB/BitMath.h"
#include "../../LIB/StdTypes.h"

#include "Timer1.h"

#define TIMER1_CTC_OCR1A_VALUE    31250

static u32 G_u32Timer1Prescaller ;
static void (*Timer1_ptr)(void) = 0 ;

void MTimer1_voidInit (u16 A_u16Prescaller , u8 A_u8Mode)
{
	G_u32Timer1Prescaller = A_u16Prescaller ;
	TCNT1 = 0 ;

	switch (A_u16Prescaller)
	{
	case TIMER1_PRESCALLER1    :
		SET_BIT(TCCR1B , 0) ;
		CLR_BIT(TCCR1B , 1) ;
		CLR_BIT(TCCR1B , 2) ;
		break ;
	case TIMER1_PRESCALLER8    :
		CLR_BIT(TCCR1B , 0) ;
		SET_BIT(TCCR1B , 1) ;
		CLR_BIT(TCCR1B , 2) ;
		break ;
	case TIMER1_PRESCALLER64   :
		SET_BIT(TCCR1B , 0) ;
		SET_BIT(TCCR1B , 1) ;
		CLR_BIT(TCCR1B , 2) ;
		break ;
	case TIMER1_PRESCALLER256  :
		CLR_BIT(TCCR1B , 0) ;
		CLR_BIT(TCCR1B , 1) ;
		SET_BIT(TCCR1B , 2) ;
		break ;
	case TIMER1_PRESCALLER1024 :
		SET_BIT(TCCR1B , 0) ;
		CLR_BIT(TCCR1B , 1) ;
		SET_BIT(TCCR1B , 2) ;
		break ;
	}

	CLR_BIT(TCCR1A , 0) ;
	CLR_BIT(TCCR1A , 1) ;
	SET_BIT(TCCR1B , 3) ;
	CLR_BIT(TCCR1B , 4) ;
}

void MTimer1_voidSetDesiredTime (u32 A_u32TimeInMicro , void (*fptr)(void))
{
	u32 L_u32Value ;

	L_u32Value = (u32)( ( (u64)A_u32TimeInMicro * 8000000UL ) / ( (u32)G_u32Timer1Prescaller * 1000000UL ) ) ;

	OCR1A = L_u32Value ;
	Timer1_ptr = fptr ;

	SET_BIT(SREG , 7) ;
	SET_BIT(TIFR , 4) ;
	SET_BIT(TIMSK , 4) ;
}

void MTimer1_voidSetCompareMatchValueA (u32 A_u32CTCValue)
{
	OCR1A = A_u32CTCValue ;
}

void MTimer1_voidSetCompareMatchValueB (u32 A_u32CTCValue)
{
	OCR1B = A_u32CTCValue ;
}

void __vector_7 (void)__attribute__((signal)) ;
void __vector_7 (void)
{
	if (Timer1_ptr != 0)
	{
		Timer1_ptr () ;
	}
}
