/*
 * I_soll.cpp
 *
 *  Created on: 20.03.2017
 *      Author: harald
 */

#include "Devices/Rotary_Encoder/Rotary_Encoder.h"
#include "Instances/Common.h"
#include "libraries/HelpersLib.h"
#include <math.h>
#include <Options/IU_Value.h>


IU_Value::IU_Value (ValueConfig value_config_in)
{
  value 		= 0.0f;
  fine_active 	= false;

  value_config = value_config_in;
}

IU_Value::~IU_Value () { }


float IU_Value::getValue(void)
{
  return value;
}

void  IU_Value::toString(char* buff, uint8_t len)
{
  long int tmp_val =
	  (long int)
	  (value * ((float) pow(10.0, value_config.decimal_place)));

 HelpersLib::value2char( buff, len, value_config.decimal_place, tmp_val);
}

void  IU_Value::hook_in()
{
  SoftwareEvents::hookIn(this, SoftwareEvents::rotenc_increment);
  SoftwareEvents::hookIn(this, SoftwareEvents::rotenc_decrement);
  SoftwareEvents::hookIn(this, SoftwareEvents::btn_pressed);
}

void  IU_Value::hook_off()
{
  SoftwareEvents::hookOff(this, SoftwareEvents::rotenc_increment);
  SoftwareEvents::hookOff(this, SoftwareEvents::rotenc_decrement);
  SoftwareEvents::hookOff(this, SoftwareEvents::btn_pressed);
}

void IU_Value::software_event_callback(
	SoftwareEvents::Event_Names_enum event_name)
{
  Rotary_Encoder::last_key_enum last_key =
	  Common::get_rotary_encoder()->get_last_key();

  if ( (last_key == value_config.rotary_encoder) &&
	  (event_name == SoftwareEvents::rotenc_increment) )
	{
	  if(fine_active == true)
		{
		  // avoid precision issues
		  value = value * 10;
		  value++;
		  value = value / 10;
		}
	  else
		{
		  // truncate fractional part
		  value = (float) ((int) value); // cast to int and back
		  value++;
		}
	}

  if ( (last_key == value_config.rotary_encoder) &&
	  (event_name == SoftwareEvents::rotenc_decrement) )
	{
	  if(fine_active == true)
		{
		  // avoid precision issues
		  value = value * 10;
		  value--;
		  value = value / 10;
		}
	  else
		{
		  // truncate fractional part
		  int tmp_val = (int) value;
		  if ((value - (float) tmp_val) < 0.1f)
			value = value - 1.0f;
		  else
			value = (float) tmp_val;
		}
	}

  // saturate
  if (value > (float) value_config.max_val)
	value = (float) value_config.max_val;
  if (value < (float) value_config.min_val)
	value = (float) value_config.min_val;

  if ( (last_key == value_config.encoder_button) &&
	  (event_name == SoftwareEvents::btn_pressed) )
	{
	  if (fine_active == true)
		fine_active = false;
	  else
		fine_active = true;
	}
}



bool IU_Value::is_fine_active(void)
{
  return fine_active;
}


