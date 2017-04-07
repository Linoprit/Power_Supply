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


uint32_t scheduler::old_Tick = 0;


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
  tests->cycle();
#endif /* DO_TESTS */
}


void scheduler::cycle(void)
{
  uint32_t tick = HAL_GetTick();

  SoftwareEvents* 	sw_events 	= Common::get_sw_events();
  Comm_Layer*		comm		= Common::get_comm_layer();
  Rotary_Encoder*	rot_enc		= Common::get_rotary_encoder();
  OMI_coordinator*  omi			= Common::get_omi_coord();

  // TODO move to common
  static DAC_socket* dac_socket = new DAC_socket();


  sw_events->loop(); // work off events



  // 1ms cycle
  if (tick != old_Tick)
	{
	  rot_enc->cycle();
	}

  // 10ms cycle
  if ((tick % 10) == 0)
	{

	}

  // 100ms cycle
  if ((tick % 100) == 0)
	{
	 // HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

	  // call OMI
	  omi->loop();


	  // TODO remove
	  dac_socket->set(20);
	}


  old_Tick = tick;
}
