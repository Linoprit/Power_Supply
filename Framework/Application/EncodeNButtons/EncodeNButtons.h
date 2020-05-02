/*
 * EncodeNButtons.h
 *
 *  Created on: 26.04.2020
 *      Author: harald
 */

#ifndef APPLICATION_ENCODENBUTTONS_ENCODENBUTTONS_H_
#define APPLICATION_ENCODENBUTTONS_ENCODENBUTTONS_H_

#include <Devices/Rotary_Encoder/MemoryButtons.h>
#include <Devices/Rotary_Encoder/Rotary_Encoder_socket.h>
#include <Devices/Rotary_Encoder/Rotary_Encoder.h>


namespace encodeNButtons {
using namespace rotaryEncoder;


class EncodeNButtons {
public:
	EncodeNButtons();
	virtual ~EncodeNButtons() {};

	void init(void);
	static EncodeNButtons& instance(void);
	void cycle(
			EventQueue_type& eventQueue, AdditionalButtons  additionalButtons);

private:
	Rotary_Encoder_socket  _socket;
	Rotary_Encoder 			   _rotEnc;
	MemoryButtons					 _memoryButtons;
};

} /* namespace encodeNButtons */

#endif /* APPLICATION_ENCODENBUTTONS_ENCODENBUTTONS_H_ */
