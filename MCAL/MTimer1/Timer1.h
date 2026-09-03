/*
 * Timer1.h
 *
 *  Created on: Aug 30, 2026
 *      Author: Mohammed
 */

#ifndef MCAL_MTIMER1_TIMER1_H_
#define MCAL_MTIMER1_TIMER1_H_

#define TIMER1_PRESCALLER1        1
#define TIMER1_PRESCALLER8        8
#define TIMER1_PRESCALLER64       64
#define TIMER1_PRESCALLER256      256
#define TIMER1_PRESCALLER1024     1024

#define TIMER1_OVER_FLOW_MODE              1
#define TIMER1_PWM_PHASE_CORRECT_8BIT      2
#define TIMER1_PWM_PHASE_CORRECT_9BIT      3
#define TIMER1_PWM_PHASE_CORRECT_10BIT     4
#define TIMER1_CTC_TOP_OCR1A               5
#define TIMER1_FAST_PWM_8BIT               6
#define TIMER1_FAST_PWM_9BIT               7
#define TIMER1_FAST_PWM_10BIT              8
#define TIMER1_FREQ_CORRECT_TOP_ICR1       9
#define TIMER1_FREQ_CORRECT_TOP_OCR1A      10
#define TIMER1_PHASE_CORRECT_TOP_ICR1      11
#define TIMER1_PHASE_CORRECT_TOP_OCR1A     12
#define TIMER1_CTC_TOP_ICR1                13
#define TIMER1_FAST_PWM_TOP_ICR1           14
#define TIMER1_FAST_PWM_TOP_OCR1A          15

#define TCCR1A    (*(volatile u8*)(0x4F))
#define TCCR1B    (*(volatile u8*)(0x4E))
#define TCNT1     (*(volatile u16*)(0x4C))
#define OCR1A     (*(volatile u16*)(0x4A))
#define OCR1B     (*(volatile u16*)(0x48))
#define ICR1      (*(volatile u16*)(0x46))
#define TIMSK     (*(volatile u8*)(0x59))
#define TIFR      (*(volatile u8*)(0x58))
#define SREG      (*(volatile u8*)(0x5F))

void MTimer1_voidInit                 (u16 A_u16Prescaller , u8 A_u8Mode) ;
void MTimer1_voidSetDesiredTime       (u32 A_u32TimeInMicro , void (*fptr)(void)) ;
void MTimer1_voidSetCompareMatchValueA (u32 A_u32CTCValue) ;
void MTimer1_voidSetCompareMatchValueB (u32 A_u32CTCValue) ;

#endif /* MCAL_MTIMER1_TIMER1_H_ */
