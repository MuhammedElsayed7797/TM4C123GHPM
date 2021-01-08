/************************************************/
/*  main.c                                      */
/*  Created on: Sep 1, 2020                     */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/

#include "../SysTick/SysTick.h"
#include "../Nvic/Nvic.h"
#include "../Port/Port.h"
#include "../Dio/Dio.h"
#include "../ExtInt/ExtInt.h"
#include "../S2I/S2I.h"
#include "../Adc/Adc.h"




/*********************************************************************************/



#define NVIC_TEST_INTERRUPT_ID  10
boolean Nvic_Test_1 = TRUE ;

/*********************************************************************************/


void SysTick_IsrTest (void) ;
boolean SysTick_TestFlag = TRUE ;


/*********************************************************************************/

uint16 Spi_ReceiveBuffer [8] = {0} ;
uint8 counter = 0 ;
uint16 * SSI_Prtr = Spi_ReceiveBuffer ;

/*********************************************************************************/

boolean Adc_Temp1 = TRUE ;
uint8 Adc_Temp2 = 0xFF ;
Adc_ModuleType ModuleId = ADC_MODULE_1 ;
Adc_SequencerType SequencerId = ADC_SEQUENCER_0 ;
Adc_InterruptType InterruptID = ADC_SEQUENCER_0_INT ;
Adc_TriggerSourceType SourceId = ADC_TRIGGER_PROCESSOR;
Adc_PwmGenratorType GeneratorId = ADC_PWM_GENERATOR_0 ;
Adc_PwmModuleType PwmId = ADC_PWM_MODULE_0 ;
uint8 Priority = 3 ;
Adc_SamplePhaseType Phase = ADC_SAMPLE_PHASE_0 ;
uint8 SequencersMask = 0x1;
uint8 FactorPower = 0 ;
Adc_DCompType DCompId = ADC_DIGITAL_COMP_0;
uint8 Mask = 0x01 ;
boolean Enable = FALSE ;
Adc_SampleType SampleId = ADC_SAMPLE_0 ;
Adc_ChannelType ChannelId = ADC_CHANNEL_0 ;
Adc_ResultType DataPtr [8] ;
uint8 SamplesNumber = 8 ;
boolean Compare = TRUE ;
Adc_DCompModeType Mode  = ADC_DCOMP_ALWAYS ;
Adc_DCompCondTyp Condition = ADC_DCOMP_LOW_BAND ;
uint16 LowerValue = 0x444 , UpperValue = 0xBBB;
Adc_SampleRateType Rate = ADC_SAMPLE_RATE_125K ;
Adc_ClkSourceType Source = ADC_CLK_SOURCE_SYS ;


/*********************************************************************************/


int main (void)
{

    /*********************************************************************************/

    * ( ( volatile unsigned long * ) ( 0x400FE000 + 0x61C ) ) |= (0xF<<0) ;     /* enable SSI clock */
    * ( ( volatile unsigned long * ) ( 0x400FE000 + 0x608 ) ) |= 0x3F ;         /* enable clock for all ports */
    * ( ( volatile unsigned long * ) ( 0x400FE000 + 0x06C ) ) |= (1<<0) ;       /* enable AHB for port A */
    * ( ( volatile unsigned long * ) ( 0x400FE000 + 0x06C ) ) |= (1<<5) ;       /* enable AHB for port F */
    * ( ( volatile unsigned long * ) ( 0x400FE000 + 0x638 ) ) |= (0x3<<0) ;     /* enable ADC clock */


    Nvic_Init() ;
    Port_Init(0x3F) ;
    ExtInt_Init(0x3F) ;
    S2I_Init(0xF) ;
    Adc_Init(0x3) ;




    Dio_FlipPin(DIO_PIN39) ;

    while (1) ;

}





void Nvic_Test (void)
{

    CS_ON ;

    Nvic_Init() ;
    Nvic_SetPriority (NVIC_TEST_INTERRUPT_ID, 7) ;
    Nvic_EnableInterrupt (NVIC_TEST_INTERRUPT_ID) ;
    Nvic_DisableInterrupt (NVIC_TEST_INTERRUPT_ID) ;
    Nvic_SetPendingFlag (NVIC_TEST_INTERRUPT_ID) ;
    Nvic_ClearPendingFlag (NVIC_TEST_INTERRUPT_ID) ;
    Nvic_Test_1 = Nvic_GetEnable (NVIC_TEST_INTERRUPT_ID) ;
    Nvic_Test_1 = Nvic_GetPendingFlag (NVIC_TEST_INTERRUPT_ID) ;
    Nvic_Test_1 = Nvic_GetPendingFlag (NVIC_TEST_INTERRUPT_ID) ;

    return ;

}


void SysTick_Test (void)
{

    SysTick_EnableInterrupt () ;
    SysTick_SelectClock ( FALSE ) ;
    SysTick_ClearTimer () ;
    SysTick_PeriodicNotification ( 3999999, 0, SysTick_IsrTest ) ;
    SysTick_StartTimer () ;


    return ;
}

void SysTick_IsrTest (void)
{

    Dio_FlipPin(DIO_PIN39) ;

    /*
    if ( SysTick_TestFlag )
    {
        SysTick_TestFlag = FALSE ;
        SysTick_PeriodicNotification ( 3999999, 0, SysTick_IsrTest ) ;

    }
    */
    return ;
}

void Dio_Test (void)
{

    Dio_WritePin(DIO_PIN39, DIO_HIGH) ;
    Dio_WritePin(DIO_PIN40, DIO_HIGH) ;
    Dio_WritePin(DIO_PIN41, DIO_HIGH) ;

    return ;
}

void S2I_Test (void)
{


    /* write transmit buffer */
    S2I_Buffer(S2I_MODULE_0) = (1) ;
    S2I_Buffer(S2I_MODULE_0) = (2) ;
    S2I_Buffer(S2I_MODULE_0) = (3) ;
    S2I_Buffer(S2I_MODULE_0) = (4) ;
    S2I_Buffer(S2I_MODULE_0) = (5) ;
    S2I_Buffer(S2I_MODULE_0) = (6) ;
    S2I_Buffer(S2I_MODULE_0) = (7) ;
    S2I_Buffer(S2I_MODULE_0) = (8) ;


    S2I_TransferStart(S2I_MODULE_0) ;
    while(S2I_ModuleBusy(S2I_MODULE_0)) ;      /* wait for Idle SSI0 */
    S2I_TransferStop (S2I_MODULE_0) ;

    /* read SSI receive buffer*/
    for( counter = 0 ; counter < 8 ; counter ++)
    {
        SSI_Prtr[counter] =  S2I_Buffer(S2I_MODULE_0) ;
    }


    S2I_Buffer(S2I_MODULE_0) = (9) ;
    S2I_Buffer(S2I_MODULE_0) = (10) ;
    S2I_Buffer(S2I_MODULE_0) = (11) ;
    S2I_Buffer(S2I_MODULE_0) = (12) ;
    S2I_Buffer(S2I_MODULE_0) = (13) ;
    S2I_Buffer(S2I_MODULE_0) = (14) ;
    S2I_Buffer(S2I_MODULE_0) = (15) ;
    S2I_Buffer(S2I_MODULE_0) = (16) ;

    S2I_TransferStart(S2I_MODULE_0) ;
    while(S2I_ModuleBusy(S2I_MODULE_0)) ;      /* wait for Idle SSI0 */
    S2I_TransferStop(S2I_MODULE_0) ;

    /* read SSI receive buffer*/
    for( counter = 0 ; counter < 8 ; counter ++)
    {
        SSI_Prtr[counter] =  S2I_Buffer(S2I_MODULE_0) ;
    }

    return ;
}


void Adc_Test (void)
{

    Adc_Temp1 = Adc_BusyState ( ModuleId ) ;
    Adc_SequencerDisable ( ModuleId, SequencerId) ;
    Adc_SequencerEnable ( ModuleId, SequencerId) ;
    Adc_Temp1 = Adc_GetSequencerEvent ( ModuleId, InterruptID ) ;
    Adc_Temp2 = Adc_GetAllSequencerEvents ( ModuleId) ;
    Adc_Temp1 = Adc_GetSequencerInterrupt ( ModuleId, InterruptID ) ;
    Adc_Temp2 = Adc_GetAllSequencerInterrupts ( ModuleId) ;
    Adc_ClearSequencerEvent ( ModuleId, InterruptID ) ;
    Adc_ClearAllSequencerEvents (  ModuleId ) ;
    Adc_DisableSequencerInterrupt ( ModuleId, InterruptID ) ;
    Adc_EnableSequencerInterrupt ( ModuleId, InterruptID ) ;
    Adc_Temp1 = Adc_GetOVState ( ModuleId, SequencerId) ;
    Adc_Temp1 = Adc_GetUVState ( ModuleId, SequencerId) ;
    Adc_Temp2 = Adc_GetAllOVStates ( ModuleId ) ;
    Adc_Temp2 = Adc_GetAllUVStates ( ModuleId ) ;
    Adc_ClearOVState ( ModuleId, SequencerId ) ;
    Adc_ClearUVState ( ModuleId, SequencerId ) ;
    Adc_ClearAllOVStates ( ModuleId ) ;
    Adc_ClearAllUVStates ( ModuleId ) ;
    Adc_TriggerSource ( ModuleId, SequencerId, SourceId) ;
    Adc_SelectPwmModule ( ModuleId, GeneratorId , PwmId ) ;
    Adc_SequencerPriority ( ModuleId, SequencerId, Priority) ;
    Adc_SetSamplePhase ( ModuleId, Phase ) ;
    Adc_InitiateSequencers ( ModuleId, SequencersMask ) ;
    Adc_AveragingFactor ( ModuleId, FactorPower ) ;
    Adc_DComp_SecletIntLine ( ModuleId, InterruptID ) ;
    Adc_DComp_DeselectIntLine ( ModuleId, InterruptID ) ;
    Adc_Temp1 = Adc_DComp_GetEventState ( ModuleId, DCompId ) ;
    Adc_Temp2 = Adc_DComp_GetEventStateAll ( ModuleId ) ;
    Adc_DComp_EventClr (ModuleId, DCompId ) ;
    Adc_DComp_EventClrAll (ModuleId, Mask  ) ;
    Adc_DitherControl ( ModuleId, Enable) ;
    Adc_SelectInputChannel ( ModuleId, SequencerId, SampleId, ChannelId) ;
    Adc_Sample_TempSensorCtrl ( ModuleId, SequencerId, SampleId, Enable ) ;
    Adc_Sample_EventCtrl ( ModuleId, SequencerId, SampleId, Enable ) ;
    Adc_Sample_EndCtrl ( ModuleId, SequencerId, SampleId, Enable ) ;
    Adc_Sample_DifferentialCtrl ( ModuleId, SequencerId, SampleId, Enable ) ;
    Adc_MultiResultRead ( ModuleId, SequencerId, DataPtr, SamplesNumber  ) ;
    Adc_Temp1 = Adc_CheckEmptyBuffer (ModuleId, SequencerId) ;
    Adc_Temp1 = Adc_CheckFullBuffer (ModuleId, SequencerId) ;
    Adc_Temp2 = Adc_GetBufferHead (ModuleId, SequencerId) ;
    Adc_Temp2 = Adc_GetBufferTail (ModuleId, SequencerId) ;
    Adc_SampleDestinationCtrl ( ModuleId, SequencerId, SampleId, Compare ) ;
    Adc_SampleDCompSelect( ModuleId, SequencerId, SampleId, DCompId ) ;
    Adc_DComp_TrigCtrl ( ModuleId, DCompId, Enable ) ;
    Adc_DComp_TrigCond ( ModuleId, DCompId, Condition ) ;
    Adc_DComp_TrigMode ( ModuleId, DCompId, Mode ) ;
    Adc_DComp_EventCtrl ( ModuleId, DCompId, Enable ) ;
    Adc_DComp_EvnetCond ( ModuleId, DCompId, Condition ) ;
    Adc_DComp_EvnetMode ( ModuleId, DCompId, Mode ) ;
    Adc_DComp_ResetInterrupt (  ModuleId, DCompId+1 ) ;
    Adc_DComp_ResetTrigger (  ModuleId, DCompId+1 ) ;
    Adc_DComp_Range ( ModuleId, DCompId, UpperValue, LowerValue ) ;
    Adc_SetSampleRate ( ModuleId, Rate ) ;
    Adc_SetClockSource ( ModuleId, Source ) ;
}


