#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

ErrorStatus DIO_SetPinDirection(u8 Port,u8 Pin, u8 Direction);
ErrorStatus DIO_SetPinValue(u8 Port,u8 Pin, u8 Value);
ErrorStatus DIO_SetPortDirecton(u8 Port,u8 Value);
ErrorStatus DIO_SetPortValue(u8 Port,u8 Value);
ErrorStatus DIO_GetPinValue(u8 Port,u8 Pin,u8 *Value);

#endif
