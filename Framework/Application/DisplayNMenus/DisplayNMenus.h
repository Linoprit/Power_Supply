/*
 * DisplayNData.h
 *
 *  Created on: 23.02.2020
 *      Author: harald
 */

#ifndef APPLICATION_DISPLAYNMENUS_DISPLAYNMENUS_H_
#define APPLICATION_DISPLAYNMENUS_DISPLAYNMENUS_H_

#include <Devices/Char_LCD/Char_LCD_socket.h>
#include <Devices/Char_LCD/Char_LCD.h>
#include <Application/EncodeNButtons/EncodeNButtons.h>
#include <Application/EncodeNButtons/ScreenState.h>
#include "cmsis_os2.h"

extern osSemaphoreId_t EncdTskDataSemHandle;


namespace displaynmenus {

class DisplayNMenus {
public:
	DisplayNMenus();
	virtual ~DisplayNMenus() {};

	void init(void);
	static DisplayNMenus& instance(void);
	void cycle(void);

private:
	Char_LCD_socket		_socket;
	Char_LCD					_charLCD;


};

} /* namespace displayndata */

#endif /* APPLICATION_DISPLAYNMENUS_DISPLAYNMENUS_H_ */
