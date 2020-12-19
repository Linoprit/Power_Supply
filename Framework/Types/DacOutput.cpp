/*
 * Value_Output.cpp
 *
 *  Created on: 01.01.2018
 *      Author: harald
 */

#include "DacOutput.h"
#include "libraries/HelpersLib.h"
#include <math.h>
#include <algorithm>


DacOutput::DacOutput (DAC_socket* dac_socket_in)
{
	_dac_socket = dac_socket_in;

	_output_min 	= 0.0f; // some save setup
	_output_max 	= 32.0f;
	_dac_min 	 	= 0;
	_dac_max 	 	= 4095;
}

void DacOutput::set_calibration(
		float output_min_, float output_max_, uint32_t dac_min_, uint32_t dac_max_)
{
	_output_min  	= output_min_;
	_output_max  	= output_max_;
	_dac_min 		= dac_min_;
	_dac_max 		= dac_max_;
}

void DacOutput::setValue_float(float value) {
	float tmp_output =
			( (value - _output_min) *
					( static_cast<float>(_dac_max) - static_cast<float>(_dac_min)) /
					(_output_max - _output_min)
					+ static_cast<float>(_dac_min) ) + 0.5f ;

	uint32_t output = static_cast<uint32_t>(tmp_output);

	if (output > _dac_max)
		output = _dac_max;
	if(output < _dac_min)
		output = _dac_min;

	_dac_socket->set( static_cast<uint16_t>(output) );
}

void DacOutput::setDAC(uint16_t value) {
	_dac_socket->set(value);
}

float DacOutput::getValue(void) {
	uint16_t out = _dac_socket->get();
	float value;

	value = (static_cast<float>(out) - static_cast<float>(_dac_min))
			* (_output_max - _output_min) /
			( static_cast<float>(_dac_max) - static_cast<float>(_dac_min) )
			+ _output_min;

	return value;
}

uint16_t DacOutput::getDAC(void) {
	return (uint16_t) _dac_socket->get();
}

