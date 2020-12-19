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
#include <Instances/OsHelpers.h>


#define LCD_WAIT_DELAY     5      // Wartezeit in ms bis Anweisung gültig
#define LCD_PULSE_DELAY_us 40     // LCD-Service pause between EN-pulses [µs]
#define LCD_PULSE_DELAY_ms 1      // LCD-Service pause between EN-pulses [ms]



class Char_LCD_socket
{
public:
	Char_LCD_socket () {
		_spi = NULL;
		_RS_port = NULL;
		_EN_port = NULL;
		_RS_pin  = 0;
		_EN_pin  = 0;
	};
	Char_LCD_socket (
					SPI_HandleTypeDef				*lcd_spi,
					GPIO_TypeDef						*RS_port,
					GPIO_TypeDef						*EN_port,
					uint16_t								RS_pin,
					uint16_t								EN_pin);
	virtual ~Char_LCD_socket() {};


	void put_byte_2_lcd_initonly (uint8_t data); // blocking!!

	inline void select_instruction_register(void)
	{
		HAL_GPIO_WritePin(_RS_port, _RS_pin, GPIO_PIN_RESET);
		//Common::delay(LCD_PULSE_DELAY_ms);
	};

	inline void select_data_register(void)
	{
		HAL_GPIO_WritePin(_RS_port, _RS_pin, GPIO_PIN_SET);
		//Common::delay(LCD_PULSE_DELAY_ms);
	};

	inline void set_lcd_en_line(void)
	{
		HAL_GPIO_WritePin(_EN_port, _EN_pin, GPIO_PIN_SET);
		//Common::delay(LCD_PULSE_DELAY_ms);
	};

	inline void reset_lcd_en_line(void)
	{
		HAL_GPIO_WritePin(_EN_port, _EN_pin, GPIO_PIN_RESET);
		//Common::delay(LCD_PULSE_DELAY_ms);

	};

	inline void do_data_valid_sequence(void)
	{
		set_lcd_en_line();
		OsHelpers::delay(LCD_PULSE_DELAY_ms);
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
		while(HAL_SPI_GetState(_spi) != HAL_SPI_STATE_READY)
		{
		}

		HAL_SPI_Transmit_IT(_spi, &byte, 1);

		return true;
	}


private:
	SPI_HandleTypeDef				*_spi;
	GPIO_TypeDef  					*_RS_port;
	GPIO_TypeDef  					*_EN_port;
	uint16_t								_RS_pin;
	uint16_t								_EN_pin;
};

#endif /* DEVICES_CHAR_LCD_CHAR_LCD_SOCKET_H_ */
