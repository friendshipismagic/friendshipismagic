/*
 * settings-state.h
 *
 *  Created on: 23 juin 2016
 *      Author: edwardvergara
 */

#ifndef SETTINGS_STATE_H_
#define SETTINGS_STATE_H_

#include "state.h"

#include "network/udp-agent.h"
//#include <SFML/System/Mutex.hpp>
#include "command/command.h"
//#include <queue>          // std::queue

class SettingsState: public State , public UDPListener{
public:
	SettingsState(StateStack&, Context&);
	virtual ~SettingsState();
	virtual void init();
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
	void notify(sf::Packet pkt);
private:

	 void printString(sf::Packet pkt);
	 sf::Font* mFont;
	 sf::Time mTextEffectTime;
	 sf::Text mText;
	 bool mShowText;
	 sf::Sprite mBackgroundSprite;
	 sf::Sprite mSettingsSprite;


	 std::unique_ptr<UDPAgent> mAgent;
	 //sf::Mutex mQueueMutex;
	 //std::queue<sf::Packet> packetBuf;
	 PacketCommand mCmd;

};

#endif /* SETTINGS_STATE_H_ */
