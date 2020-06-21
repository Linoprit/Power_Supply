/*
 * UpdateScrValues.cpp
 *
 *  Created on: 23.05.2020
 *      Author: harald
 */

#include <Application/DisplayNMenus/UpdateScrValues.h>
#include <Instances/Common.h>
#include <Application/MeasureNControl/MeasureNControl.h>

namespace displaynmenus {


void UpdateScrValues::cycle(Char_LCD& charLCD) {
	clearBuffLines(charLCD);

	osStatus_t encdStatus = osSemaphoreAcquire(EncdTskDataSemHandle, 20);
	const encodeNButtons::VolatileData	volatileData =
			encodeNButtons::EncodeNButtons::instance().getVolData();
	osSemaphoreRelease(EncdTskDataSemHandle);

	osStatus_t measStatus = osSemaphoreAcquire(CtrTskDataSemHandle, 20);
	 const measureNControl::MeasuredData measuredData =
			 measureNControl::MeasureNControl::instance().getMeasuredData();
	 const measureNControl::ControlOutput controlOutput =
			 measureNControl::MeasureNControl::instance().getControlOutput();
	osSemaphoreRelease(CtrTskDataSemHandle);

	if ( (encdStatus != osOK) || (measStatus != osOK) )
		return;

	if( checkNdisplayErrors(charLCD, measuredData.isError(), controlOutput.isError()) )
			return;

	// Line 1
	displaySpecialFields(
			charLCD, volatileData.isKeysLocked(), volatileData.isMemStoreEvntActive());

	if(volatileData.isPowActive()) {
		measuredData.get_Uist().toString(&charLCD.buffer_lines[0][1], 4, 1);
		charLCD.buffer_lines[0][5] = 'V';

		measuredData.get_Iist().toString(&charLCD.buffer_lines[0][8], 4, 1);
		charLCD.buffer_lines[0][12] = 'A';
	} else {
		memcpy(&charLCD.buffer_lines[0][0], "  -- Zero -- ", 13);
	}

	// Line 2
	displayInSource(charLCD, volatileData.getInSource());

	HelpersLib::value2char(&charLCD.buffer_lines[1][1], 4, 1, volatileData.getUsoll().get());
	charLCD.buffer_lines[1][5] = 'V';

	HelpersLib::value2char(&charLCD.buffer_lines[1][8], 4, 1, volatileData.getIsoll().get());
	charLCD.buffer_lines[1][12] = 'A';

	if (volatileData.getUsoll().isFineFlag()) {
		charLCD.buffer_lines[1][0] = 'F';
	}

	if (volatileData.getIsoll().isFineFlag()) {
		charLCD.buffer_lines[1][7] = 'F';
	}
}

void UpdateScrValues::displaySpecialFields(
		Char_LCD& charLCD,
		bool isKeysLocked,
		bool isMemStoreEvntActive	) {

	if(isKeysLocked) 					{ charLCD.buffer_lines[0][15] = 'L'; 	}
	if(isMemStoreEvntActive) 	{	charLCD.buffer_lines[0][14] = 'M'; 	}

}

void UpdateScrValues::displayInSource(
		Char_LCD& charLCD,
		encodeNButtons::InSourceEnum inSource) {
	if( inSource == encodeNButtons::inAuto) {
		charLCD.buffer_lines[1][15] = 'A';
	}
	else if( inSource == encodeNButtons::inHigh) {
		charLCD.buffer_lines[1][15] = 'H';
	}
	else if( inSource == encodeNButtons::inLow) {
		charLCD.buffer_lines[1][15] = 'L';
	}
}

bool UpdateScrValues::checkNdisplayErrors(
		Char_LCD& charLCD,
		bool measuredDataErrorFlag,
		bool ControlOutputErrorFlag) {

	if(measuredDataErrorFlag) {
		memcpy(&charLCD.buffer_lines[0][0], "Error", 5);
		memcpy(&charLCD.buffer_lines[1][0], "MeasuredData ", 13);
		return true;
	}

	if (ControlOutputErrorFlag) {
		memcpy(&charLCD.buffer_lines[0][0], "Error", 5);
		memcpy(&charLCD.buffer_lines[1][0], "ControlOutput", 13);
		return true;
	}

	return false;
}

} /* namespace displaynmenus */
