/*
 * Probiersmal.h
 *
 *  Created on: 29.04.2020
 *      Author: harald
 */

#ifndef DEVICES_ROTARY_ENCODER_MEMORYBUTTONS_H_
#define DEVICES_ROTARY_ENCODER_MEMORYBUTTONS_H_

#include <stdint.h>
#include <libraries/SimpleQueue.h>
#include "Button_Machine.h"
#include "Rotary_Encoder.h"

namespace rotaryEncoder {

class AdditionalButtons {
public:
	bool memory1;
	bool memory2;
	bool user;
};

class MemoryButtons {
public:
	MemoryButtons();
	virtual ~MemoryButtons() {};

	void cycle(EventQueue_type& eventQueue, AdditionalButtons additionalButtons);


private:
  Button_Machine			button_M1;
  Button_Machine			button_M2;
  Button_Machine			button_User;

  void check_cycle(
  		uint8_t 					buttonValue,
  		Key_enum	 				key,
  		EventQueue_type& 	eventQueue);

};

}

#endif /* DEVICES_ROTARY_ENCODER_MEMORYBUTTONS_H_ */
