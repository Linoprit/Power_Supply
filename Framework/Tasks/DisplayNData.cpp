/*
 * StrtdisplayNData.cpp
 *
 *  Created on: 23.02.2020
 *      Author: harald
 */

#include <Tasks/DisplayNData.h>
#include "cmsis_os.h"
#include <Application/DisplayNData/DisplayNData.h>


void StrtDisplayNData(void *argument)
{
	displayndata::DisplayNData::instance().init();


	for(;;)
	{
		displayndata::DisplayNData::instance().cycle();
		osDelay(1000);
	}

}


