/*
 * PiInterface.h
 *
 *  Created on: 17 juin 2016
 *      Author: admin
 */

#ifndef DIJKSTRAINTERFACE_PIINTERFACE_H_
#define DIJKSTRAINTERFACE_PIINTERFACE_H_

#include "vertexinterface.h"

class PiInterface {
public:
	PiInterface();
	virtual ~PiInterface();
	virtual void setValue(VertexInterface* vertex, int value)=0;
	virtual int getValue(VertexInterface* vertex)=0;
};

#endif /* DIJKSTRAINTERFACE_PIINTERFACE_H_ */
