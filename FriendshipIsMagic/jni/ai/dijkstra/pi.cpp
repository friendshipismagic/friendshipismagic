/*
 * Pi.cpp
 *
 *  Created on: 17 juin 2016
 *      Author: admin
 */

#include "pi.h"

#include <limits>

#include "../dijkstrainterface/vertexinterface.h"

using namespace std;

Pi::Pi() {
	// TODO Auto-generated constructor stub

}

Pi::~Pi() {
	// TODO Auto-generated destructor stub
}

void Pi::setValue(VertexInterface* vertex, int value){
	pi.insert( make_pair(vertex, value) );
}

int Pi::getValue(VertexInterface* vertex){
	auto x = pi.find(vertex);
	if (x != pi.end())
		 return x->second;
	return std::numeric_limits<int>::max();
}
