/************************************************/
/*  Adc_Cfg.h                                       */
/*  Created on: Dec 22, 2020                    */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/

#ifndef ADC_CFG_H_
#define ADC_CFG_H_

/*********************************************************************************/

/* this is initializations settings which will be applied for ADC modules after execution of ADC_Init function. */


/*
 * set sample rate for every ADC module use values of Adc_SampleRateType
 */
#define ADC_MOD_0_SAMPLE_RATE       ADC_SAMPLE_RATE_1M
#define ADC_MOD_1_SAMPLE_RATE       ADC_SAMPLE_RATE_1M


/*
 * set clock source for every module values of use Adc_ClkSourceType
 * note that both ADC modules must get their clock from same source
 * so module 0 clock source will be the source for both modules
 */
#define ADC_MOD_0_CLK_SRC           ADC_CLK_SOURCE_SYS
#define ADC_MOD_1_CLK_SRC           ADC_CLK_SOURCE_PIOSC


/*
 * initialize sample sequencer state for every module
 * every module has 4 sample sequencers each represented by bit, if bit set then sequencer is enabled.
 * LSB is for sample sequencer 0 ,
 * 4th bit for sample sequencer 1 .
 */
#define ADC_MOD_0_SEQ_CTRL          0x00
#define ADC_MOD_1_SEQ_CTRL          0x00


/*
 * initialize sample sequencer interrupts state for every module
 * every module has 4 sample sequencers each has an interrupt represented by bit, if bit set then interrupt is enabled.
 * LSB is for interrupt of sample sequencer 0 ,
 * 4th bit for interrupt of sample sequencer 1 .
 */
#define ADC_MOD_0_SEQ_INT_CTRL      0x00
#define ADC_MOD_1_SEQ_INT_CTRL      0x00


/*
 * set the trigger source for every sample sequencer in every module
 * use the values of Adc_TriggerSourceType
 */
#define ADC_MOD_0_SEQ_0_TRIG_SRC    ADC_TRIGGER_PWM_1
#define ADC_MOD_0_SEQ_1_TRIG_SRC    ADC_TRIGGER_PWM_1
#define ADC_MOD_0_SEQ_2_TRIG_SRC    ADC_TRIGGER_PWM_1
#define ADC_MOD_0_SEQ_3_TRIG_SRC    ADC_TRIGGER_PWM_1

#define ADC_MOD_1_SEQ_0_TRIG_SRC    ADC_TRIGGER_PWM_1
#define ADC_MOD_1_SEQ_1_TRIG_SRC    ADC_TRIGGER_PWM_1
#define ADC_MOD_1_SEQ_2_TRIG_SRC    ADC_TRIGGER_PWM_1
#define ADC_MOD_1_SEQ_3_TRIG_SRC    ADC_TRIGGER_PWM_1

/*
 * set the PWM module that its generator will be used as a trigger source for ADC sequencers
 * use the values of Adc_PwmGenratorType
 */
#define ADC_MOD_0_GEN_0_SLCT_PWM    ADC_PWM_MODULE_1
#define ADC_MOD_0_GEN_1_SLCT_PWM    ADC_PWM_MODULE_1
#define ADC_MOD_0_GEN_2_SLCT_PWM    ADC_PWM_MODULE_1
#define ADC_MOD_0_GEN_3_SLCT_PWM    ADC_PWM_MODULE_1

#define ADC_MOD_1_GEN_0_SLCT_PWM    ADC_PWM_MODULE_1
#define ADC_MOD_1_GEN_1_SLCT_PWM    ADC_PWM_MODULE_1
#define ADC_MOD_1_GEN_2_SLCT_PWM    ADC_PWM_MODULE_1
#define ADC_MOD_1_GEN_3_SLCT_PWM    ADC_PWM_MODULE_1


/*
 * set the priority of every sequencer in ADC modules there's 4 priorities 0 priority is the highest one
 * note that in same module every sequencer must has unique priority
 */
#define ADC_MOD_0_SEQ_0_PRIORITY    0
#define ADC_MOD_0_SEQ_1_PRIORITY    1
#define ADC_MOD_0_SEQ_2_PRIORITY    2
#define ADC_MOD_0_SEQ_3_PRIORITY    3

#define ADC_MOD_1_SEQ_0_PRIORITY    0
#define ADC_MOD_1_SEQ_1_PRIORITY    1
#define ADC_MOD_1_SEQ_2_PRIORITY    2
#define ADC_MOD_1_SEQ_3_PRIORITY    3


/*
 * set the phase shift of every ADC module
 * use the values of Adc_SamplePhaseType
 */
#define ADC_MOD_0_PHASE_SHIFT       ADC_SAMPLE_PHASE_180
#define ADC_MOD_1_PHASE_SHIFT       ADC_SAMPLE_PHASE_180


/*
 * set the power(of base 2) of average factor of every ADC module
 * max value is 6 for average factor = 64
 */
#define ADC_MOD_0_AVG_FACTOR_PWR    6
#define ADC_MOD_1_AVG_FACTOR_PWR    6


/*
 * control the digital comparator interrupt of ADC modules
 * if TRUE then interrupt is enabled
 */
#define ADC_MOD_0_DCOM_INT_CTRL     TRUE
#define ADC_MOD_1_DCOM_INT_CTRL     TRUE


/*
 * set the sequencer interrupt line used for digital comparator interrup
 * use the values of Adc_InterruptType
 */
#define ADC_MOD_0_DCOMP_INT_LINE    ADC_SEQUENCER_3_INT
#define ADC_MOD_1_DCOMP_INT_LINE    ADC_SEQUENCER_3_INT


/*
 * control dither feature for ADC modules if true then feature is enabled
 */
#define ADC_MOD_0_DITHER_CTRL       TRUE
#define ADC_MOD_1_DITHER_CTRL       TRUE


/*
 * select input channels for all samples of modules' sequencers
 * use value of Adc_ChannelType
 */

/* module 0 sequencers' samples  */
#define ADC_MOD_0_SEQ_0_SMP_0_SRC       ADC_CHANNEL_6
#define ADC_MOD_0_SEQ_0_SMP_1_SRC       ADC_CHANNEL_6
#define ADC_MOD_0_SEQ_0_SMP_2_SRC       ADC_CHANNEL_6
#define ADC_MOD_0_SEQ_0_SMP_3_SRC       ADC_CHANNEL_6
#define ADC_MOD_0_SEQ_0_SMP_4_SRC       ADC_CHANNEL_6
#define ADC_MOD_0_SEQ_0_SMP_5_SRC       ADC_CHANNEL_6
#define ADC_MOD_0_SEQ_0_SMP_6_SRC       ADC_CHANNEL_6
#define ADC_MOD_0_SEQ_0_SMP_7_SRC       ADC_CHANNEL_6

#define ADC_MOD_0_SEQ_1_SMP_0_SRC       ADC_CHANNEL_6
#define ADC_MOD_0_SEQ_1_SMP_1_SRC       ADC_CHANNEL_6
#define ADC_MOD_0_SEQ_1_SMP_2_SRC       ADC_CHANNEL_6
#define ADC_MOD_0_SEQ_1_SMP_3_SRC       ADC_CHANNEL_6

#define ADC_MOD_0_SEQ_2_SMP_0_SRC       ADC_CHANNEL_6
#define ADC_MOD_0_SEQ_2_SMP_1_SRC       ADC_CHANNEL_6
#define ADC_MOD_0_SEQ_2_SMP_2_SRC       ADC_CHANNEL_6
#define ADC_MOD_0_SEQ_2_SMP_3_SRC       ADC_CHANNEL_6

#define ADC_MOD_0_SEQ_3_SMP_0_SRC       ADC_CHANNEL_6

/* modules 1 sequencers' samples */
#define ADC_MOD_1_SEQ_0_SMP_0_SRC       ADC_CHANNEL_6
#define ADC_MOD_1_SEQ_0_SMP_1_SRC       ADC_CHANNEL_6
#define ADC_MOD_1_SEQ_0_SMP_2_SRC       ADC_CHANNEL_6
#define ADC_MOD_1_SEQ_0_SMP_3_SRC       ADC_CHANNEL_6
#define ADC_MOD_1_SEQ_0_SMP_4_SRC       ADC_CHANNEL_6
#define ADC_MOD_1_SEQ_0_SMP_5_SRC       ADC_CHANNEL_6
#define ADC_MOD_1_SEQ_0_SMP_6_SRC       ADC_CHANNEL_6
#define ADC_MOD_1_SEQ_0_SMP_7_SRC       ADC_CHANNEL_6

#define ADC_MOD_1_SEQ_1_SMP_0_SRC       ADC_CHANNEL_6
#define ADC_MOD_1_SEQ_1_SMP_1_SRC       ADC_CHANNEL_6
#define ADC_MOD_1_SEQ_1_SMP_2_SRC       ADC_CHANNEL_6
#define ADC_MOD_1_SEQ_1_SMP_3_SRC       ADC_CHANNEL_6

#define ADC_MOD_1_SEQ_2_SMP_0_SRC       ADC_CHANNEL_6
#define ADC_MOD_1_SEQ_2_SMP_1_SRC       ADC_CHANNEL_6
#define ADC_MOD_1_SEQ_2_SMP_2_SRC       ADC_CHANNEL_6
#define ADC_MOD_1_SEQ_2_SMP_3_SRC       ADC_CHANNEL_6

#define ADC_MOD_1_SEQ_3_SMP_0_SRC       ADC_CHANNEL_6

/*
 * control if input source of sample is from internal temperature sensor
 * every sequencer is represent by a macro  and every nibble represent a sample
 * if bit is set then input source for this sample is from internal temperature sensor
 * and if cleared then it from the analog input channels
 * LSN represent sample 0
 * for sequencer 0 it has 8 samples so it represent by double word
 * for sequencer 1,2 it has 4 samples so it represent by word
 * for sequencer 3 it has one sample so it represent by nibble
 */
#define ADC_MOD_0_SEQ_0_TEMP_CTRL   0x11111111
#define ADC_MOD_0_SEQ_1_TEMP_CTRL   0x1111
#define ADC_MOD_0_SEQ_2_TEMP_CTRL   0x1111
#define ADC_MOD_0_SEQ_3_TEMP_CTRL   0x1


/*
 * control if event is generated for sequencer when the sample result is obtained or not
 * every sequencer is represent by a macro  and every nibble represent a sample
 * if bit is set then the when sample result is obtained event is generated for this sequencers
 * LSB represent sample 0
 * for sequencer 0 it has 8 samples so it represent by double word
 * for sequencer 1,2 it has 4 samples so it represent by word
 * for sequencer 3 it has one sample so it represent by nibble
 */

#define ADC_MOD_0_SEQ_0_EVENT_CTRL  0x11111111
#define ADC_MOD_0_SEQ_1_EVENT_CTRL  0x1111
#define ADC_MOD_0_SEQ_2_EVENT_CTRL  0x1111
#define ADC_MOD_0_SEQ_3_EVENT_CTRL  0x1

/*
 * control if sequencer end its operation when the sample result is obtained or not
 * every sequencer is represent by a macro  and every nibble represent a sample
 * if bit is set then the when sample result is obtained sequencer stop sampling and wait for another trigger to start again from sample 0
 * LSB represent sample 0
 * for sequencer 0 it has 8 samples so it represent by double word
 * for sequencer 1,2 it has 4 samples so it represent by word
 * for sequencer 3 it has one sample so it represent by nibble
 */
#define ADC_MOD_0_SEQ_0_END_CTRL    0x11111111
#define ADC_MOD_0_SEQ_1_END_CTRL    0x1111
#define ADC_MOD_0_SEQ_2_END_CTRL    0x1111
#define ADC_MOD_0_SEQ_3_END_CTRL    0x1

/*
 * control the sampling mode for sample whether single ended or differential mode
 * every sequencer is represent by a macro  and every nibble represent a sample
 * if bit is set then sample is obtained from differential pair
 * and if cleared then it in single ended mode
 * LSN represent sample 0
 * for sequencer 0 it has 8 samples so it represent by double word
 * for sequencer 1,2 it has 4 samples so it represent by word
 * for sequencer 3 it has one sample so it represent by nibble
 */
#define ADC_MOD_0_SEQ_0_DIFF_CTRL   0x11111111
#define ADC_MOD_0_SEQ_1_DIFF_CTRL   0x1111
#define ADC_MOD_0_SEQ_2_DIFF_CTRL   0x1111
#define ADC_MOD_0_SEQ_3_DIFF_CTRL   0x1


/* same as previous macros for module 0 */
#define ADC_MOD_1_SEQ_0_TEMP_CTRL   0x11111111
#define ADC_MOD_1_SEQ_1_TEMP_CTRL   0x1111
#define ADC_MOD_1_SEQ_2_TEMP_CTRL   0x1111
#define ADC_MOD_1_SEQ_3_TEMP_CTRL   0x1

#define ADC_MOD_1_SEQ_0_EVENT_CTRL  0x11111111
#define ADC_MOD_1_SEQ_1_EVENT_CTRL  0x1111
#define ADC_MOD_1_SEQ_2_EVENT_CTRL  0x1111
#define ADC_MOD_1_SEQ_3_EVENT_CTRL  0x1

#define ADC_MOD_1_SEQ_0_END_CTRL    0x11111111
#define ADC_MOD_1_SEQ_1_END_CTRL    0x1111
#define ADC_MOD_1_SEQ_2_END_CTRL    0x1111
#define ADC_MOD_1_SEQ_3_END_CTRL    0x1

#define ADC_MOD_1_SEQ_0_DIFF_CTRL   0x11111111
#define ADC_MOD_1_SEQ_1_DIFF_CTRL   0x1111
#define ADC_MOD_1_SEQ_2_DIFF_CTRL   0x1111
#define ADC_MOD_1_SEQ_3_DIFF_CTRL   0x1


/*
 * select whether sample is saved into sequencer's FIFO or result sent to digital comparators
 * every sequencer is represent by a macro  and every nibble represent a sample
 * if nibble is set then sample result is sent to digital comparators
 * and if cleared then sampled will be saved in sequencer's FIFO
 * LSN represent sample 0
 * for sequencer 0 it has 8 samples so it represent by double word
 * for sequencer 1,2 it has 4 samples so it represent by word
 * for sequencer 3 it has one sample so it represent by nibble
 */
#define ADC_MOD_0_SEQ_0_DEST_CTRL   0x11111111
#define ADC_MOD_0_SEQ_1_DEST_CTRL   0x1111
#define ADC_MOD_0_SEQ_2_DEST_CTRL   0x1111
#define ADC_MOD_0_SEQ_3_DEST_CTRL   0x1

#define ADC_MOD_1_SEQ_0_DEST_CTRL   0x11111111
#define ADC_MOD_1_SEQ_1_DEST_CTRL   0x1111
#define ADC_MOD_1_SEQ_2_DEST_CTRL   0x1111
#define ADC_MOD_1_SEQ_3_DEST_CTRL   0x1


/*
 * select the digital comparator of every sample in every module's sequencer
 * this digital comparator is the one that sample result will be sent to ,if it won't be saved in sequencer's FIFO
 * use values of Adc_DCompType
 */
#define ADC_MOD_0_SEQ_0_SMP_0_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_0_SEQ_0_SMP_1_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_0_SEQ_0_SMP_2_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_0_SEQ_0_SMP_3_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_0_SEQ_0_SMP_4_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_0_SEQ_0_SMP_5_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_0_SEQ_0_SMP_6_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_0_SEQ_0_SMP_7_DCMP      ADC_DIGITAL_COMP_7

#define ADC_MOD_0_SEQ_1_SMP_0_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_0_SEQ_1_SMP_1_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_0_SEQ_1_SMP_2_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_0_SEQ_1_SMP_3_DCMP      ADC_DIGITAL_COMP_7

#define ADC_MOD_0_SEQ_2_SMP_0_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_0_SEQ_2_SMP_1_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_0_SEQ_2_SMP_2_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_0_SEQ_2_SMP_3_DCMP      ADC_DIGITAL_COMP_7

#define ADC_MOD_0_SEQ_3_SMP_0_DCMP      ADC_DIGITAL_COMP_7


#define ADC_MOD_1_SEQ_0_SMP_0_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_1_SEQ_0_SMP_1_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_1_SEQ_0_SMP_2_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_1_SEQ_0_SMP_3_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_1_SEQ_0_SMP_4_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_1_SEQ_0_SMP_5_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_1_SEQ_0_SMP_6_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_1_SEQ_0_SMP_7_DCMP      ADC_DIGITAL_COMP_7

#define ADC_MOD_1_SEQ_1_SMP_0_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_1_SEQ_1_SMP_1_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_1_SEQ_1_SMP_2_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_1_SEQ_1_SMP_3_DCMP      ADC_DIGITAL_COMP_7

#define ADC_MOD_1_SEQ_2_SMP_0_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_1_SEQ_2_SMP_1_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_1_SEQ_2_SMP_2_DCMP      ADC_DIGITAL_COMP_7
#define ADC_MOD_1_SEQ_2_SMP_3_DCMP      ADC_DIGITAL_COMP_7

#define ADC_MOD_1_SEQ_3_SMP_0_DCMP      ADC_DIGITAL_COMP_7


/*
 * control trigger of digital comparator whether it enabled or not
 * every module has 8 digital comparator and represent by one macro
 * every bit in macro represent one digital comparator
 * LSB for comparator 0
 * if bit set then comparator will check for trigger condition and state machine
 * and if matched it will trigger PWM generators
 */
#define ADC_MOD_0_DCOMP_TRIG_CTRL       0xFF
#define ADC_MOD_1_DCOMP_TRIG_CTRL       0xFF

/*
 * select the band of every digital comparator trigger
 * use the values of Adc_DCompCondTyp
 */
#define ADC_MOD_0_DCOMP_0_TRIG_COND     ADC_DCOMP_HIGH_BAND
#define ADC_MOD_0_DCOMP_1_TRIG_COND     ADC_DCOMP_HIGH_BAND
#define ADC_MOD_0_DCOMP_2_TRIG_COND     ADC_DCOMP_HIGH_BAND
#define ADC_MOD_0_DCOMP_3_TRIG_COND     ADC_DCOMP_HIGH_BAND
#define ADC_MOD_0_DCOMP_4_TRIG_COND     ADC_DCOMP_HIGH_BAND
#define ADC_MOD_0_DCOMP_5_TRIG_COND     ADC_DCOMP_HIGH_BAND
#define ADC_MOD_0_DCOMP_6_TRIG_COND     ADC_DCOMP_HIGH_BAND
#define ADC_MOD_0_DCOMP_7_TRIG_COND     ADC_DCOMP_HIGH_BAND

#define ADC_MOD_1_DCOMP_0_TRIG_COND     ADC_DCOMP_HIGH_BAND
#define ADC_MOD_1_DCOMP_1_TRIG_COND     ADC_DCOMP_HIGH_BAND
#define ADC_MOD_1_DCOMP_2_TRIG_COND     ADC_DCOMP_HIGH_BAND
#define ADC_MOD_1_DCOMP_3_TRIG_COND     ADC_DCOMP_HIGH_BAND
#define ADC_MOD_1_DCOMP_4_TRIG_COND     ADC_DCOMP_HIGH_BAND
#define ADC_MOD_1_DCOMP_5_TRIG_COND     ADC_DCOMP_HIGH_BAND
#define ADC_MOD_1_DCOMP_6_TRIG_COND     ADC_DCOMP_HIGH_BAND
#define ADC_MOD_1_DCOMP_7_TRIG_COND     ADC_DCOMP_HIGH_BAND

/*
 * select the mode of every digital comparator trigger
 * use the values of Adc_DCompCondTyp
 */
#define ADC_MOD_0_DCOMP_0_TRIG_MODE     ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_0_DCOMP_1_TRIG_MODE     ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_0_DCOMP_2_TRIG_MODE     ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_0_DCOMP_3_TRIG_MODE     ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_0_DCOMP_4_TRIG_MODE     ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_0_DCOMP_5_TRIG_MODE     ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_0_DCOMP_6_TRIG_MODE     ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_0_DCOMP_7_TRIG_MODE     ADC_DCOMP_MODE_HYS_ONCE

#define ADC_MOD_1_DCOMP_0_TRIG_MODE     ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_1_DCOMP_1_TRIG_MODE     ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_1_DCOMP_2_TRIG_MODE     ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_1_DCOMP_3_TRIG_MODE     ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_1_DCOMP_4_TRIG_MODE     ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_1_DCOMP_5_TRIG_MODE     ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_1_DCOMP_6_TRIG_MODE     ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_1_DCOMP_7_TRIG_MODE     ADC_DCOMP_MODE_HYS_ONCE


/*
 * same for digital comparator trigger macros but for interrupt
 * if condition and mode is matched for enabled interrupt
 * then event is generated from this digital comparator and sent on sequencer interrupt line determined for digital comparators
 */
#define ADC_MOD_0_DCOMP_INT_CTRL        0xFF
#define ADC_MOD_1_DCOMP_INT_CTRL        0xFF

#define ADC_MOD_0_DCOMP_0_INT_COND      ADC_DCOMP_HIGH_BAND
#define ADC_MOD_0_DCOMP_1_INT_COND      ADC_DCOMP_HIGH_BAND
#define ADC_MOD_0_DCOMP_2_INT_COND      ADC_DCOMP_HIGH_BAND
#define ADC_MOD_0_DCOMP_3_INT_COND      ADC_DCOMP_HIGH_BAND
#define ADC_MOD_0_DCOMP_4_INT_COND      ADC_DCOMP_HIGH_BAND
#define ADC_MOD_0_DCOMP_5_INT_COND      ADC_DCOMP_HIGH_BAND
#define ADC_MOD_0_DCOMP_6_INT_COND      ADC_DCOMP_HIGH_BAND
#define ADC_MOD_0_DCOMP_7_INT_COND      ADC_DCOMP_HIGH_BAND

#define ADC_MOD_1_DCOMP_0_INT_COND      ADC_DCOMP_HIGH_BAND
#define ADC_MOD_1_DCOMP_1_INT_COND      ADC_DCOMP_HIGH_BAND
#define ADC_MOD_1_DCOMP_2_INT_COND      ADC_DCOMP_HIGH_BAND
#define ADC_MOD_1_DCOMP_3_INT_COND      ADC_DCOMP_HIGH_BAND
#define ADC_MOD_1_DCOMP_4_INT_COND      ADC_DCOMP_HIGH_BAND
#define ADC_MOD_1_DCOMP_5_INT_COND      ADC_DCOMP_HIGH_BAND
#define ADC_MOD_1_DCOMP_6_INT_COND      ADC_DCOMP_HIGH_BAND
#define ADC_MOD_1_DCOMP_7_INT_COND      ADC_DCOMP_HIGH_BAND

#define ADC_MOD_0_DCOMP_0_INT_MODE      ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_0_DCOMP_1_INT_MODE      ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_0_DCOMP_2_INT_MODE      ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_0_DCOMP_3_INT_MODE      ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_0_DCOMP_4_INT_MODE      ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_0_DCOMP_5_INT_MODE      ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_0_DCOMP_6_INT_MODE      ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_0_DCOMP_7_INT_MODE      ADC_DCOMP_MODE_HYS_ONCE

#define ADC_MOD_1_DCOMP_0_INT_MODE      ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_1_DCOMP_1_INT_MODE      ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_1_DCOMP_2_INT_MODE      ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_1_DCOMP_3_INT_MODE      ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_1_DCOMP_4_INT_MODE      ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_1_DCOMP_5_INT_MODE      ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_1_DCOMP_6_INT_MODE      ADC_DCOMP_MODE_HYS_ONCE
#define ADC_MOD_1_DCOMP_7_INT_MODE      ADC_DCOMP_MODE_HYS_ONCE


/* set the lower range for digital comparators use values in range 0x000 ~ 0xFFF */
#define ADC_MOD_0_DCOMP_0_LO_RANGE      0x555
#define ADC_MOD_0_DCOMP_1_LO_RANGE      0x555
#define ADC_MOD_0_DCOMP_2_LO_RANGE      0x555
#define ADC_MOD_0_DCOMP_3_LO_RANGE      0x555
#define ADC_MOD_0_DCOMP_4_LO_RANGE      0x555
#define ADC_MOD_0_DCOMP_5_LO_RANGE      0x555
#define ADC_MOD_0_DCOMP_6_LO_RANGE      0x555
#define ADC_MOD_0_DCOMP_7_LO_RANGE      0x555

#define ADC_MOD_1_DCOMP_0_LO_RANGE      0x555
#define ADC_MOD_1_DCOMP_1_LO_RANGE      0x555
#define ADC_MOD_1_DCOMP_2_LO_RANGE      0x555
#define ADC_MOD_1_DCOMP_3_LO_RANGE      0x555
#define ADC_MOD_1_DCOMP_4_LO_RANGE      0x555
#define ADC_MOD_1_DCOMP_5_LO_RANGE      0x555
#define ADC_MOD_1_DCOMP_6_LO_RANGE      0x555
#define ADC_MOD_1_DCOMP_7_LO_RANGE      0x555


/* set the upper range for digital comparators use values in range 0x000 ~ 0xFFF */
#define ADC_MOD_0_DCOMP_0_UP_RANGE      0xAAA
#define ADC_MOD_0_DCOMP_1_UP_RANGE      0xAAA
#define ADC_MOD_0_DCOMP_2_UP_RANGE      0xAAA
#define ADC_MOD_0_DCOMP_3_UP_RANGE      0xAAA
#define ADC_MOD_0_DCOMP_4_UP_RANGE      0xAAA
#define ADC_MOD_0_DCOMP_5_UP_RANGE      0xAAA
#define ADC_MOD_0_DCOMP_6_UP_RANGE      0xAAA
#define ADC_MOD_0_DCOMP_7_UP_RANGE      0xAAA

#define ADC_MOD_1_DCOMP_0_UP_RANGE      0xAAA
#define ADC_MOD_1_DCOMP_1_UP_RANGE      0xAAA
#define ADC_MOD_1_DCOMP_2_UP_RANGE      0xAAA
#define ADC_MOD_1_DCOMP_3_UP_RANGE      0xAAA
#define ADC_MOD_1_DCOMP_4_UP_RANGE      0xAAA
#define ADC_MOD_1_DCOMP_5_UP_RANGE      0xAAA
#define ADC_MOD_1_DCOMP_6_UP_RANGE      0xAAA
#define ADC_MOD_1_DCOMP_7_UP_RANGE      0xAAA

/*********************************************************************************/


#endif /* ADC_CFG_H_ */
