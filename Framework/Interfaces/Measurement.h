/*
 * Measurement.h
 *
 *  Created on: 20.12.2017
 *      Author: harald
 */

#ifndef INTERFACES_MEASUREMENT_H_
#define INTERFACES_MEASUREMENT_H_

#include <stdint.h>
#include "../Application/Controller/ADC_socket.h"


// TODO create another class which takes an OP_socket as second argument,
//      and implement autorange function.

class Measurement
{
public:
  // If we have other sources of measurement later (and with that other sockets),
  // we could create an abstract class of ADC_socket and use it here.
  Measurement (ADC_socket* adc_socket_in, uint8_t channel_in);
  virtual ~Measurement () { };

  void set_calibration(
  	uint32_t _in_min_, uint32_t _in_max_, float _out_min_, float _out_max_);
  int32_t  getValue_int(uint8_t decimal_places);
  float	   getValue_flt(void);
  void 	   toString(char* buff, uint8_t len, uint8_t decimal_places);

  void 		cycle_1ms(void); //must call adc-cycle


protected:
  ADC_socket* adc_socket;

private:

  uint32_t in_min, in_max; // ADC-readings
  float out_min,out_max;   // output values
  uint8_t channel;
  float calibrate(void);



};

#endif /* INTERFACES_MEASUREMENT_H_ */
