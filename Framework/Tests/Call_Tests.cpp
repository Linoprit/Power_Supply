/*
 * Call_Tests.cpp
 *
 *  Created on: 17.12.2016
 *      Author: harald
 */

#include "Call_Tests.h"

#include "PCD8544/PCD8544_Tests.h"
#include "Sw_Timer/Sw_Timer_Test.h"
#include "Keypad/Keypadtest.h"
#include "Comm_Layer/Comm_Layer_socket_test.h"


Call_Tests::Call_Tests ()
{
}

Call_Tests::~Call_Tests() {}

void Call_Tests::cycle()
{
  //PCD8544_Tests *lcd_test = new PCD8544_Tests();
  //lcd_test->Do_Display_Tests();

  // Software-Timer and Events Tests
  //Sw_Timer_Test *sw_timer_test 	= new Sw_Timer_Test();
  //sw_timer_test->Do_Timer_Test();

  //Keypadtest *keypadtest 		= new Keypadtest();
  //keypadtest->Do_keypadtest();

   //Comm_Layer_socket_test* comm_layer_socket_test =
   //	  new Comm_Layer_socket_test();
   //comm_layer_socket_test->loop();






}
