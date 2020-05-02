/*
 * DisplayNData.h
 *
 *  Created on: 23.02.2020
 *      Author: harald
 */

#ifndef APPLICATION_DISPLAYNDATA_DISPLAYNDATA_H_
#define APPLICATION_DISPLAYNDATA_DISPLAYNDATA_H_

#include <Devices/Char_LCD/Char_LCD_socket.h>
#include <Devices/Char_LCD/Char_LCD.h>

namespace displayndata {

class DisplayNData {
public:
	DisplayNData();
	virtual ~DisplayNData() {};

	void init(void);
	static DisplayNData& instance(void);
	void cycle(void);

private:
	Char_LCD_socket		_socket;
	Char_LCD					_charLCD;


};

} /* namespace displayndata */

#endif /* APPLICATION_DISPLAYNDATA_DISPLAYNDATA_H_ */
