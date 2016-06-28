/*
 * GraphInterface.h
 *
 *  Created on: 17 juin 2016
 *      Author: admin
 */

#ifndef DIJKSTRAINTERFACE_GRAPHINTERFACE_H_
#define DIJKSTRAINTERFACE_GRAPHINTERFACE_H_

#include <vector>

using namespace std;
class VertexInterface;

class GraphInterface {
public:
	GraphInterface();
	virtual ~GraphInterface();
	virtual std::vector<VertexInterface*> getAllVertices()=0;
	virtual int getWeight(int src, int dst)=0;
	virtual int getLenghtX() = 0;
	virtual vector<int> getSuccessors(int index) = 0;
	virtual VertexInterface* getVertex(int index) = 0;
};

#endif /* DIJKSTRAINTERFACE_GRAPHINTERFACE_H_ */


