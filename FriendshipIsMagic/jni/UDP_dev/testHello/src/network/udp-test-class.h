/*
 * UDPtestClass.h
 *
 *  Created on: 21 juin 2016
 *      Author: edwardvergara
 */

#ifndef UDPTESTCLASS_H_
#define UDPTESTCLASS_H_


#include <SFML/Network/Packet.hpp>
#include <SFML/System/Mutex.hpp>
#include <queue>          // std::queue

#include "../command/command.h"
//#include "../Player.h"
#include "udp-agent.h"


class UDPtestClass : public UDPListener {
public:
	void notify(sf::Packet pkt) override;
	void testRoutine(PacketCommand& cmd);
private:
	sf::Mutex queueMutex;
	std::queue<sf::Packet> packetBuf ;
};

#endif /* UDPTESTCLASS_H_ */
