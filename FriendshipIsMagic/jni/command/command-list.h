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

//============================================
using SyncFromServerCommand = CommandMessage<5,
		sf::Vector2f, 			// P1Pos
		Entity, 				// P1Gun
		Entity,					// P2Gun
		sf::Uint16, 			// P1Health
		sf::Uint16, 			// P2Health
		sf::Uint16, 			// P1MaxH
		sf::Uint16,  			// P2MaxH
		bool, 					// P1Fire
		bool 					// P1IsLeft
>;

//============================================	P2pos, 			P2Fire	P2isLeft
using SyncFromClientCommand = CommandMessage<6, sf::Vector2f, 	bool, 	bool >;

//using SayPlayerInfoCommand = CommandMessage<4,Player>;


#endif /* COMMAND_COMMAND_LIST_H_ */
