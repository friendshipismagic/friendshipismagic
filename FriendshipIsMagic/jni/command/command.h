/*
 * Command.h
 *
 *  Created on: 17 juin 2016
 *      Author: edwardvergara
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include "command-list.h"

template<typename InstructionType, typename Stream>
class Command {
	public:
		//Command(std::string fileName);
		//virtual ~Command();

		void setCommand(InstructionType instruction, std::function<void(Stream&)>);

		void interpret(Stream& packet);

	private:
		//std::ifstream mFile;
		std::map<InstructionType, std::function<void(Stream&)> > mStoredCommands;
};

#include <SFML/Network/Packet.hpp>

using PacketCommand = Command<int, sf::Packet>;
using ConsoleCommand = Command<std::string, sf::Packet>;

#include "command.inl"
#endif /* COMMAND_H_ */
