/*
 * UpdateScrThetas.cpp
 *
 *  Created on: 23.05.2020
 *      Author: harald
 */

#include <Application/DisplayNMenus/UpdateScrThetas.h>
#include <Application/MeasureNControl/MeasureNControl.h>
#include <cstring>
#include <string.h>

namespace displaynmenus {

void UpdateScrThetas::cycle(Char_LCD& charLCD) {
	clearBuffLines(charLCD);

	osStatus_t measStatus = osSemaphoreAcquire(CtrTskDataSemHandle, 20);
	 const measureNControl::MeasuredData measuredData =
			 measureNControl::MeasureNControl::instance().getMeasuredData();
	osSemaphoreRelease(CtrTskDataSemHandle);

	if (measStatus != osOK)
		return;

	// Line 1
	memcpy(&charLCD.buffer_lines[0][0], "Po=", 3);
	measuredData.get_Pout().toString(&charLCD.buffer_lines[0][3], 4, 1);
	memcpy(&charLCD.buffer_lines[0][7], "W E", 3);
	charLCD.buffer_lines[0][15] = 223;

	// Line 2
	memcpy(&charLCD.buffer_lines[1][0], "Pv=", 3);
	measuredData.get_Pwaste().toString(&charLCD.buffer_lines[1][3], 4, 1);
	memcpy(&charLCD.buffer_lines[1][7], "W T", 3);
	charLCD.buffer_lines[1][15] = 223;



	// TODO Messwerte Ausgeben


}

} /* namespace displaynmenus */
