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
	return evnt_none;

  old_rotary_val = rotary_val;

  if ((state == off) && (rotary_val == 2))
	{
	  state = uz1;
	  return evnt_none;
	}

  if ((state == uz1) && (rotary_val == 00))
	{
	  state = off;
	  return rotenc_increment;
	}

  if ((state == off) && (rotary_val == 1))
	{
	  state = gz1;
	  return evnt_none;
	}

  if ((state == gz1) && (rotary_val == 00))
	{
	  state = off;
	  return rotenc_decrement;
	}

  state = off;
  return evnt_none;
}

}
