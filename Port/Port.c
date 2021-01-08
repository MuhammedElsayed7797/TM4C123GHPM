/************************************************/
/*  Port.c                                      */
/*  Created on: Sep 13, 2020                    */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/

#include "Port.h"
#include "Port_Private.h"

/*********************************************************************************/

/* this is internally used variables */

static boolean Port_LockFlag = FALSE ;
const uint8 Port_RegisterBusOffset [] = {0xA8, 0xA8, 0xA8, 0xA8, 0x70, 0x70} ;
extern uint8 Mcu_GpioBusAperture [] ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will initialize All pins'
 * mode, peripheral signal, internal resistor, drive strength,
 * slew rate, protection lock , ADC & DMA trigger feature .
 * initialization will be according to setting in Port_Cfg.h file .
 * follow rules demonstrated in this Port_Cfg.h file to make proper initialization .
 * Mask will determine ports to be initiated according whether port bit in Mask is set or not
 * there're 6 ports A~F, LSB is assigned to A and 6th bit assigned to F
 * don't initiate a port with disabled clock or fault exception will be generated
 */

void Port_Init ( uint8 Mask )
{

    Port_RegisterMap_Struct * RegisterBase = NULL_PTR ;

    /*********************************************************************************/

    if ( (Mask>>PORT_A_NUMBER) & TRUE )
    {
        RegisterBase =  PORT_BASE_REG_EQU(PORT_A_NUMBER) ;

        RegisterBase->Port_GPIODIR = PORT_MODE_PUSH_OUT_0_7 | PORT_MODE_DRAIN_OUT_0_7 & ~PORT_MODE_DIGITAL_IN_0_7 & ~PORT_MODE_ANALOG_IN_0_7 ;
        RegisterBase->Port_GPIOAFSEL = PORT_MODE_PUSH_ALT_0_7 | PORT_MODE_DRAIN_ALT_0_7 & ~PORT_MODE_DIGITAL_IN_0_7 & ~PORT_MODE_ANALOG_IN_0_7 & ~PORT_MODE_PUSH_OUT_0_7 & ~PORT_MODE_DRAIN_OUT_0_7 ;
        RegisterBase->Port_GPIOODR = PORT_MODE_DRAIN_OUT_0_7 | PORT_MODE_DRAIN_ALT_0_7  & ~PORT_MODE_PUSH_OUT_0_7 & ~PORT_MODE_PUSH_ALT_0_7 ;
        RegisterBase->Port_GPIODEN = ~PORT_MODE_TRI_STATE_0_7 & ~PORT_MODE_ANALOG_IN_0_7 ;
        RegisterBase->Port_GPIOAMSEL = PORT_MODE_ANALOG_IN_0_7 & ~PORT_MODE_DIGITAL_IN_0_7 & ~PORT_MODE_PUSH_OUT_0_7 & ~PORT_MODE_DRAIN_OUT_0_7 & ~PORT_MODE_PUSH_ALT_0_7 & ~PORT_MODE_DRAIN_ALT_0_7 & ~PORT_MODE_TRI_STATE_0_7 ;

        RegisterBase->Port_GPIOPCTL = PORT_PERIPHERAL_0_7 ;

        RegisterBase->Port_GPIOPUR = PORT_INTERNAL_RES_TYPE_0_7 & PORT_INTERNAL_RES_EN_0_7 ;
        RegisterBase->Port_GPIOPDR = ~PORT_INTERNAL_RES_TYPE_0_7 & PORT_INTERNAL_RES_EN_0_7 ;

        RegisterBase->Port_GPIODR2R = PORT_2MA_DRIVE_EN_0_7 ;
        RegisterBase->Port_GPIODR4R = PORT_4MA_DRIVE_EN_0_7 ;
        RegisterBase->Port_GPIODR8R = PORT_8MA_DRIVE_EN_0_7 ;

        RegisterBase->Port_GPIOSLR = PORT_SLEW_RATE_CTL_EN_0_7 ;

        RegisterBase->Port_GPIOADCCTL = PORT_ADC_TRIGGER_EN_0_7 ;
        RegisterBase->Port_GPIODMACTL = PORT_DMA_TRIGGER_EN_0_7 ;
    }
    else
    {
    }

    /*********************************************************************************/

    if ( (Mask>>PORT_B_NUMBER) & TRUE )
    {
        RegisterBase =  PORT_BASE_REG_EQU(PORT_B_NUMBER) ;

        RegisterBase->Port_GPIODIR = PORT_MODE_PUSH_OUT_0_7 | PORT_MODE_DRAIN_OUT_8_15 & ~PORT_MODE_DIGITAL_IN_8_15 & ~PORT_MODE_ANALOG_IN_8_15 ;
        RegisterBase->Port_GPIOAFSEL = PORT_MODE_PUSH_ALT_8_15 | PORT_MODE_DRAIN_ALT_8_15 & ~PORT_MODE_DIGITAL_IN_8_15 & ~PORT_MODE_ANALOG_IN_8_15 & ~PORT_MODE_PUSH_OUT_8_15 & ~PORT_MODE_DRAIN_OUT_8_15 ;
        RegisterBase->Port_GPIOODR = PORT_MODE_DRAIN_OUT_8_15 | PORT_MODE_DRAIN_ALT_8_15  & ~PORT_MODE_PUSH_OUT_8_15 & ~PORT_MODE_PUSH_ALT_8_15 ;
        RegisterBase->Port_GPIODEN = ~PORT_MODE_TRI_STATE_8_15 & ~PORT_MODE_ANALOG_IN_8_15 ;
        RegisterBase->Port_GPIOAMSEL = PORT_MODE_ANALOG_IN_8_15 & ~PORT_MODE_DIGITAL_IN_8_15 & ~PORT_MODE_PUSH_OUT_8_15 & ~PORT_MODE_DRAIN_OUT_8_15 & ~PORT_MODE_PUSH_ALT_8_15 & ~PORT_MODE_DRAIN_ALT_8_15 & ~PORT_MODE_TRI_STATE_8_15 ;

        RegisterBase->Port_GPIOPCTL = PORT_PERIPHERAL_8_15 ;

        RegisterBase->Port_GPIOPUR = PORT_INTERNAL_RES_TYPE_8_15 & PORT_INTERNAL_RES_EN_8_15 ;
        RegisterBase->Port_GPIOPDR = ~PORT_INTERNAL_RES_TYPE_8_15 & PORT_INTERNAL_RES_EN_8_15 ;

        RegisterBase->Port_GPIODR2R = PORT_2MA_DRIVE_EN_8_15 ;
        RegisterBase->Port_GPIODR4R = PORT_4MA_DRIVE_EN_8_15 ;
        RegisterBase->Port_GPIODR8R = PORT_8MA_DRIVE_EN_8_15 ;

        RegisterBase->Port_GPIOSLR = PORT_SLEW_RATE_CTL_EN_8_15 ;

        RegisterBase->Port_GPIOADCCTL = PORT_ADC_TRIGGER_EN_8_15 ;
        RegisterBase->Port_GPIODMACTL = PORT_DMA_TRIGGER_EN_8_15 ;
    }
    else
    {
    }

    /*********************************************************************************/

    if ( (Mask>>PORT_C_NUMBER) & TRUE )
    {
        RegisterBase =  PORT_BASE_REG_EQU(PORT_C_NUMBER) ;

#if PORT_PIN_UNLOCK_16_19 > 0

        RegisterBase->Port_GPIOLOCK = 0x4C4F434B ;
        RegisterBase->Port_GPIOCR = PORT_PIN_UNLOCK_16_19 ;

#endif

        RegisterBase->Port_GPIODIR = PORT_MODE_PUSH_OUT_16_23 | PORT_MODE_DRAIN_OUT_16_23 & ~PORT_MODE_DIGITAL_IN_16_23 & ~PORT_MODE_ANALOG_IN_16_23 ;
        RegisterBase->Port_GPIOAFSEL = PORT_MODE_PUSH_ALT_16_23 | PORT_MODE_DRAIN_ALT_16_23 & ~PORT_MODE_DIGITAL_IN_16_23 & ~PORT_MODE_ANALOG_IN_16_23 & ~PORT_MODE_PUSH_OUT_16_23 & ~PORT_MODE_DRAIN_OUT_16_23 ;
        RegisterBase->Port_GPIOODR = PORT_MODE_DRAIN_OUT_16_23 | PORT_MODE_DRAIN_ALT_16_23  & ~PORT_MODE_PUSH_OUT_16_23 & ~PORT_MODE_PUSH_ALT_16_23 ;
        RegisterBase->Port_GPIODEN = ~PORT_MODE_TRI_STATE_16_23 & ~PORT_MODE_ANALOG_IN_16_23 ;
        RegisterBase->Port_GPIOAMSEL = PORT_MODE_ANALOG_IN_16_23 & ~PORT_MODE_DIGITAL_IN_16_23 & ~PORT_MODE_PUSH_OUT_16_23 & ~PORT_MODE_DRAIN_OUT_16_23 & ~PORT_MODE_PUSH_ALT_16_23 & ~PORT_MODE_DRAIN_ALT_16_23 & ~PORT_MODE_TRI_STATE_16_23 ;

        RegisterBase->Port_GPIOPCTL = PORT_PERIPHERAL_16_23 ;

        RegisterBase->Port_GPIOPUR = PORT_INTERNAL_RES_TYPE_16_23 & PORT_INTERNAL_RES_EN_16_23 ;
        RegisterBase->Port_GPIOPDR = ~PORT_INTERNAL_RES_TYPE_16_23 & PORT_INTERNAL_RES_EN_16_23 ;

        RegisterBase->Port_GPIODR2R = PORT_2MA_DRIVE_EN_16_23 ;
        RegisterBase->Port_GPIODR4R = PORT_4MA_DRIVE_EN_16_23 ;
        RegisterBase->Port_GPIODR8R = PORT_8MA_DRIVE_EN_16_23 ;

        RegisterBase->Port_GPIOSLR = PORT_SLEW_RATE_CTL_EN_16_23 ;

        RegisterBase->Port_GPIOADCCTL = PORT_ADC_TRIGGER_EN_16_23 ;
        RegisterBase->Port_GPIODMACTL = PORT_DMA_TRIGGER_EN_16_23 ;
    }
    else
    {
    }

    /*********************************************************************************/

    if ( (Mask>>PORT_D_NUMBER) & TRUE )
    {
        RegisterBase =  PORT_BASE_REG_EQU(PORT_D_NUMBER) ;

#if TRUE == PORT_PIN_UNLOCK_31

        RegisterBase->Port_GPIOLOCK = 0x4C4F434B ;
        ASSIGN_BIT ( RegisterBase->Port_GPIOCR, PORT_PIN31_REG_OFFSET, PORT_PIN_UNLOCK_31 ) ;

#endif

        RegisterBase->Port_GPIODIR = PORT_MODE_PUSH_OUT_24_31 | PORT_MODE_DRAIN_OUT_24_31 & ~PORT_MODE_DIGITAL_IN_24_31 & ~PORT_MODE_ANALOG_IN_24_31 ;
        RegisterBase->Port_GPIOAFSEL = PORT_MODE_PUSH_ALT_24_31 | PORT_MODE_DRAIN_ALT_24_31 & ~PORT_MODE_DIGITAL_IN_24_31 & ~PORT_MODE_ANALOG_IN_24_31 & ~PORT_MODE_PUSH_OUT_24_31 & ~PORT_MODE_DRAIN_OUT_24_31 ;
        RegisterBase->Port_GPIOODR = PORT_MODE_DRAIN_OUT_24_31 | PORT_MODE_DRAIN_ALT_24_31  & ~PORT_MODE_PUSH_OUT_24_31 & ~PORT_MODE_PUSH_ALT_24_31 ;
        RegisterBase->Port_GPIODEN = ~PORT_MODE_TRI_STATE_24_31 & ~PORT_MODE_ANALOG_IN_24_31 ;
        RegisterBase->Port_GPIOAMSEL = PORT_MODE_ANALOG_IN_24_31 & ~PORT_MODE_DIGITAL_IN_24_31 & ~PORT_MODE_PUSH_OUT_24_31 & ~PORT_MODE_DRAIN_OUT_24_31 & ~PORT_MODE_PUSH_ALT_24_31 & ~PORT_MODE_DRAIN_ALT_24_31 & ~PORT_MODE_TRI_STATE_24_31 ;

        RegisterBase->Port_GPIOPCTL = PORT_PERIPHERAL_24_31 ;

        RegisterBase->Port_GPIOPUR = PORT_INTERNAL_RES_TYPE_24_31 & PORT_INTERNAL_RES_EN_24_31 ;
        RegisterBase->Port_GPIOPDR = ~PORT_INTERNAL_RES_TYPE_24_31 & PORT_INTERNAL_RES_EN_24_31 ;

        RegisterBase->Port_GPIODR2R = PORT_2MA_DRIVE_EN_24_31 ;
        RegisterBase->Port_GPIODR4R = PORT_4MA_DRIVE_EN_24_31 ;
        RegisterBase->Port_GPIODR8R = PORT_8MA_DRIVE_EN_24_31 ;

        RegisterBase->Port_GPIOSLR = PORT_SLEW_RATE_CTL_EN_24_31 ;

        RegisterBase->Port_GPIOADCCTL = PORT_ADC_TRIGGER_EN_24_31 ;
        RegisterBase->Port_GPIODMACTL = PORT_DMA_TRIGGER_EN_24_31 ;
    }
    else
    {
    }

    /*********************************************************************************/

    if ( (Mask>>PORT_E_NUMBER) & TRUE )
    {
        RegisterBase =  PORT_BASE_REG_EQU(PORT_E_NUMBER) ;

        RegisterBase->Port_GPIODIR = PORT_MODE_PUSH_OUT_32_37 | PORT_MODE_DRAIN_OUT_32_37 & ~PORT_MODE_DIGITAL_IN_32_37 & ~PORT_MODE_ANALOG_IN_32_37 ;
        RegisterBase->Port_GPIOAFSEL = PORT_MODE_PUSH_ALT_32_37 | PORT_MODE_DRAIN_ALT_32_37 & ~PORT_MODE_DIGITAL_IN_32_37 & ~PORT_MODE_ANALOG_IN_32_37 & ~PORT_MODE_PUSH_OUT_32_37 & ~PORT_MODE_DRAIN_OUT_32_37 ;
        RegisterBase->Port_GPIOODR = PORT_MODE_DRAIN_OUT_32_37 | PORT_MODE_DRAIN_ALT_32_37  & ~PORT_MODE_PUSH_OUT_32_37 & ~PORT_MODE_PUSH_ALT_32_37 ;
        RegisterBase->Port_GPIODEN = ~PORT_MODE_TRI_STATE_32_37 & ~PORT_MODE_ANALOG_IN_32_37 ;
        RegisterBase->Port_GPIOAMSEL = PORT_MODE_ANALOG_IN_32_37 & ~PORT_MODE_DIGITAL_IN_32_37 & ~PORT_MODE_PUSH_OUT_32_37 & ~PORT_MODE_DRAIN_OUT_32_37 & ~PORT_MODE_PUSH_ALT_32_37 & ~PORT_MODE_DRAIN_ALT_32_37 & ~PORT_MODE_TRI_STATE_32_37 ;

        RegisterBase->Port_GPIOPCTL = PORT_PERIPHERAL_32_37 ;

        RegisterBase->Port_GPIOPUR = PORT_INTERNAL_RES_TYPE_32_37 & PORT_INTERNAL_RES_EN_32_37 ;
        RegisterBase->Port_GPIOPDR = ~PORT_INTERNAL_RES_TYPE_32_37 & PORT_INTERNAL_RES_EN_32_37 ;

        RegisterBase->Port_GPIODR2R = PORT_2MA_DRIVE_EN_32_37 ;
        RegisterBase->Port_GPIODR4R = PORT_4MA_DRIVE_EN_32_37 ;
        RegisterBase->Port_GPIODR8R = PORT_8MA_DRIVE_EN_32_37 ;

        RegisterBase->Port_GPIOSLR = PORT_SLEW_RATE_CTL_EN_32_37 ;

        RegisterBase->Port_GPIOADCCTL = PORT_ADC_TRIGGER_EN_32_37 ;
        RegisterBase->Port_GPIODMACTL = PORT_DMA_TRIGGER_EN_32_37 ;
    }
    else
    {
    }

    /*********************************************************************************/

    if ( (Mask>>PORT_F_NUMBER) & TRUE )
    {
        RegisterBase =  PORT_BASE_REG_EQU(PORT_F_NUMBER) ;

#if TRUE == PORT_PIN_UNLOCK_38

        RegisterBase->Port_GPIOLOCK = PORT_GPIOLOCK_PASSWORD ;
        ASSIGN_BIT ( RegisterBase->Port_GPIOCR, PORT_PIN38_REG_OFFSET, PORT_PIN_UNLOCK_38 ) ;

#endif
        RegisterBase->Port_GPIODIR = PORT_MODE_PUSH_OUT_38_42 | PORT_MODE_DRAIN_OUT_38_42 & ~PORT_MODE_DIGITAL_IN_38_42 & ~PORT_MODE_ANALOG_IN_38_42 ;
        RegisterBase->Port_GPIOAFSEL = PORT_MODE_PUSH_ALT_38_42 | PORT_MODE_DRAIN_ALT_38_42 & ~PORT_MODE_DIGITAL_IN_38_42 & ~PORT_MODE_ANALOG_IN_38_42 & ~PORT_MODE_PUSH_OUT_38_42 & ~PORT_MODE_DRAIN_OUT_38_42 ;
        RegisterBase->Port_GPIOODR = PORT_MODE_DRAIN_OUT_38_42 | PORT_MODE_DRAIN_ALT_38_42  & ~PORT_MODE_PUSH_OUT_38_42 & ~PORT_MODE_PUSH_ALT_38_42 ;
        RegisterBase->Port_GPIODEN = ~PORT_MODE_TRI_STATE_38_42 & ~PORT_MODE_ANALOG_IN_38_42 ;
        RegisterBase->Port_GPIOAMSEL = PORT_MODE_ANALOG_IN_38_42 & ~PORT_MODE_DIGITAL_IN_38_42 & ~PORT_MODE_PUSH_OUT_38_42 & ~PORT_MODE_DRAIN_OUT_38_42 & ~PORT_MODE_PUSH_ALT_38_42 & ~PORT_MODE_DRAIN_ALT_38_42 & ~PORT_MODE_TRI_STATE_38_42 ;

        RegisterBase->Port_GPIOPCTL = PORT_PERIPHERAL_38_42 ;

        RegisterBase->Port_GPIOPUR = PORT_INTERNAL_RES_TYPE_38_42 & PORT_INTERNAL_RES_EN_38_42 ;
        RegisterBase->Port_GPIOPDR = ~PORT_INTERNAL_RES_TYPE_38_42 & PORT_INTERNAL_RES_EN_38_42 ;

        RegisterBase->Port_GPIODR2R = PORT_2MA_DRIVE_EN_38_42 ;
        RegisterBase->Port_GPIODR4R = PORT_4MA_DRIVE_EN_38_42 ;
        RegisterBase->Port_GPIODR8R = PORT_8MA_DRIVE_EN_38_42 ;

        RegisterBase->Port_GPIOSLR = PORT_SLEW_RATE_CTL_EN_38_42 ;

        RegisterBase->Port_GPIOADCCTL = PORT_ADC_TRIGGER_EN_38_42 ;
        RegisterBase->Port_GPIODMACTL = PORT_DMA_TRIGGER_EN_38_42 ;
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
 * use this function to set mode specified by PinMode to pin specified by PinId .
 * some pins(16~19, 31,38) has protection against change their configurations, to change their mode,
 * first use Port_PinLock function
 */

void Port_PinMode ( Port_PinType PinId, Port_ModeType PinMode )
{
    uint8 PinNumber = PinId&PORT_PIN_NUMBER_MASK, PortNumber = (PinId&PORT_PORT_NUMBER_MASK) >> PORT_PORT_NUMBER_OFFSET ;
    Port_RegisterMap_Struct * RegisterBase =  PORT_BASE_REG_EQU(PortNumber) ;


    switch ( PinMode )
    {
        case PORT_TRI_STATE :
        {

            CLR_BIT (RegisterBase->Port_GPIODEN, PinNumber) ;
            CLR_BIT (RegisterBase->Port_GPIOAMSEL, PinNumber) ;

            break ;
        }
        case PORT_DIGITAL_INPUT :
        {

            CLR_BIT (RegisterBase->Port_GPIODIR, PinNumber) ;
            CLR_BIT (RegisterBase->Port_GPIOAFSEL, PinNumber) ;
            SET_BIT (RegisterBase->Port_GPIODEN, PinNumber) ;
            CLR_BIT (RegisterBase->Port_GPIOAMSEL, PinNumber) ;

            break ;
        }
        case PORT_ANALOG_INPUT :
        {

            CLR_BIT (RegisterBase->Port_GPIODIR, PinNumber) ;
            CLR_BIT (RegisterBase->Port_GPIOAFSEL, PinNumber) ;
            CLR_BIT (RegisterBase->Port_GPIODEN, PinNumber) ;
            SET_BIT (RegisterBase->Port_GPIOAMSEL, PinNumber) ;

            break ;
        }
        case PORT_PUSH_PULL_OUTPUT :
        {

            SET_BIT (RegisterBase->Port_GPIODIR, PinNumber) ;
            CLR_BIT (RegisterBase->Port_GPIOAFSEL, PinNumber) ;
            CLR_BIT (RegisterBase->Port_GPIOODR, PinNumber) ;
            SET_BIT (RegisterBase->Port_GPIODEN, PinNumber) ;
            CLR_BIT (RegisterBase->Port_GPIOAMSEL, PinNumber) ;

            break ;
        }
        case PORT_OPEN_DRAIN_OUTPUT :
        {

            SET_BIT (RegisterBase->Port_GPIODIR, PinNumber) ;
            CLR_BIT (RegisterBase->Port_GPIOAFSEL, PinNumber) ;
            SET_BIT (RegisterBase->Port_GPIOODR, PinNumber) ;
            SET_BIT (RegisterBase->Port_GPIODEN, PinNumber) ;
            CLR_BIT (RegisterBase->Port_GPIOAMSEL, PinNumber) ;

            break ;
        }
        case PORT_PUSH_PULL_ALT_FUNC :
        {

            SET_BIT (RegisterBase->Port_GPIOAFSEL, PinNumber) ;
            CLR_BIT (RegisterBase->Port_GPIOODR, PinNumber) ;
            SET_BIT (RegisterBase->Port_GPIODEN, PinNumber) ;
            CLR_BIT (RegisterBase->Port_GPIOAMSEL, PinNumber) ;

            break ;
        }
        case PORT_OPEN_DRAIN_ALT_FUNC :
        {

            SET_BIT (RegisterBase->Port_GPIOAFSEL, PinNumber) ;
            SET_BIT (RegisterBase->Port_GPIOODR, PinNumber) ;
            SET_BIT (RegisterBase->Port_GPIODEN, PinNumber) ;
            CLR_BIT (RegisterBase->Port_GPIOAMSEL, PinNumber) ;

            break ;
        }
    }
    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function used to select which peripheral will control pin defined by Port_PinType,
 * in Alternate Function Modes .
 * every pin could has up to 16 peripheral function choose one of them using Peripheral argument .
 * Peripheral must be between 0x00~0X0F or it will affect another pins functions .
 * be careful with pins (16~19) because those pins are JTAG/SWD pins so that don't disconnect debugger/flasher .
 * get wanted peripheral number for every pin from Table 23-5 page 1351 in Target DataSheet .
 */

void Port_PinPeripheral ( Port_PinType PinId, uint8 Peripheral )
{
    uint8 PinNumber = (PinId&PORT_PIN_NUMBER_MASK) * PORT_GPIOPCTL_BIT_FIELD_WIDTH , PortNumber = (PinId&PORT_PORT_NUMBER_MASK) >> PORT_PORT_NUMBER_OFFSET;
    uint32 Temp = 0 ;
    Port_RegisterMap_Struct * RegisterBase =  PORT_BASE_REG_EQU(PortNumber) ;

    Temp = RegisterBase->Port_GPIOPCTL & ~(PORT_GPIOPCTL_BIT_FIELD_MASK << PinNumber) ;
    RegisterBase->Port_GPIOPCTL = Temp | ( Peripheral << PinNumber ) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function used to set an internal resistor (ResistorType) to pin defined by PinId .
 * enable one resistor type will disable the others .
 * some pins(16~19, 31,38) has protection against change their configurations,
 * to change their internal resistor first use Port_PinLock function .
 * the internal resistor setting will be ignored for open drain output modes and also for I2C signal pins .
 * internal resistor must be disabled ResistorType = PORT_NO_RESISTOR  when analog input mode is selected
 */

void Port_PinResistor ( Port_PinType PinId, uint8 ResistorType )
{

    uint8 PinNumber = PinId&PORT_PIN_NUMBER_MASK, PortNumber = (PinId&PORT_PORT_NUMBER_MASK) >> PORT_PORT_NUMBER_OFFSET ;
    Port_RegisterMap_Struct * RegisterBase =  PORT_BASE_REG_EQU(PortNumber) ;

    ASSIGN_BIT ( RegisterBase->Port_GPIOPUR, PinNumber, (ResistorType & PORT_PULL_UP_RESISTOR) ) ;
    ASSIGN_BIT ( RegisterBase->Port_GPIOPDR, PinNumber, ((ResistorType & PORT_PULL_DOWN_RESISTOR) >> 1) ) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function used to select the drive current strength for pin defined by PinId .
 * use MACROS specified to PinDriver in Port.h file .
 * this setting only has effect on pin output modes for input modes sink current up to 18mA for all pins .
 * note that don't make all pins has highest current configuration,
 * there's a limit for sum of sink and source current for different group of pins,
 * groups of pins and max sum current listed in page 1360,1361 in DataSheet .
 *
 */

void Port_PinDrivers ( Port_PinType PinId, uint8 PinDriver )
{
    uint8 PinNumber = PinId&PORT_PIN_NUMBER_MASK, PortNumber = (PinId&PORT_PORT_NUMBER_MASK) >> PORT_PORT_NUMBER_OFFSET ;
    Port_RegisterMap_Struct * RegisterBase =  PORT_BASE_REG_EQU(PortNumber) ;

    ASSIGN_BIT ( RegisterBase->Port_GPIODR2R, PinNumber, (PinDriver & PORT_2MA_DRIVER) ) ;
    ASSIGN_BIT ( RegisterBase->Port_GPIODR4R, PinNumber, ((PinDriver & PORT_4MA_DRIVER) >> 1) ) ;
    ASSIGN_BIT ( RegisterBase->Port_GPIODR8R, PinNumber, ((PinDriver & PORT_8MA_DRIVER) >> 2) ) ;


    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function enable/disable the feature of slew rate control for pin defined by PinId.
 * if EnableRateControl = TRUE then feature is enabled .
 * note that this feature is only available for pin driven by 8mA drive,
 * which could be selected for pin using Port_PinDrivers function .
 */

void Port_PinSlewRate ( Port_PinType PinId, boolean EnableRateControl )
{
    uint8 PinNumber = PinId&PORT_PIN_NUMBER_MASK, PortNumber = (PinId&PORT_PORT_NUMBER_MASK) >> PORT_PORT_NUMBER_OFFSET ;
    Port_RegisterMap_Struct * RegisterBase =  PORT_BASE_REG_EQU(PortNumber) ;

    ASSIGN_BIT ( RegisterBase->Port_GPIOSLR, PinNumber, EnableRateControl ) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, non Reentrant function .
 * this function will Lock/unlock the pins which has protection feature .
 * only pins (16~19,31,38) has lock feature JTAG/SWD and NMI pins .
 * if this function used to pin other than mentioned pins it will have no effect
 * lock feature will disable changing mode of pin and internal resistor configurations .
 * if EnableLock = FALSE then pin is locked and changing is protected setting won't take effect .
 * if EnableLock = TRUE the pin is unlocked and could change its protected settings .
 * this function is non Reentrant function so it's protected using internal flag ,
 * check on its return value to see if it was executed properly or not .
 */

StatusType Port_PinLock ( Port_PinType PinId, boolean DisableLock )
{
    StatusType ReturnResult = E_OK ;
    uint8 PinNumber = 0, PortNumber = 0 ;
    Port_RegisterMap_Struct * RegisterBase = NULL_PTR ;

    if ( FALSE == Port_LockFlag )
    {
        Port_LockFlag = TRUE ;

        PinNumber = PinId&PORT_PIN_NUMBER_MASK ;
        PortNumber = (PinId&PORT_PORT_NUMBER_MASK) >> PORT_PORT_NUMBER_OFFSET ;
        RegisterBase =  PORT_BASE_REG_EQU(PortNumber) ;

        RegisterBase->Port_GPIOLOCK = PORT_GPIOLOCK_PASSWORD ;
        ASSIGN_BIT ( RegisterBase->Port_GPIOCR, PinNumber, DisableLock ) ;
    }
    else
    {
        ReturnResult = E_NOT_OK ;
    }


    return ReturnResult ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function enable/disable ADC trigger feature for pin defined by PinId .
 * if EnableTrigger = TRUE then feature is enabled and if = FASLE feature is disabled .
 * trigger to happen pin must be configured as non masked interrupt pin using ExInt driver ,
 * and ADC should enable External trigger feature for GPIO pins using ADC driver,
 * when interrupt request is initiated due to event on PinId ,
 * and send to NVIC ( even if NVIC disable this interrupt) when (set pending flag ) the ADC is triggered .
 * note : pin 12 has this feature always enabled event if EnableTrigger = FALSE,
 * due to compatibility  with older devices .
 */

void Port_PinAdcTrigger ( Port_PinType PinId, boolean EnableTrigger )
{

    uint8 PinNumber = PinId&PORT_PIN_NUMBER_MASK, PortNumber = (PinId&PORT_PORT_NUMBER_MASK) >> PORT_PORT_NUMBER_OFFSET ;
    Port_RegisterMap_Struct * RegisterBase =  PORT_BASE_REG_EQU(PortNumber) ;

    ASSIGN_BIT ( RegisterBase->Port_GPIOADCCTL, PinNumber, EnableTrigger ) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function enable/disable DMA trigger feature for pin defined by PinId .
 * if EnableTrigger = TRUE then feature is enabled and if = FASLE feature is disabled .
 * trigger to happen pin must be configured as non masked interrupt pin using ExInt driver ,
 * and DMA should enable External trigger feature for GPIO pins using DMA driver,
 * when interrupt request is initiated due to event on PinId ,
 * and send to NVIC ( even if NVIC disable this interrupt) when (set pending flag ) the DMA is triggered .
 */

void Port_PinDmaTrigger ( Port_PinType PinId, boolean EnableTrigger )
{
    uint8 PinNumber = PinId&PORT_PIN_NUMBER_MASK, PortNumber = (PinId&PORT_PORT_NUMBER_MASK) >> PORT_PORT_NUMBER_OFFSET ;
    Port_RegisterMap_Struct * RegisterBase =  PORT_BASE_REG_EQU(PortNumber) ;

    ASSIGN_BIT ( RegisterBase->Port_GPIODMACTL, PinNumber, EnableTrigger ) ;

    return ;
}


/*********************************************************************************/

