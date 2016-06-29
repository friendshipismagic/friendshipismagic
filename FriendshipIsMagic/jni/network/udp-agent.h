/*
 * UDPAgent.h
 *
 *  Created on: 20 juin 2016
 *      Author: edwardvergara
 */

#ifndef UDPAgent_H_
#define UDPAgent_H_
#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System/Thread.hpp>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <SFML/Network/Packet.hpp>
#include <memory>
#include "event-speaker.h"
#include "udp-exception.h"

#include <memory>

class UDPAgent : public UDPSpeaker {
public:
	enum Mode{
			Server=0,
			Client=1,
			Solo=2,
			None = -1
		};
	//========== DEBUG
	const bool debug = false;

	static const unsigned short DEFAULT_PORT = 54000;
	static const unsigned short DEFAULT_DISCOVER_PORT = 56000;
	static const unsigned short DEFAULT_DISCOVER_PERIODE = 1000;

	UDPAgent(unsigned short port);
	UDPAgent(unsigned short port, sf::IpAddress ipAddr, unsigned short destPort);
	virtual ~UDPAgent();

	//***** Function to call after creating UDPAgent object
	void	start();

	//***** Set the thread period (in ms)
	void	setPeriod(unsigned short newPeriod);

	//***** Give the thread period (in ms)
	unsigned short 	getPeriod();
	bool  	send(sf::Packet pkt);

	sf::IpAddress getDestIpAddr() const {
		return mDestIPAddr;
	}

	unsigned short int getDestPort() const {
		return mDestPort;
	}

	unsigned short int getSrcPort() const {
		return mSrcPort;
	}
	UDPAgent::Mode getMode();


	sf::IpAddress getLocalAddress();

	sf::IpAddress getPublicAddress();

private:
	sf::UdpSocket listener;
	UDPAgent::Mode mode;
	bool running;
	sf::Thread the_thread;
	sf::IpAddress mDestIPAddr;

	unsigned short int mSrcPort;
	unsigned short int mDestPort;
	void agentPrintLn();
	void agentPrintLn(string str);
	void agentPrint(string str);


	//***** The function runned by the_thread
	void	AgentRoutine();

};

#endif /* UDPAgent_H_ */
