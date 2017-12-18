/*
 * DAC_out.cpp
 *
 *  Created on: 02.04.2017
 *      Author: harald
 */

#include <Controller/DAC_socket.h>
#include "System/Error_messaging.h"
#include "libraries/HelpersLib.h"


DAC_socket::DAC_socket ()
{


}

DAC_socket::~DAC_socket () { }


void DAC_socket::set(uint16_t value)
{
  char buffer[6];

  HAL_StatusTypeDef result;

  // TODO implement DAC functionality
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

}

