/*
 * Rotary_Encoder.h
 *
 *  Created on: 31.12.2016
 *      Author: harald
 */

#ifndef DEVICES_ROTARY_ENCODER_ROTARY_ENCODER_H_
#define DEVICES_ROTARY_ENCODER_ROTARY_ENCODER_H_

#include "Rotary_Encoder_socket.h"



class Rotary_Encoder
{
public:
  Rotary_Encoder (Rotary_Encoder_socket* socket_in);
  virtual
  ~Rotary_Encoder ();


  void cycle(void);


  const uint8_t mask_button_1  = 0b00000100;
  const uint8_t mask_encoder_1 = 0b00000011;
  const uint8_t mask_button_2  = 0b00100000;
  const uint8_t mask_encoder_2 = 0b00011000;
  const uint8_t mask_button_3  = 0b01000000;
  const uint8_t mask_button_4  = 0b10000000;


private:
  Rotary_Encoder_socket* socket;

};

#endif /* DEVICES_ROTARY_ENCODER_ROTARY_ENCODER_H_ */
