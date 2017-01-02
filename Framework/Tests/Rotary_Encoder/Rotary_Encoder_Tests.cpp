/*
 * Rotary_Encoder_Tests.cpp
 *
 *  Created on: 02.01.2017
 *      Author: harald
 */

#include <Tests/Rotary_Encoder/Rotary_Encoder_Tests.h>
#include "main.h"
#include "Instances/Common.h"


Rotary_Encoder_Tests::Rotary_Encoder_Tests ()
{
  socket  = new Rotary_Encoder_socket(get_I2C_1());
  encoder = new Rotary_Encoder(socket);
}

Rotary_Encoder_Tests::~Rotary_Encoder_Tests ()
{ }

void Rotary_Encoder_Tests::loop()
{
  uint32_t old_ticks = 0;

  while(1)
	{
	  if (Common::get_tick() - old_ticks > 10)
		{
		  encoder->cycle();

		  old_ticks = Common::get_tick();
		}
	}


}
