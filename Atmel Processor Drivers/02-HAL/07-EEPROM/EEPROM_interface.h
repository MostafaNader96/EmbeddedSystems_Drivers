/*
 * EEPROM_interface.h
 *
 *  Created on: Apr 15, 2020
 *      Author: MOSTAFA
 */

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

u8 EEPROM_u8WriteDataByte(u16 Copy_u16ByteAddress, u8 Copy_u8Data);
u8 EEPROM_u8ReadDataByte(u16 Copy_u16ByteAddress,u8 * Copy_pu8ReturnData);

#endif /* EEPROM_INTERFACE_H_ */
