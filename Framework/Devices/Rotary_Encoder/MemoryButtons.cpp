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

	check_cycle(static_cast<uint8_t>(additionalButtons.memory1), keyBtnM1, eventQueue);
	check_cycle(static_cast<uint8_t>(additionalButtons.memory2), keyBtnM2, eventQueue);
	check_cycle(static_cast<uint8_t>(additionalButtons.user), keyBtnUser, eventQueue);
}

void MemoryButtons::check_cycle(
		uint8_t 					buttonValue,
		Key_enum	 				key,
		EventQueue_type& 	eventQueue)
{
	KeyEvent_enum event = evntNone;

	if (key == keyBtnM1)
		event =	button_M1.cycle(buttonValue);

	if (key == keyBtnM2)
		event =	button_M2.cycle(buttonValue);

	if (key == keyBtnUser)
		event =	button_User.cycle(buttonValue);

	if(event > evntNone) {
		eventQueue.enqueue(KeyEventTuple(key, event));
	}

}


} // namespace
