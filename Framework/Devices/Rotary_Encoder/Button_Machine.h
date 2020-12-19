/*
 * Button_State_Machine.h
 *
 *  Created on: 06.01.2017
 *      Author: harald
 */

#ifndef DEVICES_ROTARY_ENCODER_BUTTON_MACHINE_H_
#define DEVICES_ROTARY_ENCODER_BUTTON_MACHINE_H_

#include <stdint.h>
#include "Rotary_Encoder_Types.h"


namespace rotaryEncoder {

constexpr uint8_t  debounce_ticks  = 20;
constexpr uint16_t btn_held_ticks  = 1000;


class Button_Machine
{
public:
	Button_Machine ();
	virtual
	~Button_Machine ();


	KeyEvent_enum cycle(uint8_t Button_val);


private:
	enum state_enum
	{ off, on, pressed, held};

	state_enum state;
	uint32_t old_ticks;


};

} /* namespace rotaryEncoder */

#endif /* DEVICES_ROTARY_ENCODER_BUTTON_MACHINE_H_ */
