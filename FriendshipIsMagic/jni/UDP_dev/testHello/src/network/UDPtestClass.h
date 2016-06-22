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
#include "UDPAgent.h"
#include <queue>          // std::queue
#include "../command/Command.h"
#include "../Player.h"
#include <memory>

class UDPtestClass : public UDPListener {
public:
	void notify(std::shared_ptr<sf::Packet> pkt) override;
	void testRoutine(PacketCommand& cmd);
private:
	sf::Mutex queueMutex;
	std::queue<std::shared_ptr<sf::Packet>> packetBuf ;
};

#endif /* UDPTESTCLASS_H_ */
