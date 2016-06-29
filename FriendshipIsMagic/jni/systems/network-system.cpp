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



NetworkSystem::NetworkSystem(World* world, State::Context& context, InputSystem* input, PhysicSystem* aPhysics, HealthSystem* aHealth, LogicSystem* aLogic, WeaponSystem* aWeapon)
:System(world, context)
, mInput(input)
, mPhysics(aPhysics)
, mHealth(aHealth)
, mLogic(aLogic)
, mWeapon(aWeapon)
, mUDP(nullptr)
, mDiscover(nullptr)
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
	mCmd.setCommand(SyncFromClientCommand::id, std::bind(&NetworkSystem::syncFromClient, this, _1));
	mCmd.setCommand(SyncFromServerCommand::id, std::bind(&NetworkSystem::syncFromServer, this, _1));
	//mCmd.setCommand(AskForInitCommand::id, std::bind(&NetworkSystem::askForInitReceived, this, _1));
	//mCmd.setCommand(AckInitCommand::id, std::bind(&NetworkSystem::ackInitReceived, this, _1));
	mCmd.setCommand(ReadyCommand::id, std::bind(&NetworkSystem::readyReceived, this, _1));
	mCmd.setCommand(AckReadyCommand::id, std::bind(&NetworkSystem::ackReadyReceived, this, _1));
}


NetworkSystem::~NetworkSystem() {
	// TODO Auto-generated destructor stub
}
/*
//=====================[ INIT SYNC METHODS ]======================//
//executed by the client when world want to init
void NetworkSystem::askForInit(){
	mUDP->send(AskForInitCommand::make());
}

//executed by server when askForInit received
void NetworkSystem::askForInitReceived(sf::Packet pkt){
		mUDP->send(InitFeedbackCommand::make(

		));
}

// executed by the client to init world then send ackInit
void NetworkSystem::initFeedbackReceived(sf::Packet pkt){
	if(mGameWorld->initEntitiesFromServer()){
		mUDP->send(AckInitCommand::make());
		mInitialized = true;
	}
}

//executed by the server when it received the ack
void NetworkSystem::ackInitReceived(sf::Packet pkt){
	mInitialized = true;
}
*/
//===================[ END INIT SYNC METHODS ]====================//


void NetworkSystem::sendReady(){
	mUDP->send(ReadyCommand::make());
}
void NetworkSystem::readyReceived(sf::Packet pkt){
	if(mInitialized)
		return;
	//std::cout <<"Server ready!"<<std::endl;
	mUDP->send(AckReadyCommand::make());
	mInitialized = true;
	mContext.foundPlayer =true;
	mGameWorld->initEntities();
}
void NetworkSystem::ackReadyReceived(sf::Packet pkt){
	if(mInitialized)
			return;
	//std::cout <<"Client ready!"<<std::endl;
	mInitialized = true;
	mContext.foundPlayer =true;
	mGameWorld->initEntities();
}

void NetworkSystem::syncFromClient(sf::Packet pkt){
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



void NetworkSystem::syncFromServer(sf::Packet pkt){
	//P1pos
	sf::Vector2f v;
	std::string gunP1, gunP2;
	HealthSystem::health_t HP1 = 0, HP2 = 0, MHP1 = 0, MHP2 = 0;
	bool fireOn, isFacingLeft;

	pkt >> v >> gunP1 >> gunP2 >> HP1 >> HP2 >> MHP1 >> MHP2 >> fireOn >> isFacingLeft;
	//std::cout << v.x << v.y << "\t gun P1: "<<gunP1 << " gun P2 : "<< gunP2 << " HP P1 : " << HP1 << " HP P2 : "<< HP2 << " " << MHP1 << MHP2 << " FireOn P1 : " << fireOn << " FacingLeft : "<< isFacingLeft << std::endl;
	mPhysics->setPosition(mGameWorld->getPlayerID(),v);
	mPhysics->syncPos(mGameWorld->getPlayerID());

	//P1 and P2 guns
	//mGameWorld->setPlayerWeaponID(mWeapon->getWeaponID(gunP1));
	//mGameWorld->setCoPlayerWeaponID(mWeapon->getWeaponID(gunP2));
	mWeapon->insertWeaponType(mGameWorld->getPlayerID(),gunP1);
	mWeapon->insertWeaponType(mGameWorld->getCoPlayerID(),gunP2);

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
	if(mContext.UDPMode == UDPAgent::None)
		return;
	if(mUDP == nullptr){
		if(mContext.UDPMode == UDPAgent::Mode::Client){
			if(mDiscover == nullptr){

				lookForServer();
				//std::cout << "Look for server" << std::endl;
				return;
			}
		}
		else if(mContext.UDPMode == UDPAgent::Mode::Server){
			startUDPServer(UDPAgent::DEFAULT_PORT);
			//std::cout << "gameState: started as Server." << std::endl;
			return;
		}
	}
	//std::cout << "hello from network system update" << std::endl;
	if(mInitialized){
		static int cpt=0;
		if(cpt++ >= DEFAULT_INPUT_SYNC_FRAME_COUNT){
			cpt=0;
			if(mContext.UDPMode == UDPAgent::Mode::Server){
				//std::cout << mPhysics->getPosition(mGameWorld->getPlayerID()).x << mPhysics->getPosition(mGameWorld->getPlayerID()).y << "\t gun P1: "<< mGameWorld->getPlayerWeaponID() << " gun P2 : "<< mGameWorld->getCoPlayerWeaponID() << " HP P1 : " << mHealth->getCurrentHealth(mGameWorld->getPlayerID()) << " HP P2 : "<< mHealth->getCurrentHealth(mGameWorld->getCoPlayerID()) << " " << mHealth->getMaxHealth(mGameWorld->getPlayerID()) << mHealth->getMaxHealth(mGameWorld->getCoPlayerID()) << " FireOn P1 : " << mLogic->getLogic(Logic::fireOn) << " FacingLeft : "<< mLogic->getLogic(Logic::isFacingLeft) << std::endl;
				mUDP->send(SyncFromServerCommand::make(
						mPhysics->getPosition(mGameWorld->getPlayerID()),
						mWeapon->getWeaponType(mGameWorld->getPlayerWeaponID()),
						mWeapon->getWeaponType(mGameWorld->getCoPlayerWeaponID()),
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

	}//fin if initialized
	else {
		mDiscover->update();
		//std::cout << "Discover updated" << std::endl;
		if(mContext.UDPMode == UDPAgent::Client && mDiscover->getDestPort() !=0){
			startUDPClient(sf::Socket::AnyPort,mDiscover->getDestIp(), mDiscover->getDestPort() );
			//std::cout << "Client started and connected to "<< mDiscover->getDestIp().toString() << " and port "<< mDiscover->getDestPort() << std::endl;
			sendReady();
		}
	}
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
		std::cout << "UDP Server Can't bind socket to port " << srcPort << std::endl;
		exit(-1);
	}
	mDiscover.reset(new NetPlayerDiscover(mContext, UDPAgent::DEFAULT_DISCOVER_PORT, mUDP->getSrcPort()));
}
void NetworkSystem::lookForServer(){
	mDiscover.reset(new NetPlayerDiscover(mContext, UDPAgent::DEFAULT_DISCOVER_PORT, 0));
}
//Client mode
void NetworkSystem::startUDPClient(int srcPort, sf::IpAddress destIp, int destPort){
	mUDP.reset(new UDPAgent(srcPort,destIp, destPort));
	mUDP->addObserver(this);
	try{
		mUDP->start();
		running = true;
	}
	catch(UDPException e){
		std::cout << "UDP Client Can't bind socket to port " << srcPort << std::endl;
		exit(-1);
	}
}

void NetworkSystem::insertNetworkID(Entity entity){


}
NetworkSystem::NetworkID NetworkSystem::getEntityNetworkID(Entity entity){

}
Entity NetworkSystem::getNetorkIDEntity( NetworkSystem::NetworkID netID){

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
