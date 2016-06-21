/*
 * UDPtestClass.h
 *
 *  Created on: 21 juin 2016
 *      Author: edwardvergara
 */

#ifndef UDPTESTCLASS_H_
#define UDPTESTCLASS_H_


#include <SFML/Network/Packet.hpp>
#include "UDPAgent.h"
#include <queue>          // std::queue


class UDPtestClass : public UDPListener {
public:
	UDPtestClass();
	virtual ~UDPtestClass();
	void Notify(sf::Packet pkt) override;
	void testRoutine();
private:
	std::queue<sf::Packet> packetBuf;
};

#endif /* UDPTESTCLASS_H_ */
