/*
 * Button_State_Machine.cpp
 *
 *  Created on: 06.01.2017
 *      Author: harald
 */

#include <Devices/Rotary_Encoder/Button_Machine.h>
#include "Instances/Common.h"

namespace rotaryEncoder {


Button_Machine::Button_Machine ()
{
  state = off;
  old_ticks = 0;
}

Button_Machine::~Button_Machine ()
{ }

KeyEvent_enum Button_Machine::cycle(
	uint8_t Button_val)
{
  if((state == off) && (Button_val == 1))
	{
	  state = on;
	  old_ticks = Common::get_tick();

	  return evntNone;
	}

  if((state == on) && (Button_val == 1) &&
	  (Common::get_tick() - old_ticks > debounce_ticks))
	{
	  state = pressed;
	  return evntPressed;
	}

  if((state == pressed) && (Button_val == 1) &&
	  (Common::get_tick() - old_ticks > btn_held_ticks))
	{
	  state = held;
	  return evntHeld;
	}

  if (((state == pressed) || (state == held)) && (Button_val == 0))
	{
	  state = off;
	  return evntReleased;
	}

  if ((state == on) && (Button_val == 0))
	{
	  state = off;
	  return evntNone;
	}

  return evntNone;
}

}
