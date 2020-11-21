/*
 * callbacks.c
 *
 *  Created on: 16.05.2016
 *      Author: harald
 */


#include "callbacks.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_uart.h"
#include "main.h"
#include "Common.h"


ISR_callback *uart1_RxCplt_callback   = NULL;
ISR_callback *uart2_RxCplt_callback   = NULL;
ISR_callback *uart3_RxCplt_callback   = NULL;
ISR_callback *rotary_encoder_callback = NULL;
ISR_callback *inaAlertPin_callback 	  = NULL;

/*void HAL_SYSTICK_Callback(void)
{


}*/


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//UNUSED(GPIO_Pin);

  // Rotary Encoder ISR
  if (GPIO_Pin == Rotary_Encoder_INT_Pin) {
	  if (rotary_encoder_callback != NULL){
	  	rotary_encoder_callback->ISR_callback_fcn();
	  }
	}

  // current limit alert pin
  if (GPIO_Pin == Ina_ALERT_Pin) {
	  if(inaAlertPin_callback != NULL) {
		  inaAlertPin_callback->ISR_callback_fcn();
	  }
  }

  //HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}

void add_uart_callback(UART_HandleTypeDef *huart, ISR_callback* callback)
{
	if (huart->Instance == USART1)
	{
		uart1_RxCplt_callback = callback;
	}

	else if (huart->Instance == USART2)
	{
		uart2_RxCplt_callback = callback;
	}

	else if (huart->Instance == USART3)
	{
		uart3_RxCplt_callback = callback;
	}
}

void call_uart_callbacks(UART_HandleTypeDef *huart)
{
	// TODO three times the same... better idea?
	if (huart->Instance == USART1)
	{
		if (uart1_RxCplt_callback == NULL)
			return;

		uart1_RxCplt_callback->ISR_callback_fcn();
	}

	else if (huart->Instance == USART2)
	{
		if (uart2_RxCplt_callback == NULL)
			return;

		uart2_RxCplt_callback->ISR_callback_fcn();
	}

	else if (huart->Instance == USART3)
	{
		if (uart3_RxCplt_callback == NULL)
			return;

		uart3_RxCplt_callback->ISR_callback_fcn();
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	// TODO do we need some overflow handler?
	//HAL_GPIO_WritePin(LED_04_GPIO_Port, LED_04_Pin, GPIO_PIN_SET);
	//HAL_GPIO_TogglePin(LED_03_GPIO_Port, LED_03_Pin);

	call_uart_callbacks(huart);
}

void HAL_UART_RxIdleCallback(UART_HandleTypeDef *huart)
{
	call_uart_callbacks(huart);
}

// Workaround hanging usart-dma
//void USART1_IRQHandler(void)
//{
//	HAL_UART_IRQHandler(get_huart1());
//}

//void USART2_IRQHandler(void)
//{
//  HAL_UART_IRQHandler(get_huart2());
//}

//void USART3_IRQHandler(void)
//{
//	HAL_UART_IRQHandler(get_huart3());
//}

void add_rotary_encoder_callback(ISR_callback* callback) {
  rotary_encoder_callback = callback;
}

void add_inaAlertPin_callback(ISR_callback* callback) {
	inaAlertPin_callback = callback;
}

