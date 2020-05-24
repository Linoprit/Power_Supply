/*
 * UpdateScrTgrenz.cpp
 *
 *  Created on: 23.05.2020
 *      Author: harald
 */

#include <Application/DisplayNMenus/UpdateScrTgrenz.h>

namespace displaynmenus {

void UpdateScrTgrenz::cycle(Char_LCD& charLCD){
	clearBuffLines(charLCD);

	osSemaphoreAcquire(EncdTskDataSemHandle, 20);
	encodeNButtons::NonVolatileData	nonVolatileData =
			encodeNButtons::EncodeNButtons::instance().getNvDataConst();
	osSemaphoreRelease(EncdTskDataSemHandle);

	// Line 1
	memcpy(&charLCD.buffer_lines[0][0], "Tmax Trafo", 10);
	HelpersLib::value2char(
			&charLCD.buffer_lines[0][11], 2, 0, nonVolatileData.getTtrafoMax().get()/10);

	// Line 2
	memcpy(&charLCD.buffer_lines[1][0], "Tmax Endst", 10);
	HelpersLib::value2char(
			&charLCD.buffer_lines[1][11], 2, 0, nonVolatileData.getTendstufeMax().get()/10);
}

} /* namespace displaynmenus */
