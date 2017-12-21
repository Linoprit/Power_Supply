/*
 * callbacks.c
 *
 *  Created on: 16.05.2016
 *      Author: harald
 */

#include "callbacks.h"
#include "stm32f3xx_hal.h"
#include "System/SoftwareEvents.h"
#include "Common.h"


ISR_callback *uart1_RxCplt_callback   = NULL;
ISR_callback *rotary_encoder_callback = NULL;


void HAL_SYSTICK_Callback(void)
{
  uint32_t tick = HAL_GetTick();
  SoftwareEvents_checkTicks(tick);
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  // Rotary Encoder ISR
  if (GPIO_Pin == Rotary_Encoder_INT_Pin)
	{
	  if (rotary_encoder_callback != NULL)
		rotary_encoder_callback->ISR_callback_fcn();
	}



}

void rotary_encoder_callback_set(ISR_callback* callback)
{
  rotary_encoder_callback = callback;
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

	  uart1_RxCplt_callback->ISR_callback_fcn();
	}
}










