/*
 * EncodeNButtons.h
 *
 *  Created on: 23.02.2020
 *      Author: harald
 */

#ifndef TASKS_ENCODENBUTTONSTSK_H_
#define TASKS_ENCODENBUTTONSTSK_H_

// C interface
#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void StrtEncoderNButtons(void *argument);

#undef EXTERNC

#ifdef __cplusplus

// put cpp includes here!!




#endif // C interface
#endif /* TASKS_ENCODENBUTTONSTSK_H_ */
