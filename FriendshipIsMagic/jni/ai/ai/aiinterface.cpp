/*
 * aiinterface.cpp
 *
 *  Created on: 22 juin 2016
 *      Author: admin
 */

#include "aiinterface.h"
#include <vector>
#include "monster.h"
#include "../matrix/matrix.h"
#include "../dijkstra/dijkstra.h"
#include "../dijkstrainterface/vertexinterface.h"
#include "../../core/player.h"
#include "../dijkstra/previous.h"
#include "monstercontroller.h"
#include <iostream>

AiInterface::AiInterface():
mMonsterController(new MonsterController())
{
}

AiInterface::~AiInterface() {
}

void AiInterface::setPath(int mobID, float playerX, float playerY, float mobX, float mobY, Matrix& g){
	int iX = int(playerX)/100;
	int iY = int(playerY)/100;

    int mX = int(mobX)/100;
	int mY = int(mobY)/100;

	/*VertexInterface* v = new VertexInterface();
	v->setVertex('J', iX, iY );
	VertexInterface& player = *v;

	VertexInterface* vertex = new VertexInterface();
	vertex->setVertex('M', mX, mY );
	VertexInterface& mob = *vertex;*/

	int player = g.coordinatesToMatrix(iX, iY);
    int mob = g.coordinatesToMatrix(mX, mY);

	Dijkstra dijkstra(&g);
	std::vector<int> previous = dijkstra.dijkstra(player, mob);

	/*int index = previous[mob];
	std::pair<int,int> pos = g.MatrixToCoordinates(previous[mob]);
	while(index != player)
    {
        std::cout << pos.first << " " << pos.second << std::endl;
        pos = g.MatrixToCoordinates(previous[index]);
        index  = previous[index];
    }*/
	//VertexInterface* next = previous->getValue(mob);
    //mMonsterController->setTarget(player);
	//mMonsterController->nextPosition = {next->getX(),next->getY()};

	//mMonsterController->storePath(*previous);
	//mMonsterController->currentPosition = {iX,iY};
	//std::cout << previous.getSize() << std::endl;

}

AiInterface::Action AiInterface::giveOrder(int mobID, float playerX, float playerY, float mobX, float mobY, Matrix& g){
	//for all types of monster
	 AiInterface::setPath(mobID, playerX, playerY, mobX, mobY, g);
	 return mMonsterController->translateOrder();
}
