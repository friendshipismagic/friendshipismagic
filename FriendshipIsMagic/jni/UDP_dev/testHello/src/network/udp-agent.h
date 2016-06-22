/*
 * UDPAgent.h
 *
 *  Created on: 20 juin 2016
 *      Author: edwardvergara
 */

#ifndef UDPAgent_H_
#define UDPAgent_H_
#include "EventSpeaker.h"
#include <iostream>
#include <SFML/Network.hpp>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <SFML/Network/Packet.hpp>
#include "UDPException.h"
#include <memory>



class UDPAgent : public UDPSpeaker {
public:
	static const int DEFAULT_PERIODE=250;
	static const int DEFAULT_PORT = 54000;
	const bool debug = true;
	UDPAgent(int port);
	UDPAgent(int port, sf::IpAddress ipAddr, int destPort);
	virtual ~UDPAgent();

	//***** Function to call after creating UDPAgent object
	void	start();

	//***** Set the thread period (in ms)
	void	setPeriod(int newPeriod);

	//***** Give the thread period (in ms)
	int 	getPeriod();
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

private:
	sf::UdpSocket listener;
    bool mLastPacketIsRead=true;
    std::shared_ptr<sf::Packet> mLastPacket;
	bool mode;
	bool running;
	int period = DEFAULT_PERIODE;
	std::thread the_thread;
	sf::IpAddress mDestIPAddr;

	unsigned short int mSrcPort;
	unsigned short int mDestPort;
	void agentPrintLn();
	void agentPrintLn(string str);
	void agentPrint(string str);


	//***** The function runned by the_thread
	void	AgentRoutine();
	enum Mode{
		Server,
		Client
	};
};

#endif /* UDPAgent_H_ */
