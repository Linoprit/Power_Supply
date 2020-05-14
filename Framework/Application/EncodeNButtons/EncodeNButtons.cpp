/*
 * EncodeNButtons.cpp
 *
 *  Created on: 26.04.2020
 *      Author: harald
 */

#include <Application/EncodeNButtons/EncodeNButtons.h>
#include <new>
#include <main.h>
#include <Instances/Common.h>


namespace encodeNButtons {

void EncodeNButtons::init(void) {
	new (&instance()) EncodeNButtons();
}

EncodeNButtons& EncodeNButtons::instance(void) {
	static EncodeNButtons encodeNButtons;
	return encodeNButtons;
}

EncodeNButtons::EncodeNButtons():
		_socket {get_hi2c1()},
		_rotEnc {&_socket}
{

}

void EncodeNButtons::cycle(
		EventQueue_type& eventQueue, AdditionalButtons  additionalButtons) {

	_rotEnc.cycle(eventQueue);
	_memoryButtons.cycle(eventQueue, additionalButtons);

	while(!eventQueue.isEmpty()) {
		KeyEventTuple actTuple = eventQueue.dequeue();

		if(actTuple.key == keyBtnSetup) {
			_screenStates.update(actTuple.event);
			continue;
		}

		if ( _screenStates.isActScreenSetup() ) {
			// update NonVolatileData

		}
		else {
			// update VolatileData

		}


	}


}


} /* namespace encodeNButtons */
