/************************************************/
/*  Adc.c                                       */
/*  Created on: Dec 22, 2020                    */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/



#include "Adc.h"
#include "Adc_Private.h"


/*********************************************************************************/

/*
 * non privilege, synchronous, non-Reentrant function .
 * this function will initialize all ADC modules, according to ADC_Cfg.h file.
 * it will initialize clock, sample rate, interrupt mask, sample sequencer and digital comparators setting.
 * follow rules demonstrated in ADC_Cfg.h file to make proper initialization .
 * Mask will determine modules to be initiated according whether module bit in Mask is set or not
 * there're 3 modules 0,1, LSB is assigned to module0 and 2nd bit assigned to module1
 * don't initiate a module with disabled clock or fault exception will be generated */

void Adc_Init ( uint8 Mask )
{
    Adc_CtrlRegisterMap_Struct * TempPtr0 = NULL_PTR ;
    Adc_SequenRegisterMap_Struct * TempPtr1 = NULL_PTR ;
    volatile uint32 * TempPtr2 = NULL_PTR ;
    volatile uint32 * TempPtr3 = NULL_PTR ;
    uint32 Temp = 0 ;

    TempPtr0->Adc_ADCIM = 0x00 ;
    TempPtr0->Adc_ADCACTSS = 0x00 ;

    if( (Mask>>ADC_MODULE_0) & TRUE )
    {
        TempPtr0 = ADC_MOD_CTRL_BASE(ADC_MODULE_0) ;
        TempPtr2 = ADC_DCOMP_CTRL_ADDR(ADC_MODULE_0) ;
        TempPtr3 = ADC_DCOMP_RANGE_ADDR(ADC_MODULE_0) ;

        /*********************************************************************************/

        *(ADC_ADCCC_REG + ADC_MODULE_0*ADC_MODULE_OFFSET ) = ADC_MOD_0_CLK_SRC ;
        *(ADC_ADCPP_REG + ADC_MODULE_0*ADC_MODULE_OFFSET )  = ADC_SAMPLE_RATE_1M ;

        Temp =
                (ADC_MOD_0_SEQ_3_TRIG_SRC<<ADC_SEQUEN_FIELD_WIDTH*ADC_SEQUENCER_3) |
                (ADC_MOD_0_SEQ_2_TRIG_SRC<<ADC_SEQUEN_FIELD_WIDTH*ADC_SEQUENCER_2) |
                (ADC_MOD_0_SEQ_1_TRIG_SRC<<ADC_SEQUEN_FIELD_WIDTH*ADC_SEQUENCER_1) |
                (ADC_MOD_0_SEQ_2_TRIG_SRC<<ADC_SEQUEN_FIELD_WIDTH*ADC_SEQUENCER_0) ;
        TempPtr0->Adc_ADCEMUX = Temp ;

        Temp =
                (ADC_MOD_0_SEQ_3_TRIG_SRC<<ADC_PWM_GENERATOR_3) |
                (ADC_MOD_0_SEQ_2_TRIG_SRC<<ADC_PWM_GENERATOR_2) |
                (ADC_MOD_0_SEQ_1_TRIG_SRC<<ADC_PWM_GENERATOR_1) |
                (ADC_MOD_0_SEQ_2_TRIG_SRC<<ADC_PWM_GENERATOR_0) ;
        TempPtr0->Adc_ADCTSSEL = Temp ;


        Temp =
                (ADC_MOD_0_SEQ_3_PRIORITY<<ADC_SEQUEN_FIELD_WIDTH*ADC_SEQUENCER_3) |
                (ADC_MOD_0_SEQ_2_PRIORITY<<ADC_SEQUEN_FIELD_WIDTH*ADC_SEQUENCER_2) |
                (ADC_MOD_0_SEQ_1_PRIORITY<<ADC_SEQUEN_FIELD_WIDTH*ADC_SEQUENCER_1) |
                (ADC_MOD_0_SEQ_0_PRIORITY<<ADC_SEQUEN_FIELD_WIDTH*ADC_SEQUENCER_0) ;
        TempPtr0->Adc_ADCSSPRI = Temp ;

        TempPtr0->Adc_ADCSPC = ADC_MOD_0_PHASE_SHIFT ;
        TempPtr0->Adc_ADCSAC = ADC_MOD_0_AVG_FACTOR_PWR ;
        TempPtr0->Adc_ADCCTL = ADC_MOD_0_DITHER_CTRL << ADC_DITHER_BIT_POS ;

        /*********************************************************************************/

        TempPtr1 = ADC_SEQUEN_BASE(ADC_MODULE_0, ADC_SEQUENCER_0);

        Temp =
                (ADC_MOD_0_SEQ_0_SMP_7_SRC<<ADC_SAMPLE_7) |
                (ADC_MOD_0_SEQ_0_SMP_6_SRC<<ADC_SAMPLE_6) |
                (ADC_MOD_0_SEQ_0_SMP_5_SRC<<ADC_SAMPLE_5) |
                (ADC_MOD_0_SEQ_0_SMP_4_SRC<<ADC_SAMPLE_4) |
                (ADC_MOD_0_SEQ_0_SMP_3_SRC<<ADC_SAMPLE_3) |
                (ADC_MOD_0_SEQ_0_SMP_2_SRC<<ADC_SAMPLE_2) |
                (ADC_MOD_0_SEQ_0_SMP_1_SRC<<ADC_SAMPLE_1) |
                (ADC_MOD_0_SEQ_0_SMP_0_SRC<<ADC_SAMPLE_0) ;
        TempPtr1->Adc_ADCSSMUX = Temp ;

        Temp =
                (ADC_MOD_0_SEQ_0_TEMP_CTRL<<ADC_SEQ_TEMP_BIT_POS)   |
                (ADC_MOD_0_SEQ_0_EVENT_CTRL<<ADC_SEQ_EVENT_BIT_POS) |
                (ADC_MOD_0_SEQ_0_END_CTRL<<ADC_SEQ_END_BIT_POS)     |
                (ADC_MOD_0_SEQ_0_DIFF_CTRL<<ADC_SEQ_DIFF_BIT_POS)   ;
        TempPtr1->Adc_ADCSSCTL = Temp ;

        TempPtr1->Adc_ADCSSOP = ADC_MOD_0_SEQ_0_DEST_CTRL ;

        Temp =
                (ADC_MOD_0_SEQ_0_SMP_7_DCMP<<ADC_SAMPLE_7) |
                (ADC_MOD_0_SEQ_0_SMP_6_DCMP<<ADC_SAMPLE_6) |
                (ADC_MOD_0_SEQ_0_SMP_5_DCMP<<ADC_SAMPLE_5) |
                (ADC_MOD_0_SEQ_0_SMP_4_DCMP<<ADC_SAMPLE_4) |
                (ADC_MOD_0_SEQ_0_SMP_3_DCMP<<ADC_SAMPLE_3) |
                (ADC_MOD_0_SEQ_0_SMP_2_DCMP<<ADC_SAMPLE_2) |
                (ADC_MOD_0_SEQ_0_SMP_1_DCMP<<ADC_SAMPLE_1) |
                (ADC_MOD_0_SEQ_0_SMP_0_DCMP<<ADC_SAMPLE_0) ;
        TempPtr1->Adc_ADCSSDC = Temp ;

        /*********************************************************************************/

        TempPtr1 = ADC_SEQUEN_BASE(ADC_MODULE_0, ADC_SEQUENCER_1);

        Temp =

                (ADC_MOD_0_SEQ_1_SMP_3_SRC<<ADC_SAMPLE_3) |
                (ADC_MOD_0_SEQ_1_SMP_2_SRC<<ADC_SAMPLE_2) |
                (ADC_MOD_0_SEQ_1_SMP_1_SRC<<ADC_SAMPLE_1) |
                (ADC_MOD_0_SEQ_1_SMP_0_SRC<<ADC_SAMPLE_0) ;
        TempPtr1->Adc_ADCSSMUX = Temp ;

        Temp =
                (ADC_MOD_0_SEQ_1_TEMP_CTRL<<ADC_SEQ_TEMP_BIT_POS)   |
                (ADC_MOD_0_SEQ_1_EVENT_CTRL<<ADC_SEQ_EVENT_BIT_POS) |
                (ADC_MOD_0_SEQ_1_END_CTRL<<ADC_SEQ_END_BIT_POS)     |
                (ADC_MOD_0_SEQ_1_DIFF_CTRL<<ADC_SEQ_DIFF_BIT_POS)   ;
        TempPtr1->Adc_ADCSSCTL = Temp ;

        TempPtr1->Adc_ADCSSOP = ADC_MOD_0_SEQ_1_DEST_CTRL ;

        Temp =
                (ADC_MOD_0_SEQ_1_SMP_3_DCMP<<ADC_SAMPLE_3) |
                (ADC_MOD_0_SEQ_1_SMP_2_DCMP<<ADC_SAMPLE_2) |
                (ADC_MOD_0_SEQ_1_SMP_1_DCMP<<ADC_SAMPLE_1) |
                (ADC_MOD_0_SEQ_1_SMP_0_DCMP<<ADC_SAMPLE_0) ;
        TempPtr1->Adc_ADCSSDC = Temp ;

        /*********************************************************************************/

        TempPtr1 = ADC_SEQUEN_BASE(ADC_MODULE_0, ADC_SEQUENCER_2);

        Temp =

                (ADC_MOD_0_SEQ_2_SMP_3_SRC<<ADC_SAMPLE_3) |
                (ADC_MOD_0_SEQ_2_SMP_2_SRC<<ADC_SAMPLE_2) |
                (ADC_MOD_0_SEQ_2_SMP_1_SRC<<ADC_SAMPLE_1) |
                (ADC_MOD_0_SEQ_2_SMP_0_SRC<<ADC_SAMPLE_0) ;
        TempPtr1->Adc_ADCSSMUX = Temp ;

        Temp =
                (ADC_MOD_0_SEQ_2_TEMP_CTRL<<ADC_SEQ_TEMP_BIT_POS)   |
                (ADC_MOD_0_SEQ_2_EVENT_CTRL<<ADC_SEQ_EVENT_BIT_POS) |
                (ADC_MOD_0_SEQ_2_END_CTRL<<ADC_SEQ_END_BIT_POS)     |
                (ADC_MOD_0_SEQ_2_DIFF_CTRL<<ADC_SEQ_DIFF_BIT_POS)   ;
        TempPtr1->Adc_ADCSSCTL = Temp ;

        TempPtr1->Adc_ADCSSOP = ADC_MOD_0_SEQ_2_DEST_CTRL ;

        Temp =
                (ADC_MOD_0_SEQ_2_SMP_3_DCMP<<ADC_SAMPLE_3) |
                (ADC_MOD_0_SEQ_2_SMP_2_DCMP<<ADC_SAMPLE_2) |
                (ADC_MOD_0_SEQ_2_SMP_1_DCMP<<ADC_SAMPLE_1) |
                (ADC_MOD_0_SEQ_2_SMP_0_DCMP<<ADC_SAMPLE_0) ;
        TempPtr1->Adc_ADCSSDC = Temp ;

        /*********************************************************************************/

        TempPtr1 = ADC_SEQUEN_BASE(ADC_MODULE_0, ADC_SEQUENCER_3);

        TempPtr1->Adc_ADCSSMUX = ADC_MOD_0_SEQ_3_SMP_0_SRC ;

        Temp =
                (ADC_MOD_0_SEQ_3_TEMP_CTRL<<ADC_SEQ_TEMP_BIT_POS)   |
                (ADC_MOD_0_SEQ_3_EVENT_CTRL<<ADC_SEQ_EVENT_BIT_POS) |
                (ADC_MOD_0_SEQ_3_END_CTRL<<ADC_SEQ_END_BIT_POS)     |
                (ADC_MOD_0_SEQ_3_DIFF_CTRL<<ADC_SEQ_DIFF_BIT_POS)   ;
        TempPtr1->Adc_ADCSSCTL = Temp ;

        TempPtr1->Adc_ADCSSOP = ADC_MOD_0_SEQ_3_DEST_CTRL ;
        TempPtr1->Adc_ADCSSDC = ADC_MOD_0_SEQ_3_SMP_0_DCMP ;

        /*********************************************************************************/

        Temp =
                (((ADC_MOD_0_DCOMP_TRIG_CTRL>>ADC_DIGITAL_COMP_0) & TRUE) << ADC_DCOMP_TRIG_EN_POS)   |
                (ADC_MOD_0_DCOMP_0_TRIG_COND<<ADC_DCOMP_TRIG_COND_POS) |
                (ADC_MOD_0_DCOMP_0_TRIG_MODE<<ADC_DCOMP_TRIG_MODE_POS) |
                (((ADC_MOD_0_DCOMP_INT_CTRL>>ADC_DIGITAL_COMP_0) & TRUE) << ADC_DCOMP_INT_EN_POS)       |
                (ADC_MOD_0_DCOMP_0_INT_COND<<ADC_DCOMP_INT_COND_POS)   |
                (ADC_MOD_0_DCOMP_0_INT_COND<<ADC_DCOMP_INT_MODE_POS)   ;
        TempPtr2[ADC_DIGITAL_COMP_0] = Temp ;
        TempPtr3[ADC_DIGITAL_COMP_0] = (ADC_MOD_0_DCOMP_0_LO_RANGE << ADC_DCOMP_LOW_RANGE_POS) | (ADC_MOD_0_DCOMP_0_UP_RANGE << ADC_DCOMP_UP_RANGE_POS) ;


        Temp =
                (((ADC_MOD_0_DCOMP_TRIG_CTRL>>ADC_DIGITAL_COMP_1) & TRUE) << ADC_DCOMP_TRIG_EN_POS)   |
                (ADC_MOD_0_DCOMP_1_TRIG_COND<<ADC_DCOMP_TRIG_COND_POS) |
                (ADC_MOD_0_DCOMP_1_TRIG_MODE<<ADC_DCOMP_TRIG_MODE_POS) |
                (((ADC_MOD_0_DCOMP_INT_CTRL>>ADC_DIGITAL_COMP_1) & TRUE) << ADC_DCOMP_INT_EN_POS)       |
                (ADC_MOD_0_DCOMP_1_INT_COND<<ADC_DCOMP_INT_COND_POS)   |
                (ADC_MOD_0_DCOMP_1_INT_COND<<ADC_DCOMP_INT_MODE_POS)   ;
        TempPtr2[ADC_DIGITAL_COMP_1] = Temp ;
        TempPtr3[ADC_DIGITAL_COMP_1] = (ADC_MOD_0_DCOMP_1_LO_RANGE << ADC_DCOMP_LOW_RANGE_POS) | (ADC_MOD_0_DCOMP_1_UP_RANGE << ADC_DCOMP_UP_RANGE_POS) ;

        Temp =
                (((ADC_MOD_0_DCOMP_TRIG_CTRL>>ADC_DIGITAL_COMP_2) & TRUE) << ADC_DCOMP_TRIG_EN_POS)   |
                (ADC_MOD_0_DCOMP_2_TRIG_COND<<ADC_DCOMP_TRIG_COND_POS) |
                (ADC_MOD_0_DCOMP_2_TRIG_MODE<<ADC_DCOMP_TRIG_MODE_POS) |
                (((ADC_MOD_0_DCOMP_INT_CTRL>>ADC_DIGITAL_COMP_2) & TRUE) << ADC_DCOMP_INT_EN_POS)       |
                (ADC_MOD_0_DCOMP_2_INT_COND<<ADC_DCOMP_INT_COND_POS)   |
                (ADC_MOD_0_DCOMP_2_INT_COND<<ADC_DCOMP_INT_MODE_POS)   ;
        TempPtr2[ADC_DIGITAL_COMP_2] = Temp ;
        TempPtr3[ADC_DIGITAL_COMP_2] = (ADC_MOD_0_DCOMP_2_LO_RANGE << ADC_DCOMP_LOW_RANGE_POS) | (ADC_MOD_0_DCOMP_2_UP_RANGE << ADC_DCOMP_UP_RANGE_POS) ;

        Temp =
                (((ADC_MOD_0_DCOMP_TRIG_CTRL>>ADC_DIGITAL_COMP_3) & TRUE) << ADC_DCOMP_TRIG_EN_POS)   |
                (ADC_MOD_0_DCOMP_3_TRIG_COND<<ADC_DCOMP_TRIG_COND_POS) |
                (ADC_MOD_0_DCOMP_3_TRIG_MODE<<ADC_DCOMP_TRIG_MODE_POS) |
                (((ADC_MOD_0_DCOMP_INT_CTRL>>ADC_DIGITAL_COMP_3) & TRUE) << ADC_DCOMP_INT_EN_POS)       |
                (ADC_MOD_0_DCOMP_3_INT_COND<<ADC_DCOMP_INT_COND_POS)   |
                (ADC_MOD_0_DCOMP_3_INT_COND<<ADC_DCOMP_INT_MODE_POS)   ;
        TempPtr2[ADC_DIGITAL_COMP_3] = Temp ;
        TempPtr3[ADC_DIGITAL_COMP_3] = (ADC_MOD_0_DCOMP_3_LO_RANGE << ADC_DCOMP_LOW_RANGE_POS) | (ADC_MOD_0_DCOMP_3_UP_RANGE << ADC_DCOMP_UP_RANGE_POS) ;

        Temp =
                (((ADC_MOD_0_DCOMP_TRIG_CTRL>>ADC_DIGITAL_COMP_4) & TRUE) << ADC_DCOMP_TRIG_EN_POS)   |
                (ADC_MOD_0_DCOMP_4_TRIG_COND<<ADC_DCOMP_TRIG_COND_POS) |
                (ADC_MOD_0_DCOMP_4_TRIG_MODE<<ADC_DCOMP_TRIG_MODE_POS) |
                (((ADC_MOD_0_DCOMP_INT_CTRL>>ADC_DIGITAL_COMP_4) & TRUE) << ADC_DCOMP_INT_EN_POS)       |
                (ADC_MOD_0_DCOMP_4_INT_COND<<ADC_DCOMP_INT_COND_POS)   |
                (ADC_MOD_0_DCOMP_4_INT_COND<<ADC_DCOMP_INT_MODE_POS)   ;
        TempPtr2[ADC_DIGITAL_COMP_4] = Temp ;
        TempPtr3[ADC_DIGITAL_COMP_4] = (ADC_MOD_0_DCOMP_4_LO_RANGE << ADC_DCOMP_LOW_RANGE_POS) | (ADC_MOD_0_DCOMP_4_UP_RANGE << ADC_DCOMP_UP_RANGE_POS) ;

        Temp =
                (((ADC_MOD_0_DCOMP_TRIG_CTRL>>ADC_DIGITAL_COMP_5) & TRUE) << ADC_DCOMP_TRIG_EN_POS)   |
                (ADC_MOD_0_DCOMP_5_TRIG_COND<<ADC_DCOMP_TRIG_COND_POS) |
                (ADC_MOD_0_DCOMP_5_TRIG_MODE<<ADC_DCOMP_TRIG_MODE_POS) |
                (((ADC_MOD_0_DCOMP_INT_CTRL>>ADC_DIGITAL_COMP_5) & TRUE) << ADC_DCOMP_INT_EN_POS)       |
                (ADC_MOD_0_DCOMP_5_INT_COND<<ADC_DCOMP_INT_COND_POS)   |
                (ADC_MOD_0_DCOMP_5_INT_COND<<ADC_DCOMP_INT_MODE_POS)   ;
        TempPtr2[ADC_DIGITAL_COMP_5] = Temp ;
        TempPtr3[ADC_DIGITAL_COMP_5] = (ADC_MOD_0_DCOMP_5_LO_RANGE << ADC_DCOMP_LOW_RANGE_POS) | (ADC_MOD_0_DCOMP_5_UP_RANGE << ADC_DCOMP_UP_RANGE_POS) ;

        Temp =
                (((ADC_MOD_0_DCOMP_TRIG_CTRL>>ADC_DIGITAL_COMP_6) & TRUE) << ADC_DCOMP_TRIG_EN_POS)   |
                (ADC_MOD_0_DCOMP_6_TRIG_COND<<ADC_DCOMP_TRIG_COND_POS) |
                (ADC_MOD_0_DCOMP_6_TRIG_MODE<<ADC_DCOMP_TRIG_MODE_POS) |
                (((ADC_MOD_0_DCOMP_INT_CTRL>>ADC_DIGITAL_COMP_6) & TRUE) << ADC_DCOMP_INT_EN_POS)       |
                (ADC_MOD_0_DCOMP_6_INT_COND<<ADC_DCOMP_INT_COND_POS)   |
                (ADC_MOD_0_DCOMP_6_INT_COND<<ADC_DCOMP_INT_MODE_POS)   ;
        TempPtr2[ADC_DIGITAL_COMP_6] = Temp ;
        TempPtr3[ADC_DIGITAL_COMP_6] = (ADC_MOD_0_DCOMP_6_LO_RANGE << ADC_DCOMP_LOW_RANGE_POS) | (ADC_MOD_0_DCOMP_6_UP_RANGE << ADC_DCOMP_UP_RANGE_POS) ;

        Temp =
                (((ADC_MOD_0_DCOMP_TRIG_CTRL>>ADC_DIGITAL_COMP_7) & TRUE) << ADC_DCOMP_TRIG_EN_POS)   |
                (ADC_MOD_0_DCOMP_7_TRIG_COND<<ADC_DCOMP_TRIG_COND_POS) |
                (ADC_MOD_0_DCOMP_7_TRIG_MODE<<ADC_DCOMP_TRIG_MODE_POS) |
                (((ADC_MOD_0_DCOMP_INT_CTRL>>ADC_DIGITAL_COMP_7) & TRUE) << ADC_DCOMP_INT_EN_POS)       |
                (ADC_MOD_0_DCOMP_7_INT_COND<<ADC_DCOMP_INT_COND_POS)   |
                (ADC_MOD_0_DCOMP_7_INT_COND<<ADC_DCOMP_INT_MODE_POS)   ;
        TempPtr2[ADC_DIGITAL_COMP_7] = Temp ;
        TempPtr3[ADC_DIGITAL_COMP_7] = (ADC_MOD_0_DCOMP_7_LO_RANGE << ADC_DCOMP_LOW_RANGE_POS) | (ADC_MOD_0_DCOMP_7_UP_RANGE << ADC_DCOMP_UP_RANGE_POS);

        /*********************************************************************************/

        TempPtr0->Adc_ADCDCISC = ADC_DCOMP_MASK ;
        TempPtr0->Adc_ADCOSTAT = ADC_SEQUEN_MASK ;
        TempPtr0->Adc_ADCUSTAT = ADC_SEQUEN_MASK ;
        TempPtr0->Adc_ADCISC = ADC_SEQUEN_MASK ;
        TempPtr0->Adc_ADCIM = ADC_MOD_1_SEQ_INT_CTRL | (ADC_MOD_1_DCOM_INT_CTRL << (ADC_MOD_1_DCOMP_INT_LINE+ADC_DCOMP_INT_BIT_POS)) ;
        TempPtr0->Adc_ADCACTSS = ADC_MOD_0_SEQ_CTRL ;

    }
    else
    {
    }

    if( (Mask>>ADC_MODULE_1) & TRUE )
    {
        TempPtr0 = ADC_MOD_CTRL_BASE(ADC_MODULE_1) ;
        TempPtr2 = ADC_DCOMP_CTRL_ADDR(ADC_MODULE_1) ;
        TempPtr3 = ADC_DCOMP_RANGE_ADDR(ADC_MODULE_1) ;

        /*********************************************************************************/

        *(ADC_ADCCC_REG + ADC_MODULE_1*ADC_MODULE_OFFSET ) = ADC_MOD_1_CLK_SRC ;
        *(ADC_ADCPP_REG + ADC_MODULE_1*ADC_MODULE_OFFSET ) = ADC_SAMPLE_RATE_1M ;

        TempPtr0->Adc_ADCACTSS = ADC_MOD_1_SEQ_CTRL ;

        Temp =
                (ADC_MOD_1_SEQ_3_TRIG_SRC<<ADC_SEQUEN_FIELD_WIDTH*ADC_SEQUENCER_3) |
                (ADC_MOD_1_SEQ_2_TRIG_SRC<<ADC_SEQUEN_FIELD_WIDTH*ADC_SEQUENCER_2) |
                (ADC_MOD_1_SEQ_1_TRIG_SRC<<ADC_SEQUEN_FIELD_WIDTH*ADC_SEQUENCER_1) |
                (ADC_MOD_1_SEQ_2_TRIG_SRC<<ADC_SEQUEN_FIELD_WIDTH*ADC_SEQUENCER_0) ;
        TempPtr0->Adc_ADCEMUX = Temp ;

        Temp =
                (ADC_MOD_1_SEQ_3_TRIG_SRC<<ADC_PWM_GENERATOR_3) |
                (ADC_MOD_1_SEQ_2_TRIG_SRC<<ADC_PWM_GENERATOR_2) |
                (ADC_MOD_1_SEQ_1_TRIG_SRC<<ADC_PWM_GENERATOR_1) |
                (ADC_MOD_1_SEQ_2_TRIG_SRC<<ADC_PWM_GENERATOR_0) ;
        TempPtr0->Adc_ADCTSSEL = Temp ;


        Temp =
                (ADC_MOD_1_SEQ_3_PRIORITY<<ADC_SEQUEN_FIELD_WIDTH*ADC_SEQUENCER_3) |
                (ADC_MOD_1_SEQ_2_PRIORITY<<ADC_SEQUEN_FIELD_WIDTH*ADC_SEQUENCER_2) |
                (ADC_MOD_1_SEQ_1_PRIORITY<<ADC_SEQUEN_FIELD_WIDTH*ADC_SEQUENCER_1) |
                (ADC_MOD_1_SEQ_0_PRIORITY<<ADC_SEQUEN_FIELD_WIDTH*ADC_SEQUENCER_0) ;
        TempPtr0->Adc_ADCSSPRI = Temp ;

        TempPtr0->Adc_ADCSPC = ADC_MOD_1_PHASE_SHIFT ;
        TempPtr0->Adc_ADCSAC = ADC_MOD_1_AVG_FACTOR_PWR ;
        TempPtr0->Adc_ADCCTL = ADC_MOD_1_DITHER_CTRL << ADC_DITHER_BIT_POS ;

        /*********************************************************************************/

        TempPtr1 = ADC_SEQUEN_BASE(ADC_MODULE_1, ADC_SEQUENCER_0);

        Temp =
                (ADC_MOD_1_SEQ_0_SMP_7_SRC<<ADC_SAMPLE_7) |
                (ADC_MOD_1_SEQ_0_SMP_6_SRC<<ADC_SAMPLE_6) |
                (ADC_MOD_1_SEQ_0_SMP_5_SRC<<ADC_SAMPLE_5) |
                (ADC_MOD_1_SEQ_0_SMP_4_SRC<<ADC_SAMPLE_4) |
                (ADC_MOD_1_SEQ_0_SMP_3_SRC<<ADC_SAMPLE_3) |
                (ADC_MOD_1_SEQ_0_SMP_2_SRC<<ADC_SAMPLE_2) |
                (ADC_MOD_1_SEQ_0_SMP_1_SRC<<ADC_SAMPLE_1) |
                (ADC_MOD_1_SEQ_0_SMP_0_SRC<<ADC_SAMPLE_0) ;
        TempPtr1->Adc_ADCSSMUX = Temp ;

        Temp =
                (ADC_MOD_1_SEQ_0_TEMP_CTRL<<ADC_SEQ_TEMP_BIT_POS)   |
                (ADC_MOD_1_SEQ_0_EVENT_CTRL<<ADC_SEQ_EVENT_BIT_POS) |
                (ADC_MOD_1_SEQ_0_END_CTRL<<ADC_SEQ_END_BIT_POS)     |
                (ADC_MOD_1_SEQ_0_DIFF_CTRL<<ADC_SEQ_DIFF_BIT_POS)   ;
        TempPtr1->Adc_ADCSSCTL = Temp ;

        TempPtr1->Adc_ADCSSOP = ADC_MOD_1_SEQ_0_DEST_CTRL ;

        Temp =
                (ADC_MOD_1_SEQ_0_SMP_7_DCMP<<ADC_SAMPLE_7) |
                (ADC_MOD_1_SEQ_0_SMP_6_DCMP<<ADC_SAMPLE_6) |
                (ADC_MOD_1_SEQ_0_SMP_5_DCMP<<ADC_SAMPLE_5) |
                (ADC_MOD_1_SEQ_0_SMP_4_DCMP<<ADC_SAMPLE_4) |
                (ADC_MOD_1_SEQ_0_SMP_3_DCMP<<ADC_SAMPLE_3) |
                (ADC_MOD_1_SEQ_0_SMP_2_DCMP<<ADC_SAMPLE_2) |
                (ADC_MOD_1_SEQ_0_SMP_1_DCMP<<ADC_SAMPLE_1) |
                (ADC_MOD_1_SEQ_0_SMP_0_DCMP<<ADC_SAMPLE_0) ;
        TempPtr1->Adc_ADCSSDC = Temp ;

        /*********************************************************************************/

        TempPtr1 = ADC_SEQUEN_BASE(ADC_MODULE_1, ADC_SEQUENCER_1);

        Temp =

                (ADC_MOD_1_SEQ_1_SMP_3_SRC<<ADC_SAMPLE_3) |
                (ADC_MOD_1_SEQ_1_SMP_2_SRC<<ADC_SAMPLE_2) |
                (ADC_MOD_1_SEQ_1_SMP_1_SRC<<ADC_SAMPLE_1) |
                (ADC_MOD_1_SEQ_1_SMP_0_SRC<<ADC_SAMPLE_0) ;
        TempPtr1->Adc_ADCSSMUX = Temp ;

        Temp =
                (ADC_MOD_1_SEQ_1_TEMP_CTRL<<ADC_SEQ_TEMP_BIT_POS)   |
                (ADC_MOD_1_SEQ_1_EVENT_CTRL<<ADC_SEQ_EVENT_BIT_POS) |
                (ADC_MOD_1_SEQ_1_END_CTRL<<ADC_SEQ_END_BIT_POS)     |
                (ADC_MOD_1_SEQ_1_DIFF_CTRL<<ADC_SEQ_DIFF_BIT_POS)   ;
        TempPtr1->Adc_ADCSSCTL = Temp ;

        TempPtr1->Adc_ADCSSOP = ADC_MOD_1_SEQ_1_DEST_CTRL ;

        Temp =
                (ADC_MOD_1_SEQ_1_SMP_3_DCMP<<ADC_SAMPLE_3) |
                (ADC_MOD_1_SEQ_1_SMP_2_DCMP<<ADC_SAMPLE_2) |
                (ADC_MOD_1_SEQ_1_SMP_1_DCMP<<ADC_SAMPLE_1) |
                (ADC_MOD_1_SEQ_1_SMP_0_DCMP<<ADC_SAMPLE_0) ;
        TempPtr1->Adc_ADCSSDC = Temp ;

        /*********************************************************************************/

        TempPtr1 = ADC_SEQUEN_BASE(ADC_MODULE_1, ADC_SEQUENCER_2);

        Temp =

                (ADC_MOD_1_SEQ_2_SMP_3_SRC<<ADC_SAMPLE_3) |
                (ADC_MOD_1_SEQ_2_SMP_2_SRC<<ADC_SAMPLE_2) |
                (ADC_MOD_1_SEQ_2_SMP_1_SRC<<ADC_SAMPLE_1) |
                (ADC_MOD_1_SEQ_2_SMP_0_SRC<<ADC_SAMPLE_0) ;
        TempPtr1->Adc_ADCSSMUX = Temp ;

        Temp =
                (ADC_MOD_1_SEQ_2_TEMP_CTRL<<ADC_SEQ_TEMP_BIT_POS)   |
                (ADC_MOD_1_SEQ_2_EVENT_CTRL<<ADC_SEQ_EVENT_BIT_POS) |
                (ADC_MOD_1_SEQ_2_END_CTRL<<ADC_SEQ_END_BIT_POS)     |
                (ADC_MOD_1_SEQ_2_DIFF_CTRL<<ADC_SEQ_DIFF_BIT_POS)   ;
        TempPtr1->Adc_ADCSSCTL = Temp ;

        TempPtr1->Adc_ADCSSOP = ADC_MOD_1_SEQ_2_DEST_CTRL ;

        Temp =
                (ADC_MOD_1_SEQ_2_SMP_3_DCMP<<ADC_SAMPLE_3) |
                (ADC_MOD_1_SEQ_2_SMP_2_DCMP<<ADC_SAMPLE_2) |
                (ADC_MOD_1_SEQ_2_SMP_1_DCMP<<ADC_SAMPLE_1) |
                (ADC_MOD_1_SEQ_2_SMP_0_DCMP<<ADC_SAMPLE_0) ;
        TempPtr1->Adc_ADCSSDC = Temp ;

        /*********************************************************************************/

        TempPtr1 = ADC_SEQUEN_BASE(ADC_MODULE_1, ADC_SEQUENCER_3);

        TempPtr1->Adc_ADCSSMUX = ADC_MOD_1_SEQ_3_SMP_0_SRC ;

        Temp =
                (ADC_MOD_1_SEQ_3_TEMP_CTRL<<ADC_SEQ_TEMP_BIT_POS)   |
                (ADC_MOD_1_SEQ_3_EVENT_CTRL<<ADC_SEQ_EVENT_BIT_POS) |
                (ADC_MOD_1_SEQ_3_END_CTRL<<ADC_SEQ_END_BIT_POS)     |
                (ADC_MOD_1_SEQ_3_DIFF_CTRL<<ADC_SEQ_DIFF_BIT_POS)   ;
        TempPtr1->Adc_ADCSSCTL = Temp ;

        TempPtr1->Adc_ADCSSOP = ADC_MOD_1_SEQ_3_DEST_CTRL ;
        TempPtr1->Adc_ADCSSDC = ADC_MOD_1_SEQ_3_SMP_0_DCMP ;

        /*********************************************************************************/

        Temp =
                (((ADC_MOD_1_DCOMP_TRIG_CTRL>>ADC_DIGITAL_COMP_0) & TRUE) << ADC_DCOMP_TRIG_EN_POS)   |
                (ADC_MOD_1_DCOMP_0_TRIG_COND<<ADC_DCOMP_TRIG_COND_POS) |
                (ADC_MOD_1_DCOMP_0_TRIG_MODE<<ADC_DCOMP_TRIG_MODE_POS) |
                (((ADC_MOD_1_DCOMP_INT_CTRL>>ADC_DIGITAL_COMP_0) & TRUE) << ADC_DCOMP_INT_EN_POS)       |
                (ADC_MOD_1_DCOMP_0_INT_COND<<ADC_DCOMP_INT_COND_POS)   |
                (ADC_MOD_1_DCOMP_0_INT_COND<<ADC_DCOMP_INT_MODE_POS)   ;
        TempPtr2[ADC_DIGITAL_COMP_0] = Temp ;
        TempPtr3[ADC_DIGITAL_COMP_0] = (ADC_MOD_1_DCOMP_0_LO_RANGE << ADC_DCOMP_LOW_RANGE_POS) | (ADC_MOD_1_DCOMP_0_UP_RANGE << ADC_DCOMP_UP_RANGE_POS) ;


        Temp =
                (((ADC_MOD_1_DCOMP_TRIG_CTRL>>ADC_DIGITAL_COMP_1) & TRUE) << ADC_DCOMP_TRIG_EN_POS)   |
                (ADC_MOD_1_DCOMP_1_TRIG_COND<<ADC_DCOMP_TRIG_COND_POS) |
                (ADC_MOD_1_DCOMP_1_TRIG_MODE<<ADC_DCOMP_TRIG_MODE_POS) |
                (((ADC_MOD_1_DCOMP_INT_CTRL>>ADC_DIGITAL_COMP_1) & TRUE) << ADC_DCOMP_INT_EN_POS)       |
                (ADC_MOD_1_DCOMP_1_INT_COND<<ADC_DCOMP_INT_COND_POS)   |
                (ADC_MOD_1_DCOMP_1_INT_COND<<ADC_DCOMP_INT_MODE_POS)   ;
        TempPtr2[ADC_DIGITAL_COMP_1] = Temp ;
        TempPtr3[ADC_DIGITAL_COMP_1] = (ADC_MOD_1_DCOMP_1_LO_RANGE << ADC_DCOMP_LOW_RANGE_POS) | (ADC_MOD_1_DCOMP_1_UP_RANGE << ADC_DCOMP_UP_RANGE_POS) ;

        Temp =
                (((ADC_MOD_1_DCOMP_TRIG_CTRL>>ADC_DIGITAL_COMP_2) & TRUE) << ADC_DCOMP_TRIG_EN_POS)   |
                (ADC_MOD_1_DCOMP_2_TRIG_COND<<ADC_DCOMP_TRIG_COND_POS) |
                (ADC_MOD_1_DCOMP_2_TRIG_MODE<<ADC_DCOMP_TRIG_MODE_POS) |
                (((ADC_MOD_1_DCOMP_INT_CTRL>>ADC_DIGITAL_COMP_2) & TRUE) << ADC_DCOMP_INT_EN_POS)       |
                (ADC_MOD_1_DCOMP_2_INT_COND<<ADC_DCOMP_INT_COND_POS)   |
                (ADC_MOD_1_DCOMP_2_INT_COND<<ADC_DCOMP_INT_MODE_POS)   ;
        TempPtr2[ADC_DIGITAL_COMP_2] = Temp ;
        TempPtr3[ADC_DIGITAL_COMP_2] = (ADC_MOD_1_DCOMP_2_LO_RANGE << ADC_DCOMP_LOW_RANGE_POS) | (ADC_MOD_1_DCOMP_2_UP_RANGE << ADC_DCOMP_UP_RANGE_POS) ;

        Temp =
                (((ADC_MOD_1_DCOMP_TRIG_CTRL>>ADC_DIGITAL_COMP_3) & TRUE) << ADC_DCOMP_TRIG_EN_POS)   |
                (ADC_MOD_1_DCOMP_3_TRIG_COND<<ADC_DCOMP_TRIG_COND_POS) |
                (ADC_MOD_1_DCOMP_3_TRIG_MODE<<ADC_DCOMP_TRIG_MODE_POS) |
                (((ADC_MOD_1_DCOMP_INT_CTRL>>ADC_DIGITAL_COMP_3) & TRUE) << ADC_DCOMP_INT_EN_POS)       |
                (ADC_MOD_1_DCOMP_3_INT_COND<<ADC_DCOMP_INT_COND_POS)   |
                (ADC_MOD_1_DCOMP_3_INT_COND<<ADC_DCOMP_INT_MODE_POS)   ;
        TempPtr2[ADC_DIGITAL_COMP_3] = Temp ;
        TempPtr3[ADC_DIGITAL_COMP_3] = (ADC_MOD_1_DCOMP_3_LO_RANGE << ADC_DCOMP_LOW_RANGE_POS) | (ADC_MOD_1_DCOMP_3_UP_RANGE << ADC_DCOMP_UP_RANGE_POS) ;

        Temp =
                (((ADC_MOD_1_DCOMP_TRIG_CTRL>>ADC_DIGITAL_COMP_4) & TRUE) << ADC_DCOMP_TRIG_EN_POS)   |
                (ADC_MOD_1_DCOMP_4_TRIG_COND<<ADC_DCOMP_TRIG_COND_POS) |
                (ADC_MOD_1_DCOMP_4_TRIG_MODE<<ADC_DCOMP_TRIG_MODE_POS) |
                (((ADC_MOD_1_DCOMP_INT_CTRL>>ADC_DIGITAL_COMP_4) & TRUE) << ADC_DCOMP_INT_EN_POS)       |
                (ADC_MOD_1_DCOMP_4_INT_COND<<ADC_DCOMP_INT_COND_POS)   |
                (ADC_MOD_1_DCOMP_4_INT_COND<<ADC_DCOMP_INT_MODE_POS)   ;
        TempPtr2[ADC_DIGITAL_COMP_4] = Temp ;
        TempPtr3[ADC_DIGITAL_COMP_4] = (ADC_MOD_1_DCOMP_4_LO_RANGE << ADC_DCOMP_LOW_RANGE_POS) | (ADC_MOD_1_DCOMP_4_UP_RANGE << ADC_DCOMP_UP_RANGE_POS) ;

        Temp =
                (((ADC_MOD_1_DCOMP_TRIG_CTRL>>ADC_DIGITAL_COMP_5) & TRUE) << ADC_DCOMP_TRIG_EN_POS)   |
                (ADC_MOD_1_DCOMP_5_TRIG_COND<<ADC_DCOMP_TRIG_COND_POS) |
                (ADC_MOD_1_DCOMP_5_TRIG_MODE<<ADC_DCOMP_TRIG_MODE_POS) |
                (((ADC_MOD_1_DCOMP_INT_CTRL>>ADC_DIGITAL_COMP_5) & TRUE) << ADC_DCOMP_INT_EN_POS)       |
                (ADC_MOD_1_DCOMP_5_INT_COND<<ADC_DCOMP_INT_COND_POS)   |
                (ADC_MOD_1_DCOMP_5_INT_COND<<ADC_DCOMP_INT_MODE_POS)   ;
        TempPtr2[ADC_DIGITAL_COMP_5] = Temp ;
        TempPtr3[ADC_DIGITAL_COMP_5] = (ADC_MOD_1_DCOMP_5_LO_RANGE << ADC_DCOMP_LOW_RANGE_POS) | (ADC_MOD_1_DCOMP_5_UP_RANGE << ADC_DCOMP_UP_RANGE_POS) ;

        Temp =
                (((ADC_MOD_1_DCOMP_TRIG_CTRL>>ADC_DIGITAL_COMP_6) & TRUE) << ADC_DCOMP_TRIG_EN_POS)   |
                (ADC_MOD_1_DCOMP_6_TRIG_COND<<ADC_DCOMP_TRIG_COND_POS) |
                (ADC_MOD_1_DCOMP_6_TRIG_MODE<<ADC_DCOMP_TRIG_MODE_POS) |
                (((ADC_MOD_1_DCOMP_INT_CTRL>>ADC_DIGITAL_COMP_6) & TRUE) << ADC_DCOMP_INT_EN_POS)       |
                (ADC_MOD_1_DCOMP_6_INT_COND<<ADC_DCOMP_INT_COND_POS)   |
                (ADC_MOD_1_DCOMP_6_INT_COND<<ADC_DCOMP_INT_MODE_POS)   ;
        TempPtr2[ADC_DIGITAL_COMP_6] = Temp ;
        TempPtr3[ADC_DIGITAL_COMP_6] = (ADC_MOD_1_DCOMP_6_LO_RANGE << ADC_DCOMP_LOW_RANGE_POS) | (ADC_MOD_1_DCOMP_6_UP_RANGE << ADC_DCOMP_UP_RANGE_POS) ;

        Temp =
                (((ADC_MOD_1_DCOMP_TRIG_CTRL>>ADC_DIGITAL_COMP_7) & TRUE) << ADC_DCOMP_TRIG_EN_POS)   |
                (ADC_MOD_1_DCOMP_7_TRIG_COND<<ADC_DCOMP_TRIG_COND_POS) |
                (ADC_MOD_1_DCOMP_7_TRIG_MODE<<ADC_DCOMP_TRIG_MODE_POS) |
                (((ADC_MOD_1_DCOMP_INT_CTRL>>ADC_DIGITAL_COMP_7) & TRUE) << ADC_DCOMP_INT_EN_POS)       |
                (ADC_MOD_1_DCOMP_7_INT_COND<<ADC_DCOMP_INT_COND_POS)   |
                (ADC_MOD_1_DCOMP_7_INT_COND<<ADC_DCOMP_INT_MODE_POS)   ;
        TempPtr2[ADC_DIGITAL_COMP_7] = Temp ;
        TempPtr3[ADC_DIGITAL_COMP_7] = (ADC_MOD_1_DCOMP_7_LO_RANGE << ADC_DCOMP_LOW_RANGE_POS) | (ADC_MOD_1_DCOMP_7_UP_RANGE << ADC_DCOMP_UP_RANGE_POS);

        /*********************************************************************************/

        TempPtr0->Adc_ADCDCISC = ADC_DCOMP_MASK ;
        TempPtr0->Adc_ADCOSTAT = ADC_SEQUEN_MASK ;
        TempPtr0->Adc_ADCUSTAT = ADC_SEQUEN_MASK ;
        TempPtr0->Adc_ADCISC = ADC_SEQUEN_MASK ;
        TempPtr0->Adc_ADCIM = ADC_MOD_1_SEQ_INT_CTRL | (ADC_MOD_1_DCOM_INT_CTRL << (ADC_MOD_1_DCOMP_INT_LINE+ADC_DCOMP_INT_BIT_POS)) ;
        TempPtr0->Adc_ADCACTSS = ADC_MOD_1_SEQ_CTRL ;

    }
    else
    {
    }

    return ;
}

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

boolean Adc_BusyState ( Adc_ModuleType ModuleId )
{
    return ((ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCACTSS) >> ADC_BUSY_FLAG_OFFSET) & TRUE ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will enable sequencers specified by SequencerId,
 * in ADC module specified by ModuleId .
 * initiate sequencer setting before enabling it .
 * when sequencer is enabled then it will start sampling according to its setting,
 * whenever right trigger for sequencer occur .
 */

void Adc_SequencerEnable ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId)
{

    (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCACTSS) |= TRUE<<SequencerId ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will disable sequencers specified by SequencerId,
 * in ADC module specified by ModuleId .
 * whenever sequencer is disabled it will stop operation and won't continue after it enabled again .
 */

void Adc_SequencerDisable ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId)
{
    (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCACTSS) &= ~(TRUE<<SequencerId) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will return the event state of interrupt specified by InterruptID in module of ModuleId .
 * if return = TRUE then event occurred and if interrupt is enabled,
 * then interrupt signal would be generated to NVIC .
 * if return = FALSE then event didn't happen yet .
 * this function is just responsible for events from sample sequencer not digital comparators too .
 */

boolean Adc_GetSequencerEvent ( Adc_ModuleType ModuleId, Adc_InterruptType InterruptID )
{
    return ((ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCRIS) >> InterruptID) & TRUE ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function is same like Adc_GetSequencerInterrupt but it will return all interrupts states .
 * it will return a byte and every bit in the lowest nibble will represent state of one interrupt
 * if bit is set then corresponding event occurred and interrupt enabled and its signal is send to NVIC .
 * if not then corresponding interrupt is disabled or event didn't occur .
 */

uint8 Adc_GetAllSequencerEvents ( Adc_ModuleType ModuleId)
{
    return (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCRIS)  & ADC_SEQUEN_MASK ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will return the state of interrupt specified by InterruptID in module of ModuleId .
 * if return = TRUE then event occurred and interrupt is enabled,
 * then interrupt signal would be generated to NVIC .
 * if return = FALSE then event didn't happen yet or interrupt is disabled .
 * this function is just responsible for events from sample sequencer not digital comparators too .
 */

boolean Adc_GetSequencerInterrupt ( Adc_ModuleType ModuleId, Adc_InterruptType InterruptID )
{
    return ((ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCISC) >> InterruptID) & TRUE ;
}
/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function is same like Adc_GetSequencerInterrupt but it will return all interrupts states .
 * it will return a byte and every bit in the lowest nibble will represent state of one interrupt
 * if bit is set then corresponding event occurred and interrupt enabled and its signal is send to NVIC .
 * if not then corresponding interrupt is disabled or event didn't occur .
 */

uint8 Adc_GetAllSequencerInterrupts ( Adc_ModuleType ModuleId)
{
    return (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCISC)  & ADC_SEQUEN_MASK ;

}
/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will clear the event of interrupt specified by InterruptID in module of ModuleId .
 * use this function inside ISR code to clear event caused interrupt,
 * or interrupt signal will be asserted again as soon as the ISR finish .
 * this function is just responsible for events from sample sequencer not digital comparators too .
 */

void Adc_ClearSequencerEvent ( Adc_ModuleType ModuleId, Adc_InterruptType InterruptID )
{
    ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCISC = TRUE << InterruptID ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function is same like Adc_ClearAllSequencerEvents but it will clear all sequencers events .
 * this function is just responsible for events from sample sequencer not digital comparators too .
 */

void Adc_ClearAllSequencerEvents (  Adc_ModuleType ModuleId )
{
    ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCISC = ADC_SEQUEN_MASK ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will enable the interrupt specified by InterruptID in module of ModuleId .
 * if interrupt is enabled then when event of this interrupt occur, interrupt signal asserted to NVIC
 * this function is just responsible for events from sample sequencer not digital comparators too .
 */

void Adc_EnableSequencerInterrupt ( Adc_ModuleType ModuleId, Adc_InterruptType InterruptID )
{
    (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCIM) |= TRUE<<InterruptID ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will disable the interrupt specified by InterruptID in module of ModuleId .
 * if interrupt is disabled then when event of this interrupt occur, interrupt signal won't asserted to NVIC .
 * this function is just responsible for events from sample sequencer not digital comparators too .
 */

void Adc_DisableSequencerInterrupt ( Adc_ModuleType ModuleId, Adc_InterruptType InterruptID )
{
    (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCIM) &= ~(TRUE<<InterruptID) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will get the buffer overflow state of sequencer defined by SequencerId of ModuleId .
 * if buffer overflowed return will = TRUE else it will be FALSE .
 * overflow happen when hardware write sequencer buffer happen and buffer is full .
 * if overflow flag is set then it won't be cleared except by software
 */

boolean Adc_GetOVState ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId)
{
    return ((ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCOSTAT) >> SequencerId) & TRUE ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will get the buffer under state of sequencer defined by SequencerId of ModuleId .
 * if buffer underflowed return will = TRUE else it will be FALSE .
 * under happen when read sequencer buffer happen and buffer is empty .
 * if underflow flag is set then it won't be cleared except by software
 */

boolean Adc_GetUVState ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId)
{
    return ((ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCUSTAT) >> SequencerId) & TRUE ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function is same like Adc_SequencerUnderflow function but will return,
 * overflow states of all sequencer, least nibble of return byte represent states of all sequencers ,
 * every bit in nibble represent one of four sequencer .
 * if bit is set then corresponding sequencer buffer is overflowed
 */

uint8 Adc_GetAllOVStates ( Adc_ModuleType ModuleId )
{
    return (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCOSTAT)  & ADC_SEQUEN_MASK ;
}

/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function is same like Adc_SequencerUnderflow function but will return,
 * underflow states of all sequencer, least nibble of return byte represent states of all sequencers ,
 * every bit in nibble represent one of four sequencer .
 * if bit is set then corresponding sequencer buffer is underflowed
 */

uint8 Adc_GetAllUVStates ( Adc_ModuleType ModuleId )
{
    return (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCUSTAT)  & ADC_SEQUEN_MASK ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will clear the buffer overflow state of sequencer defined by SequencerId of ModuleId .
 * overflow happen when hardware write sequencer buffer happen and buffer is full .
 * if overflow flag is set then it won't be cleared except by software using this function .
 */

void Adc_ClearOVState ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId )
{
    ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCOSTAT = TRUE << SequencerId ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will clear the buffer underflow state of sequencer defined by SequencerId of ModuleId .
 * underflow happen when hardware read sequencer buffer happen and buffer is empty .
 * if underflow flag is set then it won't be cleared except by software using this function .
 */

void Adc_ClearUVState ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId )
{
    ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCUSTAT = TRUE << SequencerId ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function is same like Adc_ClearOVState but it will clear all overflow flags,
 * of module specified by ModuleId
 */

void Adc_ClearAllOVStates ( Adc_ModuleType ModuleId )
{
    ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCOSTAT = ADC_SEQUEN_MASK ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function is same like Adc_ClearAllUVStates but it will clear all underflow flags,
 * of module specified by ModuleId
 */

void Adc_ClearAllUVStates ( Adc_ModuleType ModuleId )
{
    ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCUSTAT = ADC_SEQUEN_MASK ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function used to assign trigger source defined by SourceId to ,
 * sequencer defined by SequencerId in module defined by ModuleId .
 * when trigger source send a trigger signal to ADC modules according to its setting ,
 * the sequencers that configured to response to this trigger will start sampling according to their priority .
 */

void Adc_TriggerSource ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId, Adc_TriggerSourceType SourceId)
{
    uint32 Temp = (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCEMUX) & ~( ADC_SEQUEN_MASK << (SequencerId*ADC_SEQUEN_FIELD_WIDTH) ) ;
    (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCEMUX) = Temp | SourceId << (SequencerId*ADC_SEQUEN_FIELD_WIDTH) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function used to identify which PWM module contain,
 * PWM generators that used as trigger sources for sequencers .
 * PWM generator determined by PwmId contained in PWM module determined by GeneratorId
 * used as trigger source for sequencers of ADC module determined by ModuleId
 */

void Adc_SelectPwmModule ( Adc_ModuleType ModuleId, Adc_PwmGenratorType GeneratorId , Adc_PwmModuleType PwmId )
{
    uint32 Temp = (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCTSSEL) & ~(ADC_PWM_MASK << GeneratorId) ;
    (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCTSSEL) = Temp | (PwmId << GeneratorId) ;

    return ;
}


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

void Adc_SequencerPriority ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId, uint8 Priority)
{
    uint32 Temp = (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCSSPRI) & ~( ADC_SEQUEN_MASK << (SequencerId*ADC_SEQUEN_FIELD_WIDTH) ) ;
    (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCSSPRI) = Temp | (Priority << (SequencerId*ADC_SEQUEN_FIELD_WIDTH)) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function used to set ADC module determined by ModuleId to sample-phase determined by Phase
 * reference to Adc_SamplePhaseType comments for more informations about sampling phase
 */

void Adc_SetSamplePhase ( Adc_ModuleType ModuleId, Adc_SamplePhaseType Phase )
{
    (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCSPC) = Phase  ;

    return ;
}


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

void Adc_StartSequencers ( Adc_ModuleType ModuleId, uint8 SequencersMask )
{
    (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCPSSI) = SequencersMask | ADC_SEQUEN_START_MASK  ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function same as Adc_StartSequencers but it will just initiate sequencer to
 * operate when using Adc_StartSequencers function .
 * sequencers initiated by this function would start together even if Adc_StartSequencers used
 * with another ADC module .
 * this function used to synchronize to start sampling in different ADC modules at same moment using processor .
 */

void Adc_InitiateSequencers ( Adc_ModuleType ModuleId, uint8 SequencersMask )
{
    (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCPSSI) = SequencersMask | ADC_SEQUEN_INIT_MASK  ;

    return ;
}


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

void Adc_AveragingFactor ( Adc_ModuleType ModuleId, uint8 FactorPower )
{
    (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCSAC) = FactorPower ;

    return ;
}


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
void Adc_DComp_SecletIntLine ( Adc_ModuleType ModuleId, Adc_InterruptType InterruptID )
{
    (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCIM) |= TRUE << (InterruptID+ADC_DCOMP_INT_BIT_POS) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function same as Adc_DComp_EnableInterrupt but it will disable comparators interrupt
 * to be sent on interrupt line specified by InterruptID
 */

void Adc_DComp_DeselectIntLine ( Adc_ModuleType ModuleId, Adc_InterruptType InterruptID )
{
    (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCIM) &= ~(TRUE << (InterruptID+ADC_DCOMP_INT_BIT_POS)) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will return the state of interrupt generated by ,
 * comparator specified by DCompId in module specified by ModuleId .
 * if TRUE is returned then comparator event occur and will generate interrupt if,
 * there is on comparators interrupt line is selected  by Adc_DComp_SecletIntLine
 * and this interrupt line is enabled by NVIC module  .
 */

boolean Adc_DComp_GetEventState ( Adc_ModuleType ModuleId, Adc_DCompType DCompId )
{
    return ( (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCDCISC) >> DCompId ) & TRUE ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function same as Adc_DComp_IntState but it will return all comparators states .
 * in byte returned bit 0 represent comparator 0 if bit is set the interrupt state is TURE .
 */

uint8 Adc_DComp_GetEventStateAll ( Adc_ModuleType ModuleId )
{
    return (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCDCISC) & ADC_DCOMP_MASK ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will clear the state of interrupt generated by ,
 * comparator specified by DCompId in module specified by ModuleId .
 * it must be used in ISR of interrupt  triggered by digital comparator ,
 * to clear interrupt source or interrupt will be triggered again as soon as ISR finish
 */

void Adc_DComp_EventClr (Adc_ModuleType ModuleId, Adc_DCompType DCompId )
{
    ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCDCISC = TRUE << DCompId ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function same as Adc_DComp_IntClr but it will clear all comparators states ,
 * correspond for set bits in Mask .
 * bit 0 in Mask represent comparator 0 if bit is set then its interrupt state will be cleared .
 */

void Adc_DComp_EventClrAll (Adc_ModuleType ModuleId, uint8 Mask  )
{
    ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCDCISC = ADC_DCOMP_MASK ;

    return ;
}


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

void Adc_DitherControl ( Adc_ModuleType ModuleId, boolean Enable)
{
    ASSIGN_BIT ( (ADC_MOD_CTRL_BASE(ModuleId)->Adc_ADCCTL), ADC_DITHER_BIT_POS, Enable ) ;

    return ;
}


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

void Adc_SelectInputChannel ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId, Adc_SampleType SampleId, Adc_ChannelType ChannelId)
{
    uint32 Temp = ADC_SEQUEN_BASE(ModuleId, SequencerId)->Adc_ADCSSMUX & ~(ADC_SEQUEN_MASK << ChannelId) ;
    ADC_SEQUEN_BASE(ModuleId, SequencerId)->Adc_ADCSSMUX = Temp |  (SampleId << ChannelId) ;

     return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will enable/disable sampling internal temperature sensor for sample entry specified by SampleId ,
 * which belong to sequencer specified by SequencerId in ADC module specified by ModuleId .
 * internal temperature sensor used to notify the system temperature and to calibrate the internal RC oscillator .
 * if this feature is enabled then differential input mode cannot be enabled and vice versa .
 */

void Adc_Sample_TempSensorCtrl ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId, Adc_SampleType SampleId, boolean Enable )
{
    ASSIGN_BIT ( (ADC_SEQUEN_BASE(ModuleId, SequencerId)->Adc_ADCSSCTL), (SampleId+ADC_SEQ_TEMP_BIT_POS), Enable ) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will enable/disable event generation for sample entry specified by SampleId ,
 * which belong to sequencer specified by SequencerId in ADC module specified by ModuleId .
 * after sampling finish for this sample entry event is asserted from sequencer sample entry belong to .
 * and if sequencer interrupt isn't masked an interrupt signal is send to NVIC module .
 * all sample entries' events is get or together to generate its sequencer event signal .
 */

void Adc_Sample_EventCtrl ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId, Adc_SampleType SampleId, boolean Enable )
{
    ASSIGN_BIT ( (ADC_SEQUEN_BASE(ModuleId, SequencerId)->Adc_ADCSSCTL), (SampleId+ADC_SEQ_EVENT_BIT_POS), Enable ) ;

    return ;
}


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

void Adc_Sample_EndCtrl ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId, Adc_SampleType SampleId, boolean Enable )
{
    ASSIGN_BIT ( (ADC_SEQUEN_BASE(ModuleId, SequencerId)->Adc_ADCSSCTL), (SampleId+ADC_SEQ_END_BIT_POS), Enable ) ;

    return ;
}


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

void Adc_Sample_DifferentialCtrl ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId, Adc_SampleType SampleId, boolean Enable )
{
    ASSIGN_BIT ( (ADC_SEQUEN_BASE(ModuleId, SequencerId)->Adc_ADCSSCTL), (SampleId+ADC_SEQ_DIFF_BIT_POS), Enable ) ;

    return ;
}


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

void Adc_MultiResultRead ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId, Adc_ResultType * DataPtr, uint8 SamplesNumber  )
{
    uint8 Counter = 0 ;
    for( ; Counter<SamplesNumber ; Counter++ )
    {
        DataPtr[Counter] = ADC_SEQUEN_BASE(ModuleId, SequencerId)->Adc_ADCSSFIFO ;
    }

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will return TRUE if buffer of sequencer specified by SequencerId,
 * in ADC module specified by ModuleId is empty which mean is has no samples to read .
 * and any read operation done on empty buffer will result in underflow event .
 * reading of empty buffer will return the old value of the first entry to be written in buffer .
 */

boolean Adc_CheckEmptyBuffer (Adc_ModuleType ModuleId, Adc_SequencerType SequencerId)
{
    return ((ADC_SEQUEN_BASE(ModuleId, SequencerId)->Adc_ADCSSFSTAT) >> ADC_SEQ_EMPTY_BIT_POS) & TRUE ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will return TRUE if buffer of sequencer specified by SequencerId,
 * in ADC module specified by ModuleId is full which mean all its entry full with samples .
 * and any write operation done on full buffer will result in underflow event .
 * write to full buffer have no effect and sample result will be lost
 */

boolean Adc_CheckFullBuffer (Adc_ModuleType ModuleId, Adc_SequencerType SequencerId)
{
    return ((ADC_SEQUEN_BASE(ModuleId, SequencerId)->Adc_ADCSSFSTAT) >> ADC_SEQ_FULL_BIT_POS) & TRUE ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will return the index of next entry to be written in ,
 * buffer of sequencer specified by SequencerId in ADC module specified by ModuleId .
 * index of entry will be in range of 0 ~ buffer depth - 1 .
 */

uint8 Adc_GetBufferHead (Adc_ModuleType ModuleId, Adc_SequencerType SequencerId)
{
    return ((ADC_SEQUEN_BASE(ModuleId, SequencerId)->Adc_ADCSSFSTAT) >> ADC_SEQ_FIFO_HPTR_POS) & ADC_SEQ_FIFO_PTR_MASK ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function will return the index of next entry to be read in ,
 * buffer of sequencer specified by SequencerId in ADC module specified by ModuleId .
 * index of entry will be in range of 0 ~ buffer depth - 1 .
 */

uint8 Adc_GetBufferTail (Adc_ModuleType ModuleId, Adc_SequencerType SequencerId)
{
    return ((ADC_SEQUEN_BASE(ModuleId, SequencerId)->Adc_ADCSSFSTAT) >> ADC_SEQ_FIFO_TPTR_POS) & ADC_SEQ_FIFO_PTR_MASK ;
}


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

void Adc_SampleDestinationCtrl ( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId, Adc_SampleType SampleId, boolean Compare )
{
    ASSIGN_BIT ( (ADC_SEQUEN_BASE(ModuleId, SequencerId)->Adc_ADCSSOP), SampleId, Compare ) ;

    return ;
}


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

void Adc_SampleDCompSelect( Adc_ModuleType ModuleId, Adc_SequencerType SequencerId, Adc_SampleType SampleId, Adc_DCompType DCompId )
{
    uint32 Temp = ADC_SEQUEN_BASE(ModuleId, SequencerId)->Adc_ADCSSDC & ~(ADC_SEQUEN_MASK << SampleId) ;
    ADC_SEQUEN_BASE(ModuleId, SequencerId)->Adc_ADCSSMUX = Temp |  (DCompId << SampleId) ;

    return ;
}


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

void Adc_DComp_ResetInterrupt (  Adc_ModuleType ModuleId, Adc_DCompType DCompId )
{
    *(ADC_DCOMP0_RST_REG + ModuleId*ADC_MODULE_OFFSET ) = TRUE << DCompId ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * for digital comparator unit specified by DCompId which in ADC module specified by ModuleId ,
 * digital comparator depend on both current and previous sample result to check if current ,
 * sample match state machine of digital comparator .
 * this function will reset trigger state to the initial condition .
 * so that it won't depend on previous sample result and start from next one
 */

void Adc_DComp_ResetTrigger (  Adc_ModuleType ModuleId, Adc_DCompType DCompId )
{
    *(ADC_DCOMP0_RST_REG + ModuleId*ADC_MODULE_OFFSET ) = TRUE << (DCompId+ADC_DCOMP_RST_TRIG_POS) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * for digital comparator unit specified by DCompId which in ADC module specified by ModuleId ,
 * this function will enable/disable the trigger for it .
 * if trigger enabled and sample result sent to digital comparator is within trigger range (condition) ,
 * and achieve trigger state machine (mode) then trigger is sent to PWM generators .
 * if Enable is TRUE then trigger is enabled and disabled if else
 */

void Adc_DComp_TrigCtrl ( Adc_ModuleType ModuleId, Adc_DCompType DCompId, boolean Enable )
{

    ASSIGN_BIT ( ADC_DCOMP_CTRL_ADDR(ModuleId)[DCompId], ADC_DCOMP_TRIG_EN_POS, Enable ) ;

    return ;
}


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

void Adc_DComp_TrigCond ( Adc_ModuleType ModuleId, Adc_DCompType DCompId, Adc_DCompCondTyp Condition )
{
    uint32 Temp = ADC_DCOMP_CTRL_ADDR(ModuleId)[DCompId] & ~(ADC_DCOMP_CTRL_MASK << ADC_DCOMP_TRIG_COND_POS) ;
    ADC_DCOMP_CTRL_ADDR(ModuleId)[DCompId] = Temp |  (Condition << ADC_DCOMP_TRIG_COND_POS) ;
    *(ADC_DCOMP0_RST_REG + ModuleId*ADC_MODULE_OFFSET ) = TRUE << (DCompId+ADC_DCOMP_RST_TRIG_POS) ;

    return ;
}


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

void Adc_DComp_TrigMode ( Adc_ModuleType ModuleId, Adc_DCompType DCompId, Adc_DCompModeType Mode )
{
    uint32 Temp = ADC_DCOMP_CTRL_ADDR(ModuleId)[DCompId] & ~(ADC_DCOMP_CTRL_MASK << ADC_DCOMP_TRIG_MODE_POS) ;
    ADC_DCOMP_CTRL_ADDR(ModuleId)[DCompId] = Temp |  (Mode << ADC_DCOMP_TRIG_MODE_POS) ;
    *(ADC_DCOMP0_RST_REG + ModuleId*ADC_MODULE_OFFSET ) = TRUE << (DCompId+ADC_DCOMP_RST_TRIG_POS) ;

    return ;
}


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

void Adc_DComp_EventCtrl ( Adc_ModuleType ModuleId, Adc_DCompType DCompId, boolean Enable )
{
    ASSIGN_BIT ( ADC_DCOMP_CTRL_ADDR(ModuleId)[DCompId], ADC_DCOMP_INT_EN_POS, Enable ) ;

    return ;
}


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

void Adc_DComp_EvnetCond ( Adc_ModuleType ModuleId, Adc_DCompType DCompId, Adc_DCompCondTyp Condition )
{
    uint32 Temp = ADC_DCOMP_CTRL_ADDR(ModuleId)[DCompId] & ~(ADC_DCOMP_CTRL_MASK << ADC_DCOMP_INT_COND_POS) ;
    ADC_DCOMP_CTRL_ADDR(ModuleId)[DCompId] = Temp |  (Condition << ADC_DCOMP_INT_COND_POS) ;
    *(ADC_DCOMP0_RST_REG + ModuleId*ADC_MODULE_OFFSET ) = TRUE << DCompId ;

    return ;
}


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

void Adc_DComp_EvnetMode ( Adc_ModuleType ModuleId, Adc_DCompType DCompId, Adc_DCompModeType Mode )
{
    uint32 Temp = ADC_DCOMP_CTRL_ADDR(ModuleId)[DCompId] & ~(ADC_DCOMP_CTRL_MASK << ADC_DCOMP_INT_MODE_POS) ;
    ADC_DCOMP_CTRL_ADDR(ModuleId)[DCompId] = Temp |  (Mode << ADC_DCOMP_INT_MODE_POS) ;
    *(ADC_DCOMP0_RST_REG + ModuleId*ADC_MODULE_OFFSET ) = TRUE << DCompId ;

    return ;
}


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

void Adc_DComp_Range ( Adc_ModuleType ModuleId, Adc_DCompType DCompId, uint16 UpperValue, uint16 LowerValue )
{

    ADC_DCOMP_RANGE_ADDR(ModuleId)[DCompId] = (LowerValue << ADC_DCOMP_LOW_RANGE_POS) | (UpperValue << ADC_DCOMP_UP_RANGE_POS) ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function used to set the sample rate of ADC module specified by ModuleId according to Rate .
 * sample rate will be equal to the rate sample results is generated if averaging factor = 1 .
 * sample results generated by rate equal to sample rate divided by averaging factor .
 * sample rate could be doubled using both ADC modules to sample same input source with
 * same sample rate and out of phase by 180 degree of each other and their result is rearranged in back to back way .
 */

void Adc_SetSampleRate ( Adc_ModuleType ModuleId, Adc_SampleRateType Rate )
{
    *(ADC_ADCPP_REG + ModuleId*ADC_MODULE_OFFSET ) = Rate ;

    return ;
}


/*********************************************************************************/

/*
 * non privilege, synchronous, Reentrant function .
 * this function used to set the ADC modules clock source of ADC module specified by ModuleId according to Source .
 * ADC modules can't have different clock sources so if both ADC0,1 is enabled by MCU module ,
 * then ADC0 clock source configuration will overwrite ADC1 clock source configuration  .
 */

void Adc_SetClockSource ( Adc_ModuleType ModuleId, Adc_ClkSourceType Source )
{
    *(ADC_ADCCC_REG + ModuleId*ADC_MODULE_OFFSET ) = Source ;
}


/*********************************************************************************/

