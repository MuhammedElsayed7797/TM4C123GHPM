/************************************************/
/*  Port_Cfg.h                                  */
/*  Created on: Sep 13, 2020                    */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/


#ifndef PORT_CFG_H_
#define PORT_CFG_H_


/*********************************************************************************/

/*
 * set the Mode of every I/O pin after Port_Init function execution .
 * every pin is represented by a bit in following macros .
 * Example : PORT_MODE_TRI_STATE_0_7 for pin 0~7 LSB in the macro represent  pin 0 .
 * don't choose more than one mode for same pin or pin mode won't be expected
 * Warning pins(16~19) is connected to JTAG/SWD and has a lock protection to change their mode .
 * don't unlock them or if unlock then don't change mode or debugger/flasher will be disconnected
 */

/* set pin bit to 1 will make the pin in tri-state mode*/
#define PORT_MODE_TRI_STATE_0_7         0xC3
#define PORT_MODE_TRI_STATE_8_15        0xFF
#define PORT_MODE_TRI_STATE_16_23       0xF0
#define PORT_MODE_TRI_STATE_24_31       0xFF
#define PORT_MODE_TRI_STATE_32_37       0x3F
#define PORT_MODE_TRI_STATE_38_42       0x00

/* set pin bit to 1 will make the pin in Digital input mode*/
#define PORT_MODE_DIGITAL_IN_0_7        0x00
#define PORT_MODE_DIGITAL_IN_8_15       0x00
#define PORT_MODE_DIGITAL_IN_16_23      0x00
#define PORT_MODE_DIGITAL_IN_24_31      0x00
#define PORT_MODE_DIGITAL_IN_32_37      0x00
#define PORT_MODE_DIGITAL_IN_38_42      0x11

/* set pin bit to 1 will make the pin in Analog input mode*/
#define PORT_MODE_ANALOG_IN_0_7         0x00
#define PORT_MODE_ANALOG_IN_8_15        0x00
#define PORT_MODE_ANALOG_IN_16_23       0x00
#define PORT_MODE_ANALOG_IN_24_31       0x00
#define PORT_MODE_ANALOG_IN_32_37       0x00
#define PORT_MODE_ANALOG_IN_38_42       0x00

/* set pin bit to 1 will make the pin in push pull output mode*/
#define PORT_MODE_PUSH_OUT_0_7          0x00
#define PORT_MODE_PUSH_OUT_8_15         0x00
#define PORT_MODE_PUSH_OUT_16_23        0x00
#define PORT_MODE_PUSH_OUT_24_31        0x00
#define PORT_MODE_PUSH_OUT_32_37        0x00
#define PORT_MODE_PUSH_OUT_38_42        0x0E

/* set pin bit to 1 will make the pin in open drain output mode*/
#define PORT_MODE_DRAIN_OUT_0_7         0x00
#define PORT_MODE_DRAIN_OUT_8_15        0x00
#define PORT_MODE_DRAIN_OUT_16_23       0x00
#define PORT_MODE_DRAIN_OUT_24_31       0x00
#define PORT_MODE_DRAIN_OUT_32_37       0x00
#define PORT_MODE_DRAIN_OUT_38_42       0x00

/* set pin bit to 1 will make the pin in open drain alternate function mode */
#define PORT_MODE_PUSH_ALT_0_7          0x00
#define PORT_MODE_PUSH_ALT_8_15         0x00
#define PORT_MODE_PUSH_ALT_16_23        0x0F
#define PORT_MODE_PUSH_ALT_24_31        0x00
#define PORT_MODE_PUSH_ALT_32_37        0x00
#define PORT_MODE_PUSH_ALT_38_42        0x00

/* set pin bit to 1 will make the pin in push pull alternate function mode (must be used to I2C)*/
#define PORT_MODE_DRAIN_ALT_0_7         0x3F
#define PORT_MODE_DRAIN_ALT_8_15        0x00
#define PORT_MODE_DRAIN_ALT_16_23       0x00
#define PORT_MODE_DRAIN_ALT_24_31       0x00
#define PORT_MODE_DRAIN_ALT_32_37       0x00
#define PORT_MODE_DRAIN_ALT_38_42       0x00


/*********************************************************************************/

/*
 * set the Signal peripheral of every I/O pin after Port_Init function execution .
 * every pin is represented by a 4 bits in following macros .
 * Example : PORT_PERIPHERAL_0_7 for pin 0~7 the 4 LSBs in the macro represent  pin 0 .
 * this setting will be applied when pin set to operate in alternate function mode .
 * table 23-5 in data sheet demonstrate peripherals signals available for every pin,
 * and corresponding number to write in the pin bit field to choose this peripheral signal .
 * Warning pins(16~19) is connected to JTAG/SWD and configured to JTAG/SWD peripheral signal .
 * don't change their peripheral signal if changed debugger/flasher will be disconnected
 */


#define PORT_PERIPHERAL_0_7         0x00222200
#define PORT_PERIPHERAL_8_15        0x00000000
#define PORT_PERIPHERAL_16_23       0x00001111
#define PORT_PERIPHERAL_24_31       0x00000000
#define PORT_PERIPHERAL_32_37       0x000000
#define PORT_PERIPHERAL_38_42       0x00000


/*********************************************************************************/
/*
 * set the internal resistor of every I/O pin after Port_Init function execution .
 * every pin is represented by a 1 bit in following macros .
 * Example : PORT_INTERNAL_RES_EN_0_7 for pin 0~7 LSB in the macro represent  pin 0 .
 * if pin set to analog input mode then internal resistor must be disabled .
 * for open drain o/p mode internal resistor is automatically disconnected regard less its configuration ,
 * and when mode changed configuration will be applied .
 * some peripheral signals automatically disconnect internal resistor like I2C .
 * Warning pins(16~19) is connected to JTAG/SWD and has a lock protection to change their internal resistor settings .
 * don't unlock them or if unlock then don't change internal resistors or debugger/flasher won't work proberly
 */


/*
 * set pin bit will enable pin to have internal resistor, and clear pin bit will disable pull up/down internal resistor
 * this macros like a mask for PORT_INTERNAL_RES_TYPE_X_X macros
 */
#define PORT_INTERNAL_RES_EN_0_7        0x3C
#define PORT_INTERNAL_RES_EN_8_15       0x00
#define PORT_INTERNAL_RES_EN_16_23      0x0F
#define PORT_INTERNAL_RES_EN_24_31      0x00
#define PORT_INTERNAL_RES_EN_32_37      0x00
#define PORT_INTERNAL_RES_EN_38_42      0x11

/* set pin bit will enable internal pull up resistor for pin, and clear it will enable internal pull down resistor */
#define PORT_INTERNAL_RES_TYPE_0_7      0x3C
#define PORT_INTERNAL_RES_TYPE_8_15     0x00
#define PORT_INTERNAL_RES_TYPE_16_23    0x0F
#define PORT_INTERNAL_RES_TYPE_24_31    0x00
#define PORT_INTERNAL_RES_TYPE_32_37    0x00
#define PORT_INTERNAL_RES_TYPE_38_42    0x11


/*********************************************************************************/

/*
 * set the drive strength of every I/O pin after Port_Init function execution .
 * every pin is represented by a 1 bit in following macros .
 * Example : PORT_2MA_DRIVE_EN_0_7 for pin 0~7 LSB in the macro represent  pin 0 .
 * every pin could be drive by one 2mA,4mA,8mA drive
 * if one pin has its bit set for more than one drive the highest drive will be set .
 * note that don't make all pins has highest current configuration,
 * there's a limit for sum of sink and source current for different group of pins,
 * groups of pins and max sum current listed in page 1360,1361 in DataSheet .
 */


/* set pin bit bit will enable 2mA drive for pin */
#define PORT_2MA_DRIVE_EN_0_7       0xFF
#define PORT_2MA_DRIVE_EN_8_15      0xFF
#define PORT_2MA_DRIVE_EN_16_23     0xFF
#define PORT_2MA_DRIVE_EN_24_31     0xFF
#define PORT_2MA_DRIVE_EN_32_37     0x3F
#define PORT_2MA_DRIVE_EN_38_42     0x1F

/* set pin bit bit will enable 4mA drive for pin */
#define PORT_4MA_DRIVE_EN_0_7       0x00
#define PORT_4MA_DRIVE_EN_8_15      0x00
#define PORT_4MA_DRIVE_EN_16_23     0x00
#define PORT_4MA_DRIVE_EN_24_31     0x00
#define PORT_4MA_DRIVE_EN_32_37     0x00
#define PORT_4MA_DRIVE_EN_38_42     0x00

/* set pin bit bit will enable 8mA drive for pin */
#define PORT_8MA_DRIVE_EN_0_7       0x00
#define PORT_8MA_DRIVE_EN_8_15      0x00
#define PORT_8MA_DRIVE_EN_16_23     0x00
#define PORT_8MA_DRIVE_EN_24_31     0x00
#define PORT_8MA_DRIVE_EN_32_37     0x00
#define PORT_8MA_DRIVE_EN_38_42     0x00


/*********************************************************************************/

/*
 * set the slew rate control feature of every I/O pin after Port_Init function execution .
 * every pin is represented by a 1 bit in following macros .
 * Example : PORT_SLEW_RATE_CTL_EN_0_7 for pin 0~7 LSB in the macro represent  pin 0 .
 * feature is only available for pins that driven by 8mA drive .
 */

/* set pin bit will enable slew rate control feature for pin */
#define PORT_SLEW_RATE_CTL_EN_0_7           0x00
#define PORT_SLEW_RATE_CTL_EN_8_15          0x00
#define PORT_SLEW_RATE_CTL_EN_16_23         0x00
#define PORT_SLEW_RATE_CTL_EN_24_31         0x00
#define PORT_SLEW_RATE_CTL_EN_32_37         0x00
#define PORT_SLEW_RATE_CTL_EN_38_42         0x00


/*********************************************************************************/

/*
 * lock/unlock pins that have lock features which is (16~19,31,38) pins .
 * Example : PORT_PIN_UNLOCK_16_19 for pin 16~19 LSB in the macro represent  pin 16 .
 * 16~19 pins locked to JTAG/SWD feature don't unlock them and change their setting or flasher/debugger will be disconnected .
 * pins 31,38 has NMI functionality be careful with them or NMI exception handler will be generated
 */

/* set bit pin will unlock the pin for changing it's mode and internal resistor settings */
#define PORT_PIN_UNLOCK_16_19       0b0000
#define PORT_PIN_UNLOCK_31          0b00
#define PORT_PIN_UNLOCK_38          0b01


/*********************************************************************************/

/*
 * enable/disable the ADC trigger feature of every I/O pin after Port_Init function execution .
 * every pin is represented by a 1 bit in following macros .
 * Example : PORT_ADC_TRIGGER_EN_0_7 for pin 0~7 LSB in the macro represent  pin 0 .
 */


/* set pin bit will enable ADC trigger feature for pin */
#define PORT_ADC_TRIGGER_EN_0_7         0x00
#define PORT_ADC_TRIGGER_EN_8_15        0x00
#define PORT_ADC_TRIGGER_EN_16_23       0x00
#define PORT_ADC_TRIGGER_EN_24_31       0x00
#define PORT_ADC_TRIGGER_EN_32_37       0x00
#define PORT_ADC_TRIGGER_EN_38_42       0x00


/*********************************************************************************/

/*
 * enable/disable the DMA trigger feature of every I/O pin after Port_Init function execution .
 * every pin is represented by a 1 bit in following macros .
 * Example : PORT_ADC_TRIGGER_EN_0_7 for pin 0~7 LSB in the macro represent  pin 0 .
 */


/* set pin bit will enable DMA trigger feature for pin */
#define PORT_DMA_TRIGGER_EN_0_7         0x00
#define PORT_DMA_TRIGGER_EN_8_15        0x00
#define PORT_DMA_TRIGGER_EN_16_23       0x00
#define PORT_DMA_TRIGGER_EN_24_31       0x00
#define PORT_DMA_TRIGGER_EN_32_37       0x00
#define PORT_DMA_TRIGGER_EN_38_42       0x00


/*********************************************************************************/


#endif /* PORT_CFG_H_ */


