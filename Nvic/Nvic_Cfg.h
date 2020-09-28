/************************************************/
/*  Nvic_Cfg.h                                  */
/*  Created on: Sep 1, 2020                     */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/


#ifndef NVIC_CFG_H_
#define NVIC_CFG_H_


/*********************************************************************************/

/*
 * for ARM NVIC module every interrupt priority is define by 8 bits ,
 * but not all vendors use all bits to decrease system complexity and overhead .
 * this MACRO define number of reserved (not used) bits of priority bits ,
 * change it according to vendor or according to your code logic
 *
 */

#define NVIC_PRIORITY_RESERVED_BITS     5


/*
 * ARM NVIC could control up to 256 interrupt but vendors don't use all 255 interrupt,
 * to decrease system complexity and overhead .
 * this MACRO to determine number of interrupts provided by vendor must be between 1 ~ 256
 */

#define NVIC_VENDOR_INTERRUPTS_NUMBER   139


/*********************************************************************************/

/*
 * ARM NVIC could control up to 256 interrupt but vendors don't use all 255 interrupt,
 * to decrease system complexity and overhead .
 * every bit in below MACROS represent enable state of corresponding interrupt number,
 * LSB bit in NVIC_ENABLE_INTERRUPT_0_31 will represent interrupt 0 enable state .
 * if bit = 1 then interrupt will be enabled after execution of Nvic_Init function,
 * else interrupt will be disabled .
 */

#define NVIC_ENABLE_INTERRUPT_0_31      0x00000000
#define NVIC_ENABLE_INTERRUPT_32_63     0x00000000
#define NVIC_ENABLE_INTERRUPT_64_95     0x00000000
#define NVIC_ENABLE_INTERRUPT_96_127    0x00000000
#define NVIC_ENABLE_INTERRUPT_128_159   0x00000000
#define NVIC_ENABLE_INTERRUPT_160_191   0x00000000
#define NVIC_ENABLE_INTERRUPT_192_223   0x00000000
#define NVIC_ENABLE_INTERRUPT_224_255   0x00000000


/*********************************************************************************/

/*
 * ARM NVIC could control up to 256 interrupt but vendors don't use all 255 interrupt,
 * to decrease system complexity and overhead .
 * every bit in below MACROS represent pending flag state of corresponding interrupt number,
 * LSB bit in NVIC_PEND_INTERRUPT_0_31 will represent interrupt 0 pending flag state .
 * if bit = 1 then interrupt will be pended after execution of Nvic_Init function,
 * else interrupt will be not pended .
 */

#define NVIC_PEND_INTERRUPT_0_31        0x00000000
#define NVIC_PEND_INTERRUPT_32_63       0x00000000
#define NVIC_PEND_INTERRUPT_64_95       0x00000000
#define NVIC_PEND_INTERRUPT_96_127      0x00000000
#define NVIC_PEND_INTERRUPT_128_159     0x00000000
#define NVIC_PEND_INTERRUPT_160_191     0x00000000
#define NVIC_PEND_INTERRUPT_192_223     0x00000000
#define NVIC_PEND_INTERRUPT_224_255     0x00000000


/*********************************************************************************/


#endif /* NVIC_CFG_H_ */
