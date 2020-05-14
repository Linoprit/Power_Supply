/*
 * VolatileData.h
 *
 *  Created on: 03.05.2020
 *      Author: harald
 */

#ifndef APPLICATION_ENCODENBUTTONS_VOLATILEDATA_H_
#define APPLICATION_ENCODENBUTTONS_VOLATILEDATA_H_

#include <Types/Typedefs.h>
#include <Types/ExtFloat.h>

namespace encodeNButtons {

enum InSourceEnum {
	inHigh, inLow, inAuto
};

//constexpr float U_SOLL_MAX = 30.0f; // max output Voltage [V]
//constexpr float I_SOLL_MAX = 6.0f;  // max output Current [A]


class VolatileData {
public:
	VolatileData();
	virtual ~VolatileData();

	InSourceEnum getInSource() const {
		return _InSource;
	}

	void setInSource(InSourceEnum inSource) {
		_InSource = inSource;
	}

	Adjustment_0p0& getIsoll() {
		return _Isoll;
	}

/*	void setIsoll(const Adjustment_0p0& isoll) {
		_Isoll = isoll;
	}*/

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

	Adjustment_0p0& getUsoll() {
		return _Usoll;
	}

	bool isUsollFineFlag() const {
		return _UsollFineFlag;
	}

	/*void setUsollFineFlag(bool usollFineFlag) {
		_UsollFineFlag = usollFineFlag;
	}*/

private:
	Adjustment_0p0	_Usoll;
	Adjustment_0p0	_Isoll;
	InSourceEnum		_InSource;
	bool						_PowActive;
	bool						_UsollFineFlag;
	bool						_IsollFineFlag;
};

} /* namespace encodeNButtons */

#endif /* APPLICATION_ENCODENBUTTONS_VOLATILEDATA_H_ */
