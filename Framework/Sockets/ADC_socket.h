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

#define ADC_MAX 4096


class ADC_socket
{
public:
  ADC_socket (ADC_HandleTypeDef* hadc, uint8_t num_of_channels, uint8_t nr_of_conversions);

  virtual ~ADC_socket ();

  // updates measurement and triggers new conversion
  void 		cycle(void);
  uint16_t* get_measurement(void);
  uint8_t 	get_num_of_channels(void);
  const uint16_t  get_ADC_max(void) { return ADC_MAX;};
  uint16_t* get_adc_buffer(void);

protected:
  ADC_HandleTypeDef* _hadc;
  uint16_t* 				 _adc_buffer;
  uint16_t* 		 		 _measurement;
  uint8_t			 	 		 _num_of_channels;
  uint8_t 					 _nr_of_conversions;

};

#endif /* CONTROLLER_ADC_SOCKET_H_ */
