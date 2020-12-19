/*
 * callbacks.h
 *
 *  Created on: 17.05.2016
 *      Author: harald
 */

#ifndef CALLBACKS_H_
#define CALLBACKS_H_

#include <stdlib.h>
#include "stm32f3xx_hal.h"


class ISR_callback {
public:
  virtual void ISR_callback_fcn () = 0;
  virtual ~ISR_callback(void) { };
};


void add_uart_callback(UART_HandleTypeDef *huart, ISR_callback* callback);
void add_rotary_encoder_callback(ISR_callback* callback);
void add_inaAlertPin_callback(ISR_callback* callback);

#endif /* CALLBACKS_H_ */
