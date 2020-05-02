/*
 * Rotary_Encoder.h
 *
 *  Created on: 31.12.2016
 *      Author: harald
 */

#ifndef DEVICES_ROTARY_ENCODER_ROTARY_ENCODER_H_
#define DEVICES_ROTARY_ENCODER_ROTARY_ENCODER_H_

#include "Rotary_Encoder_Types.h"
#include "Button_Machine.h"
#include "ALPS_Encoder.h"
#include "Grayhill_Encoder.h"
#include "Rotary_Encoder_socket.h"


//#define ALPS
#define GRAYHILL

namespace rotaryEncoder {

// Alps Board
#ifdef ALPS
constexpr uint8_t mask_button_1  = 0b00000100;
constexpr uint8_t mask_encoder_1 = 0b00000011;
constexpr uint8_t mask_button_2  = 0b00100000;
constexpr uint8_t mask_encoder_2 = 0b00011000;
constexpr uint8_t mask_button_3  = 0b01000000;
constexpr uint8_t mask_button_4  = 0b10000000;

constexpr uint8_t offset_button_1  = 2;
constexpr uint8_t offset_encoder_1 = 0;
constexpr uint8_t offset_button_2  = 5;
constexpr uint8_t offset_encoder_2 = 3;
constexpr uint8_t offset_button_3  = 6;
constexpr uint8_t offset_button_4  = 7;
#endif

// Grayhill Board
#ifdef GRAYHILL
constexpr uint8_t mask_button_2  = 0b00010000;
constexpr uint8_t mask_encoder_2 = 0b00000011;
constexpr uint8_t mask_button_1  = 0b00100000;
constexpr uint8_t mask_encoder_1 = 0b00001100;
constexpr uint8_t mask_button_3  = 0b01000000;
constexpr uint8_t mask_button_4  = 0b10000000;

constexpr uint8_t offset_button_2  = 4;
constexpr uint8_t offset_encoder_2 = 0;
constexpr uint8_t offset_button_1  = 5;
constexpr uint8_t offset_encoder_1 = 2;
constexpr uint8_t offset_button_3  = 6;
constexpr uint8_t offset_button_4  = 7;
#endif


class Rotary_Encoder
{
public:


	Rotary_Encoder();
	Rotary_Encoder (Rotary_Encoder_socket* socket_in);
	virtual
	~Rotary_Encoder ();

	void cycle(EventQueue_type& eventQueue);


private:
	Rotary_Encoder_socket* 		_socket;
#ifdef ALPS // why not using base-class construct?
	ALPS_Encoder	  enc_left;
	ALPS_Encoder   enc_right;
#endif
#ifdef GRAYHILL
	Grayhill_Encoder  enc_left;
	Grayhill_Encoder  enc_right;
#endif
	Button_Machine			button_left;
	Button_Machine			button_right;
	Button_Machine			button_3;
	Button_Machine			button_4;

	uint8_t button_val_left;
	uint8_t button_val_right;
	uint8_t button_val_3;
	uint8_t button_val_4;

	void check_cycle(
			uint8_t 					masked_value,
			Key_enum 		key,
			EventQueue_type& 	eventQueue);
};

}

#endif /* DEVICES_ROTARY_ENCODER_ROTARY_ENCODER_H_ */
