/*
 * callbacks.h
 *
 *  Created on: 17.05.2016
 *      Author: harald
 */

#ifndef CALLBACKS_H_
#define CALLBACKS_H_

#include <stdlib.h>


class ISR_callback {
public:
  virtual void ISR_callback_fcn (void) = 0;
  virtual ~ISR_callback(void) { };
};


void keypad_callback_set(ISR_callback* callback);
void keypad_callback_clear(void);

void uart1_callback_set(ISR_callback* callback);

void rotary_encoder_callback_set(ISR_callback* callback);

#endif /* CALLBACKS_H_ */
