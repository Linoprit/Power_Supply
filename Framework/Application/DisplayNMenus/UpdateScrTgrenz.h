/*
 * UpdateScrTgrenz.h
 *
 *  Created on: 23.05.2020
 *      Author: harald
 */

#ifndef APPLICATION_DISPLAYNMENUS_UPDATESCRTGRENZ_H_
#define APPLICATION_DISPLAYNMENUS_UPDATESCRTGRENZ_H_

#include "UpdateBufflinesBase.h"
#include "DisplayNMenus.h"

namespace displaynmenus {

class UpdateScrTgrenz: UpdateBufflinesBase {
public:
	UpdateScrTgrenz() { };
	virtual ~UpdateScrTgrenz() { };

	virtual void cycle(Char_LCD& charLCD);
};

} /* namespace displaynmenus */

#endif /* APPLICATION_DISPLAYNMENUS_UPDATESCRTGRENZ_H_ */
