/*
 * Char_LCD_socket.cpp
 *
 *  Created on: 08.01.2017
 *      Author: harald
 */

#include "Char_LCD_socket.h"


Char_LCD_socket::Char_LCD_socket (SPI_HandleTypeDef* 		lcd_spi,
								  char_LCD_pinspack_type* 	lcd_pinspack)
{
  pinspack 	= lcd_pinspack;
  spi		= lcd_spi;

  set_lcd_en_line();
  select_data_register();
}

Char_LCD_socket::~Char_LCD_socket ()
{}

// this function is blocking!! Just used for init, with longer delaytimes.
void Char_LCD_socket::put_byte_2_lcd_initonly (uint8_t data)
{
	send_byte(data);

	set_lcd_en_line();
	HAL_Delay(LCD_WAIT_DELAY);

	reset_lcd_en_line();
	HAL_Delay(LCD_WAIT_DELAY);
}

