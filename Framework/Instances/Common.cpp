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



SoftwareEvents*		Common::sw_events 	= new SoftwareEvents();
//PCD8544_basis* 		Common::LCD_dev  = NULL;
PCD8544_graphics*	Common::LCD_grfx 	= NULL;
Keypad*				Common::keypad		= NULL;
Comm_Layer*			Common::comm_layer	= NULL;
Diskio_drvTypeDef*  Common::sd_card_drv = NULL;



void Common::initialize_devices()
{
  init_PCD8574();
  init_keypad();
  init_comm_layer();
//  init_SD_Card();

}

void Common::init_comm_layer(void)
{
  Comm_Layer_socket* socket = new Comm_Layer_socket( get_UART_1() );

  comm_layer = new Comm_Layer( (Rx_Tx_interface*) socket );
  Messages_Base::init();
}

void Common::init_keypad(void)
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

void Common::init_PCD8574(void)
{
  SPI_HandleTypeDef *spi 		= get_LCD_SPI();

  PCD8544_socket::spi_pinspack_type*
  lcd_pinspack = new PCD8544_socket::spi_pinspack_type
  {
	LCD_CS_GPIO_Port,
	LCD_CS_Pin,
	LCD_Reset_GPIO_Port,
	LCD_Reset_Pin,
	LCD_Data_Command_GPIO_Port,
	LCD_Data_Command_Pin,
	LCD_Background_LED_GPIO_Port,
	LCD_Background_LED_Pin
  };

  PCD8544_socket	*LCD_socket =
	  new PCD8544_socket(spi, lcd_pinspack);

  //LCD_dev 	=
	  //	  new PCD8544_basis(LCD_socket);
  LCD_grfx  =
	  new PCD8544_graphics(LCD_socket);
}

Comm_Layer*	Common::get_comm_layer(void)
{
  return comm_layer;
}

Keypad* Common::get_keypad(void)
{
  return keypad;
}

//PCD8544_basis* Common::get_LCD_basis(void)
//{
//  return LCD_dev;
//}

PCD8544_graphics* Common::get_LCD_grfx(void)
{
  return LCD_grfx;
}

SoftwareEvents* Common::get_sw_events(void)
{
  return sw_events;
}

void Common::init_SD_Card(void)
{
  sd_card_drv = new Diskio_drvTypeDef();
  sd_card_drv->disk_initialize 	= &drv_disk_initialize;
  sd_card_drv->disk_ioctl		= &drv_disk_ioctl;
  sd_card_drv->disk_read		= &drv_disk_read;
  sd_card_drv->disk_status		= &drv_disk_status;
  sd_card_drv->disk_write		= &drv_disk_write;


  // TODO hook in disk_timerproc


  // path = "a"
  FATFS_LinkDriver(sd_card_drv, (char *) "a");

  // usage: http://elm-chan.org/fsw/ff/res/app1.c

}


void Common::init_rotary_encoder()
{
  // TODO
}

Rotary_Encoder* Common::get_rotary_encoder(void)
{
  return rotary_encoder;
}



uint32_t Common::get_tick(void)
{
  return HAL_GetTick();
}



