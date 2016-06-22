/*
 * VertexInterface.h
 *
 *  Created on: 17 juin 2016
 *      Author: admin
 */

#ifndef DIJKSTRAINTERFACE_VERTEXINTERFACE_H_
#define DIJKSTRAINTERFACE_VERTEXINTERFACE_H_

#include <vector>
class GraphInterface;

using namespace std;


class VertexInterface {
private:
	unsigned int x;
	unsigned int y;
	char type;
	bool mIsReachable;

public:
	VertexInterface();
	void setVertex(char type, unsigned int x, unsigned int y);
	virtual ~VertexInterface()=default;
	virtual vector<VertexInterface*> getSuccessors(VertexInterface* A, GraphInterface* g);
	virtual unsigned int getX();
	virtual unsigned int getY();
	char getType();
	static unsigned int coordinatesToMatrix(unsigned int x, unsigned int y, GraphInterface* interface);

};

#endif /* DIJKSTRAINTERFACE_VERTEXINTERFACE_H_ */
