/************************************************/
/*  Dio.c                                       */
/*  Created on: Sep 13, 2020                    */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/


#include "Dio.h"
#include "Dio_Private.h"


extern const uint8 Port_RegisterBusOffset [] ;
extern uint8 Mcu_GpioBusAperture [] ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function used to set the state of pin defined by PinId .
 * the set will take effect according to the mode of pin set by Port driver, so apply it on output modes .
 */

void Dio_WritePin ( Dio_PinType PinId, Dio_PinLevelType State )
{
    uint8 PinNumber = PinId&DIO_PIN_NUMBER_MASK, PortNumber = (PinId&DIO_PORT_NUMBER_MASK) >> DIO_PORT_NUMBER_OFFSET ;
    Dio_RegisterMap_Struct * RegisterBase = DIO_BASE_REG_EQU(PortNumber) ;
    (RegisterBase->Dio_GPIODATA)[ State << PinNumber ] = State << PinNumber ;

    return ;
}

/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function used to get the state of pin defined by PinId .
 * the get will take effect according to the mode of pin set by Port driver, so apply it on input modes .
 * if Pin is in output mode it will return the current output state of the pin .
 */


Dio_PinLevelType Dio_ReadPin ( Dio_PinType PinId )
{
    uint8 PinNumber = PinId&DIO_PIN_NUMBER_MASK, PortNumber = (PinId&DIO_PORT_NUMBER_MASK) >> DIO_PORT_NUMBER_OFFSET ;
    Dio_RegisterMap_Struct * RegisterBase = DIO_BASE_REG_EQU(PortNumber) ;
    Dio_PinLevelType ReturnResult = ((RegisterBase->Dio_GPIODATA)[ 1 << PinNumber ]) >> PinNumber ;


    return ReturnResult;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function used to flip the state of pin defined by PinId .
 * this function read the output state of the pin and flip it then write it again
 * the flip will take effect according to the mode of pin set by Port driver, so apply it on output modes  .
 */

void Dio_FlipPin ( Dio_PinType PinId )
{

    uint8 PinNumber = PinId&DIO_PIN_NUMBER_MASK, PortNumber = (PinId&DIO_PORT_NUMBER_MASK) >> DIO_PORT_NUMBER_OFFSET ;
    Dio_RegisterMap_Struct * RegisterBase = DIO_BASE_REG_EQU(PortNumber) ;
    (RegisterBase->Dio_GPIODATA)[ DIO_HIGH << PinNumber ] ^= DIO_HIGH << PinNumber ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function like Dio_WritePin but for all port defined by PortId
 * the state of lower pin in the port will be represented by LSB in State argument .
 */

void Dio_WritePort ( Dio_PortType PortId, Dio_PortLevelType State )
{

    Dio_RegisterMap_Struct * RegisterBase = DIO_BASE_REG_EQU(PortId) ;
    (RegisterBase->Dio_GPIODATA)[ DIO_ALL_PORT_MASK ] = State ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function like Dio_ReadPin but for all port defined by PortId
 * the state of lower pin in the port will be represented by LSB in return value .
 */

Dio_PortLevelType Dio_ReadPort ( Dio_PortType PortId )
{
    Dio_RegisterMap_Struct * RegisterBase = DIO_BASE_REG_EQU(PortId) ;
    Dio_PortLevelType ReturnResult = (RegisterBase->Dio_GPIODATA)[ DIO_ALL_PORT_MASK ] ;

    return ReturnResult ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function like Dio_FlipPin but for all port defined by PortId
 */

void Dio_FlipPort ( Dio_PortType PortId )
{
    Dio_RegisterMap_Struct * RegisterBase = DIO_BASE_REG_EQU(PortId) ;
    (RegisterBase->Dio_GPIODATA)[ DIO_ALL_PORT_MASK ] ^= DIO_ALL_PORT_MASK ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function like Dio_WritePin but for group of port's pins port defined by PortId
 * the state/mask of lower pin in the port will be represented by LSB in State/Mask arguments .
 * if pin bit in Mask = 0, then the pin will ignore writing (pin state will not change according pin bit in State argument )
 */

void Dio_WriteGroup ( Dio_PortType PortId, Dio_PortLevelType State, Dio_PortLevelType Mask )
{
    Dio_RegisterMap_Struct * RegisterBase = DIO_BASE_REG_EQU(PortId) ;
    (RegisterBase->Dio_GPIODATA)[ Mask ] = State ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function like Dio_ReadPin but for group of port's pins port defined by PortId
 * the state/mask of lower pin in the port will be represented by LSB in return/Mask arguments .
 * if pin bit in Mask = 0, then the pin will ignore reading (pin bit in return value = 0 even if pin state = 1 )
 */

Dio_PortLevelType Dio_ReadGroup ( Dio_PortType PortId, Dio_PortLevelType Mask )
{
    Dio_RegisterMap_Struct * RegisterBase = DIO_BASE_REG_EQU(PortId) ;
    Dio_PortLevelType ReturnResult = (RegisterBase->Dio_GPIODATA)[ Mask ] ;

    return ReturnResult ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function like Dio_FlipPin but for group of port's pins port defined by PortId
 * the mask of lower pin in the port will be represented by LSB in Mask arguments .
 * if pin bit in Mask = 0, then the pin will ignore flip (pin state will not be flip)
 */

void Dio_FlipGroup ( Dio_PortType PortId, Dio_PortLevelType Mask )
{
    Dio_RegisterMap_Struct * RegisterBase = DIO_BASE_REG_EQU(PortId) ;
    (RegisterBase->Dio_GPIODATA)[ Mask ] ^= DIO_ALL_PORT_MASK ;

    return ;
}


/*********************************************************************************/


