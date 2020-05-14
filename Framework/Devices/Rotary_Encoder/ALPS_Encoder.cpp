/*
 * Rotary_Encoder_State_Machine.cpp
 *
 *  Created on: 06.01.2017
 *      Author: harald
 */

#include <Devices/Rotary_Encoder/ALPS_Encoder.h>

namespace rotaryEncoder {

ALPS_Encoder::ALPS_Encoder ()
{
  state = off;
  old_rotary_val = 0;
}

ALPS_Encoder::~ALPS_Encoder ()
{ }

KeyEvent_enum ALPS_Encoder::cycle(uint8_t rotary_val)
{
  if (old_rotary_val == rotary_val)
	return evntNone;

  old_rotary_val = rotary_val;

  if ((state == off) && (rotary_val == 2))
	{
	  state = uz1;
	  return evntNone;
	}

  if ((state == uz1) && (rotary_val == 00))
	{
	  state = off;
	  return evntIncrement;
	}

  if ((state == off) && (rotary_val == 1))
	{
	  state = gz1;
	  return evntNone;
	}

  if ((state == gz1) && (rotary_val == 00))
	{
	  state = off;
	  return evntDecrement;
	}

  state = off;
  return evntNone;
}

}
