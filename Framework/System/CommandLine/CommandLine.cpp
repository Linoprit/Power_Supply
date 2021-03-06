/*
 * commandLine.cpp
 *
 *  Created on: 05.11.2020
 *      Author: harald
 *  Inspired by Cat (https://github.com/ShareCat/STM32CommandLine)
 */

#include <System/CommandLine/CommandLine.h>
#include <libraries/HelpersLib.h>
#include <new>
#include "main.h"

#include "cmsis_os.h"

namespace cLine {

void CommandLine::init(void) {
	new (&instance()) CommandLine();
}

CommandLine& CommandLine::instance(void) {
	static CommandLine commandLine;
	return commandLine;
}

CommandLine::CommandLine():
		_keyBuffer(KEY_BUFFER_LEN),
		_history(),
		_interpret(),
		_cmdPos(0)

{
	_cmdBuffer.fill('\0');
	termDisplayClear();
}

uint32_t CommandLine::cycle(void) {
	uint8_t actChar = '\0';

	uint32_t hashCode = 0;
	while(readNextChar(actChar) == _SUCCESS) {
		if(actChar == _KEY_ENTER){
			hashCode = procEnter();
		} else if(actChar == _KEY_BACKSPACE) {
			procBackspace();
		} else if(actChar == _KEY_ESCAPE) {
			uint8_t result = readNextChar(actChar);
			if( (result == _SUCCESS) && (actChar == _KEY_SQBRACELEFT) ) {
				procSqrEscKeys();
			}
			// Minicom sends different END-key sequence
			else if ( (result == _SUCCESS) && (actChar == _KEY_END_MINICOM1) ) {
				result = readNextChar(actChar);
				if ( (result == _SUCCESS) && (actChar == _KEY_END_MINICOM2) ) {
					procEnd();
				}
			}
			else {
				procEscape();
			}
		} else {
			accumulateChar(actChar);
		}
	}
	return hashCode;
}

bool CommandLine::readNextChar(uint8_t &chr) {
	if(!_keyBuffer.isEmpty()){
		chr = _keyBuffer.dequeue();
		return _SUCCESS;
	}
	return _ERROR;
}

void CommandLine::accumulateChar(uint8_t chr) {
	if(_cmdPos == COMMAND_BUFFER_LEN-1){
		return;
	}
	if(_cmdBuffer.at(_cmdPos + 1) != '\0') {
		moveCmdRight(_cmdPos);
	}
	_cmdBuffer.at(_cmdPos) = chr;
	incCmdPos();
	termInsert(1u);
	tx_printBuff(&chr, 1);
}

void CommandLine::procSqrEscKeys(void) {
	uint8_t actChar = '\0';
	uint8_t result = readNextChar(actChar);

	if( (result == _SUCCESS) && (actChar == _KEY_UP) ) {
		procArrowUp();
		return;
	} else if( (result == _SUCCESS) && (actChar == _KEY_DOWN) ) {
		procArrowDown();
		return;
	} else if( (result == _SUCCESS) && (actChar == _KEY_LEFT) ) {
		procArrowLeft();
		return;
	} else if( (result == _SUCCESS) && (actChar == _KEY_RIGHT) ) {
		procArrowRight();
		return;
	}

	procFourByteEscKeys(actChar);
}

void CommandLine::procFourByteEscKeys(uint8_t actChar) {
	uint8_t seqSuffix = '\0';
	uint8_t result = readNextChar(seqSuffix);

	if( (result == _SUCCESS) && (seqSuffix == _SEQ_SUFFIX) ) {
		if( (result == _SUCCESS) && (actChar == _KEY_POS1) ) {
			procPos1();
		} else if( (result == _SUCCESS) && (actChar == _KEY_DEL) ) {
			procDel();
		}  else if( (result == _SUCCESS) && (actChar == _KEY_END) ) {
			procEnd();
		}  else if( (result == _SUCCESS) && (actChar == _KEY_PGUP) ) {
			procPGUP();
		}  else if( (result == _SUCCESS) && (actChar == _KEY_PGDN) ) {
			procPGDN();
		}
	}
}

void CommandLine::moveCmdRight(uint8_t startPos) {
	uint8_t actPos = startPos;
	uint8_t actChar = _cmdBuffer.at(actPos);

	while (_cmdBuffer.at(actPos) != '\0') {
		uint8_t nextChar = _cmdBuffer.at(actPos + 1);
		_cmdBuffer.at(actPos + 1) = actChar;
		actChar = nextChar;
		actPos++;
	}
}

void CommandLine::moveCmdLeft(uint8_t startPos) {
	uint8_t actPos = startPos;
	while (_cmdBuffer.at(actPos) != '\0') {
		_cmdBuffer.at(actPos) = _cmdBuffer.at(actPos + 1);
		actPos++;
	}
}

uint32_t CommandLine::procEnter(void) {
	uint32_t hashCode = 0;
	_history.add(_cmdBuffer);
	_history.resShowPos();

	tx_printf("\n");
	hashCode = _interpret.doit(_cmdBuffer);
	resCmdPos();
	_cmdBuffer.fill('\0');

	return hashCode;
}

void CommandLine::prompt(ExecResult execResult) {
	if(execResult == exSuccess) {
		tx_printf("\n** DONE **\n"); //  remember TI-99/4A?
		termPrompt();
	} else if (execResult == exUnknown){
		tx_printf("\nunknown Command\n");
		termPrompt();
	} else if (execResult == exEmptyCom) {
		termPrompt();
	}
}

void CommandLine::procBackspace(void) {
	if(_cmdPos != 0) {
		decCmdPos();
		termMoveLeft(1u);
		termDelete(1u);
		moveCmdLeft(_cmdPos);
	}
}

void CommandLine::procDel(void) {
	moveCmdLeft(_cmdPos);
	termDelete(1u);
}

void CommandLine::syncCmdPos(void) {
	_cmdPos = 0;
	while ((_cmdPos < COMMAND_BUFFER_LEN)
			&& (_cmdBuffer.at(_cmdPos) != '\0') ) {
		incCmdPos();
	}
}

void CommandLine::procArrowUp(void) {
	if(_history.getInsertPos() == _history.getShowPos()) {
		_history.add(_cmdBuffer);
	}
	_cmdBuffer = _history.showUp();
	termPos1();
	termEraseLine(2u);
	termPrompt();
	tx_printf("%s", _cmdBuffer.data());
	syncCmdPos();
}

void CommandLine::procArrowDown(void) {
	if(_history.getInsertPos() == _history.getShowPos()) {
		return;
	}
	_cmdBuffer = _history.showDown();
	termPos1();
	termEraseLine(2u);
	termPrompt();
	tx_printf("%s", _cmdBuffer.data());
	syncCmdPos();
}

void CommandLine::procArrowLeft(void) {
	if(_cmdPos != 0) {
		termMoveLeft(1u);
		decCmdPos();
	}
}

void CommandLine::procArrowRight(void) {
	if( (_cmdPos < COMMAND_BUFFER_LEN)
			&& (_cmdBuffer.at(_cmdPos) != '\0') ) {
		termMoveRight(1u);
		incCmdPos();
	}
}

void CommandLine::procEnd(void) {
	while ((_cmdPos < COMMAND_BUFFER_LEN)
			&& (_cmdBuffer.at(_cmdPos) != '\0') ) {
		termMoveRight(1u);
		incCmdPos();
	}
}

void CommandLine::procPos1(void) {
	termPos1();
	termPrompt();
	resCmdPos();
}

void CommandLine::procEscape(void) {
	// unused
}

void CommandLine::procPGUP(void) {
	// unused
}

void CommandLine::procPGDN(void) {
	// unused
}

} /* namespace comLine */
