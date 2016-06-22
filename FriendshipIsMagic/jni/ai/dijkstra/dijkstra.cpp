/*
 * Dijkstra.cpp
 *
 *  Created on: 17 juin 2016
 *      Author: admin
 */

#include "dijkstra.h"

#include <vector>
#include <limits>

#include "../dijkstrainterface/asetinterface.h"
#include "../dijkstrainterface/graphinterface.h"
#include "../dijkstrainterface/piinterface.h"
#include "../dijkstrainterface/previousinterface.h"
#include "../dijkstrainterface/vertexinterface.h"
#include "aset.h"
#include "pi.h"
#include "previous.h"

using namespace std;

Dijkstra::Dijkstra() {
	// TODO Auto-generated constructor stub

}

Dijkstra::~Dijkstra() {
	// TODO Auto-generated destructor stub
}


PreviousInterface& Dijkstra::dijkstra(GraphInterface& g, VertexInterface& r){
	ASet aSet;
	Pi pi;
	Previous previous;

	return dijkstra(g,r,aSet,pi,previous);
}


PreviousInterface& Dijkstra::dijkstra(GraphInterface& g,VertexInterface& r, ASetInterface& a, PiInterface& pi, PreviousInterface& previous){

	a.add(&r);
	VertexInterface* pivot = &r;
	pi.setValue(&r, 0);

	//List of the boxes available
	vector<VertexInterface*> L = g.getAllVertices();

	//Initialization of pi(x,infty)
	for(VertexInterface* vertex : L)
	{
		if(vertex != &r)
		{
			pi.setValue(vertex, std::numeric_limits<int>::max());
		}
	}

	for(std::size_t j =0; j<L.size(); j++)
	{
		VertexInterface& x = *pivot;
		vector<VertexInterface*> successorOfPi = x.getSuccessors(pivot, &g);

		//Update function pi
		for(VertexInterface* v : successorOfPi)
		{
			if(!(a.contains(v)))
			{
				if(pi.getValue(pivot) + g.getWeight(&r,pivot) < pi.getValue(v))
				{
					pi.setValue(v, pi.getValue(pivot) + g.getWeight(&r,pivot));
					previous.setValue(v,pivot);
				}
			}
		}

		//Searching for the min of pi function (and the y associated)
		int piMin = std::numeric_limits<int>::max();

		for(VertexInterface* vertex2 : L)
		{
			if(!(a.contains(vertex2)))
			{
				int l = pi.getValue(vertex2);
				if(l<piMin)
				{
					piMin = 1;
					pivot = vertex2;
				}
			}
		}

		if(pivot == nullptr)
		{
			return previous;
		}
		pi.setValue(pivot,piMin);
		a.add(pivot);
	}

	return previous;
}
