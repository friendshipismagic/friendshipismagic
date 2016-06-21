/*
 * EventSpeaker.cpp
 *
 *  Created on: 20 juin 2016
 *      Author: edwardvergara
 */

#include "EventSpeaker.h"
template<typename T>
EventSpeaker<T>::EventSpeaker() {
	// TODO Auto-generated constructor stub

}
template <typename T>
EventSpeaker<T>::~EventSpeaker() {
	// TODO Auto-generated destructor stub
}




//this method adds an observer to the vector of observers
template <typename T>
bool EventSpeaker<T>::AddObserver( EventListener<T>* eventListener )
{
	typename std::vector<EventListener<T>*>::iterator temp = find(m_ObserverVec.begin(), m_ObserverVec.end(), eventListener);
	//Return false if the observer is already in the vector. This is not expected. But there is nothing really wrong either
	if ( temp != m_ObserverVec.end() )
		return false;

	m_ObserverVec.push_back(eventListener);
	return true;
}

//This method removes an observer from the vector
template<typename T>
bool EventSpeaker<T>::RemoveObserver( EventListener<T>* eventListener )
{
	typename std::vector<EventListener<T>*>::iterator temp = find(m_ObserverVec.begin(), m_ObserverVec.end(), eventListener);
	//Return false if the observer could not be found (and evidently can’t be removed.
	if ( temp == m_ObserverVec.end() )
		return false;
	else
		m_ObserverVec.erase(remove(m_ObserverVec.begin(), m_ObserverVec.end(), eventListener));
	return true;


}

//This Method is very important, it triggers all Notify() methods of all observers.
//The specific code in each class that inherits from observer will be executed
template<typename T>
bool EventSpeaker<T>::NotifyObservers(T pkt)
{
	for(auto const& eventListener: m_ObserverVec) {
		eventListener->Notify(pkt);
	}

	//for_each(m_ObserverVec.begin(), m_ObserverVec.end(), Notify(this));
	//Return false if there are no observers in the vector
	return (m_ObserverVec.size() > 0);
}

