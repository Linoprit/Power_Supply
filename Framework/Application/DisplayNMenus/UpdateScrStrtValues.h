/*
 * UpdateScrStrtValues.h
 *
 *  Created on: 23.05.2020
 *      Author: harald
 */

#ifndef APPLICATION_DISPLAYNMENUS_UPDATESCRSTRTVALUES_H_
#define APPLICATION_DISPLAYNMENUS_UPDATESCRSTRTVALUES_H_

#include "UpdateBufflinesBase.h"
#include "DisplayNMenus.h"

namespace displaynmenus {

class UpdateScrStrtValues: UpdateBufflinesBase  {
public:
	UpdateScrStrtValues() { };
	virtual ~UpdateScrStrtValues() { };

	virtual void cycle(Char_LCD& charLCD);
};

} /* namespace displaynmenus */

#endif /* APPLICATION_DISPLAYNMENUS_UPDATESCRSTRTVALUES_H_ */
