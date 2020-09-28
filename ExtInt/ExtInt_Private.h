/************************************************/
/*  ExtInt_Private.h                            */
/*  Created on: Sep 15, 2020                    */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/

#ifndef EXTINT_PRIVATE_H_
#define EXTINT_PRIVATE_H_


/*********************************************************************************/


typedef struct
{
    uint32 ExtInt_GPIODATA [256] ;
    uint32 ExtInt_GPIODIR ;
    uint32 ExtInt_GPIOIS  ;
    uint32 ExtInt_GPIOIBE  ;
    uint32 ExtInt_GPIOIEV ;
    uint32 ExtInt_GPIOIM  ;
    uint32 ExtInt_GPIORIS  ;
    uint32 ExtInt_GPIOMIS   ;
    uint32 ExtInt_GPIOICR  ;
    uint32 ExtInt_GPIOAFSEL ;
    uint32 ExtInt_Empty1 [55] ;
    uint32 ExtInt_GPIODR2R ;
    uint32 ExtInt_GPIODR4R ;
    uint32 ExtInt_GPIODR8R ;
    uint32 ExtInt_GPIOODR ;
    uint32 ExtInt_GPIOPUR ;
    uint32 ExtInt_GPIOPDR ;
    uint32 ExtInt_GPIOSLR ;
    uint32 ExtInt_GPIODEN ;
    uint32 ExtInt_GPIOLOCK ;
    uint32 ExtInt_GPIOCR ;
    uint32 ExtInt_GPIOAMSEL ;
    uint32 ExtInt_GPIOPCTL ;
    uint32 ExtInt_GPIOADCCTL ;
    uint32 ExtInt_GPIODMACTL ;
    uint32 ExtInt_Empty2 [178] ;

}ExtInt_RegisterMap_Struct ;


/*********************************************************************************/

/* this is ISRs called when ports interrupt is triggered */

void ExtInt_PortA_ISR (void) ;
void ExtInt_PortB_ISR (void) ;
void ExtInt_PortC_ISR (void) ;
void ExtInt_PortD_ISR (void) ;
void ExtInt_PortE_ISR (void) ;
void ExtInt_PortF_ISR (void) ;


/*********************************************************************************/

/*
 * macros of ExtInt_RegisterMap_Struct is divided to two subsets 1 for defining port of the pin,
 * and other for defining pin number in its port
 */

/* this define the offset of port number subset from LSB*/
#define EXTINT_PORT_NUMBER_OFFSET   4

/* this define mask of pin number subset */
#define EXTINT_PIN_NUMBER_MASK      0x0F

/* this define mask of port number subset */
#define EXTINT_PORT_NUMBER_MASK     0xF0

/* this the mask of all port pins */
#define EXTINT_ALL_PORT_MASK        0xFF

#define EXTINT_ISR_NUMBER           0x06


/*********************************************************************************/

/* Port base registers APB bus */

#define EXTINT_PORTA_BASE_APB         (( ExtInt_RegisterMap_Struct * )( 0x40004000 ))
#define EXTINT_PORTB_BASE_APB         (( ExtInt_RegisterMap_Struct * )( 0x40005000 ))
#define EXTINT_PORTC_BASE_APB         (( ExtInt_RegisterMap_Struct * )( 0x40006000 ))
#define EXTINT_PORTD_BASE_APB         (( ExtInt_RegisterMap_Struct * )( 0x40007000 ))
#define EXTINT_PORTE_BASE_APB         (( ExtInt_RegisterMap_Struct * )( 0x40024000 ))
#define EXTINT_PORTF_BASE_APB         (( ExtInt_RegisterMap_Struct * )( 0x40025000 ))


/*********************************************************************************/

/* Port base registers AHB bus */

#define EXTINT_AHB_OFSSET_CONS         0x02

#define EXTINT_PORTA_BASE_AHB         (( ExtInt_RegisterMap_Struct * )( 0x40058000 ))
#define EXTINT_PORTB_BASE_AHB         (( ExtInt_RegisterMap_Struct * )( 0x40059000 ))
#define EXTINT_PORTC_BASE_AHB         (( ExtInt_RegisterMap_Struct * )( 0x4005A000 ))
#define EXTINT_PORTD_BASE_AHB         (( ExtInt_RegisterMap_Struct * )( 0x4005B000 ))
#define EXTINT_PORTE_BASE_AHB         (( ExtInt_RegisterMap_Struct * )( 0x4005C000 ))
#define EXTINT_PORTF_BASE_AHB         (( ExtInt_RegisterMap_Struct * )( 0x4005D000 ))

/*********************************************************************************/

/* used to calculate the port base address */

#define EXTINT_BASE_REG_EQU(PortNum)  (EXTINT_PORTA_BASE_AHB + PortNum*EXTINT_AHB_OFSSET_CONS - (Mcu_GpioBusAperture[PortNum] & Port_RegisterBusOffset[PortNum]))


/*********************************************************************************/


#endif /* EXTINT_PRIVATE_H_ */
