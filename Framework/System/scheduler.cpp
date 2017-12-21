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


#include "Tests/Call_Tests.h"


uint32_t scheduler::old_tick = 0;


// C interface
void scheduler_cycle(void) 	{ scheduler::cycle(); }
void scheduler_init(void)	{ scheduler::init(); }

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

  SoftwareEvents* 	sw_events 	= Common::get_sw_events();
  //Comm_Layer*		comm		= Common::get_comm_layer();
  Rotary_Encoder*	rot_enc		= Common::get_rotary_encoder();
  OMI_coordinator*  omi			= Common::get_omi_coord();

  // TODO use Measurement classes
  ADC_socket*		adc3_socket = Common::get_adc_socket_Uall();



  // TODO move to common
  static DAC_socket* dac_socket = new DAC_socket();


  sw_events->loop(); // work off events


  // 1ms cycle
  if (tick != old_tick)
	{
	  adc3_socket->cycle_1ms();

	  //HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);


	}

  // 5ms cycle
  if ( ((tick % 5) == 0) && (tick != old_tick) )
	{
	  rot_enc->cycle();
	  omi->loop_5ms();


	}

  // 50ms cycle
  if ( ((tick % 50) == 0) && (tick != old_tick) )
	{
	  // call display and button-action update
	  omi->loop_50ms();


	  // TODO remove
	  dac_socket->set(20);

	}

  if ( ((tick % 256) == 0) && (tick != old_tick) )
	{

	  adc3_socket->read();

	}


  old_tick = tick;
}
