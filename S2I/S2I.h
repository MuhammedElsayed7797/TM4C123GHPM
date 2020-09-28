/************************************************/
/*  S2I.h                                       */
/*  Created on: Sep 20, 2020                    */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/

#ifndef S2I_H_
#define S2I_H_


#include "../Common/Utils.h"
#include "S2I_Cfg.h"


/*********************************************************************************/


#define S2I_MODULE_OFFSET_2         0x0400
#define S2I_MOD_0_BUFFER_ADD        ((volatile uint32 *) 0x40008008 )


/*
 * use this macros as a values for S2I_SpiModeType variables.
 * this type indicate mode of SPI format case used in SSI module.
 * mode determine idle state of clock and,
 * the edge that module shift in/out the data on the bus.
 */

/* LOW is clock's idle state, and data shifted in on leading edge (rising edge)*/
#define S2I_LEADING_LOW     0b00

/*
 * HIGH is clock's idle state, and data shifted in on leading edge (falling edge).
 * clock pin must enable internal pull up resistor.
 */
#define S2I_LEADING_HIGH    0b01

/* LOW is clock's idle state, and data shifted in on leading edge (falling edge) */
#define S2I_TRAILING_LOW    0b10

/*
 * HIGH is clock's idle state, and data shifted in on leading edge (rising edge).
 * clock pin must enable internal pull up resistor.
 */
#define S2I_TRAILING_HIGH   0b11

typedef uint8 S2I_SpiModeType ;


/*********************************************************************************/

/*
 * use this macros as a values for S2I_FrameType variables, this type indicate frame format of SSI module.
 * SSI connected master and slave modules must have same format and same clock.
 * recommended to enable internal pull up resistors for all SSI module pins.
 */

/*
 * need (n * (Frame width + 1.5)) - 0.5  clock cycles to transfer n frames in leading SPI modes,
 * and (n * (frame width+ 1)) for trailing SPI modes.
 * refer to S2I_SpiModeType to get more information about SPI modes
 * master and slave in SPI format must have same mode.
 */
#define S2I_SPI             0x00

/* need (n * Frame Width + 1) clock cycles to transfer n frame using this format */
#define S2I_TI_SSI          0x01

/*
 * need (n * (9+frame width) + 1) clock cycles to transfer n frame using this format.
 * use this in format in master mode only .
 */
#define S2I_MICROWIRE       0x02

typedef uint8 S2I_FrameType ;


/*********************************************************************************/

/*
 * use this macros as a values for S2I_BufferStateType variables, this type indicate state of the buffer.
 * Case Rx buffer read done by SW and write by HW, and vice versa for Tx buffer
 */

/*
 * buffer is empty so it available for write and not for read.
 * write will initiate transmission case module is master and,
 * read will return the value of oldest written/read location in the buffer
 */
#define S2I_BUFFER_EMPTY        0b00

/*
 * buffer is not empty not full so it available for write and read.
 * write will overwrite oldest written location in buffer,
 * read will return the value of oldest unread location in the buffer.
 */
#define S2I_BUFFER_EXCEED       0b01

/*
 * buffer is full so it available for read and not for write.
 * write will have no effect,
 * read will return the value of oldest unread location in the buffer.
 */
#define S2I_BUFFER_FULL         0b11

typedef uint8 S2I_BufferStateType ;


/*********************************************************************************/

/*
 * use this macros as a values for S2I_InterruptType variables.
 * edge interrupt will be set when interrupt event occur and just cleared except by SW using S2I_ClearEvent.
 * level interrupt will be set as long as event condition is TRUE and will be cleared once condition is FALSE.
 * event flag will be set according to event condition whether interrupt is enabled or not.
 */

/* edge event happen when receive buffer is full and didn't been read by SW and new data is received */
#define S2I_RECEIVE_OVERFLOW        0x00

/* edge event happen when Rx buffer don't become empty after,
 * 32 SPI clock cycle is passed on buffer after being non empty.
 */
#define S2I_RECEIVE_TIMEOUT         0x01

/* Level event happen when Receive buffer is half full or more */
#define S2I_RECEIVE_EXCEED          0x02

/* Level event happen when transmit buffer is half empty or more */
#define S2I_TRANSMIT_EXCEED         0x03


typedef uint8 S2I_InterruptType ;



/*********************************************************************************/

/*
 * use this macros as a values for S2I_BufferType variables.
 * Tx,Rx buffer has 8 frames locations .
 */

#define S2I_RECEIVE_BUFFER      0x00
#define S2I_TRANSMIT_BUFFER     0x01

typedef uint8 S2I_BufferType ;

/*********************************************************************************/

/*
 * use this macros as a value of S2I_ModuleType variables,
 * this type indicate which SSI module is targeted
 */

#define S2I_MODULE_0        0x00
#define S2I_MODULE_1        0x01
#define S2I_MODULE_2        0x02
#define S2I_MODULE_3        0x03

typedef uint8 S2I_ModuleType    ;

/*********************************************************************************/

/*
 * use this macros as a value of S2I_ClockType variables,
 * this type indicate which clock source for SSI module .
 */

#define S2I_SYSTEM_CLOCK    0x00

/* if selected CPU clock frequency must be at least 16MHz*/
#define S2I_PIOSC_CLOCK     0x05

typedef uint8 S2I_ClockType ;


/*********************************************************************************/

/*
 * non privilege, synchronous, non-Reentrant function .
 * this function will access S2I buffer of SSI module determined by ModuleId to R/W.
 * buffer is 8 location depth,
 * read from empty buffer will return value of oldest written location,
 * write to full buffer have no effect.
 * there's 2 buffer Tx/Rx, Tx written by SW and read by HW, and vice versa for Rx buffer.
 * buffer is FIFO, after enable SSI module clock using MCU driver all buffers is empty,
 * writing to empty buffer increase number of full location and read decrease it,
 * if all 8 location is full then buffer is full buffer and if all is empty then buffer is empty one.
 * write to Tx buffer in slave mode will initiate transmission if SSI module internal clock is enabled,
 * and transfer continue till use of S2I_TransferStop which disable internal clock or till buffer is empty.
 * use S2I_TransferStop to stop clock and fill all 8 location of buffer if desired,
 * then enable clock using S2I_TransferStart to transmit all 8 frames in back to back operation.
 */
#define S2I_Buffer(ModuleId)      (*((volatile uint32 *)(S2I_MOD_0_BUFFER_ADD + ModuleId*S2I_MODULE_OFFSET_2)))

/*********************************************************************************/

/*
 * non privilege, synchronous, non-Reentrant function .
 * this function will initialize all SPI modules, according to S2I_Cfg.h file.
 * it will initialize clock, interrupt mask, SSI and SPI modes, DMA feature enable.
 * follow rules demonstrated in S2I_Cfg.h file to make proper initialization .
 */

void S2I_Init(void) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will set the prescaler and division factors of SSI clock module .
 * module divide by ModuleId, Divide is division factor range 0~255,
 * Prescaler is prescaler factor and it must be even number in range of 2-254 .
 * this factors will determine SSI Tx/Rx bit rate according to following equation,
 * BR = SSIClk/(Prescaler * (1 + Divide)), SSIClk is PIOSC clock or CPU clock .
 * for master mode fastest bit rate = 25MHz, and 6.67MHz for slave mode,
 * make sure configuration of clock won't exceed this margins.
 * SSIClk is determined by S2I_Clock function.
 * don't call this function except when transfer is disabled for ModuleId ( use S2I_TransferStop ) .
 */

void S2I_SetClock( S2I_ModuleType ModuleId, uint8 Divide, uint8 Prescaler) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will set the mode (Mode) of SPI format of SSI module determined by ModuleId.
 * refer to S2I_SpiModeType to get information about SPI modes
 * don't call this function except when transfer is disabled for ModuleId ( use S2I_TransferStop ).
 */

void S2I_SpiMode( S2I_ModuleType ModuleId, S2I_SpiModeType Mode ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will set the format (Frame) of SSI module determined by ModuleId.
 * refer to S2I_FrameType to get information about SSI frame formats
 * don't call this function except when transfer is disabled for ModuleId ( use S2I_TransferStop ).
 */

void S2I_SetFrame ( S2I_ModuleType ModuleId, S2I_FrameType Frame ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will set the frame width SSI module determined by ModuleId.
 * frame width determined by (Width+1) Width argument must by in range 3~15 bit
 * don't call this function except when transfer is disabled for ModuleId ( use S2I_TransferStop ).
 */

void S2I_FrameWidth ( S2I_ModuleType ModuleId, uint8 Width ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function select mode of SSI module determined by ModuleId as a master/slave .
 * if Disable argument = FALSE, slave if = TRUE.
 * don't call this function except when transfer is disabled for ModuleId ( use S2I_TransferStop ).
 */

void S2I_MasterDisable ( S2I_ModuleType ModuleId, boolean Disable ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function start (enable) date send/receive of SSI module determined by ModuleId as a master/slave .
 * don't call this function except when transfer is disabled for ModuleId ( use S2I_TransferStop ).
 */

void S2I_TransferStart ( S2I_ModuleType ModuleId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function stop (disable) data send/receive of SSI module determined by ModuleId as a master/slave .
 * don't call this function except when transfer is disabled for ModuleId ( use S2I_TransferStop ).
 */

void S2I_TransferStop ( S2I_ModuleType ModuleId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function enable/disable Loopback feature which is used in testing for module determined by ModuleId.
 * if Enable = TRUE then data is send form Tx buffer internally to Rx buffer
 * don't call this function except when transfer is disabled for ModuleId ( use S2I_TransferStop ).
 */

void S2I_LoopbackEnable ( S2I_ModuleType ModuleId, boolean Enable ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will return state of SSI module determined by ModuleId.
 * if return is = TRUE then module is currently busy in transmission/receiving data.
 */

boolean S2I_ModuleBusy ( S2I_ModuleType ModuleId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will return buffer state (determined  by BufferId) of SSI module determined by ModuleId.
 * refer to S2I_BufferStateType to get more information about different states of buffer
 */

S2I_BufferStateType S2I_BufferState ( S2I_ModuleType ModuleId, S2I_BufferType BufferId) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will make event condition of S2I_TRANSMIT_EXCEED trigger when Tx buffer is fully empty.
 * module is determined by ModuleId, if Enable argument = TRUE then,
 * event will trigger when buffer is empty, if = FALSE then S2I_TRANSMIT_EXCEED trigger as usual.
 */

void S2I_TxBuffer_EmptyInterrupt ( S2I_ModuleType ModuleId, boolean Enable) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will Enable interrupt determined by InterruptID of SSI module determined by ModuleId.
 * interrupt enable/disable won't effect set/clear of event status get by S2I_GetEventState.
 * if event flag is set and interrupt enabled, Interrupt request will be sent to NVIC so,
 * before enable interrupt clear its event flag.
 * refer to S2I_InterruptType to get more information about SSI interrupts.
 */

void S2I_EnableInterrupt ( S2I_ModuleType ModuleId, S2I_InterruptType InterruptID ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function just like S2I_EnableInterrupt but it disable the interrupt.
 */

void S2I_DisableInterrupt ( S2I_ModuleType ModuleId, S2I_InterruptType InterruptID ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will return (interrupt event flag & interrupt enable state) .
 * interrupt determined by InterruptID of SSI module determined by ModuleId.
 * if interrupt is disable interrupt state returned from this function will be always FASLE.
 * refer to S2I_InterruptType to get more information about SSI interrupts.
 */

boolean S2I_GetInterruptState ( S2I_ModuleType ModuleId, S2I_InterruptType InterruptID ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will return interrupt event flag state.
 * interrupt determined by InterruptID of SSI module determined by ModuleId.
 * interrupt enable/disable won't effect set/clear of event status get by S2I_GetEventState.
 * if event flag is set and interrupt enabled, Interrupt request will be sent to NVIC so,
 * before enable interrupt clear its event flag.
 * refer to S2I_InterruptType to get more information about SSI interrupts.
 */

boolean S2I_GetEventState ( S2I_ModuleType ModuleId, S2I_InterruptType InterruptID ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will clear edge interrupt Event state, it has no effect on Level interrupt
 * SSI module determined by ModuleId and Interrupt determined by InterruptID.
 * if event flag is set and interrupt enabled, Interrupt request will be sent to NVIC so,
 * before enable interrupt clear its event flag.
 * refer to S2I_InterruptType to get more information about SSI interrupts.
 */

void S2I_ClearEvent ( S2I_ModuleType ModuleId, S2I_InterruptType InterruptID ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will enable/disable DMA feature for Tx/Rx buffer.
 * SSI module determined by ModuleId and buffer determined by BufferId.
 * if argument Enable = TRUE then DMA enable is future, if = FALSE then DMA feature is disabled.
 * refer to DMA module to get more information about this future.
 */

void S2I_DmaEnable ( S2I_ModuleType ModuleId, S2I_BufferType BufferId, boolean Enable ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will set clock source of SSI module determined by ModuleId
 * refer to S2I_ClockType to get mor information about clock sources
 */

void S2I_Clock ( S2I_ModuleType ModuleId, S2I_ClockType  ClockId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will set ISR callback function of SSI module determined by ModuleId.
 * in ISR user must handle clear edge interrupt event flags that caused interrupt,
 * or CPU will re-enter interrupt after finish it.
 * if DMA feature is enable, DMA transfer complete will trigger SSI module ISR,
 * user must handle this too.
 */

void S2I_AssignISR ( S2I_ModuleType ModuleId ,void (*FuncPtr) (void) ) ;


/*********************************************************************************/


#endif /* S2I_H_ */





