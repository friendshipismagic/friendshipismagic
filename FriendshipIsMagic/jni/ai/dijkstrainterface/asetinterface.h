/*
 * ASetInterface.h
 *
 *  Created on: 17 juin 2016
 *      Author: admin
 */

#ifndef DIJKSTRAINTERFACE_ASETINTERFACE_H_
#define DIJKSTRAINTERFACE_ASETINTERFACE_H_

#include "vertexinterface.h"

class ASetInterface {
public:
	ASetInterface();
	virtual ~ASetInterface();
	virtual void add(VertexInterface* vertex)=0;
	virtual bool contains(VertexInterface* vertex)=0;
};

#endif /* DIJKSTRAINTERFACE_ASETINTERFACE_H_ */
