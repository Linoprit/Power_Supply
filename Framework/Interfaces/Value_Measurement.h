/*
 * Measurement.h
 *
 *  Created on: 20.12.2017
 *      Author: harald
 */

#ifndef INTERFACES_VALUE_MEASUREMENT_H_
#define INTERFACES_VALUE_MEASUREMENT_H_

#include <stdint.h>
#include <Controller/ADC_socket.h>
#include <Controller/Opamp_socket.h>


class Measurement
{
#define UPPER_BORDER ( ((float) adc_socket->get_ADC_max()) * 0.90f )
#define LOWER_BORDER ( ((float) adc_socket->get_ADC_max()) * 0.20f )

#define IS_OVER_UPPER  ( (float) getADC() > UPPER_BORDER )
#define IS_BELOW_LOWER ( (float) getADC() < LOWER_BORDER )


public:
  // If we have other sources of measurement later (and with that other sockets),
  // we could create an abstract class of ADC_socket and use it here.
  Measurement (ADC_socket* adc_socket_in, uint8_t channel_in);
  Measurement (ADC_socket* adc_socket_in,
			   uint8_t channel_in,
			   Opamp_socket* OP_socket_in);

  virtual ~Measurement () { };

  void set_calibration(
  	uint32_t _in_min_, uint32_t _in_max_, float _out_min_, float _out_max_);
  void set_calibration(
  	uint32_t _in_min_, uint32_t _in_max_, float _out_min_, float _out_max_,
  	uint8_t gain);

  bool is_overrange(void);

  int32_t  getValue_int(uint8_t decimal_places);

  float    get_Value_float(void);

  uint16_t getADC(void);

  void 	   toString(char* buffer, uint8_t len, uint8_t decimal_places);

  void 	   cycle_1ms(void);

  uint8_t get_gain(void);


protected:
  ADC_socket* 	adc_socket;
  Opamp_socket* OP_socket;
  uint32_t 		in_min, in_max; // ADC-readings
  float 		out_min,out_max;   // output values
  uint8_t 		channel;

};

#endif /* INTERFACES_VALUE_MEASUREMENT_H_ */
