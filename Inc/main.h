/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define Char_LCD_EN_Pin GPIO_PIN_0
#define Char_LCD_EN_GPIO_Port GPIOC
#define Char_LCD_RS_Pin GPIO_PIN_1
#define Char_LCD_RS_GPIO_Port GPIOC
#define EEPROM_DO_Pin GPIO_PIN_2
#define EEPROM_DO_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define Button_6_Pin GPIO_PIN_6
#define Button_6_GPIO_Port GPIOA
#define Button_5_Pin GPIO_PIN_7
#define Button_5_GPIO_Port GPIOA
#define Led_EEPROM_Pin GPIO_PIN_4
#define Led_EEPROM_GPIO_Port GPIOC
#define LED_State_Pin GPIO_PIN_5
#define LED_State_GPIO_Port GPIOC
#define Ina_ALERT_Pin GPIO_PIN_15
#define Ina_ALERT_GPIO_Port GPIOB
#define Ina_ALERT_EXTI_IRQn EXTI15_10_IRQn
#define FAN_out_Pin GPIO_PIN_6
#define FAN_out_GPIO_Port GPIOC
#define EEPROM_DI_Pin GPIO_PIN_7
#define EEPROM_DI_GPIO_Port GPIOC
#define EEPROM_CS_Pin GPIO_PIN_8
#define EEPROM_CS_GPIO_Port GPIOC
#define EEPROM_SCLK_Pin GPIO_PIN_9
#define EEPROM_SCLK_GPIO_Port GPIOC
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define JLink_SWO_Pin GPIO_PIN_3
#define JLink_SWO_GPIO_Port GPIOB
#define Voltage_HI_LO_Pin GPIO_PIN_4
#define Voltage_HI_LO_GPIO_Port GPIOB
#define Rotary_Encoder_INT_Pin GPIO_PIN_6
#define Rotary_Encoder_INT_GPIO_Port GPIOB
#define Rotary_Encoder_INT_EXTI_IRQn EXTI9_5_IRQn
#define Uart3_Rx_Pin GPIO_PIN_8
#define Uart3_Rx_GPIO_Port GPIOB
#define Uart3_Tx_Pin GPIO_PIN_9
#define Uart3_Tx_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
