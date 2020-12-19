/*
 *  extFloat.h
 *
 *  Created on: 02.04.2020
 *      Author: harald
 */

#ifndef INTERFACES_VALUE_PT1_FILTERED_H_
#define INTERFACES_VALUE_PT1_FILTERED_H_

#include <stdint.h>
#include <libraries/HelpersLib.h>
#include <math.h>


class ExtFloat
{

public:
	ExtFloat(float value = 0.0f){
		_value = value;
	};

  virtual ~ExtFloat () { };

  int32_t toInt(const uint8_t decimal_places){
    float factor = pow(10.0f, static_cast<float>(decimal_places) );
    return static_cast<int32_t>( round( get() * factor ) );
  };

  void fromInt(const int32_t intValue, const uint8_t decimal_places) {
  	float factor = pow(10.0f, static_cast<float>(decimal_places) );
  	set(static_cast<float>(intValue) / factor );
  }

  float get(void){
    return _value;
  };

  void set(const float floatValue) {
  	_value = floatValue;
  }

  void toString(char* buffer, const uint8_t buffLen, const uint8_t decimal_places){
    HelpersLib::value2char(buffer, buffLen, decimal_places, toInt(decimal_places));
  };

protected:
  float _value;
};

#endif /* INTERFACES_VALUE_PT1_FILTERED_H_ */
