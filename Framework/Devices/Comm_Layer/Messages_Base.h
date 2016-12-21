/*
 * Messages_Base.h
 *
 *  Created on: 03.02.2016
 *      Author: harald
 */

#ifndef SYSTEM_COMM_LAYER_MESSAGES_BASE_H_
#define SYSTEM_COMM_LAYER_MESSAGES_BASE_H_

#include <stdint.h>

#ifdef QT_TARGET
#include <QDebug>
#define ECHO_TEST_ENABLE
#else
//#include <util/crc16.h>
//#include "../../ApplicationModules/PPM_InOut/PPM_bitbanging.h"
#endif


#define	 PACKED	__attribute__ ((packed))

#define SYNC_CHAR_1          0 // DEC
#define SYNC_CHAR_2        255 // DEC
#define CHK_SUM_LENGTH       1
#define MAX_MESSAGE_LEN     30 // Maximum bytelength of received message

#ifdef QT_TARGET
uint8_t _crc_ibutton_update(uint8_t crc, uint8_t data);
#else
// TODO use hardware crc
uint8_t _crc_ibutton_update(uint8_t crc, uint8_t data);
#endif



//------------ do not change ------------
// header part of serial messages
typedef struct PACKED
{
  uint8_t  msg_class      : 8;
  uint8_t  msg_id         : 8;
  uint16_t payload_len    : 16;
} rcv_header_struct;
const uint8_t HEADER_LENGTH = sizeof(rcv_header_struct);

#define MSG_STRUCT(payload_type)			\
	typedef struct PACKED					\
	{										\
	uint8_t               sync_char[2];		\
	rcv_header_struct 	header;				\
	payload_type 	payload;				\
	uint8_t               checksum;			\
	} msg_##payload_type;					\
	const uint8_t MSG_##payload_type##_LEN = sizeof(msg_##payload_type)
//--------------------------------------


#define PPM_INOUT_CLASS		3
static const uint8_t MAX_PPM_CHANNELS = 10;

enum ppm_command_enum { write2eeprom, send_stored_params };
#define PPM_COMMAND_ID		1
typedef struct PACKED
{
  ppm_command_enum     command;
} ppm_command_type;
MSG_STRUCT(ppm_command_type);

#define PPM_RAW_CHANNELS_ID	5
typedef struct PACKED
{
  uint16_t value[MAX_PPM_CHANNELS];
} ppm_raw_channels_type;
MSG_STRUCT(ppm_raw_channels_type);

#define PPM_NORM_CHANNELS_ID	7
typedef struct PACKED
{
  uint16_t value[MAX_PPM_CHANNELS];
} ppm_norm_channels_type;
MSG_STRUCT(ppm_norm_channels_type);

#define PPM_CH_PARAMS_ID	11
typedef struct PACKED
{
  int16_t 	center;
  int16_t	range_half;
}ch_param_type;

typedef struct PACKED
{
  ch_param_type     stick[4];
  ch_param_type     others[MAX_PPM_CHANNELS - 4 ];
} ppm_ch_params_type;
MSG_STRUCT(ppm_ch_params_type);

#define PPM_CH_MAPPING_ID	13
typedef struct PACKED
{
  uint8_t	Roll		:4; // Aileron
  uint8_t	Pitch		:4;	// Elevator
  uint8_t   Yaw			:4;	// Rudder
  uint8_t   Throttle	:4;
} ppm_ch_mapping_type;
MSG_STRUCT(ppm_ch_mapping_type);

#ifdef  ECHO_TEST_ENABLE
#define ECHO_TEST_CLASS     254
#define ECHO_TEST_ID        1
typedef struct PACKED
{
  uint8_t     value_1;
  uint16_t    value_2;
  int8_t      value_3;
  int16_t     value_4;
} echo_test_data_type;
MSG_STRUCT(echo_test_data_type);
#endif


class Messages_Base
{
public:
  static msg_ppm_command_type		msg_ppm_command;
  static msg_ppm_raw_channels_type	msg_ppm_raw_channels;
  static msg_ppm_norm_channels_type	msg_ppm_norm_channels;
  static msg_ppm_ch_params_type		msg_ppm_ch_params;
  static msg_ppm_ch_mapping_type	msg_ppm_ch_mapping;


  Messages_Base ();
  // we use init() instead the constructor in static classes
  static void init();

  static void 	 put_payload_to_struct(
	  uint8_t *msg_buf, rcv_header_struct *rcv_header);
  static uint8_t calc_checksum(
	  rcv_header_struct *rcv_header, uint8_t *msg_buffer);
  static uint8_t calc_checksum(
	  rcv_header_struct *rcv_header);

#ifdef  ECHO_TEST_ENABLE
  static msg_echo_test_data_type 	msg_echo_test_data_tx;
  static echo_test_data_type 		echo_test_data_rx;
#endif
};

#endif /* SYSTEM_COMM_LAYER_MESSAGES_BASE_H_ */


// just to remember...
/*typedef struct PACKED
{
  uint8_t               sync_char[2];
  rcv_header_struct 	header;
  ppm_command_type 	payload;
  uint8_t               checksum;
} msg_ppm_command_type;
const uint8_t MSG_PPM_COMMAND_LEN = sizeof(msg_ppm_command_type);
const uint8_t PPM_COMMAND_LEN = sizeof(ppm_command_type);*/

