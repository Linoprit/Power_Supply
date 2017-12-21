/*
 * Measurement_OP.cpp
 *
 *  Created on: 21.12.2017
 *      Author: harald
 */

#include <Interfaces/Measurement_OP.h>

Measurement_OP::Measurement_OP(ADC_socket* adc_socket_in,
							   uint8_t channel_in,
							   Opamp_socket* OP_socket_in):
							   Measurement( adc_socket_in, channel_in)
{
  OP_socket = OP_socket_in;
}

void Measurement_OP::cycle_1ms(void) //must call adc-cycle
{
  float act_value = this->getValue_flt();

  float upper_border =
	  ((float) adc_socket->get_ADC_max()) * 0.90f;

  float lower_border =
	  ((float) adc_socket->get_ADC_max()) * 0.10f;

  if (act_value > upper_border)
	OP_socket->decrement_gain();

  if (act_value < lower_border)
	OP_socket->increment_gain();

  adc_socket->cycle_1ms();
}
