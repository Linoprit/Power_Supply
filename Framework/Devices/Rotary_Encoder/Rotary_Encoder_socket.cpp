/*
 * Rotary_Encoder_socket.cpp
 *
 *  Created on: 31.12.2016
 *      Author: harald
 */

#include <Devices/Rotary_Encoder/Rotary_Encoder_socket.h>
#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_i2c.h"


namespace rotaryEncoder {

Rotary_Encoder_socket::Rotary_Encoder_socket ():
_ringbuffer(socketQueueLen)
{
	_i2c_handle = NULL;
}

Rotary_Encoder_socket::Rotary_Encoder_socket(
	I2C_HandleTypeDef* i2c_handle_in):
		_ringbuffer(socketQueueLen)
{
  _i2c_handle = i2c_handle_in;
  add_rotary_encoder_callback((ISR_callback*) this);

  // do initial readout, to clear PCF8574 INT-line
  ISR_callback_fcn();
}

Rotary_Encoder_socket::~Rotary_Encoder_socket ()
{}

void Rotary_Encoder_socket::ISR_callback_fcn(void)
{
  uint8_t data = 0;
  HAL_StatusTypeDef status;

  // Blocking 180us... do we need a second callback?
  status = HAL_I2C_Master_Receive(_i2c_handle, device_address, &data, 1, Timeout);

  if (status == HAL_OK)
	  _ringbuffer.enqueue((uint8_t) ~data);
}

SimpleQueue<uint8_t>* Rotary_Encoder_socket::get_rx_queue(void)
{
  return &_ringbuffer;
}

}
