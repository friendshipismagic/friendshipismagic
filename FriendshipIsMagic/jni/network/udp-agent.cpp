/*
 * UDPAgent.cpp
 *
 *  Created on: 20 juin 2016
 *      Author: edwardvergara
 */

#include "udp-agent.h"
//-----------------------------------------------------
// UDPAgent Constructors/Destructor/Launcher
//-----------------------------------------------------

/*
 * Create as server
 */
UDPAgent::UDPAgent(int srcPort):the_thread() {
	mode = Mode::Server;
	mDestPort = 0;
	running = false;
	listener.setBlocking(false);
	mSrcPort = srcPort;
}

/*
 * Create class as client
 */
UDPAgent::UDPAgent(int srcPort, sf::IpAddress ipAddr, int destPort):the_thread() {
	mode = Mode::Client;
	mDestIPAddr = ipAddr;
	running = false;
	//listener.setBlocking(false);
	mSrcPort = srcPort;
	mDestPort = destPort;
}

UDPAgent::~UDPAgent() {
	listener.unbind();
	running = false;
	if (the_thread.joinable()) the_thread.join();
}

//***** Function to call after creating ServerThread object
void UDPAgent::start() {
	if (listener.bind(mSrcPort) != sf::Socket::Done)
		throw UDPException();

	// This will start the thread by running the serverRoutine function
	running  = true;
	the_thread = std::thread(&UDPAgent::AgentRoutine, this);

}

//-----------------------------------------------------
// UDPAgent Functions
//-----------------------------------------------------
bool UDPAgent::send(sf::Packet pkt){
	if(mDestPort == 0)
		return false;
	sf::Socket::Status st = listener.send(pkt, mDestIPAddr, mDestPort);
	switch(st){
	case sf::Socket::Status::Done:
		return true;
	default:
		if(debug) agentPrintLn("Socket sending error!");
		return false;
	}
}

//***** The function runned by the_thread
void UDPAgent::AgentRoutine(){
	string str;
	sf::Socket::Status st = sf::Socket::Status::Disconnected;
	unsigned short int tmpPort;
	sf::IpAddress tmpIP;
	while (running) {

		// Tempo de tour de boucle SUPER IMPORTANTE. Elle evite d'overload le CPU.
		// Ne pas prendre de periode inférieur à 1ms!
		//std::this_thread::sleep_for (std::chrono::milliseconds(period));

		sf::Packet pkt;
		st = listener.receive(pkt, tmpIP, tmpPort);
		switch(st){
			case sf::Socket::Done:
				if(mode == Mode::Server){
					mDestIPAddr= tmpIP;
					mDestPort= tmpPort;
					//agentPrintLn("destIp : "+mDestIPAddr.toString()+ " port : "+ std::to_string(mDestPort));
				}
				notifyObservers(pkt);
				break;
            case sf::Socket::Partial:
                std::cout << "Socket partially received" << std::endl;
			case sf::Socket::NotReady:
				//agentPrintLn("Non blocking result");
				break;
            case sf::Socket::Disconnected:
                agentPrintLn("Socket closed!");
                break;
			default:
				if(debug) agentPrintLn("Socket receiving error!");
				break;
		}



	}
}


//***** Set the thread period (in ms)
void UDPAgent::setPeriod(int newPeriod) {
	period = newPeriod;
}

//***** Give the thread period (in ms)
int UDPAgent::getPeriod() {
	return period;
}

UDPAgent::Mode UDPAgent::getMode(){
	return mode;
}

void UDPAgent::agentPrintLn(){
	std::cout << "\n";
}

sf::IpAddress UDPAgent::getLocalAddress(){
	return sf::IpAddress::getLocalAddress();
}

sf::IpAddress UDPAgent::getPublicAddress(){
	return sf::IpAddress::getPublicAddress();
}

void UDPAgent::agentPrintLn(string str){
	if(mode == Mode::Server)
		std::cout << "UDPServer : " << str << std::endl;
	else
		std::cout << "UDPClient : " << str << std::endl;
}

void UDPAgent::agentPrint(string str){
	if(mode == Mode::Server)
		std::cout  << "UDPServer : " << str;
	else
		std::cout  << "UDPClient : " << str;
}
