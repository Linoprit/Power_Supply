/*
 * EncodeNButtons.cpp
 *
 *  Created on: 23.02.2020
 *      Author: harald
 */

#include "cmsis_os.h"
#include <Tasks/EncodeNButtonsTsk.h>
#include <Application/EncodeNButtons/EncodeNButtons.h>
#include <Application/EncodeNButtons/VolatileData.h>
#include <Instances/OsHelpers.h>
#include <Instances/Common.h>
#include <System/CommandLine/CommandLine.h>
#include <System/usb_printf.h>
#include "usb_device.h"

#include "main.h"


void StrtEncoderNButtons(void *argument)
{
	UNUSED(argument);

	MX_USB_DEVICE_Init();
	cLine::CommandLine::instance().init();
	osDelay(500);

	rotaryEncoder::EventQueue_type 		eventQueue;
	rotaryEncoder::AdditionalButtons  	additionalButtons;
	encodeNButtons::EncodeNButtons::instance().init();

	//encodeNButtons::VolatileData volData =
	//		encodeNButtons::EncodeNButtons::instance().getVolData();
	encodeNButtons::EncodeNButtons::instance().getNvData().initValues();


	/*encodeNButtons::EncodeNButtons::instance().cycle(eventQueue, additionalButtons);
	volData.getIsoll().set(0L);
	volData.getUsoll().set(50L);
	uint32_t usoll = volData.getUsoll().get();
	tx_printf("usoll: %lu\n", usoll);*/

	for(;;)
	{
		//HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		//HAL_Delay(200);

		// Button pressed = GND => active low
		additionalButtons.memory1 =
				(HAL_GPIO_ReadPin(Button_5_GPIO_Port, Button_5_Pin) == GPIO_PIN_RESET);
		additionalButtons.memory2 =
				(HAL_GPIO_ReadPin(Button_6_GPIO_Port, Button_6_Pin) == GPIO_PIN_RESET);
		additionalButtons.user =
				(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET);

		encodeNButtons::EncodeNButtons::instance().cycle(eventQueue, additionalButtons);

		// commandline cycle
		uint32_t hashCode = cLine::CommandLine::instance().cycle();
		cLine::ExecResult execResult =
				encodeNButtons::EncodeNButtons::instance().getNvData().executeCommand(hashCode);
		cLine::CommandLine::instance().prompt(execResult);
		tx_cycle();


		osDelay(10);
	}

}


