/*
 * MonsterManager.h
 *
 *  Created on: 17 juin 2016
 *      Author: admin
 */

#ifndef MONSTERMANAGER_H_
#define MONSTERMANAGER_H_

#include <vector>
#include "playerandstuff.h"
#include "aiinterface.h"

using namespace std;

class Monster;
class PreviousInterface;
class Previous;
class AiInterface;


class MonsterController {
public:
	pair<int,int> currentPosition;
	pair<int,int> nextPosition;
	pair<PreviousInterface*,int> monsterPath;
	MonsterController();
	virtual ~MonsterController();
	void storePath(int mobID, PreviousInterface& previous);
	AiInterface::Action translateOrder();
	void setCurrentAndNext(pair<int,int> current, pair<int,int> next);

};

#endif /* MONSTERMANAGER_H_ */
