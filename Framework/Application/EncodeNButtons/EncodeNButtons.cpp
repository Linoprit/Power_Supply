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
		_rotEnc {&_socket},
		_isFirstCycle { true }
{
}

void EncodeNButtons::cycle(
		EventQueue_type& eventQueue, AdditionalButtons  additionalButtons) {

	_memoryButtons.cycle(eventQueue, additionalButtons);
	_rotEnc.cycle(eventQueue);


	if(_isFirstCycle == true) {
		_isFirstCycle = false;
		eventQueue.reset(); // encoders could cause unintended increment at startup
		doFirstCycle();
	}

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
			bool result = _screenState.update(actTuple.event);
			if (result == true) {
				_nonVolatileData.storeStartVals();
				_nonVolatileData.storeCalibVals();
			}
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

void EncodeNButtons::doFirstCycle(void) {
	StrtMemoryEnum strtMemory = _nonVolatileData.getStrtMemory();
	bool isPowActiveStart = _nonVolatileData.isPowActiveStart();

	uint32_t Usoll = 0;
	uint32_t Isoll = 0;
	InSourceEnum inSource = InSourceEnum::inAuto;

	if (strtMemory ==  strtMem1) {
		Usoll = _nonVolatileData.getUsollMem1().get();
		Isoll = _nonVolatileData.getIsollMem1().get();
		inSource = _nonVolatileData.getInSourceMem1();
	}
	else if (strtMemory ==  strtMem2) {
		Usoll = _nonVolatileData.getUsollMem2().get();
		Isoll = _nonVolatileData.getIsollMem2().get();
		inSource = _nonVolatileData.getInSourceMem2();
	}

	_volatileData.getUsoll().set(static_cast<int32_t>(Usoll));
	_volatileData.getIsoll().set(static_cast<int32_t>(Isoll));
	_volatileData.setInSource(inSource);

	_volatileData.setPowActive(isPowActiveStart);
}


} /* namespace encodeNButtons */
