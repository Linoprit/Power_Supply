/*
 * Probiersmal.cpp
 *
 *  Created on: 29.04.2020
 *      Author: harald
 */

#include <Devices/Rotary_Encoder/MemoryButtons.h>

namespace rotaryEncoder {

MemoryButtons::MemoryButtons()
{

}

void MemoryButtons::cycle(
		EventQueue_type& eventQueue, AdditionalButtons additionalButtons) {

	check_cycle(static_cast<uint8_t>(additionalButtons.memory1), btn_M1, eventQueue);
	check_cycle(static_cast<uint8_t>(additionalButtons.memory2), btn_M2, eventQueue);
	check_cycle(static_cast<uint8_t>(additionalButtons.user), btn_User, eventQueue);
}

void MemoryButtons::check_cycle(
		uint8_t 					buttonValue,
		Key_enum	 				key,
		EventQueue_type& 	eventQueue)
{
	KeyEvent_enum event = evnt_none;

	if (key == btn_M1)
		event =	button_M1.cycle(buttonValue);

	if (key == btn_M2)
		event =	button_M2.cycle(buttonValue);

	if (key == btn_User)
		event =	button_User.cycle(buttonValue);

	if(event > evnt_none) {
		eventQueue.enqueue(KeyEventTuple(key, event));
	}

}


} // namespace
