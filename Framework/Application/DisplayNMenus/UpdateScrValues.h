/*
 * UpdateScrValues.h
 *
 *  Created on: 23.05.2020
 *      Author: harald
 */

#ifndef APPLICATION_DISPLAYNMENUS_UPDATESCRVALUES_H_
#define APPLICATION_DISPLAYNMENUS_UPDATESCRVALUES_H_

#include "UpdateBufflinesBase.h"
#include "DisplayNMenus.h"

namespace displaynmenus {

class UpdateScrValues: UpdateBufflinesBase {
public:
	UpdateScrValues() { };
	virtual ~UpdateScrValues() { };

	virtual void cycle(Char_LCD& charLCD);

};

} /* namespace displaynmenus */

#endif /* APPLICATION_DISPLAYNMENUS_UPDATESCRVALUES_H_ */
