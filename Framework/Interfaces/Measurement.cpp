/*
 * Measurement.cpp
 *
 *  Created on: 20.12.2017
 *      Author: harald
 */

#include <Interfaces/Measurement.h>
#include "libraries/HelpersLib.h"
#include <math.h>


Measurement::Measurement(ADC_socket* adc_socket_in,
						 uint8_t channel_in)
{
  adc_socket = adc_socket_in;
  channel	 = channel_in;
  in_min 	= 0; // some save setup
  in_max 	= 100;
  out_min 	= 0.0f;
  out_max 	= 100.0f;
}

void Measurement::set_calibration(
	uint32_t _in_min_, uint32_t _in_max_, float _out_min_, float _out_max_)
{
  in_min = _in_min_;
  in_max = _in_max_;
  out_min = _out_min_;
  out_max = _out_max_;
}

int32_t Measurement::getValue_int(uint8_t decimal_places)
{
  float factor = pow(10.0f, (float) decimal_places);
  return (int32_t) (calibrate() * factor);
}

float Measurement::getValue_flt(void)
{
  return calibrate();
}

void Measurement::toString(char* buffer, uint8_t len, uint8_t decimal_places)
{
  HelpersLib::value2char(
	  (char*) &buffer[0], len, decimal_places, getValue_int(decimal_places));
}

void Measurement::cycle_1ms(void) //must call adc-cycle
{
  adc_socket->cycle_1ms();
}

float Measurement::calibrate(void)
{
  float x = (float) adc_socket->get_measurement()[channel];

  // copied from Arduino WMath.cpp, linear equation, two point form
  return (x - (float) in_min) *
	  (out_max - out_min) /
	  ((float) in_max - (float) in_min) + out_min;
}
