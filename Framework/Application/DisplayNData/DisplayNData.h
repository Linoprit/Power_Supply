/*
 * DisplayNData.h
 *
 *  Created on: 23.02.2020
 *      Author: harald
 */

#ifndef APPLICATION_DISPLAYNDATA_DISPLAYNDATA_H_
#define APPLICATION_DISPLAYNDATA_DISPLAYNDATA_H_

#include <Devices/Char_LCD/Char_LCD_socket.h>

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

	void init_char_LCD(void);
};

} /* namespace displayndata */

#endif /* APPLICATION_DISPLAYNDATA_DISPLAYNDATA_H_ */
