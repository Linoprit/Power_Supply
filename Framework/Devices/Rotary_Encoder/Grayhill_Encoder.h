/*
 * Grayhill_Encoder.h
 *
 *  Created on: 23.01.2017
 *      Author: harald
 */

#ifndef DEVICES_ROTARY_ENCODER_GRAYHILL_ENCODER_H_
#define DEVICES_ROTARY_ENCODER_GRAYHILL_ENCODER_H_

#include "Rotary_Encoder_Types.h"


namespace rotaryEncoder {


class Grayhill_Encoder
{
public:
  Grayhill_Encoder ();
  virtual ~Grayhill_Encoder ();

  KeyEvent_enum cycle(uint8_t rotary_val);

private:
  // lookup table previous / next
  const uint8_t index_tbl[4][2] =
	  { {2, 1}, {0, 3}, {3, 0}, {1, 2} };

	uint8_t old_rotary_val;

	uint8_t get_next(uint8_t encoder_val);
	uint8_t get_previous(uint8_t encoder_val);

};

}

#endif /* DEVICES_ROTARY_ENCODER_GRAYHILL_ENCODER_H_ */
