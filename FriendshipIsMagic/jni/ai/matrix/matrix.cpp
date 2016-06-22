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
 using namespace std;

Matrix::Matrix(vector<char> mCharG, unsigned int x) {

	mChar = mCharG;
	lengthT = mChar.size();
	mVertices.resize(lengthT);
	lengthX = x;
	lenghtY = lengthT/x;

	for(std::size_t i = 0; i<lengthT; i++){
		if(mChar[i] != 'W'){
			VertexInterface* vertex = new VertexInterface();
			auto coords = MatrixToCoordinates(i);
			vertex->setVertex(mChar[i], coords.first, coords.second);
			mVertices.push_back(vertex);
		} else mVertices.push_back(nullptr);
	}
}

Matrix::~Matrix() {
	for(auto ptr : mVertices) delete ptr;
	mVertices.clear();
}

std::pair<unsigned int, unsigned int> Matrix::MatrixToCoordinates(unsigned int S){

	unsigned int x = S%lengthX;
	unsigned int y = S/lengthX;
	return {x,y};
}

int Matrix::getWeight(VertexInterface* src, VertexInterface* dst) {
	return 1;
}

vector<VertexInterface*> Matrix::getAllVertices(){

	return mVertices;
}
