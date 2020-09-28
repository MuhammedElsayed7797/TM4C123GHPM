/************************************************/
/*  Dio_Private.h                               */
/*  Created on: Sep 13, 2020                    */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/




#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_


/*********************************************************************************/


typedef volatile struct
{
    uint32 Dio_GPIODATA [256] ;
    uint32 Dio_GPIODIR ;
    uint32 Dio_GPIOIS  ;
    uint32 Dio_GPIOIBE  ;
    uint32 Dio_GPIOIEV ;
    uint32 Dio_GPIOIM  ;
    uint32 Dio_GPIORIS  ;
    uint32 Dio_GPIOMIS   ;
    uint32 Dio_GPIOICR  ;
    uint32 Dio_GPIOAFSEL ;
    uint32 Dio_Empty1 [55] ;
    uint32 Dio_GPIODR2R ;
    uint32 Dio_GPIODR4R ;
    uint32 Dio_GPIODR8R ;
    uint32 Dio_GPIOODR ;
    uint32 Dio_GPIOPUR ;
    uint32 Dio_GPIOPDR ;
    uint32 Dio_GPIOSLR ;
    uint32 Dio_GPIODEN ;
    uint32 Dio_GPIOLOCK ;
    uint32 Dio_GPIOCR ;
    uint32 Dio_GPIOAMSEL ;
    uint32 Dio_GPIOPCTL ;
    uint32 Dio_GPIOADCCTL ;
    uint32 Dio_GPIODMACTL ;
    uint32 Dio_Empty2 [178] ;


}Dio_RegisterMap_Struct ;


/*********************************************************************************/

/* Port base registers APB bus */

#define DIO_PORTA_BASE_APB         (( Dio_RegisterMap_Struct * )( 0x40004000 ))
#define DIO_PORTB_BASE_APB         (( Dio_RegisterMap_Struct * )( 0x40005000 ))
#define DIO_PORTC_BASE_APB         (( Dio_RegisterMap_Struct * )( 0x40006000 ))
#define DIO_PORTD_BASE_APB         (( Dio_RegisterMap_Struct * )( 0x40007000 ))
#define DIO_PORTE_BASE_APB         (( Dio_RegisterMap_Struct * )( 0x40024000 ))
#define DIO_PORTF_BASE_APB         (( Dio_RegisterMap_Struct * )( 0x40025000 ))


/*********************************************************************************/

/* Port base registers AHB bus */

#define DIO_AHB_OFSSET_CONS         0x02

#define DIO_PORTA_BASE_AHB         (( Dio_RegisterMap_Struct * )( 0x40058000 ))
#define DIO_PORTB_BASE_AHB         (( Dio_RegisterMap_Struct * )( 0x40059000 ))
#define DIO_PORTC_BASE_AHB         (( Dio_RegisterMap_Struct * )( 0x4005A000 ))
#define DIO_PORTD_BASE_AHB         (( Dio_RegisterMap_Struct * )( 0x4005B000 ))
#define DIO_PORTE_BASE_AHB         (( Dio_RegisterMap_Struct * )( 0x4005C000 ))
#define DIO_PORTF_BASE_AHB         (( Dio_RegisterMap_Struct * )( 0x4005D000 ))

/*********************************************************************************/

/*
 * macros of Dio_PinType is divided to two subsets 1 for defining port of the pin,
 * and other for defining pin number in its port
 */

/* this define the offset of port number subset from LSB*/
#define DIO_PORT_NUMBER_OFFSET      4

/* this define mask of pin number subset */
#define DIO_PIN_NUMBER_MASK         0x0F

/* this define mask of port number subset */
#define DIO_PORT_NUMBER_MASK        0xF0

/* this the mask of all port pins */
#define DIO_ALL_PORT_MASK           0xFF


/*********************************************************************************/

/* used to calculate the port base address */

#define DIO_BASE_REG_EQU(PortNum)  (DIO_PORTA_BASE_AHB + PortNum*DIO_AHB_OFSSET_CONS - (Mcu_GpioBusAperture[PortNum] & Port_RegisterBusOffset[PortNum]))


/*********************************************************************************/


#endif /* DIO_PRIVATE_H_ */
