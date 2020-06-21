/*
 * ADC_socket.h
 *
 *  Created on: 07.04.2017
 *      Author: harald
 */

#ifndef CONTROLLER_ADC_SOCKET_H_
#define CONTROLLER_ADC_SOCKET_H_

#include <stdint.h>
#include "stm32f3xx_hal.h"
#include <array>



constexpr uint16_t ADC_MAX = 4096;

class ADC_socket
{
public:
	ADC_socket (
			ADC_HandleTypeDef* hadc, uint8_t numOfChannels, uint8_t adcBufferLen = 2);

	virtual ~ADC_socket() {};

	// updates measurement and triggers new conversion
	void 		cycle_1ms(void);

	// access to all channels measured mean values
	uint16_t* get_measurement(void);
	uint8_t 	get_num_of_channels(void);
	uint16_t  get_ADC_max(void) { return ADC_MAX; };


protected:
	ADC_HandleTypeDef* 	_hadc;
	uint8_t  						_adcBufferLen;
	unsigned long int* 	_adcBuffer;
	uint16_t* 					_measurement;
	//std::array<uint16_t>  				_measurement;
	uint32_t 						_old_cycle;
	uint8_t			 				_numOfChannels;
};

#endif /* CONTROLLER_ADC_SOCKET_H_ */
