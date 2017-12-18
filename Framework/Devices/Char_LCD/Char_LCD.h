/*
 * Char_LCD.h
 *
 *  Created on: 08.01.2017
 *      Author: harald
 */

#ifndef DEVICES_CHAR_LCD_CHAR_LCD_H_
#define DEVICES_CHAR_LCD_CHAR_LCD_H_

#include "Char_LCD_socket.h"

/* This is the size of the display */
// display 16x2
#define TWO_LINES
#define LCD_BUFFER_LEN 16

// display 20x4
//#define FOUR_LINES
//#define LCD_BUFFER_LEN 20


// refresh timer (in [ms])
#define REFRESH_CYCLE_TIME 100

/* DDRAM adresses */
#ifdef TWO_LINES
// two line LCD
#define LCD_LINES      2
#define LINE_1         0x80	      /*! Adresse erste  Zeile, erste Spalte */
#define LINE_2	       0xc0	      /*! Adresse zweite Zeile, erste Spalte */
#endif

#ifdef FOUR_LINES
// four line LCD
#define LCD_LINES      4
#define LINE_1         0x80	      /*! Adresse erste  Zeile, erste Spalte */
#define LINE_2	       0xC0	      /*! Adresse zweite Zeile, erste Spalte */
#define LINE_3         0x94	      /*! Adresse dritte Zeile, erste Spalte */
#define LINE_4	       0xD4	      /*! Adresse vierte Zeile, erste Spalte */
#endif
// 0 - 64 - 94 - 84

/* Commads */
#define LCD_CLR         1             /*! Clear display                      */
#define LCD_HOME        2             /*! Cursor home                        */
#define LCD_DATALENGTH (32+16)        /*! Data length 8 bit                  */
#define LCD_2LINES     (32+16+8+4)    /*! two lines, 5x10 dots */
#define LCD_MVCURSOR   (4+2)          /*! Increment cursor, Move cursor      */
#define LCD_CURSORON   (8+4+2+1)      /*! Cursor, Blink, Display on          */
#define LCD_CURSOROFF  (8+4+0+0)      /*! Cursor, Blink, off; Display on     */
#define LCD_RGTSHFT    (16+8+4)	      /*! Display shift Right                */
#define LCD_LFTSHFT    (16+8+0)	      /*! Display shift Left                 */

/* this is the interface-type */
typedef char buffer_lines_type[LCD_LINES][LCD_BUFFER_LEN];


class Char_LCD
{
public:

  Char_LCD (Char_LCD_socket* lcd_socket_in);
  virtual
  ~Char_LCD ();

  void init();
  void cycle(void);
  void display_step(void); // displays on char per step, nonblocking!
  void display_line(uint8_t line_nr); // first line is 0, blocking.
  void display(void); // displays whole buffer, blocking
  void clear(void);
  char* select_line(uint8_t line_nr); // sends address byte


  buffer_lines_type* get_buffer_lines_ptr(void);

  // put data to be displayed in here
  buffer_lines_type buffer_lines;

private:
  Char_LCD_socket* lcd_socket;

};

#endif /* DEVICES_CHAR_LCD_CHAR_LCD_H_ */
