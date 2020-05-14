/*
 * VolatileData.cpp
 *
 *  Created on: 03.05.2020
 *      Author: harald
 */

#include <Application/EncodeNButtons/VolatileData.h>

namespace encodeNButtons {

VolatileData::VolatileData():
	_Usoll 					{ USOLL_ADJ_SETUP },
	_Isoll 					{ ISOLL_ADJ_SETUP },
	_InSource 			{	inAuto },
	_PowActive			{ false },
	_UsollFineFlag	{ false },
	_IsollFineFlag	{ false }
{
	// TODO Auto-generated constructor stub

}

VolatileData::~VolatileData() {
	// TODO Auto-generated destructor stub
}

} /* namespace encodeNButtons */
