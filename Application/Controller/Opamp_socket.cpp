/*
 * Opamp_socket.cpp
 *
 *  Created on: 21.12.2017
 *      Author: harald
 */

#include <Controller/Opamp_socket.h>

Opamp_socket::Opamp_socket (OPAMP_HandleTypeDef* opamp_in)
{
  opamp = opamp_in;
  HAL_OPAMP_Start(opamp);
}

void Opamp_socket::set_gain(gain_enum gain_in)
{
  switch (gain_in)
  {
	case gain_none:
	  break;
	case gain_2:
	  opamp->Init.PgaGain = OPAMP_PGA_GAIN_2;
	  break;
	case gain_4:
	  opamp->Init.PgaGain = OPAMP_PGA_GAIN_4;
	  break;
	case gain_8:
	  opamp->Init.PgaGain = OPAMP_PGA_GAIN_8;
	  break;
	case gain_16:
	  opamp->Init.PgaGain = OPAMP_PGA_GAIN_16;
	  break;
  }

  HAL_OPAMP_Init(opamp);
}

Opamp_socket::gain_enum Opamp_socket::get_gain(void)
{
  switch (opamp->Init.PgaGain)
  {
	case OPAMP_PGA_GAIN_2:
	  return gain_2;
	  break;
	case OPAMP_PGA_GAIN_4:
	  return gain_4;
	  break;
	case OPAMP_PGA_GAIN_8:
	  return gain_8;
	  break;
	case OPAMP_PGA_GAIN_16:
	  return gain_16;
	  break;

	default:
	  return gain_none;
  }
}

void Opamp_socket::increment_gain(void)
{
  uint8_t new_gain = (uint8_t) ((unsigned int) get_gain() * 2u) ;

  if(new_gain > (uint8_t) gain_16)
	new_gain = (uint8_t) gain_16;

  set_gain((gain_enum) new_gain);
}

void Opamp_socket::decrement_gain(void)
{
  uint8_t new_gain = ((uint8_t) get_gain()) / 2u;

  if(new_gain < (uint8_t) gain_2)
	new_gain = (uint8_t) gain_2;

  set_gain((gain_enum) new_gain);
}
