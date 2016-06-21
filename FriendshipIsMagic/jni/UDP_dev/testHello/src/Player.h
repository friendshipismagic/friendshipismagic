/*
 * Player.h
 *
 *  Created on: 20 juin 2016
 *      Author: edwardvergara
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include"json/json.h"
#include"json/json-forwards.h"
#include <SFML/Network/Packet.hpp>

class Player {
public:
	Player();
	virtual ~Player();
	void printInfo();

	std::string mFirstName;
	std::string mLastName;
	int mPosX;
	int mPosY;
	std::vector<std::string> mInventory;
	std::vector<int> mInventoryPrices;


};




#endif /* PLAYER_H_ */
