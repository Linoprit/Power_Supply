/*
 * VolatileData.h
 *
 *  Created on: 03.05.2020
 *      Author: harald
 */

#ifndef APPLICATION_ENCODENBUTTONS_VOLATILEDATA_H_
#define APPLICATION_ENCODENBUTTONS_VOLATILEDATA_H_

#include <Application/EncodeNButtons/ScreenState.h>
#include <Devices/Rotary_Encoder/Rotary_Encoder_Types.h>
#include <Types/Typedefs.h>
#include <Types/ExtFloat.h>
#include <Types/Adjustment_0p0.h>


namespace encodeNButtons {

class NonVolatileData;

enum InSourceEnum {
	inHigh, inLow, inAuto
};


class VolatileData {
public:
	VolatileData();
	virtual ~VolatileData() { };

	void update(
			KeyEventTuple 	actTuple,
			ScreenStateEnum actScreen,
			NonVolatileData& nonVolatileData);


	InSourceEnum getInSource() const {
		return _InSource;
	}

	void setInSource(InSourceEnum inSource) {
		_InSource = inSource;
	}

	Adjustment_0p0& getIsoll() {
		return _Isoll;
	}

	bool isIsollFineFlag() const {
		return _IsollFineFlag;
	}

	void setIsollFineFlag(bool isollFineFlag) {
		_IsollFineFlag = isollFineFlag;
	}

	bool isPowActive() const {
		return _PowActive;
	}

	void setPowActive(bool powActive) {
		_PowActive = powActive;
	}

	Adjustment_0p0& getUsoll(void) {
		return _Usoll;
	}

	bool isUsollFineFlag() const {
		return _UsollFineFlag;
	}

	bool isKeysLocked() const {
		return _KeysLocked;
	}

private:
	Adjustment_0p0	_Usoll;
	Adjustment_0p0	_Isoll;
	InSourceEnum		_InSource;
	bool						_PowActive;
	bool						_UsollFineFlag;
	bool						_IsollFineFlag;
	bool						_KeysLocked;
	KeyEvent_enum		_LastOnOffButtonEvent;

	void keyMemory1(NonVolatileData&	nonVolatileData, KeyEvent_enum	event);
	void keyMemory2(NonVolatileData&	nonVolatileData, KeyEvent_enum	event);
	void keyButtonOnOff(void);
	void updateValues  (KeyEventTuple actTuple);
	void updateUsource (KeyEventTuple actTuple);

};

} /* namespace encodeNButtons */

#endif /* APPLICATION_ENCODENBUTTONS_VOLATILEDATA_H_ */
