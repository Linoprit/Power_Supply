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

Measurement*			Common::meas_U_sense		= NULL;
Measurement*			Common::meas_U_sense_auto   = NULL;
Measurement*			Common::meas_U_input        = NULL;
Measurement*			Common::meas_I_raw          = NULL;
Measurement*			Common::meas_I_auto         = NULL;
Measurement*			Common::meas_Temperature    = NULL;

// TODO remove from here and put them into init
ADC_socket* Common::adc_socket_Iamp = NULL;
ADC_socket* Common::adc_socket_Iraw = NULL;

// U_sense, U_raw, Opamp3 = U_sense * PGA
ADC_socket* Common::adc_socket_Uall = NULL;
ADC_socket* Common::adc_socket_Temp = NULL;



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
  init_measurement();

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

void Common::init_measurement()
{
  /*ADC_socket* adc_socket_Iamp = new ADC_socket(get_hadc2(), 1);
  ADC_socket* adc_socket_Iraw = new ADC_socket(get_hadc1(), 1);

  // U_sense, U_raw, Opamp3 = U_sense * PGA
  ADC_socket* adc_socket_Uall = new ADC_socket(get_hadc3(), 3);
  ADC_socket* adc_socket_Temp = new ADC_socket(get_hadc4(), 1);*/


  adc_socket_Iamp = new ADC_socket(get_hadc2(), 1);
  adc_socket_Iraw = new ADC_socket(get_hadc1(), 1);
  adc_socket_Uall = new ADC_socket(get_hadc3(), 3);
  adc_socket_Temp = new ADC_socket(get_hadc4(), 1);


  meas_U_sense		= new Measurement(adc_socket_Uall, 1);
  meas_U_input		= new Measurement(adc_socket_Uall, 2);
  meas_U_sense_auto = new Measurement(
	  adc_socket_Uall, 3, new Opamp_socket(get_hopamp3()));

  meas_I_raw 		= new Measurement(adc_socket_Iraw, 1);
  meas_I_auto		= new Measurement(
	  adc_socket_Iamp, 1, new Opamp_socket(get_hopamp2()));
  meas_Temperature	= new Measurement(
	  adc_socket_Temp, 1, new Opamp_socket(get_hopamp4()));

  meas_U_sense->set_calibration(10u, 3055u, 0.897f, 30.48f);
  meas_U_input->set_calibration(12u, 3069u, 0.836f, 30.48f);
  meas_U_sense_auto->set_calibration(30u, 3840u, 0.56f, 19.18f, 2);

  meas_I_raw->set_calibration(12u, 3069u, 0.836f, 30.48f);
  meas_I_auto->set_calibration(30u, 3840u, 0.56f, 19.18f, 2);



  // TODO calibration aus EEPROM lesen und in Measurements schreiben;



}
Measurement*	Common::get_U_sense(void)
{
  return meas_U_sense;
}

Measurement*	Common::get_U_sense_auto(void)
{
  return meas_U_sense_auto;
}

Measurement*	Common::get_U_input(void)
{
  return meas_U_input;
}

Measurement*	Common::get_I_raw(void)
{
  return meas_I_raw;
}

Measurement*	Common::get_I_auto(void)
{
  return meas_I_auto;
}

Measurement*	Common::get_Temperature(void)
{
  return meas_Temperature;
}



/*ADC_socket* Common::get_adc_socket_Uall(void) // TODO delete
{
  return adc_socket_Uall;
}*/







uint32_t Common::get_tick(void)
{
  return HAL_GetTick();
}



