/*
 * packetExplorer.h
 *
 *  Created on: 21 juin 2016
 *      Author: edwardvergara
 */

#ifndef COMMAND_PACKETEXPLORER_H_
#define COMMAND_PACKETEXPLORER_H_
#pragma once


#include <SFML/Network/Packet.hpp>
#include "../Player.h"

inline sf::Packet& operator <<(sf::Packet& packet, const Player& player)
{
	return packet << player.mFirstName << player.mLastName << player.mPosX << player.mPosY;// << player.mInventory;
}

inline sf::Packet& operator >>(sf::Packet& packet,  Player& player)
{
	return packet >> player.mFirstName >> player.mLastName >> player.mPosX >> player.mPosY;// >> player.mInventory;
}
/*sf::Packet& operator >>(sf::Packet& packet,  CommandList& list)
{
	sf::Uint8 integer;
	packet >> integer;
	list = static_cast<CommandList>(integer);
	return packet;
}
sf::Packet& operator <<(sf::Packet& packet,  CommandList& list)
{
	sf::Uint8 integer = static_cast<sf::Uint8>(list);
	return packet << integer;
}*/


#endif /* COMMAND_PACKETEXPLORER_H_ */
