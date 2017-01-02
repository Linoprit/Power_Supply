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


class Rotary_Encoder_Tests
{
public:
  Rotary_Encoder_Tests ();
  virtual
  ~Rotary_Encoder_Tests ();

  void loop(void);


private:
  Rotary_Encoder_socket* socket  = NULL;
  Rotary_Encoder*		 encoder = NULL;

};

#endif /* TESTS_ROTARY_ENCODER_ROTARY_ENCODER_TESTS_H_ */
