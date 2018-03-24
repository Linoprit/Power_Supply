/*
 * Measurement.cpp
 *
 *  Created on: 20.12.2017
 *      Author: harald
 */

#include "libraries/HelpersLib.h"
#include <Instances/Common.h>
#include <Interfaces/Value_Measurement.h>
#include <math.h>


Measurement::Measurement(ADC_socket* adc_socket_in,
						 uint8_t channel_in)
{
  adc_socket = adc_socket_in;
  channel	 = channel_in;

  OP_socket  = NULL;

  in_min 	 = 0; // some save setup
  in_max 	 = 5000;
  out_min 	 = 0.0f;
  out_max 	 = 500.0f;
}

Measurement::Measurement(ADC_socket* adc_socket_in,
						 uint8_t channel_in,
						 Opamp_socket* OP_socket_in):
									   Measurement( adc_socket_in, channel_in)
{
  OP_socket = OP_socket_in;
}

void Measurement::set_calibration(
	uint32_t _in_min_, uint32_t _in_max_, float _out_min_, float _out_max_)
{
  in_min  = _in_min_;
  in_max  = _in_max_;
  out_min = _out_min_;
  out_max = _out_max_;
}

void Measurement::set_calibration(
	uint32_t _in_min_, uint32_t _in_max_, float _out_min_, float _out_max_,
	uint8_t gain)
{
  set_calibration(_in_min_, _in_max_,
				  _out_min_ * (float) gain, _out_max_ * (float) gain);
}

void Measurement::cycle_1ms(void) //must call adc-cycle
{
  if(OP_socket != NULL)
	{
	  if (IS_OVER_UPPER)
		  OP_socket->decrement_gain();

	  if (IS_BELOW_LOWER)
		  OP_socket->increment_gain();
	}

  adc_socket->cycle_1ms(Common::get_tick());
}

uint8_t Measurement::get_gain(void)
{
  if(OP_socket != NULL)
	return (uint8_t) OP_socket->get_gain();
  else
	return 1u;
}

bool Measurement::is_overrange(void)
{
  return IS_OVER_UPPER;
}

int32_t Measurement::getValue_int(uint8_t decimal_places)
{
  float factor = pow(10.0f, (float) decimal_places);
  return (int32_t) ( (get_Value_float() * factor) +0.5 );
}

uint16_t Measurement::getADC(void)
{
  return adc_socket->get_measurement()[channel-1];
}

void Measurement::toString(char* buffer, uint8_t len, uint8_t decimal_places)
{
  HelpersLib::value2char(
	  (char*) &buffer[0], len, decimal_places, getValue_int(decimal_places));
}

float Measurement::get_Value_float(void)
{
  float adc_val = (float) adc_socket->get_measurement()[channel-1];

  // copied from Arduino WMath.cpp, linear equation, two point form
  float value =
	  ( (adc_val - (float) in_min) *  (out_max - out_min) /
	  ((float) in_max - (float) in_min)
	  + out_min) / (float) get_gain();

  return value;
}
