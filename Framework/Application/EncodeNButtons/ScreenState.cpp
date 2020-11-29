/*
 * ScreenStates.cpp
 *
 *  Created on: 03.05.2020
 *      Author: harald
 */

#include <Application/EncodeNButtons/ScreenState.h>

namespace encodeNButtons {


ScreenState::ScreenState():
_actScreen {scrValues},
_lastEvent {evntNone}
{

}


bool ScreenState::update(KeyEvent_enum scrEvent) {
	bool retVal = false;

	if(scrEvent == evntHeld) {
		if ( isActScreenSetup() ) {
			_actScreen = scrValues;
			retVal = true;
		}
		else {
			_actScreen = scrStrtValues;
		}
	}

	if( (scrEvent == evntReleased) && (_lastEvent == evntPressed) ){
			switch(_actScreen){

			case scrValues:
				_actScreen = scrThetas;
				break;

			case scrThetas:
				_actScreen = scrUsource;
				break;

			case scrUsource:
				_actScreen = scrValues;
				break;

			case scrStrtValues:
				_actScreen = scrTgrenz;
				break;

			case scrTgrenz:
				_actScreen = scrCalib;
				break;

			case scrCalib:
				_actScreen = scrStrtValues;
				break;
			}

	}

	_lastEvent = scrEvent;
	// all other cases are ignored!

	return retVal;
}

} /* namespace encodeNButtons */
