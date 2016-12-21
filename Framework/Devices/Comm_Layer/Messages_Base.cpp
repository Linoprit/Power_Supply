/*
 * Messages_Base.cpp
 *
 *  Created on: 03.02.2016
 *      Author: harald
 */

#include "Messages_Base.h"


msg_ppm_command_type 		Messages_Base::msg_ppm_command;
msg_ppm_raw_channels_type	Messages_Base::msg_ppm_raw_channels;
msg_ppm_norm_channels_type	Messages_Base::msg_ppm_norm_channels;
msg_ppm_ch_params_type		Messages_Base::msg_ppm_ch_params;
msg_ppm_ch_mapping_type		Messages_Base::msg_ppm_ch_mapping;

#ifdef  ECHO_TEST_ENABLE
echo_test_data_type     	Messages_Base::echo_test_data_rx;
msg_echo_test_data_type 	Messages_Base::msg_echo_test_data_tx;
#endif

Messages_Base::Messages_Base ()
{}

void Messages_Base::init()
{
  // prepare tx message headers
  msg_ppm_command.sync_char[0]      = SYNC_CHAR_1;
  msg_ppm_command.sync_char[1]      = SYNC_CHAR_2;
  msg_ppm_command.header.msg_class  = PPM_INOUT_CLASS;
  msg_ppm_command.header.msg_id     = PPM_COMMAND_ID;
  msg_ppm_command.header.payload_len = sizeof(ppm_command_type);

  msg_ppm_raw_channels.sync_char[0]      = SYNC_CHAR_1;
  msg_ppm_raw_channels.sync_char[1]      = SYNC_CHAR_2;
  msg_ppm_raw_channels.header.msg_class  = PPM_INOUT_CLASS;
  msg_ppm_raw_channels.header.msg_id     = PPM_RAW_CHANNELS_ID;
  msg_ppm_raw_channels.header.payload_len = sizeof(ppm_raw_channels_type);

  msg_ppm_norm_channels.sync_char[0]      = SYNC_CHAR_1;
  msg_ppm_norm_channels.sync_char[1]      = SYNC_CHAR_2;
  msg_ppm_norm_channels.header.msg_class  = PPM_INOUT_CLASS;
  msg_ppm_norm_channels.header.msg_id     = PPM_NORM_CHANNELS_ID;
  msg_ppm_norm_channels.header.payload_len = sizeof(ppm_norm_channels_type);

  msg_ppm_ch_params.sync_char[0]      = SYNC_CHAR_1;
  msg_ppm_ch_params.sync_char[1]      = SYNC_CHAR_2;
  msg_ppm_ch_params.header.msg_class  = PPM_INOUT_CLASS;
  msg_ppm_ch_params.header.msg_id     = PPM_CH_PARAMS_ID;
  msg_ppm_ch_params.header.payload_len = sizeof(ppm_ch_params_type);

  msg_ppm_ch_mapping.sync_char[0]      = SYNC_CHAR_1;
  msg_ppm_ch_mapping.sync_char[1]      = SYNC_CHAR_2;
  msg_ppm_ch_mapping.header.msg_class  = PPM_INOUT_CLASS;
  msg_ppm_ch_mapping.header.msg_id     = PPM_CH_MAPPING_ID;
  msg_ppm_ch_mapping.header.payload_len = sizeof(ppm_ch_mapping_type);
}

void Messages_Base::put_payload_to_struct(
    uint8_t *msg_buf, rcv_header_struct *rcv_header)
{
  uint8_t *pointer = 0;

  if (rcv_header->msg_class == PPM_INOUT_CLASS)
    {
      switch (rcv_header->msg_id)
        {
        case PPM_COMMAND_ID: // must use define!
          pointer = (uint8_t *) &Messages_Base::msg_ppm_command.payload;
          break;

        case PPM_RAW_CHANNELS_ID: // must use define!
          pointer = (uint8_t *) &Messages_Base::msg_ppm_raw_channels.payload;
          break;

        case PPM_NORM_CHANNELS_ID:
          pointer = (uint8_t *) &Messages_Base::msg_ppm_norm_channels.payload;
	  break;

        case PPM_CH_PARAMS_ID:
          pointer = (uint8_t *) &Messages_Base::msg_ppm_ch_params.payload;
	  break;

        case PPM_CH_MAPPING_ID:
          pointer = (uint8_t *) &Messages_Base::msg_ppm_ch_mapping.payload;
	  break;

        default:
          pointer = 0;
          break;
        }
    }

#ifdef  ECHO_TEST_ENABLE
  if (rcv_header->msg_class == ECHO_TEST_CLASS)
  {
      switch (rcv_header->msg_id)
      {
      case ECHO_TEST_ID:
          pointer = (uint8_t *) &Messages_Base::echo_test_data_rx;
          break;

      default:
          break;
      }
  }
#endif

  if (pointer != 0)
    {
      for (unsigned int i = 0; i < rcv_header->payload_len; i++)
        {
          *pointer = msg_buf[i + HEADER_LENGTH]; // payload is behind header
          pointer++;          
        }
    }
}


uint8_t Messages_Base::calc_checksum(rcv_header_struct *rcv_header)
{
    uint8_t* msg_buffer = (uint8_t*) rcv_header;
    return calc_checksum(rcv_header, msg_buffer);
}


uint8_t Messages_Base::calc_checksum(
	rcv_header_struct *rcv_header,
	uint8_t* msg_buffer)
{
    // use avr algorithm
    uint8_t i, crc = 0;

    // we must exclude the chksum byte at the end!
    for (i = 0; i < HEADER_LENGTH + rcv_header->payload_len; i++)
      {
        crc = _crc_ibutton_update(crc, *msg_buffer);
        msg_buffer++;
      }
    return crc;
}


//#ifdef QT_TARGET
// TODO use hardware crc
uint8_t _crc_ibutton_update(uint8_t crc, uint8_t data)
{
    uint8_t i;

    crc = crc ^ data;
    for (i = 0; i < 8; i++)
    {
        if (crc & 0x01)
            crc = (crc >> 1) ^ 0x8C;
        else
            crc >>= 1;
    }

    return crc;
}
//#endif
