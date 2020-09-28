/************************************************/
/*  SysTick.h                                   */
/*  Created on: Sep 1, 2020                     */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/


#ifndef SYSTICK_H_
#define SYSTICK_H_


#include "../Common/Utils.h"
#include "SysTick_Cfg.h"


/*********************************************************************************/

/*
 * privilege, synchronous, Reentrant function .
 * use this function to start SysTick Timer operation .
 * this function will start counting pulse coming to SysTick
 * from point it stop counting
 * call this function after establish all timer settings
 *
 */

void SysTick_StartTimer (void) ;


/*********************************************************************************/

/*
 * privilege, synchronous, Reentrant function .
 * use this function to stop SysTick Timer operation .
 * this function will stop counting pulse coming to SysTick
 *
 */

void SysTick_StopTimer (void) ;


/*********************************************************************************/

/*
 * privilege, synchronous, Reentrant function .
 * this function will enable interrupt of SysTick Timer
 * interrupt ISR will be executed when Timer flag is set
 *
 */

void SysTick_EnableInterrupt (void) ;


/*********************************************************************************/

/*
 * privilege, synchronous, Reentrant function .
 * this function will disable interrupt of SysTick Timer
 * interrupt ISR won't be executed when Timer flag is set
 *
 */

void SysTick_DisableInterrupt (void) ;


/*********************************************************************************/

/*
 * privilege, synchronous, Reentrant function .
 * this function will select source of Timer input signal between two options .
 * it will select system clock ( CPU clock ) if function input ( SystemClock ) is TRUE .
 * it will select PIOSC/4 ( 4 MHz ) if function input ( SystemClock ) is FALSE .
 *
 */


void SysTick_SelectClock ( boolean SystemClock ) ;


/*********************************************************************************/

/*
 * privilege, synchronous, Reentrant function .
 * this function will return state of Timer flag .
 * Timer Flag will be set when Timer reach 0 and if interrupt is enabled ISR will be executed .
 * when this function is used Timer flag will be cleared .
 *
 */

boolean SysTick_GetTimerFlag (void) ;


/*********************************************************************************/

/*
 * privilege, synchronous, Reentrant function .
 * this function will stop timer operation till use one of this functions,
 * SysTick_BusyWait, SysTick_SingleNotification, SysTick_PeriodicNotification .
 * this function will clear all timer data and cancel any running operation ,
 * unlike SysTick_DisableInterrupt which just stop timer counting.
 *
 */

void SysTick_ClearTimer (void) ;


/*********************************************************************************/

/*
 * privilege, synchronous, non Reentrant function .
 * this function will make processor enter idle loop ,
 * for number of ticks = (RoundTicks + 1) * RoundsNumber .
 * this function won't be interrupted if SYSTICK_BUSY_WAIT_CS = TRUE .
 * this function will execute SysTick_StartTimer function inside it and won't stop it .
 * if this function interrupted and any operation change Timer setting or call for,
 * SysTick_BusyWait, SysTick_SingleNotification, SysTick_PeriodicNotification ,
 * the behave will be unexpected .
 * previously three mentioned functions cancel each other operations .
 * after finishing this function timer will be cleared like using SysTick_ClearTimer .
 *
 */

void SysTick_BusyWait ( uint32 RoundTicks, uint8 RoundsNumber ) ;


/*********************************************************************************/

/*
 * privilege, asynchronous, non Reentrant function .
 * this function will call function pointed by input (FuncPtr) once,
 * after number of ticks = (RoundTicks + 1) * RoundsNumber .
 * this function won't be interrupted if SYSTICK_SINGLE_NOT_CS = TRUE .
 * if this function interrupted and any operation change Timer setting or call for,
 * SysTick_BusyWait, SysTick_SingleNotification, SysTick_PeriodicNotification ,
 * the behave will be unexpected .
 * this function won't finish its work before return so ,
 * timer setting cannot be changed till FuncPtr is called or behavior won't be expected .
 * previously three mentioned functions cancel each other operations .
 * after finishing this function timer will be cleared like using SysTick_ClearTimer .
 *
 */

void SysTick_SingleNotification ( uint32 RoundTicks, uint8 RoundsNumber, void (* FuncPtr) (void) ) ;


/*********************************************************************************/

/*
 * privilege, asynchronous, non Reentrant function .
 * this function will call function pointed by input (FuncPtr) periodically,
 * every number of ticks = (RoundTicks + 1) * RoundsNumber .
 * this function won't be interrupted if SYSTICK_PERIODIC_NOT_CS = TRUE .
 * if this function interrupted and any operation change Timer setting or call for,
 * SysTick_BusyWait, SysTick_SingleNotification, SysTick_PeriodicNotification ,
 * the behave will be unexpected .
 * previously three mentioned functions cancel each other operations .
 * so if one of them called it will cancel and stop this function operations
 *
 */

void SysTick_PeriodicNotification ( uint32 RoundTicks, uint8 RoundsNumber, void (* FuncPtr) (void) );


/*********************************************************************************/


#endif /* SYSTICK_H_ */
