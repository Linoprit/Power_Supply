/*
 * ComLineInterpreter.cpp
 *
 *  Created on: 07.11.2020
 *      Author: harald
 */

#include <System/CommandLine/Interpreter.h>
#include <System/usb_printf.h>
#include <string>

namespace cLine {

Interpreter::Interpreter() {
	//float someVal = std::stof("123.1");

}

bool Interpreter::doit(CmdBufferType comLine) {
	tx_printf("\n%s", comLine.data());
	return true;
}

} /* namespace cLine */
