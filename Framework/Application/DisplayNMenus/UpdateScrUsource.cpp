/*
 * UpdateScrUsource.cpp
 *
 *  Created on: 23.05.2020
 *      Author: harald
 */

#include <Application/DisplayNMenus/UpdateScrUsource.h>
#include <Instances/Common.h>
#include <Application/MeasureNControl/MeasureNControl.h>

namespace displaynmenus {

void UpdateScrUsource::cycle(Char_LCD& charLCD){
	clearBuffLines(charLCD);

	osStatus_t encdStatus = osSemaphoreAcquire(EncdTskDataSemHandle, 20);
	const encodeNButtons::VolatileData	volatileData =
			encodeNButtons::EncodeNButtons::instance().getVolData();
	osSemaphoreRelease(EncdTskDataSemHandle);

	osStatus_t measStatus = osSemaphoreAcquire(CtrTskDataSemHandle, 20);
	 const measureNControl::MeasuredData measuredData =
			 measureNControl::MeasureNControl::instance().getMeasuredData();
	osSemaphoreRelease(CtrTskDataSemHandle);

	if ( (encdStatus != osOK) || (measStatus != osOK) )
		return;

	// Line 1
	if(volatileData.isPowActive()) {
		measuredData.get_Uist().toString(&charLCD.buffer_lines[0][1], 4, 1);
		charLCD.buffer_lines[0][5] = 'V';

		measuredData.get_Iist().toString(&charLCD.buffer_lines[0][8], 4, 1);
		charLCD.buffer_lines[0][12] = 'A';
	} else {
		memcpy(&charLCD.buffer_lines[0][0], "  -- Zero -- ", 13);
	}

	// Line 2
	memcpy(&charLCD.buffer_lines[1][0], "Us", 2);
	measuredData.get_Uinput().toString(&charLCD.buffer_lines[1][3], 4, 1);
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
