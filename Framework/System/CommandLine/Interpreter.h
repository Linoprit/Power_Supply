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

	bool doit(CmdBufferType comLine);


private:


};

} /* namespace cLine */

#endif /* SYSTEM_COMMANDLINE_INTERPRETER_H_ */
