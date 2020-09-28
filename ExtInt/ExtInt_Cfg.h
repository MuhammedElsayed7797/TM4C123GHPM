/************************************************/
/*  ExtInt_Cfg.h                                */
/*  Created on: Sep 15, 2020                    */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/

#ifndef EXTINT_CFG_H_
#define EXTINT_CFG_H_


/*********************************************************************************/

/*
 * set the Mode of every interrupt pin after Ext_Init function execution .
 * every pin is represented by a bit in following macros .
 * Example : EXTINT_MODE_FALLING_0_7 for pin 0~7 LSB in the macro represent  pin 0 .
 * don't choose more than one mode for same pin or pin mode won't be expected
 */

/* set pin bit to 1 will make the pin interrupt in rising edge mode*/
#define EXTINT_MODE_FALLING_0_7         0x00
#define EXTINT_MODE_FALLING_8_15        0x00
#define EXTINT_MODE_FALLING_16_23       0x00
#define EXTINT_MODE_FALLING_24_31       0x00
#define EXTINT_MODE_FALLING_32_37       0x00
#define EXTINT_MODE_FALLING_38_42       0x01

/* set pin bit to 1 will make the pin interrupt in falling edge mode*/
#define EXTINT_MODE_RISING_0_7          0xFF
#define EXTINT_MODE_RISING_8_15         0xFF
#define EXTINT_MODE_RISING_16_23        0xFF
#define EXTINT_MODE_RISING_24_31        0xFF
#define EXTINT_MODE_RISING_32_37        0xFF
#define EXTINT_MODE_RISING_38_42        0x0E

/* set pin bit to 1 will make the pin interrupt in both(rising&falling) edge mode*/
#define EXTINT_MODE_BOTH_0_7            0x00
#define EXTINT_MODE_BOTH_8_15           0x00
#define EXTINT_MODE_BOTH_16_23          0x00
#define EXTINT_MODE_BOTH_24_31          0x00
#define EXTINT_MODE_BOTH_32_37          0x00
#define EXTINT_MODE_BOTH_38_42          0x00

/* set pin bit to 1 will make the pin interrupt in low level mode*/
#define EXTINT_MODE_LOW_0_7             0x00
#define EXTINT_MODE_LOW_8_15            0x00
#define EXTINT_MODE_LOW_16_23           0x00
#define EXTINT_MODE_LOW_24_31           0x00
#define EXTINT_MODE_LOW_32_37           0x00
#define EXTINT_MODE_LOW_38_42           0x10

/* set pin bit to 1 will make the pin interrupt in high level mode*/
#define EXTINT_MODE_HIGH_0_7            0x00
#define EXTINT_MODE_HIGH_8_15           0x00
#define EXTINT_MODE_HIGH_16_23          0x00
#define EXTINT_MODE_HIGH_24_31          0x00
#define EXTINT_MODE_HIGH_32_37          0x00
#define EXTINT_MODE_HIGH_38_42          0x00


/*********************************************************************************/

/*
 * set the enable state of every interrupt pin after Ext_Init function execution .
 * every pin is represented by a bit in following macros .
 * Example : EXTINT_ENABLE_0_7 for pin 0~7 LSB in the macro represent  pin 0 .
 * don't choose more than one mode for same pin or pin mode won't be expected
 */

/* set pin bit to 1 will enable the pin interrupt to generate interrupt signal of its port */
#define EXTINT_ENABLE_0_7       0x00
#define EXTINT_ENABLE_8_15      0x00
#define EXTINT_ENABLE_16_23     0x00
#define EXTINT_ENABLE_24_31     0x00
#define EXTINT_ENABLE_32_37     0x00
#define EXTINT_ENABLE_38_42     0x11


/*********************************************************************************/


#endif /* EXTINT_CFG_H_ */

