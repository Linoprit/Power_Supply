/*
 * ControlOutput.cpp
 *
 *  Created on: 07.06.2020
 *      Author: harald
 */

#include <Application/MeasureNControl/ControlOutput.h>
#include <Instances/Common.h>
#include <cfloat>

namespace measureNControl {

ControlOutput::ControlOutput(DAC_HandleTypeDef* dacHandle, uint8_t dacChannel):
		_dacSocket 						{ dacHandle, dacChannel },
		_dacOutput 						{ &_dacSocket },
		_measSemErrorCount 	 	{ 0 },
		_encdSemErrorCount	 	{ 0 },
		_wasScreenSetup 		{ false },
		_esum					{ 0.0f },
		_Ushort 				{ 0.0f }
		//_ealt					{ 0.0f }
{
	add_inaAlertPin_callback(this);
}

void ControlOutput::cycle(const MeasuredData&	measuredData) {
	encodeNButtons::ScreenStateEnum			actScreen = encodeNButtons::scrValues;;
	bool isActScreenSetup = true;

	osStatus_t encdStatus = osSemaphoreAcquire(EncdTskDataSemHandle, 2);

	const encodeNButtons::VolatileData volatileData =
			encodeNButtons::EncodeNButtons::instance().getVolData();
	const encodeNButtons::NonVolatileData nvData =
			encodeNButtons::EncodeNButtons::instance().getNvData();

	actScreen =
			encodeNButtons::EncodeNButtons::instance().getScreenState().getActSreen();
	isActScreenSetup =
		encodeNButtons::EncodeNButtons::instance().getScreenState().isActScreenSetup();

	osSemaphoreRelease(EncdTskDataSemHandle);

	if ( encdStatus == osOK ) {
		_encdSemErrorCount= 0;
	}	else {
		IncEncdSemErrorCount();
	}

	if ( osSemaphoreAcquire(CtrTskDataSemHandle, 2) == osOK ) {
		_measSemErrorCount = 0;

		const bool isPowActive =
				(volatileData.isPowActive()) &&
				( (!isActScreenSetup) || (actScreen == encodeNButtons::scrCalib) );

		Update_Ushort(volatileData.getUsoll().getMaxFlt());

		float Usoll = 0.0f;
		float Isoll = 0.0f;
		if( isPowActive )
		{
			Isoll = volatileData.getIsoll().getFlt();
			if (Isoll < 0.05) {
				Usoll = 0.0f;
			} else {
				Usoll = fmin(_Ushort, volatileData.getUsoll().getFlt());
			}
		}

		float Iist  = measuredData.get_Iist().get();
		float Uist	= measuredData.get_Uist().get();
		float Rist 	= Calc_Rist(Uist, Iist, Usoll, Isoll);
		float Umoegl = Rist * Isoll;

		float uDiff = 0.0f;
		if((Umoegl > Usoll) || (Iist < 0.05f)){
			uDiff = (Usoll - Uist); // Spannungsregler
		} else {
			uDiff = (Isoll - Iist) * Rist; // Stromregler
		}

		_esum = _esum + uDiff;
		Saturate_Esum();
		float Uout = Kp * uDiff + Ki * _esum; // PI-Regler
		//float Uout = Kp * uDiff + Ki * _esum + Kd * (uDiff - _ealt); // PID-Regler
		//_ealt = uDiff;

		Uout = Saturate_Uout(Uout, Usoll);
		Control_HiLoVoltage(Uout, volatileData.getInSource());
		_dacOutput.setValue_float(Uout);

		osSemaphoreRelease(CtrTskDataSemHandle);
	} else {
		IncMeasSemErrorCount();
	}

	if( isError() || measuredData.isError() ) {
		_dacOutput.setValue_float(0.0f);
	}

	_wasScreenSetup = isActScreenSetup;
}

void ControlOutput::Update_Ushort(float Umax) {
	if (_Ushort < Umax) {
		_Ushort = _Ushort + 0.02f;
	}
}

void ControlOutput::Control_HiLoVoltage(float Usoll, encodeNButtons::InSourceEnum inSource) {
	if (inSource == encodeNButtons::inHigh) {
		HAL_GPIO_WritePin(Voltage_HI_LO_GPIO_Port, Voltage_HI_LO_Pin, GPIO_PIN_SET);
	}
	else if (inSource == encodeNButtons::inLow) {
		HAL_GPIO_WritePin(Voltage_HI_LO_GPIO_Port, Voltage_HI_LO_Pin, GPIO_PIN_RESET);
	} else {
		if (Usoll > 9.5f) {
			HAL_GPIO_WritePin(Voltage_HI_LO_GPIO_Port, Voltage_HI_LO_Pin, GPIO_PIN_SET);
		}
		if(Usoll < 8.0f) {
			HAL_GPIO_WritePin(Voltage_HI_LO_GPIO_Port, Voltage_HI_LO_Pin, GPIO_PIN_RESET);
		}
	}
}

void ControlOutput::Saturate_Esum(void){
	if(_esum > esumSat) {
		_esum = esumSat;
	}
	if (_esum < -esumSat) {
		_esum = -esumSat;
	}
}

float ControlOutput::Saturate_Uout(float Uout, float Usoll) {
	float result = Uout;
	float Usat = Usoll * 1.2f;
	if(Uout > Usat) {
		result = Usat;
	}
	if (Uout < 0.0) {
		result = 0.0;
	}
	return result;
}

float ControlOutput::Calc_Rist(float Uist, float Iist, float Usoll, float Isoll) {
	float Rist		= FLT_MAX;
	if((Uist < 0.05) && (Iist < 0.05) && (Isoll > 0.05) && (Usoll > 0.05) ) {
		Rist = 0.5f; // avoid start-up-problem
	} else {
		Iist = fmax(fabs(Iist), 0.01); // avoid div by zero
		Rist = Uist / Iist;
	}
	return Rist;
}

void ControlOutput::IncMeasSemErrorCount(void){
	_measSemErrorCount++;
	if(_measSemErrorCount >= MAX_SEM_ERROR_COUNT) {
		_measSemErrorCount = MAX_SEM_ERROR_COUNT;
	}
}

void ControlOutput::IncEncdSemErrorCount(void){
	_encdSemErrorCount++;
	if(_encdSemErrorCount >= MAX_SEM_ERROR_COUNT) {
		_encdSemErrorCount = MAX_SEM_ERROR_COUNT;
	}
}

bool ControlOutput::isError(void)				const {
	bool isError =
			(_measSemErrorCount >= MAX_SEM_ERROR_COUNT)
			|| (_encdSemErrorCount >= MAX_SEM_ERROR_COUNT) ;

	return isError ;
}

void ControlOutput::ISR_callback_fcn() {
	_dacOutput.setValue_float(0.0f);
	_Ushort = 0.0;

	// TODO remove
	//HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

}

} /* namespace measureNControl */
