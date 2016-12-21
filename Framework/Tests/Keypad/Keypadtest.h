/*
 * keypadtest.h
 *
 *  Created on: 28.10.2015
 *      Author: harald
 */

#ifndef KEYPADTEST_H_
#define KEYPADTEST_H_

#include "Devices/keypad/Keypad.h"
#include <string.h>
#include "Devices/PCD8544_LCD/PCD8544_graphics.h"
#include "System/SoftwareTimer.h"
#include "libraries/HelpersLib.h"
#include "Instances/Common.h"


class Keypadtest
{
public:
  Keypadtest();
  void init_keypad(void);
  void Do_keypadtest (void);
  void loop (void);

  void clearTextbuffer(uint8_t len);


private:
  uint32_t old_cycle, act_cycle;

  Keypad *keypad;
  Keypad::rawKey_type *lastKey;

  char *textbuffer;
  int8_t textbuffer_len;
  PCD8544_graphics*	LCD;
};

#endif /* MAINCLASS_H_ */
