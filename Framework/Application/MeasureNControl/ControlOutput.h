/*
 * ControlOutput.h
 *
 *  Created on: 07.06.2020
 *      Author: harald
 */

#ifndef APPLICATION_MEASURENCONTROL_CONTROLOUTPUT_H_
#define APPLICATION_MEASURENCONTROL_CONTROLOUTPUT_H_

#include "main.h"
#include <Types/DacOutput.h>
#include <Application/EncodeNButtons/EncodeNButtons.h>
#include "MeasuredData.h"


namespace measureNControl {

class ControlOutput {
public:
	ControlOutput(DAC_HandleTypeDef* dacHandle, uint8_t dacChannel);
	virtual ~ControlOutput() { };

	void cycle(const MeasuredData&	measuredData);

	bool		 isError(void)				const;

private:
	DAC_socket		_dacSocket;
	DacOutput			_dacOutput;
	uint8_t				_measSemErrorCount; 	// MeasuredData semaphore error count
	uint8_t				_encdSemErrorCount;		// encoder data  semaphore error count
	bool					_wasScreenSetup;

	void IncMeasSemErrorCount(void);
	void IncEncdSemErrorCount(void);

};

} /* namespace measureNControl */

#endif /* APPLICATION_MEASURENCONTROL_CONTROLOUTPUT_H_ */
