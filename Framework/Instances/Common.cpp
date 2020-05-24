/*
 * Initclasses.cpp
 *
 *  Created on: 06.05.2016
 *      Author: harald
 */

#include <inttypes.h>
#include "Common.h"
#include "stm32f3xx_hal.h"
#include "main.h"
#include "Instances/callbacks.h"
#include "System/uart_printf.h"






// C interface instances
void common_init(void)					{ Common::init(); 				}
bool common_initIsDone(void)  	{ return Common::isInitDone(); 	}


// C++ instances
bool 							Common::_initIsDone 				= false;


/**
 * Some of the constructors use a osDelay call. So we need a running os.
 * That's why we call this function from the Start* tasks.
 */
void Common::init()
{
	if (Common::_initIsDone == true)
		return;




	_initIsDone 		= true;
}



