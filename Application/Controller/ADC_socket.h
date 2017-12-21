/*
 * ADC_socket.h
 *
 *  Created on: 07.04.2017
 *      Author: harald
 */

#ifndef CONTROLLER_ADC_SOCKET_H_
#define CONTROLLER_ADC_SOCKET_H_

#include <stdint.h>
#include "Instances/callbacks.h"
#include "stm32f3xx_hal.h"

#define ADC_MAX 4096


class ADC_socket
{
public:
  ADC_socket (ADC_HandleTypeDef* hadc_in, uint8_t adc_buffer_len_in);

  virtual ~ADC_socket ();

  uint16_t 	read(void); //TODO remove

  // updates measurement and triggers new conversion
  void 		cycle_1ms(void);
  uint16_t* get_measurement(void);
  uint8_t 	get_num_of_channels(void);
  uint16_t  get_ADC_max(void) { return ADC_MAX;};


protected:
  ADC_HandleTypeDef* hadc;
  unsigned long int* adc_buffer;
  unsigned long int* measurement;
  uint8_t  			 adc_buffer_len;
  uint8_t			 num_of_channels;


  // TODO remove later
#define TEXT_BUF_LEN 4
  uint8_t text_buf[TEXT_BUF_LEN];
  void clear_text_buf(uint8_t* text_buf, uint8_t len);

};

#endif /* CONTROLLER_ADC_SOCKET_H_ */
