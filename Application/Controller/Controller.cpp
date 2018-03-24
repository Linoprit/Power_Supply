/*
 * Controller.cpp
 *
 *  Created on: 02.04.2017
 *      Author: harald
 */

#include <Controller/Controller.h>
//#include <OMI/OMI_coordinator.h>
#include <Instances/Common.h>


Controller::Controller ()
{
  //IU_Value*	u_start	= Common::get_u_start();
  //IU_Value* i_start = Common::get_i_start();
}

Controller::~Controller () { }

void Controller::cycle_1ms()
{
   IU_Value*		u_soll	= Common::get_u_soll();
   IU_Value* 		i_soll	= Common::get_i_soll();
   HI_LO_Value* 	hi_lo	= Common::get_hi_lo();
   Value_Output* 	dac_out = Common::get_dac_output();

   dac_out->set_Value_float(u_soll->getValue());

   UNUSED(i_soll);
   UNUSED(hi_lo);


}
