/*
 * Keypadbitbanging.cpp
 *
 *  Created on: 04.11.2015
 *      Author: harald
 */

#include "Keypad_socket.h"



Keypad_socket::Keypad_socket (keypad_pinspack_type *keypad_pinspack)
{
  this->keypad_pinspack = keypad_pinspack;
}


void Keypad_socket::setRowPort_Listening(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  // set row pins input
  GPIO_InitStruct.Pin = keypad_pinspack->RowBitmask;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(keypad_pinspack->RowPort, &GPIO_InitStruct);

  // enable ISR
  /*for (int8_t i=0; i < keypad_pinspack->ISR_vect_len; i++)
	{
	  HAL_NVIC_SetPriority(
		  (IRQn_Type) keypad_pinspack->ISR_vectors[i], 15, 0);

	  HAL_NVIC_EnableIRQ(
		  (IRQn_Type) keypad_pinspack->ISR_vectors[i]);
	}*/

  /* EXTI interrupt init*/
 /* HAL_NVIC_SetPriority(EXTI0_IRQn, 15, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 15, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_TSC_IRQn, 15, 0);
  HAL_NVIC_EnableIRQ(EXTI2_TSC_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 15, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);*/

}


void Keypad_socket::setColPort_Input(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  // set row pins input
  GPIO_InitStruct.Pin = keypad_pinspack->ColBitmask;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(keypad_pinspack->ColPort, &GPIO_InitStruct);
}


void Keypad_socket::setRowPort_Output(void)
{
  // disable ISR
 /* HAL_NVIC_DisableIRQ(EXTI0_IRQn);
  HAL_NVIC_DisableIRQ(EXTI1_IRQn);
  HAL_NVIC_DisableIRQ(EXTI2_TSC_IRQn);
  HAL_NVIC_DisableIRQ(EXTI3_IRQn);*/

  GPIO_InitTypeDef GPIO_InitStruct;

  GPIO_InitStruct.Pin = keypad_pinspack->RowBitmask;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(keypad_pinspack->RowPort, &GPIO_InitStruct);
}


void Keypad_socket::setColPort_Output(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  GPIO_InitStruct.Pin = keypad_pinspack->ColBitmask;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(keypad_pinspack->ColPort, &GPIO_InitStruct);
}


uint16_t Keypad_socket::getRowPort(void)
{
  return ~keypad_pinspack->RowPort->IDR &
	  keypad_pinspack->RowBitmask & keypad_pinspack->RowBitmask;
}


uint16_t Keypad_socket::getColPort(void)
{
  return ~keypad_pinspack->ColPort->IDR &
	  keypad_pinspack->ColBitmask;
}
