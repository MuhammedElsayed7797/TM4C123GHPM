/************************************************/
/*  Dio.h                                       */
/*  Created on: Sep 13, 2020                    */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/




#ifndef DIO_H_
#define DIO_H_


#include "../Common/Utils.h"
#include "Dio_Cfg.h"

/*********************************************************************************/

/** use this macros as a value for variable of Dio_PinID type .*/

/* Port A */
#define DIO_PIN0       0x00         /* not available in TM4C123GXL launch pad connected to ICDI as UART0 */
#define DIO_PIN1       0x01         /* not available in TM4C123GXL launch pad connected to ICDI as UART0 */
#define DIO_PIN2       0x02
#define DIO_PIN3       0x03
#define DIO_PIN4       0x04
#define DIO_PIN5       0x05
#define DIO_PIN6       0x06
#define DIO_PIN7       0x07

/* PORT B */
#define DIO_PIN8       0x10
#define DIO_PIN9       0x11
#define DIO_PIN10      0x12
#define DIO_PIN11      0x13
#define DIO_PIN12      0x14
#define DIO_PIN13      0x15
#define DIO_PIN14      0x16
#define DIO_PIN15      0x17

/* PORT C */
#define DIO_PIN16      0x20         /* not available in TM4C123GXL launch pad connected to ICDI as JTAG/SWD, Locked After Reset */
#define DIO_PIN17      0x21         /* not available in TM4C123GXL launch pad connected to ICDI as JTAG/SWD, Locked After Reset */
#define DIO_PIN18      0x22         /* not available in TM4C123GXL launch pad connected to ICDI as JTAG/SWD, Locked After Reset */
#define DIO_PIN19      0x23         /* not available in TM4C123GXL launch pad connected to ICDI as JTAG/SWD, Locked After Reset */
#define DIO_PIN20      0x24
#define DIO_PIN21      0x25
#define DIO_PIN22      0x26
#define DIO_PIN23      0x27

/* PORT D */
#define DIO_PIN24      0x30
#define DIO_PIN25      0x31
#define DIO_PIN26      0x32
#define DIO_PIN27      0x33
#define DIO_PIN28      0x34         /* not available in TM4C123GXL launch pad connected to USB as USB0 */
#define DIO_PIN29      0x35         /* not available in TM4C123GXL launch pad connected to USB as USB0 */
#define DIO_PIN30      0x36
#define DIO_PIN31      0x37         /* Locked After Reset NMI*/

/* PORT E */
#define DIO_PIN32      0x40
#define DIO_PIN33      0x41
#define DIO_PIN34      0x42
#define DIO_PIN35      0x43
#define DIO_PIN36      0x44
#define DIO_PIN37      0x45

/* PORT F */
#define DIO_PIN38      0x50         /* available and connected to SW2 in TM4C123GXL launch pad,  Locked After Reset NMI */
#define DIO_PIN39      0x51         /* available and connected to RGB Red in TM4C123GXL launch pad */
#define DIO_PIN40      0x52         /* available and connected to RGB Blue in TM4C123GXL launch pad */
#define DIO_PIN41      0x53         /* available and connected to RGB Green in TM4C123GXL launch pad */
#define DIO_PIN42      0x54         /* available and connected to SW1 in TM4C123GXL launch pad */

typedef uint8 Dio_PinType ;


/*********************************************************************************/


#define DIO_PORT_A      0x00
#define DIO_PORT_B      0x01
#define DIO_PORT_C      0x02
#define DIO_PORT_D      0x03
#define DIO_PORT_E      0x04
#define DIO_PORT_F      0x05

typedef uint8 Dio_PortType ;


/*********************************************************************************/


#define DIO_LOW     0x00
#define DIO_HIGH    0x01


typedef uint8 Dio_PinLevelType ;


/*********************************************************************************/


typedef uint8 Dio_PortLevelType ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function used to set the state of pin defined by PinId .
 * the set will take effect according to the mode of pin set by Port driver, so apply it on output modes .
 */

void Dio_WritePin ( Dio_PinType PinId, Dio_PinLevelType State ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function used to get the state of pin defined by PinId .
 * the get will take effect according to the mode of pin set by Port driver, so apply it on input modes .
 * if Pin is in output mode it will return the current output state of the pin .
 */

Dio_PinLevelType Dio_ReadPin ( Dio_PinType PinId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function used to flip the state of pin defined by PinId .
 * this function read the output state of the pin and flip it then write it again
 * the flip will take effect according to the mode of pin set by Port driver, so apply it on output modes  .
 */

void Dio_FlipPin ( Dio_PinType PinId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function like Dio_WritePin but for all port defined by PortId
 * the state of lower pin in the port will be represented by LSB in State argument .
 */

void Dio_WritePort ( Dio_PortType PortId, Dio_PortLevelType State ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function like Dio_ReadPin but for all port defined by PortId
 * the state of lower pin in the port will be represented by LSB in return value .
 */

Dio_PortLevelType Dio_ReadPort ( Dio_PortType PortId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function like Dio_FlipPin but for all port defined by PortId
 */

void Dio_FlipPort ( Dio_PortType PortId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function like Dio_WritePin but for group of port's pins port defined by PortId
 * the state/mask of lower pin in the port will be represented by LSB in State/Mask arguments .
 * if pin bit in Mask = 0, then the pin will ignore writing (pin state will not change according pin bit in State argument )
 */

void Dio_WriteGroup ( Dio_PortType PortId, Dio_PortLevelType State, Dio_PortLevelType Mask ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function like Dio_ReadPin but for group of port's pins port defined by PortId
 * the state/mask of lower pin in the port will be represented by LSB in return/Mask arguments .
 * if pin bit in Mask = 0, then the pin will ignore reading (pin bit in return value = 0 even if pin state = 1 )
 */

Dio_PortLevelType Dio_ReadGroup ( Dio_PortType PortId, Dio_PortLevelType Mask ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function like Dio_FlipPin but for group of port's pins port defined by PortId
 * the mask of lower pin in the port will be represented by LSB in Mask arguments .
 * if pin bit in Mask = 0, then the pin will ignore flip (pin state will not be flip)
 */

void Dio_FlipGroup ( Dio_PortType PortId, Dio_PortLevelType Mask ) ;


/*********************************************************************************/


#endif /* DIO_H_ */
