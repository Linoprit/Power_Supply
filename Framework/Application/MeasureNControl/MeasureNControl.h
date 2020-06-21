/*
 * MeasureNControl.h
 *
 *  Created on: 07.06.2020
 *      Author: harald
 */

#ifndef APPLICATION_MEASURENCONTROL_MEASURENCONTROL_H_
#define APPLICATION_MEASURENCONTROL_MEASURENCONTROL_H_

#include "MeasuredData.h"
#include "ControlOutput.h"


namespace measureNControl {

class MeasureNControl {
public:
	MeasureNControl();
	virtual ~MeasureNControl() { };

	void init(void);
	static MeasureNControl& instance(void);
	void cycle (void);

	const MeasuredData	getMeasuredData(void) 	const { return _measuredData; 	};
	const ControlOutput getControlOutput(void) 	const { return _controlOutput; 	};

private:
	MeasuredData			_measuredData;
	ControlOutput			_controlOutput;

};

} /* namespace measureNControl */

#endif /* APPLICATION_MEASURENCONTROL_MEASURENCONTROL_H_ */
