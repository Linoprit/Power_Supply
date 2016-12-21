/*
 * SoftwareTimer.h
 *
 *  Created on: 27.10.2015
 *      Author: harald
 */

#ifndef SYSTEM_SOFTWARETIMER_H_
#define SYSTEM_SOFTWARETIMER_H_

#include <stdint.h>
#include "SoftwareEvents.h"


class SoftwareTimer_base
{
public:
  virtual void timer_hit_callback(void) = 0;
  virtual ~SoftwareTimer_base() {};
};

class SoftwareTimer: SoftwareEvents_base
{
public:

  SoftwareTimer (
      uint32_t duration,
      SoftwareTimer_base *class_pointer,
      SoftwareEvents::Event_Names_enum listening_event =
	  SoftwareEvents::Tic_1ms);

  ~SoftwareTimer();

  void software_event_callback(
      SoftwareEvents::Event_Names_enum event_name);
  void set_listening_event(
      SoftwareEvents::Event_Names_enum event_name);

  void stop(void);
  void restart(void);
  void proceed(void);

private:
  enum timer_state_enum{stopped, running};
  timer_state_enum counter_state;
  uint32_t duration, counter;
  SoftwareTimer_base *class_pointer;
  SoftwareEvents::Event_Names_enum listening_event;
};

#endif /* SYSTEM_SOFTWARETIMER_H_ */
