/*
 * Discovery_LEDs.h
 *
 *  Created on: 27.01.2017
 *      Author: harald
 */

#ifndef SYSTEM_DISCOVERY_LEDS_H_
#define SYSTEM_DISCOVERY_LEDS_H_


#define TGL_LED_SO \
	HAL_GPIO_TogglePin(LD10_GPIO_Port, LD10_Pin)

#define TGL_LED_SE \
HAL_GPIO_TogglePin(LD9_GPIO_Port, LD9_Pin)

#define TGL_LED_SW \
HAL_GPIO_TogglePin(LD8_GPIO_Port, LD8_Pin)

#define TGL_LED_EA \
HAL_GPIO_TogglePin(LD7_GPIO_Port, LD7_Pin)

#define TGL_LED_WE \
HAL_GPIO_TogglePin(LD6_GPIO_Port, LD6_Pin)

#define TGL_LED_NE \
HAL_GPIO_TogglePin(LD5_GPIO_Port, LD5_Pin)

#define TGL_LED_NW \
HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin)

#define TGL_LED_NO \
HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin)



#endif /* SYSTEM_DISCOVERY_LEDS_H_ */
