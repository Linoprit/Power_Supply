/*
 * StrtdisplayNData.cpp
 *
 *  Created on: 23.02.2020
 *      Author: harald
 */

#include "cmsis_os.h"
#include <Application/DisplayNData/DisplayNData.h>
#include <Tasks/DisplayNDataTsk.h>


void StrtDisplayNData(void *argument)
{
	displayndata::DisplayNData::instance().init();


	for(;;)
	{
		displayndata::DisplayNData::instance().cycle();
		osDelay(500);
	}

}


