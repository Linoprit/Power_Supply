/*
 * U_soll.h
 *
 *  Created on: 20.03.2017
 *      Author: harald
 */

#ifndef OPTIONS_IU_VALUE_H_
#define OPTIONS_IU_VALUE_H_


#include "System/SoftwareEvents.h"
#include "Devices/Rotary_Encoder/Rotary_Encoder.h"
#include "Basetypes/Value_template.h"


#define DECIMAL_PLACE 1 // Nachkommastellen


class IU_Value: Value_template<float>, SoftwareEvents_base
{
public:
  typedef struct
  {
    uint8_t 						decimal_place;  // Nachkommastellen
    Rotary_Encoder::last_key_enum	rotary_encoder; // encoder re oder li
    Rotary_Encoder::last_key_enum	encoder_button;	// button re oder li
    uint8_t							min_val;		// minimum
    uint8_t							max_val;		// maximum
  } ValueConfig;

  IU_Value (ValueConfig value_config_in);
  virtual ~IU_Value ();

  float getValue(void);
  void  toString(char* buff, uint8_t len);
  void  hook_in();
  void  hook_off();

  void software_event_callback(SoftwareEvents::Event_Names_enum event_name);

  bool is_fine_active(void);

private:
  float 		value;
  bool			fine_active;
  ValueConfig 	value_config;

};

#endif /* OPTIONS_U_SOLL_H_ */
