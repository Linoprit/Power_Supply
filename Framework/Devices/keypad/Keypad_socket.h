/*
 * Keypadbitbanging.h
 *
 *  Created on: 04.11.2015
 *      Author: harald
 */

#ifndef DEVICES_KEYPAD_KEYPAD_SOCKET_H_
#define DEVICES_KEYPAD_KEYPAD_SOCKET_H_

#include "stm32f3xx_hal.h"

class Keypad_socket
{
public:

  typedef struct {
	GPIO_TypeDef* 	RowPort;
	uint32_t 		RowBitmask;
	GPIO_TypeDef*	ColPort;
	uint32_t 		ColBitmask;
  } keypad_pinspack_type;

  keypad_pinspack_type *keypad_pinspack;
  Keypad_socket (keypad_pinspack_type *keypad_pinspack);

  void    	setRowPort_Listening(void);
  void    	setColPort_Input(void);
  void    	setRowPort_Output(void);
  void    	setColPort_Output(void);
  uint16_t 	getRowPort(void);
  uint16_t 	getColPort(void);

};

#endif /* DEVICES_KEYPAD_KEYPAD_SOCKET_H_ */
