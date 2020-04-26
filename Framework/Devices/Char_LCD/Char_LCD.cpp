/*
 * Char_LCD.cpp
 *
 *  Created on: 08.01.2017
 *      Author: harald
 */

#include "Char_LCD.h"
#include <string.h>


Char_LCD::Char_LCD (Char_LCD_socket* lcd_socket_in)
{
  lcd_socket = lcd_socket_in;
  init();
}

Char_LCD::~Char_LCD ()
{ }

void Char_LCD::init()
{
  uint8_t i;

  // LCD init sequence
#define INIT_LENGTH 5
  const uint8_t lcd_init_sequence[] =
	  {
		  LCD_DATALENGTH,
		  LCD_CURSOROFF,
		  LCD_CLR,
		  LCD_MVCURSOR,
		  LCD_2LINES
	  };

  // send data to initialize the lcd
  lcd_socket->select_instruction_register();
  lcd_socket->reset_lcd_en_line();
  Common::delay(LCD_WAIT_DELAY);

  for (i=0; i < INIT_LENGTH; i++)
	lcd_socket->put_byte_2_lcd_initonly(
		(uint8_t) lcd_init_sequence[i]);
}


void Char_LCD::display_step(void)
{
  static uint8_t act_line = 0; // holds which line to be refreshed
  static uint8_t act_char = 0; // this is the char, sent to the display
  static char*   act_buffer;   // points to act char in buffer_lines
  enum send_state_enum { send_address, send_char};
  static send_state_enum send_state = send_address;

  if (send_state == send_address)
	{
	  act_buffer = select_line(act_line);

	  act_line++;
	  if (act_line >= LCD_LINES)
		act_line = 0;

	  send_state = send_char;
	  lcd_socket->select_data_register();
	}

  if (send_state == send_char)
	{
	  lcd_socket->pulse_byte_2_lcd_nblk( (uint8_t) *act_buffer);

	  act_buffer++;
	  act_char++;
	  if (act_char >= LCD_BUFFER_LEN)
		{
		  act_char = 0;
		  send_state = send_address;
		}
	}
}

char* Char_LCD::select_line(uint8_t line_nr) // nonblocking
{
  // set address of corresponding LCD-line
  lcd_socket->select_instruction_register();

  switch (line_nr)
  {
	case 0:
	  lcd_socket->pulse_byte_2_lcd_nblk(LINE_1);
	  break;

	case 1:
	  lcd_socket->pulse_byte_2_lcd_nblk(LINE_2);
	  break;

#ifdef FOUR_LINES
	case 2:
	  lcd_socket->pulse_byte_2_lcd_nblk(LINE_3);
	  break;

	case 3:
	  lcd_socket->pulse_byte_2_lcd_nblk(LINE_4);
	  break;
#endif

	default:
	  break;
  }

  return &buffer_lines[line_nr][0];
}

void Char_LCD::display_line(uint8_t line_nr) // first line is 0
{
  static uint8_t i=line_nr; 	// holds which line to be refreshed
  uint8_t j;          		// loop-counter

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

void Char_LCD::display(void)
{
  uint8_t i;

  // bring the buffer to the device
  // every cycle another line is updated
  for (i=0; i < LCD_LINES; i++)
	display_line(i);
}

void Char_LCD::clear(void)
{
  uint8_t i;

  for (i=0; i < LCD_LINES; i++)
	memset(&buffer_lines[i][0], ' ', LCD_BUFFER_LEN);
}

buffer_lines_type * Char_LCD::get_buffer_lines_ptr(void)
{
  return &buffer_lines;
}

