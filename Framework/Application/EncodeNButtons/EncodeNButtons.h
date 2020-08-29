/*
 * EncodeNButtons.h
 *
 *  Created on: 26.04.2020
 *      Author: harald
 */

#ifndef APPLICATION_ENCODENBUTTONS_ENCODENBUTTONS_H_
#define APPLICATION_ENCODENBUTTONS_ENCODENBUTTONS_H_

#include <Application/EncodeNButtons/ScreenState.h>
#include <Devices/Rotary_Encoder/MemoryButtons.h>
#include <Devices/Rotary_Encoder/Rotary_Encoder_socket.h>
#include <Devices/Rotary_Encoder/Rotary_Encoder.h>
#include "NonVolatileData.h"
#include "VolatileData.h"


namespace encodeNButtons {
using namespace rotaryEncoder;

class EncodeNButtons {
public:
	EncodeNButtons();
	virtual ~EncodeNButtons() {};

	void init(void);
	static EncodeNButtons& instance(void);
	void cycle(EventQueue_type& eventQueue, AdditionalButtons  additionalButtons);

	const NonVolatileData 	getNvData(void) 		  		const	{ return _nonVolatileData; 	};
	const VolatileData	  	getVolData(void)		  		const	{ return _volatileData; 		};
	const ScreenState		getScreenState(void) 			const	{ return _screenState;			};
	NonVolatileData& 		getNvData(void) 		  				{ return _nonVolatileData; 	};
	VolatileData&	   		getVolData(void)		  				{ return _volatileData; 		};
	ScreenState&		 	getScreenState(void) 					{ return _screenState;			};

private:
	Rotary_Encoder_socket  	_socket;
	Rotary_Encoder 			_rotEnc;
	MemoryButtons			_memoryButtons;
	ScreenState				_screenState;
	NonVolatileData			_nonVolatileData;
	VolatileData			_volatileData;

};

} /* namespace encodeNButtons */

#endif /* APPLICATION_ENCODENBUTTONS_ENCODENBUTTONS_H_ */
