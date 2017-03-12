/*
 * Char_LCD_test.cpp
 *
 *  Created on: 09.01.2017
 *      Author: harald
 */

#include "Char_LCD_test.h"
#include <string.h>
#include "Instances/Common.h"
#include "Devices/Char_LCD/Char_LCD_socket.h"
#include "libraries/HelpersLib.h"


Char_LCD_test::Char_LCD_test ()
{
  SPI_HandleTypeDef* spi = get_SPI_3();

  Char_LCD_socket::char_LCD_pinspack_type*
  char_LCD_pinspack = new Char_LCD_socket::char_LCD_pinspack_type
  {
	Char_LCD_RS_GPIO_Port,
	Char_LCD_EN_GPIO_Port,
	Char_LCD_RS_Pin,
	Char_LCD_EN_Pin
  };

  Char_LCD_socket*	socket =
	  new Char_LCD_socket(spi, char_LCD_pinspack);

  LCD = new Char_LCD(socket);
  buffer_lines = LCD->get_buffer_lines_ptr();
}


Char_LCD_test::~Char_LCD_test ()
{ }


void Char_LCD_test::loop(void)
{
  uint32_t old_ticks = 0;


  LCD->init();


  while(1)
	{
	  if (Common::get_tick() - old_ticks > 100)
		{
		  do_LCD_print();

		  old_ticks = Common::get_tick();
		}
	}
}

void Char_LCD_test::do_LCD_print(void)
{
	static uint16_t i = 0;

	// for measurement                 0123456789012345
	strncpy(&LCD->buffer_lines[0][0], "Cycle: ", 7);
	HelpersLib::value2char(&LCD->buffer_lines[0][8], 8, 0, i++);
	strncpy(&LCD->buffer_lines[1][0], "0123456789012345", 16);
	// template for measuring          0123456789012345

	// You could step through every line...
	//for (uint8_t i=0; i<4; i++)
	//  LCD->display_step();
	// ...or push them all to the display
	LCD->display();
}





