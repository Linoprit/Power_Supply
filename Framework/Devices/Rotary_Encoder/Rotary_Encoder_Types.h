/*
 * Rotary_Encoder_Interface.h
 *
 *  Created on: 02.05.2020
 *      Author: harald
 */

#ifndef DEVICES_ROTARY_ENCODER_ROTARY_ENCODER_TYPES_H_
#define DEVICES_ROTARY_ENCODER_ROTARY_ENCODER_TYPES_H_

#include <libraries/SimpleQueue.h>


namespace rotaryEncoder {

constexpr uint8_t eventQueueLen = 8;

enum KeyEvent_enum {
	evnt_none,
	btn_released, btn_pressed, btn_held,
	rotenc_increment, rotenc_decrement
};

enum Key_enum {
	btn_none,
	rotenc_left, rotenc_right,
	btn_left, btn_right, btn_setup, btn_onoff,
	// additional buttons
	btn_M1, btn_M2, btn_User
};

class KeyEventTuple
{
public:
	KeyEventTuple(void) {
		event = evnt_none;
		key   = btn_none;
	}
	KeyEventTuple(Key_enum __key, KeyEvent_enum __event) {
		event = __event;
		key   = __key;
	};

	KeyEvent_enum 	event;
	Key_enum 				key;
};

typedef SimpleQueue<KeyEventTuple, eventQueueLen> EventQueue_type;

}


#endif /* DEVICES_ROTARY_ENCODER_ROTARY_ENCODER_TYPES_H_ */
