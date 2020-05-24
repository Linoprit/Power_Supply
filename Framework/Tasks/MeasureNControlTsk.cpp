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
		//HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		osDelay(1000);
	}

}



