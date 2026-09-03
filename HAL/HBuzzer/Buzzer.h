/*
 * Buzzer.h
 *
 *  Created on: Aug 29, 2026
 *      Author: Mohammed
 */

#ifndef HAL_HBUZZER_BUZZER_H_
#define HAL_HBUZZER_BUZZER_H_

#include "../../LIB/StdTypes.h"

void HBuzzer_voidBuzzerInit  (u8 A_u8PortName , u8 A_u8PinNumber) ;
void HBuzzer_voidBuzzerOn    (u8 A_u8PortName , u8 A_u8PinNumber) ;
void HBuzzer_voidBuzzerOff   (u8 A_u8PortName , u8 A_u8PinNumber) ;
void HBuzzer_voidBuzzerTog   (u8 A_u8PortName , u8 A_u8PinNumber) ;


#endif // HAL_HBUZZER_BUZZER_H_
