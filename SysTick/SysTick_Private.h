/************************************************/
/*  SysTick_Private.h                           */
/*  Created on: Sep 1, 2020                     */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/



#ifndef SYSTICK_PRIVATE_H_
#define SYSTICK_PRIVATE_H_

/*********************************************************************************/

/* SysTick registers bases */

#define STK_STCTRL_REG      (( volatile uint32* )( 0xE000E010 ))

#define STK_STRELOAD_REG    (( volatile uint32* )( 0xE000E014 ))

#define STK_STCURRENT_REG   (( volatile uint32* )( 0xE000E018 ))

/*********************************************************************************/

/* location of control bits inside STCTRL register */

#define STK_ENABLE_BIT_POS      0
#define STK_INTEN_BIT_POS       1
#define STK_CLK_SRC_BIT_POS     2
#define STK_COUNT_BIT_POS       16


/*********************************************************************************/

void SysTick_ISR (void) ;


#endif /* SYSTICK_PRIVATE_H_ */
