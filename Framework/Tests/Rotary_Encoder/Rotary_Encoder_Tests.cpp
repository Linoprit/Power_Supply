/*
 * Rotary_Encoder_Tests.cpp
 *
 *  Created on: 02.01.2017
 *      Author: harald
 */

#include <Tests/Rotary_Encoder/Rotary_Encoder_Tests.h>
#include "main.h"
#include "Instances/Common.h"
#include "libraries/HelpersLib.h"


Rotary_Encoder_Tests::Rotary_Encoder_Tests ()
{
  socket  = new Rotary_Encoder_socket(get_I2C_1());
  encoder = new Rotary_Encoder(socket);

  SoftwareEvents::hookIn(this, SoftwareEvents::btn_released);
  SoftwareEvents::hookIn(this, SoftwareEvents::btn_pressed);
  SoftwareEvents::hookIn(this, SoftwareEvents::btn_held);

  SoftwareEvents::hookIn(this, SoftwareEvents::rotenc_increment);
  SoftwareEvents::hookIn(this, SoftwareEvents::rotenc_decrement);

  // must be initialised in framework
  LCD		  = Common::get_LCD_grfx();
  LCD->switch_font(FONT_5x8);

  textbuffer_len = 17;
  textbuffer = (char*)malloc(textbuffer_len * sizeof (char));

  left_value  = 0;
  right_value = 0;
}

Rotary_Encoder_Tests::~Rotary_Encoder_Tests ()
{ }

void Rotary_Encoder_Tests::loop()
{
  uint32_t old_ticks = 0;
  SoftwareEvents* 	sw_events 	= Common::get_sw_events();


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
  clearTextbuffer(textbuffer_len);

  if(event_name == SoftwareEvents::btn_released)
	strncpy(&textbuffer[0], (const char*) "button_released", 15);

  if(event_name == SoftwareEvents::btn_pressed)
	strncpy(&textbuffer[0], (const char*) "button_pressed", 14);

  if(event_name == SoftwareEvents::btn_held)
	strncpy(&textbuffer[0], (const char*) "button_held", 11);

  if(event_name == SoftwareEvents::rotenc_increment)
	strncpy(&textbuffer[0], (const char*) "rotenc_inc", 10);

  if(event_name == SoftwareEvents::rotenc_decrement)
	strncpy(&textbuffer[0], (const char*) "rotenc_dec", 10);

  LCD->write_string(0, LCD->conv_line_2_y_pix(1), textbuffer);


  clearTextbuffer(textbuffer_len);
  Rotary_Encoder::last_key_enum last_key = encoder->get_last_key();

  if (last_key == Rotary_Encoder::rotenc_left)
	strncpy(&textbuffer[0], (const char*) "rotenc_left", 11);

  if (last_key == Rotary_Encoder::rotenc_right)
	strncpy(&textbuffer[0], (const char*) "rotenc_right", 12);

  if (last_key == Rotary_Encoder::btn_left)
	strncpy(&textbuffer[0], (const char*) "btn_left", 8);

  if (last_key == Rotary_Encoder::btn_right)
	strncpy(&textbuffer[0], (const char*) "btn_right", 9);

  if (last_key == Rotary_Encoder::btn_3)
	strncpy(&textbuffer[0], (const char*) "btn_3", 5);

  if (last_key == Rotary_Encoder::btn_4)
	strncpy(&textbuffer[0], (const char*) "btn_4", 5);

  LCD->write_string(0, LCD->conv_line_2_y_pix(2), textbuffer);


  clearTextbuffer(textbuffer_len);
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

  HelpersLib::value2char(&textbuffer[0], 3, 0, left_value);
  HelpersLib::value2char(&textbuffer[4], 3, 0, right_value);
  LCD->write_string(0, LCD->conv_line_2_y_pix(3), textbuffer);


  LCD->display();
}


void Rotary_Encoder_Tests::clearTextbuffer(uint8_t len)
{
  for (uint8_t i=0; i < len; i++)
	textbuffer[i] = ' ';
  textbuffer[textbuffer_len-1] = '\0';
}
