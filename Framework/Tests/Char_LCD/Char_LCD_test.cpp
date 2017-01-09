/*
 * Char_LCD_test.cpp
 *
 *  Created on: 09.01.2017
 *      Author: harald
 */

#include "Char_LCD_test.h"
#include "Instances/Common.h"
#include "Devices/Char_LCD/Char_LCD_socket.h"
#include "libraries/HelpersLib.h"


Char_LCD_test::Char_LCD_test ()
{
  SPI_HandleTypeDef* spi = get_LCD_SPI();

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
	  if (Common::get_tick() - old_ticks > 1)
		{
		  //strncpy(buffer_lines[0][0], (const char*) "btn_3", 5);
		  //LCD->display();

		  do_LCD_print();

		  old_ticks = Common::get_tick();
		}
	}
}

void Char_LCD_test::do_LCD_print(void)
{
	uint8_t i;
	long int some_value;

	// init interface and write into the buffer
	some_value = 1234567;
	// for measurement                 01234567890123456789
	strncpy(&LCD->buffer_lines[0][0], "value2char:", 11);
	HelpersLib::value2char(&LCD->buffer_lines[0][12], 8, 2, some_value);
	strncpy(&LCD->buffer_lines[1][0], "01234567890123456789", 20);
	strncpy(&LCD->buffer_lines[2][0], "Some text displayed.", 20);
	strncpy(&LCD->buffer_lines[3][0], "That's Text from ram", 20);
	// template for measuring          01234567890123456789

	// bring the buffer to the device
	// every cycle another line is updated
	for (i=0; i<4; i++)
	  LCD->display();
}





