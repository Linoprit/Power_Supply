/*
 * scheduler.cpp
 *
 *  Created on: 09.12.2016
 *      Author: harald
 */

#include "scheduler.h"
#include "stm32f3xx_hal.h"
#include "SoftwareEvents.h"
//#include "../Devices/PCD8544_LCD/PCD8544_graphics.h"
//#include "../Devices/keypad/Keypad.h"
#include "../Devices/Comm_Layer/Comm_Layer.h"
#include "../Devices/Comm_Layer/Messages_Base.h"
#include "../Instances/Common.h"

#include "Tests/Call_Tests.h"


uint32_t scheduler::old_Tick = 0;


// C interface
void scheduler_cycle(void) 	{ scheduler::cycle(); }
void scheduler_init(void)	{ scheduler::init(); }

scheduler::scheduler (void)  { }
scheduler::~scheduler (void) { }


 void scheduler::init(void)
{
  Common::initialize_devices();

  // TODO remove Test-Call
  Call_Tests *tests = new Call_Tests();
  tests->cycle();
}


void scheduler::cycle(void)
{
  uint32_t tick = HAL_GetTick();

  SoftwareEvents* 	sw_events 	= Common::get_sw_events();
  Comm_Layer*		comm		= Common::get_comm_layer();


  // TODO remove?
  //sw_events->checkTicks(tick);
  sw_events->loop();

/*
  // 1ms cycle
  if (tick != old_Tick)
	{
	  HAL_GPIO_TogglePin(LD10_GPIO_Port, LD10_Pin);
	  HAL_GPIO_TogglePin(LD9_GPIO_Port, LD9_Pin);
	}

  // 10ms cycle
  if ((tick % 10) == 0)
	{
	  HAL_GPIO_TogglePin(LD8_GPIO_Port, LD8_Pin);
	  HAL_GPIO_TogglePin(LD7_GPIO_Port, LD7_Pin);
	  HAL_GPIO_TogglePin(LD6_GPIO_Port, LD6_Pin);
	}

  // 100ms cycle
  if ((tick % 100) == 0)
	{
	  HAL_GPIO_TogglePin(LD5_GPIO_Port, LD5_Pin);
	  HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
	  HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
	}
*/

  old_Tick = tick;
}
