/*
 * Comm_layer_socket.h
 *
 *  Created on: 25.05.2016
 *      Author: harald
 */

#ifndef MACHINE_COMM_LAYER_COMM_LAYER_SOCKET_H_
#define MACHINE_COMM_LAYER_COMM_LAYER_SOCKET_H_

#include "System/SoftwareTimer.h"
#include <stdint.h>
#include <Sockets/RX_TX_interface.h>
#include "libraries/simpleRingbuffer.h"
#include "Instances/callbacks.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_usart.h"



class Comm_Layer_socket:
	Rx_Tx_interface,
	ISR_callback,
	SoftwareTimer_base
{
public:
	  Comm_Layer_socket (UART_HandleTypeDef *huart);
	  virtual
	  ~Comm_Layer_socket ();

	  bool 					send_byte(uint8_t byte);
	  bool 					send_many_bytes(uint8_t *ptr_to_data, uint8_t len);
	  bool 					is_TX_pending(void);
	  simpleRingbuffer* 	get_rx_ringbuffer(void);
	  UART_HandleTypeDef*	get_handle(void);


	  // callback usart receive complete
	  void callback_fcn (void);

	  // timer, flush rx-buffer if expired
	  void timer_hit_callback(void);


private:
	  SoftwareTimer 		*timer;
	  uint8_t 				*uart_rx_buffer;
	  UART_HandleTypeDef 	*usart;
	  simpleRingbuffer 		*rx_ringbuffer;


	  // we use Timer event Tic_1ms!!
	  const uint8_t TimerDuration        = 5;   // 5 = 5ms
	  const uint8_t	uart_rx_buffer_len 	 = 10;
	  const uint8_t RX_PAD_CHAR			 = 4; // 4 = EOT
	  const uint8_t simpleRingbuffer_len = 24;

};

#endif /* MACHINE_COMM_LAYER_COMM_LAYER_SOCKET_H_ */
