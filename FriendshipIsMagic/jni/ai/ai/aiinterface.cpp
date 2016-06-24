/*
 * aiinterface.cpp
 *
 *  Created on: 22 juin 2016
 *      Author: admin
 */

#include "aiinterface.h"
#include <vector>
#include "monster.h"
#include "playerandstuff.h"
#include "../matrix/matrix.h"
#include "../dijkstra/dijkstra.h"
#include "../dijkstrainterface/vertexinterface.h"
#include "../../player.h"
#include "../dijkstra/previous.h"
#include "monstercontroller.h"
#include <iostream>

AiInterface::AiInterface():
mMonsterController(new MonsterController()) 
{
}

AiInterface::~AiInterface() {
}

void AiInterface::setPath(int mobID, float playerX, float playerY, Matrix& g){
	int iX = int(playerX + 0.5)/100;
	int iY = int(playerY + 0.5)/100;

	VertexInterface* vertex = new VertexInterface();
	vertex->setVertex('J', iX, iY );
	VertexInterface& v = *vertex;

	Dijkstra dijkstra;
	auto previous = dijkstra.dijkstra(g, v);
	VertexInterface* next = previous->getValue(&v);
    mMonsterController->setTarget(vertex);
	//mMonsterController->nextPosition = {next->getX(),next->getY()};

	mMonsterController->storePath(*previous);
	//mMonsterController->currentPosition = {iX,iY};
	//std::cout << previous.getSize() << std::endl;

}

AiInterface::Action AiInterface::giveOrder(int mobID, float playerX, float playerY, Matrix& g){
	//for all types of monster
	 AiInterface::setPath(mobID, playerX, playerY, g);
	 return mMonsterController->translateOrder();
}
