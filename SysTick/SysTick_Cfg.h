/************************************************/
/*  SysTick_Cfg.h                               */
/*  Created on: Sep 1, 2020                     */
/*  Author: Bebo                                */
/*  Target: TM4C123GHPM6                        */
/************************************************/



#ifndef SYSTICK_CFG_H_
#define SYSTICK_CFG_H_


/*********************************************************************************/


/* if TRUE then function SysTick_BusyWait won't be interrupted */
#define SYSTICK_BUSY_WAIT_CS        TRUE

/* if TRUE then function SysTick_SingleNotification won't be interrupted */
#define SYSTICK_SINGLE_NOT_CS       TRUE

/* if TRUE then function SysTick_PeriodicNotification won't be interrupted */
#define SYSTICK_PERIODIC_NOT_CS     TRUE


/*********************************************************************************/


#endif /* SYSTICK_CFG_H_ */
