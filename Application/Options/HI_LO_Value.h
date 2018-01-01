/*
 * HI_LO_Value.h
 *
 *  Created on: 29.03.2017
 *      Author: harald
 */

#ifndef OPTIONS_HI_LO_VALUE_H_
#define OPTIONS_HI_LO_VALUE_H_


#include <Interfaces/Option_Option_Value_template.h>
#include "System/SoftwareEvents.h"


#define ENCODER Rotary_Encoder::rotenc_right


class HI_LO_Value: Option_Value_template<uint8_t>, SoftwareEvents_base
{
public:
  enum Options_enum { high = 0, low = 1, automatic = 2};



  HI_LO_Value ();
  virtual
  ~HI_LO_Value ();

  uint8_t 	getValue(void);
  void 		toString(char* buff, uint8_t len);
  void 		hook_in();
  void 		hook_off();
  Options_enum getEnum(void);

  void software_event_callback(SoftwareEvents::Event_Names_enum event_name);

private:
  uint8_t value;


};

#endif /* OPTIONS_HI_LO_VALUE_H_ */
