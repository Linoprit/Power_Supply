/*
 * uart_messaging.c
 *
 *  Created on: 16.12.2018
 *      Author: harald
 */

#include "uart_printf.h"
#include <stdio.h>
#include <stdarg.h>
#include <main.h>
#include <Instances/Common.h>

// which UART to use as debug-port
#define UART_PORT get_huart2()
#define USE_DMA 1 // DMA transmit on UART2 doesn't work on Nucleo F303


#define TX_BUFF_LEN 128
uint8_t txBuff[TX_BUFF_LEN];
uint16_t tx_act_pos = 0;


#ifndef min
#define min(a,b)   (((a) < (b)) ? (a) : (b))
#endif

/*
 to enable float formatted output, see:
 https://stackoverflow.com/questions/28334435/stm32-printf-float-variable.
 - add -u _printf_float to your LDFLAGS.
 or
 - printf("Result is: %d.%d", i/10, i%10);
 */

int tx_printf(const char *format, ...)
{
	tx_buff_clear();

	va_list arg;
	va_start (arg, format);
	tx_act_pos = vsprintf ((char*) &txBuff[0], format, arg);
	va_end (arg);

	uint8_t* ptr = &txBuff[0];
	for(uint8_t i=0 ; i < TX_BUFF_LEN ; i++) {
		ITM_SendChar((*ptr++)); // use SWO
		if(*ptr == '\0')
			break;
	}

	return SUCCESS;
}

void tx_buff_clear(void)
{
	for(uint16_t i=0; i < TX_BUFF_LEN; i++)
	{
		txBuff[i] = '\0';
	}
	tx_act_pos = 0;
}
