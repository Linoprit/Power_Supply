/*
 * VolatileData.cpp
 *
 *  Created on: 03.05.2020
 *      Author: harald
 */

#include <Application/EncodeNButtons/VolatileData.h>

namespace encodeNButtons {

VolatileData::VolatileData():
	_Usoll 					{ USOLL_ADJ_SETUP },
	_Isoll 					{ ISOLL_ADJ_SETUP },
	_InSource 			{	inAuto },
	_PowActive			{ false },
	_UsollFineFlag	{ false },
	_IsollFineFlag	{ false },
	_KeysLocked   { false },
	_LastOnOffButtonEvent { evntNone }
{
}

void VolatileData::update(
		KeyEventTuple 	actTuple,
		ScreenStateEnum actScreen) {

	if((actTuple.key == keyBtnOnOff) && (actTuple.event == evntPressed)) {
		_LastOnOffButtonEvent = evntPressed;
	}

	if((actTuple.key == keyBtnOnOff) && (actTuple.event == evntHeld))
	{
		_LastOnOffButtonEvent = evntHeld;
		if(_KeysLocked == true)
			_KeysLocked = false;
		else
			_KeysLocked = true;
	}

	// guard, no update, if key-lock is true
	if (_KeysLocked == true) {
		return;
	}

	if( (actTuple.key == keyBtnOnOff)
			&& (actTuple.event == evntReleased)
			&& (_LastOnOffButtonEvent == evntPressed) )
	{
		_LastOnOffButtonEvent = evntReleased;
		keyButtonOnOff();
	}

	if(actScreen == scrValues) {
		updateValues(	actTuple );
	}

	// no keys active in active Thetadisplay
	/*if(actScreen == scrThetas) {
		updateThetas(	volatileData, actTuple);
	}*/

	if(actScreen == scrUsource) {
		updateUsource(actTuple);
	}
}

void VolatileData::keyButtonOnOff(void) {
	if(_PowActive == true)
		_PowActive = false;
	else
		_PowActive = true;
}

void VolatileData::updateValues(KeyEventTuple actTuple) {
	if ( (actTuple.key == keyRotLeft) && (actTuple.event == evntIncrement) ) {
		_Usoll.increment();
	}

	if ( (actTuple.key == keyRotLeft) && (actTuple.event == evntDecrement) ) {
		_Usoll.decrement();
	}

	if ( (actTuple.key == keyRotLeft) && (actTuple.event == evntReleased) ) {
	_Usoll.toggleFineFlag();
	}

	if ( (actTuple.key == keyRotRight) && (actTuple.event == evntIncrement) ) {
		_Isoll.increment();
	}

	if ( (actTuple.key == keyRotRight) && (actTuple.event == evntDecrement) ) {
		_Isoll.decrement();
	}

	if ( (actTuple.key == keyRotRight) && (actTuple.event == evntReleased) ) {
	_Isoll.toggleFineFlag();
	}
}

void VolatileData::updateUsource(KeyEventTuple actTuple) {
	if ( (actTuple.key == keyRotRight) && (actTuple.event == evntIncrement) ) {
		if (_InSource == inHigh )
			_InSource = inLow;
		else if (_InSource == inLow)
			_InSource = inAuto;
		else if (_InSource == inAuto)
			_InSource = inHigh;
	}

	if ( (actTuple.key == keyRotRight) && (actTuple.event == evntDecrement) ) {
		if ( (actTuple.key == keyRotRight) && (actTuple.event == evntIncrement) ) {
			if (_InSource == inHigh )
				_InSource = inAuto;
			else if (_InSource == inLow)
				_InSource = inHigh;
			else if (_InSource == inAuto)
				_InSource = inLow;
		}
	}
}

} /* namespace encodeNButtons */
