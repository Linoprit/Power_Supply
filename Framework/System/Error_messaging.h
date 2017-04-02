/*
 * Error_messaging.h
 *
 *  Created on: 19.03.2017
 *      Author: harald
 */

#ifndef SYSTEM_ERROR_MESSAGING_H_
#define SYSTEM_ERROR_MESSAGING_H_

#include "stm32f3xx_hal.h"
#include "Devices/Comm_Layer/Comm_Layer_socket.h"


extern "C" UART_HandleTypeDef* get_UART_2(void);


#ifdef TRACE

class Error_messaging
{
public:
  Error_messaging ();
  virtual ~Error_messaging ();

  static void init_debug_comm(void);
  static Comm_Layer_socket* get_debug_comm(void);
  static size_t  write(const char* buf, size_t nbyte);


private:
  static Comm_Layer_socket*	debug_comm;
};

// C-interface
#ifdef __cplusplus
extern "C" {
#endif

//caddr_t _sbrk(int incr);

ssize_t trace_write (const char* buf __attribute__((unused)),
	     size_t nbyte __attribute__((unused)));

#ifdef __cplusplus
 }
#endif

#define WRITE_TRACE(msg, len)	Error_messaging::write(msg, len)
#else
#define WRITE_TRACE(msg, len)
#endif /* TRACE */



#endif /* SYSTEM_ERROR_MESSAGING_H_ */
