/*
 * newSoftwareTimer.cpp
 *
 *  Created on: 27.10.2015
 *      Author: harald
 */

#include "SoftwareTimer.h"


SoftwareTimer::SoftwareTimer (
    uint32_t duration,
    SoftwareTimer_base *class_pointer,
    SoftwareEvents::Event_Names_enum listening_event)
{
  this->class_pointer 	     = class_pointer;
  this->duration             = duration;
  this->listening_event      = listening_event;
  counter = 0;

  SoftwareEvents::hookIn(this, listening_event);

  counter_state = running;
}


SoftwareTimer::~SoftwareTimer(){ };


void SoftwareTimer::software_event_callback(
    SoftwareEvents::Event_Names_enum event_name __attribute__((unused)))
{

  if (counter_state == stopped)
    return;

  counter++;
  if (counter >= duration)
    {
      counter = 0;

      class_pointer->timer_hit_callback();
    }
}


void SoftwareTimer::set_listening_event(
    SoftwareEvents::Event_Names_enum event_name __attribute__((unused))__attribute__((unused)))
{
  SoftwareEvents::hookOff(this, listening_event);

  this->listening_event = listening_event;

  SoftwareEvents::hookIn(this, listening_event);
}

void SoftwareTimer::stop(void)
{
  counter_state = stopped;
}

void SoftwareTimer::restart(void)
{
  counter = 0;
  counter_state = running;
}

void SoftwareTimer::proceed(void)
{
  counter_state = running;
}






