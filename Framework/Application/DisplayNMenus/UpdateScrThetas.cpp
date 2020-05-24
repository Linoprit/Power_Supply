/*
 * UpdateScrThetas.cpp
 *
 *  Created on: 23.05.2020
 *      Author: harald
 */

#include <Application/DisplayNMenus/UpdateScrThetas.h>
#include <cstring>
#include <string.h>

namespace displaynmenus {

void UpdateScrThetas::cycle(Char_LCD& charLCD) {
	clearBuffLines(charLCD);

	memcpy(&charLCD.buffer_lines[0][0], "Po=", 3);
	memcpy(&charLCD.buffer_lines[0][8], "W E", 3);
	charLCD.buffer_lines[0][15] = 223;

	memcpy(&charLCD.buffer_lines[1][0], "Pv=", 3);
	memcpy(&charLCD.buffer_lines[1][8], "W T", 3);
	charLCD.buffer_lines[0][15] = 223;



	// TODO Messwerte Ausgeben


}

} /* namespace displaynmenus */
