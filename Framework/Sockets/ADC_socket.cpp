/*
 * ADC_socket.cpp
 *
 *  Created on: 07.04.2017
 *      Author: harald
 */

#include <Sockets/ADC_socket.h>
#include "Instances/callbacks.h"
#include <string.h>

/**
 * hadc: ADC to use i.e. hadc1
 * num_of_channels: how many measurements are used. I.e. if IN1 and IN2 are used,
 * 		num_of_channels = 2
 * nr_of_conversions: same as in cube configured. I.e if IN1 and IN2 are mesured
 * 		two times, nr_of_conversions = 4. This value must be dividable by 2!!
 * 	In Cube the ranks must be alternating, i.e. IN1 - IN2 - IN1 - IN2.
 */
ADC_socket::ADC_socket (
		ADC_HandleTypeDef* hadc, uint8_t num_of_channels, uint8_t nr_of_conversions)
{
  _hadc 			  			= hadc;
  _num_of_channels 		= num_of_channels;
  _nr_of_conversions 	= nr_of_conversions;

  _adc_buffer 	 = new uint16_t [_nr_of_conversions];
  memset(_adc_buffer, 0, _nr_of_conversions * sizeof(uint16_t));

  _measurement	= new uint16_t[num_of_channels];
  memset(_measurement, 0, num_of_channels * sizeof(uint16_t));
}

ADC_socket::~ADC_socket () { }

void ADC_socket::cycle(void)
{
 /* uint8_t i=0, j=0;
  uint32_t tmp_akku = 0;


  volatile uint32_t tmp_meas = 0;
  for(i=0; i < _nr_of_conversions; i++) {
  	tmp_meas = _adc_buffer[i];
  }
  _measurement[0] = _adc_buffer[0];
  _measurement[1]	= _adc_buffer[1];*/

  /*for(i=0; i < _num_of_channels; i++)
	{
	  for (j=0+i; j < _nr_of_conversions; j= (uint8_t) (j + _num_of_channels) )
		{
		  tmp_akku += _adc_buffer[j];
		  tmp_meas = _adc_buffer[j];
		}
	  _measurement[i] = (uint16_t) tmp_akku / _num_of_channels;
	  tmp_akku = 0;
	}*/

  HAL_ADC_Start_DMA(_hadc, (uint32_t*) _adc_buffer, _nr_of_conversions);
}

uint16_t* ADC_socket::get_adc_buffer(void)
{
  return (uint16_t*) _adc_buffer;
}


uint16_t* ADC_socket::get_measurement(void)
{
  return (uint16_t*) _measurement;
}

uint8_t ADC_socket::get_num_of_channels(void)
{
  return _num_of_channels;
}




