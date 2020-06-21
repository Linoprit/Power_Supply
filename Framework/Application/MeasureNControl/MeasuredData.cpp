/*
 * MeasuredData.cpp
 *
 *  Created on: 03.05.2020
 *      Author: harald
 */

#include <Application/MeasureNControl/MeasuredData.h>
#include <Application/EncodeNButtons/EncodeNButtons.h>
#include <main.h>

//#include <System/uart_printf.h>


namespace measureNControl {

// TODO the i2cSocket is not used at the Moment, also the ins226.init is not configurable
MeasuredData::MeasuredData(I2C_HandleTypeDef* I2cHandle, ADC_HandleTypeDef* adcHandle):
	_I2Csocket 			{ I2cHandle },
	_adcSocket 			{ new ADC_socket(adcHandle, 1, 2) },
	_SemErrorCount 	{ 0 },
	counter 				{ 0 }
{
	//status theErrorCode =
	_ina226.Init(INA226_IC2_ADDRESS, SHUNT_RESISTOR_OHMS, MAX_CURRENT_AMPS);



}

void MeasuredData::cycle (void) {
	encodeNButtons::ScreenStateEnum			actScreen = encodeNButtons::scrValues;
	if ( osSemaphoreAcquire(EncdTskDataSemHandle, 2) == osOK ) {
		actScreen =
				encodeNButtons::EncodeNButtons::instance().getScreenState().getActSreen();
		osSemaphoreRelease(EncdTskDataSemHandle);
	}

	// one reading lasts aprox 230us
	float UistTmp = static_cast<float>(_ina226.GetBusVoltage_uV()) / 1E6;
	float IistTmp = static_cast<float>(_ina226.GetCurrent_uA()) / 1E6;
	_adcSocket->cycle_1ms();

	if ( osSemaphoreAcquire(CtrTskDataSemHandle, 2) == osOK ) {

		_SemErrorCount = 0;

		// TODO make the factor for Uin configurable, by a menu
		_Uinput.set(static_cast<float>(_adcSocket->get_measurement()[0]) / 50.45f);

		_Uist.set(UistTmp);
		_Iist.set(IistTmp);

		_Pout.set( _Uist.get() * _Iist.get() ) ;
		_Pwaste.set( (_Uinput.get() - _Uist.get()) * _Iist.get() );


		// TODO
		//		_Ttrafo;
		//		_Tendstufe;


		if(actScreen == encodeNButtons::scrCalib) {
			_Ushunt.set(static_cast<float>(_ina226.GetShuntVoltage_uV()) / 1E6 );
		}

		osSemaphoreRelease(CtrTskDataSemHandle);
	} else {
		_SemErrorCount++;
		if( _SemErrorCount >= MAX_SEM_ERROR_COUNT) {
			_SemErrorCount = MAX_SEM_ERROR_COUNT;
		}
	}

	/*{
		//constexpr uint8_t buffLen = 7;
		//char voltageBuff[buffLen] { '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
		//char currentBuff[buffLen] { '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
		//char powerBuff[buffLen]   { '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
		//char shuntBuff[buffLen]   { '\0', '\0', '\0', '\0', '\0', '\0', '\0'};

		int32_t theVoltage_mV = _ina226.GetBusVoltage_uV() / 1E3;
		int32_t thePower_mW 	= _ina226.GetPower_uW() / 1E3;
		int32_t theCurrent_mA = _ina226.GetCurrent_uA() / 1E3;
		int32_t theShunt_mV		= _ina226.GetShuntVoltage_uV() / 1E3;

		//HelpersLib::value2char(voltageBuff, buffLen-1, 3, theVoltage_mV);
		//HelpersLib::value2char(currentBuff, buffLen-1, 3, theCurrent_mA);
		//HelpersLib::value2char(powerBuff, buffLen-1, 3, thePower_mW);
		//HelpersLib::value2char(shuntBuff, buffLen-1, 3, theShunt_mV);


		switch(counter) {
		case 0:
			tx_printf("Bus Voltage:   %i mV\n", theVoltage_mV);
			break;
		case 1:
			tx_printf("Current:       %i mA\n", theCurrent_mA);
			break;
		case 2:
			tx_printf("ShuntVolt:     %i mV\n", theShunt_mV);
			break;
		case 3:
			tx_printf("Power:         %i mW\n\n", thePower_mW);
			break;
		default:
			break;
		}

		counter++;
		if(counter > 3)
			counter = 0;
	}*/


}




} /* namespace measureNControl */
