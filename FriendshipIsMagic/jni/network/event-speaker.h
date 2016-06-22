/*
 * EventSpeaker.h
 *
 *  Created on: 20 juin 2016
 *      Author: edwardvergara
 */

#ifndef EVENTSPEAKER_H_
#define EVENTSPEAKER_H_

//-----------------------------------------------------
// EventSpeaker Class
//-----------------------------------------------------

#include "event-listener.h"
template <typename T> class EventListener;

template <typename T>
class EventSpeaker {
public:
	virtual ~EventSpeaker();		//destructor

	bool addObserver(EventListener<T>* eventListener);
	bool removeObserver(EventListener<T>* eventListener);
	bool notifyObservers(T pkt);

protected:
	//constructor is protected because this class is abstract, it’s only meant to be inherited!
	EventSpeaker();
private:
	std::vector<EventListener<T>*> m_ObserverVec;
	// -------------------------
	// Disabling default copy constructor and default
	// assignment operator.
	// -------------------------
	EventSpeaker(const EventSpeaker& yRef);
	EventSpeaker& operator=(const EventSpeaker& yRef);
};

using UDPSpeaker = EventSpeaker<sf::Packet>;

#include "event-speaker.inl"
#endif /* EVENTSPEAKER_H_ */





