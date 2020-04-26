/*
 * DisplayNData.cpp
 *
 *  Created on: 23.02.2020
 *      Author: harald
 */

#include <Application/DisplayNData/DisplayNData.h>
#include <new>
#include <main.h>
#include <Instances/Common.h>



namespace displayndata {

//Char_LCD_socket	DisplayNData::_socket;


void DisplayNData::init(void) {
	new (&instance()) DisplayNData();
}

DisplayNData& DisplayNData::instance(void) {
	static DisplayNData displayNData;
	return displayNData;
}

DisplayNData::DisplayNData() {
	_socket =
			Char_LCD_socket(
					get_hspi3,
					Char_LCD_RS_GPIO_Port,
					Char_LCD_EN_GPIO_Port,
					Char_LCD_RS_Pin,
					Char_LCD_EN_Pin);
}

void DisplayNData::cycle(void) {

}

void DisplayNData::init_char_LCD(void) {


	char_lcd = new Char_LCD(socket);
}

} // end namespace

