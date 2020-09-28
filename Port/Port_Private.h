/************************************************/
/*  Port_Private                                */
/*  Created on: Sep 13, 2020                    */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/



#ifndef PORT_PRIVATE_H_
#define PORT_PRIVATE_H_


/*********************************************************************************/

typedef volatile struct
{
    uint32 Port_GPIODATA [256] ;
    uint32 Port_GPIODIR ;
    uint32 Port_GPIOIS  ;
    uint32 Port_GPIOIBE  ;
    uint32 Port_GPIOIEV ;
    uint32 Port_GPIOIM  ;
    uint32 Port_GPIORIS  ;
    uint32 Port_GPIOMIS   ;
    uint32 Port_GPIOICR  ;
    uint32 Port_GPIOAFSEL ;
    uint32 Port_Empty1 [55] ;
    uint32 Port_GPIODR2R ;
    uint32 Port_GPIODR4R ;
    uint32 Port_GPIODR8R ;
    uint32 Port_GPIOODR ;
    uint32 Port_GPIOPUR ;
    uint32 Port_GPIOPDR ;
    uint32 Port_GPIOSLR ;
    uint32 Port_GPIODEN ;
    uint32 Port_GPIOLOCK ;
    uint32 Port_GPIOCR ;
    uint32 Port_GPIOAMSEL ;
    uint32 Port_GPIOPCTL ;
    uint32 Port_GPIOADCCTL ;
    uint32 Port_GPIODMACTL ;
    uint32 Port_Empty2 [178] ;


}Port_RegisterMap_Struct ;


/*********************************************************************************/

/* Port base registers APB bus */

#define PORT_PORTA_BASE_APB         (( Port_RegisterMap_Struct * )( 0x40004000 ))
#define PORT_PORTB_BASE_APB         (( Port_RegisterMap_Struct * )( 0x40005000 ))
#define PORT_PORTC_BASE_APB         (( Port_RegisterMap_Struct * )( 0x40006000 ))
#define PORT_PORTD_BASE_APB         (( Port_RegisterMap_Struct * )( 0x40007000 ))
#define PORT_PORTE_BASE_APB         (( Port_RegisterMap_Struct * )( 0x40024000 ))
#define PORT_PORTF_BASE_APB         (( Port_RegisterMap_Struct * )( 0x40025000 ))


/*********************************************************************************/

/* Port base registers AHB bus */

#define PORT_AHB_OFSSET_CONS        0x02

#define PORT_PORTA_BASE_AHB         (( Port_RegisterMap_Struct * )( 0x40058000 ))
#define PORT_PORTB_BASE_AHB         (( Port_RegisterMap_Struct * )( 0x40059000 ))
#define PORT_PORTC_BASE_AHB         (( Port_RegisterMap_Struct * )( 0x4005A000 ))
#define PORT_PORTD_BASE_AHB         (( Port_RegisterMap_Struct * )( 0x4005B000 ))
#define PORT_PORTE_BASE_AHB         (( Port_RegisterMap_Struct * )( 0x4005C000 ))
#define PORT_PORTF_BASE_AHB         (( Port_RegisterMap_Struct * )( 0x4005D000 ))


/*********************************************************************************/

/* this is value to write in GPIOLOCK register  to unlock GPIOCR register */

#define PORT_GPIOLOCK_PASSWORD      0x4C4F434B


/*********************************************************************************/

/* used inside Port_Init function */

#define PORT_A_NUMBER           0
#define PORT_B_NUMBER           1
#define PORT_C_NUMBER           2
#define PORT_D_NUMBER           3
#define PORT_E_NUMBER           4
#define PORT_F_NUMBER           5

#define PORT_PIN31_REG_OFFSET   7
#define PORT_PIN38_REG_OFFSET   0
#define PORT_NUMBER_OF_PORTS    5


/*********************************************************************************/

/*
 * macros of Port_PinType is divided to two subsets 1 for defining port of the pin,
 * and other for defining pin number in its port
 */

/* this define the offset of port number subset from LSB*/
#define PORT_PORT_NUMBER_OFFSET     4

/* this define mask of pin number subset */
#define PORT_PIN_NUMBER_MASK        0x0F

/* this define mask of port number subset */
#define PORT_PORT_NUMBER_MASK       0xF0

/* this the mask of all port pins */
#define PORT_ALL_PORT_MASK          0xFF

/* define the number of bits represent pin's peripheral signal in GPIOPCTL register */
#define PORT_GPIOPCTL_BIT_FIELD_WIDTH   4

/* define the mask of bits represent pin's peripheral signal in GPIOPCTL register */
#define PORT_GPIOPCTL_BIT_FIELD_MASK    4


/*********************************************************************************/

/* used to calculate the port base address */

#define PORT_BASE_REG_EQU(PortNum)  (PORT_PORTA_BASE_AHB + PortNum*PORT_AHB_OFSSET_CONS - (Mcu_GpioBusAperture[PortNum] & Port_RegisterBusOffset[PortNum]))


/*********************************************************************************/

#endif /* PORT_PRIVATE_H_ */
