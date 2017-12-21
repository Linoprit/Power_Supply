/*
 * OMI_coordinator.h
 *
 *  Created on: 12.03.2017
 *      Author: harald
 */

#ifndef DISPLAY_OMI_COORDINATOR_H_
#define DISPLAY_OMI_COORDINATOR_H_

#include "System/SoftwareEvents.h"
#include "Screens.h"
#include "Menus.h"

#define SCREENS 0
#define MENUS  	1

class OMI_coordinator: SoftwareEvents_base
{
public:

  OMI_coordinator ();
  virtual ~OMI_coordinator ();

  void software_event_callback(SoftwareEvents::Event_Names_enum event_name);
  void loop_50ms(void);
  void loop_5ms(void);


private:
  Screens* 	screen_class;
  Menus*	menu_class;

  uint8_t actv_dspl;
  SoftwareEvents::Event_Names_enum 	old_event;

};

#endif /* DISPLAY_OMI_COORDINATOR_H_ */
