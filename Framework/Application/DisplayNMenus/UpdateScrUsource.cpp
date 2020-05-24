/*
 * UpdateScrUsource.cpp
 *
 *  Created on: 23.05.2020
 *      Author: harald
 */

#include <Application/DisplayNMenus/UpdateScrUsource.h>

namespace displaynmenus {

void UpdateScrUsource::cycle(Char_LCD& charLCD){
	clearBuffLines(charLCD);

	osSemaphoreAcquire(EncdTskDataSemHandle, 20);
	encodeNButtons::VolatileData	volatileData =
			encodeNButtons::EncodeNButtons::instance().getVolDataConst();
	osSemaphoreRelease(EncdTskDataSemHandle);

	// Line 1
	// TODO
	charLCD.buffer_lines[0][5] = 'V';
	charLCD.buffer_lines[0][12] = 'A';


	// Line 2
	memcpy(&charLCD.buffer_lines[1][0], "Us", 2);
	charLCD.buffer_lines[1][7] = 'V';

	if( volatileData.getInSource() == encodeNButtons::inAuto) {
		memcpy(&charLCD.buffer_lines[1][10], "S:Auto", 6);
	} else if( volatileData.getInSource() == encodeNButtons::inHigh) {
		memcpy(&charLCD.buffer_lines[1][10], "S:High", 6);
	} else if( volatileData.getInSource() == encodeNButtons::inLow) {
		memcpy(&charLCD.buffer_lines[1][10], "S:Low ", 6);
	}

}

} /* namespace displaynmenus */
