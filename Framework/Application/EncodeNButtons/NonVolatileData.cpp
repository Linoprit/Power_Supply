/*
 * NonVolatileData.cpp
 *
 *  Created on: 03.05.2020
 *      Author: harald
 */

#include <Application/EncodeNButtons/NonVolatileData.h>

namespace encodeNButtons {

NonVolatileData::NonVolatileData(void):
_strtMemory 		{	strtNone },
_PowActiveStart {	false },
_Rshunt 			  { RSHUNT_ADJ_SETUP },
_TtrafoMax 		  { TEMP_ADJ_SETUP },
_TendstufeMax   { TEMP_ADJ_SETUP },
_UsollMem1      { USET_FIX_SETUP },
_IsollMem1      { ISET_FIX_SETUP },
_InSourceMem1   { inAuto },
_UsollMem2 		  { USET_FIX_SETUP },
_IsollMem2 		  { ISET_FIX_SETUP },
_InSourceMem2   { inAuto },
_RshuntFineFlag { false }
{

}

void NonVolatileData::update(
		KeyEventTuple 	actTuple,
		ScreenStateEnum actScreen,
		VolatileData		volatileData) {

	if(actTuple.key == keyBtnM1) {
		keyMemory1(	volatileData, actTuple.event );
	}

	if (actTuple.key == keyBtnM2) {
		keyMemory2(	volatileData, actTuple.event );
	}

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

void NonVolatileData::keyMemory1(VolatileData	volatileData, KeyEvent_enum	event) {
	// set mem1
	if(event == evntHeld) {
		_UsollMem1.set( volatileData.getUsoll().get() );
		_IsollMem1.set( volatileData.getIsoll().get() );
		_InSourceMem1	= volatileData.getInSource();
	}

	// recall mem1
	if(event == evntReleased) {
		volatileData.getUsoll().set(_UsollMem1.get());
		volatileData.getIsoll().set(_IsollMem1.get());
		volatileData.setInSource(_InSourceMem1);
	}
}

void NonVolatileData::keyMemory2(VolatileData	volatileData, KeyEvent_enum	event) {
	// set mem2
	if(event == evntHeld) {
		_UsollMem2.set(volatileData.getUsoll().get());
		_IsollMem2.set(volatileData.getIsoll().get());
		_InSourceMem2	= volatileData.getInSource();
	}

	// recall mem2
	if(event == evntReleased) {
		volatileData.getUsoll().set(_UsollMem2.get());
		volatileData.getIsoll().set(_IsollMem2.get());
		volatileData.setInSource(_InSourceMem2);
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

InSourceEnum NonVolatileData::getInSourceMem1() const {
	return _InSourceMem1;
}

InSourceEnum NonVolatileData::getInSourceMem2() const {
	return _InSourceMem2;
}

bool NonVolatileData::isPowActiveStart() const {
	return _PowActiveStart;
}

void NonVolatileData::setPowActiveStart(bool powActiveStart) {
	_PowActiveStart = powActiveStart;
}

ExtFloat& NonVolatileData::getRshunt() {
	return _Rshunt;
}

bool NonVolatileData::isRshuntFineFlag() const {
	return _RshuntFineFlag;
}

void NonVolatileData::setRshuntFineFlag(bool rshuntFineFlag) {
	_RshuntFineFlag = rshuntFineFlag;
}

StrtMemoryEnum NonVolatileData::getStrtMemory() const {
	return _strtMemory;
}

const ExtFloat& NonVolatileData::getTendstufeMax() const {
	return _TendstufeMax;
}

const ExtFloat& NonVolatileData::getTtrafoMax() const {
	return _TtrafoMax;
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
