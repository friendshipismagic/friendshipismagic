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
#include <iostream>

using namespace std;

Matrix::Matrix(vector<char> mCharG, unsigned int x) {

	mChar = mCharG;
	lengthT = mChar.size();
	lengthX = x;

	for(int i = 0; i < lengthT; i++)
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

	// Definition of the vectorInterface neighbour's coordinates.
	vector<int> coords = {
			index+lengthX,
			index-lengthX,
			index+1,
			index-1
	};

	for(int coord : coords) {
		// Informations about the neighbour
		if ((coord < 0) || (coord >= lengthT))
        {
            //std::cout << coord << std::endl;
            continue;
        }
		VertexInterface* neighbour = mVertices[coord];
		if (neighbour == nullptr)
            continue;
		char neighbourType = neighbour->getType();

		if(neighbourType != 'W')
		{
		    //std::cout << "wall" << std::endl;
			neighbours.push_back(coord);
		}
	}
	return neighbours;
}

