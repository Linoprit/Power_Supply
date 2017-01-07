/*
 * Keypadbitbanging.h
 *
 *  Created on: 25.10.2015
 *      Author: harald
 */

#ifndef DEVICES_KEYPAD_KEYPAD_H_
#define DEVICES_KEYPAD_KEYPAD_H_

#include "Keypad_socket.h"
#include "System/SoftwareEvents.h"
#include "System/SoftwareTimer.h"
#include "Instances/callbacks.h"
#include "Default_Keymap.h"


class Keypad:
	ISR_callback,
	SoftwareTimer_base
{
public:
	  struct rawKey_type{
		uint8_t col;
		uint8_t row;
	  };

	  enum button_state_enum {
		bttn_released, bttn_pressed, bttn_held};


	  Keypad (Keypad_socket *socket);

	  button_state_enum getActualKeyState(void);
	  rawKey_type*       getLastRawKey(void);

	  char 	getLastChar(void);
	  char 	convertRaw2Command(rawKey_type* raw_key);
	  char 	getLastKeyCommand(void);
	  void 	bindCharMap(uint8_t *map,
						rawKey_type nrOfCols_n_Rows);
	  char 	convertRaw2Char(rawKey_type* raw_key);
	  void 	bindCommandMap(uint8_t *commandmap,
						   rawKey_type nrOfCols_n_Rows);


	  // actually private, but called by ISR handler, or timer callback
	  void ISR_callback_fcn (void);
	  void timer_hit_callback(void);


private:
	  // we use Timer event Tic_10ms!!
	  const uint8_t  TimerDuration             = 1;   // = 10ms
	  const uint8_t  keyOpenCounter_max        = 2;   // = 20ms
	  const uint16_t keyPressedLoopCounter_max = 100; // = 1000ms

	  Keypad_socket *socket;

	  Keypad::rawKey_type lastRawKey;
	  uint8_t  keyOpenCounter;
	  uint16_t keyPressedLoopCounter;
	  uint8_t *keymap_ptr, *commandmap_ptr;
	  uint8_t keymap_max_rows, keymap_max_cols;
	  uint8_t commandmap_max_rows, commandmap_max_cols;
	  button_state_enum button_state;

	  SoftwareTimer *timer;

};

#endif /* DEVICES_KEYPAD_KEYPAD_H_ */
