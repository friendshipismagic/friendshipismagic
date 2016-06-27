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

#include "../network/udp-agent.h"
#include "../command/command.h"
#include "inputsystem.h"
#define DEFAULT_SYNC_PERIOD 500

class PhysicSystem;
class HealthSystem;

class NetworkSystem : public System, public UDPListener{
public:
	NetworkSystem(World* world, State::Context& context, InputSystem* input, PhysicSystem* aPhysics, HealthSystem* aHealth);
	virtual ~NetworkSystem();
	void update(sf::Time dt);
	void startUDPServer(int srcPort);
	void startUDPClient(int srcPort, sf::IpAddress destIp, int destPort);
	void notify(sf::Packet pkt);

	bool isRunning() const { return running;}
	void updateCoPlayerInput(sf::Packet pkt);
	bool getInputState(Input input);
	void Sync(sf::Packet pkt);

	sf::Time getPeriode() const { return periode;}

	void setPeriode(sf::Time periode) {this->periode = periode;}

private:
	InputSystem* mInput;
	PhysicSystem* mPhysics;
	HealthSystem* mHealth;
	std::unique_ptr<UDPAgent> mUDP;
	std::map<Input, bool> mInputs;
	PacketCommand mCmd;
	sf::Clock mClock;
	sf::Time periode ;

	sf::Clock clk;



	bool running = false;
};

#endif /* NETWORK_SYSTEM_H_ */
