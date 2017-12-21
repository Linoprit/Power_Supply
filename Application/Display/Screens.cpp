/*
 * Screens.cpp
 *
 *  Created on: 12.03.2017
 *      Author: harald
 */

#include <Display/Screens.h>
#include <string.h>
#include "Devices/Char_LCD/Char_LCD.h"
#include "Instances/Common.h"
#include "libraries/HelpersLib.h"



Screens::Screens ()
{
  actv_screen 	= UI_VALUES_SCR;



}

Screens::~Screens () { }

void Screens::increment(void)
{
  if(actv_screen == WATTS_SCR)
	actv_screen = UI_VALUES_SCR;
  else
	actv_screen++;
}


void Screens::loop_50ms(void)
{
  static uint16_t i = 0;
  Char_LCD* LCD = Common::get_char_lcd();

  LCD->clear();

  if (actv_screen == UI_VALUES_SCR)
	{
	  // u_soll
	  if (Common::get_u_soll()->is_fine_active() == true)
		strncpy(&LCD->buffer_lines[1][0], "F", 1);
	  else
		strncpy(&LCD->buffer_lines[1][0], " ", 1);

	  Common::get_u_soll()->toString(&LCD->buffer_lines[1][1], 4);
	  strncpy(&LCD->buffer_lines[1][5], "V", 1);

	  // i_soll
	  if (Common::get_i_soll()->is_fine_active() == true)
		strncpy(&LCD->buffer_lines[1][7], "F", 1);
	  else
		strncpy(&LCD->buffer_lines[1][7], " ", 1);

	  Common::get_i_soll()->toString(&LCD->buffer_lines[1][8], 4);
	  strncpy(&LCD->buffer_lines[1][12], "A", 1);

	  // TODO remove!
	  //HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

	}
  else if (actv_screen == TEMPERATUR_SCR)
	{
	  strncpy(&LCD->buffer_lines[0][0], "Cycle: ", 7);
	  HelpersLib::value2char(&LCD->buffer_lines[0][8], 8, 0, i++);
	  strncpy(&LCD->buffer_lines[1][0], "Screen 02", 9);
	  // template for measuring          0123456789012345
	}
  else if (actv_screen == WATTS_SCR)
	{
	  strncpy(&LCD->buffer_lines[0][0], "Cycle: ", 7);
	  HelpersLib::value2char(&LCD->buffer_lines[0][8], 8, 0, i++);
	  strncpy(&LCD->buffer_lines[1][0], "Screen 03", 9);
	  // template for measuring          0123456789012345
	}
}


void Screens::hook_in(void)
{
  Common::get_u_soll()->hook_in();
  Common::get_i_soll()->hook_in();
}

void Screens::hook_off(void)
{
  Common::get_u_soll()->hook_off();
  Common::get_i_soll()->hook_off();
}



