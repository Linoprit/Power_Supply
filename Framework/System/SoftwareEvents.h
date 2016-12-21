/*
 * SoftwareEvents.h
 *
 *  Created on: 28.10.2015
 *      Author: harald
 *
 *  NO multiple instances possible!
 */

#ifndef SYSTEM_NEWSOFTWAREEVENTS_H_
#define SYSTEM_NEWSOFTWAREEVENTS_H_

#include <stdint.h>





#ifdef __cplusplus

#include <stdlib.h>
#include "libraries/simpleRingbuffer.h"



// This many callbacks can hook in
const uint8_t EVENTS_TABLE_LEN  = 20;
// This many events can be buffered
const uint8_t newEVENTS_BUFFER_LEN = 10;


class SoftwareEvents_base;

class SoftwareEvents
{
public:
  enum Event_Names_enum {None, All, Tic_1ms, Tic_10ms, Tic_100ms,
	key_released, key_pressed, key_held};
  // type "All" is only allowed for listening!

  struct EventSet
  {
	SoftwareEvents_base *class_pointer;
	Event_Names_enum     listening_event_name;
  };


  SoftwareEvents ();

  void loop (void);

  static uint8_t hookIn (SoftwareEvents_base *class_pointer,
						 Event_Names_enum listening_event_name);

  static void hookOff (
	  uint8_t ID,
	  SoftwareEvents_base *class_pointer);

  static void hookOff (
	  SoftwareEvents_base *class_pointer,
	  Event_Names_enum event_name);

  static void sendEvent(Event_Names_enum event_name);
  static void checkTicks(uint32_t sysTick);


  //static EventSet EventTable[newEVENTS_TABLE_LEN];



private:
  static EventSet EventTable[EVENTS_TABLE_LEN];

  void execute_callbacks(Event_Names_enum event_name);

};


class SoftwareEvents_base
{
public:
  virtual void software_event_callback(
	  SoftwareEvents::Event_Names_enum event_name) = 0;

  virtual ~SoftwareEvents_base() { };
};

#endif


// C interface
#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void SoftwareEvents_checkTicks(uint32_t sysTick);
EXTERNC void SoftwareEvents_sendEvent(
	SoftwareEvents::Event_Names_enum event_name);

#undef EXTERNC


#endif /* SYSTEM_NEWSOFTWAREEVENTS_H_ */
