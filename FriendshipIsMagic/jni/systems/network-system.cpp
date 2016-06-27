/*
 * network-system.cpp
 *
 *  Created on: 24 juin 2016
 *      Author: edwardvergara
 */

#include "network-system.h"
#include "physicsystem.h"
#include "healthsystem.h"
#include <SFML/System.hpp>


//Network system



NetworkSystem::NetworkSystem(World* world, State::Context& context, InputSystem* input, PhysicSystem* aPhysics, HealthSystem* aHealth)
:System(world, context)
, mInput(input)
, mPhysics(aPhysics)
, mHealth(aHealth)
, mUDP(nullptr)
{

	mInputs.insert(std::make_pair(Input::jump, false));
	mInputs.insert(std::make_pair(Input::right, false));
	mInputs.insert(std::make_pair(Input::left, false));
	mInputs.insert(std::make_pair(Input::fire, false));
	//TO DO finir sync
	periode = sf::milliseconds(DEFAULT_SYNC_PERIOD);
	using std::placeholders::_1;
	mCmd.setCommand(ShareInputCommand::id,std::bind(&NetworkSystem::updateCoPlayerInput, this, _1));
	mCmd.setCommand(SyncCommand::id,std::bind(&NetworkSystem::Sync, this, _1));

}


NetworkSystem::~NetworkSystem() {
	// TODO Auto-generated destructor stub
}

void NetworkSystem::updateCoPlayerInput(sf::Packet pkt){
	bool right, left, fire, jump;
	pkt >> right >>left >> fire >> jump;

	mInputs[Input::right] = right;
	mInputs[Input::left] = left;
	mInputs[Input::fire] = fire;
	mInputs[Input::jump] = jump;
}

void NetworkSystem::Sync(sf::Packet pkt){
	pkt >> mPhysics->getPositions() >> mHealth->getCurrentHealth() >> mHealth->getMaxHealth();
}

void NetworkSystem::update(sf::Time dt){

	if(mUDP == nullptr){
		std::cout << "UDP error"<< std::endl;
		return;
	}
	sf::Packet pkt ;
	sf::Time time = clk.getElapsedTime();
	//TO DO finir sync
	if(time > periode){
		if(mContext.UDPMode == UDPAgent::Mode::Server){
			//std::cout<< "sync tick" <<std::endl;
			pkt = SyncCommand::make(mPhysics->getPositions(), mHealth->getCurrentHealth(), mHealth->getMaxHealth());
		}
		clk.restart();
	}

	pkt = ShareInputCommand::make(
			mInput->getInputState(Input::right),
			mInput->getInputState(Input::left),
			mInput->getInputState(Input::fire),
			mInput->getInputState(Input::jump));

	mUDP->send(pkt);

	//Receive
	//sf::Clock master;
	while(emptyBuf() == false){
		//std::cout << "master has waited " << master.getElapsedTime().asSeconds();
		//sf::Clock slave;
		auto pkt = popFrontBuf();
		//std::cout << " and slave " << slave.getElapsedTime().asSeconds() << std::endl;
		mCmd.interpret(pkt);
		//master = sf::Clock();
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
		std::cout << "Can't bind socket to port " << srcPort << std::endl;
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
		std::cout << "Can't bind socket to port " << srcPort << std::endl;
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
