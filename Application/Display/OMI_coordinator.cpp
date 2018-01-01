/*
 * OMI_coordinator.cpp
 *
 *  Created on: 12.03.2017
 *      Author: harald
 */

#include <Display/OMI_coordinator.h>
#include "Instances/Common.h"



OMI_coordinator::OMI_coordinator ()
{
  screen_class 	= new Screens();
  menu_class  	= new Menus();

  SoftwareEvents::hookIn(this, SoftwareEvents::btn_held);
  SoftwareEvents::hookIn(this, SoftwareEvents::btn_pressed);
  SoftwareEvents::hookIn(this, SoftwareEvents::btn_released);

  actv_dspl = SCREENS;
  old_event	= SoftwareEvents::None;

  screen_class->hook_in();
}

OMI_coordinator::~OMI_coordinator () { }


void OMI_coordinator::software_event_callback(
	SoftwareEvents::Event_Names_enum event_name)
{
  Rotary_Encoder::last_key_enum last_key =
	  Common::get_rotary_encoder()->get_last_key();

  if ( (last_key == Rotary_Encoder::btn_4) &&
	  (event_name == SoftwareEvents::btn_held) )
	{
	  // menu button was held, switch screens and menus
	  if (actv_dspl == SCREENS)
		{
		  screen_class->hook_off();

		  actv_dspl = MENUS;
		  menu_class->hook_in();


		}
	  else
		{
		  actv_dspl = SCREENS;
		  menu_class->hook_off();

		  screen_class->hook_in();
		}
	}

  if ( (last_key == Rotary_Encoder::btn_4) &&
	  (event_name == SoftwareEvents::btn_released) &&
	  (old_event  == SoftwareEvents::btn_pressed))
	{
	  if (actv_dspl == SCREENS)
		screen_class->increment();

	  if(actv_dspl == MENUS)
		menu_class->increment();
	}

  old_event = event_name;
}

void OMI_coordinator::update_values(void)
{

}

void OMI_coordinator::loop_5ms(void)
{
  Common::get_char_lcd()->display_step();
}



void OMI_coordinator::loop_50ms(void)
{
  if (actv_dspl == SCREENS)
	screen_class->loop_50ms();
  else
	menu_class->loop_50ms();

}
