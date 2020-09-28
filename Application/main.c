/************************************************/
/*  main.c                                      */
/*  Created on: Sep 1, 2020                     */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/

#include "../SysTick/SysTick.h"
#include "../Nvic/Nvic.h"
#include "../Port/Port.h"
#include "../Dio/Dio.h"
#include "../ExtInt/ExtInt.h"
#include "../S2I/S2I.h"




/*********************************************************************************/



#define NVIC_TEST_INTERRUPT_ID  10
boolean Nvic_Test_1 = TRUE ;

/*********************************************************************************/


void SysTick_IsrTest (void) ;
boolean SysTick_TestFlag = TRUE ;


/*********************************************************************************/

uint16 Spi_ReceiveBuffer [8] = {0} ;
uint8 counter = 0 ;
uint16 * SSI_Prtr = Spi_ReceiveBuffer ;

/*********************************************************************************/


int main (void)
{

    /*********************************************************************************/

    * ( ( volatile unsigned long * ) ( 0x400FE000 + 0x61C ) ) |= (0xF<<0) ;     /* enable SSI clock */
    * ( ( volatile unsigned long * ) ( 0x400FE000 + 0x608 ) ) |= 0x3F ;         /* enable clock for all ports */
    * ( ( volatile unsigned long * ) ( 0x400FE000 + 0x06C ) ) |= (1<<0) ;       /* enable AHB for port A */
    * ( ( volatile unsigned long * ) ( 0x400FE000 + 0x06C ) ) |= (1<<5) ;       /* enable AHB for port F */


    Nvic_Init() ;
    Port_Init() ;
    ExtInt_Init() ;
    S2I_Init() ;


    /* write transmit buffer */
    S2I_Buffer(S2I_MODULE_0) = (1) ;
    S2I_Buffer(S2I_MODULE_0) = (2) ;
    S2I_Buffer(S2I_MODULE_0) = (3) ;
    S2I_Buffer(S2I_MODULE_0) = (4) ;
    S2I_Buffer(S2I_MODULE_0) = (5) ;
    S2I_Buffer(S2I_MODULE_0) = (6) ;
    S2I_Buffer(S2I_MODULE_0) = (7) ;
    S2I_Buffer(S2I_MODULE_0) = (8) ;


    S2I_TransferStart(S2I_MODULE_0) ;
    while(S2I_ModuleBusy(S2I_MODULE_0)) ;      /* wait for Idle SSI0 */
    S2I_TransferStop (S2I_MODULE_0) ;

    /* read SSI receive buffer*/
    for( counter = 0 ; counter < 8 ; counter ++)
    {
        SSI_Prtr[counter] =  S2I_Buffer(S2I_MODULE_0) ;
    }


    S2I_Buffer(S2I_MODULE_0) = (9) ;
    S2I_Buffer(S2I_MODULE_0) = (10) ;
    S2I_Buffer(S2I_MODULE_0) = (11) ;
    S2I_Buffer(S2I_MODULE_0) = (12) ;
    S2I_Buffer(S2I_MODULE_0) = (13) ;
    S2I_Buffer(S2I_MODULE_0) = (14) ;
    S2I_Buffer(S2I_MODULE_0) = (15) ;
    S2I_Buffer(S2I_MODULE_0) = (16) ;

    S2I_TransferStart(S2I_MODULE_0) ;
    while(S2I_ModuleBusy(S2I_MODULE_0)) ;      /* wait for Idle SSI0 */
    S2I_TransferStop(S2I_MODULE_0) ;

    /* read SSI receive buffer*/
    for( counter = 0 ; counter < 8 ; counter ++)
    {
        SSI_Prtr[counter] =  S2I_Buffer(S2I_MODULE_0) ;
    }


    /*
    Dio_WritePin(DIO_PIN39, DIO_HIGH) ;
    Dio_WritePin(DIO_PIN40, DIO_HIGH) ;
    Dio_WritePin(DIO_PIN41, DIO_HIGH) ;

    */

    /*********************************************************************************/

    /*
    SysTick_EnableInterrupt () ;
    SysTick_SelectClock ( FALSE ) ;
    SysTick_ClearTimer () ;
    SysTick_PeriodicNotification ( 3999999, 0, SysTick_IsrTest ) ;
    SysTick_StartTimer () ;
    */

    /*********************************************************************************/

    /*
    CS_ON

    Nvic_Init() ;
    Nvic_SetPriority (NVIC_TEST_INTERRUPT_ID, 7) ;
    Nvic_EnableInterrupt (NVIC_TEST_INTERRUPT_ID) ;
    Nvic_DisableInterrupt (NVIC_TEST_INTERRUPT_ID) ;
    Nvic_SetPendingFlag (NVIC_TEST_INTERRUPT_ID) ;
    Nvic_ClearPendingFlag (NVIC_TEST_INTERRUPT_ID) ;
    Nvic_Test_1 = Nvic_GetEnable (NVIC_TEST_INTERRUPT_ID) ;
    Nvic_Test_1 = Nvic_GetPendingFlag (NVIC_TEST_INTERRUPT_ID) ;
    Nvic_Test_1 = Nvic_GetPendingFlag (NVIC_TEST_INTERRUPT_ID) ;
    */


    Dio_FlipPin(DIO_PIN39) ;

    while (1) ;

}



void SysTick_IsrTest (void)
{

    Dio_FlipPin(DIO_PIN39) ;

    /*
    if ( SysTick_TestFlag )
    {
        SysTick_TestFlag = FALSE ;
        SysTick_PeriodicNotification ( 3999999, 0, SysTick_IsrTest ) ;

    }
    */
    return ;
}







