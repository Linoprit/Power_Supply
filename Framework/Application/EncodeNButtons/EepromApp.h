/*
 * EepromApp.h
 *
 *  Created on: Nov 22, 2020
 *      Author: harald
 */

#ifndef APPLICATION_ENCODENBUTTONS_EEPROMAPP_H_
#define APPLICATION_ENCODENBUTTONS_EEPROMAPP_H_


#include "Devices/Eeprom_93C86/Eeprom_93C86.h"
#include <Types/Typedefs.h>


namespace encodeNButtons {

class StartValType {
public:
	encodeNButtons::StrtMemoryEnum 	memID;
	bool	 		powActive;
	uint16_t 		padding;
	eeprom::CrcType crc;
}__attribute__ ((packed));

class MemValType {
public:
	int32_t Usoll1;
	int32_t Isoll1;
	int32_t Usoll2;
	int32_t Isoll2;
	encodeNButtons::InSourceEnum 	inSource1;
	encodeNButtons::InSourceEnum 	inSource2;
	uint16_t padding;
	eeprom::CrcType crc;
}__attribute__ ((packed));

class CalibValType {
public:
	int32_t Rshunt;
	uint8_t TtrafoMax;
	uint8_t	TendstMax;
	uint16_t padding;
	eeprom::CrcType crc;
}__attribute__ ((packed));


class EepromApp {
public:
	EepromApp();
	virtual ~EepromApp() {};

	// returns false and erases device, if no valid data can be found
	bool initialRead(void);

	// returns false, if no valid data can be found
	bool readCalibVals(
			int32_t& Rshunt, uint8_t& TtrafoMax, uint8_t& TendstMax);

	// returns false and erases device, if no valid data can be found
	bool writeCalibVals(
			int32_t Rshunt, uint8_t TtrafoMax, uint8_t TendstMax);

	// returns false, if no valid data can be found
	bool readMemVals(
			int32_t &Usoll1, int32_t &Isoll1, encodeNButtons::InSourceEnum &inSource1,
			int32_t &Usoll2, int32_t &Isoll2, encodeNButtons::InSourceEnum &inSource2);

	// returns false and erases device, if no valid data can be found
	bool writeMemVals(
			int32_t Usoll1, int32_t Isoll1, encodeNButtons::InSourceEnum &inSource1,
			int32_t Usoll2, int32_t Isoll2, encodeNButtons::InSourceEnum &inSource2);

	// returns false, if no valid data can be found
	bool readStartVals(
			encodeNButtons::StrtMemoryEnum &strtMemory,
			bool &isPowActiveStart);

	// returns false and erases device, if no valid data can be found
	bool writeStartVals(
			encodeNButtons::StrtMemoryEnum strtMemory,
			bool isPowActiveStart);

	void E2LedOn(void) {
		HAL_GPIO_WritePin(Led_EEPROM_GPIO_Port, Led_EEPROM_Pin, GPIO_PIN_SET);	};
	void E2LedOff(void) {
		HAL_GPIO_WritePin(Led_EEPROM_GPIO_Port, Led_EEPROM_Pin, GPIO_PIN_RESET);	};

	// for service
	bool cleanEeprom(void);
	eeprom::Eeprom_93C86 getEepromDevice(void) { return _eeprom; };


private:
	Eeprom_93C86_socket		_e2Socket;
	eeprom::Eeprom_93C86	_eeprom;

};

} /* namespace encodeNButtons */

#endif /* APPLICATION_ENCODENBUTTONS_EEPROMAPP_H_ */
