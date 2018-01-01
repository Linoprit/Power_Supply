/*
 * Option.h
 *
 *  Created on: 20.03.2017
 *      Author: harald
 */

#ifndef INTERFACES_OPTION_OPTION_VALUE_TEMPLATE_H_
#define INTERFACES_OPTION_OPTION_VALUE_TEMPLATE_H_

#include <stdint.h>

template<typename T>
class Option_Value_template
{
public:
  Option_Value_template() { };
  virtual ~Option_Value_template() { };

  virtual T 	getValue(void) 	= 0;
  virtual void 	toString(char* buff, uint8_t len) = 0;
  virtual void 	hook_in() 		= 0;
  virtual void 	hook_off() 		= 0;
  //virtual T    first() 		= 0;
  //virtual T    last() 		= 0;


};

#endif /* INTERFACES_OPTION_OPTION_VALUE_TEMPLATE_H_ */
