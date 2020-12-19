/*
 * EepromApp.cpp
 *
 *  Created on: Nov 22, 2020
 *      Author: harald
 */

#include <Application/EncodeNButtons/EepromApp.h>

#include <System/usb_printf.h>

namespace encodeNButtons {

EepromApp::EepromApp():
		_e2Socket {},
		_eeprom {&_e2Socket}
{
}

bool EepromApp::initialRead(void) {
	E2LedOn();
	bool result = _eeprom.init();

	if (result == false) { // format Eeprom
		_eeprom.eraseEeprom();
	}

	E2LedOff();
	return result;
}

bool EepromApp::readCalibVals(
		int32_t &Rshunt, uint8_t &TtrafoMax, uint8_t &TendstMax) {
	E2LedOn();

	CalibValType vals;
	bool result = _eeprom.readData(
			eeprom::ValueID::CalibVal,
			reinterpret_cast<uint8_t*>(&vals));

	Rshunt	= vals.Rshunt;
	TtrafoMax =	vals.TtrafoMax;
	TendstMax =	vals.TendstMax;

	E2LedOff();
	return result;
}

bool EepromApp::writeCalibVals(
		int32_t Rshunt, uint8_t TtrafoMax, uint8_t TendstMax) {

	E2LedOn();
	bool result = false;

	CalibValType newVals;
	newVals.Rshunt = Rshunt;
	newVals.TtrafoMax = TtrafoMax;
	newVals.TendstMax = TendstMax;

	int32_t oldRshunt = 0;
	uint8_t oldTtrafoMax;
	uint8_t oldTendstMax;
	result = readCalibVals(oldRshunt, oldTtrafoMax, oldTendstMax);

	if( (result != true)
			|| (oldRshunt != newVals.Rshunt)
			|| (oldTtrafoMax != newVals.TtrafoMax)
			|| (oldTendstMax != newVals.TendstMax) ) {

		result = _eeprom.writeData(
				eeprom::ValueID::CalibVal,
				reinterpret_cast<uint8_t*>(&newVals),
				sizeof(CalibValType));

		if (result == false) {
			_eeprom.eraseEeprom();
		}
	}

	E2LedOff();
	return result;
}

bool EepromApp::readMemVals(
		int32_t &Usoll1, int32_t &Isoll1, encodeNButtons::InSourceEnum &inSource1,
		int32_t &Usoll2, int32_t &Isoll2, encodeNButtons::InSourceEnum &inSource2) {

	E2LedOn();

	MemValType vals;
	bool result = _eeprom.readData(
			eeprom::ValueID::MemVal,
			reinterpret_cast<uint8_t*>(&vals));

	Usoll1 = vals.Usoll1;
	Isoll1 = vals.Isoll1;
	inSource1 = vals.inSource1;
	Usoll2 = vals.Usoll2;
	Isoll2 = vals.Isoll2;
	inSource2 = vals.inSource2;

	E2LedOff();
	return result;
}

bool EepromApp::writeMemVals(
		int32_t Usoll1, int32_t Isoll1, encodeNButtons::InSourceEnum &inSource1,
		int32_t Usoll2, int32_t Isoll2, encodeNButtons::InSourceEnum &inSource2) {

	E2LedOn();
	bool result = false;

	MemValType newVals;
	newVals.Usoll1 = Usoll1;
	newVals.Isoll1 = Isoll1;
	newVals.inSource1 = inSource1 ;
	newVals.Usoll2 = Usoll2;
	newVals.Isoll2 = Isoll2;
	newVals.inSource2 = inSource2;
	newVals.padding = 0;

	int32_t oldUsoll1 = 0;
	int32_t oldIsoll1 = 0;
	encodeNButtons::InSourceEnum oldInSource1 = encodeNButtons::InSourceEnum::inAuto ;
	int32_t oldUsoll2 = 0;
	int32_t oldIsoll2 = 0;
	encodeNButtons::InSourceEnum oldInSource2 = encodeNButtons::InSourceEnum::inAuto;

	result = readMemVals(oldUsoll1, oldIsoll1, oldInSource1,
			oldUsoll2, oldIsoll2, oldInSource2);

	if( (result != true)
			|| (oldUsoll1 != newVals.Usoll1)
			|| (oldIsoll1 != newVals.Isoll1)
			|| (oldInSource1 != newVals.inSource1)
			|| (oldUsoll2 != newVals.Usoll2)
			|| (oldIsoll2 != newVals.Isoll2)
			|| (oldInSource2 != newVals.inSource2) ) {

		result = _eeprom.writeData(
				eeprom::ValueID::MemVal,
				reinterpret_cast<uint8_t*>(&newVals),
				sizeof(MemValType));

		if (result == false) {
			_eeprom.eraseEeprom();
		}
	}

	E2LedOff();
	return result;
}

bool EepromApp::readStartVals(
		encodeNButtons::StrtMemoryEnum &strtMemory, bool &isPowActiveStart) {
	E2LedOn();

	StartValType vals;
	bool result = _eeprom.readData(
			eeprom::ValueID::StartVal,
			reinterpret_cast<uint8_t*>(&vals));

	strtMemory = vals.memID;
	isPowActiveStart = vals.powActive;

	E2LedOff();
	return result;
}

bool EepromApp::writeStartVals(
		encodeNButtons::StrtMemoryEnum strtMemory, bool isPowActiveStart) {

	E2LedOn();
	bool result = false;
	StartValType newVals;
	newVals.memID = strtMemory;
	newVals.powActive = isPowActiveStart;
	newVals.padding = 0;

	encodeNButtons::StrtMemoryEnum oldStrtMemory = encodeNButtons::StrtMemoryEnum::strtNone ;
	bool oldIsPowActiveStart = false;
	result = readStartVals(oldStrtMemory, oldIsPowActiveStart);

	if( (result != true)
			|| (oldStrtMemory != newVals.memID)
			|| (oldIsPowActiveStart != newVals.powActive) )
	{
		result = _eeprom.writeData(
				eeprom::ValueID::StartVal,
				reinterpret_cast<uint8_t*>(&newVals),
				sizeof(StartValType));

		if (result == false) {
			_eeprom.eraseEeprom();
			E2LedOff();
			return false;
		}
	}
	E2LedOff();
	return true;
}

bool EepromApp::cleanEeprom(void) {
	E2LedOn();
	_eeprom.eraseEeprom();
	E2LedOff();
	return true;
}




} /* namespace encodeNButtons */
