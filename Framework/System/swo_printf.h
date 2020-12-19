/*
 * uart_messaging.h
 *
 *  Created on: 16.12.2018
 *      Author: harald
 */

#ifndef SWO_PRINTF_H_
#define SWO_PRINTF_H_

#include "stm32f3xx_hal.h"

// C interface
#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC int swoPrintf(const char *format, ...);

#undef EXTERNC
#ifdef __cplusplus
// put cpp includes here!!

#endif // C interface
#endif /* SWO_PRINTF_H_ */
