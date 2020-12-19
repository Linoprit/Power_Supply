/*
 * MeasureNControl.cpp
 *
 *  Created on: 23.02.2020
 *      Author: harald
 */


#include "cmsis_os.h"
#include <Tasks/MeasureNControlTsk.h>
#include <Application/MeasureNControl/MeasureNControl.h>
#include "main.h"


void StrtMeasureNControl(void *argument)
{
	UNUSED(argument);

	measureNControl::MeasureNControl::instance().init();



	for(;;)
	{

		//HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		measureNControl::MeasureNControl::instance().cycle();
		//HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

		//HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

		osDelay(2);


	}

}



