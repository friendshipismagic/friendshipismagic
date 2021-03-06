/*
 * Previous.h
 *
 *  Created on: 17 juin 2016
 *      Author: admin
 */

#ifndef DIJKSTRA_PREVIOUS_H_
#define DIJKSTRA_PREVIOUS_H_

#include "../dijkstrainterface/previousinterface.h"
#include <vector>
#include <map>

class VertexInterface;

class Previous : public PreviousInterface {


private:
	std::map<VertexInterface*, VertexInterface*> previous;

public:
	Previous();
	virtual ~Previous();
	void setValue(VertexInterface* vertex, VertexInterface* value) override;
	VertexInterface* getValue(VertexInterface* vertex) override;
	vector<VertexInterface*> getShortestPathTo(VertexInterface* vertex, VertexInterface* r) override;
	virtual int getSize() { return previous.size();};
};

#endif /* DIJKSTRA_PREVIOUS_H_ */
