/*
 * commandList.h
 *
 *  Created on: 21 juin 2016
 *      Author: edwardvergara
 */

#ifndef COMMAND_COMMANDLIST_H_
#define COMMAND_COMMANDLIST_H_


#include "CommandMessage.h"
#include "../Player.h"
#include <string>

using SayHelloCommand = CommandMessage<2>;
using PrintStringCommand = CommandMessage<3, std::string>;
using SayPlayerInfoCommand = CommandMessage<4,Player>;


#endif /* COMMAND_COMMANDLIST_H_ */
