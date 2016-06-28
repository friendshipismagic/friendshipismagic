/*
 * network-system.h
 *
 *  Created on: 24 juin 2016
 *      Author: edwardvergara
 */

#ifndef NETWORK_SYSTEM_H_
#define NETWORK_SYSTEM_H_
#include <SFML/System/Time.hpp>

#include "system.h"
#include "inputsystem.h"
#include "logicsystem.h"
#include "weaponsystem.h"

#include "../network/udp-agent.h"
#include "../command/command.h"

#define DEFAULT_SYNC_PERIOD 2000
#define DEFAULT_INPUT_SYNC_FRAME_COUNT 0

class NetPlayerDiscover;
class PhysicSystem;
class HealthSystem;


class NetworkSystem : public System, public UDPListener{
public:
	using NetworkID = Entity;
	NetworkSystem(
			World* world,
			State::Context& context,
			InputSystem* input,
			PhysicSystem* aPhysics,
			HealthSystem* aHealth,
			LogicSystem* aLogic,
			WeaponSystem* aWeapon
	);
	virtual ~NetworkSystem();
	void update(sf::Time dt);
	void startUDPServer(int srcPort);
	void startUDPClient(int srcPort, sf::IpAddress destIp, int destPort);
	void notify(sf::Packet pkt);

	bool isRunning() const { return running;}
	//void updateCoPlayerInput(sf::Packet pkt);
	bool getInputState(Input input);
	bool getLogicState(Logic logic);
	//void Sync(sf::Packet pkt);

	void syncFromClient(sf::Packet pkt);
	void syncFromServer(sf::Packet pkt);

	/*
	void askForInit();
	void askForInitReceived(sf::Packet pkt);
	void initFeedbackReceived(sf::Packet pkt);
	void ackInitReceived(sf::Packet pkt);
	*/

	void sendReady();
	void readyReceived(sf::Packet pkt);
	void ackReadyReceived(sf::Packet pkt);

	void insertNetworkID(Entity entity);
	NetworkID getEntityNetworkID(Entity entity);
	Entity getNetorkIDEntity( NetworkID netID);
	bool isInitialized() const {return mInitialized;}
	void lookforServer();

private:
	InputSystem* mInput;
	PhysicSystem* mPhysics;
	HealthSystem* mHealth;
	LogicSystem* mLogic;
	WeaponSystem* mWeapon;
	std::unique_ptr<UDPAgent> mUDP;
	std::unique_ptr<NetPlayerDiscover> mDiscover;
	std::map<Input, bool> mInputs;
	std::map<Logic, bool> mLogics;
	PacketCommand mCmd;
	bool mInitialized = false;
	std::map<NetworkID, Entity> NetEntities;
	//sf::Clock mClock;
	//sf::Time periode;
	sf::Clock clk;



	bool running = false;
};

#endif /* NETWORK_SYSTEM_H_ */
