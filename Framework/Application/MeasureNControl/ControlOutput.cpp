/*
 * ControlOutput.cpp
 *
 *  Created on: 07.06.2020
 *      Author: harald
 */

#include <Application/MeasureNControl/ControlOutput.h>
#include <Instances/Common.h>

namespace measureNControl {

ControlOutput::ControlOutput(DAC_HandleTypeDef* dacHandle, uint8_t dacChannel):
		_dacSocket 						{ dacHandle, dacChannel },
		_dacOutput 						{ &_dacSocket },
		_measSemErrorCount 	 	{ 0 },
		_encdSemErrorCount	 	{ 0 },
		_wasScreenSetup 			{ false }
{
}

void ControlOutput::cycle(const MeasuredData&	measuredData) {

	float Usoll = 0.0f;
	float Isoll = 0.0f;

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
				( (isActScreenSetup) && !(actScreen == encodeNButtons::scrCalib) )
				|| (!volatileData.isPowActive()) ;

		if( isPowActive )
		{
			Usoll = 0.0f;
			Isoll = 0.0f;
		} else {
			Usoll = volatileData.getUsoll().getFlt();
			Isoll = volatileData.getIsoll().getFlt();
		}

	_dacOutput.setValue_float(Usoll);



	osSemaphoreRelease(CtrTskDataSemHandle);
	} else {
		IncMeasSemErrorCount();
	}

	if( isError() || measuredData.isError() ) {
		_dacOutput.setValue_float(0.0f);
	}

	_wasScreenSetup = isActScreenSetup;

	UNUSED(measuredData);
	UNUSED(Isoll);
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

} /* namespace measureNControl */
