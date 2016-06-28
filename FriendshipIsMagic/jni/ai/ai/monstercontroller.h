/*
 * MonsterManager.h
 *
 *  Created on: 17 juin 2016
 *      Author: admin
 */

#ifndef MONSTERMANAGER_H_
#define MONSTERMANAGER_H_

#include <vector>
#include "aiinterface.h"

using namespace std;

class Monster;
class PreviousInterface;
class Previous;
class AiInterface;
class VertexInterface;


class MonsterController {
public:
	MonsterController();
	virtual ~MonsterController();
    void setTarget(int target);
	void storePath(std::vector<int> previous, int mob);
	AiInterface::Action translateOrder();
	void setCurrentAndNext(pair<int,int> current, pair<int,int> next);

private:
	pair<int,int> currentPosition;
	pair<int,int> nextPosition;
    int mTarget = 0;
    std::vector<int> mPath;

};

#endif /* MONSTERMANAGER_H_ */
