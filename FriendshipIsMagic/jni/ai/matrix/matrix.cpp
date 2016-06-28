/*
 * Matrix.cpp
 *
 *  Created on: 20 juin 2016
 *      Author: admin
 */

#include "matrix.h"

#include <vector>

#include "../dijkstrainterface/graphinterface.h"
#include "../dijkstrainterface/vertexinterface.h"
#include <assert.h>

using namespace std;

Matrix::Matrix(vector<char> mCharG, unsigned int x) {

	mChar = mCharG;
	lengthT = mChar.size();
	lengthX = x;

	for(unsigned int i = 0; i < lengthT; i++)
    {
			VertexInterface* vertex = new VertexInterface();
			auto coords = MatrixToCoordinates(i);
			vertex->setVertex(mChar[i], coords.first, coords.second);
			vertex->setIndex(i);
			assert(vertex != nullptr);
			mVertices.push_back(vertex);
	}
}

Matrix::~Matrix()
{
	for(auto ptr : mVertices)
        delete ptr;
	mVertices.clear();
}

std::pair<unsigned int, unsigned int> Matrix::MatrixToCoordinates(unsigned int S)
{
	unsigned int x = S%lengthX;
	unsigned int y = S/lengthX;
	return {x,y};
}

int Matrix::getWeight(int src, int dst)
{
	return 1;
}

vector<VertexInterface*> Matrix::getAllVertices()
{
	return mVertices;
}

VertexInterface* Matrix::getVertex(int index)
{
    return mVertices[index];
}

int Matrix::coordinatesToMatrix(int x, int y)
{
    return (x + lengthX*y);
}

int Matrix::getLenghtX()
{
    return lengthX;
}

int Matrix::getLenghtT()
{
    return lengthT;
}

vector<int> Matrix::getSuccessors(int index)
{
	vector<int> neighbours;

    std::pair<int, int> pos = MatrixToCoordinates(index);
    int x = pos.first;
    int y = pos.second;

	// Definition of the vectorInterface neighbour's coordinates.
	vector<pair<int,int> > coords = {
			make_pair (x-1, y),
			make_pair (x+1, y),
			make_pair (x, y-1),
			make_pair (x, y+1)
	};

	for(auto coord : coords) {
        // To be sure to stay in the map
        if ((coord.first < 0) || (coord.first >= lengthX) || (coord.second < 0) || (coord.second >= lengthX))
			continue;
		// Informations about the neighbour
		int nindex = coordinatesToMatrix(coord.first,coord.second);
		if ((nindex < 0) || (nindex >= lengthT))
			continue;
		VertexInterface* neighbour = mVertices[nindex];
		if (neighbour == nullptr)
            continue;
		char neighbourType = neighbour->getType();

		if(neighbourType != 'W')
		{
			neighbours.push_back(nindex);
		}
	}
	return neighbours;
}

