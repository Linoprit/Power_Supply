/*
 * NonVolatileData.cpp
 *
 *  Created on: 03.05.2020
 *      Author: harald
 */

#include <Application/EncodeNButtons/NonVolatileData.h>
#include <Types/Typedefs.h>
#include <System/usb_printf.h>
#include <Devices/Eeprom_93C86/Eeprom_93C86.h>


namespace encodeNButtons {

NonVolatileData::NonVolatileData(void):
_strtMemory 	{	strtNone },
_Rshunt 		{ RSHUNT_ADJ_SETUP },
_TtrafoMax 		{ TEMP_ADJ_SETUP },
_TendstufeMax   { TEMP_ADJ_SETUP },
_UsollMem1      { USET_FIX_SETUP },
_IsollMem1      { ISET_FIX_SETUP },
_InSourceMem1   { inAuto },
_UsollMem2 		{ USET_FIX_SETUP },
_IsollMem2 		{ ISET_FIX_SETUP },
_InSourceMem2   { inAuto },
_RshuntFineFlag { false },
_PowActiveStart { false }
{

}

void NonVolatileData::update(
		KeyEventTuple 	actTuple,
		ScreenStateEnum actScreen,
		VolatileData	volatileData) {

	if(actScreen == scrStrtValues) {
		updateStrtValues(actTuple);
	}

	if(actScreen == scrCalib) {
		updateCalib(volatileData, actTuple);
	}

	if(actScreen == scrTgrenz) {
		updateTgrenz(actTuple);
	}

}

void NonVolatileData::updateStrtValues(KeyEventTuple actTuple) {
	if ( (actTuple.key == keyRotLeft) && (actTuple.event == evntIncrement) ) {
		incrementStrtMemoryEnum(_strtMemory);
	}

	if ( (actTuple.key == keyRotLeft) && (actTuple.event == evntDecrement) ) {
		decrementStrtMemoryEnum(_strtMemory);
	}

	if ( (actTuple.key == keyBtnOnOff) && (actTuple.event == evntReleased) ) {
		if(_PowActiveStart == true)
			_PowActiveStart = false;
		else
			_PowActiveStart = true;
	}
}

void NonVolatileData::updateCalib(
		VolatileData	volatileData, KeyEventTuple actTuple) {
	if ( (actTuple.key == keyRotLeft) && (actTuple.event == evntIncrement) ) {
		volatileData.getUsoll().increment();
	}

	if ( (actTuple.key == keyRotLeft) && (actTuple.event == evntDecrement) ) {
		volatileData.getUsoll().decrement();
	}

	if ( (actTuple.key == keyBtnLeft) && (actTuple.event == evntReleased) ) {
		volatileData.getUsoll().toggleFineFlag();
	}

	if ( (actTuple.key == keyRotRight) && (actTuple.event == evntIncrement) ) {
		_Rshunt.increment();
	}

	if ( (actTuple.key == keyRotRight) && (actTuple.event == evntDecrement) ) {
		_Rshunt.decrement();
	}

	if ( (actTuple.key == keyBtnRight) && (actTuple.event == evntReleased) ) {
		_Rshunt.incrementActualPlace();
	}
}


void NonVolatileData::updateTgrenz(KeyEventTuple actTuple) {

	if ( (actTuple.key == keyRotLeft) && (actTuple.event == evntIncrement) ) {
		_TtrafoMax.increment();
	}
	if ( (actTuple.key == keyRotLeft) && (actTuple.event == evntDecrement) ) {
		_TtrafoMax.decrement();
	}
	if ( (actTuple.key == keyRotRight) && (actTuple.event == evntIncrement) ) {
		_TendstufeMax.increment();
	}
	if ( (actTuple.key == keyRotRight) && (actTuple.event == evntDecrement) ) {
		_TendstufeMax.decrement();
	}
}

void NonVolatileData::incrementStrtMemoryEnum(StrtMemoryEnum& in) {
	switch(in) {
	case strtNone:
		in = strtMem1;
		break;
	case strtMem1:
		in = strtMem2;
		break;
	case strtMem2:
		in = strtNone;
		break;
	}
}

void NonVolatileData::decrementStrtMemoryEnum(StrtMemoryEnum& in) {
	switch(in) {
	case strtNone:
		in = strtMem2;
		break;
	case strtMem1:
		in = strtNone;
		break;
	case strtMem2:
		in = strtMem1;
		break;
	}
}

void NonVolatileData::initValues() {
	bool result = _eeprom.initialRead();

	if (result == true) {
		initCalibVals();
		initMemVals();
		initStartVals(); // must be called at last
	} else {
		writeAllDataUnchecked();
	}
}

void NonVolatileData::initStartVals() {
	encodeNButtons::StrtMemoryEnum strtMemory;
	bool isPowActiveStart;

	bool result =
			_eeprom.readStartVals(strtMemory, isPowActiveStart);

	if (result == true) {
		_strtMemory = strtMemory;
		_PowActiveStart = isPowActiveStart;
	}
}

void NonVolatileData::initCalibVals(void) {
	int32_t Rshunt = 0;
	uint8_t TtrafoMax = 0;
	uint8_t TendstMax =0;

	bool result =
			_eeprom.readCalibVals(Rshunt, TtrafoMax, TendstMax);
	if (result == true) {
		_Rshunt.set(Rshunt);
		_TtrafoMax.set(static_cast<int32_t>(TtrafoMax));
		_TendstufeMax.set(static_cast<int32_t>(TendstMax));
	}
}

void NonVolatileData::initMemVals(void) {
	int32_t Usoll1 = 0;
	int32_t Isoll1 = 0;
	int32_t Usoll2 = 0;
	int32_t Isoll2 = 0;
	encodeNButtons::InSourceEnum 	inSource1;
	encodeNButtons::InSourceEnum 	inSource2;

	bool result =
			_eeprom.readMemVals(Usoll1, Isoll1, inSource1, Usoll2, Isoll2, inSource2);

	if (result == true) {
		_UsollMem1.set(Usoll1);
		_IsollMem1.set(Isoll1);
		_InSourceMem1 = inSource1;
		_UsollMem2.set(Usoll2);
		_IsollMem2.set(Isoll2);
		_InSourceMem2 = inSource2;
	}
}

void NonVolatileData::storeMemVals(void) {
	bool result = _eeprom.writeMemVals(
			_UsollMem1.get(), _IsollMem1.get(), _InSourceMem1,
			_UsollMem2.get(), _IsollMem2.get(), _InSourceMem2);

	if (result == false) {
		writeAllDataUnchecked();
	}
}

void NonVolatileData::storeCalibVals(void) {
	bool result = _eeprom.writeCalibVals(
			_Rshunt.get(), _TtrafoMax.get(), _TendstufeMax.get());

	if (result == false) {
		writeAllDataUnchecked();
	}
}

void NonVolatileData::storeStartVals(void){
	bool result = _eeprom.writeStartVals(_strtMemory, _PowActiveStart);

	if (result == false) {
		writeAllDataUnchecked();
	}
}

void NonVolatileData::writeAllDataUnchecked() {
	_eeprom.writeMemVals(
			_UsollMem1.get(), _IsollMem1.get(), _InSourceMem1,
			_UsollMem2.get(), _IsollMem2.get(), _InSourceMem2);

	_eeprom.writeCalibVals(
			_Rshunt.get(), _TtrafoMax.get(), _TendstufeMax.get());

	_eeprom.writeStartVals(_strtMemory, _PowActiveStart);
}

cLine::ExecResult NonVolatileData::executeCommand(uint32_t hashCode) {

	// zero means, no command to process, EMPTY_COMLINE_CRC means return was pressed
	// with an empty line
	if(hashCode == 0) {
		return cLine::exNone;
	} if (hashCode == cLine::EMPTY_COMLINE_CRC) {
		return cLine::exEmptyCom;
	}
	tx_printf("Got hashCode: %lu\n", hashCode);

	if(hashCode == 23668487) { // e2dumpstate HashCode=23668487
		txPrintfImm("e2dumpstate: ");
		uint16_t nextDataAddress = _eeprom.getEepromDevice().getNextDataAddress();
		uint32_t freeDataSpace = _eeprom.getEepromDevice().getFreeDataSpace();
		uint8_t numOfJournalEntries = _eeprom.getEepromDevice().getNumOfJournalEntries();
		uint16_t freeJournalEntries = _eeprom.getEepromDevice().getFreeJournalEntries();
		txPrintfImm("\nnextDataAddress: %i\nfreeDataSpace: %i\nnumOfJournalEntries: %i\nfreeJournalEntries %i\n",
				nextDataAddress, freeDataSpace, numOfJournalEntries, freeJournalEntries );
		return  cLine::exSuccess;
	}
	if(hashCode == 2165209579) { // e2dumpjournal HashCode=2165209579
		tx_printf("e2dumpjournal: ");
		eeprom::Eeprom_93C86::JournalEntryType je;
		uint8_t numOfJe = _eeprom.getEepromDevice().getNumOfJournalEntries();
		txPrintfImm("Found %i journal entries.\n", numOfJe);
		for(uint8_t i=0; i < numOfJe; i++) {
			bool result = _eeprom.getEepromDevice().readJournalEntry(i, je);
			if (result == false) {
				break;
			}
			txPrintfImm( "%i. entryID: %i / startAddress: %i / size: %i / crc: %i\n",
					i, je.entryID, je.startAddress, je.size, je.crc);
		}
		return  cLine::exSuccess;
	}
	if(hashCode == 1749811747) { // e2dumpjournalmap HashCode=1749811747
		txPrintfImm("e2dumpjournalmap\n");
		eeprom::Eeprom_93C86::JournalEntryMap jmap =
				_eeprom.getEepromDevice().getJournalEntryMap();

		for (uint8_t i=0; i <= static_cast<uint8_t>(eeprom::ValueID::VALUE_ID_LAST); i++) {
			eeprom::Eeprom_93C86::JournalEntryType je =
					jmap.get(static_cast<eeprom::ValueID>(i) );
			txPrintfImm("entryID: %i / startAddress: %i / size: %i / crc: %i\n",
					je.entryID, je.startAddress, je.size, je.crc);
		}
		return  cLine::exSuccess;
	}
	if(hashCode == 333689048) { // e2writedefault HashCode=333689048
		tx_printf("e2writedefault: ");
		bool result1 = _eeprom.writeStartVals(_strtMemory, _PowActiveStart);
		bool result2 = _eeprom.writeCalibVals(
				_Rshunt.get(), _TtrafoMax.get(), _TendstufeMax.get());
		bool result3 = _eeprom.writeMemVals(
				_UsollMem1.get(), _IsollMem1.get(), _InSourceMem1,
				_UsollMem2.get(), _IsollMem2.get(), _InSourceMem2);
		if (result1 && result2 && result3){
			tx_printf("successs\n");
		} else {
			txPrintfImm("start: %i / calib: %i / mem: %i\n",
					result1, result2, result3);
		}
		return  cLine::exSuccess;
	}
	if(hashCode == 909876832) { // e2erase HashCode=909876832
		tx_printf("e2erase: ");
		bool result = _eeprom.cleanEeprom();
		if(result == false) {
			tx_printf("failed\n");
		} else {
			tx_printf("success\n");
		}
		return  cLine::exSuccess;
	}
	if(hashCode == 249225350) { // e2init HashCode=249225350
		tx_printf("e2init: ");
		bool result = _eeprom.initialRead();
		if(result == false) {
			tx_printf("failed\n");
		} else {
			tx_printf("success\n");
		}
		return  cLine::exSuccess;
	}
	if(hashCode == 1120287783) { // e2dumpcalib HashCode=1120287783
		tx_printf("e2dumpcalib: ");

		int32_t Rshunt = 0;
		uint8_t TtrafoMax = 0;
		uint8_t TendstMax =0;

		bool result =
				_eeprom.readCalibVals(Rshunt, TtrafoMax, TendstMax);
		if (result == true) {
			tx_printf("\n");
			tx_printf("Rshunt: %lu\n", Rshunt);
			tx_printf("TtrafoMax: %lu\n", TtrafoMax);
			tx_printf("TendstMax: %lu\n", TendstMax);
		}
		else
			tx_printf("false\n");

		return  cLine::exSuccess;
	}
	if(hashCode == 2496122676) { // e2dumpmem HashCode=2496122676
		tx_printf("e2dumpmem:");

		int32_t Usoll1 = 0;
		int32_t Isoll1 = 0;
		int32_t Usoll2 = 0;
		int32_t Isoll2 = 0;
		encodeNButtons::InSourceEnum 	inSource1;
		encodeNButtons::InSourceEnum 	inSource2;

		bool result =
				_eeprom.readMemVals(Usoll1, Isoll1, inSource1, Usoll2, Isoll2, inSource2);

		if (result == true ){
			tx_printf("\n");
			tx_printf("Usoll1: %lu \n", Usoll1);
			tx_printf("Isoll1: %lu \n", Isoll1);
			tx_printf("inSource1: %i \n", inSource1);

			tx_printf("Usoll2: %lu \n", Usoll2);
			tx_printf("Isoll2: %lu \n", Isoll2);
			tx_printf("inSource1: %i \n", inSource1);
		}
		else
			tx_printf("false\n");

		return  cLine::exSuccess;
	}

	if(hashCode == 4176346198) {	 // e2dumpstart HashCode=4176346198
		tx_printf("e2dumpstart: ");

		encodeNButtons::StrtMemoryEnum strtMemory;
		bool isPowActiveStart;

		bool result =
				_eeprom.readStartVals(strtMemory, isPowActiveStart);

		if (result == true) {
			tx_printf("\n");
			tx_printf("strtMemory: %i\n", strtMemory);
			tx_printf("isPowActiveStart: %i\n", isPowActiveStart);
		}
		else
			tx_printf("false\n");

		return  cLine::exSuccess;
	}

	if(hashCode == 3509638897) { // help HashCode=3509638897
		txPrintfImm("help: \n");
		txPrintfImm("e2dumpstart\n");
		txPrintfImm("e2dumpmem\n");
		txPrintfImm("e2dumpcalib\n");
		txPrintfImm("e2init\n");
		txPrintfImm("e2erase\n");
		txPrintfImm("e2writedefault\n");
		txPrintfImm("e2dumpjournalmap\n");
		txPrintfImm("e2dumpjournal\n");
		txPrintfImm("e2dumpstate\n");
		return  cLine::exSuccess;
	}

	return  cLine::exUnknown;
}

} /* namespace encodeNButtons */
