/*
 * Comm_Layer_test.cpp
 *
 *  Created on: 22.12.2016
 *      Author: harald
 */

#include "Comm_Layer_test.h"
#include "Devices/Comm_Layer/Messages_Base.h"
#include "libraries/HelpersLib.h"


Comm_Layer_test::Comm_Layer_test ()
{
  comm_layer = Common::get_comm_layer();

}

Comm_Layer_test::~Comm_Layer_test ()
{
}

void Comm_Layer_test::loop(void)
{
  static  uint32_t 	old_counter = 0;
  SoftwareEvents* 	sw_events 	= Common::get_sw_events();

  // must be initialised in framework
  LCD		  = Common::get_LCD_grfx();
  LCD->switch_font(FONT_5x8);

  Keypad*			keypad = Common::get_keypad();

  textbuffer_len = 17;
  textbuffer = (char*)malloc(textbuffer_len * sizeof (char));



  while (1)
	{
	  sw_events->loop();

	  if (Common::get_tick() - old_counter  > 100)
		{
		  Messages_Base::msg_test_01_tx.payload.counter ++;
		  Messages_Base::msg_test_01_tx.payload.value_2 =
			  (uint16_t)
			  Messages_Base::msg_test_01_tx.payload.counter / 2;
		  Messages_Base::msg_test_01_tx.payload.value_3 =
			  (int8_t)
			  Messages_Base::msg_test_01_tx.payload.counter / 8;
		  Messages_Base::msg_test_01_tx.payload.value_4 =
			  (int16_t)
			  Messages_Base::msg_test_01_tx.payload.counter / (-2);

		  comm_layer->pack_n_queue_msg(&Messages_Base::msg_test_01_tx.header);

		  Messages_Base::msg_test_02_tx.payload.counter =
			  Messages_Base::msg_test_01_tx.payload.counter /2;
		  Messages_Base::msg_test_02_tx.payload.value_2 =
			  (uint16_t)
			  Messages_Base::msg_test_02_tx.payload.counter / 2;
		  Messages_Base::msg_test_02_tx.payload.value_3 =
			  (int8_t)
			  Messages_Base::msg_test_02_tx.payload.counter / 8;
		  Messages_Base::msg_test_02_tx.payload.value_4 =
			  (int16_t)
			  Messages_Base::msg_test_02_tx.payload.counter / (-2);

		  comm_layer->pack_n_queue_msg(&Messages_Base::msg_test_02_tx.header);

		  Messages_Base::msg_test_03_tx.payload.counter =
			  Messages_Base::msg_test_01_tx.payload.counter /4;
		  Messages_Base::msg_test_03_tx.payload.value_2 =
			  (uint16_t)
			  Messages_Base::msg_test_03_tx.payload.counter / 2;
		  Messages_Base::msg_test_03_tx.payload.value_3 =
			  (int8_t)
			  Messages_Base::msg_test_03_tx.payload.counter / 8;
		  Messages_Base::msg_test_03_tx.payload.value_4 =
			  (int16_t)
			  Messages_Base::msg_test_03_tx.payload.counter / (-2);

		  comm_layer->pack_n_queue_msg(&Messages_Base::msg_test_03_tx.header);



		  // Display RX-Messages
		  clearTextbuffer();
		  strncpy(&textbuffer[0], (const char*) "test_01:", 8);
		  HelpersLib::value2char(
			  &textbuffer[8], 8, 0,
			  Messages_Base::test_01_rx.counter);
		  LCD->write_string(0, LCD->conv_line_2_y_pix(1), textbuffer);
		  clearTextbuffer();
		  HelpersLib::value2char(
			  &textbuffer[0], 4, 0,
			  Messages_Base::test_01_rx.value_2);
		  HelpersLib::value2char(
			  &textbuffer[5], 4, 0,
			  Messages_Base::test_01_rx.value_4);
		  HelpersLib::value2char(
			  &textbuffer[10], 4, 0,
			  Messages_Base::test_01_rx.value_3);
		  LCD->write_string(0, LCD->conv_line_2_y_pix(2), textbuffer);


		  clearTextbuffer();
		  strncpy(&textbuffer[0], (const char*) "test_02:", 8);
		  HelpersLib::value2char(
			  &textbuffer[8], 8, 0,
			  Messages_Base::test_02_rx.counter);
		  LCD->write_string(0, LCD->conv_line_2_y_pix(3), textbuffer);
		  clearTextbuffer();
		  HelpersLib::value2char(
			  &textbuffer[0], 4, 0,
			  Messages_Base::test_02_rx.value_2);
		  HelpersLib::value2char(
			  &textbuffer[5], 4, 0,
			  Messages_Base::test_02_rx.value_4);
		  HelpersLib::value2char(
			  &textbuffer[10], 4, 0,
			  Messages_Base::test_02_rx.value_3);
		  LCD->write_string(0, LCD->conv_line_2_y_pix(4), textbuffer);


		  clearTextbuffer();
		  strncpy(&textbuffer[0], (const char*) "test_03:", 8);
		  HelpersLib::value2char(
			  &textbuffer[8], 8, 0,
			  Messages_Base::test_03_rx.counter);
		  LCD->write_string(0, LCD->conv_line_2_y_pix(5), textbuffer);
		  clearTextbuffer();
		  HelpersLib::value2char(
			  &textbuffer[0], 4, 0,
			  Messages_Base::test_03_rx.value_2);
		  HelpersLib::value2char(
			  &textbuffer[5], 4, 0,
			  Messages_Base::test_03_rx.value_4);
		  HelpersLib::value2char(
			  &textbuffer[10], 4, 0,
			  Messages_Base::test_03_rx.value_3);
		  LCD->write_string(0, LCD->conv_line_2_y_pix(6), textbuffer);


		  LCD->display();

		  old_counter = Common::get_tick();
		}



	}
}

void Comm_Layer_test::clearTextbuffer()
{
  for (uint8_t i=0; i < textbuffer_len; i++)
	textbuffer[i] = ' ';
  textbuffer[textbuffer_len-1] = '\0';
}

