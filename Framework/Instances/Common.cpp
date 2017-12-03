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
#include "System/Error_messaging.h"


SoftwareEvents*			Common::sw_events 		= new SoftwareEvents();
Comm_Layer*				Common::comm_layer		= NULL;
Char_LCD* 				Common::char_lcd 		= NULL;
Rotary_Encoder* 		Common::rotary_encoder 	= NULL;
OMI_coordinator*		Common::omi_coord		= NULL;
IU_Value* 				Common::u_soll			= NULL;
IU_Value* 				Common::i_soll			= NULL;
IU_Value* 				Common::u_start			= NULL;
IU_Value* 				Common::i_start			= NULL;
HI_LO_Value* 			Common::hi_lo			= NULL;




// Workaround undefined reference error
//const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
//const uint8_t APBPrescTable[8]  = {0, 0, 0, 0, 1, 2, 3, 4};


void Common::initialize_devices()
{
#ifdef TRACE
  Error_messaging::init_debug_comm();
#endif /* TRACE */

  init_comm_layer();
  init_char_LCD();
  init_rotary_encoder();

  init_values();
  init_omi_coord();


}

void Common::init_values(void)
{
  const IU_Value::ValueConfig i_config =
	  {
		  1,
		  Rotary_Encoder::last_key_enum::rotenc_right,
		  Rotary_Encoder::btn_right,
		  0,
		  10,
	  };
  i_soll  = new IU_Value(i_config);
  i_start = new IU_Value(i_config);

  const IU_Value::ValueConfig u_config =
	  {
		  1,
		  Rotary_Encoder::last_key_enum::rotenc_left,
		  Rotary_Encoder::btn_left,
		  0,
		  24,
	  };
  u_soll  = new IU_Value(u_config);
  u_start = new IU_Value(u_config);

  hi_lo = new HI_LO_Value();
}

IU_Value* 		Common::get_u_soll(void) 	{ return u_soll;  }
IU_Value* 		Common::get_i_soll(void) 	{ return i_soll;  }
IU_Value* 		Common::get_u_start(void) 	{ return u_start; }
IU_Value* 		Common::get_i_start(void) 	{ return i_start; }
HI_LO_Value* 	Common::get_hi_lo(void)		{ return hi_lo;	  }


void Common::init_comm_layer(void)
{
  Comm_Layer_socket* socket = new Comm_Layer_socket( get_huart1() );

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
  SPI_HandleTypeDef* spi = get_hspi3();

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
  Rotary_Encoder_socket* socket  = new Rotary_Encoder_socket(get_hi2c1());
  rotary_encoder = new Rotary_Encoder(socket);
}

Rotary_Encoder* Common::get_rotary_encoder(void)
{
  return rotary_encoder;
}

void Common::init_omi_coord(void)
{
  omi_coord = new OMI_coordinator();
}

OMI_coordinator* Common::get_omi_coord(void)
{
  return omi_coord;
}





uint32_t Common::get_tick(void)
{
  return HAL_GetTick();
}



