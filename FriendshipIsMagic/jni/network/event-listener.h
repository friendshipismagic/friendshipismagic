/*
 * EventListener.h
 *
 *  Created on: 20 juin 2016
 *      Author: edwardvergara
 */

#ifndef EVENTLISTENER_H_
#define EVENTLISTENER_H_

//-----------------------------------------------------
// EventListener Class
//-----------------------------------------------------
#include <SFML/Network/Packet.hpp>
#include <SFML/System/Mutex.hpp>
#include <queue>          // std::queue

using namespace std;
template<typename T> class EventSpeaker;

template<typename T>
class EventListener {
public:
	virtual ~EventListener();		// Destructor
	virtual void notify(T pkt){};
protected:
//constructor is protected because this class is abstract, it’s only meant to be inherited!
	EventListener();
	void pushBuf(T);
	T frontBuf();
	void popBuf();
	T popFrontBuf();
	bool emptyBuf();
private:
	// -------------------------
	// Disabling default copy constructor and default
	// assignment operator.
	// -------------------------
	EventListener(const EventListener& yRef);
	EventListener& operator=(const EventListener& yRef);
	sf::Mutex mQueueMutex;
	std::queue<T> mBuf;
};

using UDPListener = EventListener<sf::Packet> ;
#include "event-listener.inl"
#endif /* EVENTLISTENER_H_ */





