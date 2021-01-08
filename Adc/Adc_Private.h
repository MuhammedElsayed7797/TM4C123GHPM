/************************************************/
/*  Adc_Private.h                                       */
/*  Created on: Dec 22, 2020                    */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_


/*********************************************************************************/


typedef volatile struct
{
    uint32 Adc_ADCSSMUX ;
    uint32 Adc_ADCSSCTL ;
    uint32 Adc_ADCSSFIFO ;
    uint32 Adc_ADCSSFSTAT ;
    uint32 Adc_ADCSSOP ;
    uint32 Adc_ADCSSDC ;
    uint32 Adc_Empty1 ;
    uint32 Adc_Empty2 ;
} Adc_SequenRegisterMap_Struct ;


/*********************************************************************************/


typedef volatile struct
{
    uint32 Adc_ADCACTSS ;
    uint32 Adc_ADCRIS    ;
    uint32 Adc_ADCIM ;
    uint32 Adc_ADCISC ;
    uint32 Adc_ADCOSTAT ;
    uint32 Adc_ADCEMUX ;
    uint32 Adc_ADCUSTAT ;
    uint32 Adc_ADCTSSEL ;
    uint32 Adc_ADCSSPRI ;
    uint32 Adc_ADCSPC ;
    uint32 Adc_ADCPSSI ;
    uint32 Adc_Empty1 ;
    uint32 Adc_ADCSAC ;
    uint32 Adc_ADCDCISC ;
    uint32 Adc_ADCCTL ;
    uint32 Adc_Empty2 ;

} Adc_CtrlRegisterMap_Struct;


#define ADC_MOD_CTRL_BASE(ModuleId)                 (ADC_MOD0_CTRL_BASE + ModuleId*ADC_MOD_CTRL_OFFSET)

#define ADC_SEQUEN_BASE(ModuleId, SequencerId)      (ADC_SEQUEN0_CTRL_BASE + ModuleId*ADC_SEQUEN_OFFSET + SequencerId )

#define ADC_DCOMP_CTRL_ADDR(ModuleId)               (ADC_DCOMP0_CTRL_REG + ModuleId*ADC_MODULE_OFFSET)

#define ADC_DCOMP_RANGE_ADDR(ModuleId)              (ADC_DCOMP0_RANGE_REG + ModuleId*ADC_MODULE_OFFSET)

/*********************************************************************************/


#define ADC_MOD0_CTRL_BASE          (( Adc_CtrlRegisterMap_Struct * )( 0x40038000 ))
#define ADC_MOD_CTRL_OFFSET         0x40

#define ADC_SEQUEN0_CTRL_BASE       (( Adc_SequenRegisterMap_Struct * )( 0x40038040 ))
#define ADC_SEQUEN_OFFSET           0x80


/*********************************************************************************/


#define ADC_DCOMP0_RST_REG          (( volatile uint32 * )( 0x40038D00 ))
#define ADC_DCOMP0_CTRL_REG         (( volatile uint32 * )( 0x40038E00 ))
#define ADC_DCOMP0_RANGE_REG        (( volatile uint32 * )( 0x40038E40 ))
#define ADC_ADCPP_REG               (( volatile uint32 * )( 0x40038FC4 ))
#define ADC_ADCCC_REG               (( volatile uint32 * )( 0x40038FC8 ))
#define ADC_MODULE_OFFSET           0x400


/*********************************************************************************/


#define ADC_BUSY_FLAG_OFFSET        16
#define ADC_SEQUEN_MASK             0xF
#define ADC_PWM_MASK                0x3
#define ADC_SEQUEN_FIELD_WIDTH      4
#define ADC_SEQUEN_START_MASK       0x80000000
#define ADC_SEQUEN_INIT_MASK        0x08000000
#define ADC_DCOMP_MASK              0xFF
#define ADC_DITHER_BIT_POS          0x06
#define ADC_SEQ_TEMP_BIT_POS        0x3
#define ADC_SEQ_EVENT_BIT_POS       0x2
#define ADC_SEQ_END_BIT_POS         0x1
#define ADC_SEQ_DIFF_BIT_POS        0x0
#define ADC_SEQ_FULL_BIT_POS        0xC
#define ADC_SEQ_EMPTY_BIT_POS       0x8
#define ADC_SEQ_FIFO_HPTR_POS       0x4
#define ADC_SEQ_FIFO_TPTR_POS       0x0
#define ADC_SEQ_FIFO_PTR_MASK       0xF
#define ADC_DCOMP_FIELD_WIDTH       4
#define ADC_DCOMP_RST_TRIG_POS      0x10
#define ADC_DCOMP_TRIG_EN_POS       0xC
#define ADC_DCOMP_TRIG_COND_POS     0xA
#define ADC_DCOMP_TRIG_MODE_POS     0x8
#define ADC_DCOMP_INT_EN_POS        0x4
#define ADC_DCOMP_INT_COND_POS      0x2
#define ADC_DCOMP_INT_MODE_POS      0x0
#define ADC_DCOMP_CTRL_MASK         0x3
#define ADC_DCOMP_UP_RANGE_POS      0x10
#define ADC_DCOMP_LOW_RANGE_POS     0x00
#define ADC_DCOMP_INT_BIT_POS       0x10

/*********************************************************************************/


#endif /* ADC_PRIVATE_H_ */
