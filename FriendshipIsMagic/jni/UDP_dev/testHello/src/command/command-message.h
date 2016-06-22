/*
 * CommandMessage.h
 *
 *  Created on: 21 juin 2016
 *      Author: edwardvergara
 */

#ifndef COMMAND_COMMANDMESSAGE_H_
#define COMMAND_COMMANDMESSAGE_H_

#include <SFML/Network/Packet.hpp>

template<int ID, typename... Args>
class CommandMessage {
public:
	CommandMessage()=delete;

	enum { id = ID };

	static sf::Packet make(Args... args);

	static bool check(Args... args);

private:
	template<typename T, typename... Args2>
	static sf::Packet& make_all(sf::Packet& packet, const T& value, Args2... args);

	static sf::Packet& make_all(sf::Packet& packet) ;
};



#include "CommandMessage.inl"
#endif /* COMMAND_COMMANDMESSAGE_H_ */
