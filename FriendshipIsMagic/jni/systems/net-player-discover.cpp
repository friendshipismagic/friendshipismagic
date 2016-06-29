/*
 * ClientDiscover.cpp
 *
 *  Created on: 28 juin 2016
 *      Author: edwardvergara
 */

#include "net-player-discover.h"
void sayHello(sf::Packet pkt){
	std::cout << "hello received" << std::endl;
}

NetPlayerDiscover::NetPlayerDiscover(State::Context& context, sf::Uint32 srcPort, sf::Uint32 playerSrcPort) :
mContext(context)
, discover(nullptr){
	// TODO Auto-generated constructor stub
	mPLayerSrcPort = playerSrcPort;
	mSrcPort = srcPort;
	using std::placeholders::_1;
	mCmd.setCommand(BroadcastServerCommand::id, std::bind(&NetPlayerDiscover::registerServer, this, _1));
	mCmd.setCommand(SayHelloCommand::id, sayHello);


	if(mContext.UDPMode == UDPAgent::Mode::Client){

		discover.reset(new UDPAgent(mSrcPort));
		//std::cout << "client discover: listening port" << mSrcPort << std::endl;
	}
	else if(mContext.UDPMode == UDPAgent::Mode::Server){
		discover.reset(new UDPAgent(playerSrcPort+10,sf::IpAddress::Broadcast, srcPort));
		//discover.reset(new UDPAgent(playerSrcPort+10,"localhost", srcPort));
		//std::cout << "server discover: broadcasting from port : "<< playerSrcPort << "and sending message at " << sf::IpAddress::Broadcast.toString() <<  " on port "<<srcPort<< std::endl;

	}
	else{
		//std::cout << "netPlayerDiscover: no mode found for UDPAgent, launching solo mode." << std::endl;
	}
	clk.restart();
	discover->addObserver(this);
	try{
		discover->start();
	}
	catch(UDPException* e){
		std::cout << "Can't bind socket to port " << srcPort << std::endl;
		exit(-1);
	}

}

void NetPlayerDiscover::registerServer(sf::Packet pkt){
	//std::cout << "broadcst received!"<<std::endl;
	pkt >> mDestPort;
	mDestIP = discover->getDestIpAddr();
}

void NetPlayerDiscover::update(){
	if(discover == nullptr){
			std::cout << "UDP error"<< std::endl;
			return;
		}
	time = clk.getElapsedTime();
	if( mContext.UDPMode == UDPAgent::Mode::Server &&
		time > sf::milliseconds(UDPAgent::DEFAULT_DISCOVER_PERIODE))
	{
		discover->send(BroadcastServerCommand::make(mPLayerSrcPort));
		//discover->send(SayHelloCommand::make());
		//std::cout <<"Broadcast sent" << std::endl;
		clk.restart();
	}


	//Receive
	while(emptyBuf() == false){
		//std::cout <<"received something!"<< std::endl;
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

