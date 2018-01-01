/*
 * ADC_socket.cpp
 *
 *  Created on: 07.04.2017
 *      Author: harald
 */

#include <Controller/ADC_socket.h>
#include "Instances/callbacks.h"
#include <string.h>


// TODO remove
//#include "Instances/Common.h"
#include "System/Error_messaging.h"
#include "libraries/HelpersLib.h"



#define BUFFER_LEN 8



ADC_socket::ADC_socket (ADC_HandleTypeDef* hadc_in,
						uint8_t num_of_channels_in)
{
  old_cycle = 0;
  hadc 			  = hadc_in;
  num_of_channels = num_of_channels_in;

  adc_buffer_len = (uint8_t) (BUFFER_LEN *  num_of_channels_in);
  adc_buffer 	 = new unsigned long int[adc_buffer_len];
  memset(adc_buffer, 0, adc_buffer_len);

  measurement	= new uint16_t[num_of_channels_in];
  memset(measurement, 0, num_of_channels_in);

  HAL_ADC_Start_DMA(hadc, adc_buffer, adc_buffer_len);
}

ADC_socket::~ADC_socket () { }

void ADC_socket::cycle_1ms(uint32_t tick)
{
  // prevent starting the adc several times in one cycle
  if (old_cycle == tick)
	return;
  old_cycle = tick;

  uint8_t i=0, j=0;
  unsigned long int tmp_akku = 0;

  for(i=0; i < num_of_channels; i++)
	{
	  for (j=0+i; j < adc_buffer_len; j= (uint8_t) (j+num_of_channels) )
		{
		  tmp_akku += adc_buffer[j];
		}
	  measurement[i] = (uint16_t) tmp_akku / BUFFER_LEN;
	  tmp_akku = 0;
	}

  HAL_ADC_Start_DMA(hadc, adc_buffer, adc_buffer_len);
}

uint16_t* ADC_socket::get_measurement(void)
{
  return (uint16_t*) measurement;
}

uint8_t ADC_socket::get_num_of_channels(void)
{
  return num_of_channels;
}

void ADC_socket::print_values(void)
{
#define TEXT_BUF_LEN 4
  uint8_t text_buf[TEXT_BUF_LEN];

  for (uint8_t i=0; i < num_of_channels; i++)
	{
	  HelpersLib::value2char((char*) &text_buf[0], TEXT_BUF_LEN, 0, measurement[i]);
	  Error_messaging::write((char*) &text_buf[0], TEXT_BUF_LEN);
	  Error_messaging::write((char*) " ", 1);
	}
}



