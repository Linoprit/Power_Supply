/*
 * MeasuredData.h
 *
 *  Created on: 03.05.2020
 *      Author: harald
 */

#ifndef APPLICATION_MEASURENCONTROL_MEASUREDDATA_H_
#define APPLICATION_MEASURENCONTROL_MEASUREDDATA_H_


#include <Types/ExtFloat.h>
#include <Instances/Common.h>
#include <Devices/INA226/Autofox_INA226.h>
#include <Sockets/ADC_socket.h>
#include "main.h"


namespace measureNControl {

class MeasuredData {
public:
	MeasuredData(I2C_HandleTypeDef* I2Csocket, ADC_HandleTypeDef* hadc);
	virtual ~MeasuredData() { };

	void cycle (void);

	ExtFloat get_Uist() 		const { return _Uist; 			};
	ExtFloat get_Iist() 		const { return _Iist;				};
	ExtFloat get_Ushunt() 		const { return _Ushunt; 		};
	ExtFloat get_Pout() 		const { return _Pout;     	};
	ExtFloat get_Ttrafo() 		const { return _Ttrafo;  		};
	ExtFloat get_Tendstufe() 	const { return _Tendstufe;	};
	ExtFloat get_Uinput() 		const { return _Uinput;    	};
	ExtFloat get_Pwaste() 		const { return _Pwaste;   	};
	bool	 isError()			const { return (_SemErrorCount >= MAX_SEM_ERROR_COUNT); };


private:
	void setNewCurrentLimit(float iSoll_flt, int32_t iSoll_int);

	I2C_HandleTypeDef*			_I2Csocket;
	ADC_socket*  				_adcSocket;
	AutoFox_INA226    			_ina226;

	uint8_t			_SemErrorCount;

	ExtFloat 		_Uist;
	ExtFloat		_Iist;
	ExtFloat		_Ushunt;
	ExtFloat		_Pout;
	ExtFloat		_Ttrafo;
	ExtFloat		_Tendstufe;
	ExtFloat		_Uinput;
	ExtFloat		_Pwaste;
	int32_t			_old_Isoll;

	// TODO remove counter for debug
	uint8_t counter;
};

} /* namespace measureNControl */

#endif /* APPLICATION_MEASURENCONTROL_MEASUREDDATA_H_ */
