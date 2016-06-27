/*
 * network-system.cpp
 *
 *  Created on: 24 juin 2016
 *      Author: edwardvergara
 */

#include <SFML/System.hpp>
#include "network-system.h"
#include "physicsystem.h"
#include "healthsystem.h"
#include "../core/world.h"



//Network system



NetworkSystem::NetworkSystem(World* world, State::Context& context, InputSystem* input, PhysicSystem* aPhysics, HealthSystem* aHealth, LogicSystem* aLogic)
:System(world, context)
, mInput(input)
, mPhysics(aPhysics)
, mHealth(aHealth)
, mLogic(aLogic)
, mUDP(nullptr)
{

	mInputs.insert(std::make_pair(Input::jump, false));
	mInputs.insert(std::make_pair(Input::right, false));
	mInputs.insert(std::make_pair(Input::left, false));
	mInputs.insert(std::make_pair(Input::fire, false));

	mLogics.insert(std::make_pair(Logic::isFacingLeft, false));
	mLogics.insert(std::make_pair(Logic::fireOn, false));
	//TO DO finir sync
	//periode = sf::milliseconds(DEFAULT_SYNC_PERIOD);
	using std::placeholders::_1;
	mCmd.setCommand(SyncFromClientCommand::id,std::bind(&NetworkSystem::SyncFromClient, this, _1));
	mCmd.setCommand(SyncFromServerCommand::id,std::bind(&NetworkSystem::SyncFromServer, this, _1));

}


NetworkSystem::~NetworkSystem() {
	// TODO Auto-generated destructor stub
}

/*
void NetworkSystem::updateCoPlayerInput(sf::Packet pkt){
	bool right, left, fire, jump;
	pkt >> right >>left >> fire >> jump;

	mInputs[Input::right] = right;
	mInputs[Input::left] = left;
	mInputs[Input::fire] = fire;
	mInputs[Input::jump] = jump;
}
*/

/*
void NetworkSystem::Sync(sf::Packet pkt){
	//std::cout << "before sync" << mPhysics->getPositions()[Systems::PLAYER].x << std::endl;
	pkt >> mPhysics->getPositions() >> mHealth->getCurrentHealth() >> mHealth->getMaxHealth();
	mPhysics->syncPos();
	//std::cout << "after sync" << mPhysics->getPositions()[Systems::PLAYER].x << std::endl;
}
*/

void NetworkSystem::SyncFromClient(sf::Packet pkt){
	sf::Vector2f v;
	pkt >>v;
	mPhysics->setPosition(mGameWorld->getCoPlayerID(),v);
	mPhysics->syncPos(mGameWorld->getCoPlayerID());

	bool boolean;
	pkt >> boolean;
	mLogics[Logic::fireOn] = boolean;

	pkt >> boolean;
	mLogics[Logic::isFacingLeft] = boolean;
	mLogics[Logic::isFacingRight] = !boolean;

}

void NetworkSystem::SyncFromServer(sf::Packet pkt){
	//P1pos
	sf::Vector2f v;
	Entity gunP1, gunP2;
	HealthSystem::health_t HP1 = 0, HP2 = 0, MHP1 = 0, MHP2 = 0;
	bool fireOn, isFacingLeft;

	pkt >> v >> gunP1 >> gunP2 >> HP1 >> HP2 >> MHP1 >> MHP2 >> fireOn >> isFacingLeft;
	//std::cout << v.x << v.y << "\t gun P1: "<<gunP1 << " gun P2 : "<< gunP2 << " HP P1 : " << HP1 << " HP P2 : "<< HP2 << " " << MHP1 << MHP2 << " FireOn P1 : " << fireOn << " FacingLeft : "<< isFacingLeft << std::endl;
	mPhysics->setPosition(mGameWorld->getPlayerID(),v);
	mPhysics->syncPos(mGameWorld->getPlayerID());

	//P1 and P2 guns
	mGameWorld->setPlayerWeaponID(gunP1);
	mGameWorld->setCoPlayerWeaponID(gunP2);

	//Heal and max Heal

	mHealth->setCurrentHealth(mGameWorld->getPlayerID(), HP1);
	mHealth->setCurrentHealth(mGameWorld->getCoPlayerID(), HP2);
	mHealth->setMaxHealth(mGameWorld->getPlayerID(), MHP1);
	mHealth->setMaxHealth(mGameWorld->getCoPlayerID(), MHP2);

	// fireOn
	mLogics[Logic::fireOn] = fireOn;

	// Orientation
	mLogics[Logic::isFacingLeft] = isFacingLeft;
	mLogics[Logic::isFacingRight] = !isFacingLeft;

}

void NetworkSystem::update(sf::Time dt){

	if(mUDP == nullptr){
		std::cout << "UDP error"<< std::endl;
		return;
	}
	/*
	sf::Time time = clk.getElapsedTime();
	//TO DO finir sync
	if(time > periode){
		if(mContext.UDPMode == UDPAgent::Mode::Server){
			//std::cout<< "sync tick" <<std::endl;
			mUDP->send(SyncCommand::make(
					mPhysics->getPositions(),
					mHealth->getCurrentHealth(),
					mHealth->getMaxHealth())
			);
		}
		clk.restart();
	}
	*/
	static int cpt=0;
	if(cpt++ >= DEFAULT_INPUT_SYNC_FRAME_COUNT){
		cpt=0;
		if(mContext.UDPMode == UDPAgent::Mode::Server){
			//std::cout << mPhysics->getPosition(mGameWorld->getPlayerID()).x << mPhysics->getPosition(mGameWorld->getPlayerID()).y << "\t gun P1: "<< mGameWorld->getPlayerWeaponID() << " gun P2 : "<< mGameWorld->getCoPlayerWeaponID() << " HP P1 : " << mHealth->getCurrentHealth(mGameWorld->getPlayerID()) << " HP P2 : "<< mHealth->getCurrentHealth(mGameWorld->getCoPlayerID()) << " " << mHealth->getMaxHealth(mGameWorld->getPlayerID()) << mHealth->getMaxHealth(mGameWorld->getCoPlayerID()) << " FireOn P1 : " << mLogic->getLogic(Logic::fireOn) << " FacingLeft : "<< mLogic->getLogic(Logic::isFacingLeft) << std::endl;
			mUDP->send(SyncFromServerCommand::make(
					mPhysics->getPosition(mGameWorld->getPlayerID()),
					mGameWorld->getPlayerWeaponID(),
					mGameWorld->getCoPlayerWeaponID(),
					mHealth->getCurrentHealth(mGameWorld->getPlayerID()),
					mHealth->getCurrentHealth(mGameWorld->getCoPlayerID()),
					mHealth->getMaxHealth(mGameWorld->getPlayerID()),
					mHealth->getMaxHealth(mGameWorld->getCoPlayerID()),
					mLogic->getLogic(Logic::fireOn),
					mLogic->getLogic(Logic::isFacingLeft)
			));
		}
		else if(mContext.UDPMode == UDPAgent::Mode::Client){
			//std::cout<< "sync tick" <<std::endl;

			mUDP->send(SyncFromClientCommand::make(
					mPhysics->getPosition(mGameWorld->getCoPlayerID()),
					mLogic->getLogic(Logic::coFireOn),
					mLogic->getLogic(Logic::coIsFacingLeft)
			));
		}
	} //== fin if cpt

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
bool NetworkSystem::getLogicState(Logic logic)
{
    return mLogics[logic];
}
