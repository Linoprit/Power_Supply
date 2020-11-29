/*
 * Eeprom_93C86_socket.cpp
 *
 *  Created on: 25.03.2018
 *     Author: harald
 *     based on Bob Ryans 93C46B EEprom Driver, (c) 2010
 */


#include <Devices/Eeprom_93C86/Eeprom_93C86_socket.h>
#include <Instances/OsHelpers.h>

// on 93C86, 8-bit mode, we have eleven address-bits
#define ADDRESS_MASK 1024 // the 11th bit
#define ADDRESS_BITS 11
#define LAST_DATABIT 128


Eeprom_93C86_socket::Eeprom_93C86_socket ()
{ }

void Eeprom_93C86_socket::strobe_sck(void)
{
  uint32_t i;
#define WAITVAL 5000

  HAL_GPIO_WritePin(EEPROM_SCLK_GPIO_Port, EEPROM_SCLK_Pin, GPIO_PIN_SET);
  for (i=0; i < WAITVAL; i++) {} // should be 50us

  HAL_GPIO_WritePin(EEPROM_SCLK_GPIO_Port, EEPROM_SCLK_Pin, GPIO_PIN_RESET);
  for (i=0; i < WAITVAL; i++) {}
}

void Eeprom_93C86_socket::put_opcode(uint8_t code)
{
  // slave select has to go low >250ns between commands
  HAL_GPIO_WritePin(EEPROM_CS_GPIO_Port, EEPROM_CS_Pin, GPIO_PIN_RESET);
  strobe_sck();

  HAL_GPIO_WritePin(EEPROM_CS_GPIO_Port, EEPROM_CS_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(EEPROM_DI_GPIO_Port, EEPROM_DI_Pin, GPIO_PIN_SET);
  strobe_sck();

  // write opcode bit 1
  if (code & 0x02)
	HAL_GPIO_WritePin(EEPROM_DI_GPIO_Port, EEPROM_DI_Pin, GPIO_PIN_SET);
  else
	HAL_GPIO_WritePin(EEPROM_DI_GPIO_Port, EEPROM_DI_Pin, GPIO_PIN_RESET);
  strobe_sck();

  // write opcode bit 2
  if (code & 0x01)
	HAL_GPIO_WritePin(EEPROM_DI_GPIO_Port, EEPROM_DI_Pin, GPIO_PIN_SET);
  else
	HAL_GPIO_WritePin(EEPROM_DI_GPIO_Port, EEPROM_DI_Pin, GPIO_PIN_RESET);
  strobe_sck();
}

void Eeprom_93C86_socket::put_address(uint16_t address)
{
	if (address > MAX_ADDRESS)
		address = MAX_ADDRESS;

  for (uint8_t i=0; i < ADDRESS_BITS; i++)
	{
	  if (address & ADDRESS_MASK)
		HAL_GPIO_WritePin(EEPROM_DI_GPIO_Port, EEPROM_DI_Pin, GPIO_PIN_SET);
	  else
		HAL_GPIO_WritePin(EEPROM_DI_GPIO_Port, EEPROM_DI_Pin, GPIO_PIN_RESET);
	  strobe_sck();

	  address = uint16_t (address << 1u);
	}
}

void Eeprom_93C86_socket::erase(uint16_t address)
{
  put_opcode(0x03);			// ERASE instruction
  put_address(address);

  put_to_standby();
}

void Eeprom_93C86_socket::eraseall(void)
{
  put_opcode(0x00);			// ERASE ALL instruction
  put_address(0x20);

  put_to_standby();
}

void Eeprom_93C86_socket::write_disable(void)
{
  put_opcode(0x00);			// ERASE WRITE DISABLE instruction
  put_address(0x00);

  put_to_standby();
}

void Eeprom_93C86_socket::write_enable(void)
{
  put_opcode(0x00);			// ERASE WRITE ENABLE instruction
  put_address(0x600);		// 93C86 / 8-bit: eleven bits

  put_to_standby();
}

uint8_t Eeprom_93C86_socket::read(uint16_t address)
{
  uint8_t databyte = 0x00;
  uint8_t mask     = 0x80; // 93C86 8-bit

  put_opcode(0x02);			// READ instruction
  put_address(address);

  strobe_sck();				// strobing here fixes a bit offset

  for (uint8_t i=0; i < 8; i++)
	{
	  if (HAL_GPIO_ReadPin(EEPROM_DO_GPIO_Port, EEPROM_DO_Pin) == GPIO_PIN_SET)
		  databyte = uint8_t (databyte | mask);

	  mask = uint8_t (mask >> 1);
	  strobe_sck();
	}

  put_to_standby();
  return databyte;
}

void Eeprom_93C86_socket::readBlock(uint16_t address, uint8_t *data, uint8_t len)
{
  uint8_t databyte = 0x00;
  uint8_t mask     = 0x80; // 93C86 8-bit

  put_opcode(0x02);			// READ instruction
  put_address(address);

  strobe_sck();				// strobing here fixes a bit offset

  for (uint8_t j=0; j < len; j++) {
	  for (uint8_t i=0; i < 8; i++)
	  {
		  if (HAL_GPIO_ReadPin(EEPROM_DO_GPIO_Port, EEPROM_DO_Pin) == GPIO_PIN_SET)
			  databyte = uint8_t (databyte | mask);

		  mask = uint8_t (mask >> 1);
		  strobe_sck();
	  }
	  data[j]  = databyte;
	  databyte = 0;
	  mask     = 0x80;
  }

  put_to_standby();
}

void Eeprom_93C86_socket::write(uint16_t address, uint8_t data)
{
  put_opcode(0x01);			// WRITE instruction
  put_address(address);

  for (uint8_t i=0; i < 8; i++)
	{
	  if (data & LAST_DATABIT)
		HAL_GPIO_WritePin(EEPROM_DI_GPIO_Port, EEPROM_DI_Pin, GPIO_PIN_SET);
	  else
		HAL_GPIO_WritePin(EEPROM_DI_GPIO_Port, EEPROM_DI_Pin, GPIO_PIN_RESET);

	  strobe_sck();
	  data = uint8_t (data << 1u);
	}

  put_to_standby();
  while(is_busy()) {  }; // blocks until byte is processed!!
}

void Eeprom_93C86_socket::writeBlock(uint16_t address, uint8_t* data, uint8_t len) {
	uint16_t tmpAddress = address;
	for (uint8_t i=0; i < len; i++) {
		write(tmpAddress, data[i]);
		tmpAddress++;
		//while(is_busy()) {  }; // done in write
	}
}

void Eeprom_93C86_socket::writeall(uint8_t data)
{
  put_opcode(0x00);			// WRITE ALL instruction
  put_address(0x10);

  for (uint8_t i=0; i < 8; i++)
	{
	  if (data & LAST_DATABIT)
		HAL_GPIO_WritePin(EEPROM_DI_GPIO_Port, EEPROM_DI_Pin, GPIO_PIN_SET);
	  else
		HAL_GPIO_WritePin(EEPROM_DI_GPIO_Port, EEPROM_DI_Pin, GPIO_PIN_RESET);

	  strobe_sck();
	  data = uint8_t (data << 1u);
	}

  put_to_standby();
}



