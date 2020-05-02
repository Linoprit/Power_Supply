/*
 * Comm_layer_socket.cpp
 *
 *  Created on: 25.05.2016
 *      Author: harald
 */


#include <Sockets/uart_socket.h>
#include <Instances/callbacks.h>
#include <Instances/OsHelpers.h>
#include <string.h>


#if USE_RTOS
/**
 * We need osTreadId to be passed as function pointer, because sockets
 * are initialized before the threads.
 */
uart_socket::uart_socket (UART_HandleTypeDef *huart,
		osThreadId* task_to_notify ):
		uart_socket(huart)
{
	this->task_to_notify = task_to_notify;
}
#else

uart_socket::uart_socket (UART_HandleTypeDef *huart)
{
	this->huart 	= huart;
	rx_queue = new SimpleQueue<uint8_t>(UART_RX_BUFF_LEN);

	uart_rx_buffer 	= new uint8_t[UART_RX_BUFF_LEN];
	memset(uart_rx_buffer, RX_PAD_CHAR, UART_RX_BUFF_LEN);

	uart_tx_buffer 	= new uint8_t[UART_TX_BUFF_LEN];
	memset(uart_tx_buffer, RX_PAD_CHAR, UART_TX_BUFF_LEN);

	__HAL_UART_ENABLE_IT(huart, UART_IT_IDLE); // @suppress("Field cannot be resolved")

	// same as HAL_UART_RxCpltCallback
	add_uart_callback(huart, (ISR_callback*) this);
	HAL_UART_Receive_DMA(this->huart, uart_rx_buffer, UART_RX_BUFF_LEN);
}
#endif


bool uart_socket::send_byte(uint8_t byte)
{
	return send_many_bytes(&byte, 1);
}

bool uart_socket::send_many_bytes(
		uint8_t *ptr_to_data, uint8_t len, uint16_t timeout)
{
	uint16_t count = 0;


	if (len > UART_TX_BUFF_LEN)
		return ERROR;

	while ( is_TX_pending() == true )
	{
		if(count >= timeout) {
			return ERROR;
		}

		OsHelpers::delay(1);
		count++;
	}

	// copy dynamic content to static buffer
	for (uint8_t i=0; i < len; i++)
	{
		uart_tx_buffer[i] = *ptr_to_data;
		ptr_to_data++;
	}

	HAL_UART_Transmit_DMA(huart, uart_tx_buffer, len);
	return SUCCESS;
}

/*bool uart_socket::is_TX_pending(void)
{
	HAL_UART_StateTypeDef usart_status =
			HAL_UART_GetState(huart) &  129; // 128 = Error, 1 = Tx Busy;

	return (usart_status == 0);
}*/
bool uart_socket::is_TX_pending(void)
{
	HAL_UART_StateTypeDef usart_status = HAL_UART_GetState(huart);

	return
			( (usart_status == HAL_UART_STATE_BUSY_TX) ||
					(usart_status == HAL_UART_STATE_BUSY_TX_RX) );
}


SimpleQueue<uint8_t>* uart_socket::get_rx_queue()
{
	return rx_queue;
}

/*
 * This function must be called either if uart-line is idle or
 * if dma-rx is complete (rx-buffer is full)
 */
void uart_socket::ISR_callback_fcn ()
{
	uint8_t i=0;
	uint16_t rxXferCount = 0;
	if(huart->hdmarx != NULL)
	{
		DMA_HandleTypeDef *hdma = huart->hdmarx;

		/* Determine how many items of data have been received */
		rxXferCount = huart->RxXferSize - __HAL_DMA_GET_COUNTER(hdma); // @suppress("Field cannot be resolved")
		HAL_DMA_Abort(huart->hdmarx);
		huart->RxXferCount = 0;

		// Check if a transmit process is ongoing or not
		//FIXME has no effect!!
		HAL_UART_StateTypeDef usart_status = HAL_UART_GetState(huart);
		if(usart_status == HAL_UART_STATE_BUSY_TX_RX)
		{
			//usart_status = HAL_UART_STATE_BUSY_TX;
			huart->gState = HAL_UART_STATE_BUSY_TX;
			huart->RxState = HAL_UART_STATE_READY;
		}
		else
		{
			//usart_status = HAL_UART_STATE_READY;
			huart->gState = HAL_UART_STATE_READY;
			huart->RxState = HAL_UART_STATE_READY;
		}
	}

	// copy uart-buffer to ringbuffer
	for (i = 0; i < rxXferCount; i++)	{
		rx_queue->enqueue(uart_rx_buffer[i]);
	}

	// we need rx-buffer filled with pad-chars
	memset(uart_rx_buffer, RX_PAD_CHAR, UART_RX_BUFF_LEN);

	HAL_UART_Receive_DMA(this->huart, uart_rx_buffer, UART_RX_BUFF_LEN);

#if USE_RTOS
	// notify the controlling task, that data has arrived
	osSignalSet (*task_to_notify, 0);
#endif
}


UART_HandleTypeDef*	uart_socket::get_handle(void)
{
	return huart;
}



