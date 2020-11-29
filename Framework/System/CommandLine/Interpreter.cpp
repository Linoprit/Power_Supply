/*
 * ComLineInterpreter.cpp
 *
 *  Created on: 07.11.2020
 *      Author: harald
 */

#include <System/CommandLine/Interpreter.h>
#include <string.h>
#include <Sockets/CrcSocket.h>
#include <System/usb_printf.h>


namespace cLine {

Interpreter::Interpreter() {
}

uint32_t Interpreter::doit(CmdBufferType comLine) {
	uint32_t hashCode = 0;
	uint8_t i = 0;
	uint8_t commandBuf[COMMAND_BUFFER_LEN];
	memset(commandBuf, ' ', COMMAND_BUFFER_LEN);

	for (i=0; i < COMMAND_BUFFER_LEN; i++) {
		uint8_t actChar = comLine.at(i);
		if( (actChar == ' ') || (actChar == '\0') ) {
			break;
		}
		commandBuf[i] = actChar;
	}

	//if (i > 0) {
		// adjust size to fit into uint32 type
		uint32_t len32 = (i + UINT32_SIZE - (i % UINT32_SIZE)) / 4;
		hashCode = CrcSocket::calc_chksum32(reinterpret_cast<uint32_t*>(commandBuf), len32);
	//}

	// here we could look for arguments, starting at i
	// uint8_t oldPos = i;
	// oldPos++; // was positioned at first space
	// std::string argStr;
	// for ( i = oldPos; i < COMMAND_BUFFER_LEN; i++) {
	// 	uint8_t actChar = comLine.at(i);
	// 	if( (actChar == ' ') || (actChar == '\0') ) {
	// 		break;
	// 	}
	// 	argStr.insert(i, actChar, 1);
	// }
	// uint32_t argVal = std::stoi(argStr);

	return hashCode;
}

/* for later usage
bool Interpreter::dispatch(uint32_t hashCode) {

	//tx_printf("HashCode=%ul\n", hashCode);
	if(hashCode == 159682253ll) { // e2dumpjournal HashCode=159682253ll
		tx_printf("e2dumpjournal\n");
		return true;
	}
	if(hashCode == 873361028l) { // e2init HashCode=873361028l
		tx_printf("e2init\n");
		return true;
	}
	if(hashCode == 92878466l) { // e2dumpjournalmap HashCode=92878466l
		tx_printf("e2dumpjournalmap\n");
		return true;
	}
	if(hashCode == 1366722125l) { // e2erase HashCode=1366722125l
		tx_printf("e2erase\n");
		return true;
	}
	if(hashCode == 1689283434l) { // e2dumpcalib HashCode=1689283434l
		tx_printf("e2dumpcalib\n");
		return true;
	}
	if(hashCode == 1631391739l) { // e2dumpmem HashCode=1631391739l
		tx_printf("e2dumpmem\n");
		return true;
	}
	if(hashCode == 3820427237l) {	 // e2dumpstart HashCode=3820427237l
		tx_printf("e2dumpstart\n");
		return true;
	}
	return false;
}
*/

} /* namespace cLine */
