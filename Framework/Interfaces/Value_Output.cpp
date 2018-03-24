/*
 * Value_Output.cpp
 *
 *  Created on: 01.01.2018
 *      Author: harald
 */

#include <Interfaces/Value_Output.h>
#include "libraries/HelpersLib.h"
#include <math.h>


Value_Output::Value_Output (DAC_socket* dac_socket_in)
{
  dac_socket = dac_socket_in;

  in_min 	 = 0.0f; // some save setup
  in_max 	 = 32.0f;
  out_min 	 = 0;
  out_max 	 = 4095;
}

void Value_Output::set_calibration(
	float _in_min_, float _in_max_, uint32_t _out_min_, uint32_t _out_max_)
{
  in_min  = _in_min_;
  in_max  = _in_max_;
  out_min = _out_min_;
  out_max = _out_max_;
}

void Value_Output::setValue_int(uint32_t value, uint8_t decimal_places)
{
  float setValue = ((float) value) /  pow(10.0f, (float) decimal_places);
  set_Value_float( setValue );
}

void Value_Output::set_Value_float(float value)
{
  float tmp_output =
	  ( (value - in_min) *  ( (float) out_max - (float) out_min) /
		  (in_max - in_min)
		  + (float) out_min ) +0.5f ;

  uint32_t output = (uint32_t) tmp_output;

  if (output > out_max)
	output = out_max;
  if(output < out_min)
	output = out_min;

  dac_socket->set((uint16_t) output);





}

void Value_Output::setDAC(uint16_t value)
{
  dac_socket->set(value);
}

int32_t Value_Output::getValue_int(uint8_t decimal_places)
{
  float factor = pow(10.0f, (float) decimal_places);
  return (int32_t) ( (get_Value_float() * factor) +0.5 );
}

float Value_Output::get_Value_float(void)
{
  uint16_t out = dac_socket->get();
  float value;

  value = ((float) out - (float) out_min) * (in_max - in_min) /
	  ( (float) out_max - (float) out_min )
	  + in_min;

  return value;
}

uint16_t Value_Output::getDAC(void)
{
  return (uint16_t) dac_socket->get();
}

void Value_Output::toString(char* buffer, uint8_t len, uint8_t decimal_places)
{
  HelpersLib::value2char(
	  (char*) &buffer[0], len, decimal_places, getValue_int(decimal_places));
}
