/*
 * ComLineInterpreter.h
 *
 *  Created on: 07.11.2020
 *      Author: harald
 */

#ifndef SYSTEM_COMMANDLINE_INTERPRETER_H_
#define SYSTEM_COMMANDLINE_INTERPRETER_H_

#include "ComLineConfig.h"


namespace cLine {

class Interpreter {
public:
	Interpreter();
	virtual ~Interpreter() {};

	uint32_t doit(CmdBufferType comLine);


private:
	bool dispatch(uint32_t hashCode);

};

} /* namespace cLine */

#endif /* SYSTEM_COMMANDLINE_INTERPRETER_H_ */
