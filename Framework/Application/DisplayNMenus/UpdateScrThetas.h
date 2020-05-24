/*
 * UpdateScrThetas.h
 *
 *  Created on: 23.05.2020
 *      Author: harald
 */

#ifndef APPLICATION_DISPLAYNMENUS_UPDATESCRTHETAS_H_
#define APPLICATION_DISPLAYNMENUS_UPDATESCRTHETAS_H_

#include "UpdateBufflinesBase.h"
#include "DisplayNMenus.h"

namespace displaynmenus {

class UpdateScrThetas: UpdateBufflinesBase {
public:
	UpdateScrThetas() { };
	virtual ~UpdateScrThetas() { };

	virtual void cycle(Char_LCD& charLCD);
};

} /* namespace displaynmenus */

#endif /* APPLICATION_DISPLAYNMENUS_UPDATESCRTHETAS_H_ */
