/*
 * Initclasses.h
 *
 *  Created on: 06.05.2016
 *      Author: harald
 */

#ifndef COMMON_H_
#define COMMON_H_


#include "System/SoftwareEvents.h"
#include "Devices/Comm_Layer/Comm_Layer_socket.h"
#include "Devices/Comm_Layer/Comm_Layer.h"
#include "Devices/Char_LCD/Char_LCD.h"
#include "Devices/Rotary_Encoder/Rotary_Encoder_socket.h"
#include "Devices/Rotary_Encoder/Rotary_Encoder.h"
#include "Controller/ADC_socket.h"

#include "Options/IU_Value.h"
#include "Options/HI_LO_Value.h"

#include "../Application/Display/OMI_coordinator.h"



extern "C" UART_HandleTypeDef* get_huart1(void);
extern "C" UART_HandleTypeDef* get_huart2(void);
extern "C" SPI_HandleTypeDef*  get_hspi3 (void);
extern "C" I2C_HandleTypeDef*  get_hi2c1 (void);

extern "C" ADC_HandleTypeDef* get_hadc1(void);
extern "C" ADC_HandleTypeDef* get_hadc2(void);
extern "C" ADC_HandleTypeDef* get_hadc3(void);
extern "C" ADC_HandleTypeDef* get_hadc4(void);

extern "C" DAC_HandleTypeDef* get_hdac1(void);

extern "C" OPAMP_HandleTypeDef* get_hopamp2(void);
extern "C" OPAMP_HandleTypeDef* get_hopamp3(void);
extern "C" OPAMP_HandleTypeDef* get_hopamp4(void);




class Common
{
public:

  Common() {};
  virtual ~Common() {};

  static void initialize_devices(void);
  static SoftwareEvents*    get_sw_events(void);

  static uint32_t get_tick(void);

  static Comm_Layer*		get_comm_layer(void);
  static Rotary_Encoder* 	get_rotary_encoder(void);
  static Char_LCD* 			get_char_lcd(void);
  static OMI_coordinator* 	get_omi_coord(void);

  static IU_Value*			get_u_soll(void);
  static IU_Value* 			get_i_soll(void);
  static IU_Value*			get_u_start(void);
  static IU_Value* 			get_i_start(void);
  static HI_LO_Value* 		get_hi_lo(void);

  // TODO use measurement class
  static ADC_socket*		get_adc_socket_Uall(void);



  static inline void delay(uint32_t delay)
  { HAL_Delay(delay); }


private:
  static void init_comm_layer(void);
  static Comm_Layer *comm_layer;

  static void init_rotary_encoder(void);
  static Rotary_Encoder* rotary_encoder;

  static void init_char_LCD(void);
  static Char_LCD* char_lcd;

  static void init_omi_coord(void);
  static OMI_coordinator* omi_coord;




  static void init_values(void);
  static IU_Value* u_soll;
  static IU_Value* i_soll;
  static IU_Value* u_start;
  static IU_Value* i_start;
  static HI_LO_Value* hi_lo;

  static void init_adcs(void);
  static ADC_socket* 	adc_socket_Iamp;
  static ADC_socket* 	adc_socket_Iraw;
  static ADC_socket* 	adc_socket_Uall;
  static ADC_socket* 	adc_socket_Temp;


  static SoftwareEvents    *sw_events;
};

#endif /* COMMON_H_ */
