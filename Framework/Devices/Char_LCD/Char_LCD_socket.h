/*
 * Char_LCD_socket.h
 *
 *  Created on: 08.01.2017
 *      Author: harald
 */

#ifndef DEVICES_CHAR_LCD_CHAR_LCD_SOCKET_H_
#define DEVICES_CHAR_LCD_CHAR_LCD_SOCKET_H_


#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_spi.h"
//#include "Instances/Common.h"


#define LCD_WAIT_DELAY     5      // Wartezeit in ms bis Anweisung gültig
#define LCD_PULSE_DELAY_us 40     // LCD-Service pause between EN-pulses [µs]
#define LCD_PULSE_DELAY_ms 1      // LCD-Service pause between EN-pulses [ms]



class Char_LCD_socket
{
public:

  typedef struct {
	GPIO_TypeDef* 	RS_port;
	GPIO_TypeDef*	EN_port;
	uint16_t		RS_pin;
	uint16_t		EN_pin;
  } char_LCD_pinspack_type;


  Char_LCD_socket (SPI_HandleTypeDef* 		lcd_spi,
				   char_LCD_pinspack_type* 	lcd_pinspack);
  virtual ~Char_LCD_socket ();


  void put_byte_2_lcd_initonly (uint8_t data); // blocking!!

  inline void select_instruction_register(void)
  {
	HAL_GPIO_WritePin(pinspack->RS_port, pinspack->RS_pin, GPIO_PIN_RESET);
	//HAL_Delay(LCD_PULSE_DELAY_ms);
  };

  inline void select_data_register(void)
  {
	HAL_GPIO_WritePin(pinspack->RS_port, pinspack->RS_pin, GPIO_PIN_SET);
	//HAL_Delay(LCD_PULSE_DELAY_ms);
  };

  inline void set_lcd_en_line(void)
  {
	HAL_GPIO_WritePin(pinspack->EN_port, pinspack->EN_pin, GPIO_PIN_SET);
	//HAL_Delay(LCD_PULSE_DELAY_ms);
  };

  inline void reset_lcd_en_line(void)
  {
	HAL_GPIO_WritePin(pinspack->EN_port, pinspack->EN_pin, GPIO_PIN_RESET);
	//HAL_Delay(LCD_PULSE_DELAY_ms);
  };

  inline void do_data_valid_sequence(void)
  {
	set_lcd_en_line();
	HAL_Delay(LCD_PULSE_DELAY_ms);
	reset_lcd_en_line();
  };

  inline void pulse_byte_2_lcd (uint8_t data)
  {
	send_byte(data);
	do_data_valid_sequence();
  };

  inline void pulse_byte_2_lcd_nblk(uint8_t data)
  {
	send_byte(data);
	set_lcd_en_line();

	// TODO pause sufficient? 0xff was too short!!
	// we still need a small delay, approx 25µs
	for(uint32_t i=0; i<(0x10f); i++);

	reset_lcd_en_line();
  }

  inline bool send_byte(uint8_t byte)
  {
	while(HAL_SPI_GetState(spi) != HAL_SPI_STATE_READY)
	  {
	  }

	HAL_SPI_Transmit_IT(spi, &byte, 1);

	return true;
  }

  // Interfacing. Use this outside the socket.
  inline void delay_ms(uint8_t delay)
  {
	HAL_Delay((unsigned long) delay);
  }


private:
  SPI_HandleTypeDef* spi;
  char_LCD_pinspack_type* pinspack;
};

#endif /* DEVICES_CHAR_LCD_CHAR_LCD_SOCKET_H_ */
