/*
 * UpdateScrUsource.h
 *
 *  Created on: 23.05.2020
 *      Author: harald
 */

#ifndef APPLICATION_DISPLAYNMENUS_UPDATESCRUSOURCE_H_
#define APPLICATION_DISPLAYNMENUS_UPDATESCRUSOURCE_H_

#include "UpdateBufflinesBase.h"
#include "DisplayNMenus.h"

namespace displaynmenus {

class UpdateScrUsource: UpdateBufflinesBase  {
public:
	UpdateScrUsource() { };
	virtual ~UpdateScrUsource() { };

	virtual void cycle(Char_LCD& charLCD);

};

} /* namespace displaynmenus */

#endif /* APPLICATION_DISPLAYNMENUS_UPDATESCRUSOURCE_H_ */
