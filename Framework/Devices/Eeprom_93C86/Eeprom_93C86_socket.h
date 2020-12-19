/*
 * Eeprom_93C86_socket.h
 *
 *  Created on: 25.03.2018
 *      Author: harald
 */

#ifndef DEVICES_EEPROM_93C86_EEPROM_93C86_SOCKET_H_
#define DEVICES_EEPROM_93C86_EEPROM_93C86_SOCKET_H_

#include <stdint.h>
#include <main.h>
#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_gpio.h"

// These pins are connected to eeprom...
// EEPROM_DI_Port,  EEPROM_DI_Pin 	: data_in pin
// EEPROM_DO_Port,  EEPROM_DO_Pin	: data_out pin
// EEPROM_CLK_Port, EEPROM_CLK_Pin  : clock pin
// EEPROM_CS_Port,  EEPROM_CS_Pin	: chip select pin

class Eeprom_93C86_socket
{
public:
  Eeprom_93C86_socket ();
  virtual ~Eeprom_93C86_socket() {};

  void strobe_sck(void);
  void put_opcode(uint8_t code);
  void put_address(uint16_t address);
  void erase(uint16_t address);
  void eraseall(void);
  void write_disable(void);
  void write_enable(void);
  uint8_t read(uint16_t address);
  void readBlock(uint16_t address, uint8_t *data, uint8_t len);
  void write(uint16_t address, uint8_t data);
  void writeBlock(uint16_t address, uint8_t* data, uint8_t len);
  void writeall(uint8_t data);

  inline bool is_busy(void)
  {
	  bool result = false;

	  HAL_GPIO_WritePin(EEPROM_CS_GPIO_Port, EEPROM_CS_Pin, GPIO_PIN_SET);
	  strobe_sck();
	  result = HAL_GPIO_ReadPin(
		  EEPROM_DO_GPIO_Port, EEPROM_DO_Pin) == GPIO_PIN_RESET;
	  HAL_GPIO_WritePin(EEPROM_CS_GPIO_Port, EEPROM_CS_Pin, GPIO_PIN_SET);

	 if (result == false)  {
		 return true;
	   }
	  else	{
		  return false;
		}
  };

  inline void put_to_standby(void)  {
	HAL_GPIO_WritePin(EEPROM_CS_GPIO_Port, EEPROM_CS_Pin, GPIO_PIN_RESET);
  };

  uint16_t getMaxAddress(void) { return MAX_ADDRESS; };

  static constexpr uint16_t MAX_ADDRESS = 2047; // 93C86 highest address

};

#endif /* DEVICES_EEPROM_93C86_EEPROM_93C86_SOCKET_H_ */
