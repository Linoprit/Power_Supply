/*
 * Comm_layer_socket.cpp
 *
 *  Created on: 25.05.2016
 *      Author: harald
 */

#include "Comm_Layer_socket.h"
#include "Instances/callbacks.h"
#include "stm32f3xx_hal.h"
#include <string.h>

//#include "gpio.h"


Comm_Layer_socket::Comm_Layer_socket (UART_HandleTypeDef *huart)
{
  this->usart 	= huart;
  rx_ringbuffer = new simpleRingbuffer(simpleRingbuffer_len);

  uart_rx_buffer 	= new uint8_t[uart_rx_buffer_len];
  memset(uart_rx_buffer, RX_PAD_CHAR, uart_rx_buffer_len);

  // same as HAL_UART_RxCpltCallback
  uart1_callback_set((ISR_callback*) this);

  HAL_UART_Receive_DMA(this->usart, uart_rx_buffer, uart_rx_buffer_len);

  timer = new SoftwareTimer(TimerDuration, this, SoftwareEvents::Tic_1ms);

  // use this timer for socket-testing
  //timer = new SoftwareTimer(20, this, SoftwareEvents::Tic_100ms);

}

Comm_Layer_socket::~Comm_Layer_socket ()
{
}

bool Comm_Layer_socket::send_byte(uint8_t byte)
{
  return send_many_bytes(&byte, 1);
}

bool Comm_Layer_socket::send_many_bytes(uint8_t *ptr_to_data, uint8_t len)
{
  HAL_UART_StateTypeDef uart_status = HAL_UART_GetState(usart);

  if ( (uart_status != HAL_UART_STATE_READY) &&
	  (uart_status != HAL_UART_STATE_BUSY_RX) )
	return ERROR;

  HAL_UART_Transmit_DMA(usart, ptr_to_data, len);
  return SUCCESS;
}

bool Comm_Layer_socket::is_TX_pending(void)
{
  HAL_UART_StateTypeDef usart_status = HAL_UART_GetState(usart);

  return
	  ( (usart_status == HAL_UART_STATE_BUSY_TX) ||
		  (usart_status == HAL_UART_STATE_BUSY_TX_RX) );
}

simpleRingbuffer* Comm_Layer_socket::get_rx_ringbuffer()
{
  return rx_ringbuffer;
}


void Comm_Layer_socket::ISR_callback_fcn (void)
{
  uint8_t i=0;

  // copy uart-buffer to ringbuffer
  for (i = 0; i < uart_rx_buffer_len; i++)
	{
	  rx_ringbuffer->Write(uart_rx_buffer[i]);
	}

  // Be sure, no start sequence remains in the buffer
  memset(uart_rx_buffer, RX_PAD_CHAR, uart_rx_buffer_len);

  timer->restart();
}

void Comm_Layer_socket::timer_hit_callback(void)
{
  uint8_t i;


  for (i = 0; i < uart_rx_buffer_len; i++)
	{
	  if (uart_rx_buffer[i] != RX_PAD_CHAR)
		break;

	  if (i == uart_rx_buffer_len - 1)
		return;
	}

  if (is_TX_pending())
	{
	  timer->restart();
	  return;
	}

  // We copy the whole rx-buffer to the ringbuffer, so we
  // can be sure to catch the tail of the last incomming
  // uart-message.
  // The Comm_Layer will skip over the other bytes, because
  // there is no start sequence in. Remember: we filled the
  // rx-buffer with EOT.
  for(i = 0; i < uart_rx_buffer_len; i++)
	{
	  rx_ringbuffer->Write(uart_rx_buffer[i]);
	}

  // Be sure, no start sequence remains in the buffer
  memset(uart_rx_buffer, RX_PAD_CHAR, uart_rx_buffer_len);

}

UART_HandleTypeDef*	Comm_Layer_socket::get_handle(void)
{
  return usart;
}
