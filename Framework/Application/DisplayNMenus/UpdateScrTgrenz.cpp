/*
 * UpdateScrTgrenz.cpp
 *
 *  Created on: 23.05.2020
 *      Author: harald
 */

#include <Application/DisplayNMenus/UpdateScrTgrenz.h>
#include <Instances/Common.h>

namespace displaynmenus {

void UpdateScrTgrenz::cycle(Char_LCD& charLCD){
	clearBuffLines(charLCD);

	osStatus_t status = osSemaphoreAcquire(EncdTskDataSemHandle, 20);
	const encodeNButtons::NonVolatileData	nonVolatileData =
			encodeNButtons::EncodeNButtons::instance().getNvData();
	osSemaphoreRelease(EncdTskDataSemHandle);

	if (status != osOK)
		return;

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
