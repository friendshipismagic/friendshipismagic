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
#include <assert.h>
#include <iostream>

using namespace std;

Previous::Previous() {
	// TODO Auto-generated constructor stub

}

Previous::~Previous() {
	// TODO Auto-generated destructor stub
}

void Previous::setValue(VertexInterface* vertex, VertexInterface* value){
	//setting the result for a vertex
	if (previous.find(vertex) != previous.end())
        previous[vertex] = value;
    else
        previous.insert(make_pair(vertex, value));
	//std::cout << previous.size() << std::endl;
}

VertexInterface* Previous::getValue(VertexInterface* vertex){
	//returns the value for a vertex or null if this value has not been set
	auto x = previous.find(vertex);
	if (x != previous.end())
	    return x->second;
    return nullptr;
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
