/*
 * Rotary_Encoder_socket.h
 *
 *  Created on: 31.12.2016
 *      Author: harald
 */

#ifndef DEVICES_ROTARY_ENCODER_ROTARY_ENCODER_SOCKET_H_
#define DEVICES_ROTARY_ENCODER_ROTARY_ENCODER_SOCKET_H_

#include <System/RX_interface.h>
#include "Instances/callbacks.h"
#include "Instances/callbacks.h"
#include "stm32f3xx_hal.h"

namespace rotaryEncoder {

/* in this special case, we use a
   standard device, with zero address */
// TODO put this into the constructor
#define BASE_ADDRESS ADDR_PCF8574
#define HW_ADDRESS   HW_ADDRESS_0

// PCF8574
/* base addresses of the two derivates */
#define ADDR_PCF8574    0x40 /* 01000000 */
#define ADDR_PCF8574_A  0x70 /* 01110000 */

/* possible hardware-addresses of the device */
#define HW_ADDRESS_0 0x00 /* A2=0 A1=0 A0=0 */
#define HW_ADDRESS_1 0x01 /* A2=0 A1=0 A0=1 */
#define HW_ADDRESS_2 0x02 /* A2=0 A1=1 A0=0 */
#define HW_ADDRESS_3 0x03 /* A2=0 A1=1 A0=1 */
#define HW_ADDRESS_4 0x04 /* A2=1 A1=0 A0=0 */
#define HW_ADDRESS_5 0x05 /* A2=1 A1=0 A0=1 */
#define HW_ADDRESS_6 0x06 /* A2=1 A1=1 A0=0 */
#define HW_ADDRESS_7 0x07 /* A2=1 A1=1 A0=1 */


constexpr uint32_t Timeout			  			= 10; // ms?
constexpr uint8_t  socketQueueLen				= 8;
constexpr uint8_t  device_address		  	= ( BASE_ADDRESS | (HW_ADDRESS << 1) );


class Rotary_Encoder_socket:
		ISR_callback,
		RX_interface
{
public:
			Rotary_Encoder_socket ();
			Rotary_Encoder_socket (I2C_HandleTypeDef* i2c_handle);
			virtual
			~Rotary_Encoder_socket ();

			// ISR_callback
			void ISR_callback_fcn(void);

			// RX_interface
			SimpleQueue<uint8_t>* get_rx_queue();

private:
			SimpleQueue<uint8_t> 	_ringbuffer;
			I2C_HandleTypeDef* 		_i2c_handle;

};

}
#endif /* DEVICES_ROTARY_ENCODER_ROTARY_ENCODER_SOCKET_H_ */
