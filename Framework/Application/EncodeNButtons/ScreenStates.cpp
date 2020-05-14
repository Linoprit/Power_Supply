/*
 * ScreenStates.cpp
 *
 *  Created on: 03.05.2020
 *      Author: harald
 */

#include <Application/EncodeNButtons/ScreenStates.h>

namespace encodeNButtons {


ScreenStates::ScreenStates():
_actScreen {scrValues},
_lastEvent {evntNone}
{

}


void ScreenStates::update(KeyEvent_enum 	scrEvent) {

	if(scrEvent == evntHeld) {
		if ( isActScreenSetup() ) {
			_actScreen = scrValues;
		}
		else {
			_actScreen = scrStrtValues;
			// TODO save to E2P here?
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


}

} /* namespace encodeNButtons */
