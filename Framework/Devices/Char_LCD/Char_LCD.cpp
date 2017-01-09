/*
 * Char_LCD.cpp
 *
 *  Created on: 08.01.2017
 *      Author: harald
 */

#include "Char_LCD.h"



Char_LCD::Char_LCD (Char_LCD_socket* lcd_socket_in)
{
  lcd_socket = lcd_socket_in;
}

Char_LCD::~Char_LCD ()
{ }

void Char_LCD::init()
{
  uint8_t i, j;

  // LCD init sequence
  #define INIT_LENGTH 5
  const uint8_t lcd_init_sequence[] =
  	{
  		LCD_DATALENGTH,
  		LCD_2LINES,
  		LCD_CURSOROFF,
  		LCD_CLR,
  		LCD_MVCURSOR
  	};

  // send data to initialize the lcd
  lcd_socket->select_instruction_register();
  lcd_socket->reset_lcd_en_line();
  lcd_socket->delay_ms(LCD_WAIT_DELAY);

  for (i=0; i < INIT_LENGTH; i++)
	lcd_socket->put_byte_2_lcd_initonly(
		(uint8_t) lcd_init_sequence[i]);

  // clear display
  for (i=0; i < LCD_LINES; i++)
	for (j=0; j < LCD_BUFFER_LEN; j++)
	  buffer_lines[i][j] = ' ';
}


void Char_LCD::display(void)
{
  static uint8_t i=0; // holds which line to be refreshed
  uint8_t j;          // loop-counter

  {
	//char buffer[] = "12345678901234567890"; // comment in for testing
	//char * buffer_ptr = &buffer[0];         // comment in for testing
	char * buffer_ptr = &buffer_lines[i][0];  // comment out if testing

	// set address of corresponding line in LCD
	lcd_socket->select_instruction_register();
	switch (i)
	{
	  case 0:
		lcd_socket->pulse_byte_2_lcd(LINE_1);
		break;

	  case 1:
		lcd_socket->pulse_byte_2_lcd(LINE_2);
		break;

#ifdef FOUR_LINES
	  case 2:
		lcd_socket->pulse_byte_2_lcd(LINE_3);
		break;

	  case 3:
		lcd_socket->pulse_byte_2_lcd(LINE_4);
		break;
#endif

	  default:
		break;
	}

	// increment and loop line-counter
	i++;
	if (i > LCD_LINES-1)
	  i=0;

	// push buffer-content to LCD
	lcd_socket->select_data_register();
	for (j=0; j<LCD_BUFFER_LEN; j++)
	  {
		lcd_socket->pulse_byte_2_lcd (*buffer_ptr);
		buffer_ptr ++;
	  }
  }
}

buffer_lines_type * Char_LCD::get_buffer_lines_ptr(void)
{
  return &buffer_lines;
}

