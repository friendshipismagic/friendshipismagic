/*
 * commandList.h
 *
 *  Created on: 21 juin 2016
 *      Author: edwardvergara
 */

#ifndef COMMAND_COMMAND_LIST_H_
#define COMMAND_COMMAND_LIST_H_


#include <string>

//#include "../player.h"
#include "command-message.h"
#include "../core/entity.h"
/*
 * This file is used to store all the commands
 * availables in the game.
 */

using SayHelloCommand = CommandMessage<2>;
using ShareInputCommand = CommandMessage<4, bool, bool, bool, bool>;
using SyncCommand = CommandMessage<5, std::map<Entity, sf::Vector2f>, std::map<Entity, int>, std::map<Entity, int> >;
//using SayPlayerInfoCommand = CommandMessage<4,Player>;


#endif /* COMMAND_COMMAND_LIST_H_ */
