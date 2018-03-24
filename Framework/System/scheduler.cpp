/*
 * scheduler.cpp
 *
 *  Created on: 09.12.2016
 *      Author: harald
 */

#include "scheduler.h"
#include "stm32f3xx_hal.h"
#include "SoftwareEvents.h"
#include "../Devices/Comm_Layer/Comm_Layer.h"
#include "../Devices/Comm_Layer/Messages_Base.h"
#include "../Instances/Common.h"
#include "../Devices/Rotary_Encoder/Rotary_Encoder.h"
#include "../Application/Controller/DAC_socket.h"

// TODO remove later
#include "System/Error_messaging.h"
#include "libraries/HelpersLib.h"
uint8_t scheduler::text_buf[TEXT_BUF_LEN];



#include "Tests/Call_Tests.h"


uint32_t scheduler::old_tick = 0;
Value_PT1_filtered* scheduler::Uist_pt1 = new Value_PT1_filtered(0.005f);
Value_PT1_filtered* scheduler::Iist_pt1 = new Value_PT1_filtered(0.005f);
Value_PT1_filtered* scheduler::Uin_pt1  = new Value_PT1_filtered(0.005f);
Value_PT1_filtered* scheduler::Temp_pt1 = new Value_PT1_filtered(0.001f);



// C interface
void scheduler_cycle(void) 	{ scheduler::cycle(); }
void scheduler_init(void)	{ scheduler::init();  }

scheduler::scheduler (void) { }
scheduler::~scheduler (void) { }


void scheduler::init(void)
{
  Common::initialize_devices();

#ifdef DO_TESTS
  Call_Tests *tests = new Call_Tests();
  tests->cycle_1ms();
#endif /* DO_TESTS */
}


void scheduler::cycle(void)
{
  uint32_t tick = HAL_GetTick();

  Common::get_sw_events()->loop(); // work off events


  // 1ms cycle
  if (tick != old_tick)
	{
	  Common::get_U_sense()->cycle_1ms();
	  Common::get_U_sense_auto()->cycle_1ms();
	  Common::get_U_input()->cycle_1ms();

	  Common::get_I_raw()->cycle_1ms();
	//  Common::get_I_auto()->cycle_1ms();
	//  Common::get_Temperature()->cycle_1ms();

	  update_pt1_values();

	  Common::get_controller()->cycle_1ms();

	  // TODO remove
	  //HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

	}

  // 5ms cycle
  if ( ((tick % 5) == 0) && (tick != old_tick) )
	{
	  Common::get_rotary_encoder()->cycle();
	  Common::get_omi_coord()->loop_5ms();


	}

  // 50ms cycle
  if ( ((tick % 50) == 0) && (tick != old_tick) )
	{
	  // call display and button-action update
	  Common::get_omi_coord()->loop_50ms();




	  // TODO remove
	  //dac_socket->set(20);

	}

  if ( ((tick % 256) == 0) && (tick != old_tick) )
	{
	  dbg_push_values();




	}


  old_tick = tick;
}

void scheduler::update_pt1_values(void)
{
  if(Common::get_U_sense_auto()->is_overrange())
	Uist_pt1->cycle( Common::get_U_sense()->get_Value_float() );
  else
	Uist_pt1->cycle(Common::get_U_sense_auto()->get_Value_float());

  Uin_pt1->cycle( Common::get_U_input()->get_Value_float() );
  Temp_pt1->cycle( Common::get_Temperature()->get_Value_float() );

  if (Common::get_I_auto()->is_overrange())
	Iist_pt1->cycle( Common::get_I_raw()->get_Value_float() );
  else
	Iist_pt1->cycle( Common::get_I_auto()->get_Value_float() );
}



// TODO remove later
void scheduler::dbg_push_values(void)
{
  Measurement*		meas_U_sense		= Common::get_U_sense();
  Measurement*		meas_U_sense_auto   = Common::get_U_sense_auto();
  Measurement*		meas_U_input        = Common::get_U_input();
  Measurement*		meas_I_raw          = Common::get_I_raw();
  Measurement*		meas_I_auto         = Common::get_I_auto();
  Measurement*		meas_Temperature    = Common::get_Temperature();

  clear_text_buf(&text_buf[0], TEXT_BUF_LEN);

  static uint16_t j;
  HelpersLib::value2char((char*) &text_buf[0], 5, 0, (long int) j);
  Error_messaging::write((char*) &text_buf[0], 5);
  Error_messaging::write((char*) ": ", 2);
  j++;

  Error_messaging::write((char*) "Usns: ", 6);
  send_value( meas_U_sense->getValue_int(2) );

  Error_messaging::write((char*) "Uaut: ", 6);
  send_value( meas_U_sense_auto->getValue_int(2) );

  Error_messaging::write((char*) "UautRaw: ", 9);
  send_value( meas_U_sense_auto->getADC() );

  Error_messaging::write((char*) "G: ", 3);
  send_value( meas_U_sense_auto->get_gain() * 100 );

  Error_messaging::write((char*) "Upt1: ", 6);
  send_value( Uist_pt1->getValue_int(2) );

  Error_messaging::write((char*) "Uinp: ", 6);
  send_value( meas_U_input->getValue_int(2) );

 /* Error_messaging::write((char*) "Iraw: ", 6);
  send_value( meas_I_raw->getValue_int(2) );

  Error_messaging::write((char*) "Iaut: ", 6);
  send_value( meas_I_auto->getValue_int(2) );

  Error_messaging::write((char*) "G: ", 3);
  send_value( meas_I_auto->get_gain() * 100);

  Error_messaging::write((char*) "Temp: ", 6);
  send_value( meas_Temperature->getValue_int(2) );*/




  //Common::adc_socket_Iraw->print_values();
  //Common::adc_socket_Iamp->print_values();
  //Common::adc_socket_Temp->print_values();

  Error_messaging::write((char*) "\n", 1);
}

void scheduler::send_value(long int value)
{
  clear_text_buf(&text_buf[0], TEXT_BUF_LEN);
  HelpersLib::value2char((char*) &text_buf[0], TEXT_BUF_LEN, 2, value);
  Error_messaging::write((char*) &text_buf[0], TEXT_BUF_LEN);
  Error_messaging::write((char*) " ", 1);
}

void scheduler::clear_text_buf(uint8_t* text_buf_in, uint8_t len)
{
  for(int i=0; i<len; i++)
	{
	  *text_buf_in = (uint8_t) '\0';
	  text_buf_in++;
	}
}







