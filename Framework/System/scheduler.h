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

#include <Interfaces/Value_PT1_filtered.h>


class scheduler
{
public:
  scheduler (void);
  virtual ~scheduler (void);

  static void cycle (void);
  static void init (void);
  static void update_pt1_values(void);

  static Value_PT1_filtered* getIistPt1 () { return Iist_pt1; }
  static Value_PT1_filtered* getTempPt1 () { return Temp_pt1; }
  static Value_PT1_filtered* getUinPt1 ()  { return Uin_pt1;  }
  static Value_PT1_filtered* getUistPt1 () { return Uist_pt1; }



private:
  static uint32_t old_tick;

  static Value_PT1_filtered* Uist_pt1;
  static Value_PT1_filtered* Iist_pt1;
  static Value_PT1_filtered* Uin_pt1;
  static Value_PT1_filtered* Temp_pt1;



  // TODO remove later
#define TEXT_BUF_LEN 6
  static uint8_t text_buf[TEXT_BUF_LEN];
  static void dbg_push_values(void);
  static void clear_text_buf(uint8_t* text_buf_in, uint8_t len);
  static void send_value(long int value);

};

#endif // C interface
#endif /* SYSTEM_SCHEDULER_H_ */
