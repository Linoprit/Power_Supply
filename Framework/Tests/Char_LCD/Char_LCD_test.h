/*
 * Char_LCD_test.h
 *
 *  Created on: 09.01.2017
 *      Author: harald
 */

#ifndef TESTS_CHAR_LCD_CHAR_LCD_TEST_H_
#define TESTS_CHAR_LCD_CHAR_LCD_TEST_H_

#include "Devices/Char_LCD/Char_LCD.h"



class Char_LCD_test
{
public:
  Char_LCD_test ();
  virtual ~Char_LCD_test ();

  void loop();


private:

  Char_LCD* LCD;
  buffer_lines_type* buffer_lines;
  const uint16_t TIME_BETWEEN_TEST_MS = 3000;


  void do_LCD_print(void);

};

#endif /* TESTS_CHAR_LCD_CHAR_LCD_TEST_H_ */
