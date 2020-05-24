/*
 * UpdateBufflinesBase.h
 *
 *  Created on: 23.05.2020
 *      Author: harald
 */

#ifndef APPLICATION_DISPLAYNMENUS_UPDATEBUFFLINESBASE_H_
#define APPLICATION_DISPLAYNMENUS_UPDATEBUFFLINESBASE_H_

#include <libraries/HelpersLib.h>
#include <Devices/Char_LCD/Char_LCD.h>
#include <string.h>

namespace displaynmenus {

class UpdateBufflinesBase {
public:

	virtual ~UpdateBufflinesBase() { };
	virtual void cycle(Char_LCD& charLCD) = 0;

	void clearBuffLines(Char_LCD& charLCD) {
		memset(&charLCD.buffer_lines[0][0], ' ', LCD_BUFFER_LEN);
		memset(&charLCD.buffer_lines[1][0], ' ', LCD_BUFFER_LEN);
	}


protected:
	UpdateBufflinesBase() { };
};

} /* namespace displaynmenus */

#endif /* APPLICATION_DISPLAYNMENUS_UPDATEBUFFLINESBASE_H_ */
