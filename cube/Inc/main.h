/*
 * main.h
 *
 *  Created on: 11.05.2016
 *      Author: harald
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "stm32f3xx_hal.h"

#ifdef __cplusplus
 extern "C" {
#endif


SPI_HandleTypeDef* 	get_LCD_SPI(void);
UART_HandleTypeDef* get_UART_1(void);
SPI_HandleTypeDef* 	get_SD_SPI(void);
I2C_HandleTypeDef* 	get_I2C_1(void);


#ifdef __cplusplus
}
#endif

#endif /* MAIN_H_ */
