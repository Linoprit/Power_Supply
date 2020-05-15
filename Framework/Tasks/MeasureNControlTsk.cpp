/*
 * MeasureNControl.cpp
 *
 *  Created on: 23.02.2020
 *      Author: harald
 */

#include <Tasks/MeasureNControlTsk.h>
#include "cmsis_os.h"
#include "main.h"


void StrtMeasureNControl(void *argument)
{
	UNUSED(argument);

	for(;;)
	{

		osDelay(1000);
	}

}



