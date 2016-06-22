/*
 * Previous.cpp
 *
 *  Created on: 17 juin 2016
 *      Author: admin
 */

#include "previous.h"

#include<vector>
#include "../dijkstrainterface/previousinterface.h"
#include "../dijkstrainterface/vertexinterface.h"

using namespace std;

Previous::Previous() {
	// TODO Auto-generated constructor stub

}

Previous::~Previous() {
	// TODO Auto-generated destructor stub
}

void Previous::setValue(VertexInterface* vertex, VertexInterface* value){
	//setting the result for a vertex
	previous.insert(make_pair(vertex, value));
}

VertexInterface* Previous::getValue(VertexInterface* vertex){
	//returns the value for a vertex or null if this value has not been set
	auto x = previous.find(vertex);
	if (x == previous.end())
		return nullptr;
	return x->second;
}

vector<VertexInterface*> Previous::getShortestPathTo(VertexInterface* vertex, VertexInterface* r){
	//returns the shortest path from the root to a vertex
		vector<VertexInterface*> path;
		while(vertex != nullptr && path.size()<1000)
			{
				path.push_back(vertex);
				vertex = getValue(vertex);
			}
		path.push_back(r);
		return path;
}
