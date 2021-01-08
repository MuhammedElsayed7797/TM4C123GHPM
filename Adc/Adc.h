/************************************************/
/*  Adc.h                                       */
/*  Created on: Dec 22, 2020                    */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/


#ifndef ADC_H_
#define ADC_H_


#include "../Common/Utils.h"
#include "Adc_Cfg.h"



/*********************************************************************************/

#define ADC_MOD_0_BUFFER_ADD    0x40038048
#define ADC_MODULE_OFFSET       0x400
#define ADC_SEQ_OFFSET          0x8

/*********************************************************************************/

/*
 * use this macros as a value for variable of Adc_ModuleType
 * this type indicate ADC module referenced by the functions
 */

/* for ADC module 0 */
#define ADC_MODULE_0    0x00

/* for ADC module 1 */
#define ADC_MODULE_1    0x01

typedef uint8 Adc_ModuleType ;


/*********************************************************************************/

/*
 * sample sequencers represent the unit of sampling in every ADC module .
 * every sequencers has specific number of entries .
 * every entry represent a sample and contain sample source, setting and destination .
 * sample destination could by storing inside sequencer which has depth as number of entries,
 * or could be pointed to digital comparator to process sample value according to its setting .
 * to start sampling software much use a sample sequencer ,
 * and set its entries setting to sample according to it .
 */

/*
 * use this macros as a value for variable of Adc_SequencerType
 * this type indicate sample sequencers inside every module
 */

/* for sample sequencer 0 whit 8 entries */
#define ADC_SEQUENCER_0       0x00

/* for sample sequencer 1 whit 4 entries */
#define ADC_SEQUENCER_1       0x01

/* for sample sequencer 2 whit 4 entries */
#define ADC_SEQUENCER_2       0x02

/* for sample sequencer 3 whit 1 entry */
#define ADC_SEQUENCER_3       0x03

typedef uint8 Adc_SequencerType ;


/*********************************************************************************/
/*
 * every ADC module has 4 interrupt lines connected to NVIC which mean 4 location (ISR) in vector table .
 * there's interrupt line for every sample sequencer with 4 sequencer for every module .
 * sample inside sequencer have an event, and all samples events is combined together,
 * to produce sequencer event which is sent through sequencer interrupt line to NVIC .
 */

/*
 * there's 8 digital comparators in every module, each one has its event .
 * all comparators event is combined together to produce one event for digital comparators,
 * which this event could be sent to NVIC through one sequencer interrupt line (choose one by Adc_EnableSequencerInterrupts) .
 * just one line must be enabled for digital comparators event, if more then all event are masked by hardware.
 */

/*
 * use this macros as a value for variable of Adc_InterruptType
 * this type indicate event/interrupts of every module
 */

/* for sample sequencer 0 interrupt/event */
#define ADC_SEQUENCER_0_INT     0x00

/* for sample sequencer 1 interrupt/event */
#define ADC_SEQUENCER_1_INT     0x01

/* for sample sequencer 2 interrupt/event */
#define ADC_SEQUENCER_2_INT     0x02

/* for sample sequencer 3 interrupt/event */
#define ADC_SEQUENCER_3_INT     0x03

typedef uint8 Adc_InterruptType ;

/*********************************************************************************/

/*
 * for every sequencer there's many sources of triggers that would trigger sequencer to start sampling .
 * this triggers could be from another peripherals or from processor(software) .
 * when sequencer is triggered then it will start sampling unless another sequencer is in operation .
 * if two or more sequencers triggered at same time they will queued according to their priority .
 */

/* use this macros as a values for variables from Adc_TriggerSourceType */

/* triggered by software by using Adc_StartSequencers function */
#define ADC_TRIGGER_PROCESSOR   0x00

/* trigger by analog comparator module 0 */
#define ADC_TRIGGER_ACOMP_0     0x01

/* trigger by analog comparator module 1 */
#define ADC_TRIGGER_ACOMP_1     0x02

/* trigger by analog comparator module 0 */
#define ADC_TRIGGER_GPIO        0x04

/* trigger by general purpose time module */
#define ADC_TRIGGER_TIMER       0x05

/* trigger by PWM generator 0  */
#define ADC_TRIGGER_PWM_0       0x06

/* trigger by PWM generator 1  */
#define ADC_TRIGGER_PWM_1       0x07

/* trigger by PWM generator 2  */
#define ADC_TRIGGER_PWM_2       0x08

/* trigger by PWM generator 3  */
#define ADC_TRIGGER_PWM_3       0x09

/* always mode will continuously start sampling again after it finish all samples according to its setting */
#define ADC_TRIGGER_ALWAYS      0x0F

typedef uint8 Adc_TriggerSourceType ;


/*********************************************************************************/

/*
 * there's 2 PWM modules each with four PWM generators ,
 * every generator could generate a trigger signal and be trigger source for ADC modules
 * this type to identify this generator
 */

/* use this macros as a values for variables from Adc_PwmGenratorType */

/* define PWM generator 0 */
#define ADC_PWM_GENERATOR_0     0x04

/* define PWM generator 1 */
#define ADC_PWM_GENERATOR_1     0x0C

/* define PWM generator 2 */
#define ADC_PWM_GENERATOR_2     0x14

/* define PWM generator 3 */
#define ADC_PWM_GENERATOR_3     0x1C

typedef uint8 Adc_PwmGenratorType ;


/*********************************************************************************/

/*
 * use this macros as a values for variables from Adc_PwmModuleType
 * this type indicate PWM module referenced by the functions
 */

/* define PWM module 0 */
#define ADC_PWM_MODULE_0    0x00

/* define PWM module 1 */
#define ADC_PWM_MODULE_1    0x01

typedef uint8 Adc_PwmModuleType ;


/*********************************************************************************/

/*
 * use this macros as a values for variables from Adc_SamplePhaseType
 * this type indicate phases referenced by functions
 */

/*
 * for ADC module sample rate, period between every sampling signal divided into 16 clock cycle,
 * with max sample rate 1Msps and 16MHz clock .
 * sampling could be delayed from trigger event occur by certain clock cycles,
 * according to ADC module phase .
 * for example if sample rate is 1Msps (period 1us) and ADC0 phase is 180 degree
 * then sampling start by 1/2 us after trigger event occur
 */

/*
 * this method could be used to double sampling rate by using 2 ADC modules with sampling rate
 * on of them is out of phase by 180 with another and make them sample same input
 * with same trigger source then combine their sample results to get a double sample rate
 */

/* for phase 0 sampling start once trigger event occur */
#define ADC_SAMPLE_PHASE_0          0x00

/* for phase 0 sampling start after 1/16 of period of sampling clock from trigger event occur */
#define ADC_SAMPLE_PHASE_22_5       0x01

/* for phase 0 sampling start after 2/16 of period of sampling clock from trigger event occur */
#define ADC_SAMPLE_PHASE_45         0x02

/* for phase 0 sampling start after 3/16 of period of sampling clock from trigger event occur */
#define ADC_SAMPLE_PHASE_67_5       0x03

/* for phase 0 sampling start after 4/16 of period of sampling clock from trigger event occur */
#define ADC_SAMPLE_PHASE_90         0x04

/* for phase 0 sampling start after 5/16 of period of sampling clock from trigger event occur */
#define ADC_SAMPLE_PHASE_112_5      0x05

/* for phase 0 sampling start after 6/16 of period of sampling clock from trigger event occur */
#define ADC_SAMPLE_PHASE_135        0x06

/* for phase 0 sampling start after 7/16 of period of sampling clock from trigger event occur */
#define ADC_SAMPLE_PHASE_157_5      0x07

/* for phase 0 sampling start after 8/16 of period of sampling clock from trigger event occur */
#define ADC_SAMPLE_PHASE_180        0x08

/* for phase 0 sampling start after 9/16 of period of sampling clock from trigger event occur */
#define ADC_SAMPLE_PHASE_202_5      0x09

/* for phase 0 sampling start after 10/16 of period of sampling clock from trigger event occur */
#define ADC_SAMPLE_PHASE_225        0x0A

/* for phase 0 sampling start after 11/16 of period of sampling clock from trigger event occur */
#define ADC_SAMPLE_PHASE_247_5      0x0B

/* for phase 0 sampling start after 12/16 of period of sampling clock from trigger event occur */
#define ADC_SAMPLE_PHASE_270        0x0C

/* for phase 0 sampling start after 13/16 of period of sampling clock from trigger event occur */
#define ADC_SAMPLE_PHASE_292_5      0x0D

/* for phase 0 sampling start after 14/16 of period of sampling clock from trigger event occur */
#define ADC_SAMPLE_PHASE_315        0x0E

/* for phase 0 sampling start after 15/16 of period of sampling clock from trigger event occur */
#define ADC_SAMPLE_PHASE_337_5      0x0F

typedef uint8 Adc_SamplePhaseType ;


/*********************************************************************************/

/*
 * use this macros as a value for variable of Adc_DCompType
 * this type indicate Digital comparator unit referenced by the functions
 * there ara 8 digital comparators inside every ADC module .
 */

/* Digital comparator 0 */
#define ADC_DIGITAL_COMP_0  0x00

/* Digital comparator 1 */
#define ADC_DIGITAL_COMP_1  0x01

/* Digital comparator 2 */
#define ADC_DIGITAL_COMP_2  0x02

/* Digital comparator 3 */
#define ADC_DIGITAL_COMP_3  0x03

/* Digital comparator 4 */
#define ADC_DIGITAL_COMP_4  0x04

/* Digital comparator 5 */
#define ADC_DIGITAL_COMP_5  0x05

/* Digital comparator 6 */
#define ADC_DIGITAL_COMP_6  0x06

/* Digital comparator 7 */
#define ADC_DIGITAL_COMP_7  0x07

typedef uint8 Adc_DCompType ;


/*********************************************************************************/

/*
 * use this macros as a value for variable of Adc_SampleType
 * this type indicate samples of sample sequecner referenced by the functions
 * there ara at most 8 samples entries for sample sequencer .
 * sample sequencer 0 have 8 samples
 * sample sequencer 1 have 4 samples
 * sample sequencer 2 have 4 samples
 * sample sequencer 3 have 1 samples
 * if user referenced sample entry beyond sequencer limit no effect will happen
 */

/*
 * sample entry represent all about sample i.e ,
 * its control setting, its destination and source, and what happen when sampled
 * for every sample all this setting must be set for every used sample sequencer
 */

/* sample entry 0 */
#define ADC_SAMPLE_0    0x00

/* sample entry 1 */
#define ADC_SAMPLE_1    0x04

/* sample entry 2 */
#define ADC_SAMPLE_2    0x08

/* sample entry 3 */
#define ADC_SAMPLE_3    0x0C

/* sample entry 4 */
#define ADC_SAMPLE_4    0x10

/* sample entry 5 */
#define ADC_SAMPLE_5    0x14

/* sample entry 6 */
#define ADC_SAMPLE_6    0x18

/* sample entry 7 */
#define ADC_SAMPLE_7    0x1C

typedef uint8 Adc_SampleType ;

/*********************************************************************************/

/*
 * use this macros as a value for variable of Adc_ChannelType
 * this type indicate ADC input channels referenced by the functions
 */

/*
 * some i/o pins could be used as input to ADC modules to sample its signal .
 * this analog functionality must be enabled by port driver to use i/o pin as input source .
 * for each sample entry in each sample sequencer input channel could be selected by software .
 * there's a total of 12 analog input channel could be use them as single ended input ,
 * or could be used as differential inputs, and in this case they used as pairs with total of 6 pairs .
 * channel 0,1 represent pair 0 , channel 10,11 represent pair 5 .
 * ADC module sample the result signal of (even channel signal) - (odd channel signal) in differential mode .
 */

/* input channel 0 */
#define ADC_CHANNEL_0   0x00

/* input channel 1 */
#define ADC_CHANNEL_1   0x01

/* input channel 2 */
#define ADC_CHANNEL_2   0x02

/* input channel 3 */
#define ADC_CHANNEL_3   0x03

/* input channel 4 */
#define ADC_CHANNEL_4   0x04

/* input channel 5 */
#define ADC_CHANNEL_5   0x05

/* input channel 6 */
#define ADC_CHANNEL_6   0x06

/* input channel 7 */
#define ADC_CHANNEL_7   0x07

/* input channel 8 */
#define ADC_CHANNEL_8   0x08

/* input channel 9 */
#define ADC_CHANNEL_9   0x09

/* input channel 10 */
#define ADC_CHANNEL_10  0x0A

/* input channel 11 */
#define ADC_CHANNEL_11  0x0B

typedef uint8 Adc_ChannelType ;

/*********************************************************************************/

/* this type used to indicate sample conversion result */

typedef uint16 Adc_ResultType ;

/*********************************************************************************/

/*
 * use this macros as a value for variable of Adc_DCompModeType
 * this type indicate different modes of digital comparator of ADC module
 */

/*
 * for every digital comparator there's a separate mode (state machine) for trigger and event
 * and comparator check for both if sample result achieve state machine or not
 * and it sent signal of achieved one trigger or event or both
 */

/*
 * as long as sample results sent to digital comparator is within specified range (condition)
 * the state machine of event/trigger is achieved and signal is send .
 * this state machine like level interrupt as long as interrupt level is present as long as interrupt is asserted .
 */
#define ADC_DCOMP_ALWAYS            0x00

/*
 * for this state machine it will sample result will achieve it if and only if
 * the previous result didn't achieve the state machine .
 * this state machine like edge interrupt .
 */
#define ADC_DCOMP_MODE_ONCE         0x01

/*
 * this mode mustn't be used with ADC_DCOMP_MID_BAND range (condition) .
 * for this mode it same like ADC_DCOMP_ALWAYS mode but with hysteresis .
 * which mean if a sample result is within comparator range (condition) the state ,
 * machine is achieved and event/trigger signal is asserted for all following ,
 * sample result till result became in opposite range (condition) and then ,
 * all following sample results wouldn't achieve state machine till a result become within range and so on .
 */
#define ADC_DCOMP_MODE_HYS_ALWAYS   0x02

/*
 * this mode mustn't be used with ADC_DCOMP_MID_BAND range (condition) .
 * for this mode it same like ADC_DCOMP_ALWAYS mode but with hysteresis .
 * which mean if a sample result is within comparator range (condition) the state ,
 * machine is achieved and event/trigger signal is asserted for this sample result .
 * and to achieve state machine again digital comparator must receive a sample result ,
 * within opposite range of its range and then for first sample result within comparator range ,
 * state machine would be achieved .
 */
#define ADC_DCOMP_MODE_HYS_ONCE     0x03

typedef uint8 Adc_DCompModeType ;

/*********************************************************************************/

/*
 * use this macros as a value for variable of Adc_DCompCondTyp
 * this type indicate different ranges (conditions) of digital comparator of ADC module
 */

/*
 * for every digital comparator there's a separate condition (range) for trigger and event
 * and comparator check for both if sample result within range or not
 * and it sent signal of achieved one trigger or event or both
 */


/* the range of sample result must be 0 ~ Comp0(LowerValue) */
#define ADC_DCOMP_LOW_BAND      0x00

/* the range of sample result must be Comp0(LowerValue)+1 ~ Comp1(UpperValue)-1 */
#define ADC_DCOMP_MID_BAND      0x01

/* the range of sample result must be  Comp1(UpperValue) ~ 0xFFF */
#define ADC_DCOMP_HIGH_BAND     0x03

typedef uint8 Adc_DCompCondTyp ;

/*********************************************************************************/

/*
 * use this macros as a value for variable of Adc_SampleRateType
 * this type indicate different sample rate for ADC module to work on
 */

/*
 * sample rate could be doubled using both ADC modules and with phase shift = 180 degree of each other
 */

/* sample rate is 125kSample/s */
#define ADC_SAMPLE_RATE_125K    0x01

/* sample rate is 250kSample/s */
#define ADC_SAMPLE_RATE_250K    0x03

/* sample rate is 500kSample/s */
#define ADC_SAMPLE_RATE_500K    0x05

/* sample rate is 1MSample/s */
#define ADC_SAMPLE_RATE_1M      0x07

typedef uint8 Adc_SampleRateType ;

/*********************************************************************************/

/*
 * use this macros as a value for variable of Adc_ClkSourceType
 * this type indicate clock sources for ADC modules
 */

/*
 * ADC clock source is 16Mhz clock come from PIOSC, PLL or MOSC
 */

/*
 * clock source will be PLL/25 if system clock derived from  PLL
 * and will be MOSC (system clock) if PLL is bypassed
 */
#define ADC_CLK_SOURCE_SYS      0x00

/*
 * clock source will from PIOSC and in this case ADC could work in deep sleep mode .
 */
#define ADC_CLK_SOURCE_PIOSC    0x01

typedef uint8 Adc_ClkSourceType ;

/*********************************************************************************/

#define ADC_BufferRead( ModuleId, SequencerId )      (*((volatile uint32 *)(ADC_MOD_0_BUFFER_ADD + ModuleId*ADC_MODULE_OFFSET + SequencerId* ADC_SEQ_OFFSET)))

/*********************************************************************************/

/*
 * non privilege, synchronous, non-Reentrant function .
 * this function will initialize all ADC modules, according to ADC_Cfg.h file.
 * it will initialize clock, sample rate, interrupt mask, sample sequencer and digital comparators setting.
 * follow rules demonstrated in ADC_Cfg.h file to make proper initialization .
 * Mask will determine modules to be initiated according whether module bit in Mask is set or not
 * there're 3 modules 0,1, LSB is assigned to module0 and 2nd bit assigned to module1
 * don't initiate a module with disabled clock or fault exception will be generated
 */

void Adc_Init (  uint8 Mask ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will return the state of ADC module defined by ModuleId .
 * if return value = TRUE then the ADC is currently operate in conversion,
 * or it wait for pended trigger .
 * if return value = FALSE then ADC is idle and no conversion running,
 * and no pending triggers
 * software must use this function before disable ADC clock to ensure ADC is idle .
 */

boolean Adc_BusyState ( Adc_ModuleType ModuleId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will enable sequencers specified by SequencerId,
 * in ADC module specified by ModuleId .
 * initiate sequencer setting before enabling it .
 * when sequencer is enabled then it will start sampling according to its setting,
 * whenever right trigger for sequencer occur .
 */

void Adc_SequencerEnable ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will disable sequencers specified by SequencerId,
 * in ADC module specified by ModuleId .
 * whenever sequencer is disabled it will stop operation and won't continue after it enabled again .
 */

void Adc_SequencerDisable ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId) ;

/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will return the event state of interrupt specified by InterruptID in module of ModuleId .
 * if return = TRUE then event occurred and if interrupt is enabled,
 * then interrupt signal would be generated to NVIC .
 * if return = FALSE then event didn't happen yet .
 * this function is just responsible for events from sample sequencer not digital comparators too .
 */

boolean Adc_GetSequencerEvent ( Adc_ModuleType ModuleId, Adc_InterruptType InterruptID ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function is same like Adc_GetSequencerEvent but it will return all events status .
 * it will return a byte and every bit in the lowest nibble will represent state of one interrupt .
 * LSB (bit0) represent interrupt ADC_SEQUENCER_0_INT and bit 3 represent ADC_SEQUENCER_3_INT  .
 * if bit is set then corresponding event occurred .
 */

uint8 Adc_GetAllSequencerEvents ( Adc_ModuleType ModuleId) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will return the state of interrupt specified by InterruptID in module of ModuleId .
 * if return = TRUE then event occurred and interrupt is enabled,
 * then interrupt signal would be generated to NVIC .
 * if return = FALSE then event didn't happen yet or interrupt is disabled .
 * this function is just responsible for events from sample sequencer not digital comparators too .
 */

boolean Adc_GetSequencerInterrupt ( Adc_ModuleType ModuleId, Adc_InterruptType InterruptID ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function is same like Adc_GetSequencerInterrupt but it will return all interrupts states .
 * it will return a byte and every bit in the lowest nibble will represent state of one interrupt
 * if bit is set then corresponding event occurred and interrupt enabled and its signal is send to NVIC .
 * if not then corresponding interrupt is disabled or event didn't occur .
 */

uint8 Adc_GetAllSequencerInterrupts ( Adc_ModuleType ModuleId) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will clear the event of interrupt specified by InterruptID in module of ModuleId .
 * use this function inside ISR code to clear event caused interrupt,
 * or interrupt signal will be asserted again as soon as the ISR finish .
 * this function is just responsible for events from sample sequencer not digital comparators too .
 */

void Adc_ClearSequencerEvent ( Adc_ModuleType ModuleId, Adc_InterruptType InterruptID ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function is same like Adc_ClearAllSequencerEvents but it will clear all sequencers events .
 * this function is just responsible for events from sample sequencer not digital comparators too .
 */

void Adc_ClearAllSequencerEvents (  Adc_ModuleType ModuleId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will enable the interrupt specified by InterruptID in module of ModuleId .
 * if interrupt is enabled then when event of this interrupt occur, interrupt signal asserted to NVIC
 * this function is just responsible for events from sample sequencer not digital comparators too .
 */

void Adc_EnableSequencerInterrupt ( Adc_ModuleType ModuleId, Adc_InterruptType InterruptID ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will disable the interrupt specified by InterruptID in module of ModuleId .
 * if interrupt is disabled then when event of this interrupt occur, interrupt signal won't asserted to NVIC .
 * this function is just responsible for events from sample sequencer not digital comparators too .
 */

void Adc_DisableSequencerInterrupt ( Adc_ModuleType ModuleId, Adc_InterruptType InterruptID ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will get the buffer overflow state of sequencer defined by SequencerId of ModuleId .
 * if buffer overflowed return will = TRUE else it will be FALSE .
 * overflow happen when hardware write sequencer buffer happen and buffer is full .
 * if overflow flag is set then it won't be cleared except by software
 */

boolean Adc_GetOVState ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will get the buffer under state of sequencer defined by SequencerId of ModuleId .
 * if buffer underflowed return will = TRUE else it will be FALSE .
 * under happen when read sequencer buffer happen and buffer is empty .
 * if underflow flag is set then it won't be cleared except by software
 */

boolean Adc_GetUVState ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function is same like Adc_SequencerUnderflow function but will return,
 * overflow states of all sequencer, least nibble of return byte represent states of all sequencers ,
 * every bit in nibble represent one of four sequencer .
 * if bit is set then corresponding sequencer buffer is overflowed
 */

uint8 Adc_GetAllOVStates ( Adc_ModuleType ModuleId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function is same like Adc_SequencerUnderflow function but will return,
 * underflow states of all sequencer, least nibble of return byte represent states of all sequencers ,
 * every bit in nibble represent one of four sequencer .
 * if bit is set then corresponding sequencer buffer is underflowed
 */

uint8 Adc_GetAllUVStates ( Adc_ModuleType ModuleId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will clear the buffer overflow state of sequencer defined by SequencerId of ModuleId .
 * overflow happen when hardware write sequencer buffer happen and buffer is full .
 * if overflow flag is set then it won't be cleared except by software using this function .
 */

void Adc_ClearOVState ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will clear the buffer underflow state of sequencer defined by SequencerId of ModuleId .
 * underflow happen when hardware read sequencer buffer happen and buffer is empty .
 * if underflow flag is set then it won't be cleared except by software using this function .
 */

void Adc_ClearUVState ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function is same like Adc_ClearOVState but it will clear all overflow flags,
 * of module specified by ModuleId
 */

void Adc_ClearAllOVStates ( Adc_ModuleType ModuleId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function is same like Adc_ClearAllUVStates but it will clear all underflow flags,
 * of module specified by ModuleId
 */

void Adc_ClearAllUVStates ( Adc_ModuleType ModuleId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function used to assign trigger source defined by SourceId to ,
 * sequencer defined by SequencerId in module defined by ModuleId .
 * when trigger source send a trigger signal to ADC modules according to its setting ,
 * the sequencers that configured to response to this trigger will start sampling according to their priority .
 */

void Adc_TriggerSource ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId, Adc_TriggerSourceType SourceId) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function used to identify which PWM module contain,
 * PWM generators that used as trigger sources for sequencers .
 * PWM generator determined by PwmId contained in PWM module determined by GeneratorId
 * used as trigger source for sequencers of ADC module determined by ModuleId
 */

void Adc_SelectPwmModule ( Adc_ModuleType ModuleId, Adc_PwmGenratorType GeneratorId , Adc_PwmModuleType PwmId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function used to set priority of sequencers .
 * in any moment only one sample sequencers could be operate in every ADC module .
 * so for two or more sequencers triggered in same moment they are queued to operate according to their priority .
 * there's four priorities 0 ~ 3 and 0 is highest one .
 * it's recommended for every sequencer to have a unique priority .
 * if two sequencers has same priority and triggered at same time behavior is unexpected
 */

void Adc_SequencerPriority ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId, uint8 Priority) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function used to set ADC module determined by ModuleId to sample-phase determined by Phase
 * reference to Adc_SamplePhaseType comments for more informations about sampling phase
 */

void Adc_SetSamplePhase ( Adc_ModuleType ModuleId, Adc_SamplePhaseType Phase ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * use this function to start the sequencers that their trigger source is processor -> ADC_TRIGGER_PROCESSOR .
 * least nibble of SequencersMask represent 4 sequencer of ADC module determined by ModuleId .
 * LSB represent sequencer0 and 4th bit represent sequencer 4 .
 * if sequencer corresponding bit is set then sequencer will start if its trigger source is processor .
 * if more than one sequencer triggered at same time then will queued according to their priority .
 * this function also will start any sequencer ( if it's processor triggered ) ,
 * that been initiated by Adc_InitiateSequencers function ,
 * even if it's in another ADC module and even if SequencersMask = 0 .
 */

void Adc_StartSequencers ( Adc_ModuleType ModuleId, uint8 SequencersMask ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function same as Adc_StartSequencers but it will just initiate sequencer to
 * operate when using Adc_StartSequencers function .
 * sequencers initiated by this function would start together even if Adc_StartSequencers used
 * with another ADC module .
 * this function used to synchronize to start sampling in different ADC modules at same moment using processor .
 */

void Adc_InitiateSequencers ( Adc_ModuleType ModuleId, uint8 SequencersMask ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function set average factor for ADC module determined by ModuleId .
 * average factor is 2 ^ FactorPower, and represent number of samples that ,
 * ADC module will take their average to generate a more accurate result which ,
 * considered as one sample for sample sequencer (stored in buffer or go to comparators) .
 * averaging will decrease sample rate by same factor of average factor
 * so if sample rate is 1Msps and FactorPower = 2 which mean average factor = 4 ,
 * then the o/p sample rate that reach sequencers is 250Ksps ,
 * because averaging circuit collect 4 samples to generate 1 sample for sequencers .
 */

void Adc_AveragingFactor ( Adc_ModuleType ModuleId, uint8 FactorPower ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function used to enable Digital comparator interrupt as illustrated in Adc_InterruptType .
 * for every ADC module specified by ModuleId there must be one enabled interrupt for comparators .
 * if this function used to enable comparators interrupt for more than one InterruptID ,
 * the all comparators interrupts will be masked till just one be enabled .
 * interrupt line specified by InterruptID will be interrupt line of digital comparator ,
 * so comparator ISR code must be invoked in that interrupt's position in vector table ,
 * and SW must check when this ISR executed whether trigger source come from comparators ,
 * or sample sequencer of that interrupt line if enabled
 * also all 8 digital comparator trigger same interrupt so ,
 * SW must check for the comparator that triggered interrupt in the ISR code
 */
void Adc_DComp_SecletIntLine ( Adc_ModuleType ModuleId, Adc_InterruptType InterruptID ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function same as Adc_DComp_EnableInterrupt but it will disable comparators interrupt
 * to be sent on interrupt line specified by InterruptID
 */

void Adc_DComp_DeselectIntLine ( Adc_ModuleType ModuleId, Adc_InterruptType InterruptID ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will return the state of interrupt generated by ,
 * comparator specified by DCompId in module specified by ModuleId .
 * if TRUE is returned then comparator event occur and will generate interrupt if,
 * there is on comparators interrupt line is selected  by Adc_DComp_SecletIntLine
 * and this interrupt line is enabled by NVIC module  .
 */

boolean Adc_DComp_GetEventState ( Adc_ModuleType ModuleId, Adc_DCompType DCompId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function same as Adc_DComp_IntState but it will return all comparators states .
 * in byte returned bit 0 represent comparator 0 if bit is set the interrupt state is TURE .
 */

uint8 Adc_DComp_GetEventStateAll ( Adc_ModuleType ModuleId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will clear the state of interrupt generated by ,
 * comparator specified by DCompId in module specified by ModuleId .
 * it must be used in ISR of interrupt  triggered by digital comparator ,
 * to clear interrupt source or interrupt will be triggered again as soon as ISR finish
 */

void Adc_DComp_EventClr (Adc_ModuleType ModuleId, Adc_DCompType DCompId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function same as Adc_DComp_IntClr but it will clear all comparators states ,
 * correspond for set bits in Mask .
 * bit 0 in Mask represent comparator 0 if bit is set then its interrupt state will be cleared .
 */

void Adc_DComp_EventClrAll (Adc_ModuleType ModuleId, uint8 Mask  ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will enable/disable the Dither feature of ADC module specified by ModuleId .
 * if Enable is TRUE then the feature is enable if else then it will disabled .
 * Dither feature is used to reduce random noise in ADC sampling and keep module operation ,
 * within specific performance of MCU kit .
 * it's recommended to enable this feature when using module to take consecutive samples .
 * this feature is disabled by default after reset .
 */

void Adc_DitherControl ( Adc_ModuleType ModuleId, boolean Enable) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will assign the input channel/pair for sample entry specified by SampleId ,
 * which belong to sequencer specified by SequencerId in ADC module specified by ModuleId .
 * for single ended mode, ChannelId represent the input channel and could use all values of Adc_ChannelType .
 * and for differential input mode, ChannelId represent the input pair and there's just 6 pairs,
 * so ChannelId could just take values from ADC_CHANNEL_0 ~ ADC_CHANNEL_5 .
 *
 */

void Adc_SelectInputChannel ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId, Adc_SampleType SampleId, Adc_ChannelType ChannelId) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will enable/disable sampling internal temperature sensor for sample entry specified by SampleId ,
 * which belong to sequencer specified by SequencerId in ADC module specified by ModuleId .
 * internal temperature sensor used to notify the system temperature and to calibrate the internal RC oscillator .
 * if this feature is enabled then differential input mode cannot be enabled and vice versa .
 */

void Adc_Sample_TempSensorCtrl ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId, Adc_SampleType SampleId, boolean Enable ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will enable/disable event generation for sample entry specified by SampleId ,
 * which belong to sequencer specified by SequencerId in ADC module specified by ModuleId .
 * after sampling finish for this sample entry event is asserted from sequencer sample entry belong to .
 * and if sequencer interrupt isn't masked an interrupt signal is send to NVIC module .
 * all sample entries' events is get or together to generate its sequencer event signal .
 */

void Adc_Sample_EventCtrl ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId, Adc_SampleType SampleId, boolean Enable ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will enable/disable end flag for sample entry specified by SampleId ,
 * which belong to sequencer specified by SequencerId in ADC module specified by ModuleId .
 * for any sequencer it start sampling from sample entry 0 till the last sample entry ,
 * or till find enabled end flag for any sample .
 * so if end flag of sample 5 in sequencer 0 is enabled then sampling end to sequencer 0 after the fifth sample ,
 * and wait for another trigger to start new sampling from sample 0 .
 */

void Adc_Sample_EndCtrl ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId, Adc_SampleType SampleId, boolean Enable ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will enable/disable differential mode for sample entry specified by SampleId ,
 * which belong to sequencer specified by SequencerId in ADC module specified by ModuleId .
 * if this feature is enabled then internal temperature sensor input mode cannot be enabled and vice versa .
 * when enabling differential mode for any entry, its input pair is chosen by Adc_SelectInputChannel function  ,
 * the pair chosen will specify the two input channels for this sample which will be 2*pair and 2*pair + 1 .
 * the entry will sample result of even channel signal - odd channel signal .
 */

void Adc_Sample_DifferentialCtrl ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId, Adc_SampleType SampleId, boolean Enable ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function used to read multiple samples result from sequencer buffer into user passed array .
 * sequencer buffers has certain depth 8 for sequencer 0, 4 for sequencer 1,2 and 1 for sequencer 3 .
 * user pass array to read data in array specified by DataPtr ,
 * the number of samples to be read specified by SamplesNumber ,
 * and this mustn't exceed the buffer depth of sequencer specified by SequencerId in ADC module ModuleId .
 * if user want to read single sample it's recommended to use ADC_BufferRead() function.
 * software must check if buffer is have at least number of samples to read equal to SamplesNumber
 * or underflow event will be asserted and read operation won't be useful .
 */

void Adc_MultiResultRead ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId, Adc_ResultType * DataPtr, uint8 SamplesNumber  ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will return TRUE if buffer of sequencer specified by SequencerId,
 * in ADC module specified by ModuleId is empty which mean is has no samples to read .
 * and any read operation done on empty buffer will result in underflow event .
 * reading of empty buffer will return the old value of the first entry to be written in buffer .
 */

boolean Adc_CheckEmptyBuffer (Adc_ModuleType ModuleId, Adc_SequencerType SequencerId) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will return TRUE if buffer of sequencer specified by SequencerId,
 * in ADC module specified by ModuleId is full which mean all its entry full with samples .
 * and any write operation done on full buffer will result in underflow event .
 * write to full buffer have no effect and sample result will be lost
 */

boolean Adc_CheckFullBuffer (Adc_ModuleType ModuleId, Adc_SequencerType SequencerId) ;

/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will return the index of next entry to be written in ,
 * buffer of sequencer specified by SequencerId in ADC module specified by ModuleId .
 * index of entry will be in range of 0 ~ buffer depth - 1 .
 */

uint8 Adc_GetBufferHead (Adc_ModuleType ModuleId, Adc_SequencerType SequencerId) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will return the index of next entry to be read in ,
 * buffer of sequencer specified by SequencerId in ADC module specified by ModuleId .
 * index of entry will be in range of 0 ~ buffer depth - 1 .
 */

uint8 Adc_GetBufferTail (Adc_ModuleType ModuleId, Adc_SequencerType SequencerId) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will specify destination for sample entry specified by SampleId ,
 * which belong to sequencer specified by SequencerId in ADC module specified by ModuleId .
 * if Compare is TRUE then sample result will send to ,
 * digital comparator specified to this entry by Adc_SampleDCompSelect() ,
 * to be compared according to this digital comparator setting .
 * if Compare is FALSE then sample result will be saved in sequencer buffer .
 */

void Adc_SampleDestinationCtrl ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId, Adc_SampleType SampleId, boolean Compare ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will specify digital comparator for sample entry specified by SampleId ,
 * which belong to sequencer specified by SequencerId in ADC module specified by ModuleId .
 * if sample entry destination specified by Adc_SampleDestinationCtrl() is set to digital comparator .
 * then sample result will be sent to digital comparator unit specified by DCompId ,
 * to be compared according to its setting and take proper action .
 * if destination for the sample entry is to be saved in sequencer buffer ,
 * then this function won't affect sampling operation .
 */

void Adc_SampleDCompSelect( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId, Adc_SampleType SampleId, Adc_DCompType DCompId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * for digital comparator unit specified by DCompId which in ADC module specified by ModuleId ,
 * digital comparator depend on both current and previous sample result to check if current ,
 * sample match state machine of digital comparator .
 * this function will reset interrupt state to the initial condition .
 * so that it won't depend on previous sample result and start from next one
 *
 */

void Adc_DComp_ResetInterrupt (  Adc_ModuleType ModuleId, Adc_DCompType DCompId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * for digital comparator unit specified by DCompId which in ADC module specified by ModuleId ,
 * digital comparator depend on both current and previous sample result to check if current ,
 * sample match state machine of digital comparator .
 * this function will reset trigger state to the initial condition .
 * so that it won't depend on previous sample result and start from next one
 */

void Adc_DComp_ResetTrigger (  Adc_ModuleType ModuleId, Adc_DCompType DCompId ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * for digital comparator unit specified by DCompId which in ADC module specified by ModuleId ,
 * this function will enable/disable the trigger for it .
 * if trigger enabled and sample result sent to digital comparator is within trigger range (condition) ,
 * and achieve trigger state machine (mode) then trigger is sent to PWM generators .
 * if Enable is TRUE then trigger is enabled and disabled if else
 */

void Adc_DComp_TrigCtrl ( Adc_ModuleType ModuleId, Adc_DCompType DCompId, boolean Enable ) ;

/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * for digital comparator unit specified by DCompId which in ADC module specified by ModuleId ,
 * this function will set the trigger condition (work range) of it .
 * refer to Adc_DCompCondTyp to more information about comparator conditions (ranges).
 * if sample result sent to digital comparator is within trigger range ,
 * and achieve trigger state machine then ADC trigger PWM generator
 * calling of this function will reset the state of digital comparator trigger like Adc_DComp_ResetTrigger()
 */

void Adc_DComp_TrigCond ( Adc_ModuleType ModuleId, Adc_DCompType DCompId, Adc_DCompCondTyp Condition ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * for digital comparator unit specified by DCompId which in ADC module specified by ModuleId ,
 * this function will set the trigger mode (state machine) of it .
 * refer to Adc_DCompModeType to more information about comparator conditions (ranges) .
 * if sample result sent to digital comparator is within trigger range ,
 * and achieve trigger state machine then ADC trigger PWM generator
 * calling of this function will reset the state of digital comparator trigger like Adc_DComp_ResetTrigger()
 */

void Adc_DComp_TrigMode ( Adc_ModuleType ModuleId, Adc_DCompType DCompId, Adc_DCompModeType Mode ) ;

/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * for digital comparator unit specified by DCompId which in ADC module specified by ModuleId ,
 * this function will enable/disable the event for it .
 * if event enabled and sample result sent to digital comparator is within event range (condition),
 * and achieve event state machine (mode) then digital comparator event flag is set and,
 * interrupt signal is sent to NVIC on interrupt line chosen to digital comparators by Adc_DComp_SecletIntLine() .
 * if Enable is TRUE then event is enabled and disabled if else
 * make sure to clear digital comparator flag on ISR to avoid reentering the ISR after finishing it .
 */

void Adc_DComp_EventCtrl ( Adc_ModuleType ModuleId, Adc_DCompType DCompId, boolean Enable ) ;

/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * for digital comparator unit specified by DCompId which in ADC module specified by ModuleId ,
 * this function will set the event condition (work range) of it .
 * refer to Adc_DCompCondTyp to more information about comparator conditions (ranges) .
 * if sample result sent to digital comparator is within trigger range ,
 * and achieve trigger state machine then digital comparator event  is set .
 * calling of this function will reset the state of digital comparator interrupt like Adc_DComp_ResetInterrupt()
 */

void Adc_DComp_EvnetCond ( Adc_ModuleType ModuleId, Adc_DCompType DCompId, Adc_DCompCondTyp Condition ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * for digital comparator unit specified by DCompId which in ADC module specified by ModuleId ,
 * this function will set the event condition (work range) of it .
 * refer to Adc_DCompModeType to more information about comparator conditions (ranges) .
 * if sample result sent to digital comparator is within trigger range ,
 * and achieve trigger state machine then digital comparator event  is set .
 * calling of this function will reset the state of digital comparator interrupt like Adc_DComp_ResetInterrupt()
 */

void Adc_DComp_EvnetMode ( Adc_ModuleType ModuleId, Adc_DCompType DCompId, Adc_DCompModeType Mode ) ;


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * for digital comparator specified by DCompId in ADC module specified by ModuleId ,
 * this function will set values that separate comparator range and determine
 * the area of every range .
 * low band start from 0 ~ LowerValue-1 , high band start from UpperValue ~ 0xFFF and rest for mid band
 * LowerValue must be less than or equal to UpperValue .
 * if UpperValue = LowerValue then comparator will just have 2 ranges high and low band with no mid band .
 * if LowerValue > UpperValue then the behavior is not expected
 */

void Adc_DComp_Range ( Adc_ModuleType ModuleId, Adc_DCompType DCompId, uint16 UpperValue, uint16 LowerValue ) ;


/*********************************************************************************/


/*
 * non privilege, synchronous, Reentrant function .
 * this function used to set the sample rate of ADC module specified by ModuleId according to Rate .
 * sample rate will be equal to the rate sample results is generated if averaging factor = 1 .
 * sample results generated by rate equal to sample rate divided by averaging factor .
 * sample rate could be doubled using both ADC modules to sample same input source with
 * same sample rate and out of phase by 180 degree of each other and their result is rearranged in back to back way .
 */

void Adc_SetSampleRate ( Adc_ModuleType ModuleId, Adc_SampleRateType Rate ) ;


/*********************************************************************************/


/*
 * non privilege, synchronous, Reentrant function .
 * this function used to set the ADC modules clock source of ADC module specified by ModuleId according to Source .
 * ADC modules can't have different clock sources so if both ADC0,1 is enabled ,
 * then ADC0 clock source configuration will overwrite ADC1 clock source configuration .
 */

void Adc_SetClockSource ( Adc_ModuleType ModuleId, Adc_ClkSourceType Source ) ;


/*********************************************************************************/

#endif /* ADC_H_ */

