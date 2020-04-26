/*

 * Comm_layer_socket.h
 *
 *  Created on: 25.05.2016
 *      Author: harald
 */

#ifndef MACHINE_COMM_LAYER_COMM_LAYER_SOCKET_H_
#define MACHINE_COMM_LAYER_COMM_LAYER_SOCKET_H_

#ifdef STM32F303xE
#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_uart.h"
#endif
#ifdef STM32F103xB
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"
#endif
#if USE_RTOS
#include "cmsis_os.h"
#endif

#include <stdint.h>
#include <System/RX_TX_interface.h>
#include <libraries/SimpleQueue.h>
#include <Instances/callbacks.h>



#define UART_TX_BUFF_LEN	50
#define UART_RX_BUFF_LEN 	30
#define RX_PAD_CHAR			  4   // 4 = EOT



class uart_socket:
		Rx_Tx_interface,
		ISR_callback
{
public:
#if USE_RTOS
			uart_socket (UART_HandleTypeDef *huart,
					osThreadId* task_to_notify );
#else
			uart_socket (UART_HandleTypeDef *huart);
#endif

			virtual ~uart_socket () {};

			bool 	send_byte(uint8_t byte);
			bool 	send_many_bytes(
					uint8_t *ptr_to_data, uint8_t len, uint16_t timeout=10);
			bool 	is_TX_pending(void);

			SimpleQueue<uint8_t>* 	get_rx_queue(void);

			UART_HandleTypeDef*	get_handle(void);


			// callback usart receive complete / idle line
			void ISR_callback_fcn (void);

			uint8_t 				*uart_rx_buffer;


private:
#if USE_RTOS
			osThreadId 			*task_to_notify;
#endif
			uint8_t*							uart_tx_buffer;
			UART_HandleTypeDef*		huart;

			SimpleQueue<uint8_t>* 	rx_queue;

};

#endif /* MACHINE_COMM_LAYER_COMM_LAYER_SOCKET_H_ */
