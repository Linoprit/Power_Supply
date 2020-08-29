/*
 * VolatileData.cpp
 *
 *  Created on: 03.05.2020
 *      Author: harald
 */

#include <Application/EncodeNButtons/VolatileData.h>
#include <Instances/Common.h>
#include "NonVolatileData.h"
#include "main.h"


namespace encodeNButtons {

VolatileData::VolatileData():
	_Usoll 					{ USOLL_ADJ_SETUP },
	_Isoll 					{ ISOLL_ADJ_SETUP },
	_InSource 				{	inAuto },
	_PowActive				{ false },
	_UsollFineFlag			{ false },
	_IsollFineFlag			{ false },
	_KeysLocked   			{ false },
	_LastOnOffButtonEvent 	{ evntNone },
	_MemStoreEvntActive		{ false		 },
	_MemEvntCounter			{ 0 			 }
{
}

void VolatileData::update(
		KeyEventTuple 	actTuple,
		ScreenStateEnum actScreen,
		NonVolatileData& nonVolatileData) {

	if((actTuple.key == keyBtnOnOff) && (actTuple.event == evntPressed)) {
		_LastOnOffButtonEvent = evntPressed;
	}

	// allow to unlock in case of key-lock
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

	if(actTuple.key == keyBtnM1) {
		keyMemory1(	nonVolatileData, actTuple.event );
	}

	if (actTuple.key == keyBtnM2) {
		keyMemory2(	nonVolatileData, actTuple.event );
	}

	if( (actTuple.key == keyBtnOnOff)
			&& (actTuple.event == evntReleased)
			&& (_LastOnOffButtonEvent == evntPressed) )
	{
		_LastOnOffButtonEvent = evntReleased;
		keyButtonOnOff();
	}

	if( (actScreen == scrValues) || (actScreen == scrThetas) ){
		updateValues(	actTuple );
	}

	if(actScreen == scrUsource) {
		updateUsource(actTuple);
	}
}

void VolatileData::setMemEvent(void) {
	_MemStoreEvntActive = true;
	_MemEvntCounter 		= Common::get_tick() + MemEventCount;
}

void VolatileData::updateMemEvent(void) {
	if (Common::get_tick() > _MemEvntCounter) {
		_MemStoreEvntActive = false;
	}
}

void VolatileData::keyMemory1(NonVolatileData& nonVolatileData, KeyEvent_enum	event) {
	// set mem1
	if(event == evntHeld) {
		nonVolatileData.getUsollMem1().set(_Usoll.get());
		nonVolatileData.getIsollMem1().set(_Isoll.get());
		nonVolatileData.setInSourceMem1(getInSource());
		// TODO store MEM1 to EEPROM
		setMemEvent();
	}

	// recall mem1
	if(event == evntReleased) {
		_Usoll.set(nonVolatileData.getUsollMem1().get());
		_Isoll.set(nonVolatileData.getIsollMem1().get());
		_InSource = nonVolatileData.getInSourceMem1();
	}
}

void VolatileData::keyMemory2(NonVolatileData& nonVolatileData, KeyEvent_enum	event) {
	// set mem2
	if(event == evntHeld) {
		nonVolatileData.getUsollMem2().set(_Usoll.get());
		nonVolatileData.getIsollMem2().set(_Isoll.get());
		nonVolatileData.setInSourceMem2(getInSource());
		// TODO store MEM2 to EEPROM
		setMemEvent();
	}

	// recall mem2
	if(event == evntReleased) {
		_Usoll.set(nonVolatileData.getUsollMem2().get());
		_Isoll.set(nonVolatileData.getIsollMem2().get());
		_InSource = nonVolatileData.getInSourceMem2();
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

	if ( (actTuple.key == keyBtnLeft) && (actTuple.event == evntReleased) ) {
		_Usoll.toggleFineFlag();
	}

	if ( (actTuple.key == keyRotRight) && (actTuple.event == evntIncrement) ) {
		_Isoll.increment();
	}

	if ( (actTuple.key == keyRotRight) && (actTuple.event == evntDecrement) ) {
		_Isoll.decrement();
	}

	if ( (actTuple.key == keyBtnRight) && (actTuple.event == evntReleased) ) {
		_Isoll.toggleFineFlag();
	}
}

void VolatileData::updateUsource(KeyEventTuple actTuple) {
	// RotEnc for Usoll is active
	if ( (actTuple.key == keyRotLeft) && (actTuple.event == evntIncrement) ) {
		_Usoll.increment();
	}

	if ( (actTuple.key == keyRotLeft) && (actTuple.event == evntDecrement) ) {
		_Usoll.decrement();
	}

	if ( (actTuple.key == keyBtnLeft) && (actTuple.event == evntReleased) ) {
		_Usoll.toggleFineFlag();
	}

	if ( (actTuple.key == keyRotRight) && (actTuple.event == evntIncrement) ) {
		if (_InSource == inHigh )
			_InSource = inLow;
		else if (_InSource == inLow)
			_InSource = inAuto;
		else if (_InSource == inAuto)
			_InSource = inHigh;
	}

	if ( (actTuple.key == keyRotRight) && (actTuple.event == evntDecrement) ) {
		if (_InSource == inHigh )
			_InSource = inAuto;
		else if (_InSource == inLow)
			_InSource = inHigh;
		else if (_InSource == inAuto)
			_InSource = inLow;

	}
}

} /* namespace encodeNButtons */
