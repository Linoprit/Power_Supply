/*
 * Opamp_socket.h
 *
 *  Created on: 21.12.2017
 *      Author: harald
 */

#ifndef CONTROLLER_OPAMP_SOCKET_H_
#define CONTROLLER_OPAMP_SOCKET_H_

#include "stm32f3xx_hal.h"



class Opamp_socket
{
public:
  enum gain_enum { gain_none = 0, gain_2 = 2, gain_4 = 4, gain_8 = 8, gain_16 = 16};

  Opamp_socket(OPAMP_HandleTypeDef* opamp_in);
  virtual ~Opamp_socket() { };

  void set_gain(gain_enum gain_in);
  gain_enum get_gain(void);
  void increment_gain(void);
  void decrement_gain(void);


private:
  OPAMP_HandleTypeDef* 	opamp;
  gain_enum				old_gain;
};

#endif /* CONTROLLER_OPAMP_SOCKET_H_ */
