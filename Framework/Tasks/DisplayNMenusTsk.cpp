/*
 * StrtdisplayNData.cpp
 *
 *  Created on: 23.02.2020
 *      Author: harald
 */

#include <Application/DisplayNMenus/DisplayNMenus.h>
#include "cmsis_os.h"
#include <Tasks/DisplayNMenusTsk.h>
#include "main.h"
#include <stdio.h>
#include <System/CommandLine/CommandLine.h>
#include <System/usb_printf.h>
#include "usb_device.h"
//#include <usbd_cdc_if.h>



void StrtDisplayNMenus(void *argument)
{
	UNUSED(argument);
	uint8_t loopCounter = 0;
	MX_USB_DEVICE_Init();
	displaynmenus::DisplayNMenus::instance().init();

	cLine::CommandLine::instance().init();
	osDelay(500);

	for(;;)
	{

		//HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		//HAL_GPIO_TogglePin(LED_State_GPIO_Port, LED_State_Pin);
		//HAL_GPIO_TogglePin(Led_EEPROM_GPIO_Port, Led_EEPROM_Pin);

		cLine::CommandLine::instance().cycle();
		tx_cycle();

		if (loopCounter >= 10){
			displaynmenus::DisplayNMenus::instance().cycle();
			loopCounter = 0;
		}
		loopCounter++;

		osDelay(10);
	}

}


// from main.c
//osSemaphoreId_t ThetaTskDataSemHandle;
//osSemaphoreId_t CtrTskDataSemHandle;
//osSemaphoreId_t EncdTskDataSemHandle;

// from cmsis_os2.h
/// Acquire a Semaphore token or timeout if no tokens are available.
/// \param[in]     semaphore_id  semaphore ID obtained by \ref osSemaphoreNew.
/// \param[in]     timeout       \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
/// \return status code that indicates the execution status of the function.
//osStatus_t osSemaphoreAcquire (osSemaphoreId_t semaphore_id, uint32_t timeout);

/// Release a Semaphore token up to the initial maximum count.
/// \param[in]     semaphore_id  semaphore ID obtained by \ref osSemaphoreNew.
/// \return status code that indicates the execution status of the function.
//osStatus_t osSemaphoreRelease (osSemaphoreId_t semaphore_id);

/// Get current Semaphore token count.
/// \param[in]     semaphore_id  semaphore ID obtained by \ref osSemaphoreNew.
/// \return number of tokens available.
//uint32_t osSemaphoreGetCount (osSemaphoreId_t semaphore_id);
