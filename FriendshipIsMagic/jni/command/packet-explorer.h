/*
 * packetExplorer.h
 *
 *  Created on: 21 juin 2016
 *      Author: edwardvergara
 */

#ifndef COMMAND_PACKET_EXPLORER_H_
#define COMMAND_PACKET_EXPLORER_H_
#pragma once


#include <SFML/Network/Packet.hpp>
//#include "../Player.h"
/*
 * This file is used to declare all "<<" and ">>" operator definition
 * for custom classes.
 */
/*
inline sf::Packet& operator <<(sf::Packet& packet, const Player& player)
{
	return packet << player.mFirstName << player.mLastName << player.mPosX << player.mPosY;// << player.mInventory;
}

inline sf::Packet& operator >>(sf::Packet& packet,  Player& player)
{
	return packet >> player.mFirstName >> player.mLastName >> player.mPosX >> player.mPosY;// >> player.mInventory;
}
*/
#endif /* COMMAND_PACKET_EXPLORER_H_ */
