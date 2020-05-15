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

		// allow to release the locking
		if(_volatileData.isKeysLocked()) {
			_volatileData.update(actTuple, _screenStates.getActSreen());
			continue;
		}

		if(actTuple.key == keyBtnSetup) {
			_screenStates.update(actTuple.event);
			continue;
		}

		if ( _screenStates.isActScreenSetup() ) {
			_nonVolatileData.update(actTuple, _screenStates.getActSreen(), _volatileData);
		}
		else {
			_volatileData.update(actTuple, _screenStates.getActSreen());
		}
	}
}


} /* namespace encodeNButtons */
