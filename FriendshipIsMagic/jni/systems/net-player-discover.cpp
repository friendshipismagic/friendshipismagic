/*
 * ClientDiscover.cpp
 *
 *  Created on: 28 juin 2016
 *      Author: edwardvergara
 */

#include "net-player-discover.h"

NetPlayerDiscover::NetPlayerDiscover(State::Context& context, sf::Uint32 srcPort, sf::Uint32 playerSrcPort) :
mContext(context)
, discover(nullptr){
	// TODO Auto-generated constructor stub
	mPLayerSrcPort = playerSrcPort;
	mSrcPort = srcPort;
	using std::placeholders::_1;
	mCmd.setCommand(BroadcastServerCommand::id, std::bind(&NetPlayerDiscover::registerServer, this, _1));


	if(mContext.UDPMode == UDPAgent::Mode::Client){
		discover.reset(new UDPAgent(mSrcPort));
		//std::cout << "gameState: started as Client." << std::endl;
	}
	else if(mContext.UDPMode == UDPAgent::Mode::Server){
		discover.reset(new UDPAgent(UDPAgent::DEFAULT_DISCOVER_PORT, sf::IpAddress::Broadcast, UDPAgent::DEFAULT_DISCOVER_PORT));
		//std::cout << "gameState: started as Server." << std::endl;

	}
	else{
		//std::cout << "netPlayerDiscover: no mode found for UDPAgent, launching solo mode." << std::endl;
	}
	clk.restart();
	discover->addObserver(this);

}
void NetPlayerDiscover::registerServer(sf::Packet pkt){
	pkt >> mDestPort;
	mDestIP = discover->getDestIpAddr();
}

void NetPlayerDiscover::update(){
	if(discover == nullptr){
			std::cout << "UDP error"<< std::endl;
			return;
		}
	//std::cout << "hello from discover" << std::endl;
	time = clk.getElapsedTime();
	if( mContext.UDPMode == UDPAgent::Mode::Server &&
		time > sf::milliseconds(UDPAgent::DEFAULT_DISCOVER_PERIODE))
	{
		discover->send(BroadcastServerCommand::make(mPLayerSrcPort));
		//std::cout <<"Broadcast sent" << std::endl;
	}
	//Receive
	while(emptyBuf() == false){
		auto pkt = popFrontBuf();
		mCmd.interpret(pkt);
	}
}//fin update

NetPlayerDiscover::~NetPlayerDiscover() {
	// TODO Auto-generated destructor stub
}
void NetPlayerDiscover::notify(sf::Packet pkt){
	pushBuf(pkt);
}

