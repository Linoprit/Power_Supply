/*
 * Rotary_Encoder_Types.h
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
	evntNone,
	evntReleased, evntPressed, evntHeld,
	evntIncrement, evntDecrement
};

enum Key_enum {
	keyNone,
	keyRotLeft, keyRotRight,
	keyBtnLeft, keyBtnRight, keyBtnSetup, keyBtnOnOff,
	// additional buttons
	keyBtnM1, keyBtnM2, keyBtnUser
};

class KeyEventTuple
{
public:
	KeyEventTuple(void) {
		event = evntNone;
		key   = keyNone;
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
