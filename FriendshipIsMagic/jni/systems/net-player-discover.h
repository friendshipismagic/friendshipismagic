/*
 * ClientDiscover.h
 *
 *  Created on: 28 juin 2016
 *      Author: edwardvergara
 */

#ifndef NETWORK_NET_PLAYER_DISCOVER_H_
#define NETWORK_NET_PLAYER_DISCOVER_H_
#include <SFML/Network.hpp>
#include "../network/udp-agent.h"
#include "../network/event-listener.h"
#include "../command/command.h"
#include "../states/state.h"


class NetPlayerDiscover : public UDPListener{
public:
	NetPlayerDiscover(State::Context& context,  sf::Uint32 srcPort, sf::Uint32 playerSrcPort);

	virtual ~NetPlayerDiscover();
	void update();
	sf::Time time;
	void registerServer(sf::Packet pkt);
	void endDiscover(sf::Packet pkt);
	sf::Uint32 getDestPort(){return mDestPort;};
	sf::IpAddress getDestIp(){return mDestIP;};
	void notify(sf::Packet pkt);
private:


	State::Context& mContext;
	std::unique_ptr<UDPAgent> discover;
	PacketCommand mCmd;
	sf::Uint32 mPLayerSrcPort = 0;
	sf::Uint32 mSrcPort = 0;
	sf::Uint32 mDestPort = 0;
	sf::IpAddress mDestIP;
	sf::Clock clk;


};

#endif /* NETWORK_NET_PLAYER_DISCOVER_H_ */
