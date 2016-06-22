//============================================================================
// Name        : testHello.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "command/Command.h"
#include "Player.h"
#include "network/UDPtestClass.h"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

#include "network/UDPAgent.h"
#include "command/commandList.h"
#include "command/packetExplorer.h"


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


void sayHello(sf::Packet pkt){
	std::cout << "Hello from main!" << std::endl;
}
void printString(sf::Packet pkt){
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

	cmd.setCommand(SayHelloCommand::id,sayHello);
	cmd.setCommand(PrintStringCommand::id,printString);
	cmd.setCommand(SayPlayerInfoCommand::id,sayPlayerInfo);

	sf::Packet pkt;
	Player player;

	sf::Packet p = SayPlayerInfoCommand::make(player);
	cmd.interpret(p);

	//packet >> toto >> titi >> tata;
	//CommandMessage::check (toto, titi, tata);

	//==========[ UDP test routine ]==========//
	UDPtestClass test;
	test.testRoutine(cmd);

	return 0;
}




