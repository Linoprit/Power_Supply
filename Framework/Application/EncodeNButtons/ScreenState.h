/*
 * ScreenStates.h
 *
 *  Created on: 03.05.2020
 *      Author: harald
 */

#ifndef APPLICATION_ENCODENBUTTONS_SCREENSTATE_H_
#define APPLICATION_ENCODENBUTTONS_SCREENSTATE_H_

#include <Devices/Rotary_Encoder/Rotary_Encoder_Types.h>


namespace encodeNButtons {
using namespace rotaryEncoder;

enum ScreenStateEnum {
	scrValues = 0, scrThetas, scrUsource, // contains volatile data
	scrStrtValues, scrTgrenz, scrCalib		// contains nonVolatile data
};


class ScreenState {
public:
	ScreenState();
	virtual ~ScreenState() {};

	// only btn_released, btn_pressed, btn_held is taken into account
	void update(KeyEvent_enum 	scrEvent);

	ScreenStateEnum getActSreen(void) const { return _actScreen; };

	// returns true, if _actScreen contains NonVolatileData
	bool isActScreenSetup(void) const { return _actScreen > scrUsource; };

private:
	ScreenStateEnum 	_actScreen;
	KeyEvent_enum			_lastEvent;

};

} /* namespace encodeNButtons */

#endif /* APPLICATION_ENCODENBUTTONS_SCREENSTATE_H_ */
