/*
 * NonVolatileData.h
 *
 *  Created on: 03.05.2020
 *      Author: harald
 */

#ifndef APPLICATION_ENCODENBUTTONS_NONVOLATILEDATA_H_
#define APPLICATION_ENCODENBUTTONS_NONVOLATILEDATA_H_

//#include <Types/Adjustment_0p0.h>
#include "ScreenStates.h"
#include <Devices/Rotary_Encoder/Rotary_Encoder_Types.h>
#include "VolatileData.h"
#include <Types/Fixed.h>
#include <Types/Adjustment_0p0.h>
#include <Types/Adjustment_0pxx.h>
#include <Types/Typedefs.h>

namespace encodeNButtons {
using namespace rotaryEncoder;

enum StrtMemoryEnum {
	strtNone, strtMem1, strtMem2
};



class NonVolatileData {
public:
	NonVolatileData();
	virtual ~NonVolatileData() {};

	void update(
			KeyEventTuple 	actTuple,
			ScreenStateEnum actScreen,
			VolatileData		volatileData);

	void incrementStrtMemoryEnum(StrtMemoryEnum& in);
	void decrementStrtMemoryEnum(StrtMemoryEnum& in);
	InSourceEnum getInSourceMem1() const;
	InSourceEnum getInSourceMem2() const;
	const ExtFloat& getIsollMem1() const;
	const ExtFloat& getIsollMem2() const;
	bool isPowActiveStart() const;
	void setPowActiveStart(bool powActiveStart);
	Adjustment_0pxx& getRshunt();
	bool isRshuntFineFlag() const;
	void setRshuntFineFlag(bool rshuntFineFlag);
	StrtMemoryEnum getStrtMemory() const;
	const Adjustment_0p0& getTendstufeMax() const;
	const Adjustment_0p0& getTtrafoMax() const;
	const ExtFloat& getUsollMem1() const;
	const ExtFloat& getUsollMem2() const;


private:
	StrtMemoryEnum  _strtMemory;

	Adjustment_0pxx _Rshunt;
	Adjustment_0p0	_TtrafoMax;
	Adjustment_0p0	_TendstufeMax;

	Fixed						_UsollMem1;
	Fixed						_IsollMem1;
	InSourceEnum		_InSourceMem1;
	Fixed   				_UsollMem2;
	Fixed   				_IsollMem2;
	InSourceEnum		_InSourceMem2;

	bool						_RshuntFineFlag;
	bool					  _PowActiveStart;

	// ToDo
	//ExtFloat			_PowOnDynamic;
	//ExtFloat			_DisplDynamic;

	void keyMemory1(VolatileData	volatileData, KeyEvent_enum	event);
	void keyMemory2(VolatileData	volatileData, KeyEvent_enum	event);
	void updateStrtValues(KeyEventTuple actTuple);
	void updateCalib(VolatileData	volatileData, KeyEventTuple actTuple);
	void updateTgrenz(KeyEventTuple actTuple);


};

} /* namespace encodeNButtons */

#endif /* APPLICATION_ENCODENBUTTONS_NONVOLATILEDATA_H_ */
