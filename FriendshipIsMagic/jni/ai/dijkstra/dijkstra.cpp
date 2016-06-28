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
#include <iostream>

using namespace std;

Dijkstra::Dijkstra(Matrix* matrix)
: mMatrix(matrix)
{
    for(unsigned int i = 0; i < mMatrix->getAllVertices().size(); i++)
    {
        a.push_back(false);
        pi.push_back(-1);
        previous.push_back(i);
    }
}

Dijkstra::~Dijkstra()
{

}

std::vector<int> Dijkstra::dijkstra(int player, int mob)
{
	a[player] = true;
	pi[player] = 0;

	int pivot = player;

	while(pivot != mob)
	{
	    //std::cout << "dijkstra running " << std::endl;

		vector<int> successorOfPi = mMatrix->getSuccessors(pivot);

		for(int i : successorOfPi)
		{
			if(!a[i])
			{
			    int distance =  pi[pivot] + mMatrix->getWeight(i,pivot);
			    if(pi[i] != -1)
                {
                    if(distance < pi[i])
                    {
                        previous[i] = pivot;
                        pi[i] = distance;
                    }
                }
                else
                {
                    previous[i] = pivot;
                    pi[i] = distance;
                }
			}
		}

		//Searching for the min of pi function
		int piMin = -1;

		for(int j = 0; j < mMatrix->getLenghtT(); j++)
		{
			if(!a[j])
			{
				int l = pi[j];
				if( ((l < piMin) || (piMin == -1)) && (l != -1))
				{
					piMin = l;
					pivot = j;
				}
			}
		}

		if(pivot == mob)
		{
            //std::cout << "dijkstra ending " << std::endl;
			return previous;
		}
		pi[pivot] = piMin;
		a[pivot] = true;
	}

	return previous;
}
