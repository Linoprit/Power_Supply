/*
 * Nokia_3310_Tests.cpp
 *
 *  Created on: 30.09.2015
 *      Author: harald
 */

#include "PCD8544_Tests.h"

#include "test_glcd.h"
#include "test_bitmaps.h"
#include "Instances/Common.h"

#define TIME_BETWEEN_TEST_MS 3000


// To run this tests, you must enable usage of all fonts
// in the file PCD8544_basis.h.


PCD8544_Tests::PCD8544_Tests(void)
{
  SPI_HandleTypeDef*
  spi 		= get_LCD_SPI();

  PCD8544_socket::spi_pinspack_type*
  lcd_pinspack = new PCD8544_socket::spi_pinspack_type
  {
	LCD_CS_GPIO_Port,
	LCD_CS_Pin,
	LCD_Reset_GPIO_Port,
	LCD_Reset_Pin,
	LCD_Data_Command_GPIO_Port,
	LCD_Data_Command_Pin,
	LCD_Background_LED_GPIO_Port,
	LCD_Background_LED_Pin
  };

  PCD8544_socket	*LCD_socket =
	  new PCD8544_socket(spi, lcd_pinspack);

  LCD_basis	=
	  new PCD8544_basis(LCD_socket);
  LCD_grfx  =
	  new PCD8544_graphics(LCD_socket);
}

PCD8544_Tests::~PCD8544_Tests(void)
{ }

void PCD8544_Tests::write_char_map(void)
{
  uint8_t i,j, char_width = LCD_basis->get_actual_fontwidth();
  uint8_t chars_per_line =  (DISPLAY_WIDTH_px - 1) / char_width;

  uint8_t blah = (DISPLAY_WIDTH_px - 1) / char_width;

  LCD_basis->clear();
  for(i=0; i<6; i++) // 5 lines, fixed
	{
	  for(j=0; j < chars_per_line; j++)
		{
		  LCD_basis->set_line_n_column(j*char_width,i);
		  LCD_basis->write_char(
			  i*chars_per_line+j+32, MENU_NORMAL);
		}
	}
}

void PCD8544_Tests::grfx_write_char_map(void)
{
  uint8_t i,j;
  uint8_t chars_per_line =
	  (DISPLAY_WIDTH_px-1) / LCD_grfx->get_actual_fontwidth();
  uint8_t lines = DISPLAY_HEIGHT_px /
	  LCD_grfx->get_actual_fontheight();

  for(i=0; i < lines; i++)
	{
	  for(j=0; j < chars_per_line; j++)
		{
		  LCD_grfx->setCursor(
			  j * LCD_grfx->get_actual_fontwidth(),
			  i * LCD_grfx->get_actual_fontheight());
		  LCD_grfx->write_char(
			  (char) i * chars_per_line + j + 32);
		}
	}
  LCD_grfx->display();
}


void PCD8544_Tests::grfx_show_text(void)
{
  LCD_grfx->clear();
  LCD_grfx->write_string(
	  0, 0, "Graphical Test\n with newline");
  LCD_grfx->write_string(
	  0, LCD_grfx->conv_line_2_y_pix(3), "Text from ROM.");
  LCD_grfx->display();
}


void PCD8544_Tests::show_text(void)
{
  LCD_basis->clear();
  LCD_basis->write_string(
	  0, 0, (const char*) "Direct Test", MENU_NORMAL);
  LCD_basis->write_string(
	  0, 2, (const char*) "Text from ROM.", MENU_NORMAL);
  LCD_basis->write_string(
	  0, 3, (char*) "Text from RAM.", MENU_NORMAL);
}


void PCD8544_Tests::Do_Display_Tests(void)
{
  while(1)
	{
	  //--------- direct tests -----------//

	  LCD_basis->switch_font(FONT_6x8);
	  LCD_basis->write_string(
		  0, 0, (const char*) "LCD Base Test");
	  Common::delay(TIME_BETWEEN_TEST_MS);

	  LCD_basis->switch_font(FONT_4x6);
	  show_text();
	  Common::delay(TIME_BETWEEN_TEST_MS);

	  LCD_basis->clear();
	  write_char_map();
	  Common::delay(TIME_BETWEEN_TEST_MS);

	  LCD_basis->switch_font(FONT_5x8);
	  show_text();
	  Common::delay(TIME_BETWEEN_TEST_MS);

	  LCD_basis->clear();
	  write_char_map();
	  Common::delay(TIME_BETWEEN_TEST_MS);

	  LCD_basis->switch_font(FONT_6x8);
	  show_text();
	  Common::delay(TIME_BETWEEN_TEST_MS);

	  LCD_basis->clear();
	  write_char_map();
	  Common::delay(TIME_BETWEEN_TEST_MS);

	  LCD_basis->switch_font(FONT_8x8);
	  show_text();
	  Common::delay(TIME_BETWEEN_TEST_MS);

	  LCD_basis->clear();
	  write_char_map();
	  Common::delay(TIME_BETWEEN_TEST_MS);

	  LCD_basis->switch_font(FONT_16x8);
	  show_text();
	  Common::delay(TIME_BETWEEN_TEST_MS);

	  LCD_basis->clear();
	  write_char_map();
	  Common::delay(TIME_BETWEEN_TEST_MS);

	  LCD_basis->clear();
	  LCD_basis->switch_font(FONT_5x8);
	  LCD_basis->draw_bitmap(
		  0,0, test_glcd_bmp, TEST_GLCD_WIDTH,TEST_GLCD_HEIGHT);
	  Common::delay(TIME_BETWEEN_TEST_MS);
	  LCD_basis->write_string(
		  10, 5, (char*) "Bitmap-Test", MENU_HIGHLIGHT );
	  Common::delay(TIME_BETWEEN_TEST_MS);

	  // write  temperature
	  LCD_grfx->clear();
	  LCD_basis->write_string_big(
		  10, 0, (char*) "+12.30", 0);
	  LCD_basis->write_string(
		  78, 1, (char*) "C", MENU_NORMAL);
	  LCD_basis->write_string(
		  5, 5, (char*) "Big-Font-Test", MENU_HIGHLIGHT );
	  Common::delay(TIME_BETWEEN_TEST_MS);


	  //--------- graphics tests -----------//
	  LCD_grfx->clear();
	  LCD_grfx->switch_font(FONT_6x8);
	  LCD_grfx->write_string(0,0, "LCD Graphic Test");
	  LCD_grfx->display();
	  Common::delay(TIME_BETWEEN_TEST_MS);

	  LCD_grfx->clear();
	  LCD_grfx->draw_bitmap(
		  0,0, &ada_fruit_bmp[0], 84,48, BLACK);
	  LCD_grfx->display();
	  Common::delay(TIME_BETWEEN_TEST_MS);

	  LCD_grfx->clear();
	  LCD_grfx->draw_bitmap(
		  0,0, test_glcd_bmp, 80,40, BLACK);
	  LCD_grfx->display();
	  Common::delay(TIME_BETWEEN_TEST_MS);

	  LCD_grfx->clear();
	  LCD_grfx->draw_filled_rectangle(10,10,20,20,BLACK);
	  LCD_grfx->draw_rectangle(30,20,20,20,BLACK);
	  LCD_grfx->draw_circle(40,24, 10, BLACK);
	  LCD_grfx->draw_filled_circle(60, 30, 10, BLACK);
	  LCD_grfx->draw_line(5,5,70,20, BLACK);
	  LCD_grfx->display();
	  Common::delay(TIME_BETWEEN_TEST_MS);

	  LCD_grfx->switch_font(FONT_4x6);
	  grfx_show_text();
	  Common::delay(TIME_BETWEEN_TEST_MS);

	  grfx_write_char_map();
	  Common::delay(TIME_BETWEEN_TEST_MS);

	  LCD_grfx->switch_font(FONT_5x8);
	  grfx_show_text();
	  Common::delay(TIME_BETWEEN_TEST_MS);

	  grfx_write_char_map();
	  Common::delay(TIME_BETWEEN_TEST_MS);
	  LCD_grfx->clear();

	  LCD_grfx->switch_font(FONT_6x8);
	  grfx_show_text();
	  Common::delay(TIME_BETWEEN_TEST_MS);

	  grfx_write_char_map();
	  Common::delay(TIME_BETWEEN_TEST_MS);
	  LCD_grfx->clear();

	  LCD_grfx->switch_font(FONT_8x8);
	  //grfx_show_text();
	  //Common::delay(TIME_BETWEEN_TEST_MS);

	  LCD_grfx->clear();
	  grfx_write_char_map();
	  Common::delay(TIME_BETWEEN_TEST_MS);
	  LCD_grfx->clear();

	  LCD_grfx->switch_font(FONT_16x8);
	  //grfx_show_text();
	  //Common::delay(TIME_BETWEEN_TEST_MS);

	  LCD_grfx->clear();
	  grfx_write_char_map();
	  Common::delay(TIME_BETWEEN_TEST_MS);

	  //LCD_grfx->clear();
	  // back to default font
	  LCD_grfx->switch_font(FONT_6x8);
	}

}
