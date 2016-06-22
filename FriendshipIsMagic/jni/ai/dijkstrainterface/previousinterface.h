/*
 * PreviousInterface.h
 *
 *  Created on: 17 juin 2016
 *      Author: admin
 */

#ifndef DIJKSTRAINTERFACE_PREVIOUSINTERFACE_H_
#define DIJKSTRAINTERFACE_PREVIOUSINTERFACE_H_

#include <vector>

#include "vertexinterface.h"

using namespace std;

class PreviousInterface {
public:
	PreviousInterface();
	virtual ~PreviousInterface();
	virtual void setValue(VertexInterface* vertex, VertexInterface* value)=0;
	virtual VertexInterface* getValue(VertexInterface* vertex)=0;
	virtual vector<VertexInterface*> getShortestPathTo(VertexInterface* vertex, VertexInterface* r)=0;
};

#endif /* DIJKSTRAINTERFACE_PREVIOUSINTERFACE_H_ */
