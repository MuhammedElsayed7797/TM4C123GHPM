/************************************************/
/*  Nvic_Private.h                              */
/*  Created on: Sep 1, 2020                     */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/



#ifndef NVIC_PRIVATE_H_
#define NVIC_PRIVATE_H_


/*********************************************************************************/

/* NVIC registre bases */

#define NVIC_ENABLE_REG_BASE    (( volatile uint32* )( 0xE000E100 ))

#define NVIC_DISABLE_REG_BASE   (( volatile uint32* )( 0xE000E180 ))

#define NVIC_PEND_REG_BASE      (( volatile uint32* )( 0xE000E200 ))

#define NVIC_UNPEND_REG_BASE    (( volatile uint32* )( 0xE000E280 ))

#define NVIC_ACTIVE_REG_BASE    (( volatile uint32* )( 0xE000E300 ))

#define NVIC_PRIORITY_REG_BASE  (( volatile uint8* )( 0xE000E400 ))     /* byte accessible*/

#define NVIC_TRIGGER_REG_BASE   (( volatile uint32* )( 0xE000EF00 ))


/*********************************************************************************/

/* width (resolution) of registers */
#define NVIC_REGISTER_OFFSET    32


/*********************************************************************************/


#endif /* NVIC_PRIVATE_H_ */
