/*
 * Menus.cpp
 *
 *  Created on: 12.03.2017
 *      Author: harald
 */

#include <Display/Menus.h>
#include <string.h>
#include "Devices/Char_LCD/Char_LCD.h"
#include "Instances/Common.h"
#include "libraries/HelpersLib.h"



Menus::Menus ()
{
  actv_screen 	= HI_LO_MENU;
}

Menus::~Menus () { }

void Menus::increment(void)
{
  if(actv_screen == CHARGE_MENU)
  	actv_screen = HI_LO_MENU;
    else
  	actv_screen++;

  switch (actv_screen)
  {
	case HI_LO_MENU:
	  // charge_menu.hook_off
	  Common::get_hi_lo()->hook_in();
	  break;

	case START_VALS_MENU:
	  Common::get_hi_lo()->hook_off();
	  Common::get_u_start()->hook_in();
	  Common::get_i_start()->hook_in();
	  break;

	case SWEEP_MENU:
	  Common::get_u_start()->hook_off();
	  Common::get_i_start()->hook_off();
	  break;

	case CHARGE_MENU:
	  break;
  }
}

void Menus::hook_in(void)
{
  Common::get_hi_lo()->hook_in();
}

void Menus::hook_off(void)
{
  Common::get_hi_lo()->hook_off();
  Common::get_u_start()->hook_off();
  Common::get_i_start()->hook_off();
}

void Menus::loop(void)
{
  static uint16_t i = 0;
  Char_LCD* LCD = Common::get_char_lcd();

  LCD->clear();

  if (actv_screen == HI_LO_MENU)
	{
	  // for measurement                0123456789012345
	  strncpy(&LCD->buffer_lines[0][0], "Source: ", 7);
	  Common::get_hi_lo()->toString(&LCD->buffer_lines[0][8], 4);
	}
  else if (actv_screen == START_VALS_MENU)
	{
	  // for measurement                0123456789012345
	  strncpy(&LCD->buffer_lines[0][0], "Start-up Values", 15);

	  // u_start
	  if (Common::get_u_start()->is_fine_active() == true)
		strncpy(&LCD->buffer_lines[1][0], "F", 1);
	  else
		strncpy(&LCD->buffer_lines[1][0], " ", 1);

	  Common::get_u_start()->toString(&LCD->buffer_lines[1][1], 4);
	  strncpy(&LCD->buffer_lines[1][5], "V", 1);

	  // i_start
	  if (Common::get_i_start()->is_fine_active() == true)
		strncpy(&LCD->buffer_lines[1][7], "F", 1);
	  else
		strncpy(&LCD->buffer_lines[1][7], " ", 1);

	  Common::get_i_start()->toString(&LCD->buffer_lines[1][8], 4);
	  strncpy(&LCD->buffer_lines[1][12], "A", 1);
	}
  else if (actv_screen == SWEEP_MENU)
	{
	  strncpy(&LCD->buffer_lines[0][0], "Cycle: ", 7);
	  HelpersLib::value2char(&LCD->buffer_lines[0][8], 8, 0, i++);
	  strncpy(&LCD->buffer_lines[1][0], "Menu   03", 9);
	  // template for measuring          0123456789012345
	}
  else if (actv_screen == CHARGE_MENU)
	{
	  strncpy(&LCD->buffer_lines[0][0], "Cycle: ", 7);
	  HelpersLib::value2char(&LCD->buffer_lines[0][8], 8, 0, i++);
	  strncpy(&LCD->buffer_lines[1][0], "Menu   04", 9);
	  // template for measuring          0123456789012345
	}



  LCD->display();
}
