/*
 * CommandMessage.cpp
 *
 *  Created on: 21 juin 2016
 *      Author: edwardvergara
 */

#include "packetExplorer.h"


template<int ID, typename... Args>
sf::Packet CommandMessage<ID, Args...>::make(Args... args) {
	sf::Packet packet;
	packet << ID;
	return CommandMessage<ID, Args...>::make_all(packet, args...);
}

template<int ID, typename... Args>
template<typename T, typename... Args2>
sf::Packet& CommandMessage<ID, Args...>::make_all(sf::Packet& packet, const T& value, Args2... args) {
	return CommandMessage<ID, Args...>::make_all(packet << value, args...);
}

template<int ID, typename... Args>
sf::Packet& CommandMessage<ID, Args...>::make_all(sf::Packet& packet) {
	return packet;
}

template<int ID, typename... Args>
bool CommandMessage<ID, Args...>::check(Args... args) {
	
	return true;
}