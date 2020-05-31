/*
 * HSwitch.h
 *
 *  Created on: Mar 16, 2020
 *      Author: MOSTAFA
 */

#ifndef HSWITCH_H_
#define HSWITCH_H_
#include "HSwitch_SwitchNumber.h"

/*************************************
 ************SWITCH_STATE*************
 *************************************/
#define SWITCH_PRESSED 0xfa
#define SWITCH_RELEASED 0xbb


/************************************************************************
 * Function name: Switch_Init
 *
 * parameters:  Input: NA      
 *
 *
 *              Output: NA
 *              In/out: NA
 * return: OK, NOT_OK
 * Description: a function to initialize switch
 ***************************************************************************/
 
uint_8t Switch_Init (void);

/************************************************************************
 * Function name: Switch_GetSwitchState
 *
 * parameters:  Input: 
 *                 SwitchNum
 *                     Type: uint_8t
 *                     Description: Switch Name and Number (Hswitch_LED...)
 *
 *              Output: NA
 *              In/out: state
 *                     type: pointer to uint_8t
 *                     Description: Switch State which to be read
 * return: OK, NOT_OK
 * Description: a function to read Switch State
 ***************************************************************************/
 
uint_8t Switch_GetSwitchState(uint_8t SwitchNum,uint_8t * state);


#endif /* HSWITCH_H_ */
