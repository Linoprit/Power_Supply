/*
 * scheduler.h
 *
 *  Created on: 09.12.2016
 *      Author: harald
 */

#ifndef SYSTEM_SCHEDULER_H_
#define SYSTEM_SCHEDULER_H_


#include <stdint.h>

// C interface
#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void scheduler_cycle(void);
EXTERNC void scheduler_init(void);

#undef EXTERNC



#ifdef __cplusplus


class scheduler
{
public:
  scheduler (void);
  virtual ~scheduler (void);

  static void cycle (void);
  static void init (void);

  static uint32_t old_Tick;
};

#endif // C interface
#endif /* SYSTEM_SCHEDULER_H_ */