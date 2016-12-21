/*
 * Nokia_3310_Tests.h
 *
 *  Created on: 30.09.2015
 *      Author: harald
 */

#ifndef DEVICES_PCD8544_LCD_TEST_NOKIA_3310_TESTS_H_
#define DEVICES_PCD8544_LCD_TEST_NOKIA_3310_TESTS_H_

#include "PCD8544_Tests.h"

#include "Devices/PCD8544_LCD/PCD8544_basis.h"
#include "Devices/PCD8544_LCD/PCD8544_graphics.h"


class PCD8544_Tests {
public:

  PCD8544_Tests();
  virtual
  ~PCD8544_Tests();

  void Do_Display_Tests(void);
  void write_char_map(void);
  void grfx_write_char_map(void);
  void show_text(void);
  void grfx_show_text(void);

private:
  PCD8544_graphics  *LCD_grfx;
  PCD8544_basis		*LCD_basis;

};




#endif /* DEVICES_PCD8544_LCD_TEST_NOKIA_3310_TESTS_H_ */
