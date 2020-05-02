/*
 * Rotary_Encoder.cpp
 *
 *  Created on: 31.12.2016
 *      Author: harald
 */

#include <Devices/Rotary_Encoder/Rotary_Encoder.h>
#include "stm32f3xx_hal.h"

namespace rotaryEncoder {

Rotary_Encoder::Rotary_Encoder()
{
	_socket 			= NULL;

	button_val_left  = 0;
	button_val_right = 0;
	button_val_3     = 0;
	button_val_4     = 0;

}

Rotary_Encoder::Rotary_Encoder (Rotary_Encoder_socket* socket_in)
{
	_socket = socket_in;

	button_val_left  = 0;
	button_val_right = 0;
	button_val_3     = 0;
	button_val_4     = 0;

}


Rotary_Encoder::~Rotary_Encoder ()
{ }


void Rotary_Encoder::cycle(EventQueue_type& eventQueue)
{
	uint8_t input = 0;

	while(!_socket->get_rx_queue()->isEmpty())
	{
		input = _socket->get_rx_queue()->dequeue();

		button_val_left 	= (uint8_t)((input & mask_button_1) >> offset_button_1);
		button_val_right 	= (uint8_t)((input & mask_button_2) >> offset_button_2);
		button_val_3 			= (uint8_t)((input & mask_button_3) >> offset_button_3);
		button_val_4 			= (uint8_t)((input & mask_button_4) >> offset_button_4);

		check_cycle(
				(uint8_t)((input & mask_encoder_1)>> offset_encoder_1),
				rotenc_left,
				eventQueue);
		check_cycle(
				(uint8_t)((input & mask_encoder_2) >> offset_encoder_2),
				rotenc_right,
				eventQueue);
		check_cycle(button_val_left, 	btn_left,		eventQueue);
		check_cycle(button_val_right, btn_right, 	eventQueue);
		check_cycle(button_val_3, 		btn_setup, 			eventQueue);
		check_cycle(button_val_4, 		btn_onoff, 			eventQueue);
	}

	check_cycle(button_val_left, 		btn_left, 	eventQueue);
	check_cycle(button_val_right, 	btn_right, 	eventQueue);
	check_cycle(button_val_3, 			btn_setup, 			eventQueue);
	check_cycle(button_val_4, 			btn_onoff, 			eventQueue);
}


void Rotary_Encoder::check_cycle(
		uint8_t 					masked_value,
		Key_enum	 				key,
		EventQueue_type& 	eventQueue)
{
	KeyEvent_enum last_event = evnt_none;

	if(key == rotenc_left)
		last_event = enc_left.cycle(masked_value);

	if(key == rotenc_right)
		last_event = enc_right.cycle(masked_value);

	if (key == btn_left)
		last_event = button_left.cycle(masked_value);

	if (key == btn_right)
		last_event = button_right.cycle(masked_value);

	if (key == btn_setup)
		last_event = button_3.cycle(masked_value);

	if (key == btn_onoff)
		last_event = button_4.cycle(masked_value);

	if (last_event > evnt_none) {
		eventQueue.enqueue(KeyEventTuple(key, last_event));
	}

}



}
