/*
 * Rotary_Encoder_State_Machine.h
 *
 *  Created on: 06.01.2017
 *      Author: harald
 */

#ifndef DEVICES_ROTARY_ENCODER_ALPS_ENCODER_H_
#define DEVICES_ROTARY_ENCODER_ALPS_ENCODER_H_

#include "Rotary_Encoder_Types.h"

namespace rotaryEncoder {

class ALPS_Encoder
{
public:
  ALPS_Encoder ();
  virtual
  ~ALPS_Encoder ();

  KeyEvent_enum cycle(uint8_t rotary_val);

private:
  enum state_enum
  { off, uz1, gz1 };

  state_enum state;
  uint8_t old_rotary_val;

};

}

#endif /* DEVICES_ROTARY_ENCODER_ALPS_ENCODER_H_ */
