/*
 * Rotary_Encoder_State_Machine.h
 *
 *  Created on: 06.01.2017
 *      Author: harald
 */

#ifndef DEVICES_ROTARY_ENCODER_ROTARY_ENCODER_STATE_MACHINE_H_
#define DEVICES_ROTARY_ENCODER_ROTARY_ENCODER_STATE_MACHINE_H_

#include "System/SoftwareEvents.h"



class Rotary_Encoder_State_Machine
{
public:
  Rotary_Encoder_State_Machine ();
  virtual
  ~Rotary_Encoder_State_Machine ();

  SoftwareEvents::Event_Names_enum cycle(uint8_t rotary_val);

private:
  enum state_enum
  { off, uz1, gz1 };

  state_enum state;
  uint8_t old_rotary_val;

};

#endif /* DEVICES_ROTARY_ENCODER_ROTARY_ENCODER_STATE_MACHINE_H_ */
