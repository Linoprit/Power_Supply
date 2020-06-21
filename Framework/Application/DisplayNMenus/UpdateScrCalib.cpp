/*
 * UpdateScrCalib.cpp
 *
 *  Created on: 23.05.2020
 *      Author: harald
 */

#include <Application/DisplayNMenus/UpdateScrCalib.h>
#include <Application/MeasureNControl/MeasureNControl.h>
#include <Instances/Common.h>
#include "DisplayNMenus.h"

namespace displaynmenus {

void UpdateScrCalib::cycle(Char_LCD& charLCD){
	clearBuffLines(charLCD);

	osStatus_t encdStatus = osSemaphoreAcquire(EncdTskDataSemHandle, 20);
	const encodeNButtons::NonVolatileData	nonVolatileData =
			encodeNButtons::EncodeNButtons::instance().getNvData();
	osSemaphoreRelease(EncdTskDataSemHandle);

	osStatus_t measStatus = osSemaphoreAcquire(CtrTskDataSemHandle, 20);
	 const measureNControl::MeasuredData measuredData =
			 measureNControl::MeasureNControl::instance().getMeasuredData();
	osSemaphoreRelease(CtrTskDataSemHandle);

	if ( (encdStatus != osOK) || (measStatus != osOK) )
		return;

	// Line 1
	measuredData.get_Uist().toString(&charLCD.buffer_lines[0][0], 4, 1);
	charLCD.buffer_lines[0][4] = 'V';

	measuredData.get_Iist().toString(&charLCD.buffer_lines[0][6], 4, 1);
	charLCD.buffer_lines[0][10] = 'A';

	uint8_t actPlace = nonVolatileData.getRshunt().getActualPlace();
	charLCD.buffer_lines[0][11 + actPlace] = 170;

	// Line 2
	//memcpy(&charLCD.buffer_lines[1][0], "Us", 2);
	measuredData.get_Ushunt().toString(&charLCD.buffer_lines[1][0], 5, 3);
	memcpy(&charLCD.buffer_lines[1][0], "Us ", 3);
	memcpy(&charLCD.buffer_lines[1][5], "mV Rs", 5);

	HelpersLib::value2char(
				&charLCD.buffer_lines[1][10], 6, 4, nonVolatileData.getRshunt().get());
}

} /* namespace displaynmenus */
