/*
 * UDPException.h
 *
 *  Created on: 22 juin 2016
 *      Author: edwardvergara
 */

#ifndef NETWORK_UDPEXCEPTION_H_
#define NETWORK_UDPEXCEPTION_H_
#include <exception>

class UDPException: public std::exception
{
public:
	UDPException();
	virtual ~UDPException();
	  /*virtual const char* errorMessage() const throw()
	  {
		return "error";//this->exception();
	  }*/
};
#endif /* NETWORK_UDPEXCEPTION_H_ */
