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

class ControlOutput:
	ISR_callback {

public:
	ControlOutput(DAC_HandleTypeDef* dacHandle, uint8_t dacChannel);
	virtual ~ControlOutput() { };

	void cycle(const MeasuredData&	measuredData);

	bool isError(void)	const;

	void ISR_callback_fcn();
private:
	DAC_socket		_dacSocket;
	DacOutput		_dacOutput;
	uint8_t			_measSemErrorCount; 	// MeasuredData semaphore error count
	uint8_t			_encdSemErrorCount;		// encoder data  semaphore error count
	bool			_wasScreenSetup;
	float			_esum;					// PI error-sum
	//float 			_ealt;					// PID old error
	float			_Ushort;

	static constexpr float Kp = 1.0f;
	static constexpr float Ki = 0.05f;//0.1f;
	//static constexpr float Kd = 0.0f;
	static constexpr float esumSat = 25.4 / Ki; // esum saturation Umax / Ki

	float Calc_Rist(float Uist, float Iist, float Usoll, float Isoll);
	void Saturate_Esum(void);
	float Saturate_Uout(float Uout, float Usoll);
	void Control_HiLoVoltage(float Usoll, encodeNButtons::InSourceEnum inSource);
	void Update_Ushort(float Umax);
	void IncMeasSemErrorCount(void);
	void IncEncdSemErrorCount(void);

};

} /* namespace measureNControl */

#endif /* APPLICATION_MEASURENCONTROL_CONTROLOUTPUT_H_ */
