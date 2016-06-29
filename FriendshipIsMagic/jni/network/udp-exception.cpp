/*
 * UDPException.cpp
 *
 *  Created on: 22 juin 2016
 *      Author: edwardvergara
 */

#include "udp-exception.h"

UDPException::UDPException(){};

UDPException::UDPException(sf::Socket::Status status) {
	switch(status) {
	case sf::Socket::NotReady:
		mMessage = "Not Ready";
		break;
	case sf::Socket::Partial:
		mMessage = "partial status";
		break;
	case sf::Socket::Disconnected:
		mMessage = "Disconnected";
		break;
	case sf::Socket::Error:
		mMessage = "status is error";
		break;
	default:
		mMessage = "Unknown";
	}
}

UDPException::~UDPException() {
	// TODO Auto-generated destructor stub
}

