/*
 * OMI_coordinator.h
 *
 *  Created on: 12.03.2017
 *      Author: harald
 */

#ifndef OMI_OMI_COORDINATOR_H_
#define OMI_OMI_COORDINATOR_H_

#include <OMI/Menus.h>
#include <OMI/Screens.h>
#include "System/SoftwareEvents.h"

#define SCREENS 0
#define MENUS  	1

class OMI_coordinator: SoftwareEvents_base
{
public:

  OMI_coordinator ();
  virtual ~OMI_coordinator ();

  void software_event_callback(SoftwareEvents::Event_Names_enum event_name);
  void update_values(void);
  void loop_50ms(void);
  void loop_5ms(void);


private:
  Screens* 	screen_class;
  Menus*	menu_class;

  uint8_t actv_dspl;
  SoftwareEvents::Event_Names_enum 	old_event;

};

#endif /* OMI_OMI_COORDINATOR_H_ */
