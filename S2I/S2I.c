/************************************************/
/*  S2I.c                                       */
/*  Created on: Sep 20, 2020                    */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/



#include "S2I.h"
#include "S2I_Private.h"


/*********************************************************************************/

/* used to hold pointers to call back functions that called inside ISRs */

void ( * S2I_IsrPtr_Arr [S2I_ISR_NUMBER] ) (void) = {NULL_PTR} ;


/*********************************************************************************/

/*
 * non privilege, synchronous, non-Reentrant function .
 * this function will initialize all SPI modules, according to S2I_Cfg.h file.
 * it will initialize clock, interrupt mask, SSI and SPI modes, DMA feature enable.
 * follow rules demonstrated in S2I_Cfg.h file to make proper initialization .
 */

void S2I_Init(void)

{
    S2I_RegisterMap_Struct * RegisterBase = NULL_PTR ;

    /*********************************************************************************/

    RegisterBase = S2I_MODULE_0_BASE ;

    CLR_BIT( (S2I_MODULE_0_BASE)->S2I_SSICR1_REG, S2I_ENABLE_BIT_POS ) ;
    RegisterBase->S2I_SSIIM_REG = FALSE;

    *S2I_MODULE_0_SSICC_REG = S2I_MOD_0_CLOCK_SOURCE ;
    RegisterBase->S2I_SSICR0_REG = (S2I_MOD_0_DIVISON_FACTOR<<S2I_SCR_FIELD_OFFSET) | (S2I_MOD_0_SPI_MODE<<S2I_SPI_FIELD_OFFSET) | (S2I_MOD_0_FRAME_TYPE<<S2I_FRAME_FIELD_OFFSET) | (S2I_MOD_0_FRAME_WIDTH) ;
    RegisterBase->S2I_SSICR1_REG = (S2I_MOD_0_EMPTY_TX_INT<<S2I_EOT_BIT_POS) | (S2I_MOD_0_DIS_MASTER<<S2I_MASTER_BIT_POS) | (S2I_MOD_0_LOOP_BACK) ;
    RegisterBase->S2I_SSICPSR_REG = S2I_MOD_0_PRESCALER ;
    RegisterBase->S2I_SSIDMACTL_REG = S2I_MOD_0_EN_DMA;
    RegisterBase->S2I_SSIICR_REG = S2I_INTERRUPT_CLR_MASK;
    RegisterBase->S2I_SSIIM_REG = S2I_MOD_0_EN_INTERRUPT;

    /*********************************************************************************/

    RegisterBase = S2I_MODULE_1_BASE ;

    CLR_BIT( (S2I_MODULE_1_BASE)->S2I_SSICR1_REG, S2I_ENABLE_BIT_POS ) ;
    RegisterBase->S2I_SSIIM_REG = FALSE;

    *S2I_MODULE_1_SSICC_REG = S2I_MOD_1_CLOCK_SOURCE ;
    RegisterBase->S2I_SSICR0_REG = (S2I_MOD_1_DIVISON_FACTOR<<S2I_SCR_FIELD_OFFSET) | (S2I_MOD_1_SPI_MODE<<S2I_SPI_FIELD_OFFSET) | (S2I_MOD_1_FRAME_TYPE<<S2I_FRAME_FIELD_OFFSET) | (S2I_MOD_1_FRAME_WIDTH) ;
    RegisterBase->S2I_SSICR1_REG = (S2I_MOD_1_EMPTY_TX_INT<<S2I_EOT_BIT_POS) | (S2I_MOD_1_DIS_MASTER<<S2I_MASTER_BIT_POS) | (S2I_MOD_1_LOOP_BACK) ;
    RegisterBase->S2I_SSICPSR_REG = S2I_MOD_1_PRESCALER ;
    RegisterBase->S2I_SSIDMACTL_REG = S2I_MOD_1_EN_DMA;
    RegisterBase->S2I_SSIICR_REG = S2I_INTERRUPT_CLR_MASK;
    RegisterBase->S2I_SSIIM_REG = S2I_MOD_1_EN_INTERRUPT;

    /*********************************************************************************/

    RegisterBase = S2I_MODULE_2_BASE ;

    CLR_BIT( (S2I_MODULE_2_BASE)->S2I_SSICR1_REG, S2I_ENABLE_BIT_POS ) ;
    RegisterBase->S2I_SSIIM_REG = FALSE;

    *S2I_MODULE_2_SSICC_REG = S2I_MOD_2_CLOCK_SOURCE ;
    RegisterBase->S2I_SSICR0_REG = (S2I_MOD_2_DIVISON_FACTOR<<S2I_SCR_FIELD_OFFSET) | (S2I_MOD_2_SPI_MODE<<S2I_SPI_FIELD_OFFSET) | (S2I_MOD_2_FRAME_TYPE<<S2I_FRAME_FIELD_OFFSET) | (S2I_MOD_2_FRAME_WIDTH) ;
    RegisterBase->S2I_SSICR1_REG = (S2I_MOD_2_EMPTY_TX_INT<<S2I_EOT_BIT_POS) | (S2I_MOD_2_DIS_MASTER<<S2I_MASTER_BIT_POS) | (S2I_MOD_2_LOOP_BACK) ;
    RegisterBase->S2I_SSICPSR_REG = S2I_MOD_2_PRESCALER ;
    RegisterBase->S2I_SSIDMACTL_REG = S2I_MOD_2_EN_DMA;
    RegisterBase->S2I_SSIICR_REG = S2I_INTERRUPT_CLR_MASK;
    RegisterBase->S2I_SSIIM_REG = S2I_MOD_2_EN_INTERRUPT;

    /*********************************************************************************/

    RegisterBase = S2I_MODULE_3_BASE ;

    CLR_BIT( (S2I_MODULE_3_BASE)->S2I_SSICR1_REG, S2I_ENABLE_BIT_POS ) ;
    RegisterBase->S2I_SSIIM_REG = FALSE;

    *S2I_MODULE_3_SSICC_REG = S2I_MOD_3_CLOCK_SOURCE ;
    RegisterBase->S2I_SSICR0_REG = (S2I_MOD_3_DIVISON_FACTOR<<S2I_SCR_FIELD_OFFSET) | (S2I_MOD_3_SPI_MODE<<S2I_SPI_FIELD_OFFSET) | (S2I_MOD_3_FRAME_TYPE<<S2I_FRAME_FIELD_OFFSET) | (S2I_MOD_3_FRAME_WIDTH) ;
    RegisterBase->S2I_SSICR1_REG = (S2I_MOD_3_EMPTY_TX_INT<<S2I_EOT_BIT_POS) | (S2I_MOD_3_DIS_MASTER<<S2I_MASTER_BIT_POS) | (S2I_MOD_3_LOOP_BACK) ;
    RegisterBase->S2I_SSICPSR_REG = S2I_MOD_3_PRESCALER ;
    RegisterBase->S2I_SSIDMACTL_REG = S2I_MOD_3_EN_DMA;
    RegisterBase->S2I_SSIICR_REG = S2I_INTERRUPT_CLR_MASK;
    RegisterBase->S2I_SSIIM_REG = S2I_MOD_3_EN_INTERRUPT;

    /*********************************************************************************/

    return ;
}


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

void S2I_SetClock( S2I_ModuleType ModuleId, uint8 Divide, uint8 Prescaler)
{
    uint32 Temp = ( (S2I_MODULE_0_BASE + ModuleId*S2I_MODULE_OFFSET_1 )->S2I_SSICR0_REG & S2I_SCR_FIELD_MASK ) | (Prescaler << S2I_SCR_FIELD_OFFSET) ;


    (S2I_MODULE_0_BASE + ModuleId*S2I_MODULE_OFFSET_1 )->S2I_SSICR0_REG = Temp ;
    (S2I_MODULE_0_BASE + ModuleId*S2I_MODULE_OFFSET_1 )->S2I_SSICPSR_REG = Prescaler ;


    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will set the mode (Mode) of SPI format of SSI module determined by ModuleId.
 * refer to S2I_SpiModeType to get information about SPI modes
 * don't call this function except when transfer is disabled for ModuleId ( use S2I_TransferStop ).
 */

void S2I_SpiMode( S2I_ModuleType ModuleId, S2I_SpiModeType Mode )
{
    uint32 Temp = ( (S2I_MODULE_0_BASE + ModuleId*S2I_MODULE_OFFSET_1 )->S2I_SSICR0_REG & S2I_SPI_FIELD_MASK ) | (Mode << S2I_SPI_FIELD_OFFSET) ;

    (S2I_MODULE_0_BASE + ModuleId*S2I_MODULE_OFFSET_1 )->S2I_SSICR0_REG = Temp ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will set the format (Frame) of SSI module determined by ModuleId.
 * refer to S2I_FrameType to get information about SSI frame formats
 * don't call this function except when transfer is disabled for ModuleId ( use S2I_TransferStop ).
 */

void S2I_SetFrame ( S2I_ModuleType ModuleId, S2I_FrameType Frame )
{
    uint32 Temp = ( (S2I_MODULE_0_BASE + ModuleId*S2I_MODULE_OFFSET_1 )->S2I_SSICR0_REG & S2I_FRAME_FIELD_MASK ) | (Frame << S2I_FRAME_FIELD_OFFSET) ;

    (S2I_MODULE_0_BASE + ModuleId*S2I_MODULE_OFFSET_1 )->S2I_SSICR0_REG = Temp ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will set the frame width SSI module determined by ModuleId.
 * frame width determined by (Width+1) Width argument must by in range 3~15 bit
 * don't call this function except when transfer is disabled for ModuleId ( use S2I_TransferStop ).
 */

void S2I_FrameWidth ( S2I_ModuleType ModuleId, uint8 Width )
{
    uint32 Temp = ( (S2I_MODULE_0_BASE + ModuleId*S2I_MODULE_OFFSET_1 )->S2I_SSICR0_REG & S2I_WIDTH_FIELD_MASK ) | Width ;

    (S2I_MODULE_0_BASE + ModuleId*S2I_MODULE_OFFSET_1 )->S2I_SSICR0_REG = Temp ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function select mode of SSI module determined by ModuleId as a master/slave .
 * if Disable argument = FALSE, slave if = TRUE.
 * don't call this function except when transfer is disabled for ModuleId ( use S2I_TransferStop ).
 */

void S2I_MasterDisable ( S2I_ModuleType ModuleId, boolean Disable )
{

    ASSIGN_BIT( (S2I_MODULE_0_BASE + ModuleId*S2I_MODULE_OFFSET_1 )->S2I_SSICR1_REG, S2I_ENABLE_BIT_POS, Disable ) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function start (enable) date send/receive of SSI module determined by ModuleId as a master/slave .
 * don't call this function except when transfer is disabled for ModuleId ( use S2I_TransferStop ).
 */

void S2I_TransferStart ( S2I_ModuleType ModuleId )
{
    SET_BIT( (S2I_MODULE_0_BASE + ModuleId*S2I_MODULE_OFFSET_1 )->S2I_SSICR1_REG, S2I_ENABLE_BIT_POS ) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function stop (disable) data send/receive of SSI module determined by ModuleId as a master/slave .
 * don't call this function except when transfer is disabled for ModuleId ( use S2I_TransferStop ).
 */

void S2I_TransferStop ( S2I_ModuleType ModuleId )
{

    CLR_BIT( (S2I_MODULE_0_BASE + ModuleId*S2I_MODULE_OFFSET_1 )->S2I_SSICR1_REG, S2I_ENABLE_BIT_POS ) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function enable/disable Loopback feature which is used in testing for module determined by ModuleId.
 * if Enable = TRUE then data is send form Tx buffer internally to Rx buffer
 * don't call this function except when transfer is disabled for ModuleId ( use S2I_TransferStop ).
 */

void S2I_LoopbackEnable ( S2I_ModuleType ModuleId, boolean Enable )
{

    ASSIGN_BIT( (S2I_MODULE_0_BASE + ModuleId*S2I_MODULE_OFFSET_1 )->S2I_SSICR1_REG, S2I_LBM_BIT_POS, Enable ) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will return state of SSI module determined by ModuleId.
 * if return is = TRUE then module is currently busy in transmission/receiving data.
 */

boolean S2I_ModuleBusy ( S2I_ModuleType ModuleId )
{

    return GET_BIT( (S2I_MODULE_0_BASE + ModuleId*S2I_MODULE_OFFSET_1 )->S2I_SSISR_REG, S2I_BSY_BIT_POS ) ;
}

/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will return buffer state (determined  by BufferId) of SSI module determined by ModuleId.
 * refer to S2I_BufferStateType to get more information about different states of buffer
 */

S2I_BufferStateType S2I_BufferState ( S2I_ModuleType ModuleId, S2I_BufferType BufferId)
{
    S2I_BufferStateType ReturnResult = (S2I_MODULE_0_BASE + ModuleId*S2I_MODULE_OFFSET_1 )->S2I_SSISR_REG ;
    ReturnResult >>= (BufferId + BufferId) ;
    ReturnResult ^= BufferId * 2 ;
    return ReturnResult & S2I_BUFFER_STATE_MASK ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will make event condition of S2I_TRANSMIT_EXCEED trigger when Tx buffer is fully empty.
 * module is determined by ModuleId, if Enable argument = TRUE then,
 * event will trigger when buffer is empty, if = FALSE then S2I_TRANSMIT_EXCEED trigger as usual.
 */

void S2I_TxBuffer_EmptyInterrupt ( S2I_ModuleType ModuleId, boolean Enable)
{
    ASSIGN_BIT( (S2I_MODULE_0_BASE + ModuleId*S2I_MODULE_OFFSET_1 )->S2I_SSICR1_REG, S2I_EOT_BIT_POS, Enable ) ;
    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will Enable interrupt determined by InterruptID of SSI module determined by ModuleId.
 * interrupt enable/disable won't effect set/clear of event status get by S2I_GetEventState.
 * if event flag is set and interrupt enabled, Interrupt request will be sent to NVIC so,
 * before enable interrupt clear its event flag.
 * refer to S2I_InterruptType to get more information about SSI interrupts.
 */

void S2I_EnableInterrupt ( S2I_ModuleType ModuleId, S2I_InterruptType InterruptID )
{
   SET_BIT( (S2I_MODULE_0_BASE + ModuleId*S2I_MODULE_OFFSET_1 )->S2I_SSIIM_REG, InterruptID) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function just like S2I_EnableInterrupt but it disable the interrupt.
 */

void S2I_DisableInterrupt ( S2I_ModuleType ModuleId, S2I_InterruptType InterruptID )
{
    CLR_BIT( (S2I_MODULE_0_BASE + ModuleId*S2I_MODULE_OFFSET_1 )->S2I_SSIIM_REG, InterruptID) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will return (interrupt event flag & interrupt enable state) .
 * interrupt determined by InterruptID of SSI module determined by ModuleId.
 * if interrupt is disable interrupt state returned from this function will be always FASLE.
 * refer to S2I_InterruptType to get more information about SSI interrupts.
 */

boolean S2I_GetInterruptState ( S2I_ModuleType ModuleId, S2I_InterruptType InterruptID )
{
    return  GET_BIT( (S2I_MODULE_0_BASE + ModuleId*S2I_MODULE_OFFSET_1 )->S2I_SSIMIS_REG, InterruptID) ; ;
}


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

boolean S2I_GetEventState ( S2I_ModuleType ModuleId, S2I_InterruptType InterruptID )
{
    return  GET_BIT( (S2I_MODULE_0_BASE + ModuleId*S2I_MODULE_OFFSET_1 )->S2I_SSIRIS_REG, InterruptID) ; ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will clear edge interrupt Event state, it has no effect on Level interrupt
 * SSI module determined by ModuleId and Interrupt determined by InterruptID.
 * if event flag is set and interrupt enabled, Interrupt request will be sent to NVIC so,
 * before enable interrupt clear its event flag.
 * refer to S2I_InterruptType to get more information about SSI interrupts.
 */

void S2I_ClearEvent ( S2I_ModuleType ModuleId, S2I_InterruptType InterruptID )
{
    SET_BIT( (S2I_MODULE_0_BASE + ModuleId*S2I_MODULE_OFFSET_1 )->S2I_SSIICR_REG, InterruptID) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will enable/disable DMA feature for Tx/Rx buffer.
 * SSI module determined by ModuleId and buffer determined by BufferId.
 * if argument Enable = TRUE then DMA enable is future, if = FALSE then DMA feature is disabled.
 * refer to DMA module to get more information about this future.
 */

void S2I_DmaEnable ( S2I_ModuleType ModuleId, S2I_BufferType BufferId, boolean Enable )
{
    ASSIGN_BIT( (S2I_MODULE_0_BASE + ModuleId*S2I_MODULE_OFFSET_1 )->S2I_SSIDMACTL_REG, BufferId, Enable ) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will set clock source of SSI module determined by ModuleId
 * refer to S2I_ClockType to get mor information about clock sources
 */

void S2I_Clock ( S2I_ModuleType ModuleId, S2I_ClockType  ClockId )
{
    *( S2I_MODULE_0_SSICC_REG + ModuleId*S2I_MODULE_OFFSET_2 ) = ClockId ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function.
 * this function will set ISR callback function of SSI module determined by ModuleId.
 * in ISR user must handle clear edge interrupt event flags that caused interrupt,
 * or CPU will re-enter interrupt after finish it.
 * if DMA feature is enable, DMA transfer complete will trigger SSI module ISR,
 * user must handle this too.
 */

void S2I_AssignISR ( S2I_ModuleType ModuleId ,void (*FuncPtr) (void) )
{
    S2I_IsrPtr_Arr[ModuleId] = FuncPtr ;
    return ;
}


/*********************************************************************************/

/* SSI0 module ISR */

void S2I_Module0_ISR ( void )
{
    (S2I_IsrPtr_Arr[S2I_MODULE_0]) () ;

    return ;
}


/*********************************************************************************/

/* SSI1 module ISR */

void S2I_Module1_ISR ( void )
{
    (S2I_IsrPtr_Arr[S2I_MODULE_1]) () ;

    return ;
}


/*********************************************************************************/

/* SSI2 module ISR */

void S2I_Module2_ISR ( void )
{
    (S2I_IsrPtr_Arr[S2I_MODULE_2]) () ;

    return ;
}


/*********************************************************************************/

/* SSI3 module ISR */

void S2I_Module3_ISR ( void )
{
    (S2I_IsrPtr_Arr[S2I_MODULE_3]) () ;

    return ;
}


/*********************************************************************************/




