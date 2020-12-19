/*
 * DAC_out.cpp
 *
 *  Created on: 02.04.2017
 *      Author: harald
 */

#include "DAC_socket.h"
#include "libraries/HelpersLib.h"


DAC_socket::DAC_socket (DAC_HandleTypeDef* dac_handle_in, uint8_t channel_in)
{
  this->dac_handle  = dac_handle_in;

  if(channel_in == 1)
	this->channel = DAC_CHANNEL_1;
  else
	this->channel = DAC_CHANNEL_2;

  HAL_DAC_Init(dac_handle);
  HAL_DAC_Start(dac_handle, channel);
}

DAC_socket::~DAC_socket () { }


void DAC_socket::set(uint16_t value)
{
  HAL_DAC_SetValue(dac_handle, channel, DAC_ALIGN_12B_R, (uint32_t) value);



}

uint16_t DAC_socket::get(void)
{
  uint32_t result = HAL_DAC_GetValue(dac_handle, channel);
  return (uint16_t) result;
}

// TODO Delete
  //char buffer[6];

  //HAL_StatusTypeDef result;

 // HAL_DAC_GetValue(get_hdac1(), 1);


  /*
  value = (uint16_t) Common::get_u_soll()->getValue();
  value = value * 200;

  HelpersLib::value2char(&buffer[0], 5, 0, (long int) value);
  buffer[5] = ' ';
  Error_messaging::write((const char*) &buffer[0], 6);


  result = HAL_DAC_SetValue(
	  get_hdac1(), DAC_CHANNEL_1, DAC_ALIGN_12B_R, (uint32_t) value);

  Error_messaging::print_hal_status(result);
  Error_messaging::write((const char*) " ", 1);

  result = HAL_DAC_Start(get_hdac1(), DAC_CHANNEL_1);

  Error_messaging::print_hal_status(result);
  Error_messaging::write((const char*) "\n", 1);
  */



