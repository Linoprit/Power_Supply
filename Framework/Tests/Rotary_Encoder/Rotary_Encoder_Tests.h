/*
 * Rotary_Encoder_Tests.h
 *
 *  Created on: 02.01.2017
 *      Author: harald
 */

#ifndef TESTS_ROTARY_ENCODER_ROTARY_ENCODER_TESTS_H_
#define TESTS_ROTARY_ENCODER_ROTARY_ENCODER_TESTS_H_

#include "Devices/Rotary_Encoder/Rotary_Encoder_socket.h"
#include "Devices/Rotary_Encoder/Rotary_Encoder.h"
#include "System/SoftwareEvents.h"
#include "Devices/Char_LCD/Char_LCD.h"


class Rotary_Encoder_Tests: SoftwareEvents_base
{
public:
  Rotary_Encoder_Tests ();
  virtual
  ~Rotary_Encoder_Tests ();

  void loop(void);

  void software_event_callback(
  	  SoftwareEvents::Event_Names_enum event_name);


private:
  Rotary_Encoder_socket* socket  = NULL;
  Rotary_Encoder*		 encoder = NULL;

  Char_LCD* LCD = NULL;


  uint8_t left_value, right_value;
};

#endif /* TESTS_ROTARY_ENCODER_ROTARY_ENCODER_TESTS_H_ */
