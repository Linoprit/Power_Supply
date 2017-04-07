/*
 * DAC_out.h
 *
 *  Created on: 02.04.2017
 *      Author: harald
 */

#ifndef CONTROLLER_DAC_SOCKET_H_
#define CONTROLLER_DAC_SOCKET_H_

#include <stdint.h>
#include "Instances/Common.h"



class DAC_socket
{
public:
  DAC_socket ();
  virtual
  ~DAC_socket ();

  void set(uint16_t value);


};

#endif /* CONTROLLER_DAC_SOCKET_H_ */
