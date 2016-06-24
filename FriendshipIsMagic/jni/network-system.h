/*
 * network-system.h
 *
 *  Created on: 24 juin 2016
 *      Author: edwardvergara
 */

#ifndef NETWORK_SYSTEM_H_
#define NETWORK_SYSTEM_H_
#include "system.h"
#include "network/udp-agent.h"
#include "command/command.h"
#include "inputsystem.h"

class NetworkSystem : public System, public UDPListener{
public:
	NetworkSystem(World* world, State::Context& context, InputSystem* input);
	virtual ~NetworkSystem();
	void update(sf::Time dt);
	void startUDPServer(int srcPort);
	void startUDPClient(int srcPort, sf::IpAddress destIp, int destPort);
	void notify(sf::Packet pkt);

	bool isRunning() const { return running;}
	void updateCoPlayerInput(sf::Packet pkt);
	bool getInputState(Input input);
private:
	InputSystem* mInput;
	std::unique_ptr<UDPAgent> mUDP;
	std::map<Input, bool> mInputs;
	PacketCommand mCmd;


	bool running = false;
};

#endif /* NETWORK_SYSTEM_H_ */
