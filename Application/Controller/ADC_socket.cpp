/*
 * ADC_socket.cpp
 *
 *  Created on: 07.04.2017
 *      Author: harald
 */

#include <Controller/ADC_socket.h>
#include "Instances/callbacks.h"
#include <string.h>
#include "libraries/HelpersLib.h"
#include "System/Error_messaging.h"

// TODO remove
#include "Instances/Common.h"


#define BUFFER_LEN 8



ADC_socket::ADC_socket (ADC_HandleTypeDef* hadc_in,
			uint8_t num_of_channels_in)
{
  hadc 			  = hadc_in;
  num_of_channels = num_of_channels_in;

  adc_buffer_len = (uint8_t) (BUFFER_LEN *  num_of_channels_in);
  adc_buffer 	 = new unsigned long int[adc_buffer_len];
  memset(adc_buffer, 0, adc_buffer_len);

  measurement	= new unsigned long int[num_of_channels_in];
  memset(measurement, 0, num_of_channels_in);

  HAL_ADC_Start_DMA(hadc, adc_buffer, adc_buffer_len);


  // TODO Move to OP_socket class
  OPAMP_HandleTypeDef* opamp3 = get_hopamp3();
  HAL_OPAMP_Start(opamp3);

  opamp3->Init.PgaGain = OPAMP_PGA_GAIN_2;
  HAL_OPAMP_Init(opamp3);

}


ADC_socket::~ADC_socket () { }


void ADC_socket::cycle_1ms(void)
{
  uint8_t i=0, j=0;
  unsigned long int tmp_akku = 0;

  for(i=0; i < num_of_channels; i++)
	{
	  for (j=0+i; j < adc_buffer_len; j= (uint8_t) (j+num_of_channels) )
		{
		  tmp_akku += adc_buffer[j];
		}
	  measurement[i] = tmp_akku / BUFFER_LEN;
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

  // TODO remove
uint16_t ADC_socket::read(void)
{


  clear_text_buf(&text_buf[0], TEXT_BUF_LEN);

  static uint16_t j;
  HelpersLib::value2char((char*) &text_buf[0], 5, 0, (long int) j);
  Error_messaging::write((char*) &text_buf[0], 5);
  Error_messaging::write((char*) ": ", 2);
  j++;

  for (uint8_t i=0; i<adc_buffer_len; i++)
    {
	  //clear_text_buf(&text_buf[0], TEXT_BUF_LEN);
      HelpersLib::value2char((char*) &text_buf[0], TEXT_BUF_LEN, 0, (long int) adc_buffer[i]);
      Error_messaging::write((char*) &text_buf[0], TEXT_BUF_LEN);
      Error_messaging::write((char*) " ", 1);
    }
  Error_messaging::write((char*) "\n", 1);


  for(uint8_t h=0; h < num_of_channels; h++)
	{
	  HelpersLib::value2char(
		  (char*) &text_buf[0], TEXT_BUF_LEN, 0, (long int) measurement[h]);
	  Error_messaging::write((char*) &text_buf[0], TEXT_BUF_LEN);
	  Error_messaging::write((char*) " ", 1);
	}
  Error_messaging::write((char*) "\n", 1);



  //uint32_t adcRead = HAL_ADC_GetValue(hadc);
  //HelpersLib::value2char((char*) &text_buf[0], TEXT_BUF_LEN, 0, (long int) adcRead);
  //Error_messaging::write((char*) &text_buf[0], TEXT_BUF_LEN);
  //Error_messaging::write((char*) "\n", 1);








  return 0;
}

void ADC_socket::clear_text_buf(uint8_t* text_buf_in, uint8_t len)
{
  for(int i=0; i<len; i++)
	{
	  *text_buf_in = (uint8_t) '\0';
	  text_buf_in++;
	}
}

