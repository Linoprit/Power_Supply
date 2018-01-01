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
#include <System/scheduler.h>




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
		LCD->buffer_lines[1][0] = 'F';
	  else
		LCD->buffer_lines[1][0] = ' ';

	  Common::get_u_soll()->toString(&LCD->buffer_lines[1][1], 4);
	  LCD->buffer_lines[1][5] = 'V';

	  // i_soll
	  if (Common::get_i_soll()->is_fine_active() == true)
		LCD->buffer_lines[1][7] = 'F';
	  else
		LCD->buffer_lines[1][7] = ' ';

	  Common::get_i_soll()->toString(&LCD->buffer_lines[1][8], 4);
	  LCD->buffer_lines[1][12] = 'A';

	  // u_ist
	  scheduler::getUistPt1()->toString(&LCD->buffer_lines[0][1], 4, 1);
	  LCD->buffer_lines[0][5] = 'V';

	  // i_soll
	  scheduler::getIistPt1()->toString(&LCD->buffer_lines[0][8], 4, 1);
	  LCD->buffer_lines[0][12] = 'A';


	  // TODO remove!
	  //HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

	}
  else if (actv_screen == TEMPERATUR_SCR)

	{
	  strncpy(&LCD->buffer_lines[0][0], "Temp: ", 6);
	  scheduler::getTempPt1()->toString(&LCD->buffer_lines[0][6], 4 ,1);
	  LCD->buffer_lines[0][10] = 223; // '°'-char
	  LCD->buffer_lines[0][11] = 'C';

	  strncpy(&LCD->buffer_lines[1][0], "Uin: ", 5);
	  scheduler::getUinPt1()->toString(&LCD->buffer_lines[1][6], 4, 1);
	  LCD->buffer_lines[1][10] = 'V';
	}
  else if (actv_screen == WATTS_SCR)
	{
	  strncpy(&LCD->buffer_lines[0][0], "Cycle: ", 7);
	  HelpersLib::value2char(&LCD->buffer_lines[0][8], 8, 0, i++);
	  strncpy(&LCD->buffer_lines[1][0], "Watts-Screen", 12);
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



