/*
 * Initclasses.h
 *
 *  Created on: 06.05.2016
 *      Author: harald
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "System/SoftwareEvents.h"
#include "Devices/PCD8544_LCD/PCD8544_socket.h"
#include "Devices/PCD8544_LCD/PCD8544_basis.h"
#include "Devices/PCD8544_LCD/PCD8544_graphics.h"
#include "Devices/keypad/Keypad_socket.h"
#include "Devices/keypad/Keypad.h"
#include "Devices/Comm_Layer/Comm_Layer_socket.h"
#include "Devices/Comm_Layer/Comm_Layer.h"
#include "sd_spi_stm32.h"
#include "ff_gen_drv.h"


class Common
{
public:

  Common() {};
  virtual ~Common() {};

  static void initialize_devices(void);
  static SoftwareEvents*    get_sw_events(void);

  static uint32_t get_tick(void);

  //static PCD8544_basis* 	get_LCD_basis(void);
  static PCD8544_graphics*  get_LCD_grfx(void);
  static Keypad*			get_keypad(void);
  static Comm_Layer*		get_comm_layer(void);

  static inline void delay(uint32_t delay)
  { HAL_Delay(delay); }


private:
  static void init_PCD8574(void);
  //static PCD8544_basis		*LCD_dev;
  static PCD8544_graphics 	*LCD_grfx;

  static void init_keypad(void);
  static Keypad	*keypad;

  static void init_comm_layer(void);
  static Comm_Layer *comm_layer;

  static void init_SD_Card(void);
  static Diskio_drvTypeDef* sd_card_drv;
  // TODO get_sd_card handler...

  static SoftwareEvents    *sw_events;
};

#endif /* COMMON_H_ */
