/*
 * NonVolatileData.cpp
 *
 *  Created on: 03.05.2020
 *      Author: harald
 */

#include <Application/EncodeNButtons/NonVolatileData.h>


namespace encodeNButtons {

NonVolatileData::NonVolatileData(void):
_strtMemory 	{	strtNone },
_Rshunt 		{ RSHUNT_ADJ_SETUP },
_TtrafoMax 		{ TEMP_ADJ_SETUP },
_TendstufeMax   { TEMP_ADJ_SETUP },
_UsollMem1      { USET_FIX_SETUP },
_IsollMem1      { ISET_FIX_SETUP },
_InSourceMem1   { inAuto },
_UsollMem2 		{ USET_FIX_SETUP },
_IsollMem2 		{ ISET_FIX_SETUP },
_InSourceMem2   { inAuto },
_RshuntFineFlag { false },
_PowActiveStart { false }
{

}

void NonVolatileData::update(
		KeyEventTuple 	actTuple,
		ScreenStateEnum actScreen,
		VolatileData		volatileData) {

	if(actScreen == scrStrtValues) {
		updateStrtValues(actTuple);
	}

	if(actScreen == scrCalib) {
		updateCalib(volatileData, actTuple);
	}

	if(actScreen == scrTgrenz) {
		updateTgrenz(actTuple);
	}

}

void NonVolatileData::updateStrtValues(KeyEventTuple actTuple) {
	if ( (actTuple.key == keyRotLeft) && (actTuple.event == evntIncrement) ) {
		incrementStrtMemoryEnum(_strtMemory);
	}

	if ( (actTuple.key == keyRotLeft) && (actTuple.event == evntDecrement) ) {
		decrementStrtMemoryEnum(_strtMemory);
	}

	if ( (actTuple.key == keyBtnOnOff) && (actTuple.event == evntReleased) ) {
		if(_PowActiveStart == true)
			_PowActiveStart = false;
		else
			_PowActiveStart = true;
	}
}

void NonVolatileData::updateCalib(
		VolatileData	volatileData, KeyEventTuple actTuple) {
	if ( (actTuple.key == keyRotLeft) && (actTuple.event == evntIncrement) ) {
		volatileData.getUsoll().increment();
	}

	if ( (actTuple.key == keyRotLeft) && (actTuple.event == evntDecrement) ) {
		volatileData.getUsoll().decrement();
	}

	if ( (actTuple.key == keyBtnLeft) && (actTuple.event == evntReleased) ) {
		volatileData.getUsoll().toggleFineFlag();
	}

	if ( (actTuple.key == keyRotRight) && (actTuple.event == evntIncrement) ) {
		_Rshunt.increment();
	}

	if ( (actTuple.key == keyRotRight) && (actTuple.event == evntDecrement) ) {
		_Rshunt.decrement();
	}

	if ( (actTuple.key == keyBtnRight) && (actTuple.event == evntReleased) ) {
		_Rshunt.incrementActualPlace();
	}
}


void NonVolatileData::updateTgrenz(KeyEventTuple actTuple) {

	if ( (actTuple.key == keyRotLeft) && (actTuple.event == evntIncrement) ) {
		_TtrafoMax.increment();
	}
	if ( (actTuple.key == keyRotLeft) && (actTuple.event == evntDecrement) ) {
		_TtrafoMax.decrement();
	}
	if ( (actTuple.key == keyRotRight) && (actTuple.event == evntIncrement) ) {
		_TendstufeMax.increment();
	}
	if ( (actTuple.key == keyRotRight) && (actTuple.event == evntDecrement) ) {
		_TendstufeMax.decrement();
	}

}

void NonVolatileData::incrementStrtMemoryEnum(StrtMemoryEnum& in) {
	switch(in) {
	case strtNone:
		in = strtMem1;
		break;
	case strtMem1:
		in = strtMem2;
		break;
	case strtMem2:
		in = strtNone;
		break;
	}
}

void NonVolatileData::decrementStrtMemoryEnum(StrtMemoryEnum& in) {
	switch(in) {
	case strtNone:
		in = strtMem2;
		break;
	case strtMem1:
		in = strtNone;
		break;
	case strtMem2:
		in = strtMem1;
		break;
	}
}

} /* namespace encodeNButtons */
