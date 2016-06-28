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


unsigned int VertexInterface::getMatrixCoordinates()
{
	return index;
}

void VertexInterface::setIndex(int n)
{
    index = n;
}
