/*
 * ASet.h
 *
 *  Created on: 17 juin 2016
 *      Author: admin
 */

#ifndef DIJKSTRA_ASET_H_
#define DIJKSTRA_ASET_H_

#include "../dijkstrainterface/asetinterface.h"

class VertexInterface;

#include <set>

class ASet : public ASetInterface{

private :
	std::set<VertexInterface*> A;

public:
	ASet();
	virtual ~ASet();
	void add(VertexInterface* vertex) override;
	bool contains(VertexInterface* vertex) override;
};

#endif /* DIJKSTRA_ASET_H_ */
