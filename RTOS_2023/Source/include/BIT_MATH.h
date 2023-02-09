/*
 * BIT_MATH.h
 *
 *  Created on: Feb 8, 2023
 *      Author: wario
 */

#ifndef SOURCE_INCLUDE_BIT_MATH_H_
#define SOURCE_INCLUDE_BIT_MATH_H_

#define  SET_BIT(REG,BIT_NUM)    ((REG) |= ( 1 << (BIT_NUM)))
#define  CLR_BIT(REG,BIT_NUM)    ((REG) &= (~(1<< (BIT_NUM))))
#define  TOG_BIT(REG,BIT_NUM)    ((REG) ^= ( 1 << (BIT_NUM)))
#define  GET_BIT(REG,BIT_NUM)    (((REG) >> (BIT_NUM)) & 1)

#define  IS_LO(REG,BIT_NUM)      (!(((REG)>>(BIT_NUM))&1))
#define  IS_HI(REG,BIT_NUM)      (((REG)>>(BIT_NUM))&1)

#endif /* SOURCE_INCLUDE_BIT_MATH_H_ */
