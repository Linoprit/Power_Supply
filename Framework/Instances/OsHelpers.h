/*
 * OsHelpers.h
 *
 *  Created on: 26.04.2020
 *      Author: harald
 */

#ifndef INSTANCES_OSHELPERS_H_
#define INSTANCES_OSHELPERS_H_

#ifdef STM32F303xE
#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_uart.h"
#endif
#ifdef STM32F103xB
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"
#endif
// We must enable OS manually
//#if USE_RTOS
#include "cmsis_os.h"
//#endif

void * operator new( size_t size );
void * operator new[]( size_t size );
void operator delete( void * ptr );
void operator delete[]( void * ptr );


class OsHelpers {
public:
	OsHelpers() {};
	virtual ~OsHelpers() {};

	// We just look, if there is any RTOS definition
#if osWaitForever
	static inline void delay(uint32_t delay) { osDelay(delay); }
#else
	static inline void delay(uint32_t delay) { HAL_Delay(delay); }
#endif


};

#endif /* INSTANCES_OSHELPERS_H_ */
