/*
 * Previous.h
 *
 *  Created on: 17 juin 2016
 *      Author: admin
 */

#ifndef DIJKSTRA_PREVIOUS_H_
#define DIJKSTRA_PREVIOUS_H_

#include "../dijkstrainterface/previousinterface.h"
class VertexInterface;
#include <vector>
#include <tr1/unordered_map>

using namespace std::tr1;

class Previous : public PreviousInterface {

private:
	unordered_map<VertexInterface*, VertexInterface*> previous;

public:
	Previous();
	virtual ~Previous();
	void setValue(VertexInterface* vertex, VertexInterface* value) override;
	VertexInterface* getValue(VertexInterface* vertex) override;
	vector<VertexInterface*> getShortestPathTo(VertexInterface* vertex, VertexInterface* r) override;
};

#endif /* DIJKSTRA_PREVIOUS_H_ */
