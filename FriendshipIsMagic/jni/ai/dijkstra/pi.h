/*
 * Pi.h
 *
 *  Created on: 17 juin 2016
 *      Author: admin
 */

#ifndef DIJKSTRA_PI_H_
#define DIJKSTRA_PI_H_

#include "../dijkstrainterface/piinterface.h"
class VertexInterface;

#include <tr1/unordered_map>

using namespace std::tr1;

class Pi : public PiInterface {

private :
	unordered_map<VertexInterface*, int> pi;

public:
	Pi();
	virtual ~Pi();
	void setValue(VertexInterface* vertex, int value) override;
	int getValue(VertexInterface* vertex) override;
};

#endif /* DIJKSTRA_PI_H_ */
