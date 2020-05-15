/*
 * EncodeNButtons.cpp
 *
 *  Created on: 23.02.2020
 *      Author: harald
 */

#include "cmsis_os.h"
#include <Tasks/EncodeNButtonsTsk.h>
#include <Application/EncodeNButtons/EncodeNButtons.h>
#include <Instances/OsHelpers.h>


#include "main.h"


void StrtEncoderNButtons(void *argument)
{
	UNUSED(argument);

	rotaryEncoder::EventQueue_type 		eventQueue;
	rotaryEncoder::AdditionalButtons  additionalButtons;

	encodeNButtons::EncodeNButtons::instance().init();

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

		// TODO remove
		while(!eventQueue.isEmpty()) {
			rotaryEncoder::KeyEventTuple keyEventTuple = eventQueue.dequeue();

			tx_printf("Key: %i, Event: %i\n", keyEventTuple.key, keyEventTuple.event);
			osDelay(10);
		}


		// ToDo HMI_coordinator(eventQueue);


		osDelay(10);
	}

}


