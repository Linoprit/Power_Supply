/*
 * MeasureNControl.cpp
 *
 *  Created on: 07.06.2020
 *      Author: harald
 */

#include <Application/MeasureNControl/MeasureNControl.h>
#include <Application/EncodeNButtons/EncodeNButtons.h>
#include <Instances/Common.h>
#include <new>



namespace measureNControl {

void MeasureNControl::init(void) {
	new (&instance()) MeasureNControl();
}

MeasureNControl& MeasureNControl::instance(void) {
	static MeasureNControl measureNControl;
	return measureNControl;
}


MeasureNControl::MeasureNControl():
	_measuredData 	{ get_hi2c3(), get_hadc3() },
	_controlOutput 	{ get_hdac1(), 1u } // DAC channel 1
{
}

void MeasureNControl::cycle() {

	_measuredData.cycle();
	_controlOutput.cycle(_measuredData);


}


} /* namespace measureNControl */
