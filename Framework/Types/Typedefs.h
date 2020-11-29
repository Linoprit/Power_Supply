/*
 * Typedefs.h
 *
 *  Created on: 14.05.2020
 *      Author: harald
 */

#ifndef TYPES_TYPEDEFS_H_
#define TYPES_TYPEDEFS_H_


#define USOLL_ADJ_SETUP  0, 0.0f, 25.4f
#define ISOLL_ADJ_SETUP  0, 0.0f, 4.0f
#define TEMP_ADJ_SETUP	 0, 25.0f, 65.0f
#define RSHUNT_ADJ_SETUP 100, 4, 0.0001f, 0.2000f

#define USET_FIX_SETUP  0, 1, 0.0f, 25.4f
#define ISET_FIX_SETUP  0, 1, 0.0f, 8.2f

namespace encodeNButtons {
enum PowActive { PowOn = 0, PowOff = 1 };
enum StrtMemoryEnum { strtNone, strtMem1, strtMem2 };
enum InSourceEnum { inHigh, inLow, inAuto };
} // namespace encodeNButtons

namespace cLine {
enum ExecResult { exNone = 0, exEmptyCom, exSuccess, exUnknown };
constexpr uint32_t EMPTY_COMLINE_CRC = 2927135660;
} // namespace cLine

#endif /* TYPES_TYPEDEFS_H_ */
