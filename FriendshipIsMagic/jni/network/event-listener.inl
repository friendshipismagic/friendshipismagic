/*
 * EventListener.cpp
 *
 *  Created on: 20 juin 2016
 *      Author: edwardvergara
 */

#include "event-listener.h"
template<typename T>
EventListener<T>::EventListener() {
	// TODO Auto-generated constructor stub

}
template<typename T>
EventListener<T>::~EventListener() {
	// TODO Auto-generated destructor stub
}

template<typename T>
void EventListener<T>::pushBuf(T t){
	mQueueMutex.lock();
	mBuf.push(t);
	mQueueMutex.unlock();
}

template<typename T>
T EventListener<T>::frontBuf(){
	mQueueMutex.lock();
	T t = mBuf.front();
	mQueueMutex.unlock();
	return t;
	
}
template<typename T>
void EventListener<T>::popBuf(){
	mQueueMutex.lock();
	mBuf.pop();
	mQueueMutex.unlock();
	
}
template<typename T>
T EventListener<T>::popFrontBuf(){
	mQueueMutex.lock();
	T t = mBuf.front();
	mBuf.pop();
	mQueueMutex.unlock();
	return t;
}

template<typename T>
bool EventListener<T>::emptyBuf(){
	mQueueMutex.lock();
	bool b = mBuf.empty();
	mQueueMutex.unlock();
	return b;
}

