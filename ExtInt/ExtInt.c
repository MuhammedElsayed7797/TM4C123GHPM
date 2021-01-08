/************************************************/
/*  ExtInt.c                                    */
/*  Created on: Sep 15, 2020                    */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/


#include "ExtInt.h"
#include "ExtInt_Private.h"

/* this is internally used variables */

extern const uint8 Port_RegisterBusOffset [] ;
extern uint8 Mcu_GpioBusAperture [] ;
void (* ExtInt_IsrPtr_Arr [EXTINT_ISR_NUMBER] ) (void) = {NULL_PTR} ;

/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will initialize All pins' interrupt modes & masks
 * initialization will be according to setting in ExtInt_Cfg.h file .
 * follow rules demonstrated in ExtInt_Cfg.h file to make proper initialization .
 * Mask will determine ports to be initiated according whether port bit in Mask is set or not
 * there're 6 ports A~F, LSB is assigned to A and 6th bit assigned to F
 * don't initiate a port with disabled clock or fault exception will be generated
 */

void ExtInt_Init (uint8 Mask )
{

    ExtInt_RegisterMap_Struct * RegisterBase = NULL_PTR ;

    /*********************************************************************************/

    if ( (Mask>>EXTINT_PORT_A_NUMBER) & TRUE )
    {
        RegisterBase =  EXTINT_BASE_REG_EQU(EXTINT_PORT_A) ;

        RegisterBase->ExtInt_GPIOIS = EXTINT_MODE_LOW_0_7 | EXTINT_MODE_HIGH_0_7 & ~EXTINT_MODE_FALLING_0_7 & ~EXTINT_MODE_RISING_0_7 & ~EXTINT_MODE_BOTH_0_7 ;
        RegisterBase->ExtInt_GPIOIBE = EXTINT_MODE_BOTH_0_7 & ~EXTINT_MODE_FALLING_0_7 & ~EXTINT_MODE_RISING_0_7 ;
        RegisterBase->ExtInt_GPIOIEV = EXTINT_MODE_RISING_0_7 | EXTINT_MODE_HIGH_0_7 & ~EXTINT_MODE_FALLING_0_7 & ~EXTINT_MODE_LOW_0_7 ;
        RegisterBase->ExtInt_GPIOIM = EXTINT_ENABLE_0_7 ;
    }
    else
    {
    }

    /*********************************************************************************/

    if ( (Mask>>EXTINT_PORT_B_NUMBER) & TRUE )
    {
        RegisterBase =  EXTINT_BASE_REG_EQU(EXTINT_PORT_B) ;

        RegisterBase->ExtInt_GPIOIS = EXTINT_MODE_LOW_8_15 | EXTINT_MODE_HIGH_8_15 & ~EXTINT_MODE_FALLING_8_15 & ~EXTINT_MODE_RISING_8_15 & ~EXTINT_MODE_BOTH_8_15 ;
        RegisterBase->ExtInt_GPIOIBE = EXTINT_MODE_BOTH_8_15 & ~EXTINT_MODE_FALLING_8_15 & ~EXTINT_MODE_RISING_8_15 ;
        RegisterBase->ExtInt_GPIOIEV = EXTINT_MODE_RISING_8_15 | EXTINT_MODE_HIGH_8_15 & ~EXTINT_MODE_FALLING_8_15 & ~EXTINT_MODE_LOW_8_15 ;
        RegisterBase->ExtInt_GPIOIM = EXTINT_ENABLE_8_15 ;
    }
    else
    {
    }

    /*********************************************************************************/

    if ( (Mask>>EXTINT_PORT_C_NUMBER) & TRUE )
    {
        RegisterBase =  EXTINT_BASE_REG_EQU(EXTINT_PORT_C) ;

        RegisterBase->ExtInt_GPIOIS = EXTINT_MODE_LOW_16_23 | EXTINT_MODE_HIGH_16_23 & ~EXTINT_MODE_FALLING_16_23 & ~EXTINT_MODE_RISING_16_23 & ~EXTINT_MODE_BOTH_16_23 ;
        RegisterBase->ExtInt_GPIOIBE = EXTINT_MODE_BOTH_16_23 & ~EXTINT_MODE_FALLING_16_23 & ~EXTINT_MODE_RISING_16_23 ;
        RegisterBase->ExtInt_GPIOIEV = EXTINT_MODE_RISING_16_23 | EXTINT_MODE_HIGH_16_23 & ~EXTINT_MODE_FALLING_16_23 & ~EXTINT_MODE_LOW_16_23 ;
        RegisterBase->ExtInt_GPIOIM = EXTINT_ENABLE_16_23 ;
    }
    else
    {
    }

    /*********************************************************************************/

    if ( (Mask>>EXTINT_PORT_D_NUMBER) & TRUE )
    {
        RegisterBase =  EXTINT_BASE_REG_EQU(EXTINT_PORT_D) ;

        RegisterBase->ExtInt_GPIOIS = EXTINT_MODE_LOW_24_31 | EXTINT_MODE_HIGH_24_31 & ~EXTINT_MODE_FALLING_24_31 & ~EXTINT_MODE_RISING_24_31 & ~EXTINT_MODE_BOTH_24_31 ;
        RegisterBase->ExtInt_GPIOIBE = EXTINT_MODE_BOTH_24_31 & ~EXTINT_MODE_FALLING_24_31 & ~EXTINT_MODE_RISING_24_31 ;
        RegisterBase->ExtInt_GPIOIEV = EXTINT_MODE_RISING_24_31 | EXTINT_MODE_HIGH_24_31 & ~EXTINT_MODE_FALLING_24_31 & ~EXTINT_MODE_LOW_24_31 ;
        RegisterBase->ExtInt_GPIOIM = EXTINT_ENABLE_24_31 ;
    }
    else
    {
    }

    /*********************************************************************************/

    if ( (Mask>>EXTINT_PORT_E_NUMBER) & TRUE )
    {
        RegisterBase =  EXTINT_BASE_REG_EQU(EXTINT_PORT_E) ;

        RegisterBase->ExtInt_GPIOIS = EXTINT_MODE_LOW_32_37 | EXTINT_MODE_HIGH_32_37 & ~EXTINT_MODE_FALLING_32_37 & ~EXTINT_MODE_RISING_32_37 & ~EXTINT_MODE_BOTH_32_37 ;
        RegisterBase->ExtInt_GPIOIBE = EXTINT_MODE_BOTH_32_37 & ~EXTINT_MODE_FALLING_32_37 & ~EXTINT_MODE_RISING_32_37 ;
        RegisterBase->ExtInt_GPIOIEV = EXTINT_MODE_RISING_32_37 | EXTINT_MODE_HIGH_32_37 & ~EXTINT_MODE_FALLING_32_37 & ~EXTINT_MODE_LOW_32_37 ;
        RegisterBase->ExtInt_GPIOIM = EXTINT_ENABLE_32_37 ;
    }
    else
    {
    }

    /*********************************************************************************/

    if ( (Mask>>EXTINT_PORT_F_NUMBER) & TRUE )
    {
        RegisterBase =  EXTINT_BASE_REG_EQU(EXTINT_PORT_F) ;

        RegisterBase->ExtInt_GPIOIS = EXTINT_MODE_LOW_38_42 | EXTINT_MODE_HIGH_38_42 & ~EXTINT_MODE_FALLING_38_42 & ~EXTINT_MODE_RISING_38_42 & ~EXTINT_MODE_BOTH_38_42 ;
        RegisterBase->ExtInt_GPIOIBE = EXTINT_MODE_BOTH_38_42 & ~EXTINT_MODE_FALLING_38_42 & ~EXTINT_MODE_RISING_38_42 ;
        RegisterBase->ExtInt_GPIOIEV = EXTINT_MODE_RISING_38_42 | EXTINT_MODE_HIGH_38_42 & ~EXTINT_MODE_FALLING_38_42 & ~EXTINT_MODE_LOW_38_42 ;
        RegisterBase->ExtInt_GPIOIM = EXTINT_ENABLE_38_42 ;
    }
    else
    {
    }

    /*********************************************************************************/

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will change interrupt mode of interrupt pin defined by (PinId) to mode defined by (Mode) .
 * see note on interrupt modes in ExtIng.h file at ExtInt_ModeType type definition .
 */

void ExtInt_InterruptMode ( ExtInt_PinType PinId, ExtInt_ModeType Mode )
{

    boolean InterruptState = FALSE ;
    uint8 PinNumber = PinId&EXTINT_PIN_NUMBER_MASK, PortNumber = (PinId&EXTINT_PORT_NUMBER_MASK) >> EXTINT_PORT_NUMBER_OFFSET ;
    ExtInt_RegisterMap_Struct * RegisterBase = EXTINT_BASE_REG_EQU(PortNumber) ;

    InterruptState = GET_BIT( RegisterBase->ExtInt_GPIOIM, PinNumber ) ;
    CLR_BIT( RegisterBase->ExtInt_GPIOIM, PinNumber ) ;
    switch ( Mode )
    {

        case EXTINT_FALLING_EDGE :
        {
            CLR_BIT( RegisterBase->ExtInt_GPIOIS, PinNumber ) ;
            CLR_BIT( RegisterBase->ExtInt_GPIOIBE, PinNumber ) ;
            CLR_BIT( RegisterBase->ExtInt_GPIOIEV, PinNumber ) ;

            break ;
        }
        case EXTINT_RISING_EDGE :
        {
            CLR_BIT( RegisterBase->ExtInt_GPIOIS, PinNumber ) ;
            CLR_BIT( RegisterBase->ExtInt_GPIOIBE, PinNumber ) ;
            SET_BIT( RegisterBase->ExtInt_GPIOIEV, PinNumber ) ;

            break ;
        }
        case EXTINT_BOTH_EDGE :
        {

            CLR_BIT( RegisterBase->ExtInt_GPIOIS, PinNumber ) ;
            SET_BIT( RegisterBase->ExtInt_GPIOIBE, PinNumber ) ;
            break ;
        }
        case EXTINT_LOW_LEVEL :
        {
            SET_BIT( RegisterBase->ExtInt_GPIOIS, PinNumber ) ;
            CLR_BIT( RegisterBase->ExtInt_GPIOIEV, PinNumber ) ;

            break ;
        }
        case EXTINT_HIGH_LEVEL :
        {
            SET_BIT( RegisterBase->ExtInt_GPIOIS, PinNumber ) ;
            SET_BIT( RegisterBase->ExtInt_GPIOIEV, PinNumber ) ;

            break ;
        }

    }

    RegisterBase->ExtInt_GPIORIS = TRUE << PinNumber ;
    ASSIGN_BIT( RegisterBase->ExtInt_GPIOIM, PinNumber, InterruptState ) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will change interrupt enable state of pin defined by (PinId) .
 * if Enable argument = TRUE then interrupt is unmasked .
 * masking interrupt won't prevent setting of it's flag .
 * if event flag is set and interrupt is unmasked then interrupt signal of port will be set to NVIC if it was cleared .
 * operations on port interrupt like pending & enable is done by NVIC driver .
 */

void ExtInt_EnableInterrupt ( ExtInt_PinType PinId, boolean Enable )
{

    uint8 PinNumber = PinId&EXTINT_PIN_NUMBER_MASK, PortNumber = (PinId&EXTINT_PORT_NUMBER_MASK) >> EXTINT_PORT_NUMBER_OFFSET ;
    ExtInt_RegisterMap_Struct * RegisterBase = EXTINT_BASE_REG_EQU(PortNumber) ;

    ASSIGN_BIT( RegisterBase->ExtInt_GPIOIM, PinNumber, Enable ) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will get state of event flag of unmasked  interrupt pin defined by (PinId) .
 * if  interrupt pin is masked the this function will return FALSE in all cases
 */

boolean ExtInt_GetInterruptState ( ExtInt_PinType PinId )
{

    uint8 PinNumber = PinId&EXTINT_PIN_NUMBER_MASK, PortNumber = (PinId&EXTINT_PORT_NUMBER_MASK) >> EXTINT_PORT_NUMBER_OFFSET ;
    ExtInt_RegisterMap_Struct * RegisterBase = EXTINT_BASE_REG_EQU(PortNumber) ;
    boolean ReturnResult = GET_BIT( RegisterBase->ExtInt_GPIOMIS, PinNumber ) ;

    return ReturnResult;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will get state of event flag of unmasked and masked interrupt pin defined by (PinId) .
 */

boolean ExtInt_GetEventState ( ExtInt_PinType PinId )
{
    uint8 PinNumber = PinId&EXTINT_PIN_NUMBER_MASK, PortNumber = (PinId&EXTINT_PORT_NUMBER_MASK) >> EXTINT_PORT_NUMBER_OFFSET ;
    ExtInt_RegisterMap_Struct * RegisterBase = EXTINT_BASE_REG_EQU(PortNumber) ;
    boolean ReturnResult = GET_BIT( RegisterBase->ExtInt_GPIORIS, PinNumber ) ;

    return ReturnResult;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will clear event flag interrupt pin defined by (PinId) .
 * this is function for interrupt pin that work in edges interrupt modes .
 * event flag of level interrupt modes is cleared automatically and can't done by software .
 * use this function inside ISR of interrupt pin to allow event flag to be set again and generate new interrupt .
 * and to prevent execution of interrupt pin ISR, when the interrupt port ISR is fired due to other interrupt pin
 */

void ExtInt_ClearEvent ( ExtInt_PinType PinId )
{

    uint8 PinNumber = PinId&EXTINT_PIN_NUMBER_MASK, PortNumber = (PinId&EXTINT_PORT_NUMBER_MASK) >> EXTINT_PORT_NUMBER_OFFSET ;
    ExtInt_RegisterMap_Struct * RegisterBase = EXTINT_BASE_REG_EQU(PortNumber) ;
    RegisterBase->ExtInt_GPIORIS = TRUE << PinNumber ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this will assign call back function to be called inside port ISR .
 * the port ISR should handle all port's pin ISRs that configured to generate interrupts .
 * all unmasked interrupt pins' event flags is or and result is the port interrupt signal,
 * so if all unmasked events is cleared and on of them get set the port interrupt ISR will be executed if enable in NVIC .
 */

void ExtInt_AssignISR ( ExtInt_PortType PortNumber ,void (*FuncPtr) (void) )
{
    ExtInt_IsrPtr_Arr[PortNumber] = FuncPtr ;
    return ;
}

/*********************************************************************************/

/* this is ISR called when port A interrupt is triggered */

void ExtInt_PortA_ISR (void)
{
    (ExtInt_IsrPtr_Arr[EXTINT_PORT_A]) () ;
    return ;
}


/*********************************************************************************/

/* this is ISR called when port B interrupt is triggered */

void ExtInt_PortB_ISR (void)
{
    (ExtInt_IsrPtr_Arr[EXTINT_PORT_B]) () ;
    return ;
}


/*********************************************************************************/

/* this is ISR called when port C interrupt is triggered */

void ExtInt_PortC_ISR (void)
{
    (ExtInt_IsrPtr_Arr[EXTINT_PORT_C]) () ;
    return ;
}

/*********************************************************************************/

/* this is ISR called when port D interrupt is triggered */

void ExtInt_PortD_ISR (void)
{
    (ExtInt_IsrPtr_Arr[EXTINT_PORT_D]) () ;
    return ;
}

/*********************************************************************************/

/* this is ISR called when port E interrupt is triggered */

void ExtInt_PortE_ISR (void)
{
    (ExtInt_IsrPtr_Arr[EXTINT_PORT_E]) () ;
    return ;
}

/*********************************************************************************/

/* this is ISR called when port F interrupt is triggered */

void ExtInt_PortF_ISR (void)
{
    (ExtInt_IsrPtr_Arr[EXTINT_PORT_F]) () ;
    return ;
}


/*********************************************************************************/



