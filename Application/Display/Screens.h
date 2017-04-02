/*
 * Screens.h
 *
 *  Created on: 12.03.2017
 *      Author: harald
 */

#ifndef DISPLAY_SCREENS_H_
#define DISPLAY_SCREENS_H_

#include <stdint.h>


#define UI_VALUES_SCR	0
#define TEMPERATUR_SCR 	1
#define WATTS_SCR		2

class Screens
{
public:

  Screens ();
  virtual ~Screens ();

  void increment(void);
  void hook_in(void);
  void hook_off(void);
  void loop(void);


private:
  uint8_t 	actv_screen;



};

#endif /* DISPLAY_SCREENS_H_ */
