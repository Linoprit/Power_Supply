/*
 * Rotary_Encoder.cpp
 *
 *  Created on: 31.12.2016
 *      Author: harald
 */

#include <Devices/Rotary_Encoder/Rotary_Encoder.h>
#include "stm32f3xx_hal.h"


Rotary_Encoder::Rotary_Encoder (Rotary_Encoder_socket* socket_in)
{
  socket = socket_in;

}

Rotary_Encoder::~Rotary_Encoder ()
{ }

void Rotary_Encoder::cycle(void)
{
  uint8_t input = 0;

  if(socket->rx_ringbuffer()->HasData())
	{
	  input = socket->rx_ringbuffer()->Read();


	  if (input & mask_button_1)
		HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);

	  if (input & mask_button_2)
		HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
	}


}
