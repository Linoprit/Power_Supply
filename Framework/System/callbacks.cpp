/*
 * callbacks.c
 *
 *  Created on: 16.05.2016
 *      Author: harald
 */

#include "callbacks.h"
#include "stm32f3xx_hal.h"
#include "System/SoftwareEvents.h"


ISR_callback *keypad_GPIO_callback 		= NULL;
ISR_callback *uart1_RxCplt_callback 	= NULL;



void HAL_SYSTICK_Callback(void)
{
  uint32_t tick = HAL_GetTick();
  SoftwareEvents_checkTicks(tick);
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (keypad_GPIO_callback == NULL)
	return;

  if ( (GPIO_Pin == Key_Row_0_Pin) ||
	  (GPIO_Pin == Key_Row_1_Pin) ||
	  (GPIO_Pin == Key_Row_2_Pin) ||
	  (GPIO_Pin == Key_Row_3_Pin) )
	{
	  keypad_GPIO_callback->callback_fcn();
	}
}

void keypad_callback_set(ISR_callback* callback)
{
  keypad_GPIO_callback = callback;
}

void keypad_callback_clear(void)
{
  keypad_GPIO_callback = NULL;
}


void uart1_callback_set(ISR_callback* callback)
{
  uart1_RxCplt_callback = callback;
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
	{
	  if (uart1_RxCplt_callback == NULL)
		return;

	  uart1_RxCplt_callback->callback_fcn();
	}
}
