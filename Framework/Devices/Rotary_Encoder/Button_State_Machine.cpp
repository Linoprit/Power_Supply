/*
 * Button_State_Machine.cpp
 *
 *  Created on: 06.01.2017
 *      Author: harald
 */

#include <Devices/Rotary_Encoder/Button_State_Machine.h>
#include "Instances/Common.h"


Button_State_Machine::Button_State_Machine ()
{
  state = off;
  old_ticks = 0;
}

Button_State_Machine::~Button_State_Machine ()
{ }

SoftwareEvents::Event_Names_enum Button_State_Machine::cycle(
	uint8_t Button_val)
{
  if((state == off) && (Button_val == 1))
	{
	  state = on;
	  old_ticks = Common::get_tick();

	  return SoftwareEvents::None;
	}

  if((state == on) && (Button_val == 1) &&
	  (Common::get_tick() - old_ticks > debounce_ticks))
	{
	  state = pressed;
	  return SoftwareEvents::btn_pressed;
	}

  if((state == pressed) && (Button_val == 1) &&
	  (Common::get_tick() - old_ticks > btn_held_ticks))
	{
	  state = held;
	  return SoftwareEvents::btn_held;
	}

  if (((state == pressed) || (state == held)) && (Button_val == 0))
	{
	  state = off;
	  return SoftwareEvents::btn_released;
	}

  if ((state == on) && (Button_val == 0))
	{
	  state = off;
	  return SoftwareEvents::None;
	}

  return SoftwareEvents::None;
}
