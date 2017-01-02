/*
 * MainClass.cpp
 *
 *  Created on: 28.10.2015
 *      Author: harald
 */

#include "Keypadtest.h"
#include "Instances/callbacks.h"


Keypadtest::Keypadtest ()
{
  old_cycle = 0;
  act_cycle = 0;
  lastKey   = NULL;

  // must be initialised in framework
  LCD		  = Common::get_LCD_grfx();
  LCD->switch_font(FONT_5x8);

  textbuffer_len = 17;
  textbuffer = (char*)malloc(textbuffer_len * sizeof (char));

  // we initialise devices in common.cpp
  //init_keypad();
  keypad = Common::get_keypad();
}

void Keypadtest::init_keypad(void)
{
  Keypad_socket::keypad_pinspack_type*
  keypad_pinspack = new Keypad_socket::keypad_pinspack_type
  {
				Key_Row_0_GPIO_Port,
	(uint32_t) 	0b00001111,
				Key_Col_0_GPIO_Port,
	(uint32_t) 	0b01110000
  };

  Keypad_socket* keypad_socket = new Keypad_socket(keypad_pinspack);
  keypad = new Keypad(keypad_socket);
}

void Keypadtest::Do_keypadtest (void)
{
  SoftwareEvents* 	sw_events 	= Common::get_sw_events();

  while(1)
	{
	  act_cycle = HAL_GetTick();
	  sw_events->loop();
	  loop();
	}
}


void Keypadtest::loop (void)
{
  if (act_cycle - old_cycle >= 2)
     {
       old_cycle = act_cycle;

       lastKey = keypad->getLastRawKey();

       // print lastKey col / row
       clearTextbuffer(textbuffer_len);
       strncpy(&textbuffer[0], (const char*) "Col:", 4);
       HelpersLib::value2char(&textbuffer[4], 2, 0, lastKey->col);
       strncpy(&textbuffer[7], (const char*) "Row:", 4);
       HelpersLib::value2char(&textbuffer[11], 2, 0, lastKey->row);
       LCD->write_string(0, LCD->conv_line_2_y_pix(1), textbuffer);

       // line 2, print key-state
       clearTextbuffer(textbuffer_len);
       strncpy(&textbuffer[0], (const char*) "B-State:", 8);
       HelpersLib::value2char(&textbuffer[9], 2, 0,
			      keypad->getActualKeyState());
       LCD->write_string(0, LCD->conv_line_2_y_pix(2), textbuffer);

       // line 3 command-ID
       clearTextbuffer(textbuffer_len);
       strncpy(&textbuffer[0], (const char*) "Command-ID:", 11);
       HelpersLib::value2char(&textbuffer[12], 2, 0,
       			      keypad->getLastKeyCommand());
       LCD->write_string(0, LCD->conv_line_2_y_pix(3), textbuffer);

       // line 4 char
       clearTextbuffer(textbuffer_len);
       strncpy(&textbuffer[0], (const char*) "Char:", 5);
       textbuffer[6] = keypad->getLastChar();
       LCD->write_string(0, LCD->conv_line_2_y_pix(4), textbuffer);

       // line 3 cycle count as alive-counter
       clearTextbuffer(textbuffer_len);
       strncpy(&textbuffer[0], (const char*) "Cycle:", 6);
       HelpersLib::value2char(
	   &textbuffer[7], 9, 0, act_cycle);
       LCD->write_string(0, LCD->conv_line_2_y_pix(5), textbuffer);

       LCD->display();
     }
}

void Keypadtest::clearTextbuffer(uint8_t len)
{
  for (uint8_t i=0; i < len; i++)
       textbuffer[i] = ' ';
  textbuffer[textbuffer_len-1] = '\0';
}


