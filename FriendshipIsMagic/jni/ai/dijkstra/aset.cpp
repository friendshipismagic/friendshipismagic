/*
 * ASet.cpp
 *
 *  Created on: 17 juin 2016
 *      Author: admin
 */

#include "aset.h"

#include "../dijkstrainterface/vertexinterface.h"

using namespace std;

ASet::ASet() {
	// TODO Auto-generated constructor stub

}

ASet::~ASet() {
	// TODO Auto-generated destructor stub
}

void ASet::add(VertexInterface* vertex){
	// method add : adds the specified element to this set if it is not already present.
	A.insert(vertex);
}

bool ASet::contains(VertexInterface* vertex){
	//method contains : returns true if this set contains the specified element.
	return (A.find(vertex) != A.end());
}

