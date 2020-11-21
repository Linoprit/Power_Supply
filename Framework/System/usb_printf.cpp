/*
 * uart_messaging.c
 *
 *  Created on: 16.12.2018
 *      Author: harald
 */

#include <usbd_cdc_if.h>
#include <stdio.h>
#include <stdarg.h>
#include <main.h>
#include <System/usb_printf.h>
#include "cmsis_os.h"
#include "libraries/HelpersLib.h"
#include <System/CommandLine/CommandLine.h>


constexpr uint16_t TX_BUFF_LEN = 256;
constexpr uint8_t  TX_DELAY = 10;
constexpr uint8_t  TX_RETRIES = 10;

uint8_t txBuff[TX_BUFF_LEN];
uint16_t tx_act_pos = 0;

// private
void tx_buff_clear(void);

/*
 * to enable FLOAT formatted output, see:
 * https://stackoverflow.com/questions/28334435/stm32-printf-float-variable.
 * - add -u _printf_float to your LDFLAGS.
 * or
 * - printf("Result is: %d.%d", i/10, i%10);
 */
int tx_printf(const char *format, ...) {
	if(tx_act_pos >= TX_BUFF_LEN-1) {
		return _ERROR;
	}
	va_list arg;
	va_start (arg, format);
	tx_act_pos += vsprintf ((char*) &txBuff[tx_act_pos], format, arg);
	va_end (arg);

	return _SUCCESS;
}

uint8_t tx_cycle(void) {
	if( tx_act_pos > 0) {
		uint8_t result = USBD_FAIL;

		for (uint8_t i=0; i < TX_RETRIES; i++) {
			result = CDC_Transmit_FS(txBuff, tx_act_pos);
			// @retval USBD_OK if all operations are OK else USBD_FAIL or USBD_BUSY
			if(result == USBD_OK) {
				break;
			} else {
				osDelay(TX_DELAY);
			}
		}

		tx_buff_clear();

		if (result == USBD_OK)
			return _SUCCESS;
		else
			return _ERROR;
	}
	return _SUCCESS;
}

/*
 * directly print buffer, without formatting
 */
int tx_printBuff(uint8_t* buffer, uint8_t len) {
	memcpy( &txBuff[tx_act_pos], buffer, (std::size_t) len );
	tx_act_pos += len;
	return _SUCCESS;
}

void tx_buff_clear(void) {
	memset(txBuff, '\0', TX_BUFF_LEN);
	tx_act_pos = 0;
}

/*
 * callback from Cube USB firmware
 */
void usb_receive(uint8_t* buf, uint32_t len) {
	for (uint8_t i=0; i < len; i++) {
		cLine::CommandLine::instance().putChar(buf[i]);
	}
}







