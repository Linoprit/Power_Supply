/*
 * Char_LCD_socket.cpp
 *
 *  Created on: 08.01.2017
 *      Author: harald
 */

#include "Char_LCD_socket.h"


Char_LCD_socket::Char_LCD_socket (
		SPI_HandleTypeDef				*lcd_spi,
		GPIO_TypeDef						*RS_port,
		GPIO_TypeDef						*EN_port,
		uint16_t								RS_pin,
		uint16_t								EN_pin)
{
  _spi				= lcd_spi;
	_RS_port 		= RS_port;
	_EN_port		= EN_port;
	_RS_pin			= RS_pin;
	_EN_pin			= EN_pin;

  set_lcd_en_line();
  select_data_register();
}

// this function is blocking!! Just used for init, with longer delaytimes.
void Char_LCD_socket::put_byte_2_lcd_initonly (uint8_t data)
{
	send_byte(data);

	set_lcd_en_line();
	Common::delay(LCD_WAIT_DELAY);

	reset_lcd_en_line();
	Common::delay(LCD_WAIT_DELAY);
}

