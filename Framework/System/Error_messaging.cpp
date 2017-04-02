/*
 * Error_messaging.cpp
 *
 *  Created on: 19.03.2017
 *      Author: harald
 */

#include <System/Error_messaging.h>
#include <errno.h>

#ifdef TRACE

Comm_Layer_socket*	Error_messaging::debug_comm		= NULL;


Error_messaging::Error_messaging  () { }
Error_messaging::~Error_messaging () { }


void Error_messaging::init_debug_comm(void)
{
  debug_comm = new Comm_Layer_socket( get_UART_2() );
}

Comm_Layer_socket* Error_messaging::get_debug_comm(void)
{
  return debug_comm;
}

size_t Error_messaging::write(const char* buf, size_t nbyte)
{
  while (!debug_comm->send_many_bytes((uint8_t*) buf, (uint8_t) nbyte))
	{	}

  return nbyte;
}

ssize_t trace_write (const char* buf __attribute__((unused)),
	     size_t nbyte __attribute__((unused)))
{
  return Error_messaging::write(buf, nbyte);
}


// workaround for sprintf TODO remove
/*caddr_t _sbrk(int incr)
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
}*/

#endif  /* TRACE */
