/*
 * Nokia_3310_bitbanging.cpp
 *
 *  Created on: 18.09.2015
 *      Author: harald
 */


#include "PCD8544_socket.h"


/**
 * Initializes the ports to which the Nokia 3310
 * graphic display is conneted to
 *
 * Parameters:
 *
 */
PCD8544_socket::PCD8544_socket(SPI_HandleTypeDef* spi,
							   spi_pinspack_type* lcd_pinspack)
{
  this->spi 	 = spi;
  this->pinspack = lcd_pinspack;

}

void PCD8544_socket::write_byte(uint8_t data, uint8_t command_or_data)
{
  activate_CS();

  if (command_or_data == PCD8544_COMMAND)
    command_active();
  else
    data_active();

  send_byte(data);
  deactivate_CS();
}


bool PCD8544_socket::send_byte(uint8_t byte)
{
  while(HAL_SPI_GetState(spi) != HAL_SPI_STATE_READY)
    {
    }

  HAL_SPI_Transmit_IT(spi, &byte, 1);

  return true;
}
