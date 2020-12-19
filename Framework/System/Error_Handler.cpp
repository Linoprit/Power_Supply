/*
 * Error_Handler.cpp
 *
 *  Created on: 07.10.2019
 *      Author: harald
 */

#include <System/Error_Handler.h>
#include <stdint.h>
#include <stdio.h>
#include <main.h>
#include <System/usb_printf.h>

// example: error_handler(__FILE__, __LINE__ );
void error_handler(const char* file, uint32_t line)
{

	HAL_GPIO_WritePin(LED_State_GPIO_Port, LED_State_Pin, GPIO_PIN_SET);
	tx_printf("Exception in %s, line: %ld\n", file, line);


	while (1) { }; // infinite loop
}

