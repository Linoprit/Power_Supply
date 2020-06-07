/*
 * UpdateScrCalib.cpp
 *
 *  Created on: 23.05.2020
 *      Author: harald
 */

#include <Application/DisplayNMenus/UpdateScrCalib.h>
#include "DisplayNMenus.h"

namespace displaynmenus {

void UpdateScrCalib::cycle(Char_LCD& charLCD){
	clearBuffLines(charLCD);

	osSemaphoreAcquire(EncdTskDataSemHandle, 20);
	encodeNButtons::NonVolatileData	nonVolatileData =
			encodeNButtons::EncodeNButtons::instance().getNvDataConst();
	osSemaphoreRelease(EncdTskDataSemHandle);

	// Line 1
	//HelpersLib::value2char(
	//		&charLCD.buffer_lines[0][1], 4, 1,  /* measurement */);
	charLCD.buffer_lines[0][4] = 'V';

	//HelpersLib::value2char(
	//		&charLCD.buffer_lines[1][8], 4, 1, /* measurement */);
	charLCD.buffer_lines[0][10] = 'A';

	uint8_t actPlace = nonVolatileData.getRshunt().getActualPlace();
	charLCD.buffer_lines[0][11 + actPlace] = 170;

	// Line 2
	//HelpersLib::value2char(
	//		&charLCD.buffer_lines[1][8], 4, 1, /* measurement */);
	memcpy(&charLCD.buffer_lines[1][5], "mV", 2);

	HelpersLib::value2char(
				&charLCD.buffer_lines[1][10], 6, 4, nonVolatileData.getRshunt().get());
	memcpy(&charLCD.buffer_lines[1][8], "Rs", 2);
}

} /* namespace displaynmenus */
