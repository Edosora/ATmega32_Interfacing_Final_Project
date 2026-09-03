/*
 * BitMath.h
 *
 *  Created on: Aug 29, 2026
 *      Author: Mohammed
 */

#ifndef LIB_BITMATH_H_
#define LIB_BITMATH_H_

#define SET_BIT(reg , bit)    ((reg)|=(1<<(bit)))
#define TOG_BIT(reg , bit)    ((reg)^=(1<<(bit)))
#define CLR_BIT(reg , bit)    ((reg)&=(~(1<<(bit))))
#define READ_BIT(reg , bit)   (((reg)&(1<<(bit)))>>(bit))

#endif // LIB_BITMATH_H_
