/*
 * Initclasses.h
 *
 *  Created on: 06.05.2016
 *      Author: harald
 */

#ifndef COMMON_H_
#define COMMON_H_

#ifdef STM32F303xE
#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_uart.h"
#endif
#ifdef STM32F103xB
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"
#endif
#if USE_RTOS
#include "cmsis_os.h"
#endif

// C includes only
#include <stdbool.h>
#include "cmsis_os2.h"


// C interface
#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void common_init(void);
EXTERNC bool common_initIsDone(void);
EXTERNC void mainCycle(void);

// bodies are in main.c
EXTERNC UART_HandleTypeDef* get_huart1(void);
//EXTERNC UART_HandleTypeDef* get_huart2(void);
EXTERNC UART_HandleTypeDef* get_huart3(void);
EXTERNC SPI_HandleTypeDef* 	get_hspi3 (void);
EXTERNC SPI_HandleTypeDef* 	get_hspi3 (void);
EXTERNC I2C_HandleTypeDef* 	get_hi2c1 (void);
EXTERNC I2C_HandleTypeDef* 	get_hi2c3 (void);
EXTERNC ADC_HandleTypeDef*  get_hadc3 (void);
EXTERNC DAC_HandleTypeDef*  get_hdac1 (void);
EXTERNC CRC_HandleTypeDef* 	get_hcrc(void);

// semaphores
EXTERNC osSemaphoreId_t CtrTskDataSemHandle;
EXTERNC osSemaphoreId_t EncdTskDataSemHandle;

#undef EXTERNC

#ifdef __cplusplus

// put cpp includes here!!
#include <Sockets/uart_socket.h>


// Common defines / constexpr

// We set an error-state, if a semaphore was refused this many times.
// Used in MeasureNControl module
constexpr uint8_t	MAX_SEM_ERROR_COUNT	= 5;

// INA226 setup (TODO some values have currently no effect)
constexpr uint8_t INA226_IC2_ADDRESS 	= 0x40;
constexpr double 	SHUNT_RESISTOR_OHMS = 0.01017;
constexpr double 	MAX_CURRENT_AMPS    = 8.192f;

// TODO put further values here



class Common
{
public:

  Common() {};
  virtual ~Common() {};
  static void init(void);
  static inline bool isInitDone(void) 	{ return _initIsDone;		};
  static inline uint32_t get_tick(void) { return HAL_GetTick(); };





private:
  static bool _initIsDone;



};

#endif // C interface
#endif /* COMMON_H_ */
