/*
 * Measurement_OP.h
 *
 *  Created on: 21.12.2017
 *      Author: harald
 */

#ifndef INTERFACES_MEASUREMENT_OP_H_
#define INTERFACES_MEASUREMENT_OP_H_

#include "Measurement.h"
#include <Controller/Opamp_socket.h>


class Measurement_OP: public Measurement
{
public:
  Measurement_OP (ADC_socket* adc_socket_in,
				  uint8_t channel_in,
				  Opamp_socket* OP_socket_in);
  virtual ~Measurement_OP() { };

  void cycle_1ms(void);



private:
  Opamp_socket* OP_socket;

};

#endif /* INTERFACES_MEASUREMENT_OP_H_ */
