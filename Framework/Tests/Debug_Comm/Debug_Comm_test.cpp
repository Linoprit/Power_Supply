/*
 * Debug_Comm_test.cpp
 *
 *  Created on: 08.03.2017
 *      Author: harald
 */

#include <Tests/Debug_Comm/Debug_Comm_test.h>


Debug_Comm_test::Debug_Comm_test ()
{
  debug_comm = Common::get_debug_comm();
  sw_events  = Common::get_sw_events();
}


Debug_Comm_test::~Debug_Comm_test () { }

void Debug_Comm_test::loop()
{
  static  uint32_t 	old_counter = 0;
  uint32_t 	act_counter         = 0;

  int 		k = 34;
  char 		s[100];


  while (1)
	{
	  sw_events->loop();

	  act_counter = Common::get_tick();
	  if (act_counter - old_counter  > 100)
		{
		  int size = sprintf(s, (const char*) "Hi from MCU! %d \n", k);

		  debug_comm->send_many_bytes((uint8_t*) &s[0], 22);
		  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);


		  old_counter = act_counter;
		}
	}
}


caddr_t _sbrk(int incr)
{
  extern char _ebss; // Defined by the linker
  static char *heap_end;
  char *prev_heap_end;

  if (heap_end == 0)
  {
    heap_end = &_ebss;
  }

  prev_heap_end = heap_end;
  char * stack = (char*) __get_MSP();

  if (heap_end + incr > stack)
  {
    errno = ENOMEM;
    return (caddr_t) -1;
  }

  heap_end += incr;
  return (caddr_t) prev_heap_end;
}
