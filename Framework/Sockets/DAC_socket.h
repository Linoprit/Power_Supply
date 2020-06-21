/*
 * DAC_out.h
 *
 *  Created on: 02.04.2017
 *      Author: harald
 */

#ifndef CONTROLLER_DAC_SOCKET_H_
#define CONTROLLER_DAC_SOCKET_H_

#include <stdint.h>
#include "stm32f3xx_hal.h"


class DAC_socket
{
public:
  DAC_socket (DAC_HandleTypeDef* dac_handle_in, uint8_t channel_in);
  virtual ~DAC_socket ();

  void 		set(uint16_t value);
  uint16_t 	get(void);

private:
  DAC_HandleTypeDef* dac_handle;
  uint32_t channel; // 1 = DAC_CHANNEL_1 / >1 = DAC_CHANNEL_2

};

#endif /* CONTROLLER_DAC_SOCKET_H_ */
