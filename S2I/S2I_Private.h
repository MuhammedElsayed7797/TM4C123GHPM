/************************************************/
/*  S2I.h                                       */
/*  Created on: Sep 20, 2020                    */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/

#ifndef S2I_PRIVATE_H_
#define S2I_PRIVATE_H_


/*********************************************************************************/

/* macros used for determine bit offset and position and masks */

#define S2I_ISR_NUMBER              4


#define S2I_MODULE_OFFSET_1         0x0040
#define S2I_MODULE_OFFSET_2         0x0400


#define S2I_SCR_FIELD_MASK          0x00FF
#define S2I_SCR_FIELD_OFFSET        8


#define S2I_SPI_FIELD_MASK          0xFF3F
#define S2I_SPI_FIELD_OFFSET        6

#define S2I_FRAME_FIELD_MASK        0xFFCF
#define S2I_FRAME_FIELD_OFFSET      4

#define S2I_WIDTH_FIELD_MASK        0xFFF0

#define S2I_EOT_BIT_POS             4

#define S2I_MASTER_BIT_POS          2

#define S2I_ENABLE_BIT_POS          1

#define S2I_LBM_BIT_POS             0

#define S2I_BSY_BIT_POS             4

#define S2I_BUFFER_STATE_MASK       0b11

#define S2I_INTERRUPT_CLR_MASK      0x3


/*********************************************************************************/


typedef volatile struct
{
    uint32 S2I_SSICR0 ;
    uint32 S2I_SSICR1 ;
    uint32 S2I_SSIDR ;
    uint32 S2I_SSISR ;
    uint32 S2I_SSICPSR ;
    uint32 S2I_SSIIM ;
    uint32 S2I_SSIRIS ;
    uint32 S2I_SSIMIS ;
    uint32 S2I_SSIICR ;
    uint32 S2I_SSIDMACTL ;
    uint32 S2I_Empty1 [6] ;



} S2I_RegisterMap_Struct ;


/*********************************************************************************/

/* SSI modules base registers address */

#define S2I_MODULE_0_BASE       (( S2I_RegisterMap_Struct * )( 0x40008000 ))
#define S2I_MODULE_1_BASE       (( S2I_RegisterMap_Struct * )( 0x40009000 ))
#define S2I_MODULE_2_BASE       (( S2I_RegisterMap_Struct * )( 0x4000A000 ))
#define S2I_MODULE_3_BASE       (( S2I_RegisterMap_Struct * )( 0x4000B000 ))


#define S2I_MODULE_0_SSICC_REG      ((volatile uint32 *) 0x40008FC8 )
#define S2I_MODULE_1_SSICC_REG      ((volatile uint32 *) 0x40009FC8 )
#define S2I_MODULE_2_SSICC_REG      ((volatile uint32 *) 0x4000AFC8 )
#define S2I_MODULE_3_SSICC_REG      ((volatile uint32 *) 0x4000BFC8 )


/*********************************************************************************/


#endif /* S2I_PRIVATE_H_ */
