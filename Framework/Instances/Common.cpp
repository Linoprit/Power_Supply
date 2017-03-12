/*
 * Initclasses.cpp
 *
 *  Created on: 06.05.2016
 *      Author: harald
 */

#include "Common.h"
#include "stm32f3xx_hal.h"
#include "main.h"
#include "Instances/callbacks.h"



SoftwareEvents*		Common::sw_events 		= new SoftwareEvents();
Comm_Layer*			Common::comm_layer		= NULL;
Char_LCD* 			Common::char_lcd 		= NULL;
Rotary_Encoder* 	Common::rotary_encoder 	= NULL;
Comm_Layer_socket*	Common::debug_comm		= NULL;


// Workaround undefined reference error
//const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
const uint8_t APBPrescTable[8]  = {0, 0, 0, 0, 1, 2, 3, 4};


void Common::initialize_devices()
{
  init_comm_layer();
  init_char_LCD();
  init_rotary_encoder();
  init_debug_comm();



}

void Common::init_debug_comm(void)
{
  debug_comm = new Comm_Layer_socket( get_UART_2() );
}

Comm_Layer_socket* Common::get_debug_comm(void)
{
  return debug_comm;
}

void Common::init_comm_layer(void)
{
  Comm_Layer_socket* socket = new Comm_Layer_socket( get_UART_1() );

  comm_layer = new Comm_Layer( (Rx_Tx_interface*) socket );
  Messages_Base::init();
}


Comm_Layer*	Common::get_comm_layer(void)
{
  return comm_layer;
}


SoftwareEvents* Common::get_sw_events(void)
{
  return sw_events;
}

void Common::init_char_LCD(void)
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

  char_lcd = new Char_LCD(socket);
}

Char_LCD* Common::get_char_lcd(void)
{
  return char_lcd;
}

void Common::init_rotary_encoder()
{
  Rotary_Encoder_socket* socket  = new Rotary_Encoder_socket(get_I2C_1());
  rotary_encoder = new Rotary_Encoder(socket);
}

Rotary_Encoder* Common::get_rotary_encoder(void)
{
  return rotary_encoder;
}

uint32_t Common::get_tick(void)
{
  return HAL_GetTick();
}



