/************************************************/
/*  Port.h                                      */
/*  Created on: Sep 13, 2020                    */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/



#ifndef PORT_H_
#define PORT_H_


#include "../Common/Utils.h"
#include "Port_Cfg.h"


/*********************************************************************************/

/*
 * use this macros as a value for variable of Port_PinType type .
 * every pin could be used as a GPIO pin with software control,
 * or as a peripheral pin with hardware control .
 */

/* Port A */
#define PORT_PIN0       0x00         /* not available in TM4C123GXL launch pad connected to ICDI as UART0 */
#define PORT_PIN1       0x01         /* not available in TM4C123GXL launch pad connected to ICDI as UART0 */
#define PORT_PIN2       0x02
#define PORT_PIN3       0x03
#define PORT_PIN4       0x04
#define PORT_PIN5       0x05
#define PORT_PIN6       0x06
#define PORT_PIN7       0x07

/* Port B */
#define PORT_PIN8       0x10
#define PORT_PIN9       0x11
#define PORT_PIN10      0x12
#define PORT_PIN11      0x13
#define PORT_PIN12      0x14
#define PORT_PIN13      0x15
#define PORT_PIN14      0x16
#define PORT_PIN15      0x17

/* Port C */
#define PORT_PIN16      0x20         /* not available in TM4C123GXL launch pad connected to ICDI as JTAG/SWD, Locked After Reset */
#define PORT_PIN17      0x21         /* not available in TM4C123GXL launch pad connected to ICDI as JTAG/SWD, Locked After Reset */
#define PORT_PIN18      0x22         /* not available in TM4C123GXL launch pad connected to ICDI as JTAG/SWD, Locked After Reset */
#define PORT_PIN19      0x23         /* not available in TM4C123GXL launch pad connected to ICDI as JTAG/SWD, Locked After Reset */
#define PORT_PIN20      0x24
#define PORT_PIN21      0x25
#define PORT_PIN22      0x26
#define PORT_PIN23      0x27

/* Port D */
#define PORT_PIN24      0x30
#define PORT_PIN25      0x31
#define PORT_PIN26      0x32
#define PORT_PIN27      0x33
#define PORT_PIN28      0x34         /* not available in TM4C123GXL launch pad connected to USB as USB0 */
#define PORT_PIN29      0x35         /* not available in TM4C123GXL launch pad connected to USB as USB0 */
#define PORT_PIN30      0x36
#define PORT_PIN31      0x37         /* Locked After Reset NMI*/

/* Port E */
#define PORT_PIN32      0x40
#define PORT_PIN33      0x41
#define PORT_PIN34      0x42
#define PORT_PIN35      0x43
#define PORT_PIN36      0x44
#define PORT_PIN37      0x45

/* Port F */
#define PORT_PIN38      0x50         /* available and connected to SW2 in TM4C123GXL launch pad,  Locked After Reset NMI */
#define PORT_PIN39      0x51         /* available and connected to RGB Red in TM4C123GXL launch pad */
#define PORT_PIN40      0x52         /* available and connected to RGB Blue in TM4C123GXL launch pad */
#define PORT_PIN41      0x53         /* available and connected to RGB Green in TM4C123GXL launch pad */
#define PORT_PIN42      0x54         /* available and connected to SW1 in TM4C123GXL launch pad */

typedef uint8 Port_PinType ;

/*********************************************************************************/

/*
 * pin in this mode will be floating pin .
 * digital and analog capabilities for the pin will be disable in this mode .
 */
#define PORT_TRI_STATE              0x00

/*
 * pin in this mode will be input and software can read state of input level using DIO driver .
 * in this mode pin could sink up to 18mA and 5V .
 * for this mode analog capabilities is disabled for this pin
 */
#define PORT_DIGITAL_INPUT          0x01

/*
 * in this mode pin could sink up to 18mA .
 * not all pins could be in this mode just (8,9,12,13,20~29,32~37) .
 * for this mode digital capabilities is disabled for this pin .
 */
#define PORT_ANALOG_INPUT           0x02

/*
 * pin in this mode will be output and software can write state of input level using DIO driver .
 * for this mode analog capabilities is disabled for this pin
 * low state represent by 0V, high state represent by 3.3V
 *
 */
#define PORT_PUSH_PULL_OUTPUT       0x03

/*
 * pin in this mode will be output and software can write state of output level using DIO driver .
 * for this mode analog capabilities is disabled for this pin
 * low state represent by 0V, high state represent tri state .
 * use this mode to drive high state by external pull up to determine high voltage > 3.3V
 */
#define PORT_OPEN_DRAIN_OUTPUT      0x04

/*
 * pin in this mode will be output and hardware can write state of output level .
 * the peripheral control the pin is determined using Port_PinPeripheral function .
 * for this mode analog capabilities is disabled for this pin .
 */
#define PORT_PUSH_PULL_ALT_FUNC     0x05

/*
 * pin in this mode will be output and hardware can write state of output level .
 * the peripheral control the pin is determined using Port_PinPeripheral function .
 * for this mode analog capabilities is disabled for this pin .
 * this mode must be used in case the pin will be driven by I2C module
 */
#define PORT_OPEN_DRAIN_ALT_FUNC    0x06

typedef uint8 Port_ModeType ;


/*********************************************************************************/

/*
 * used with  ResistorType input argument in Port_PinResistor function
 */

#define PORT_NO_RESISTOR            0b00
#define PORT_PULL_UP_RESISTOR       0b01
#define PORT_PULL_DOWN_RESISTOR     0b10


/*********************************************************************************/

/*
 * used with  PinDrive input argument in Port_PinDrivers function
 */

#define PORT_2MA_DRIVER     0b001
#define PORT_4MA_DRIVER     0b010
#define PORT_8MA_DRIVER     0b100       /* using this option will allow enable slew rate control feature */


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will initialize All pins'
 * mode, peripheral signal, internal resistor, drive strength,
 * slew rate, protection lock , ADC & DMA trigger feature .
 * initialization will be according to setting in Port_Cfg.h file .
 * follow rules demonstrated in this Port_Cfg.h file to make proper initialization .
 *
 */

void Port_Init (void) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * use this function to set mode specified by PinMode to pin specified by PinId .
 * some pins(16~19, 37,38) has protection against change their configurations, to change their mode,
 * first use Port_PinLock function
 */

void Port_PinMode ( Port_PinType PinId, Port_ModeType PinMode ) ;


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

void Port_PinPeripheral ( Port_PinType PinId, uint8 Peripheral ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function used to set an internal resistor (ResistorType) to pin defined by PinId .
 * enable one resistor type will disable the others .
 * some pins(16~19, 37,38) has protection against change their configurations,
 * to change their internal resistor first use Port_PinLock function .
 * the internal resistor setting will be ignored for open drain output modes and also for I2C signal pins .
 * internal resistor must be disabled ResistorType = PORT_NO_RESISTOR  when analog input mode is selected
 */

void Port_PinResistor ( Port_PinType PinId, uint8 ResistorType ) ;


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

void Port_PinDrivers ( Port_PinType PinId, uint8 PinDriver ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function enable/disable the feature of slew rate control for pin defined by PinId.
 * if EnableRateControl = TRUE then feature is enabled .
 * note that this feature is only available for pin driven by 8mA drive,
 * which could be selected for pin using Port_PinDrivers function .
 */

void Port_PinSlewRate ( Port_PinType PinId, boolean EnableRateControl ) ;


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

StatusType Port_PinLock ( Port_PinType PinId, boolean DisableLock ) ;


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

void Port_PinAdcTrigger ( Port_PinType PinId, boolean EnableTrigger ) ;



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

void Port_PinDmaTrigger ( Port_PinType PinId, boolean EnableTrigger ) ;


/*********************************************************************************/

#endif /* PORT_H_ */




