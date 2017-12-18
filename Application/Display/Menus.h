/*
 * Menus.h
 *
 *  Created on: 12.03.2017
 *      Author: harald
 */

#ifndef DISPLAY_MENUS_H_
#define DISPLAY_MENUS_H_

#include <stdint.h>

#define HI_LO_MENU 		0
#define START_VALS_MENU 1
#define SWEEP_MENU		2
#define CHARGE_MENU		3



class Menus
{
public:

  Menus ();
  virtual ~Menus ();

  void increment(void);
  void hook_in(void);
  void hook_off(void);
  void loop_100ms(void);

private:
  uint8_t actv_screen;



};

#endif /* DISPLAY_MENUS_H_ */
