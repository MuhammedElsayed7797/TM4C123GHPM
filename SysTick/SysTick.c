/************************************************/
/*  SysTick.c                                   */
/*  Created on: Sep 1, 2020                     */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/

#include "SysTick.h"
#include "SysTick_Private.h"

/*********************************************************************************/

/* used to indicate single or periodic notification, TRUE for periodic */
boolean SysTick_SingleNotification_Flag = FALSE ;

/* used to hold number of rounds of ticks */
uint8 SysTick_RoundsIsr = 0 ;

/* used in case of periodic notification to resetting it */
uint8 SysTick_RoundsIsr_Temp = 0 ;

/* hold callback notification function */
void (* SysTick_CallBack_Ptr ) (void) = NULL_PTR ;


/*********************************************************************************/

/*
 * privilege, synchronous, Reentrant function .
 * use this function to start SysTick Timer operation .
 * this function will start counting pulse coming to SysTick
 * from point it stop counting
 * call this function after establish all timer settings
 *
 */

void SysTick_StartTimer (void)
{

    SET_BIT( *STK_STCTRL_REG, STK_ENABLE_BIT_POS ) ;

    return ;
}


/*********************************************************************************/

/*
 * privilege, synchronous, Reentrant function .
 * use this function to stop SysTick Timer operation .
 * this function will stop counting pulse coming to SysTick
 *
 */

void SysTick_StopTimer (void)
{

    CLR_BIT( *STK_STCTRL_REG, STK_ENABLE_BIT_POS ) ;

    return ;
}


/*********************************************************************************/

/*
 * privilege, synchronous, Reentrant function .
 * this function will enable interrupt of SysTick Timer
 * interrupt ISR will be executed when Timer flag is set
 *
 */

void SysTick_EnableInterrupt (void)
{

    SET_BIT( *STK_STCTRL_REG, STK_INTEN_BIT_POS ) ;

    return ;
}


/*********************************************************************************/

/*
 * privilege, synchronous, Reentrant function .
 * this function will disable interrupt of SysTick Timer
 * interrupt ISR won't be executed when Timer flag is set
 *
 */

void SysTick_DisableInterrupt (void)
{

    CLR_BIT( *STK_STCTRL_REG, STK_INTEN_BIT_POS ) ;

    return ;
}


/*********************************************************************************/

/*
 * privilege, synchronous, Reentrant function .
 * this function will select source of Timer input signal between two options .
 * it will select system clock ( CPU clock ) if function input ( SystemClock ) is TRUE .
 * it will select PIOSC/4 ( 4 MHz ) if function input ( SystemClock ) is FALSE .
 *
 */

void SysTick_SelectClock ( boolean SystemClock )
{

    ASSIGN_BIT( *STK_STCTRL_REG, STK_CLK_SRC_BIT_POS, SystemClock ) ;

    return ;
}


/*********************************************************************************/

/*
 * privilege, synchronous, Reentrant function .
 * this function will return state of Timer flag .
 * Timer Flag will be set when Timer reach 0 and if interrupt is enabled ISR will be executed .
 * when this function is used Timer flag will be cleared .
 *
 */

boolean SysTick_GetTimerFlag (void)
{
    return GET_BIT( *STK_STCTRL_REG, STK_COUNT_BIT_POS ) ;
}


/*********************************************************************************/

/*
 * privilege, synchronous, Reentrant function .
 * this function will stop timer operation till use one of this functions,
 * SysTick_BusyWait, SysTick_SingleNotification, SysTick_PeriodicNotification .
 * this function will clear all timer data and cancel any running operation ,
 * unlike SysTick_DisableInterrupt which just stop timer counting.
 *
 */

void SysTick_ClearTimer (void)
{
    *STK_STRELOAD_REG = 0  ;
    *STK_STCURRENT_REG = 0 ;

    return ;
}


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

void SysTick_BusyWait ( uint32 RoundTicks, uint8 RoundsNumber )
{

#if SYSTICK_BUSY_WAIT_CS ==  TRUE

    CS_ON ;

#endif

    *STK_STCURRENT_REG = 0 ;
    *STK_STRELOAD_REG = RoundTicks  ;
    SET_BIT( *STK_STCTRL_REG, STK_ENABLE_BIT_POS ) ;

    do
    {
        while( ! (GET_BIT( *STK_STCTRL_REG, STK_COUNT_BIT_POS )) ) ;

    }
    while( RoundsNumber -- ) ;

    /* clear timer setting */
    *STK_STRELOAD_REG = 0  ;
    *STK_STCURRENT_REG = 0 ;

#if SYSTICK_BUSY_WAIT_CS ==  TRUE

    CS_OFF ;

#endif

    return ;
}


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

void SysTick_SingleNotification ( uint32 RoundTicks, uint8 RoundsNumber, void (* FuncPtr) (void) )
{

#if SYSTICK_SINGLE_NOT_CS ==  TRUE

    CS_ON ;

#endif

    *STK_STCURRENT_REG = 0 ;
    *STK_STRELOAD_REG = RoundTicks  ;

    SysTick_SingleNotification_Flag = TRUE ;
    SysTick_RoundsIsr = RoundsNumber ;
    SysTick_CallBack_Ptr =FuncPtr ;


#if SYSTICK_SINGLE_NOT_CS ==  TRUE

    CS_OFF ;

#endif

    return ;
}


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

void SysTick_PeriodicNotification ( uint32 RoundTicks, uint8 RoundsNumber, void (* FuncPtr) (void) )
{

#if SYSTICK_PERIODIC_NOT_CS ==  TRUE

    CS_OFF ;

#endif

    *STK_STCURRENT_REG = 0 ;
    *STK_STRELOAD_REG = RoundTicks  ;

    SysTick_SingleNotification_Flag = FALSE ;
    SysTick_RoundsIsr = RoundsNumber ;
    SysTick_RoundsIsr_Temp = RoundsNumber ;
    SysTick_CallBack_Ptr =FuncPtr ;


#if SYSTICK_PERIODIC_NOT_CS ==  TRUE

    CS_OFF ;

#endif

    return ;
}


/*********************************************************************************/

/* this is ISR of SysTick timer called when timer flag is set */
void SysTick_ISR (void)
{
    /* to clear timer flag */
    GET_BIT( *STK_STCTRL_REG, STK_COUNT_BIT_POS ) ;

    if ( SysTick_RoundsIsr )
    {
        SysTick_RoundsIsr -- ;
    }
    else
    {


        SysTick_CallBack_Ptr () ;
        if ( SysTick_SingleNotification_Flag )
        {
            /* case of single notification */
            /* clear timer operation */
            *STK_STRELOAD_REG = 0  ;
            *STK_STCURRENT_REG = 0 ;
            SysTick_CallBack_Ptr =  NULL_PTR ;

        }
        else
        {
            /* case of periodic notification */
            /* resetting periodic notification */
            SysTick_RoundsIsr = SysTick_RoundsIsr_Temp ;
        }
    }
    return ;
}


/*********************************************************************************/
