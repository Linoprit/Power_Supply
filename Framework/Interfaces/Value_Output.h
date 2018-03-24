/*
 * Value_Output.h
 *
 *  Created on: 01.01.2018
 *      Author: harald
 */

#ifndef INTERFACES_VALUE_OUTPUT_H_
#define INTERFACES_VALUE_OUTPUT_H_

#include <stdint.h>
#include <Controller/DAC_socket.h>


class Value_Output
{
public:
  Value_Output (DAC_socket* dac_socket_in);
  virtual ~Value_Output () { };

  void set_calibration(
	  float _in_min_, float _in_max_, uint32_t _out_min_, uint32_t _out_max_);

  void setValue_int(uint32_t value, uint8_t decimal_places);

  void set_Value_float(float value);

  void setDAC(uint16_t value);

  int32_t  getValue_int(uint8_t decimal_places);

  float    get_Value_float(void);

  uint16_t getDAC(void);

  void 	   toString(char* buffer, uint8_t len, uint8_t decimal_places);


protected:
  DAC_socket* 	dac_socket;
  float 		in_min, in_max;  // soll-output nach Verstärker
  uint32_t 		out_min,out_max; // DAC Werte

};

#endif /* INTERFACES_VALUE_OUTPUT_H_ */
