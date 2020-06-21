/*
 * Value_Output.h
 *
 *  Created on: 01.01.2018
 *      Author: harald
 */

#ifndef INTERFACES_VALUE_OUTPUT_H_
#define INTERFACES_VALUE_OUTPUT_H_

#include <stdint.h>
#include <Sockets/DAC_socket.h>


class DacOutput
{
public:
  DacOutput (DAC_socket* dac_socket_in);
  virtual ~DacOutput () { };

  void set_calibration(
	  float output_min_, float output_max_, uint32_t dac_min_, uint32_t dac_max_);

  void 			setValue_float(float value);
  void 			setDAC(uint16_t value);
  float    	getValue(void);
  uint16_t 	getDAC(void);

protected:
  DAC_socket* 	_dac_socket;
  float 				_output_min;		// soll-output an Klemme
	float 				_output_max;
  uint32_t 			_dac_min;				// berechnete DAC Werte
	uint32_t			_dac_max;

};

#endif /* INTERFACES_VALUE_OUTPUT_H_ */
