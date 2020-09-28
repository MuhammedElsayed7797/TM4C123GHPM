/************************************************/
/*  Nvic.h                                      */
/*  Created on: Sep 1, 2020                     */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/


#ifndef NVIC_H_
#define NVIC_H_


#include "../Common/Utils.h"
#include "Nvic_Cfg.h"


/*********************************************************************************/

/*
 * privilege, synchronous, non Reentrant function .
 * use this function to initialize NVIC according to configuration in Nvic_Cfg.h file .
 * used to initialize the enable and pend state of all NVIC interrupts in system ( not processor interrupts ) .
 *
 */

void Nvic_Init (void) ;


/*********************************************************************************/

/*
 * privilege, synchronous, Reentrant function .
 * use this function to set priority of interrupt defined by InterruptID .
 * the lower the Priority the higher level of interrupt .
 * Priority is divided to group and sub priority according to setting in SCB module .
 * priority for ARM defined by 8 bits, not all vendors use them all,
 * NVIC_PRIORITY_RESERVED_BITS determine number of reserved bits from 8 bits,
 * initialize it according to your vendor or code logic .
 *
 */

void Nvic_SetPriority ( uint8 InterruptID, uint8 Priority ) ;


/*********************************************************************************/

/*
 * privilege, synchronous,  Reentrant function .
 * this function used to enable interrupt defined by InterruptID
 *
 */

void Nvic_EnableInterrupt ( uint8 InterruptID ) ;


/*********************************************************************************/

/*
 * privilege, synchronous,  Reentrant function .
 * this function used to disable interrupt defined by InterruptID
 *
 */

void Nvic_DisableInterrupt ( uint8 InterruptID ) ;


/*********************************************************************************/

/*
 * privilege, synchronous,  Reentrant function .
 * this function used to set pend flag of interrupt defined by InterruptID .
 * if pend flag is set and interrupt is enabled interrupt will triggered and ISR executed .
 *
 */

void Nvic_SetPendingFlag ( uint8 InterruptID ) ;


/*********************************************************************************/

/*
 * privilege, synchronous,  Reentrant function .
 * this function used to clear pend flag of interrupt defined by InterruptID .
 * pend flag is set whenever interrupt's event is happened,
 * and cleared automatically when ISR start to execute .
 * if pend flag is cleared before ISR get start, interrupt won't trigger any ISR,
 * this happen in case of interrupt is disabled or waiting for another ISR (interrupt nesting) .
 *
 */

void Nvic_ClearPendingFlag ( uint8 InterruptID ) ;


/*********************************************************************************/

/*
 * privilege, synchronous,  Reentrant function .
 * this function used to get enable state of interrupt defined by InterruptID .
 * if return value is TRUE then interrupt is enabled, else interrupt is disabled .
 *
 */

boolean Nvic_GetEnable ( uint8 InterruptID ) ;


/*********************************************************************************/

/*
 * privilege, synchronous,  Reentrant function .
 * this function used to get pend flag state of interrupt defined by InterruptID .
 * if return value is TRUE then flag is set, else flag is cleared .
 * pend flag will be cleared automatically when ISR start execution,
 * but if while execution interrupt event happened pend flag will be set during ISR execution ,
 * and if flag didn't cleared it ISR will be executed again after current ISR finish .
 *
 */

boolean Nvic_GetPendingFlag ( uint8 InterruptID ) ;


/*********************************************************************************/

/*
 * privilege, synchronous,  Reentrant function .
 * this function used to get active flag state of interrupt defined by InterruptID .
 * if return value is TRUE then flag is set, else flag is cleared .
 * active flag will be set when interrupt ISR start execution,
 * and will cleared automatically when execution finish .
 * if higher priority interrupt happened while executing ISR,
 * then two interrupts will be active .
 *
 */

boolean Nvic_GetActiveFlag ( uint8 InterruptID ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous,  Reentrant function .
 * this function will set pend flag of interrupt defined by InterruptID ,
 * and if interrupt is enabled its ISR will be executed .
 * this function just like Nvic_SetPendingFlag but its execution take less time ,
 * and don't need for privilege level
 * this function can't be used except after being enable using SCB module .
 *
 */

void Nvic_TriggerInterrupt ( uint8 InterruptID ) ;


/*********************************************************************************/


#endif /* NVIC_H_ */
