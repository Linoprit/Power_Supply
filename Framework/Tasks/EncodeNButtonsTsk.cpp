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
#include <Instances/Common.h>

#include "main.h"


void StrtEncoderNButtons(void *argument)
{
	UNUSED(argument);

	rotaryEncoder::EventQueue_type 		eventQueue;
	rotaryEncoder::AdditionalButtons  additionalButtons;

	encodeNButtons::EncodeNButtons::instance().init();

	// Then encoders could cause unintended increment at startup
	encodeNButtons::EncodeNButtons::instance().cycle(eventQueue, additionalButtons);
	encodeNButtons::EncodeNButtons::instance().getVolData().getIsoll().set(0L);
	encodeNButtons::EncodeNButtons::instance().getVolData().getUsoll().set(0L);
	// TODO restore startupVals from EEPROM


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
		/*encodeNButtons::NonVolatileData
		nvData = encodeNButtons::EncodeNButtons::instance().getNvData();
		//encodeNButtons::VolatileData
		//volData = encodeNButtons::EncodeNButtons::instance().getVolData();
		static uint32_t oldTick = 0;
		if( (Common::get_tick() - oldTick) > 1000 ) {
			tx_printf("encNBut:  rs %i %i %i %i\n",
					nvData.getRshunt().get(),
					nvData.getRshunt().getActualPlace(),
					nvData.getRshunt().getExp() );
			oldTick = Common::get_tick();
		}*/

	/*	while(!eventQueue.isEmpty()) {
			rotaryEncoder::KeyEventTuple keyEventTuple = eventQueue.dequeue();

			tx_printf("Key: %i, Event: %i\n", keyEventTuple.key, keyEventTuple.event);
			osDelay(10);
		}
*/




		osDelay(10);
	}

}


