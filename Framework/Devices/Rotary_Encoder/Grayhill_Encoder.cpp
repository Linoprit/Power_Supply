/*
 * Grayhill_Encoder.cpp
 *
 *  Created on: 23.01.2017
 *      Author: harald
 */

#include <Devices/Rotary_Encoder/Grayhill_Encoder.h>
#include "stm32f3xx_hal.h"

namespace rotaryEncoder {


Grayhill_Encoder::Grayhill_Encoder ()
{
  old_rotary_val = 0;
}

Grayhill_Encoder::~Grayhill_Encoder ()
{ }

KeyEvent_enum Grayhill_Encoder::cycle(uint8_t rotary_val)
{
  KeyEvent_enum event = evntNone;

  if (rotary_val == get_next(old_rotary_val))
	event = evntIncrement;

  if (rotary_val == get_previous(old_rotary_val))
	event = evntDecrement;

  old_rotary_val = rotary_val;
  return event;
}

uint8_t Grayhill_Encoder::get_next(uint8_t encoder_val)
{
  return index_tbl[encoder_val][1];
}

uint8_t Grayhill_Encoder::get_previous(uint8_t encoder_val)
{
  return index_tbl[encoder_val][0];
}

}
