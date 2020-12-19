/*
 * Comm_socket_RX_only.h
 *
 *  Created on: 29.03.2016
 *      Author: harald
 */

#ifndef DRIVERS_COMM_SOCKET_RX_only_H_
#define DRIVERS_COMM_SOCKET_RX_only_H_

#include "libraries/SimpleQueue.h"


class RX_interface
{
public:
  RX_interface() {};

  virtual ~RX_interface() {};

  virtual SimpleQueue<uint8_t>* get_rx_queue() 		= 0;

};

#endif /* DRIVERS_COMM_SOCKET_RX_only_H_ */
