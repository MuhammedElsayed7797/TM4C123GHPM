/************************************************/
/*  S2I_Cfg.h                                   */
/*  Created on: Sep 20, 2020                    */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/

#ifndef S2I_CFG_H_
#define S2I_CFG_H_


/*********************************************************************************/

/* this is initializations settings which will be applied for SSI modules after execution of S2I_Init function. */


/*
 * set clock source for every SSI module choose value from macros of S2I_ClockType.
 * example S2I_MOD_0_CLOCK_SOURCE will set clock source for SSI0 module.
 * if S2I_PIOSC_CLOCKis selected for module CPU clock frequency must be at least 16MHz.
 * bit rate of SSI module determined by equation,
 * BR = SSIClk/(Prescaler * (1 + Divide)), SSIClk is PIOSC clock or CPU clock .
 *
 */
#define S2I_MOD_0_CLOCK_SOURCE          S2I_SYSTEM_CLOCK
#define S2I_MOD_1_CLOCK_SOURCE          S2I_SYSTEM_CLOCK
#define S2I_MOD_2_CLOCK_SOURCE          S2I_SYSTEM_CLOCK
#define S2I_MOD_3_CLOCK_SOURCE          S2I_SYSTEM_CLOCK

/*
 * set clock division factor for every SSI module choose value from macros of S2I_ClockType.
 * example S2I_MOD_0_DIVISON_FACTOR will set clock division factor for SSI0 module.
 * devision factor must be in range of 0~255.
 * master clock mustn't exceed 25MHz for master module and 6.67MHz for slave.
 */
#define S2I_MOD_0_DIVISON_FACTOR        0xFF
#define S2I_MOD_1_DIVISON_FACTOR        0x00
#define S2I_MOD_2_DIVISON_FACTOR        0x00
#define S2I_MOD_3_DIVISON_FACTOR        0x00

/*
 * set clock prescaler factor for every SSI module choose value from macros of S2I_ClockType.
 * example S2I_MOD_0_PRESCALER will set SPI mode for SSI0 module.
 * devision factor must be even value in range of 2~254.
 * master clock mustn't exceed 25MHz for master module and 6.67MHz for slave.
 */
#define S2I_MOD_0_PRESCALER             0xFE
#define S2I_MOD_1_PRESCALER             0x04
#define S2I_MOD_2_PRESCALER             0x04
#define S2I_MOD_3_PRESCALER             0x04

/*
 * set SPI mode for every SSI module choose value from macros of S2I_SpiModeType.
 * example S2I_MOD_0_SPI_MODE will set clock prescaler factor for SSI0 module.
 */
#define S2I_MOD_0_SPI_MODE              S2I_LEADING_LOW
#define S2I_MOD_1_SPI_MODE              S2I_LEADING_LOW
#define S2I_MOD_2_SPI_MODE              S2I_LEADING_LOW
#define S2I_MOD_3_SPI_MODE              S2I_LEADING_LOW

/*
 * set frame format for every SSI module choose value from macros of S2I_FrameType.
 * example S2I_MOD_0_FRAME_TYPE will set frame type for SSI0 module.
 */
#define S2I_MOD_0_FRAME_TYPE            S2I_TI_SSI
#define S2I_MOD_1_FRAME_TYPE            S2I_TI_SSI
#define S2I_MOD_2_FRAME_TYPE            S2I_TI_SSI
#define S2I_MOD_3_FRAME_TYPE            S2I_TI_SSI

/*
 * set frame width for every SSI module.
 * example S2I_MOD_0_FRAME_WIDTH will set frame width for SSI0 module.
 * frame width determined by (value+1) value must by in range 3~15 bit
 */
#define S2I_MOD_0_FRAME_WIDTH           15
#define S2I_MOD_1_FRAME_WIDTH           15
#define S2I_MOD_2_FRAME_WIDTH           15
#define S2I_MOD_3_FRAME_WIDTH           15

/*
 * initialize feature provided by S2I_TxBuffer_EmptyInterrupt .
 * example if S2I_MOD_0_EMPTY_TX_INT = TRUE then S2I_TRANSMIT_EXCEED interrupt of SSI0 module,
 * will be triggered when Tx buffer is Empty.
 */
#define S2I_MOD_0_EMPTY_TX_INT          FALSE
#define S2I_MOD_1_EMPTY_TX_INT          FALSE
#define S2I_MOD_2_EMPTY_TX_INT          FALSE
#define S2I_MOD_3_EMPTY_TX_INT          FALSE

/*
 * initialize SSI module as master or slave.
 * example if S2I_MOD_0_DIS_MASTER = FALSE then SSI0 module will be Master, if FALSW will be slave.
 */
#define S2I_MOD_0_DIS_MASTER            FALSE
#define S2I_MOD_1_DIS_MASTER            FALSE
#define S2I_MOD_2_DIS_MASTER            FALSE
#define S2I_MOD_3_DIS_MASTER            FALSE


/*
 * initialize loop back feature of SSI module.
 * example if S2I_MOD_0_LOOP_BACK = TRUE then  loop back feature is enabled for SSI0 module.
 */
#define S2I_MOD_0_LOOP_BACK             TRUE
#define S2I_MOD_1_LOOP_BACK             FALSE
#define S2I_MOD_2_LOOP_BACK             FALSE
#define S2I_MOD_3_LOOP_BACK             FALSE

/*
 * initialize interrupt MASK state for every module
 * every module has 4 interrupt each represented by bit, if bit set then interrupt is enable.
 * LSB is for S2I_RECEIVE_OVERFLOW,
 * next bit for S2I_RECEIVE_TIMEOUT,
 * next bit for S2I_RECEIVE_EXCEED,
 * MSB for S2I_TRANSMIT_EXCEED.
 * S2I_MOD_0_EN_INTERRUPT for SSI0 module.
 */
#define S2I_MOD_0_EN_INTERRUPT          0b0000
#define S2I_MOD_1_EN_INTERRUPT          0b0000
#define S2I_MOD_2_EN_INTERRUPT          0b0000
#define S2I_MOD_3_EN_INTERRUPT          0b0000

/*
 * initialize DMA feature of SSI module.
 * every module has 2 buffers each represent by bit, if bit set then feature is enable.
 * LSB is for Rx buffer,
 * MSB is for Tx buffer,
 */
#define S2I_MOD_0_EN_DMA            0b00
#define S2I_MOD_1_EN_DMA            0b00
#define S2I_MOD_2_EN_DMA            0b00
#define S2I_MOD_3_EN_DMA            0b00


/*********************************************************************************/


#endif /* S2I_CFG_H_ */


