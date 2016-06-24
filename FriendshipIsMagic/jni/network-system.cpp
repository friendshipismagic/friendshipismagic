/*
 * network-system.cpp
 *
 *  Created on: 24 juin 2016
 *      Author: edwardvergara
 */

#include "network-system.h"

void printString(sf::Packet pkt){
	std::string str;
	pkt >> str;
	std::cout << str << std::endl;
}
NetworkSystem::NetworkSystem(World* world, State::Context& context, InputSystem* input)
:System(world, context)
, mInput(input)
, mUDP(nullptr)
, mInputs(){

	mInputs.insert(std::make_pair(Input::jump, false));
	mInputs.insert(std::make_pair(Input::right, false));
	mInputs.insert(std::make_pair(Input::left, false));
	mInputs.insert(std::make_pair(Input::fire, false));
	// TODO Auto-generated constructor stub
	using std::placeholders::_1;
	mCmd.setCommand(PrintStringCommand::id,printString);
	mCmd.setCommand(ShareInputCommand::id,std::bind(&NetworkSystem::updateCoPlayerInput, this, _1));
}


NetworkSystem::~NetworkSystem() {
	// TODO Auto-generated destructor stub
}

void NetworkSystem::updateCoPlayerInput(sf::Packet pkt){
	bool right, left, fire, jump;
	pkt >> right >>left >> fire >> jump;
	/*
	mInputs[Input::right] = right;
	mInputs[Input::left] = left;
	mInputs[Input::fire] = fire;
	mInputs[Input::jump] = jump;
	*/

	if(mContext.UDPMode == UDPAgent::Mode::Server)
		//std::cout << "received " << std::hex << ordre << std::dec << std::endl;
		std::cout << "Received client inputs: " << right << left << fire << jump << std::endl;
}

void NetworkSystem::update(sf::Time dt){
	if(mUDP == nullptr){
		std::cout << "UDP error"<< std::endl;
		return;
	}
	sf::Packet pkt ;
	pkt = ShareInputCommand::make(
			mInput->getInputState(Input::right),
			mInput->getInputState(Input::left),
			mInput->getInputState(Input::fire),
			mInput->getInputState(Input::jump));
	/*
	if( mContext.UDPMode == UDPAgent::Mode::Server){
		pkt = PrintStringCommand::make("From server:");// + std::to_string(mInput->getInputState(Input::jump)));
	}
	else{
		pkt = PrintStringCommand::make("From client:");//+ std::to_string(mInput->getInputState(Input::jump)));
	}*/
	mUDP->send(pkt);

	//Receive
	while(emptyBuf() == false){
		auto pkt = popFrontBuf();
		mCmd.interpret(pkt);
	}

}
//Server mode
void NetworkSystem::startUDPServer(int srcPort){

	mUDP.reset(new UDPAgent(srcPort));
	mUDP->addObserver(this);
	try{
	mUDP->start();
	running = true;
	}
	catch(UDPException* e){
		std::cout << "Can't bind socket to port " << std::to_string(srcPort) << std::endl;
		exit(-1);
	}
}
//Client mode
void NetworkSystem::startUDPClient(int srcPort, sf::IpAddress destIp, int destPort){
	mUDP.reset(new UDPAgent(srcPort,destIp, destPort));
	mUDP->addObserver(this);
	try{
		mUDP->start();
		running = true;
	}
	catch(UDPException* e){
		std::cout << "Can't bind socket to port " << std::to_string(srcPort) << std::endl;
		exit(-1);
	}
}

void NetworkSystem::notify(sf::Packet pkt){
	pushBuf(pkt);
}

bool NetworkSystem::getInputState(Input input)
{
    return mInputs[input];
}
