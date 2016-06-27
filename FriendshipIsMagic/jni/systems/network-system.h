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

#include "../network/udp-agent.h"
#include "../command/command.h"

#define DEFAULT_SYNC_PERIOD 2000
#define DEFAULT_INPUT_SYNC_FRAME_COUNT 0

class PhysicSystem;
class HealthSystem;


class NetworkSystem : public System, public UDPListener{
public:
	NetworkSystem(World* world, State::Context& context, InputSystem* input, PhysicSystem* aPhysics, HealthSystem* aHealth, LogicSystem* aLogic);
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

	void SyncFromClient(sf::Packet pkt);
	void SyncFromServer(sf::Packet pkt);

private:
	InputSystem* mInput;
	PhysicSystem* mPhysics;
	HealthSystem* mHealth;
	LogicSystem* mLogic;
	std::unique_ptr<UDPAgent> mUDP;
	std::map<Input, bool> mInputs;
	std::map<Logic, bool> mLogics;
	PacketCommand mCmd;
	//sf::Clock mClock;
	//sf::Time periode;

	sf::Clock clk;



	bool running = false;
};

#endif /* NETWORK_SYSTEM_H_ */
