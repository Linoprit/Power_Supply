/*
 * NonVolatileData.h
 *
 *  Created on: 03.05.2020
 *      Author: harald
 */

#ifndef APPLICATION_ENCODENBUTTONS_NONVOLATILEDATA_H_
#define APPLICATION_ENCODENBUTTONS_NONVOLATILEDATA_H_

//#include <Types/Adjustment_0p0.h>
#include <Application/EncodeNButtons/ScreenState.h>
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


	Adjustment_0pxx& getRshunt()  								{ return _Rshunt; 				};
	const Adjustment_0pxx getRshunt() 			const { return _Rshunt; 				};
	bool isRshuntFineFlag() 								const	{ return _RshuntFineFlag;	};
	StrtMemoryEnum getStrtMemory() 					const	{	return _strtMemory;			};
	Adjustment_0p0& getTendstufeMax() 						{ return _TendstufeMax;		};
	Adjustment_0p0& getTtrafoMax() 								{ return _TtrafoMax;			};
	const Adjustment_0p0 getTendstufeMax() 	const { return _TendstufeMax;		};
	const Adjustment_0p0 getTtrafoMax() 	 	const	{ return _TtrafoMax;			};
	bool isPowActiveStart() 								const	{	return _PowActiveStart;	};
	InSourceEnum getInSourceMem1() 					const	{ return _InSourceMem1; 	};
	InSourceEnum getInSourceMem2() 					const { return _InSourceMem2; 	};
	Fixed& getUsollMem1()  												{ return _UsollMem1;			};
	Fixed& getUsollMem2()  												{ return _UsollMem2;			};
	Fixed& getIsollMem1()  												{ return _IsollMem1;			};
	Fixed& getIsollMem2() 		 										{ return _IsollMem2;			};
	void setInSourceMem1(InSourceEnum in) 				{ _InSourceMem1 = in; 		};
	void setInSourceMem2(InSourceEnum in) 				{ _InSourceMem2 = in; 		};

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

	void updateStrtValues(KeyEventTuple actTuple);
	void updateCalib(VolatileData	volatileData, KeyEventTuple actTuple);
	void updateTgrenz(KeyEventTuple actTuple);
};

} /* namespace encodeNButtons */

#endif /* APPLICATION_ENCODENBUTTONS_NONVOLATILEDATA_H_ */
