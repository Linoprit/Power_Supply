/*
 * UpdateScrStrtValues.cpp
 *
 *  Created on: 23.05.2020
 *      Author: harald
 */

#include <Application/DisplayNMenus/UpdateScrStrtValues.h>

namespace displaynmenus {

void UpdateScrStrtValues::cycle(Char_LCD& charLCD){
	clearBuffLines(charLCD);

	osSemaphoreAcquire(EncdTskDataSemHandle, 20);
	encodeNButtons::NonVolatileData	nonVolatileData =
			encodeNButtons::EncodeNButtons::instance().getNvDataConst();
	osSemaphoreRelease(EncdTskDataSemHandle);

	uint32_t Umem = 0;
	uint32_t Imem = 0;
	encodeNButtons::InSourceEnum inSource = encodeNButtons::inAuto;

	if(nonVolatileData.getStrtMemory() == encodeNButtons::strtNone) {
		memcpy(&charLCD.buffer_lines[0][0], "None", 4);
	} else if(nonVolatileData.getStrtMemory() == encodeNButtons::strtMem1) {
		memcpy(&charLCD.buffer_lines[0][0], "Mem1", 4);
		Umem = nonVolatileData.getUsollMem1().get();
		Imem = nonVolatileData.getIsollMem1().get();
		inSource = nonVolatileData.getInSourceMem1();
	} else if(nonVolatileData.getStrtMemory() == encodeNButtons::strtMem2) {
		memcpy(&charLCD.buffer_lines[0][0], "Mem2", 4);
		Umem = nonVolatileData.getUsollMem2().get();
		Imem = nonVolatileData.getIsollMem2().get();
		inSource = nonVolatileData.getInSourceMem2();
	}

	HelpersLib::value2char(
			&charLCD.buffer_lines[1][1], 4, 1, Umem);
	charLCD.buffer_lines[1][5] = 'V';

	HelpersLib::value2char(
			&charLCD.buffer_lines[1][8], 4, 1, Imem);
	charLCD.buffer_lines[1][12] = 'A';

	if( inSource == encodeNButtons::inAuto) {
		charLCD.buffer_lines[1][15] = 'A';
	} else if( inSource == encodeNButtons::inHigh) {
		charLCD.buffer_lines[1][15] = 'H';
	} else if( inSource == encodeNButtons::inLow) {
		charLCD.buffer_lines[1][15] = 'L';
	}

	if(nonVolatileData.isPowActiveStart()){
		memcpy(&charLCD.buffer_lines[0][8], "On ", 3);
	} else {
		memcpy(&charLCD.buffer_lines[0][8], "Off", 3);
	}

}


} /* namespace displaynmenus */
