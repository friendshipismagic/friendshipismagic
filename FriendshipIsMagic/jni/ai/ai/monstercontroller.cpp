/*
 * MonsterManager.cpp
 *
 *  Created on: 17 juin 2016
 *      Author: admin
 */

#include "monstercontroller.h"
#include "AiInterface.h"
#include "monster.h"
#include "../dijkstra/previous.h"
#include "../dijkstrainterface/previousinterface.h"

using namespace std;
class PlayerAndStuff;

MonsterController::MonsterController() {
	// TODO Auto-generated constructor stub
	currentPosition = {0,0};
	nextPosition = {0,0};

}

MonsterController::~MonsterController() {
	// TODO Auto-generated destructor stub
}

void MonsterController::storePath(int mobID, PreviousInterface& previous){
	monsterPath = make_pair(&previous, mobID);
}

void MonsterController::setCurrentAndNext(pair<int,int> current, pair<int,int> next){
	currentPosition = current;
	nextPosition = next;
}

AiInterface::Action MonsterController::translateOrder(){
	int deltaX = currentPosition.first - nextPosition.first;
	int deltaY = currentPosition.second - nextPosition.second;

	if(deltaX == 0 && deltaY == 0){
		return AiInterface::still;
	}

	if(deltaX == 1 && deltaY == 0){
		return AiInterface::left;
	}

	if(deltaX == -1 && deltaY == 0){
		return AiInterface::right;
	}

	if(deltaX == 0 && deltaY == 1){
			return AiInterface::up;
		}

	if(deltaX == 0 && deltaY == -1){
			return AiInterface::down;
		}
}
