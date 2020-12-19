/*
 * DisplayNData.cpp
 *
 *  Created on: 23.02.2020
 *      Author: harald
 */

#include <Application/DisplayNMenus/DisplayNMenus.h>
#include <Instances/Common.h>
#include <new>
#include <string.h>
#include <main.h>
#include <Instances/Common.h>
#include <libraries/HelpersLib.h>
#include "UpdateScrValues.h"
#include "UpdateScrStrtValues.h"
#include "UpdateScrTgrenz.h"
#include "UpdateScrThetas.h"
#include "UpdateScrUsource.h"
#include "UpdateScrCalib.h"

namespace displaynmenus {

void DisplayNMenus::init(void) {
	new (&instance()) DisplayNMenus();
}

DisplayNMenus& DisplayNMenus::instance(void) {
	static DisplayNMenus displayNData;
	return displayNData;
}

DisplayNMenus::DisplayNMenus()
{
	_socket =
			Char_LCD_socket(
					get_hspi3(),
					Char_LCD_RS_GPIO_Port,
					Char_LCD_EN_GPIO_Port,
					Char_LCD_RS_Pin,
					Char_LCD_EN_Pin);

	_charLCD = Char_LCD(&_socket);
	_charLCD.clear();
}

void DisplayNMenus::cycle(void) {
	osSemaphoreAcquire(EncdTskDataSemHandle, 20);
	const encodeNButtons::ScreenStateEnum			actScreen =
			encodeNButtons::EncodeNButtons::instance().getScreenState().getActSreen();
	osSemaphoreRelease(EncdTskDataSemHandle);

	if(actScreen == encodeNButtons::scrValues) {
		UpdateScrValues updateScrValues;
		updateScrValues.cycle(_charLCD);
  }
	else if(actScreen == encodeNButtons::scrThetas) {
		UpdateScrThetas updateScrThetas;
		updateScrThetas.cycle(_charLCD);
  }
	else if(actScreen == encodeNButtons::scrUsource) {
		UpdateScrUsource updateUsource;
		updateUsource.cycle(_charLCD);
  }
	else if(actScreen == encodeNButtons::scrStrtValues) {
		UpdateScrStrtValues updateScrStrtValues;
		updateScrStrtValues.cycle(_charLCD);
  }
	else if(actScreen == encodeNButtons::scrTgrenz) {
		UpdateScrTgrenz updateScrTgrenz;
		updateScrTgrenz.cycle(_charLCD);
  }
	else if(actScreen == encodeNButtons::scrCalib) {
		UpdateScrCalib updateScrCalib;
		updateScrCalib.cycle(_charLCD);
  }

	_charLCD.display();


	//buffer_lines_type* lcdBuffer = _charLCD.get_buffer_lines_ptr();

/*	static uint8_t counter = 0;
	char buffer[] {'\0', '\0', '\0', '\0'};

	 HelpersLib::value2char(buffer, 3, 0, counter);

	strncpy(&_charLCD.buffer_lines[0][0], buffer, 3);

	_charLCD.display();

	counter++;*/
}



} // end namespace

