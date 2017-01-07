/*
 * Rotary_Encoder.cpp
 *
 *  Created on: 31.12.2016
 *      Author: harald
 */

#include <Devices/Rotary_Encoder/Rotary_Encoder.h>
#include "stm32f3xx_hal.h"


Rotary_Encoder::Rotary_Encoder (Rotary_Encoder_socket* socket_in)
{
  socket = socket_in;

  enc_left 		= new Rotary_Encoder_State_Machine();
  enc_right  	= new Rotary_Encoder_State_Machine();
  button_left	= new Button_State_Machine();
  button_right	= new Button_State_Machine();
  button_3		= new Button_State_Machine();
  button_4		= new Button_State_Machine();

  button_val_left  = 0;
  button_val_right = 0;
  button_val_3     = 0;
  button_val_4     = 0;

  last_key 		   = none;
}

Rotary_Encoder::~Rotary_Encoder ()
{ }

void Rotary_Encoder::cycle(void)
{
  uint8_t input = 0;

  while(socket->rx_ringbuffer()->HasData())
	{
	  input = socket->rx_ringbuffer()->Read();

	  button_val_left 	= (input & mask_button_1)  	>> 2;
	  button_val_right 	= (input & mask_button_2)  	>> 5;
	  button_val_3 		= (input & mask_button_3)  	>> 6;
	  button_val_4 		= (input & mask_button_4)  	>> 7;

	  if (check_cycle((input & mask_encoder_1), rotenc_left))
		return;

	  if (check_cycle(((input & mask_encoder_2) >> 3), rotenc_right))
		return;

	  if (check_cycle(button_val_left, btn_left))
		return;

	  if (check_cycle(button_val_right, btn_right))
		return;

	  if (check_cycle(button_val_3, btn_3))
		return;

	  if (check_cycle(button_val_4, btn_4))
		return;

	  return;
	}

  if (check_cycle(button_val_left, btn_left))
	return;

  if (check_cycle(button_val_right, btn_right))
	return;

  if (check_cycle(button_val_3, btn_3))
	return;

  if (check_cycle(button_val_4, btn_4))
	return;

}


bool Rotary_Encoder::check_cycle(
	uint8_t masked_value,
	last_key_enum key)
{
  SoftwareEvents::Event_Names_enum
  last_event = SoftwareEvents::None;

  if(key == rotenc_left)
	last_event = enc_left->cycle(masked_value);

  if(key == rotenc_right)
	last_event = enc_right->cycle(masked_value);

  if (key == btn_left)
	last_event = button_left->cycle(masked_value);

  if (key == btn_right)
	last_event = button_right->cycle(masked_value);

  if (key == btn_3)
	last_event = button_3->cycle(masked_value);

  if (key == btn_4)
	last_event = button_3->cycle(masked_value);


  if (last_event > SoftwareEvents::None)
	{
	  SoftwareEvents::sendEvent(last_event);
	  last_key = key;
	  return true;
	}

  return false;
}

Rotary_Encoder::last_key_enum Rotary_Encoder::get_last_key(void)
{
  return last_key;
}
