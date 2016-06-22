/*
 * UDPAgent.cpp
 *
 *  Created on: 20 juin 2016
 *      Author: edwardvergara
 */

#include "UDPAgent.h"
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
	// lie la socket à un port
	mSrcPort = srcPort;
}
/*
 * Create class as client
 */
UDPAgent::UDPAgent(int srcPort, sf::IpAddress ipAddr, int destPort):the_thread() {
	mode = Mode::Client;
	mDestIPAddr = ipAddr;
	running = false;
	listener.setBlocking(false);
	// lie la socket à un port
	mSrcPort = srcPort;
	mDestPort = destPort;
}

UDPAgent::~UDPAgent() {
	// TODO Auto-generated destructor stub
	running = false;
    listener.unbind();
    listener.setBlocking(false);
	if (the_thread.joinable()) the_thread.join();
}

//***** Function to call after creating ServerThread object
void UDPAgent::start() {
	if (listener.bind(mSrcPort) != sf::Socket::Done)
	{
		// erreur...
		 //agentPrintLn("Binding error");
		throw UDPException();
	}
	// This will start the thread by running the serverRoutine function
	running  = true;
	//if(debug)agentPrintLn("Running");
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
		//if(debug)agentPrintLn("Packet sent");
		return true;
	default:
		if(debug) agentPrintLn("Socket sending error!");
		return false;
	}
}

//***** The function runned by the_thread
void UDPAgent::AgentRoutine(){


	string str;
	sf::Socket::Status st;
	unsigned short int tmpPort;
	sf::IpAddress tmpIP;
	while (running) {
		//std::cout << "Hello from thread!\n";

        if (mLastPacketIsRead)
            mLastPacket = std::make_shared<sf::Packet>();
            
        auto& pkt = mLastPacket;
		// socket UDP:
		st = listener.receive(*pkt, tmpIP, tmpPort);
		switch(st){
			case sf::Socket::Done:
				if(mode == Mode::Server){
					mDestIPAddr= tmpIP;
					mDestPort= tmpPort;
					//agentPrintLn("destIp : "+mDestIPAddr.toString()+ " port : "+ std::to_string(mDestPort));
				}
				//pkt >> str;
				//agentPrintLn("Received : "+str);
                if(!(*pkt))
                    std::cout <<"packet not complete" << std::endl;
                else {
                    std::cout <<"packet complete" << std::endl;
                    mLastPacketIsRead = false;
                    sf::Packet p = *pkt;
                    int instruction; 
                    p >> instruction;
                    std::cout << "[[[" << instruction << "]]]" << std::endl;
                    notifyObservers(*pkt);
                }
				break;
            case sf::Socket::Partial:
                std::cout << "§§§§§§§§§ PARTIAL £££££££££" << std::endl;
			case sf::Socket::NotReady:
				//agentPrintLn("Non blocking result");
				break;
            case sf::Socket::Disconnected:
                agentPrintLn("Socket closed!");
                break;
			default:
				//erreur
				if(debug) agentPrintLn("Socket receiving error!");
				break;
		}


		// Tempo de tour de boucle SUPER IMPORTANTE. Elle evite d'overload le CPU.
		// Ne pas prendre de periode inférieur à 1ms!
		std::this_thread::sleep_for (std::chrono::milliseconds(period));
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

void UDPAgent::agentPrintLn(){
	std::cout << "\n";
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
