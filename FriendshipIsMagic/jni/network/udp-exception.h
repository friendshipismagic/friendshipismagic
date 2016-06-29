/*
 * UDPException.h
 *
 *  Created on: 22 juin 2016
 *      Author: edwardvergara
 */

#ifndef NETWORK_UDP_EXCEPTION_H_
#define NETWORK_UDP_EXCEPTION_H_
#include <exception>
#include <string>
#include <SFML/Network.hpp>

class UDPException: public std::exception
{
public:
	UDPException();

	UDPException(sf::Socket::Status status);
	virtual ~UDPException();

	const char* what() const throw() override
	{
		return std::string("UDPException : " + mMessage).c_str();//this->exception();
	}

private:
	std::string mMessage;
};
#endif /* NETWORK_UDP_EXCEPTION_H_ */
