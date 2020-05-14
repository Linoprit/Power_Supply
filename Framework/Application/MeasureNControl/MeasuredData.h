/*
 * MeasuredData.h
 *
 *  Created on: 03.05.2020
 *      Author: harald
 */

#ifndef APPLICATION_MEASURENCONTROL_MEASUREDDATA_H_
#define APPLICATION_MEASURENCONTROL_MEASUREDDATA_H_

#include <Types/ExtFloat.h>


namespace measureNControl {

class MeasuredData {
public:
	MeasuredData();
	virtual ~MeasuredData();



private:
	ExtFloat 		_Uist;
	ExtFloat		_Iist;
	ExtFloat		_Ushunt;
	ExtFloat		_Pout;
	ExtFloat		_Ttrafo;
	ExtFloat		_Tendstufe;
	ExtFloat		_Uinput;
	ExtFloat		_Pwaste;

};

} /* namespace measureNControl */

#endif /* APPLICATION_MEASURENCONTROL_MEASUREDDATA_H_ */
