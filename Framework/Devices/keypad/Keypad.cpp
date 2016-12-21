/*
 * Keypadbitbanging.cpp
 *
 *  Created on: 25.10.2015
 *      Author: harald
 */


#include "Keypad.h"
#include "System/callbacks.h"
#include "libraries/HelpersLib.h"



Keypad::Keypad (Keypad_socket *socket)
{
  this->socket = socket;

  timer = new SoftwareTimer(TimerDuration, this,
      SoftwareEvents::Tic_10ms);
  timer->stop();

  // tell the ISR-handler what to call, if a button was pressed
  keypad_callback_set((ISR_callback*) this);
  socket->setRowPort_Listening();
  socket->setColPort_Output();

  keyOpenCounter        = 0;
  keyPressedLoopCounter = 0;
  lastRawKey.col        = 0;
  lastRawKey.row        = 0;
  button_state          = bttn_released;

  rawKey_type tmp_raw_key;
  tmp_raw_key.col = default_keypmap_3x4_cols;
  tmp_raw_key.row = default_keypmap_3x4_rows;
  bindCharMap(
      (uint8_t *) default_keypmap_3x4, tmp_raw_key);

  tmp_raw_key.col = default_commandmap_3x4_cols;
  tmp_raw_key.row = default_commandmap_3x4_rows;

  bindCommandMap(
	  (uint8_t *) default_commandmap_3x4, tmp_raw_key);
}


void Keypad::callback_fcn(void)
{
  uint8_t countToRotate;
  uint8_t alignedVal;

  if (socket->getRowPort() == 0)
    return;

  // align row
  countToRotate =
      HelpersLib::findFirstSetBitFromRight(socket->keypad_pinspack->RowBitmask);
  alignedVal = socket->getRowPort() >> countToRotate;

  lastRawKey.row = HelpersLib::findFirstSetBitFromRight(
      alignedVal);

  keypad_callback_clear();
  socket->setColPort_Input();
  socket->setRowPort_Output();

  // align col
  countToRotate =
      HelpersLib::findFirstSetBitFromRight(socket->keypad_pinspack->ColBitmask);
  alignedVal = socket->getColPort() >> countToRotate;

  lastRawKey.col = HelpersLib::findFirstSetBitFromRight(
      alignedVal);

  SoftwareEvents::sendEvent(SoftwareEvents::key_pressed);
  button_state = bttn_pressed;
  timer->restart();
}


Keypad::button_state_enum Keypad::getActualKeyState(void)
{
  return button_state;
}

Keypad::rawKey_type* Keypad::getLastRawKey(void)
{
  return &lastRawKey;
}


void Keypad::timer_hit_callback(void)
{
  keyPressedLoopCounter++;

  // key is released
  if (socket->getColPort() == 0)
    keyOpenCounter++;

  // all keys released
  if (keyOpenCounter >= keyOpenCounter_max)
    {
      // reset listening-settings
	  keypad_callback_set((ISR_callback*) this);
      socket->setRowPort_Listening();
      socket->setColPort_Output();

      SoftwareEvents::sendEvent(SoftwareEvents::key_released);
      keyPressedLoopCounter = 0;
      keyOpenCounter        = 0;
      timer->stop();
      button_state = bttn_released;
      return;
     }

  if (keyPressedLoopCounter >= keyPressedLoopCounter_max)
    {
      SoftwareEvents::sendEvent(SoftwareEvents::key_held);
      button_state = bttn_held;
      keyPressedLoopCounter = 0;
    }
}


void Keypad::bindCommandMap(
    uint8_t *commandmap, rawKey_type nrOfCols_n_Rows)
{
  commandmap_ptr      = commandmap;
  commandmap_max_rows = nrOfCols_n_Rows.row;
  commandmap_max_cols = nrOfCols_n_Rows.col;
}

void Keypad::bindCharMap(
    uint8_t *keymap, rawKey_type nrOfCols_n_Rows)
{
  keymap_ptr      = keymap;
  keymap_max_rows = nrOfCols_n_Rows.row;
  keymap_max_cols = nrOfCols_n_Rows.col;
}

char Keypad::convertRaw2Char(rawKey_type* raw_key)
{
  uint8_t row = raw_key->row;
  uint8_t col = raw_key->col;

  if ( (row > keymap_max_rows) || (col > keymap_max_cols) )
    return ' ';

  return *(keymap_ptr + (row*keymap_max_cols) + col);
}

char Keypad::getLastChar(void)
{
  return convertRaw2Char(getLastRawKey());
}

char Keypad::getLastKeyCommand(void)
{
  return convertRaw2Command(getLastRawKey());
}


char Keypad::convertRaw2Command(rawKey_type* raw_key)
{
  uint8_t row = raw_key->row;
  uint8_t col = raw_key->col;

  if ( (row > commandmap_max_rows) || (col > commandmap_max_cols) )
    return KEY_SPACE;

  return *(commandmap_ptr + (row*commandmap_max_cols) + col);
}





