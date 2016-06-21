//============================================================================
// Name        : testHello.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "Command.h"
#include "Player.h"
#include "network/UDPtestClass.h"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

#include "network/UDPAgent.h"
//#include "Command2.h"
using namespace std;


/*
 * link de SFML pour Eclipse CDT
 * Projet>>propriétés>>C/C++ Build>>Settings >> Linker >> libraries
 * -l
 * sfml-graphics
 * sfml-window
 * sfml-network
 * sfml-system
 *
 * -L
 * /Applications/Antony/DEV_LIB/SFML-2.3.2-osx-clang-universal/lib
 *
 *Run>>Run Configuration >> Envirronement
 * Name: 	DYLD_LIBRARY_PATH
 * Value: 	/Applications/Antony/DEV_LIB/SFML-2.3.2-osx-clang-universal/lib
 *
 * Pour mac, copier le contenu du dosser extlibs de la library dans
 * le dossier /Library/Frameworks du Mac
 */

sf::Packet& operator <<(sf::Packet& Packet, const Player& player)
{
	return Packet << player.mFirstName << player.mLastName << player.mPosX << player.mPosY;// << player.mInventory;
}

sf::Packet& operator >>(sf::Packet& Packet,  Player& player)
{
	return Packet >> player.mFirstName >> player.mLastName >> player.mPosX >> player.mPosY;// >> player.mInventory;
}

void sayHello(sf::Packet pkt){
	//cout << "Hello!!\n";
	string str;
	pkt >> str;
	cout << str;
}

void sayPlayerInfo(sf::Packet pkt){
	Player player;
	pkt >> player;
	player.printInfo();
}
int main() {

	//Janniaux command
	PacketCommand cmd;
	sf::Packet pkt;
	Player player;
	pkt << 5 << player;
	cmd.setCommand(5,sayPlayerInfo);

	cmd.interpret(pkt);

	UDPtestClass test;
	test.testRoutine();

	return 0;
}




