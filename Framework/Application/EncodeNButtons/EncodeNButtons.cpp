/*
 * EncodeNButtons.cpp
 *
 *  Created on: 26.04.2020
 *      Author: harald
 */

#include <Application/EncodeNButtons/EncodeNButtons.h>
#include <Instances/Common.h>
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

	osStatus_t status = osSemaphoreAcquire(EncdTskDataSemHandle, 20);
	if (status != osOK)
		return;

	_volatileData.updateMemEvent();

	while(!eventQueue.isEmpty()) {
		KeyEventTuple actTuple = eventQueue.dequeue();

		// allow to release the locking
		if(_volatileData.isKeysLocked()) {
			_volatileData.update(actTuple, _screenState.getActSreen(), _nonVolatileData);
			continue;
		}

		if(actTuple.key == keyBtnSetup) {
			_screenState.update(actTuple.event);
			continue;
		}

		if ( _screenState.isActScreenSetup() ) {
			_nonVolatileData.update(actTuple, _screenState.getActSreen(), _volatileData);
		}
		else {
			_volatileData.update(actTuple, _screenState.getActSreen(), _nonVolatileData);
		}
	}

	osSemaphoreRelease(EncdTskDataSemHandle);


}


} /* namespace encodeNButtons */
