/*
 * ADC_socket.cpp
 *
 *  Created on: 07.04.2017
 *      Author: harald
 */

#include <Sockets/ADC_socket.h>
#include <Instances/Common.h>
#include <string.h>


/**
 * hadc: ADC to use i.e. hadc1
 * numOfChannels: how many measurements are used. I.e. if IN1 and IN2 are used,
 * 		numOfChannels = 2
 * nrOfMeasurementsPerCycle: same as in cube configured. I.e if IN1 and IN2 are measured
 * 		two times, nrOfMeasurementsPerCycle = 4. This value must be divideable by 2!!
 * 	In Cube the ranks must be alternating, i.e. IN1 - IN2 - IN1 - IN2.
 */
ADC_socket::ADC_socket (
		ADC_HandleTypeDef* hadc, uint8_t numOfChannels, uint8_t nrOfMeasurementsPerCycle):
		_hadc 					{ hadc },
		_adcBufferLen 	{ (uint8_t) (nrOfMeasurementsPerCycle *  numOfChannels) },
		_adcBuffer 			{ new unsigned long int[_adcBufferLen] },
		_measurement 		{ new uint16_t[numOfChannels] },
		_old_cycle 			{ 0 },
		_numOfChannels 	{ numOfChannels }
{
  memset(_adcBuffer, 		0, _adcBufferLen);
  memset(_measurement, 	0, numOfChannels);
}

void ADC_socket::cycle_1ms()
{
	// prevent starting the adc several times in one cycle
uint32_t tick = Common::get_tick();
  if (_old_cycle == tick) {
  	return;
  }
  _old_cycle = tick;

  uint8_t i = 0;
  uint8_t	j = 0;
  uint8_t count = 0;
  unsigned long int tmp_akku = 0;

  for(i=0; i < _numOfChannels; i++)
	{
	  for (j=0+i; j < _adcBufferLen; j= (uint8_t) (j+_numOfChannels) )
		{
		  tmp_akku += _adcBuffer[j];
		  count++;
		}
	  _measurement[i] = (uint16_t) tmp_akku / count;
	  tmp_akku = 0;
	  count = 0;
	}

  HAL_ADC_Start_DMA(_hadc, _adcBuffer, _adcBufferLen);
}

uint16_t* ADC_socket::get_measurement(void)
{
  return (uint16_t*) _measurement;
}

uint8_t ADC_socket::get_num_of_channels(void)
{
  return _numOfChannels;
}




