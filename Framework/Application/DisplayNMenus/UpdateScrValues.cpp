/*
 * UpdateScrValues.cpp
 *
 *  Created on: 23.05.2020
 *      Author: harald
 */

#include <Application/DisplayNMenus/UpdateScrValues.h>

namespace displaynmenus {


void UpdateScrValues::cycle(Char_LCD& charLCD) {
	clearBuffLines(charLCD);

	osSemaphoreAcquire(EncdTskDataSemHandle, 20);
	encodeNButtons::VolatileData	volatileData =
			encodeNButtons::EncodeNButtons::instance().getVolDataConst();
	osSemaphoreRelease(EncdTskDataSemHandle);

	// Line 1
	if(volatileData.isKeysLocked()) {
		charLCD.buffer_lines[0][15] = 'L';
	} else {
		charLCD.buffer_lines[0][15] = ' ';
	}

	//HelpersLib::value2char(
	//		&charLCD.buffer_lines[0][1], 4, 1,  /* measurement */);
	charLCD.buffer_lines[0][5] = 'V';

	//HelpersLib::value2char(
	//		&charLCD.buffer_lines[1][8], 4, 1, /* measurement */);
	charLCD.buffer_lines[0][12] = 'A';

	// Line 2
	if( volatileData.getInSource() == encodeNButtons::inAuto) {
		charLCD.buffer_lines[1][15] = 'A';
	} else if( volatileData.getInSource() == encodeNButtons::inHigh) {
		charLCD.buffer_lines[1][15] = 'H';
	} else if( volatileData.getInSource() == encodeNButtons::inLow) {
		charLCD.buffer_lines[1][15] = 'L';
	}

	HelpersLib::value2char(
			&charLCD.buffer_lines[1][1], 4, 1, volatileData.getUsoll().get());
	charLCD.buffer_lines[1][5] = 'V';

	HelpersLib::value2char(
			&charLCD.buffer_lines[1][8], 4, 1, volatileData.getIsoll().get());
	charLCD.buffer_lines[1][12] = 'A';

	if (volatileData.getUsoll().isFineFlag()) {
		charLCD.buffer_lines[1][0] = 'F';
	} else {
		charLCD.buffer_lines[1][0] = ' ';
	}

	if (volatileData.getIsoll().isFineFlag()) {
		charLCD.buffer_lines[1][7] = 'F';
	} else {
		charLCD.buffer_lines[1][7] = ' ';
	}
}


} /* namespace displaynmenus */
