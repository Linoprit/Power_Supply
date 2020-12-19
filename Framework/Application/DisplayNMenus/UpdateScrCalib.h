/*
 * UpdateScrCalib.h
 *
 *  Created on: 23.05.2020
 *      Author: harald
 */

#ifndef APPLICATION_DISPLAYNMENUS_UPDATESCRCALIB_H_
#define APPLICATION_DISPLAYNMENUS_UPDATESCRCALIB_H_

#include "UpdateBufflinesBase.h"
#include <Devices/Char_LCD/Char_LCD.h>


namespace displaynmenus {

class UpdateScrCalib: UpdateBufflinesBase {
public:
	UpdateScrCalib() { };
	virtual ~UpdateScrCalib() { };

	virtual void cycle(Char_LCD& charLCD);
};

} /* namespace displaynmenus */

#endif /* APPLICATION_DISPLAYNMENUS_UPDATESCRCALIB_H_ */
