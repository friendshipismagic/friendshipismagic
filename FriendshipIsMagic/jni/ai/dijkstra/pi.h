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

#include <map>


class Pi : public PiInterface {

private :
	std::map<VertexInterface*, int> pi;

public:
	Pi();
	virtual ~Pi();
	void setValue(VertexInterface* vertex, int value) override;
	int getValue(VertexInterface* vertex) override;
};

#endif /* DIJKSTRA_PI_H_ */
