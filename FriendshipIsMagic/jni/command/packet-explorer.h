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
#include "../core/entity.h"
#include <SFML/Network.hpp>
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


inline sf::Packet& operator >>(sf::Packet& packet,   sf::Vector2f& position)
{
	float x , y;
	packet >> x >> y;
	position = sf::Vector2f(x,y);
	return packet;
}
inline sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2f& position)
{
	return packet << position.x << position.y;
}

template<typename T>
inline sf::Packet& operator >>(sf::Packet& packet,  std::map<Entity, T>& position)
{
	sf::Uint32  mapSize;
	packet >> mapSize;
	for( sf::Uint32 i =0; i<mapSize; ++i ){
		Entity key;
		T value;
		packet >> key >> value;
		position[key]=value;
	}

	return packet;
}
template<typename T>
inline sf::Packet& operator <<(sf::Packet& packet, const std::map<Entity, T>& position)
{
	packet << (sf::Uint32) position.size();
	for( auto it = position.begin(); it != position.end(); ++it ){
		const Entity& key = it->first;
		const T& value = it->second;
		packet << key << value;
	}
	return packet;
}



#endif /* COMMAND_PACKET_EXPLORER_H_ */
