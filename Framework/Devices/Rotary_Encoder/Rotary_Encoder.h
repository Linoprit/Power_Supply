/*
 * Rotary_Encoder.h
 *
 *  Created on: 31.12.2016
 *      Author: harald
 */

#ifndef DEVICES_ROTARY_ENCODER_ROTARY_ENCODER_H_
#define DEVICES_ROTARY_ENCODER_ROTARY_ENCODER_H_

#include <Devices/Rotary_Encoder/Button_Machine.h>
#include "ALPS_Encoder.h"
#include "Grayhill_Encoder.h"
#include "Rotary_Encoder_socket.h"


//#define ALPS
#define GRAYHILL


class Rotary_Encoder
{
public:
  enum last_key_enum {
	none,
	rotenc_left, rotenc_right,
	btn_left, btn_right, btn_3, btn_4
  };

  Rotary_Encoder (Rotary_Encoder_socket* socket_in);
  virtual
  ~Rotary_Encoder ();


  void cycle(void);
  last_key_enum get_last_key(void);

  // Alps Board
#ifdef ALPS
  const uint8_t mask_button_1  = 0b00000100;
  const uint8_t mask_encoder_1 = 0b00000011;
  const uint8_t mask_button_2  = 0b00100000;
  const uint8_t mask_encoder_2 = 0b00011000;
  const uint8_t mask_button_3  = 0b01000000;
  const uint8_t mask_button_4  = 0b10000000;

  const uint8_t offset_button_1  = 2;
  const uint8_t offset_encoder_1 = 0;
  const uint8_t offset_button_2  = 5;
  const uint8_t offset_encoder_2 = 3;
  const uint8_t offset_button_3  = 6;
  const uint8_t offset_button_4  = 7;
#endif

  // Grayhill Board
#ifdef GRAYHILL
  const uint8_t mask_button_2  = 0b00010000;
  const uint8_t mask_encoder_2 = 0b00000011;
  const uint8_t mask_button_1  = 0b00100000;
  const uint8_t mask_encoder_1 = 0b00001100;
  const uint8_t mask_button_3  = 0b01000000;
  const uint8_t mask_button_4  = 0b10000000;

  const uint8_t offset_button_2  = 4;
  const uint8_t offset_encoder_2 = 0;
  const uint8_t offset_button_1  = 5;
  const uint8_t offset_encoder_1 = 2;
  const uint8_t offset_button_3  = 6;
  const uint8_t offset_button_4  = 7;
#endif


private:
  Rotary_Encoder_socket* 		socket;
#ifdef ALPS
  ALPS_Encoder*	  enc_left;
  ALPS_Encoder*   enc_right;
#endif
#ifdef GRAYHILL
  Grayhill_Encoder*  enc_left;
  Grayhill_Encoder*  enc_right;
#endif
  Button_Machine*			button_left;
  Button_Machine*			button_right;
  Button_Machine*			button_3;
  Button_Machine*			button_4;

  uint8_t button_val_left;
  uint8_t button_val_right;
  uint8_t button_val_3;
  uint8_t button_val_4;

  last_key_enum last_key;

  bool check_cycle(uint8_t masked_value, last_key_enum key);
};

#endif /* DEVICES_ROTARY_ENCODER_ROTARY_ENCODER_H_ */
