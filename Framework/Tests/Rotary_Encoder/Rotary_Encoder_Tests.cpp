/*
 * Rotary_Encoder_Tests.cpp
 *
 *  Created on: 02.01.2017
 *      Author: harald
 */

#include <Tests/Rotary_Encoder/Rotary_Encoder_Tests.h>
#include <string.h>
#include "main.h"
#include "Instances/Common.h"
#include "libraries/HelpersLib.h"



Rotary_Encoder_Tests::Rotary_Encoder_Tests ()
{
  // Test standalone
  //socket  = new Rotary_Encoder_socket(get_I2C_1());
  //encoder = new Rotary_Encoder(socket);
  // Test after init from framework
  encoder = Common::get_rotary_encoder();

  SoftwareEvents::hookIn(this, SoftwareEvents::btn_released);
  SoftwareEvents::hookIn(this, SoftwareEvents::btn_pressed);
  SoftwareEvents::hookIn(this, SoftwareEvents::btn_held);

  SoftwareEvents::hookIn(this, SoftwareEvents::rotenc_increment);
  SoftwareEvents::hookIn(this, SoftwareEvents::rotenc_decrement);

  // LCD must be initialised in framework
  LCD = Common::get_char_lcd();
  LCD->clear();

  left_value  = 0;
  right_value = 0;
}

Rotary_Encoder_Tests::~Rotary_Encoder_Tests ()
{ }

void Rotary_Encoder_Tests::loop()
{
  uint32_t old_ticks = 0;
  SoftwareEvents* 	sw_events 	= Common::get_sw_events();

  // for measurement                 0123456789012345
  strncpy(&LCD->buffer_lines[0][0], "Rot_Enc Test...", 15);
  strncpy(&LCD->buffer_lines[1][0], "Operate buttons.", 16);
  LCD->display();

  while(1)
	{
	  if (Common::get_tick() - old_ticks > 1)
		{
		  encoder->cycle();
		  old_ticks = Common::get_tick();
		}

	  sw_events->loop();
	}

}

void Rotary_Encoder_Tests::software_event_callback(
	SoftwareEvents::Event_Names_enum event_name)
{
  // for measurement                 0123456789012345


  //HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);



  LCD->clear();

  if(event_name == SoftwareEvents::btn_released)
	strncpy(&LCD->buffer_lines[0][8], (const char*) "released", 8);

  if(event_name == SoftwareEvents::btn_pressed)
	strncpy(&LCD->buffer_lines[0][8], (const char*) "pressed", 7);

  if(event_name == SoftwareEvents::btn_held)
	strncpy(&LCD->buffer_lines[0][8], (const char*) "held", 4);

  if(event_name == SoftwareEvents::rotenc_increment)
	strncpy(&LCD->buffer_lines[0][8], (const char*) "inc", 3);

  if(event_name == SoftwareEvents::rotenc_decrement)
	strncpy(&LCD->buffer_lines[0][8], (const char*) "dec", 3);


  Rotary_Encoder::last_key_enum last_key = encoder->get_last_key();

  if (last_key == Rotary_Encoder::rotenc_left)
	strncpy(&LCD->buffer_lines[0][0], (const char*) "enc_lft", 7);

  if (last_key == Rotary_Encoder::rotenc_right)
	strncpy(&LCD->buffer_lines[0][0], (const char*) "enc_rgt", 7);

  if (last_key == Rotary_Encoder::btn_left)
	strncpy(&LCD->buffer_lines[0][0], (const char*) "btn_lft", 7);

  if (last_key == Rotary_Encoder::btn_right)
	strncpy(&LCD->buffer_lines[0][0], (const char*) "btn_rgt", 7);

  if (last_key == Rotary_Encoder::btn_3)
	strncpy(&LCD->buffer_lines[0][0], (const char*) "btn_3", 5);

  if (last_key == Rotary_Encoder::btn_4)
	strncpy(&LCD->buffer_lines[0][0], (const char*) "btn_4", 5);

  if( (event_name == SoftwareEvents::rotenc_increment) &&
	  (last_key == Rotary_Encoder::rotenc_left))
	{
	  if (left_value < UINT8_MAX)
		left_value++;
	}

  if( (event_name == SoftwareEvents::rotenc_decrement) &&
	  (last_key == Rotary_Encoder::rotenc_left))
	{
	  if (left_value > 0)
		left_value--;
	}

  if( (event_name == SoftwareEvents::rotenc_increment) &&
	  (last_key == Rotary_Encoder::rotenc_right))
	{
	  if (right_value < UINT8_MAX)
		right_value++;
	}

  if( (event_name == SoftwareEvents::rotenc_decrement) &&
	  (last_key == Rotary_Encoder::rotenc_right))
	{
	  if (right_value > 0)
		right_value--;
	}

  HelpersLib::value2char(&LCD->buffer_lines[1][0], 3, 0, left_value);
  HelpersLib::value2char(&LCD->buffer_lines[1][4], 3, 0, right_value);

  LCD->display();
}

