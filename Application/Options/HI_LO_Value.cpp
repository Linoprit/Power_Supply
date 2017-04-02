/*
 * HI_LO_Value.cpp
 *
 *  Created on: 29.03.2017
 *      Author: harald
 */

#include <Options/HI_LO_Value.h>
#include <string.h>
#include "Devices/Rotary_Encoder/Rotary_Encoder.h"
#include "Instances/Common.h"



HI_LO_Value::HI_LO_Value ()
{
  value	= automatic;
}

HI_LO_Value::~HI_LO_Value () { }


uint8_t HI_LO_Value::getValue(void)
{
  return value;
}

HI_LO_Value::Options_enum HI_LO_Value::getEnum(void)
{
  return (Options_enum) value;
}

void HI_LO_Value::toString(char* buff, uint8_t len)
{
  switch (value)
  {
	case high:
	  strncpy(buff, "high", len);
	  break;

	case low:
	  strncpy(buff, "low ", len);
	  break;

	case automatic:
	  strncpy(buff, "auto", len);
	  break;
  }
}

void HI_LO_Value::hook_in()
{
  SoftwareEvents::hookIn(this, SoftwareEvents::rotenc_increment);
  SoftwareEvents::hookIn(this, SoftwareEvents::rotenc_decrement);
}

void HI_LO_Value::hook_off()
{
  SoftwareEvents::hookOff(this, SoftwareEvents::rotenc_increment);
  SoftwareEvents::hookOff(this, SoftwareEvents::rotenc_decrement);
}


void HI_LO_Value::software_event_callback(
	SoftwareEvents::Event_Names_enum event_name)
{
  Rotary_Encoder::last_key_enum last_key =
	  Common::get_rotary_encoder()->get_last_key();

  if ( (last_key == ENCODER) &&
	  (event_name == SoftwareEvents::rotenc_decrement) )
	{
	  if (value >= automatic)
		return;
	  else
		value++;
	}

  if ( (last_key == ENCODER) &&
	  (event_name == SoftwareEvents::rotenc_increment) )
	{
	  if (value <= high)
		return;
	  else
		value--;
	}
}

