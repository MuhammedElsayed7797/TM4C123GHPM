/************************************************/
/*  ExtInt.h                                    */
/*  Created on: Sep 15, 2020                    */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/

#ifndef EXTINT_H_
#define EXTINT_H_


#include "../Common/Utils.h"
#include "ExtInt_Cfg.h"


/*********************************************************************************/

/* use this macros as a value for variable of ExtInt_PinType type  */

/* Port A */
#define EXTINT_PIN0       0x00         /* not available in TM4C123GXL launch pad connected to ICDI as UART0 */
#define EXTINT_PIN1       0x01         /* not available in TM4C123GXL launch pad connected to ICDI as UART0 */
#define EXTINT_PIN2       0x02
#define EXTINT_PIN3       0x03
#define EXTINT_PIN4       0x04
#define EXTINT_PIN5       0x05
#define EXTINT_PIN6       0x06
#define EXTINT_PIN7       0x07

/* PORT B */
#define EXTINT_PIN8       0x10
#define EXTINT_PIN9       0x11
#define EXTINT_PIN10      0x12
#define EXTINT_PIN11      0x13
#define EXTINT_PIN12      0x14
#define EXTINT_PIN13      0x15
#define EXTINT_PIN14      0x16
#define EXTINT_PIN15      0x17

/* PORT C */
#define EXTINT_PIN16      0x20         /* not available in TM4C123GXL launch pad connected to ICDI as JTAG/SWD, Locked After Reset */
#define EXTINT_PIN17      0x21         /* not available in TM4C123GXL launch pad connected to ICDI as JTAG/SWD, Locked After Reset */
#define EXTINT_PIN18      0x22         /* not available in TM4C123GXL launch pad connected to ICDI as JTAG/SWD, Locked After Reset */
#define EXTINT_PIN19      0x23         /* not available in TM4C123GXL launch pad connected to ICDI as JTAG/SWD, Locked After Reset */
#define EXTINT_PIN20      0x24
#define EXTINT_PIN21      0x25
#define EXTINT_PIN22      0x26
#define EXTINT_PIN23      0x27

/* PORT D */
#define EXTINT_PIN24      0x30
#define EXTINT_PIN25      0x31
#define EXTINT_PIN26      0x32
#define EXTINT_PIN27      0x33
#define EXTINT_PIN28      0x34         /* not available in TM4C123GXL launch pad connected to USB as USB0 */
#define EXTINT_PIN29      0x35         /* not available in TM4C123GXL launch pad connected to USB as USB0 */
#define EXTINT_PIN30      0x36
#define EXTINT_PIN31      0x37         /* Locked After Reset NMI*/

/* PORT E */
#define EXTINT_PIN32      0x40
#define EXTINT_PIN33      0x41
#define EXTINT_PIN34      0x42
#define EXTINT_PIN35      0x43
#define EXTINT_PIN36      0x44
#define EXTINT_PIN37      0x45

/* PORT F */
#define EXTINT_PIN38      0x50         /* available and connected to SW2 in TM4C123GXL launch pad,  Locked After Reset NMI */
#define EXTINT_PIN39      0x51         /* available and connected to RGB Red in TM4C123GXL launch pad */
#define EXTINT_PIN40      0x52         /* available and connected to RGB Blue in TM4C123GXL launch pad */
#define EXTINT_PIN41      0x53         /* available and connected to RGB Green in TM4C123GXL launch pad */
#define EXTINT_PIN42      0x54         /* available and connected to SW1 in TM4C123GXL launch pad */

typedef uint8 ExtInt_PinType ;


/*********************************************************************************/

/* use this macros as a value for variable of ExtInt_PortType type  */

#define EXTINT_PORT_A      0x00
#define EXTINT_PORT_B      0x01
#define EXTINT_PORT_C      0x02
#define EXTINT_PORT_D      0x03
#define EXTINT_PORT_E      0x04
#define EXTINT_PORT_F      0x05

typedef uint8 ExtInt_PortType ;


/*********************************************************************************/

/* use this macros as a value for variable of ExtInt_ModeType type  */

/*
 *  for edge modes to set event flag the shortest time of states on the pin must be ,
 * 1 system clock cycle for pins in AHB ports ,
 * 2 system clock cycle for pins in APB ports .
 * when event flag is set it must be cleared by software to allow setting it again .
 */

/*
 *  for level modes to set event flag the shortest time of states on the pin must be ,
 * 1 system clock cycle for pins in AHB ports ,
 * 2 system clock cycle for pins in APB ports .
 * when event flag is set it will be cleared automatically when pin state is changed to opposite state .
 * clearing event flag by software has no
 */

/*
* all events flag of non masked pin interrupts on same port will be or together,
* and result will be signal to interrupt for NVIC, which need 1 system clock cycle to set port interrupt pending flag .
* so it will be 2 system clock cycles till port interrupt from apply event condition state to ,
* NVIC pending flag to be set(if it was cleared) (case AHB port), and 3 for APB port .
* if NVIC pending flag is set it won't be cleared by clearing Event flag .
* to make pending flag be set again after cleared port interrupt signal must has a rising edge,
* which mean all events flag of port must be cleared then at least one of them being set again .
*/


/* when signal on pin become low after being high the event flag will be set */
#define EXTINT_FALLING_EDGE     0x00

/* when signal on pin become high after being low the event flag will be set */
#define EXTINT_RISING_EDGE      0x01

/* when signal on pin become high after being low or low after being high the event flag will be set */
#define EXTINT_BOTH_EDGE        0x02

/* as long as the signal on pin is low, the event will be set  */
#define EXTINT_LOW_LEVEL        0x03

/* as long as the signal on pin is high, the event will be set  */
#define EXTINT_HIGH_LEVEL       0x04

typedef uint8 ExtInt_ModeType ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will initialize All pins' interrupt modes & masks
 * initialization will be according to setting in ExtInt_Cfg.h file .
 * follow rules demonstrated in ExtInt_Cfg.h file to make proper initialization .
 */


void ExtInt_Init (void) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will change interrupt mode of interrupt pin defined by (PinId) to mode defined by (Mode) .
 * see note on interrupt modes in ExtIng.h file at ExtInt_ModeType type definition .
 */

void ExtInt_InterruptMode ( ExtInt_PinType PinId, ExtInt_ModeType Mode ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will change interrupt enable state of pin defined by (PinId) .
 * if Enable argument = TRUE then interrupt is unmasked .
 * masking interrupt won't prevent setting of it's flag .
 * if event flag is set and interrupt is unmasked then interrupt signal of port will be set to NVIC if it was cleared .
 * operations on port interrupt like pending & enable is done by NVIC driver .
 */

void ExtInt_EnableInterrupt ( ExtInt_PinType PinId, boolean Enable ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will get state of event flag of unmasked  interrupt pin defined by (PinId) .
 * if  interrupt pin is masked the this function will return FALSE in all cases
 */

boolean ExtInt_GetInterruptState ( ExtInt_PinType PinId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will get state of event flag of unmasked and masked interrupt pin defined by (PinId) .
 */

boolean ExtInt_GetEventState ( ExtInt_PinType PinId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will clear event flag interrupt pin defined by (PinId) .
 * this is function for interrupt pin that work in edges interrupt modes .
 * event flag of level interrupt modes is cleared automatically and can't done by software .
 * use this function inside ISR of interrupt pin to allow event flag to be set again and generate new interrupt .
 * and to prevent execution of interrupt pin ISR, when the interrupt port ISR is fired due to other interrupt pin
 */

void ExtInt_ClearEvent ( ExtInt_PinType PinId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this will assign call back function to be called inside port ISR .
 * the port ISR should handle all port's pin ISRs that configured to generate interrupts .
 * all unmasked interrupt pins' event flags is or and result is the port interrupt signal,
 * so if all unmasked events is cleared and on of them get set the port interrupt ISR will be executed if enable in NVIC .
 */

void ExtInt_AssignISR ( ExtInt_PortType PortNumber ,void (*FuncPtr) (void) ) ;


/*********************************************************************************/


#endif /* EXTINT_H_ */



