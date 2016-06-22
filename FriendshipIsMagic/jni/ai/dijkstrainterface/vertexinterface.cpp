/*
 * VertexInterface.cpp
 *
 *  Created on: 17 juin 2016
 *      Author: admin
 */

#include "vertexinterface.h"

#include <vector>
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "graphinterface.h"

using namespace std;

VertexInterface::VertexInterface(){
	type = 'W';
	x = 0;
	y = 0;
	mIsReachable = false;
}

void VertexInterface::setVertex(char typeOf, unsigned int u, unsigned int v) {
	// TODO Auto-generated constructor stub
	type = typeOf;
	x = u;
	y = v;
}

unsigned int VertexInterface::getX(){
	return x;
}

unsigned int VertexInterface::getY(){
	return y;
}

char VertexInterface::getType(){
	return type;
}

vector<VertexInterface*> VertexInterface::getSuccessors(VertexInterface* A, GraphInterface* g){

	vector<VertexInterface*> neighbours;

	vector<VertexInterface*> graph = g->getAllVertices();
	x = A->getX();
	y = A->getY();


	// Definition of the vectorInterface neighbour's coordinates.
	vector<pair<int,int> > coords = {
			make_pair (x-1, y),
			make_pair (x+1, y),
			make_pair (x, y-1),
			make_pair (x, y+1)
	};

	for(auto coord : coords) {
		// To be sure to stay in the map
		if (coord.first < 0 || coord.first >= 16 || coord.second < 0 || coord.second >= 16)
			continue;

		// Informations about the neighbour
		int index = VertexInterface::coordinatesToMatrix(coord.first,coord.second,g);
		VertexInterface* neighbour = graph[index];
		char neighbourType = neighbour->getType();

		if(neighbourType != 'W')
		{
			neighbours.push_back(neighbour);
		}
	}
	return neighbours;
}


unsigned int VertexInterface::coordinatesToMatrix(unsigned int x, unsigned int y, GraphInterface* g){
	return (x + 16*y);
	//TODO g.size
}
