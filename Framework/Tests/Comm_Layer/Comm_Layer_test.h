/*
 * Comm_Layer_test.h
 *
 *  Created on: 22.12.2016
 *      Author: harald
 */

#ifndef TESTS_COMM_LAYER_COMM_LAYER_TEST_H_
#define TESTS_COMM_LAYER_COMM_LAYER_TEST_H_

#include "Instances/Common.h"




class Comm_Layer_test
{
public:
  Comm_Layer_test ();
  virtual
  ~Comm_Layer_test ();

  void loop();
  void clearTextbuffer();


private:
  Comm_Layer*		comm_layer;
  char *textbuffer;
  int8_t textbuffer_len;
  PCD8544_graphics*	LCD;


};

#endif /* TESTS_COMM_LAYER_COMM_LAYER_TEST_H_ */
